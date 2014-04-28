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
  
}

void CRunLoopCFRunLoopBase::Run(IWorkItem* aWorkItem)
{
  
}

void CRunLoopCFRunLoopBase::Stop()
{
  
}

void CRunLoopCFRunLoopBase::ScheduleWork()
{
  
}

void CRunLoopCFRunLoopBase::ScheduleDelayedWork(TTimeInterval aTTimeInterval)
{
  
}

void CRunLoopCFRunLoopBase::DoRun(IWorkItem* aWorkItem)
{
  
}

NSAutoreleasePool* CRunLoopCFRunLoopBase::CreateAutoreleasePool()
{
  return 0;
}

void CRunLoopCFRunLoopBase::PreWaitObserver(CFRunLoopObserverRef aObserver, CFRunLoopActivity aActivity, void* aInfo)
{
  
}

void CRunLoopCFRunLoopBase::PreSourceObserver(CFRunLoopObserverRef aObserver, CFRunLoopActivity aActivity, void* aInfo)
{
  
}

void CRunLoopCFRunLoopBase::EnterExitObserver(CFRunLoopObserverRef aObserver, CFRunLoopActivity aActivity, void* aInfo)
{
  
}

void CRunLoopCFRunLoopBase::DoPerformSourceWork(void* aInfo)
{
  
}
bool CRunLoopCFRunLoopBase::DoPerformWork()
{
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
  CFRunLoopSourceContext sourceContext = CFRunLoopSourceContext(); //valid since we are always gonna compile this by c++ compiler
  sourceContext.info = this;
  sourceContext.perform = DoPerformSourceWork;
  
  CFAllocatorRef allocator = 0;
  CFIndex order = 1;
  mWorkSource = CFRunLoopSourceCreate(allocator, order, &sourceContext);
  
  //Add it to runloop
  CFRunLoopAddSource(mRunLoop, mWorkSource, kCFRunLoopCommonModes);
}

void CRunLoopCFRunLoopBase::DoCreateIdleWorkSource()
{
  CFRunLoopSourceContext sourceContext = CFRunLoopSourceContext();
  sourceContext.info = this;
  sourceContext.perform = DoPerformIdleSourceWork;
  
  CFAllocatorRef allocator = 0;
  CFIndex order = 2;
  mIdleWorkSource = CFRunLoopSourceCreate(allocator, order, &sourceContext);
  
    //Add it to runloop
  CFRunLoopAddSource(mRunLoop, mIdleWorkSource, kCFRunLoopCommonModes);

}

CRunLoopCFRunLoopBase::CRunLoopCFRunLoopBase()
  : mRunLoop(0)
  , mWorkSource(0)
  , mIdleWorkSource(0)
  , mPreWaitObserver(0)
  , mPreSourceObserver(0)
  , mEnterExitObserver(0)
  , mIWorkItem(0)
{
  
}

void CRunLoopCFRunLoopBase::Construct()
{
  mRunLoop = CFRunLoopGetCurrent();
  CFRetain(mRunLoop);
  
  DoCreateWorkSource();
  DoCreateIdleWorkSource();
}









} //namespace detail
} //namespace vbase
