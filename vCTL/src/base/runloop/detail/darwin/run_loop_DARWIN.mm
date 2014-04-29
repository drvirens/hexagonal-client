//
//  run_loop_DARWIN.cpp
//  vClientTemplateLib
//
//  Created by Virendra Shakya on 4/27/14.
//  Copyright (c) 2014 Virendra Shakya. All rights reserved.
//

#include "base/runloop/detail/darwin/run_loop_DARWIN.h"

namespace vbase
    {
namespace detail
    {

    CRunLoopCFRunLoopBase::~CRunLoopCFRunLoopBase()
        {
        //TODO: tear down all CF* objects here.
        CFRelease(mRunLoop);
        }

    void CRunLoopCFRunLoopBase::SetWorkItem(IWorkItem* aWorkItem)
        {
        mIWorkItem = aWorkItem;
        if( !mIWorkItem )
            {
            LOG_ERROR << "SetWorkItem called with NULL pointer";
            return;
            }
        }

    void CRunLoopCFRunLoopBase::Run(IWorkItem* aWorkItem)
        {
        //TODO: We don't support nesting of CFRunLoop at least for phase 1
        IWorkItem* prevworkitem = mIWorkItem;
        SetWorkItem(aWorkItem);

        DoRun(aWorkItem);

        SetWorkItem(prevworkitem); //TODO: Not really needed???
        }

    void CRunLoopCFRunLoopBase::Stop()
        {

        }

    void CRunLoopCFRunLoopBase::ScheduleWork()
        {
        CFRunLoopSourceSignal(mWorkSource);
        CFRunLoopWakeUp(mRunLoop); //must if you want the thread to do the work ASAP
        }

    void CRunLoopCFRunLoopBase::ScheduleDelayedWork(TTimeInterval aTTimeInterval)
        {
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


//    NSAutoreleasePool* CRunLoopCFRunLoopBase::CreateAutoreleasePool()
//        {
//        return [[NSAutoreleasePool alloc] init];
//        }

    void CRunLoopCFRunLoopBase::ObserverPreAndPostWait(CFRunLoopObserverRef aObserver, CFRunLoopActivity aActivity, void* aInfo)
        {

        }

    void CRunLoopCFRunLoopBase::ObserverPreSource(CFRunLoopObserverRef aObserver, CFRunLoopActivity aActivity, void* aInfo)
        {

        }

    void CRunLoopCFRunLoopBase::ObserverLoopEnterExit(CFRunLoopObserverRef aObserver, CFRunLoopActivity aActivity, void* aInfo)
        {

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
            if( r )
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

        CFAllocatorRef allocator = 0;
        CFIndex order = 1;
        mWorkSource = CFRunLoopSourceCreate(allocator, order, &ctxt);

        //Add it to runloop
        CFRunLoopAddSource(mRunLoop, mWorkSource, kCFRunLoopCommonModes);
        }

    void CRunLoopCFRunLoopBase::DoCreateIdleWorkSource()
        {
        CFRunLoopSourceContext ctxt = CFRunLoopSourceContext();
        ctxt.info = this;
        ctxt.perform = DoPerformIdleSourceWork;

        CFAllocatorRef allocator = 0;
        CFIndex order = 2;
        mIdleWorkSource = CFRunLoopSourceCreate(allocator, order, &ctxt);

        //Add it to runloop
        CFRunLoopAddSource(mRunLoop, mIdleWorkSource, kCFRunLoopCommonModes);
        }
        
    void CRunLoopCFRunLoopBase::DoCreateObserverPreAndPostWait()
        {
        CFRunLoopObserverContext observer = CFRunLoopObserverContext();
        observer.info = this;
            {
            CFAllocatorRef allocator = 0;
            CFOptionFlags activities = kCFRunLoopBeforeWaiting | kCFRunLoopAfterWaiting;
            Boolean repeats = true;
            CFIndex order = 0;
            CFRunLoopObserverCallBack callout = ObserverPreAndPostWait;
            CFRunLoopObserverContext* context = &observer;
            mObserverPreAndPostWait = CFRunLoopObserverCreate(allocator, activities, repeats, order, callout, context);
            }
        CFRunLoopAddObserver(mRunLoop, mObserverPreAndPostWait, kCFRunLoopCommonModes);
        }
        
    void CRunLoopCFRunLoopBase::DoCreateObserverPreSource()
        {
        CFRunLoopObserverContext observer = CFRunLoopObserverContext();
        observer.info = this;
            {
            CFAllocatorRef allocator = 0;
            CFOptionFlags activities = kCFRunLoopBeforeSources;
            Boolean repeats = true;
            CFIndex order = 0;
            CFRunLoopObserverCallBack callout = ObserverPreSource;
            CFRunLoopObserverContext* context = &observer;
            mObserverPreSource = CFRunLoopObserverCreate(allocator, activities, repeats, order, callout, context);
            }
        CFRunLoopAddObserver(mRunLoop, mObserverPreSource, kCFRunLoopCommonModes);
        }
        
    void CRunLoopCFRunLoopBase::DoCreateObserverLoopEnterExit()
        {
        CFRunLoopObserverContext observer = CFRunLoopObserverContext();
        observer.info = this;
        {
            CFAllocatorRef allocator = 0;
            CFOptionFlags activities = kCFRunLoopEntry | kCFRunLoopExit;
            Boolean repeats = true;
            CFIndex order = 0;
            CFRunLoopObserverCallBack callout = ObserverLoopEnterExit;
            CFRunLoopObserverContext* context = &observer;
            mObserverLoopEnterExit = CFRunLoopObserverCreate(allocator, activities, repeats, order, callout, context);
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

