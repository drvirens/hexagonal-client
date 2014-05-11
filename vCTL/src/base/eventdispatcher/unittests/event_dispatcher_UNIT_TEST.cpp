//
//  event_dispatcher_UT.cpp
//  vClientTemplateLib
//
//  Created by Virendra Shakya on 5/1/14.
//  Copyright (c) 2014 Virendra Shakya. All rights reserved.
//

#include "base/eventdispatcher/event_dispatcher.h"
#include "base/lambda/lambda.h"
#include "base/thread/thread_loopless.h"
#include "3p/google/gtest/include/gtest/gtest.h"

namespace vbase
{

class MyWorkToDo : public TLambda
    {
public:
    MyWorkToDo() : iInt(69) {}
    virtual void Run()
        {
        }
    virtual TLambda* CreateCopy()
        {
        MyWorkToDo* me = new MyWorkToDo(*this);
        return me;
        }
private:
    int iInt;
    };
    
class UT_MEventDispatcher_LooplessThread
    : public TLooplessThread
    , private TNonCopyable<UT_MEventDispatcher_LooplessThread>
    {
public:
    explicit UT_MEventDispatcher_LooplessThread(std::string& aThreadName)
    : TLooplessThread(aThreadName)
    , iDidRun(false)
    , iThreadName(aThreadName)
    , iMEventDispatcher(0)
    {}
    
    virtual void Run()
        {
        iDidRun = true;
        iMEventDispatcher = MEventDispatcher::New();
        iMEventDispatcher->Run();
        }
    
    void PostLambda(TLambda& lambda)
        {
        iMEventDispatcher->ExecuteAsynch(lambda);
        }
    
    bool GetDidRunTag() const { return iDidRun; }
private:
    bool iDidRun;
    MEventDispatcher* iMEventDispatcher;
    std::string iThreadName;
};

    
TEST(UT_MEventDispatcher, DISABLED_Trivial)
    {
    std::string threadName = "UT_MEventDispatcher_LooplessThread";
    UT_MEventDispatcher_LooplessThread* looplessThread = new UT_MEventDispatcher_LooplessThread(threadName);
    EXPECT_TRUE(looplessThread->GetDidRunTag() == false);
    looplessThread->Start();
    //EXPECT_TRUE(looplessThread->GetDidRunTag() == true);
    
    sleep(3);
    //TLambda lambda;
    MyWorkToDo* lambda = new MyWorkToDo();
    looplessThread->PostLambda(*lambda);
    
    EXPECT_TRUE(looplessThread->GetDidRunTag() == true);
    }
    
    
} //namespace vbase