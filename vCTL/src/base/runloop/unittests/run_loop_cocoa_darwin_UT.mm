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
#include "3p/google/gtest/include/gtest/gtest.h"

#include "base/runloop/unittests/run_loop_cocoa_darwin_UT.h"

namespace vbase
{
    
    class MyRealDumbWork : public IWorkLoad
    {
    public:
        virtual bool PerformWork()
        {
            LOG_INFO << "PerformWork called";
            for(int i = 0; i < 10000; i++)
            {
                    //TPlatformThread::Sleep(5);
                    //LOG_INFO << "i : " << i;
            }
            return false;
        }
        
        virtual bool PerformIdleWork()
        {
            return false;
        }
    };
    
    
    
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
    TEST(UT_CRunLoopCFRunLoop, Trivial)
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
    TEST(UT_CRunLoopCFRunLoop, CallRun)
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

