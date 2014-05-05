//
//  thread_loopless.cpp
//  vClientTemplateLib
//
//  Created by Virendra Shakya on 4/27/14.
//  Copyright (c) 2014 Virendra Shakya. All rights reserved.
//

#include "base/thread/thread_loopless.h"
#include "logging/log_logger.h"
#include "build/build_utils.h"

namespace vbase
{

static const size_t kStackSize = 0;
static const bool kJoinable = true;
static const EThreadPriority kLooplessThreadDefaultPriority = EThreadPriority_Normal;

TLooplessThread::TLooplessThread(std::string& aThreadName)
    :  iLock()
    , iConditionVariable(&iLock)
    , iIsStarted(false)
    , iIsJoined(false)
    , iThreadHandle()
    , iThreadName(aThreadName)
    {
        
    }
    
void TLooplessThread::MainEntry()
    {
    TPlatformThread::SetName(iThreadName.c_str());
    
    LOG_INFO << "threadName: " << iThreadName.c_str() << "threadId: " << TPlatformThread::CurrentID();
    
    iLock.Acquire();
    iIsStarted = true;
    iConditionVariable.NotifyOne(); //Wait in TLooplessThread::Start()
    iLock.Release();
    
    Run();
    }

void TLooplessThread::Start()
    {
    ASSERT(!iIsStarted);
    if( iIsStarted )
        {
        LOG_ERROR << "Start: This thread " << "[" << iThreadName << "]" << " was already started";
        return;
        }
    ASSERT(!iIsJoined);
    if( iIsJoined )
        {
        LOG_ERROR << "Start: This thread " << "[" << iThreadName << "]" << " is in join state so cant call start";
        return;
        }
    
    bool e = TPlatformThread::Create(kStackSize, kJoinable, this, &iThreadHandle, kLooplessThreadDefaultPriority);
    ASSERT(e);
    if(!e)
        {
        LOG_ERROR << "Start: Problem in creating thread ";
        return;
        }
    
        //wait for MainEntry to run
    iLock.Acquire();
    while(false == iIsStarted)
        {
        iConditionVariable.Wait(); //Signal in TLooplessThread::MainEntry()
        }
    iLock.Release();
    }

void TLooplessThread::Join()
    {
    ASSERT(iIsStarted);
    if( !iIsStarted )
        {
        LOG_ERROR << "Start: This thread " << "[" << iThreadName << "]" << " was not started so cant join";
        return;
        }
    ASSERT(iIsJoined == false);
    if( iIsJoined )
        {
        LOG_ERROR << "Start: This thread " << "[" << iThreadName << "]" << " is in join state so cant call join again";
        return;
        }
    TPlatformThread::Join(&iThreadHandle);
    
        //TODO: needs careful testing
    iLock.Acquire();
    iIsJoined = true;
    iLock.Release();
    }
    
    
} //namespace vbase

