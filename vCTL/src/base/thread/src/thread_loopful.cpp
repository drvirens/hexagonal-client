//
//  thread_loopful.cpp
//  vClientTemplateLib
//
//  Created by Virendra Shakya on 5/4/14.
//  Copyright (c) 2014 Virendra Shakya. All rights reserved.
//

#include "base/thread/thread_loopful.h"
#include "base/thread_syn_logger/macrologger.h"
#include "build/build_utils.h"
#include "base/eventdispatcher/event_dispatcher.h"
#include "base/lambda/lambda.h"

namespace vbase
{

static const size_t kStackSize = 0;
static const bool kJoinable = true;
static const EThreadPriority kLooplessThreadDefaultPriority = EThreadPriority_Normal;

TThread::TThread(std::string& aThreadName)
    : iLock()
    //, iConditionVariable(&iLock)
    , iIsStarted(false)
    , iIsJoined(false)
    , iThreadHandle()
    , iThreadName(aThreadName)
    , iMEventDispatcher(0)
    , iRunning(false)
    , iStopping(false)
    {
    }
    
TThread::~TThread()
    {
    //Stop();
    }
    
void TThread::MainEntry()
    {
    TPlatformThread::SetName(iThreadName.c_str());
    
    LOG_INFO << "threadName: " << iThreadName.c_str() << "threadId: " << TPlatformThread::CurrentID();
    
    PreNotifyInit();
    
    iRunning = true;
    
//    iLock.Acquire();
    iIsStarted = true;
//    iConditionVariable.NotifyOne(); //Wait in TThread::Start()
//    iLock.Release();
    
    RunEventLoop(); //on iOS, the CFRunLoopRun() call will not return once this function
        // is called untill CFRunLoopStop() is issued. So this Run() must be the
        // last one in the bootstrap sequence here
        
    iRunning = false;
    OnThreadGonnaExit();
    
    delete iMEventDispatcher;
    iMEventDispatcher = 0;
    }
    
void TThread::RunEventLoop()
    {
    iMEventDispatcher = MEventDispatcher::New();
    iMEventDispatcher->Run();
    }
    
void TThread::FireAndForgetLambda(TLambda& aLambda)
    {
    }
    
void TThread::FireLambdaWithCompletion(TLambda& aLambda, TLambda& aCompletion)
    {
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
    
    TThreadHandle threadhandle = TPlatformThread::Create(kStackSize, kJoinable, this, &iThreadHandle, kLooplessThreadDefaultPriority);
    if(iThreadHandle.RawHandle() == 0) //set this in case the thread exit/join comes immediately
        {
        iThreadHandle.SetRawHandle( threadhandle );
        }
        
//    ASSERT(e);
//    if(!e)
//        {
//        LOG_ERROR << "Start: Problem in creating thread ";
//        return false;
//        }
//    
//        //wait for MainEntry to run
//    iLock.Acquire();
//    while(false == iIsStarted)
//        {
//        iConditionVariable.Wait(); //Signal in TThread::MainEntry()
//        }
//    iLock.Release();
//    
    return true;
    }
    
void TThread::Stop()
    {
    if( !iIsStarted )
        {
        return;
        }
    StopSoon();
    
    Join();
    iIsStarted = false;
    iRunning = false;
    }
    
void TThread::StopSoon()
    {
    if(!iStopping || !iMEventDispatcher)
        {
        return;
        }
    iStopping = true;
    }

void TThread::Join()
    {
//    ASSERT(iIsStarted);
//    if( !iIsStarted )
//        {
//        LOG_ERROR << "Start: This thread " << "[" << iThreadName << "]" << " was not started so cant join";
//        return;
//        }
    ASSERT(iIsJoined == false);
    if( iIsJoined )
        {
        LOG_ERROR << "Start: This thread " << "[" << iThreadName << "]" << " is in join state so cant call join again";
        return;
        }
    TPlatformThread::Join(&iThreadHandle);
    
    iLock.Acquire();
    iIsJoined = true;
    iLock.Release();
    }
    
    
} //namespace vbase

