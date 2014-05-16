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
class CLambda;

class TThreadStartupData;

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
    
    void FireAndForgetLambda(CLambda& aLambda);
    //todo: second param should be TLambdaCompletion that should enclose
    //      the thread-details on which the completion should be posted
    void FireLambdaWithCompletion(CLambda& aLambda, CLambda& aCompletion);
    
protected:
    virtual void RunEventLoop();
    virtual void PreNotifyInit() {}
    virtual void OnThreadGonnaExit() {}
    void Join();
    void StopSoon();
    
private:
    virtual void MainEntry(); //from IThreadMainEntryPoint

private:
    bool iIsStarted;
    bool iIsJoined;
    TPlatformThreadHandle iThreadHandle;
    TPlatformThreadID iThreadId;
    std::string iThreadName;
    
    MEventDispatcher* iMEventDispatcher;
    bool iRunning;
    bool iStopping;
    bool iStopScheduled;
    
    TThreadStartupData* iStartupData;
    };

} //namespace vbase

#endif /* defined(__vClientTemplateLib__thread_loopful__) */
