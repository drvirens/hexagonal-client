//
//  thread_platform.cpp
//  vClientTemplateLib
//
//  Created by Virendra Shakya on 4/21/14.
//  Copyright (c) 2014 Virendra Shakya. All rights reserved.
//

#include <errno.h>
#include "base/thread/thread_platform.h"
#include "base/logging/log.h"
#include "build/build_utils.h"
#include "base/error_handler.h"
#include "base/synchronize/lock.h"
#include "base/synchronize/condition_variable.h"

#if defined(V_PLATFORM_ANDROID)
#elif defined(V_PLATFORM_IOS)

  #include "base/thread/detail/thread_platform_optional_IOS.h"

  typedef IOSThreadOptionalImpl PosixOptionalImpl;

#elif defined(V_PLATFORM_TIZEN)
#else
#error Define optional thread interface
#endif

namespace vbase
{
  
// -------------------------------------------------------------- TThreadParams
class TThreadParams
{
public:
  TThreadParams()
    : mMainEntry(0)
    , mJoinable(false)
    , mThreadPriority(EThreadPriority_Normal)
    , mHandle(0)
    , mConditionVariable(&mLock)
    , mWaitCondition(false)
  {}
  
  TThreadParams(IThreadMainEntryPoint* aMainEntry, bool aJoinable, EThreadPriority aThreadPriority, TPlatformThreadHandle* aHandle)
    : mMainEntry(aMainEntry)
    , mJoinable(aJoinable)
    , mThreadPriority(aThreadPriority)
    , mHandle(aHandle)
    , mConditionVariable(&mLock)
    , mWaitCondition(false)
  {
  }
  
  static void* ThreadEntryFunction(void* aTThreadParamsPtr);
  void Wait()
  {
    mLock.Acquire();
    mWaitCondition = false;
    while(mWaitCondition == false) //while waitcondition is false
    {
      mConditionVariable.Wait();
    }
    mLock.Release();
  }
  void Signal()
  {
    mLock.Acquire();
    mWaitCondition = true;
    mConditionVariable.NotifyOne();
    mLock.Release();
    
  }
  
private:
  IThreadMainEntryPoint* mMainEntry;
  bool mJoinable;
  EThreadPriority mThreadPriority;
  TPlatformThreadHandle* mHandle;
  //WaitableEvent
  TLock mLock;
  TConditionVariable mConditionVariable;
  bool mWaitCondition;
};

// -------------------------------------------------------------- TPlatformThread impl

void* TThreadParams::ThreadEntryFunction(void* aTThreadParamsPtr)
{
  IThreadOptionalInterface<PosixOptionalImpl>::OnThreadMainEnter();
  
  ASSERT( aTThreadParamsPtr != 0 );
  TThreadParams* tThis = static_cast<TThreadParams*>(aTThreadParamsPtr);
  IThreadMainEntryPoint* mainEntry = tThis->mMainEntry;
  ASSERT( mainEntry != 0 );
  
  if( !aTThreadParamsPtr || !mainEntry )
  {
    LOG_ERROR << "aTThreadParamsPtr or mainEntry was NULL";
    return 0;
  }
  
  if(EThreadPriority_Normal != tThis->mThreadPriority)
  {
    TPlatformThread::SetPriority(TPlatformThread::CurrentHandle(), tThis->mThreadPriority);
  }
  
  TPlatformThreadHandle th = TPlatformThread::TPlatformThread::CurrentHandle();
  *(tThis->mHandle) = th;
  
  tThis->Signal();
  
  //TODO: Signal TPlatformThread::Create here
  mainEntry->MainEntry();
  
  
  IThreadOptionalInterface<PosixOptionalImpl>::OnThreadMainExit();
  return 0;
}

TPlatformThreadHandle TPlatformThread::CurrentHandle()
{
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
  
  TThreadParams params(aMainENtry, aJoinable, aPriority, aThreadHandle);
  pthread_t pthreadHandle = 0;
  V_PTHREAD_CALL_RET_ERROR( pthread_create(&pthreadHandle, &attributes, &TThreadParams::ThreadEntryFunction, &params), err );
  ret = !err;
  if( 0 != err)
  {
    errno = err;
    LOG_ERROR << "Could not create thread pthread_create";
  }
  
  pthread_attr_destroy(&attributes);
  
  //wait until thread id is set in the handle (which happens in ThreadEntryPoint)
  if(ret)
  {
    params.Wait();
  }
  ASSERT( pthreadHandle == aThreadHandle->RawHandle() );
  if(pthreadHandle != aThreadHandle->RawHandle())
  {
    LOG_ERROR << "pthreadHandle != aThreadHandle->RawHandle: Serious ERROR in threading";
    //return false;
  }

  return ret;
}

void TPlatformThread::Join(TPlatformThreadHandle* aThreadHandle)
{
  V_PTHREAD_CALL( pthread_join(aThreadHandle->RawHandle(), 0) );
}

void TPlatformThread::SetPriority(TPlatformThreadHandle aThreadHandle, EThreadPriority aPriority)
{
  
}

void TPlatformThread::Yield()
{
  
}

void TPlatformThread::SetName(const char* Name)
{
  //TODO:
}

const char* TPlatformThread::Name()
{
  return 0; //TODO:
}

}
