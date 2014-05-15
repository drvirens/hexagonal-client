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
#include "base/synchronize/rendezvous_simple.h"

namespace vbase
{

static const size_t kStackSize = 0;
static const bool kJoinable = true;
static const EThreadPriority kLooplessThreadDefaultPriority = EThreadPriority_Normal;

class TThreadStartupData
    {
public:
    TThreadStartupData() {}
public:
    TRendezvous iRendezvous;
    };


TThread::TThread(std::string& aThreadName)
    : iIsStarted(false)
    , iIsJoined(false)
    , iThreadHandle()
    , iThreadName(aThreadName)
    , iMEventDispatcher(0)
    , iRunning(false)
    , iStopping(false)
    {}
    
TThread::~TThread()
    {
    Stop();
    }
    
void TThread::MainEntry()
    {
    TPlatformThread::SetName(iThreadName.c_str());
    iThreadId = TPlatformThread::CurrentID();
    LOG_INFO << "threadName: " << iThreadName.c_str() << "threadId: " << TPlatformThread::CurrentID();
    
    PreNotifyInit();
    
    iRunning = true;
    iStartupData->iRendezvous.Rendezvous(TRendezvous::ECheckpoint_Second_Arrived);
    
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
    
void TThread::FireAndForgetLambda(CLambda& aLambda)
    {
    }
    
void TThread::FireLambdaWithCompletion(CLambda& aLambda, CLambda& aCompletion)
    {
    }

bool TThread::Start()
    {
    ASSERT( iMEventDispatcher == 0 ); //dont re-create the fucking runloops
    if( iMEventDispatcher ) //thread was laready started
        {
        return false;
        }
        
    TThreadStartupData startupdata;
    iStartupData = &startupdata;
    
    /* TThreadHandle threadhandle = */
    TPlatformThread::Create(kStackSize, kJoinable, this, &iThreadHandle, kLooplessThreadDefaultPriority);
        
    //wait until main entry is run
    startupdata.iRendezvous.Rendezvous(TRendezvous::ECheckpoint_First_Arrived);
    iStartupData = 0;
    iIsStarted = true;
    
    //ASSERT( iMEventDispatcher != 0 );
        
    return true;
    }
    
void TThread::Stop()
    {
    if( !iIsStarted )
        {
        return;
        }
    StopSoon();
    
    TPlatformThread::Join(&iThreadHandle);
    
    iIsStarted = false;
    iRunning = false;
    }
    
void TThread::StopSoon()
    {
    if(!iStopping || !iMEventDispatcher)
        {
        return;
        }
    //TODO: Post lambda in the work queue
    iStopping = true;
    }
    
} //namespace vbase

