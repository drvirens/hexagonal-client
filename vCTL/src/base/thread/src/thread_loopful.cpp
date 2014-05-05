//
//  thread_loopful.cpp
//  vClientTemplateLib
//
//  Created by Virendra Shakya on 5/4/14.
//  Copyright (c) 2014 Virendra Shakya. All rights reserved.
//

#include "base/thread/thread_loopful.h"
#include "logging/log_logger.h"
#include "build/build_utils.h"

namespace vbase
{

static const size_t kStackSize = 0;
static const bool kJoinable = true;
static const EThreadPriority kLooplessThreadDefaultPriority = EThreadPriority_Normal;

TThread::TThread(std::string& aThreadName)
    :  iLock()
    , iConditionVariable(&iLock)
    , iIsStarted(false)
    , iIsJoined(false)
    , iThreadHandle()
    , iThreadName(aThreadName)
    {
        
    }
    
TThread::~TThread()
    {
    }
    
void TThread::MainEntry()
    {
    TPlatformThread::SetName(iThreadName.c_str());
    
    LOG_INFO << "threadName: " << iThreadName.c_str() << "threadId: " << TPlatformThread::CurrentID();
    
    iLock.Acquire();
    iIsStarted = true;
    iConditionVariable.NotifyOne(); //Wait in TThread::Start()
    iLock.Release();
    
    Run();
    }

bool TThread::Start()
    {
    ASSERT(!iIsStarted);
    if( iIsStarted )
        {
        LOG_ERROR << "Start: This thread " << "[" << iThreadName << "]" << " was already started";
        return false;
        }
    ASSERT(!iIsJoined);
    if( iIsJoined )
        {
        LOG_ERROR << "Start: This thread " << "[" << iThreadName << "]" << " is in join state so cant call start";
        return false;
        }
    
    bool e = TPlatformThread::Create(kStackSize, kJoinable, this, &iThreadHandle, kLooplessThreadDefaultPriority);
    ASSERT(e);
    if(!e)
        {
        LOG_ERROR << "Start: Problem in creating thread ";
        return false;
        }
    
        //wait for MainEntry to run
    iLock.Acquire();
    while(false == iIsStarted)
        {
        iConditionVariable.Wait(); //Signal in TThread::MainEntry()
        }
    iLock.Release();
    
    return true;
    }

void TThread::Join()
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

