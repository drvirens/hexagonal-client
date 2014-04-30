//
//  run_loop_cocoa_darwin_UT.mm
//  vClientTemplateLib
//
//  Created by Virendra Shakya on 4/29/14.
//  Copyright (c) 2014 Virendra Shakya. All rights reserved.
//

#include "base/thread/thread_platform.h"
#include "3p/google/gtest/include/gtest/gtest.h"

namespace vbase
{
    class MMyRunLoopThreadMainEntry
    : public IThreadMainEntryPoint
    , private TNonCopyable<MMyRunLoopThreadMainEntry>
    {
    public:
        MMyRunLoopThreadMainEntry()
        : mTagDidRun(false)
        , mSleep(false)
        {}
        
        virtual void MainEntry()
        {
            mTagDidRun = true;
            TPlatformThread::SetName("viren-thread");
            const char* name = TPlatformThread::Name();
            int ret = strcmp(name, "viren-thread");
            EXPECT_EQ(0, ret);
            
//            if(mSleep)
//            {
//                for(int i = 0; i < 10; i++) //infinite
//                {
//                    TPlatformThread::Sleep(5);
//                }
//            }
            //call run-loop shit here for testing
            
            return;
        }
        
        bool TagDidRun() const { return mTagDidRun; }
        void SetSleepTag(bool aSleep) { mSleep = aSleep; }
        TPlatformThreadID GetThreadId() { return TPlatformThread::CurrentID(); }
        
    private:
        bool mTagDidRun;
        bool mSleep;
    };
    
    
    static const size_t kStackSize = 0;
    static const bool kJoinable = true;
        // ------------------------------------------------------------ CreatePlatformThread
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
    
    
} //namespace vbase
