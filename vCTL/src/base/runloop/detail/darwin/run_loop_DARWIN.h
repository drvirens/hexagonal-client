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

#if defined(V_PLATFORM_IOS)
#import <Foundation/Foundation.h>
#endif

#include "base/runloop/run_loop.h"
#include "base/non_copyable.h"

namespace vbase
{
namespace detail
{
  class CRunLoopCFRunLoopBase
    : public IRunLoopBase
    , TNonCopyable<CRunLoopCFRunLoopBase>
  {
  public:
    virtual ~CRunLoopCFRunLoopBase();
    
    //from IRunLoopBase
    virtual void Run(IWorkItem* aWorkItem);
    virtual void Stop(); //can only be called from thread that called Run()
    virtual void ScheduleWork();
    //TODO: Use better abstraction on top of long here
    typedef long long TTimeInterval;
    virtual void ScheduleDelayedWork(TTimeInterval aTTimeInterval); //more like Symbians' DFC
    
    virtual void DoRun(IWorkItem* aWorkItem) = 0;
  
  protected:
    CRunLoopCFRunLoopBase();
    void Construct();
    virtual NSAutoreleasePool* CreateAutoreleasePool();
    CFRunLoopRef NativeRunLoop() const { return mRunLoop; }
    
    //Callbacks for CFRunLoopObserverRef observers: must match signature below:
    // typedef void (*CFRunLoopObserverCallBack)(CFRunLoopObserverRef observer, CFRunLoopActivity activity, void *info);
    // Refer to CFRunLoop.h/.c for more info
    static void PreWaitObserver(CFRunLoopObserverRef aObserver, CFRunLoopActivity aActivity, void* aInfo);
    static void PreSourceObserver(CFRunLoopObserverRef aObserver, CFRunLoopActivity aActivity, void* aInfo);
    static void EnterExitObserver(CFRunLoopObserverRef aObserver, CFRunLoopActivity aActivity, void* aInfo);
    
  private:
  /*
         typedef struct {
           CFIndex	version;
           void *	info;
           const void *(*retain)(const void *info);
           void	(*release)(const void *info);
           CFStringRef	(*copyDescription)(const void *info);
           Boolean	(*equal)(const void *info1, const void *info2);
           CFHashCode	(*hash)(const void *info);
           void	(*schedule)(void *info, CFRunLoopRef rl, CFStringRef mode);
           void	(*cancel)(void *info, CFRunLoopRef rl, CFStringRef mode);
           void	(*perform)(void *info);
         } CFRunLoopSourceContext;
  */
    //
    // Function that will be passed to CFRunLoopSourceContext->perform
    //
    static void DoPerformSourceWork(void* aInfo);
    bool DoPerformWork();
    
    static void DoPerformIdleSourceWork(void* aInfo);
    bool DoPerformIdleWork();
    
    void DoCreateWorkSource();
    void DoCreateIdleWorkSource();
    
  private:
    CFRunLoopRef mRunLoop;
    
    CFRunLoopSourceRef mWorkSource;
    CFRunLoopSourceRef mIdleWorkSource;
  
    CFRunLoopObserverRef mPreWaitObserver;    // PreWaitObserver
    CFRunLoopObserverRef mPreSourceObserver;  // PreSourceObserver
    CFRunLoopObserverRef mEnterExitObserver;  // EnterExitObserver
    
    IWorkItem* mIWorkItem;
  };
  
} //namespace detail
} //namespace vbase


#endif /* defined(__vClientTemplateLib__run_loop_DARWIN__) */
