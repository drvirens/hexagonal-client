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
    : iIsStarted(false)
    , iIsJoined(false)
    , iThreadHandle()
    , iThreadName(aThreadName)
    {}
    
void TLooplessThread::MainEntry()
    {
    TPlatformThread::SetName(iThreadName.c_str());
    
    KERNEL_LOG_INFO ("threadName: %s, threadId: %d", iThreadName.c_str(), TPlatformThread::CurrentID());
    
    iIsStarted = true;
   
    iRendezvous.Rendezvous(TRendezvous::ECheckpoint_Second_Arrived);
    
    Run();
    }

void TLooplessThread::Start()
    {
    ASSERT(!iIsStarted);
    if( iIsStarted )
        {
        KERNEL_LOG_ERROR ( "Start: This thread [ %s ] was already started", iThreadName.c_str() );
        return;
        }
    ASSERT(!iIsJoined);
    if( iIsJoined )
        {
        KERNEL_LOG_ERROR ("Start: This thread  [ %s ] is in join state so cant call start", iThreadName.c_str() );
        return;
        }
    
    TThreadHandle threadhandle = TPlatformThread::Create(kStackSize, kJoinable, this, &iThreadHandle, kLooplessThreadDefaultPriority);
    
    if(iThreadHandle.RawHandle() == 0) //set this in case the thread deletion comes immediately
        {
        //use threadhandle
        iThreadHandle.SetRawHandle( threadhandle );
        }

    iRendezvous.Rendezvous(TRendezvous::ECheckpoint_First_Arrived);
    }

void TLooplessThread::Join()
    {
    ASSERT(iIsStarted);
    if( !iIsStarted )
        {
        KERNEL_LOG_ERROR ( "Start: This thread  [ %s ] was not started so cant join" , iThreadName.c_str() );
        return;
        }
    ASSERT(iIsJoined == false);
    if( iIsJoined )
        {
        KERNEL_LOG_ERROR ( "Start: This thread  [ %s ] is in join state so cant call join again", iThreadName.c_str() );
        return;
        }
    TPlatformThread::Join(&iThreadHandle);
    
//    iLock.Acquire();
    iIsJoined = true;
//    iLock.Release();
    }
    
    
} //namespace vbase

