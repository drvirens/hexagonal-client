//
//  run_loop_DARWIN.cpp
//  vClientTemplateLib
//
//  Created by Virendra Shakya on 4/27/14.
//  Copyright (c) 2014 Virendra Shakya. All rights reserved.
//

#include "base/runloop/detail/darwin/run_loop_DARWIN.h"
#include "logging/log_logger.h"

namespace vbase
{
namespace detail
{

CRunLoopCFRunLoopBase::~CRunLoopCFRunLoopBase()
    {
    CFRunLoopRemoveObserver(mRunLoop, mObserverLoopEnterExit, kCFRunLoopCommonModes);
    CFRelease(mObserverLoopEnterExit);
    
    CFRunLoopRemoveObserver(mRunLoop, mObserverPreSource, kCFRunLoopCommonModes);
    CFRelease(mObserverPreSource);
    
    CFRunLoopRemoveObserver(mRunLoop, mObserverPreAndPostWait, kCFRunLoopCommonModes);
    CFRelease(mObserverPreAndPostWait);
    
    CFRunLoopRemoveSource(mRunLoop, mIdleWorkSource, kCFRunLoopCommonModes);
    CFRelease(mIdleWorkSource);
    
    CFRunLoopRemoveSource(mRunLoop, mWorkSource, kCFRunLoopCommonModes);
    CFRelease(mWorkSource);
    
    CFRelease(mRunLoop);
    }

void CRunLoopCFRunLoopBase::SetWorkLoad(IWorkLoad* aWorkLoad)
    {
    mIWorkItem = aWorkLoad;
    if( !mIWorkItem )
        {
        LOG_ERROR << "SetWorkLoad called with NULL pointer";
        return;
        }
    }
    
void CRunLoopCFRunLoopBase::Run(IWorkLoad* aWorkLoad)
    {
    AssertValidThreadCall();
    
    //TODO: We don't support nesting of CFRunLoop at least for phase 1
    IWorkLoad* prevworkitem = mIWorkItem;
    SetWorkLoad(aWorkLoad);
    DoRun(aWorkLoad);
    SetWorkLoad(prevworkitem); //TODO: Not really needed???
    }

void CRunLoopCFRunLoopBase::SetStopWhenIdle()
    {
    mSetStopWhenIdelTag = true;
    }
    
void CRunLoopCFRunLoopBase::Stop()
    {
    AssertValidThreadCall();
    }

void CRunLoopCFRunLoopBase::ScheduleWork()
    {
    CFRunLoopSourceSignal(mWorkSource);
    CFRunLoopWakeUp(mRunLoop);
    }

void CRunLoopCFRunLoopBase::ScheduleDelayedWork(TTimeInterval aTTimeInterval)
    {
    //CFRunLoopTimerSetNextFireDate();
    }

void CRunLoopCFRunLoopBase::DoObservePreAndPostWait(CFRunLoopObserverRef aObserver, CFRunLoopActivity aActivity, void* aInfo)
    {
    LOG_INFO << "----> DoObservePreAndPostWait";
    }

void CRunLoopCFRunLoopBase::DoObservePreSource(CFRunLoopObserverRef aObserver, CFRunLoopActivity aActivity, void* aInfo)
    {
    LOG_INFO << "----> DoObservePreSource";
    }

void CRunLoopCFRunLoopBase::DoObserveLoopEnterExit(CFRunLoopObserverRef aObserver, CFRunLoopActivity aActivity, void* aInfo)
    {
    LOG_INFO << "----> DoObserveLoopEnterExit";
    }

void CRunLoopCFRunLoopBase::DoPerformSourceWork(void* aInfo)
    {
    CRunLoopCFRunLoopBase* thiz = static_cast<CRunLoopCFRunLoopBase*>(aInfo);
    ASSERT( thiz != 0);
    if( !thiz )
        {
        return;
        }
    thiz->DoPerformWork();
    }
    
bool CRunLoopCFRunLoopBase::DoPerformWork()
    {
    bool r = false;
    @autoreleasepool
        {
        r = mIWorkItem->PerformWork();
        if( r )
            {
            CFRunLoopSourceSignal(mWorkSource);
            }
        }
    return r;
    }

void CRunLoopCFRunLoopBase::DoPerformIdleSourceWork(void* aInfo)
    {
    CRunLoopCFRunLoopBase* thiz = static_cast<CRunLoopCFRunLoopBase*>(aInfo);
    ASSERT( thiz != 0);
    if( !thiz )
        {
        return;
        }
    thiz->DoPerformIdleWork();
    }
    
bool CRunLoopCFRunLoopBase::DoPerformIdleWork()
    {
    bool r = false;
    @autoreleasepool
        {
        r = mIWorkItem->PerformIdleWork();
        //if( r )
        if( mSetStopWhenIdelTag )
            {
            CFRunLoopSourceSignal(mIdleWorkSource);
            }
        }
    return r;
    }

void CRunLoopCFRunLoopBase::DoCreateWorkSource()
    {
    CFRunLoopSourceContext ctxt = CFRunLoopSourceContext(); //valid since we are always gonna compile this by c++ compiler
    ctxt.info = this;
    ctxt.perform = DoPerformSourceWork;

    CFIndex order = 1;
    mWorkSource = CFRunLoopSourceCreate(kCFAllocatorDefault, order, &ctxt);

    CFRunLoopAddSource(mRunLoop, mWorkSource, kCFRunLoopCommonModes);
    }

void CRunLoopCFRunLoopBase::DoCreateIdleWorkSource()
    {
    CFRunLoopSourceContext ctxt = CFRunLoopSourceContext();
    ctxt.info = this;
    ctxt.perform = DoPerformIdleSourceWork;

    CFIndex order = 2;
    mIdleWorkSource = CFRunLoopSourceCreate(kCFAllocatorDefault, order, &ctxt);

    //Add it to runloop
    CFRunLoopAddSource(mRunLoop, mIdleWorkSource, kCFRunLoopCommonModes);
    }
    
void CRunLoopCFRunLoopBase::DoCreateObserverPreAndPostWait()
    {
    CFRunLoopObserverContext observer = CFRunLoopObserverContext();
    observer.info = this;
        {
        CFOptionFlags activities = kCFRunLoopBeforeWaiting | kCFRunLoopAfterWaiting;
        Boolean repeats = true;
        CFIndex order = 0;
        CFRunLoopObserverCallBack callout = &CRunLoopCFRunLoopBase::DoObservePreAndPostWait;
        CFRunLoopObserverContext* context = &observer;
        mObserverPreAndPostWait = CFRunLoopObserverCreate(kCFAllocatorDefault, activities, repeats, order, callout, context);
        }
    CFRunLoopAddObserver(mRunLoop, mObserverPreAndPostWait, kCFRunLoopCommonModes);
    }
    
void CRunLoopCFRunLoopBase::DoCreateObserverPreSource()
    {
    CFRunLoopObserverContext observer = CFRunLoopObserverContext();
    observer.info = this;
        {
        CFOptionFlags activities = kCFRunLoopBeforeSources;
        Boolean repeats = true;
        CFIndex order = 0;
        CFRunLoopObserverCallBack callout = &CRunLoopCFRunLoopBase::DoObservePreSource;
        CFRunLoopObserverContext* context = &observer;
        mObserverPreSource = CFRunLoopObserverCreate(kCFAllocatorDefault, activities, repeats, order, callout, context);
        }
    CFRunLoopAddObserver(mRunLoop, mObserverPreSource, kCFRunLoopCommonModes);
    }
    
void CRunLoopCFRunLoopBase::DoCreateObserverLoopEnterExit()
    {
    CFRunLoopObserverContext observer = CFRunLoopObserverContext();
    observer.info = this;
    {
        CFOptionFlags activities = kCFRunLoopEntry | kCFRunLoopExit;
        Boolean repeats = true;
        CFIndex order = 0;
        CFRunLoopObserverCallBack callout = &CRunLoopCFRunLoopBase::DoObserveLoopEnterExit;
        CFRunLoopObserverContext* context = &observer;
        mObserverLoopEnterExit = CFRunLoopObserverCreate(kCFAllocatorDefault, activities, repeats, order, callout, context);
    }
    CFRunLoopAddObserver(mRunLoop, mObserverLoopEnterExit, kCFRunLoopCommonModes);
    }

CRunLoopCFRunLoopBase::CRunLoopCFRunLoopBase()
    : mRunLoop(0)
    , mWorkSource(0)
    , mIdleWorkSource(0)
    , mObserverPreAndPostWait(0)
    , mObserverPreSource(0)
    , mObserverLoopEnterExit(0)
    , mIWorkItem(0)
    , mSetStopWhenIdelTag(false)
{}

void CRunLoopCFRunLoopBase::Construct()
    {
    mRunLoop = CFRunLoopGetCurrent();
    CFRetain(mRunLoop);

    DoCreateWorkSource();
    DoCreateIdleWorkSource();
    
    DoCreateObserverPreAndPostWait();
    DoCreateObserverPreSource();
    DoCreateObserverLoopEnterExit();
    }

} //namespace detail
} //namespace vbase

