//
//  thread_loopful.h
//  vClientTemplateLib
//
//  Created by Virendra Shakya on 5/4/14.
//  Copyright (c) 2014 Virendra Shakya. All rights reserved.
//

#ifndef __vClientTemplateLib__thread_loopful__
#define __vClientTemplateLib__thread_loopful__

#include <string>
#include "base/thread/thread_platform.h"
#include "base/synchronize/lock.h"
#include "base/synchronize/condition_variable.h"

namespace vbase
{
class MEventDispatcher;

class TThread
    : public IThreadMainEntryPoint
    , private TNonCopyable<TThread>
    {
public:
    explicit TThread(std::string& aThreadName);
    virtual ~TThread();
    
    bool Start();
    void Stop();
    bool IsRunning() const { return iRunning; }
    
protected:
    virtual void RunEventLoop();
    virtual void PreNotifyInit() {}
    virtual void OnThreadGonnaExit() {}
    void Join();
    
private:
    virtual void MainEntry(); //from IThreadMainEntryPoint

private:
    TLock iLock; // to access iIsStarted
    TConditionVariable iConditionVariable; // to be used by iLock
    bool iIsStarted;
    bool iIsJoined;
    TPlatformThreadHandle iThreadHandle;
    std::string iThreadName;
    
    MEventDispatcher* iMEventDispatcher;
    bool iRunning;
    };

} //namespace vbase

#endif /* defined(__vClientTemplateLib__thread_loopful__) */
