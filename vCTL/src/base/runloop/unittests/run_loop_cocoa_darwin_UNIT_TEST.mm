//
//  run_loop_cocoa_darwin_UT.mm
//  vClientTemplateLib
//
//  Created by Virendra Shakya on 4/29/14.
//  Copyright (c) 2014 Virendra Shakya. All rights reserved.
//

#include "base/thread/thread_platform.h"
#include "base/runloop/detail/darwin/run_loop_cocoa_DARWIN.h"
#include "base/runloop/run_loop.h"
#include "base/thread/thread_loopless.h"
#include "3p/google/gtest/include/gtest/gtest.h"

namespace vbase
{

/*
CallsPerformWorkCorrectlyOnLooplessThread description:
        Create loopless thread
        In loopless mainentry:
            Create runloop
            Add MyRealDumbWork as work
            Run runloop 
 EXPECT: (1) MyRealDumbWork::PerformWork is not called
         (2) UI is not blocked  (not automated)
            
 
            Signal runloop (ScheduleWOrk)
 EXPECT: (1) MyRealDumbWork::PerformWork is called
         (2) UI is not blocked (not automated)
*/
    
class MyRealDumbWork : public IWorkLoad
    {
public:
    virtual bool PerformWork()
        {
        LOG_INFO << "PerformWork called";
        for(int i = 0; i < 10000; i++)
            {
            //LOG_INFO << "i : " << i;
            }
        return false;
        }
    
    virtual bool PerformIdleWork()
        {
        return false;
        }
};
    
class UT_CRunLoopCFRunLoop_LooplessThread
    : public TLooplessThread
    , private TNonCopyable<UT_CRunLoopCFRunLoop_LooplessThread>
    {
public:
    explicit UT_CRunLoopCFRunLoop_LooplessThread(std::string& aThreadName)
    : TLooplessThread(aThreadName)
    , mDidRun(false)
    {}
    
    virtual void Run()
        {
        mDidRun = true;
        
        RunTheLoop();
        }
    
    void RunTheLoop()
        {
        MyRealDumbWork* work = new MyRealDumbWork();
        iRunLoop = detail::CRunLoopCFRunLoop::New();
        iRunLoop->Run(work);
        }
    
    void Signal()
        {
        iRunLoop->ScheduleWork();
        }
    
    bool GetDidRunTag() const { return mDidRun; }
private:
    bool mDidRun;
    IRunLoopBase* iRunLoop;
    };
    

TEST(UT_CRunLoopCFRunLoop, DISABLED_CallsPerformWorkCorrectlyOnLooplessThread)
    {
    std::string threadName = "viren-loopless-thread";
    UT_CRunLoopCFRunLoop_LooplessThread* looplessThread = new UT_CRunLoopCFRunLoop_LooplessThread(threadName);
    EXPECT_TRUE(looplessThread->GetDidRunTag() == false);
    looplessThread->Start();
    EXPECT_TRUE(looplessThread->GetDidRunTag() == true);
    
    unsigned int r = sleep(20);
    LOG_INFO << "sleep returned : " << r;
    looplessThread->Signal();
    }
} //namespace vbase

