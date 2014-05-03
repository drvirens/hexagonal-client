//
//  event_dispatcher_UT.cpp
//  vClientTemplateLib
//
//  Created by Virendra Shakya on 5/1/14.
//  Copyright (c) 2014 Virendra Shakya. All rights reserved.
//

#include "base/eventdispatcher/event_dispatcher.h"
#include "base/task/task_lambda.h"
#include "base/thread/thread_loopless.h"
#include "3p/google/gtest/include/gtest/gtest.h"

namespace vbase
{

class UT_MEventDispatcher_LooplessThread
    : public TLooplessThread
    , private TNonCopyable<UT_MEventDispatcher_LooplessThread>
    {
public:
    explicit UT_MEventDispatcher_LooplessThread(std::string& aThreadName)
    : TLooplessThread(aThreadName)
    , iDidRun(false)
    , iThreadName(aThreadName)
    {}
    
    virtual void Run()
        {
        iDidRun = true;
        
        TestEventDispatcher();
        
        }
    
    void TestEventDispatcher()
        {
        iMEventDispatcher = MEventDispatcher::New();
//        TLambda lambda;
//        iMEventDispatcher->ExecuteAsynch(lambda);

        //PostLambda();
        }
        
    void PostLambda()
        {
        TLambda lambda;
        iMEventDispatcher->ExecuteAsynch(lambda);
        }
    
    void Signal()
        {
        iMEventDispatcher->ScheduleWork();
        }
    
    bool GetDidRunTag() const { return iDidRun; }
private:
    bool iDidRun;
    MEventDispatcher* iMEventDispatcher;
    std::string iThreadName;
    };
    
    
TEST(UT_MEventDispatcher, DISABLED_ExecuteLambda)
    {
    std::string threadName = "viren-loopless-thread";
    UT_MEventDispatcher_LooplessThread* looplessThread = new UT_MEventDispatcher_LooplessThread(threadName);
    EXPECT_TRUE(looplessThread->GetDidRunTag() == false);
    looplessThread->Start();
    EXPECT_TRUE(looplessThread->GetDidRunTag() == true);
    
    unsigned int r = sleep(3);
    LOG_INFO << "sleep returned : " << r;
    //looplessThread->Signal();
    
    looplessThread->PostLambda();
    }
    
    
} //namespace vbase