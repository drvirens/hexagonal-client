//
//  run_loop_DARWIN.h
//  vClientTemplateLib
//
//  Created by Virendra Shakya on 4/27/14.
//  Copyright (c) 2014 Virendra Shakya. All rights reserved.
//

#ifndef __vClientTemplateLib__run_loop_DARWIN__
#define __vClientTemplateLib__run_loop_DARWIN__

#include "build/build_config.h"

#if defined(V_PLATFORM_DARWIN)
#import <CoreFoundation/CoreFoundation.h>
//#elif defined(V_PLATFORM_IOS)
//#import <CoreFoundation/CoreFoundation.h>
#endif

#include "base/runloop/run_loop.h"
#include "base/non_copyable.h"

namespace vbase
{
namespace detail
{

class CRunLoopCFRunLoopBase : public IRunLoopBase, TNonCopyable<CRunLoopCFRunLoopBase>
    {
typedef long long TTimeInterval; //TODO: Use better abstraction on top of long here
protected:
    virtual ~CRunLoopCFRunLoopBase();
    virtual void DoRun(IWorkLoad* aWorkLoad) = 0;
    virtual void Stop() = 0; //can only be called from thread that called Run()
    virtual void SetStopWhenIdle();
    virtual void Run(IWorkLoad* aWorkLoad); //from IRunLoopBase
    
    virtual void ScheduleWork();
    virtual void ScheduleDelayedWork(TTimeInterval aTTimeInterval); //more like Symbians' DFC

protected:
    CRunLoopCFRunLoopBase();
    void Construct();
    void SetWorkLoad(IWorkLoad* aWorkLoad);
    CFRunLoopRef NativeRunLoop() const { return mRunLoop; }
    
private:
    static void DoObservePreAndPostWait(CFRunLoopObserverRef aObserver, CFRunLoopActivity aActivity, void* aInfo);
    static void DoObservePreSource(CFRunLoopObserverRef aObserver, CFRunLoopActivity aActivity, void* aInfo);
    static void DoObserveLoopEnterExit(CFRunLoopObserverRef aObserver, CFRunLoopActivity aActivity, void* aInfo);

    static void DoPerformSourceWork(void* aInfo); // CFRunLoopSourceContext->perform
    bool DoPerformWork();
    static void DoPerformIdleSourceWork(void* aInfo);
    bool DoPerformIdleWork();
    
    void DoCreateWorkSource();
    void DoCreateIdleWorkSource();
    void DoCreateObserverPreAndPostWait();
    void DoCreateObserverPreSource();
    void DoCreateObserverLoopEnterExit();

private:
    CFRunLoopRef mRunLoop;
    CFRunLoopSourceRef mWorkSource;
    CFRunLoopSourceRef mIdleWorkSource;
    CFRunLoopObserverRef mObserverPreAndPostWait;    // cb : DoObservePreAndPostWait()
    CFRunLoopObserverRef mObserverPreSource;  // cb : DoObservePreSource
    CFRunLoopObserverRef mObserverLoopEnterExit;  // cb : DoObserveLoopEnterExit
    IWorkLoad* mIWorkItem; //not owned so dont delete
    bool mSetStopWhenIdelTag;
    };

} //namespace detail
} //namespace vbase


#endif /* defined(__vClientTemplateLib__run_loop_DARWIN__) */
