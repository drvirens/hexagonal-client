//
//  thread_loopless.cpp
//  vClientTemplateLib
//
//  Created by Virendra Shakya on 4/27/14.
//  Copyright (c) 2014 Virendra Shakya. All rights reserved.
//

#include "base/thread/thread_loopless.h"
#include "base/thread_syn_logger/macrologger.h"
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
    
    //LOG_INFO << "threadName: " << iThreadName.c_str() << "threadId: " << TPlatformThread::CurrentID();
    LOG_INFO ("threadName: %s, threadId: %d", iThreadName.c_str(), TPlatformThread::CurrentID());
    
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
        LOG_ERROR ( "Start: This thread [ %s ] was already started", iThreadName.c_str() );
        return;
        }
    ASSERT(!iIsJoined);
    if( iIsJoined )
        {
        LOG_ERROR ("Start: This thread  [ %s ] is in join state so cant call start", iThreadName.c_str() );
        return;
        }
    
    bool e = TPlatformThread::Create(kStackSize, kJoinable, this, &iThreadHandle, kLooplessThreadDefaultPriority);
    ASSERT(e);
    if(!e)
        {
        LOG_ERROR ( "Start: Problem in creating thread " );
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
        LOG_ERROR ( "Start: This thread  [ %s ] was not started so cant join" , iThreadName.c_str() );
        return;
        }
    ASSERT(iIsJoined == false);
    if( iIsJoined )
        {
        LOG_ERROR ( "Start: This thread  [ %s ] is in join state so cant call join again", iThreadName.c_str() );
        return;
        }
    TPlatformThread::Join(&iThreadHandle);
    
        //TODO: needs careful testing
    iLock.Acquire();
    iIsJoined = true;
    iLock.Release();
    }
    
    
} //namespace vbase

