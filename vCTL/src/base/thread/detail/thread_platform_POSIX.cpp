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
  {}
  
  TThreadParams(IThreadMainEntryPoint* aMainEntry, bool aJoinable, EThreadPriority aThreadPriority, TPlatformThreadHandle* aHandle)
    : mMainEntry(aMainEntry)
    , mJoinable(aJoinable)
    , mThreadPriority(aThreadPriority)
    , mHandle(aHandle)
  {}
  
  static void* ThreadEntryFunction(void* aTThreadParamsPtr);
  void Wait()
  {
    
  }
  
private:
  IThreadMainEntryPoint* mMainEntry;
  bool mJoinable;
  EThreadPriority mThreadPriority;
  TPlatformThreadHandle* mHandle;
  //WaitableEvent
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
    LOG_ERROR << "";
    return 0;
  }
  
  if(EThreadPriority_Normal != tThis->mThreadPriority)
  {
    TPlatformThread::SetPriority(TPlatformThread::CurrentHandle(), tThis->mThreadPriority);
  }
  
  *(tThis->mHandle) = TPlatformThread::CurrentHandle();
  
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
  return pthread_mach_thread_np(pthread_self());
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
  err = pthread_attr_init(&attributes);
  if(0 != err) //error
  {
    errno = err;
    LOG_ERROR << "Could not init pthread_attr_init";
  }
  
  if(!aJoinable)
  {
    err = pthread_attr_setdetachstate(&attributes, PTHREAD_CREATE_DETACHED); //by default, pthread is joinable so explicitly make it detached if aJoinable==false
    if( 0 != err)
    {
      errno = err;
      LOG_ERROR << "Could not make thread un-joinable pthread_attr_setdetachstate error";
    }
  }
  
  if(0 == aStackSize)
  {
    aStackSize = IThreadOptionalInterface<PosixOptionalImpl>::GetDefaultStackSize(attributes);
  }
  if(aStackSize > 0)
  {
    err = pthread_attr_setstacksize(&attributes, aStackSize);
    if( 0 != err)
    {
      errno = err;
      LOG_ERROR << "Could not pthread_attr_setstacksize error";
    }
  }
  
  TThreadParams params(aMainENtry, aJoinable, aPriority, aThreadHandle);
  pthread_t pthreadHandle = 0;
  err = pthread_create(&pthreadHandle, &attributes, &TThreadParams::ThreadEntryFunction, &params);
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
    return false;
  }

  return ret;
}

void TPlatformThread::Join(TPlatformThreadHandle* aThreadHandle)
{
  
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
