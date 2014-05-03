//
//  thread_loopless.cpp
//  vClientTemplateLib
//
//  Created by Virendra Shakya on 4/27/14.
//  Copyright (c) 2014 Virendra Shakya. All rights reserved.
//

#include "base/thread/thread_loopless.h"
#include "base/logging/log.h"
#include "build/build_utils.h"

namespace vbase
{
static const size_t kStackSize = 0;
static const bool kJoinable = true;
static const EThreadPriority kLooplessThreadDefaultPriority = EThreadPriority_Normal;

TLooplessThread::TLooplessThread(std::string& aThreadName)
    :  mLock()
    , mConditionVariable(&mLock)
    , mIsStarted(false)
    , mIsJoined(false)
    , mThreadHandle()
    , mThreadName(aThreadName)
    {
        
    }
    
void TLooplessThread::MainEntry()
    {
    TPlatformThread::SetName(mThreadName.c_str());
    
    mLock.Acquire();
    mIsStarted = true;
    mConditionVariable.NotifyOne(); //Wait in TLooplessThread::Start()
    mLock.Release();
    
    Run();
    }
    
void TLooplessThread::Start()
    {
    ASSERT(!mIsStarted);
    if( mIsStarted )
        {
        LOG_ERROR << "Start: This thread " << "[" << mThreadName << "]" << " was already started";
        return;
        }
    ASSERT(!mIsJoined);
    if( mIsJoined )
        {
        LOG_ERROR << "Start: This thread " << "[" << mThreadName << "]" << " is in join state so cant call start";
        return;
        }
    
    bool e = TPlatformThread::Create(kStackSize, kJoinable, this, &mThreadHandle, kLooplessThreadDefaultPriority);
    ASSERT(e);
    if(!e)
        {
        LOG_ERROR << "Start: Problem in creating thread ";
        return;
        }
    
    //wait for MainEntry to run
    mLock.Acquire();
    while(false == mIsStarted)
        {
        mConditionVariable.Wait(); //Signal in TLooplessThread::MainEntry()
        }
    mLock.Release();
    }
    
    void TLooplessThread::Join()
        {
        ASSERT(mIsStarted);
        if( !mIsStarted )
            {
            LOG_ERROR << "Start: This thread " << "[" << mThreadName << "]" << " was not started so cant join";
            return;
            }
        ASSERT(mIsJoined == false);
        if( mIsJoined )
            {
            LOG_ERROR << "Start: This thread " << "[" << mThreadName << "]" << " is in join state so cant call join again";
            return;
            }
        TPlatformThread::Join(&mThreadHandle);
        
            //TODO: needs careful testing
        mLock.Acquire();
        mIsJoined = true;
        mLock.Release();
        }
    
    
} //namespace vbase

