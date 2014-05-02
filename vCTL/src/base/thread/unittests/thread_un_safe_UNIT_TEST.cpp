    //
    //  thread_un_safe_UNIT_TEST.cpp
    //  vClientTemplateLib
    //
    //  Created by Virendra Shakya on 4/26/14.
    //  Copyright (c) 2014 Virendra Shakya. All rights reserved.
    //

#include <stdio.h>

#include "base/thread/thread_un_safe.h"
#include "base/thread/detail/thread_un_safe_debug.h"
#include "base/thread/detail/thread_un_safe_production.h"
#include "base/thread/thread_loopless.h"
#include "base/non_copyable.h"
#include "3p/google/gtest/include/gtest/gtest.h"

namespace vbase
{
    
    class MyThreadUnSafeClass : public TNotThreadSafe
    {
    public:
        MyThreadUnSafeClass()
        {
            
        }
        void Foo()
        {
            AssertValidThreadCall();
        }
        void DiwOwnThread()
        {
            DisOwnThread();
        }
    };
    
    TEST(UT_TThreadUnSafe, ThreadUnSafeTrivial)
    {
        TNotThreadSafe tud;
        tud.AssertValidThreadCall();
    }
    
    TEST(UT_TThreadUnSafe, DeriveFromThreadUnSafe)
    {
        MyThreadUnSafeClass t;
        t.Foo();
    }
    
        // ---------------------
    class FooCallerThread
    : public TLooplessThread
    , private TNonCopyable<FooCallerThread>
    {
    public:
        explicit FooCallerThread(std::string& aThreadName, MyThreadUnSafeClass* aMyThreadUnSafeClass)
        : TLooplessThread(aThreadName)
        , mDidRun(false)
        , mMyThreadUnSafeClass(aMyThreadUnSafeClass)
        {}
        
        virtual void Run()
        {
            mDidRun = true;
            mMyThreadUnSafeClass->Foo(); //should assert for IsNotThreadSafe-test
        }
        
        bool GetDidRunTag() const { return mDidRun; }
    private:
        bool mDidRun;
        MyThreadUnSafeClass* mMyThreadUnSafeClass;
    };
    
        //since it calls Foo in other thread, program should abort
    void CanNotCallMethodOnOtherThreadTest()
    {
            //constructor allocated on this thread, so should not call Foo() on other thread
        MyThreadUnSafeClass* ctorThread = new MyThreadUnSafeClass();
        
        std::string threadName = "viren-loopless-thread";
        FooCallerThread looplessThread(threadName, ctorThread);
        EXPECT_TRUE(looplessThread.GetDidRunTag() == false);
        looplessThread.Start();
        looplessThread.Join();
        EXPECT_TRUE(looplessThread.GetDidRunTag() == true);
    }
    
#if !defined(NDEBUG) 
#if defined( __i386__)
    //assert_death is not compiling on arm
    TEST(UT_TThreadUnSafe, DISABLED_CanNotCallMethodOnOtherThreadInDebug)
    {
        ASSERT_DEATH({ CanNotCallMethodOnOtherThreadTest(); }, "");
    }
#endif
#else
    TEST(UT_TThreadUnSafe, CanCallMethodOnOtherThreadInProduction)
    {
        CanNotCallMethodOnOtherThreadTest();
    }
#endif
    
    
    
    
} // namespace vbase