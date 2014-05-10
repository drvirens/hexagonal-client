//
//  thread_bootstrap_params.cpp
//  vClientTemplateLib
//
//  Created by Virendra Shakya on 5/8/14.
//  Copyright (c) 2014 Virendra Shakya. All rights reserved.
//

#include "base/thread/detail/thread_bootstrap_params.h"
#include "base/thread_syn_logger/macrologger.h"
#include "build/build_utils.h"
#include "base/synchronize/lock.h"
#include "base/synchronize/condition_variable.h"

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
namespace detail
{

void* CThreadBootstrapParams::ThreadEntryFunction(void* aTThreadParamsPtr)
    {
    KERNEL_LOG_INFO(">> CThreadBootstrapParams::ThreadEntryFunction <---- ENTER");
    
    IThreadOptionalInterface<PosixOptionalImpl>::OnThreadMainEnter();
    
    ASSERT( aTThreadParamsPtr != 0 );
    CThreadBootstrapParams* tThis = static_cast<CThreadBootstrapParams*>(aTThreadParamsPtr);
    IThreadMainEntryPoint* mainEntry = tThis->mMainEntry;
    ASSERT( mainEntry != 0 );
    if( !aTThreadParamsPtr || !mainEntry )
        {
        return 0;
        }
    
    KERNEL_LOG_INFO(">> CThreadBootstrapParams:: before CurrentHandle <----");
    
    *(tThis->mHandle) = TPlatformThread::TPlatformThread::CurrentHandle();
    
    KERNEL_LOG_INFO(">> CThreadBootstrapParams:: after CurrentHandle <----");
    
    if(EThreadPriority_Normal != tThis->mThreadPriority)
        {
        TPlatformThread::SetPriority(TPlatformThread::CurrentHandle(), tThis->mThreadPriority);
        }
    
//    tThis->Signal(); //Signal for Wait in TPlatformThread::Create
    mainEntry->MainEntry();
    
    
    
    IThreadOptionalInterface<PosixOptionalImpl>::OnThreadMainExit();
    
    KERNEL_LOG_INFO(">> CThreadBootstrapParams::ThreadEntryFunction <---- EXIT");
    return 0;
    }
    
CThreadBootstrapParams* CThreadBootstrapParams::New(IThreadMainEntryPoint* aMainEntry,
                            bool aJoinable,
                            EThreadPriority aThreadPriority,
                            TPlatformThreadHandle* aHandle)
    {
    KERNEL_LOG_INFO(">> CThreadBootstrapParams::New");
    CThreadBootstrapParams* obj = new CThreadBootstrapParams(aMainEntry, aJoinable, aThreadPriority, aHandle);
    if(obj)
        {
        obj->Construct();
        }
    return obj;
    }
    
void CThreadBootstrapParams::Construct()
    {
    KERNEL_LOG_INFO(">> CThreadBootstrapParams::Construct");
//    mLock = new TLock();
//    mConditionVariable = new TConditionVariable(mLock);
    }

CThreadBootstrapParams::CThreadBootstrapParams(IThreadMainEntryPoint* aMainEntry, bool aJoinable, EThreadPriority aThreadPriority, TPlatformThreadHandle* aHandle)
    : mMainEntry(aMainEntry)
    , mJoinable(aJoinable)
    , mThreadPriority(aThreadPriority)
    , mHandle(aHandle)
//    , mLock(0)
//    , mConditionVariable(0)
//    , mWaitCondition(false)
    {
    
    }
    
CThreadBootstrapParams::~CThreadBootstrapParams()
    {
    KERNEL_LOG_INFO(">> CThreadBootstrapParams::destructor");
//    delete mConditionVariable; mConditionVariable= 0;
//    delete mLock; mLock = 0;
    }

//void CThreadBootstrapParams::Wait()
//    {
//    LOG_INFO(">> CThreadBootstrapParams::Wait");
//    mLock->Acquire();
//    while(mWaitCondition == false)
//        {
//        LOG_INFO("Waiting...");
//        mConditionVariable->Wait();
//        }
//    mLock->Release();
//    }
//
//void CThreadBootstrapParams::Signal()
//    {
//    LOG_INFO(">> CThreadBootstrapParams::Signal");
//    //mLock->Acquire(); 
//    mWaitCondition = true;
//    mConditionVariable->NotifyOne();
//    //mConditionVariable.NotifyAll();
//    //mLock->Release();
//    }
    
    
 

} //namespace detail
} //namespace vbase


