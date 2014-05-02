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

#include "base/runloop/unittests/run_loop_cocoa_darwin_UT.h"

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
         (2) UI is not blocked
            
            Now add another work
            Signal runloop (ScheduleWOrk)
 EXPECT: (1) MyRealDumbWork::PerformWork is called
         (2) UI is not blocked
 
*/
    
    class MyRealDumbWork : public IWorkLoad
        {
    public:
        virtual bool PerformWork()
            {
            LOG_INFO << "PerformWork called";
            for(int i = 0; i < 10000; i++)
                {
                LOG_INFO << "i : " << i;
                }
            return false;
            }
        
        virtual bool PerformIdleWork()
            {
            return false;
            }
    };
    
//    TEST(UT_CRunLoopCFRunLoop, DISABLED_Simple)
//        {
//        IRunLoopBase* iRunLoop;
//        MyRealDumbWork* work = new MyRealDumbWork();
//        
//        iRunLoop = detail::CRunLoopCFRunLoop::New();
//        iRunLoop->Run(work);
//        iRunLoop->ScheduleWork(); //hmm this wont work. signalling should happen from outside thread
//        }
//    
    
        // -----------
    
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
            iRunLoop->ScheduleWork(); //hmm this wont work since no underlying cfrunloop* shit is guaranteed to be ready.
            }
        
        bool GetDidRunTag() const { return mDidRun; }
    private:
        bool mDidRun;
        IRunLoopBase* iRunLoop;
        };
    
    TEST(UT_CRunLoopCFRunLoop, CallsPerformWorkCorrectlyOnLooplessThread)
        {
        std::string threadName = "viren-loopless-thread";
        UT_CRunLoopCFRunLoop_LooplessThread* looplessThread = new UT_CRunLoopCFRunLoop_LooplessThread(threadName);
        EXPECT_TRUE(looplessThread->GetDidRunTag() == false);
        looplessThread->Start();
            //looplessThread.Join();
        EXPECT_TRUE(looplessThread->GetDidRunTag() == true);
        
        unsigned int r = sleep(20);
        LOG_INFO << "sleep returned : " << r;
        looplessThread->Signal();
        }
    
    
    
        //
    
    
    
    class MMyRunLoopThreadMainEntry
    : public IThreadMainEntryPoint
    , private TNonCopyable<MMyRunLoopThreadMainEntry>
    {
    public:
        MMyRunLoopThreadMainEntry()
        : mTagDidRun(false)
        , iCallRun(false)
        {}
        
        virtual void MainEntry()
        {
            mTagDidRun = true;
            TPlatformThread::SetName("viren-thread");
            const char* name = TPlatformThread::Name();
            int ret = strcmp(name, "viren-thread");
            EXPECT_EQ(0, ret);
            
            MyRealDumbWork* work = new MyRealDumbWork();
            iRunLoop = detail::CRunLoopCFRunLoop::New();
                //iRunLoop = detail::CRunLoopNSRunLoop::New();
            
            if(iCallRun)
            {
                iRunLoop->Run(work);
                iRunLoop->ScheduleWork(); //hmm this wont work since no underlying cfrunloop* shit is guaranteed to be ready.
            }
                //call run-loop shit here for testing
            
            return;
        }
        
        void ScheduleWOrk()
        {
                //iRunLoop->ScheduleWork();
        }
        
        bool TagDidRun() const { return mTagDidRun; }
        void SetSleepTag(bool aSleep) { iCallRun = aSleep; }
        
        TPlatformThreadID GetThreadId() { return TPlatformThread::CurrentID(); }
        
    private:
        bool mTagDidRun;
        bool iCallRun;
        IRunLoopBase* iRunLoop;
    };
    
    
    static const size_t kStackSize = 0;
    static const bool kJoinable = true;
        // ------------------------------------------------------------ Trivial
    TEST(UT_CRunLoopCFRunLoop, DISABLED_Trivial)
    {
        MMyRunLoopThreadMainEntry threadEntry;
        TPlatformThreadHandle h;
        threadEntry.SetSleepTag(false);
        ASSERT_FALSE( threadEntry.TagDidRun() );
        
        EThreadPriority aPriority = EThreadPriority_Normal;
        ASSERT_TRUE( TPlatformThread::Create(kStackSize, kJoinable, &threadEntry, &h, aPriority) );
        
        TPlatformThread::Join(&h);
        ASSERT_TRUE( threadEntry.TagDidRun() );
    }
    
    
        // ------------------------------------------------------------ CallRun
    MMyRunLoopThreadMainEntry* threadEntry;
    TEST(UT_CRunLoopCFRunLoop, DISABLED_CallRun)
    {
        threadEntry = new MMyRunLoopThreadMainEntry();
        TPlatformThreadHandle h;
        threadEntry->SetSleepTag(true);
        ASSERT_FALSE( threadEntry->TagDidRun() );
        
        EThreadPriority aPriority = EThreadPriority_Normal;
        ASSERT_TRUE( TPlatformThread::Create(kStackSize, kJoinable, threadEntry, &h, aPriority) );
        
            //TPlatformThread::Sleep(10);
            //threadEntry->ScheduleWOrk();
        
            //TPlatformThread::Join(&h);
        ASSERT_TRUE( threadEntry->TagDidRun() );
    }
    
    void UT_CRunLoopCFRunLoop_ScheduleWOrk()
    {
        ASSERT(threadEntry != 0);
        threadEntry->ScheduleWOrk();
    }
    
} //namespace vbase

