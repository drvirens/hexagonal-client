//
//  thread_platform.cpp
//  vClientTemplateLib
//
//  Created by Virendra Shakya on 4/21/14.
//  Copyright (c) 2014 Virendra Shakya. All rights reserved.
//

#include <errno.h>
#include <time.h> //for sleep::nanoseconds
#include <sched.h> //for yield

#include "base/time/time.h" //for sleep
#include "base/thread_syn_logger/macrologger.h"

#include "build/build_utils.h"
#include "base/error_handler.h"
#include "base/synchronize/lock.h"
#include "base/synchronize/condition_variable.h"

#include "base/thread/detail/thread_bootstrap_params.h"


#if defined(V_PLATFORM_ANDROID)
    #error for android do we need any other things like thread_platform_optional_IOS.h?
#elif defined(V_PLATFORM_IOS)

    #include "base/thread/detail/ios/thread_platform_optional_IOS.h"
    typedef IOSThreadOptionalImpl PosixOptionalImpl;

#else
    #error Define optional thread interface
#endif


namespace vbase
{



TPlatformThreadHandle TPlatformThread::CurrentHandle()
    {
    LOG_INFO(">> TPlatformThread::CurrentHandle: CurrentID: [ %d ]", CurrentID());
    return TPlatformThreadHandle(pthread_self(), CurrentID());
    }

TPlatformThreadID TPlatformThread::CurrentID()
    {
        //pthreads don't have concept of id, unlike windows, so we need to cross over to kernel space
#if defined(V_PLATFORM_DARWIN)
    unsigned int r = pthread_mach_thread_np(pthread_self());
    return r;
#elif defined(V_PLATFORM_ANDROID)
    return gettid();
#elif defined(V_PLATFORM_TIZEN)
    return pthread_self(); //TODO: Okay???
#else
#error Add support for TPlatformThread::CurrentID in your code
#endif
    }

bool TPlatformThread::Create(size_t aStackSize, bool aJoinable, IThreadMainEntryPoint* aMainENtry, TPlatformThreadHandle* aThreadHandle, EThreadPriority aPriority)
    {
    LOG_INFO(">> TPlatformThread::Create");
    
    IThreadOptionalInterface<PosixOptionalImpl>::OnPreThreadCreate();
    bool ret = false;
    int err = 0;
    
    pthread_attr_t attributes;
    V_PTHREAD_CALL( pthread_attr_init(&attributes) );
    if(!aJoinable)
        {
        V_PTHREAD_CALL( pthread_attr_setdetachstate(&attributes, PTHREAD_CREATE_DETACHED) ); //by default, pthread is joinable so explicitly make it detached if aJoinable==false
        }
    if(0 == aStackSize)
        {
        aStackSize = IThreadOptionalInterface<PosixOptionalImpl>::GetDefaultStackSize(attributes);
        }
    if(aStackSize > 0)
        {
        V_PTHREAD_CALL( pthread_attr_setstacksize(&attributes, aStackSize) );
        }
    
    detail::CThreadBootstrapParams* params = detail::CThreadBootstrapParams::New(aMainENtry, aJoinable, aPriority, aThreadHandle);
    pthread_t pthreadHandle = 0;
    V_PTHREAD_CALL_RET_ERROR( pthread_create(&pthreadHandle, &attributes, &detail::CThreadBootstrapParams::ThreadEntryFunction, params), err );
    ret = !err;
    if(0 != err)
        {
        errno = err;
        LOG_ERROR("Could not create thread pthread_create");
        }
    
    LOG_INFO(">> pthread_create called");
    
    pthread_attr_destroy(&attributes);
    
        //wait until thread id is set in the handle (which happens in ThreadEntryPoint)
    if(ret)
        {
        params->Wait(); //Wait to be signalled in TThreadParams::ThreadEntryFunction
        }
    ASSERT( pthreadHandle == aThreadHandle->RawHandle() );
    if(pthreadHandle != aThreadHandle->RawHandle())
        {
        LOG_ERROR ("pthreadHandle != aThreadHandle->RawHandle: Serious ERROR in threading");
            //return false;
        }
    
    return ret;
    }

void TPlatformThread::Join(TPlatformThreadHandle* aThreadHandle)
    {
    LOG_INFO(">> pthread_join called");
    TThreadHandle handle = aThreadHandle->RawHandle();
    V_PTHREAD_CALL( pthread_join(handle, 0) );
    //V_PTHREAD_CALL( pthread_join(pthread_self(), 0) );
    }

void TPlatformThread::Yield()
    {
    /**
     TODO: Look into this later: In the Linux implementation, sched_yield() always succeeds.
     http://man7.org/linux/man-pages/man2/sched_yield.2.html
     */
    V_PTHREAD_CALL( sched_yield() );
    }

void TPlatformThread::Sleep(int64_t aSeconds)
    {
    struct timespec requested;
    struct timespec remaining;
    requested.tv_sec = 0;
    int64_t nanoSeconds = aSeconds * TTime::kNanoSecondsPerSecond;
    requested.tv_nsec = (long)nanoSeconds;
        //TODO: CHeck if thread has permissions to sleep. needs TLS to be implemented so do in phase2
    int e = nanosleep(&requested, &remaining);
    //LOG_ERROR << "Sleep returned : " << strerror(e);
    LOG_INFO("Sleep returned : %s", strerror(e));
    while( -1 == e && EINTR == errno ) //-1 == e interuppted by signal handler
        {
        requested = remaining;
        nanosleep(&requested, &remaining);
        }
    }
    
} //namespace vbase

