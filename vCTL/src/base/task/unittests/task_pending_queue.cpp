//
//  task_pending_queue.cpp
//  vClientTemplateLib
//
//  Created by Virendra Shakya on 5/2/14.
//  Copyright (c) 2014 Virendra Shakya. All rights reserved.
//

#include "base/task/task_lambda.h"
#include "base/thread/thread_loopless.h"
#include "base/task/task_pending_queue.h"
#include "base/task/task_pending_q_listener.h"
#include "base/time/time.h"
#include "base/logging/log.h"
#include "base/runloop/detail/darwin/run_loop_cocoa_DARWIN.h"
#include "base/runloop/run_loop.h"
#include "3p/google/gtest/include/gtest/gtest.h"

namespace vbase
{

class Test_ITaskPendingQueueListener : public ITaskPendingQueueListener
    {
public:
    virtual ~Test_ITaskPendingQueueListener()
        {
            
        }
    Test_ITaskPendingQueueListener() : iVal(0) {}
    int Val() const { return iVal; }
    void SetVal(int aVal) { iVal = aVal; }
    
private:
    virtual void OnTaskAdded(TTask* aTask)
        {
        LOG_INFO << "OnTaskAdded";
        iVal++;
        }
    virtual void OnTaskRemoved(TTask* aTask)
        {
        LOG_INFO << "OnTaskRemoved";
        iVal--;
        }
private:
    int iVal;
    };

TEST(UT_TPendingTasksQ, Trivial)
    {
    Test_ITaskPendingQueueListener listener;
    TPendingTasksQ q(listener);
    EXPECT_EQ(listener.Val(), 0);
    }
    
TEST(UT_TPendingTasksQ, AddLambda)
    {
    Test_ITaskPendingQueueListener listener;
    TPendingTasksQ q(listener);
    EXPECT_EQ(listener.Val(), 0);
    
    TLambda lambda;
    TTimeDelta delta(0);
    q.Add(lambda, delta);
    
    EXPECT_EQ(listener.Val(), 1); //we increment the counter
    }
    
// --- threadsafe tests
class UT_TPendingTasksQ_LooplessThread
    : public TLooplessThread
    , private TNonCopyable<UT_TPendingTasksQ_LooplessThread>
    , public ITaskPendingQueueListener
    {
public:
    explicit UT_TPendingTasksQ_LooplessThread(std::string& aThreadName)
        : TLooplessThread(aThreadName)
        , iDidRun(false)
        , iVal(0)
        , iPendingTasksQ(*this)
        {}
    
    virtual void Run()
        {
        iDidRun = true;
        iRunLoop = detail::CRunLoopCFRunLoop::New();
        PostLambdaFromSameThread();
        iRunLoop->Run(0);
        
        }
    
    void TestEventDispatcher()
        {
        }
    
    void PostLambdaFromSameThread()
        {
        TLambda lambda;
        TTimeDelta delta(0);
        iPendingTasksQ.Add(lambda, delta);
        }
    void PostLambdaFromOtherThread()
        {
        TLambda lambda;
        TTimeDelta delta(0);
        iPendingTasksQ.Add(lambda, delta);
        }
        
    int QueueSize() const
        {
        return iPendingTasksQ.Size();
        }
    
    bool GetDidRunTag() const { return iDidRun; }
    int Val() const { return iVal; }
    void SetVal(int aVal) { iVal = aVal; }
        
private:
    virtual void OnTaskAdded(TTask* aTask)
        {
        LOG_INFO << "OnTaskAdded from thread: " << TPlatformThread::Name();
        iVal++;
        }
    virtual void OnTaskRemoved(TTask* aTask)
        {
        LOG_INFO << "OnTaskRemoved";
        iVal--;
        }
    
private:
    bool iDidRun;
    int iVal;
    TPendingTasksQ iPendingTasksQ;
    IRunLoopBase* iRunLoop;
    };
    
TEST(UT_TPendingTasksQ, MultithreadedAddLambda)
    {
    std::string threadName = "UT_TPendingTasksQ_LooplessThread";
    UT_TPendingTasksQ_LooplessThread* thread = new UT_TPendingTasksQ_LooplessThread(threadName);
    thread->Start();
    sleep(3);
    EXPECT_EQ(thread->QueueSize(), 1);
    
    sleep(1);
    thread->PostLambdaFromOtherThread();
    EXPECT_EQ(thread->QueueSize(), 2);
    }

 

} //namespace vbase
