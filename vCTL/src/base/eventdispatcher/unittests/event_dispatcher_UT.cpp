    //
    //  event_dispatcher_UT.cpp
    //  vClientTemplateLib
    //
    //  Created by Virendra Shakya on 5/1/14.
    //  Copyright (c) 2014 Virendra Shakya. All rights reserved.
    //

#include "base/eventdispatcher/event_dispatcher.h"
#include "base/task/task_lambda.h"
#include "3p/google/gtest/include/gtest/gtest.h"

namespace vbase
{
    
    class MMyEventDispatcherThreadMainEntry
    : public IThreadMainEntryPoint
    , private TNonCopyable<MMyEventDispatcherThreadMainEntry>
    {
    public:
        MMyEventDispatcherThreadMainEntry()
        : mTagDidRun(false)
        , iCallRun(false)
        {
            iMEventDispatcher = MEventDispatcher::New(); //ctor for MEventDispatcher run on whoever called this MMyEventDispatcherThreadMainEntry ctor's thread
        }
        
        virtual void MainEntry()
        {
            mTagDidRun = true;
            TPlatformThread::SetName("viren-thread");
            const char* name = TPlatformThread::Name();
            int ret = strcmp(name, "viren-thread");
            EXPECT_EQ(0, ret);
            
            TLambda lambda;
            iMEventDispatcher->ExecuteAsynch(lambda);
            
            return;
        }
        
        
        bool TagDidRun() const { return mTagDidRun; }
        void SetSleepTag(bool aSleep) { iCallRun = aSleep; }
        
        void ScheduleWork()
        {
            iMEventDispatcher->ScheduleWork(); // should abort. see comments in ctor
        }
        
        TPlatformThreadID GetThreadId() { return TPlatformThread::CurrentID(); }
        
    private:
        bool mTagDidRun;
        bool iCallRun;
        MEventDispatcher* iMEventDispatcher;
    };
    
    
    static const size_t kStackSize = 0;
    static const bool kJoinable = true;
    
        // ------------------------------------------------------------ thread unsafe
    
    
    void EventDispatcherThreadUnSafeTest()
    {
        MMyEventDispatcherThreadMainEntry* eventDispatcherThreadEntryObject = new MMyEventDispatcherThreadMainEntry();
        TPlatformThreadHandle h;
        eventDispatcherThreadEntryObject->SetSleepTag(true);
        ASSERT_FALSE( eventDispatcherThreadEntryObject->TagDidRun() );
        
        EThreadPriority aPriority = EThreadPriority_Normal;
        ASSERT_TRUE( TPlatformThread::Create(kStackSize, kJoinable, eventDispatcherThreadEntryObject, &h, aPriority) );
        
            //TPlatformThread::Sleep(10);
        eventDispatcherThreadEntryObject->ScheduleWork();
        
            //TPlatformThread::Join(&h);
        ASSERT_TRUE( eventDispatcherThreadEntryObject->TagDidRun() );
    }
    
#if !defined(NDEBUG)
    TEST(UT_MEventDispatcher, DISABLED_EventDispatcherThreadUnSafeDebug)
    {
        ASSERT_DEATH({ EventDispatcherThreadUnSafeTest(); }, "");
    }
#else
    TEST(UT_MEventDispatcher, EventDispatcherThreadUnSafeProduction)
    {
        EventDispatcherThreadUnSafeTest();
    }
#endif
    
    
        // -------------------------------------------
    class MMyEventDispatcherThreadUnSafeMainEntry
    : public IThreadMainEntryPoint
    , private TNonCopyable<MMyEventDispatcherThreadUnSafeMainEntry>
    {
    public:
        MMyEventDispatcherThreadUnSafeMainEntry()
        : mTagDidRun(false)
        , iCallRun(false)
        {}
        
        virtual void MainEntry()
        {
            mTagDidRun = true;
            TPlatformThread::SetName("MMyEventDispatcherThreadUnSafeMainEntry");
            const char* name = TPlatformThread::Name();
            int ret = strcmp(name, "MMyEventDispatcherThreadUnSafeMainEntry");
            EXPECT_EQ(0, ret);
            
            iMEventDispatcher = MEventDispatcher::New(); //ideally should be here
//            TLambda lambda;
//            iMEventDispatcher->ExecuteAsynch(lambda);
            
            
            //ScheduleWork();
            
            
            return;
        }
        
        
        bool TagDidRun() const { return mTagDidRun; }
        void SetSleepTag(bool aSleep) { iCallRun = aSleep; }
        
       void PostTask()
            {
            TLambda lambda;
            iMEventDispatcher->ExecuteAsynch(lambda);
            }
        
        TPlatformThreadID GetThreadId() { return TPlatformThread::CurrentID(); }
        
    private:
        bool mTagDidRun;
        bool iCallRun;
        MEventDispatcher* iMEventDispatcher;
    };
    
    
    
    TEST(UT_MEventDispatcher, CallRun)
    {
        MMyEventDispatcherThreadUnSafeMainEntry* threadUnSafeEvtDispatcher = new MMyEventDispatcherThreadUnSafeMainEntry();
        TPlatformThreadHandle h;
        threadUnSafeEvtDispatcher->SetSleepTag(true);
        ASSERT_FALSE( threadUnSafeEvtDispatcher->TagDidRun() );
        
        EThreadPriority aPriority = EThreadPriority_Normal;
        ASSERT_TRUE( TPlatformThread::Create(kStackSize, kJoinable, threadUnSafeEvtDispatcher, &h, aPriority) );
        TPlatformThread::Join(&h);
            //TPlatformThread::Sleep(100);
        threadUnSafeEvtDispatcher->PostTask();
        ASSERT_TRUE( threadUnSafeEvtDispatcher->TagDidRun() );
    }
    
    
} //namespace vbase