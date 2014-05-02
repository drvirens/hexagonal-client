//
//  run_loop_DARWIN.cpp
//  vClientTemplateLib
//
//  Created by Virendra Shakya on 4/27/14.
//  Copyright (c) 2014 Virendra Shakya. All rights reserved.
//

#include "base/runloop/detail/darwin/run_loop_DARWIN.h"
#include "base/logging/log.h"

namespace vbase
{
namespace detail
{

CRunLoopCFRunLoopBase::~CRunLoopCFRunLoopBase()
    {
    //TODO: tear down all CF* objects here.
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
    
    
//    static void emptyPerform(void*)
//    {
//    LOG_INFO << "emptyPerform";
//    }

void CRunLoopCFRunLoopBase::Run(IWorkLoad* aWorkLoad)
    {
    AssertValidThreadCall();
    
    //TODO: We don't support nesting of CFRunLoop at least for phase 1
    IWorkLoad* prevworkitem = mIWorkItem;
    SetWorkLoad(aWorkLoad);
    
            // Must add a source to the run loop to prevent CFRunLoopRun() from exiting.
//        CFRunLoopSourceContext ctxt = {0, (void*)1 /*must be non-NULL*/, 0, 0, 0, 0, 0, 0, 0, emptyPerform};
//        CFRunLoopSourceRef bogusSource = CFRunLoopSourceCreate(0, 0, &ctxt);
//        CFRunLoopAddSource(mRunLoop, bogusSource, kCFRunLoopDefaultMode);

    DoRun(aWorkLoad);

    SetWorkLoad(prevworkitem); //TODO: Not really needed???
    }

void CRunLoopCFRunLoopBase::Stop()
    {
    AssertValidThreadCall();
    }

void CRunLoopCFRunLoopBase::ScheduleWork()
    {
    //AssertValidThreadCall();
    
    CFRunLoopSourceSignal(mWorkSource);
    CFRunLoopWakeUp(mRunLoop); //must if you want the thread to do the work ASAP
    }

void CRunLoopCFRunLoopBase::ScheduleDelayedWork(TTimeInterval aTTimeInterval)
    {
    //AssertValidThreadCall();
    
    //CFRunLoopTimerSetNextFireDate();
    }

    /*
    For details, see: http://www.opensource.apple.com/source/CF/CF-476.15/CFRunLoop.c
    void CFRunLoopRun(void) {	//DOES CALLOUT
    int32_t result;
    do {
    result = CFRunLoopRunSpecific(CFRunLoopGetCurrent(), kCFRunLoopDefaultMode, 1.0e10, false);
    CHECK_FOR_FORK();
    } while (kCFRunLoopRunStopped != result && kCFRunLoopRunFinished != result);
    }
    */

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
        //drain the Autoreleasepool per run of the CFRunLoop to release all shit created by higher-level classes, if any
        
        //Arguably, @autoreleasepool is much faster than using NSAutoreleasePool manually:
        //      1) http://stackoverflow.com/questions/21421715/why-autoreleasepool-is-6-times-faster-than-nsautoreleasepool
        //      Comment by Greg parker: NSAutoreleasePool allocates an NSAutoreleasePool object (or fetches an existing one from a cache); @autoreleasepool does not. NSAutoreleasePool sends several Objective-C messages; @autoreleasepool does not. –
        //      2) More info: https://developer.apple.com/library/ios/releasenotes/ObjectiveC/RN-TransitioningToARC/Introduction/Introduction.html
        
    @autoreleasepool
        {
        bool r = mIWorkItem->PerformWork();
        if( r ) //more work to do
            {
            CFRunLoopSourceSignal(mWorkSource);
            }
            return r;
        }
    return false;
    }

void CRunLoopCFRunLoopBase::DoPerformIdleSourceWork(void* aInfo)
    {

    }
bool CRunLoopCFRunLoopBase::DoPerformIdleWork()
    {
    return false;
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

