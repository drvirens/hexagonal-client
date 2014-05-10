//
//  thread_loopless.h
//  vClientTemplateLib
//
//  Created by Virendra Shakya on 4/27/14.
//  Copyright (c) 2014 Virendra Shakya. All rights reserved.
//

#ifndef __vClientTemplateLib__thread_loopless__
#define __vClientTemplateLib__thread_loopless__

#include <string>
#include "base/thread/thread_platform.h"
#include "base/synchronize/lock.h"
#include "base/synchronize/condition_variable.h"

namespace vbase
{
class TLooplessThread
    : public IThreadMainEntryPoint
    , private TNonCopyable<TLooplessThread>
//
// this thread does not have any runloop in it
//
    {
public:
    explicit TLooplessThread(std::string& aThreadName);
    virtual ~TLooplessThread() {}
    
    virtual void Run() = 0;
    virtual void MainEntry(); //from IThreadMainEntryPoint
    virtual void Start();
    virtual void Join();
    
private:
    TLock iLock; // to access iIsJoined
//    TConditionVariable iConditionVariable; // to be used by iLock
    bool iIsStarted;
    
    bool iIsJoined;
    TPlatformThreadHandle iThreadHandle;
    std::string iThreadName;
    };
    
} //namespace vbase

#endif /* defined(__vClientTemplateLib__thread_loopless__) */
