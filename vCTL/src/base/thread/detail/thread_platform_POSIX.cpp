//
//  thread_platform.cpp
//  vClientTemplateLib
//
//  Created by Virendra Shakya on 4/21/14.
//  Copyright (c) 2014 Virendra Shakya. All rights reserved.
//

#include <string.h>
#include <errno.h>
#include <time.h> //for sleep::nanoseconds
#include <sched.h> //for yield

#include "build/build_utils.h"
#include "base/time/time.h" //for sleep
#include "base/thread_syn_logger/macrologger.h"
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
    KERNEL_LOG_INFO(">> TPlatformThread::CurrentHandle: CurrentID: [ %d ]", CurrentID());
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

TThreadHandle TPlatformThread::Create(size_t aStackSize, bool aJoinable, IThreadMainEntryPoint* aMainENtry, TPlatformThreadHandle* aThreadHandle, EThreadPriority aPriority)
    {
    KERNEL_LOG_INFO(">> TPlatformThread::Create");
    
    IThreadOptionalInterface<PosixOptionalImpl>::OnPreThreadCreate();
    bool ret = false;
    int err = 0;
    
    pthread_attr_t attributes;
    int e = pthread_attr_init(&attributes);
    if ( 0 != e )
        {
        KERNEL_LOG_ERROR("pthread_attr_init error = [%s]", strerror(errno));
        }

    if(!aJoinable)
        {
        e = pthread_attr_setdetachstate(&attributes, PTHREAD_CREATE_DETACHED); //by default, pthread is joinable so explicitly make it detached if aJoinable==false
        if ( 0 != e )
            {
            KERNEL_LOG_ERROR("pthread_attr_setdetachstate error = [%s]", strerror(errno));
            }
        }
    if(0 == aStackSize)
        {
        aStackSize = IThreadOptionalInterface<PosixOptionalImpl>::GetDefaultStackSize(attributes);
        }
    if(aStackSize > 0)
        {
        e = pthread_attr_setstacksize(&attributes, aStackSize);
        if ( 0 != e )
            {
            KERNEL_LOG_ERROR("pthread_attr_setstacksize error = [%s]", strerror(errno));
            }
        }
    
    detail::CThreadBootstrapParams* params = detail::CThreadBootstrapParams::New(aMainENtry, aJoinable, aPriority, aThreadHandle);
    pthread_t pthreadHandle = 0;
    e = pthread_create(&pthreadHandle, &attributes, &detail::CThreadBootstrapParams::ThreadEntryFunction, params);
    if ( 0 != e )
        {
        KERNEL_LOG_ERROR("pthread_create error = [%s]", strerror(errno));
        }

    ret = !err;
    if(0 != err)
        {
        errno = err;
        KERNEL_LOG_ERROR("Could not create thread pthread_create");
        }
    
    e = pthread_attr_destroy(&attributes);
    if ( 0 != e )
        {
        KERNEL_LOG_ERROR("pthread_attr_destroy error = [%s]", strerror(errno));
        }

    
    //TODO: Use Rendezevous Syncrhonization here:
    // Signal() here and outside TPlatformThread::Create, use Wait()
    /*
        
    Thread Parent                              Thread Child
    
    Create();                                  DoThreadInit();
    child.Wait();                              child.Signal();
    parent.Signal();                           parent.Wait();
    
    NOTE: above will cause un-necessary thread-switch. Figure out how?

    Thread Parent                              Thread Child
    
    Create();                                  DoThreadInit();
    parent.Signal();                           child.Signal();
    child.Wait();                              parent.Wait();
     */
    
        //wait until thread id is set in the handle (which happens in ThreadEntryPoint)
//    if(ret)
//        {
//        params->Wait(); //Wait to be signalled in TThreadParams::ThreadEntryFunction
//        }
//    ASSERT( pthreadHandle == aThreadHandle->RawHandle() );
//    if(pthreadHandle != aThreadHandle->RawHandle())
//        {
//        KERNEL_LOG_ERROR ("pthreadHandle != aThreadHandle->RawHandle: Serious ERROR in threading");
//            //return false;
//        }
    
    return pthreadHandle;
    }

void TPlatformThread::Join(TPlatformThreadHandle* aThreadHandle)
    {
    KERNEL_LOG_INFO(">> pthread_join called");
    TThreadHandle handle = aThreadHandle->RawHandle();
    int e = pthread_join(handle, 0);
    if( 0 != e )
        {
        KERNEL_LOG_ERROR("pthread_join error = [%s]", strerror(errno));
        }

    }

void TPlatformThread::Yield()
    {
    /**
     TODO: Look into this later: In the Linux implementation, sched_yield() always succeeds.
     http://man7.org/linux/man-pages/man2/sched_yield.2.html
     */
    int e = sched_yield();
    if( 0 != e )
        {
        KERNEL_LOG_ERROR("sched_yield error = [%s]", strerror(errno));
        }

    }

void TPlatformThread::Sleep(long aSeconds)
    {
    #define NSEC_PER_USEC 1000ull
    //const struct timespec t = {.tv_nsec = static_cast<long>(aSeconds * 50000*NSEC_PER_USEC)};
    long seconds = aSeconds;
    struct timespec t = {.tv_nsec =  seconds * 50000 * 1000 };
    
    struct timespec remaining = {0, 0};
    
    int e = nanosleep(&t, NULL);
    //KERNEL_LOG_INFO("Sleep returned : %s, errno = %d, ret = %d", strerror(errno), errno, e);
    while( -1 == e && EINTR == errno ) //-1 == e interuppted by signal handler
        {
        t = remaining;
        nanosleep(&t, &remaining);
        }


//    struct timespec a;
//    a.tv_nsec = aSeconds * 10000;
//
//    /** THE FIX! **/
//    a.tv_sec = 0;
//    /** THE FIX! **/
//KERNEL_LOG_INFO("Sleep:start");
//    nanosleep(&a,NULL);

    /*
    struct timespec requested = {0, static_cast<long>(aSeconds * TTime::kNanoSecondsPerSecond)};
    int e = nanosleep(&requested, 0);
    KERNEL_LOG_INFO("Sleep returned : %s, errno = %d, ret = %d", strerror(errno), errno, e);
*/
//    struct timespec remaining = {0};
//    requested.tv_sec = 0;
//    int64_t nanoSeconds = aSeconds * TTime::kNanoSecondsPerSecond;
//    requested.tv_nsec = (long)nanoSeconds;
//    requested.tv_nsec = (long)nanoSeconds;
    
        //TODO: CHeck if thread has permissions to sleep. needs TLS to be implemented so do in phase2
//    int e = nanosleep(&requested, &remaining);
//    KERNEL_LOG_INFO("Sleep returned : %s, errno = %d", strerror(errno), errno);
//    while( -1 == e && EINTR == errno ) //-1 == e interuppted by signal handler
//        {
//        requested = remaining;
//        nanosleep(&requested, &remaining);
//        }
    
    }
    
} //namespace vbase

