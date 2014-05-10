//
//  thread_platform_UNIT_TEST.cpp
//  vClientTemplateLib
//
//  Created by Virendra Shakya on 4/21/14.
//  Copyright (c) 2014 Virendra Shakya. All rights reserved.
//


#include "base/thread/thread_platform.h"
#include "3p/google/gtest/include/gtest/gtest.h"

namespace vbase
{
class TestTrivialThread
    : public IThreadMainEntryPoint
    , private TNonCopyable<TestTrivialThread>
    {
public:
    TestTrivialThread()
        : mTagDidRun(false)
        , mSleep(false)
        {}
    
    virtual void MainEntry()
        {
        TPlatformThread::SetName("UT_TPlatformThread");
        
        mTagDidRun = true;
    
        const char* name = TPlatformThread::Name();
        int ret = strcmp(name, "UT_TPlatformThread");
        EXPECT_EQ(0, ret);

        if(mSleep)
            {
            for(int i = 0; i < 1; i++)
                {
                TPlatformThread::Sleep(1);
                }
            }
        
        return;
        }
    
    bool TagDidRun() const { return mTagDidRun; }
    void SetSleepTag(bool aSleep) { mSleep = aSleep; }
    
private:
    bool mTagDidRun;
    bool mSleep;
    };
    
    
static const size_t kStackSize = 0;
static const bool kJoinable = true;
    // ------------------------------------------------------------ CreatePlatformThread
TEST(UT_TPlatformThread, CreateOnePlatformThread)
    {
    TestTrivialThread threadEntry;
    
    TPlatformThreadHandle h;
    
    threadEntry.SetSleepTag(false);
    ASSERT_FALSE( threadEntry.TagDidRun() );
    
    EThreadPriority aPriority = EThreadPriority_Normal;
    
    TThreadHandle threadhandle = TPlatformThread::Create(kStackSize, kJoinable, &threadEntry, &h, aPriority) ;
    
    TPlatformThreadHandle joinhandle;
    if(h.RawHandle() == 0)
        {
        //use threadhandle
        joinhandle.SetRawHandle( threadhandle );
        }
    else
        {
        joinhandle = h;
        }
    TPlatformThread::Join(&joinhandle);
    
    ASSERT_TRUE( threadEntry.TagDidRun() );
    }
    
TEST(UT_TPlatformThread, CreateTenPlatformThreads)
    {
    TestTrivialThread threadEntry[10];
    
    TPlatformThreadHandle h[10];
    
    TThreadHandle threadhandle[10];
    
    for(int i = 0; i < 10; i++)
        {
        threadEntry[i].SetSleepTag(false);
        ASSERT_FALSE( threadEntry[i].TagDidRun() );
        }
    
    EThreadPriority aPriority = EThreadPriority_Normal;
    
    for(int i = 0; i < 10; i++)
        {
        threadhandle[i] = TPlatformThread::Create(kStackSize, kJoinable, &threadEntry[i], &h[i], aPriority) ;
        }
    
    for(int i = 0; i < 10; i++)
        {
        TPlatformThreadHandle joinhandle;
        if(h[i].RawHandle() == 0)
            {
            //use threadhandle
            joinhandle.SetRawHandle( threadhandle[i] );
            }
        else
            {
            joinhandle = h[i];
            }
        TPlatformThread::Join(&joinhandle);
        }
    
//    for(int i = 0; i < 10; i++)
//        {
//        TPlatformThread::Join(&h[i]);
//        }
    
    for(int i = 0; i < 10; i++)
        {
        ASSERT_TRUE( threadEntry[i].TagDidRun() );
        }
    }

    // ------------------------------------------------------------ SleepForNSeconds
TEST(UT_TPlatformThread, DISABLED_SleepForNSeconds)
    {
    TestTrivialThread threadEntry;
    TPlatformThreadHandle handle;
    threadEntry.SetSleepTag(true);
    ASSERT_FALSE( threadEntry.TagDidRun() );
    
    EThreadPriority aPriority = EThreadPriority_Normal;
    ASSERT_TRUE( TPlatformThread::Create(kStackSize, kJoinable, &threadEntry, &handle, aPriority) );
    
    TPlatformThread::Join(&handle);
    ASSERT_TRUE( threadEntry.TagDidRun() );
    }

    // ------------------------------------------------------------ ThreadID
TEST(UT_TPlatformThread, ThreadID)
    {
    TPlatformThreadID mainThreadId = TPlatformThread::CurrentID();
    
    TestTrivialThread threadEntry;
    TPlatformThreadHandle h;
    threadEntry.SetSleepTag(false);
    ASSERT_FALSE( threadEntry.TagDidRun() );
    
    EThreadPriority aPriority = EThreadPriority_Normal;
    TThreadHandle threadhandle = TPlatformThread::Create(kStackSize, kJoinable, &threadEntry, &h, aPriority);
    
    TPlatformThreadHandle joinhandle;
    if(h.RawHandle() == 0)
        {
        //use threadhandle
        joinhandle.SetRawHandle( threadhandle );
        }
    else
        {
        joinhandle = h;
        }
    TPlatformThread::Join(&joinhandle);
    
//    TPlatformThread::Join(&h);
    ASSERT_TRUE( threadEntry.TagDidRun() );
    
    EXPECT_EQ(mainThreadId, TPlatformThread::CurrentID());
    }

    // -----------------------------------------
class MYielderThreadMainEntry
    : public IThreadMainEntryPoint
    , private TNonCopyable<MYielderThreadMainEntry>
    {
public:
    MYielderThreadMainEntry()
        : mTagDidRun(false)
        , mSleep(false)
        {}
    
    virtual void MainEntry()
        {
        mTagDidRun = true;
        mYielderThreadId = TPlatformThread::CurrentID();
        
        TPlatformThread::SetName("MYielderThreadMainEntry");
        const char* name = TPlatformThread::Name();
        int ret = strcmp(name, "MYielderThreadMainEntry");
        EXPECT_EQ(0, ret);
        
        TPlatformThread::Yield();
        TPlatformThread::Sleep(1);
        
        EXPECT_EQ(TPlatformThread::CurrentID(), mYielderThreadId);
        
        return;
        }
    
    bool TagDidRun() const { return mTagDidRun; }
    void SetSleepTag(bool aSleep) { mSleep = aSleep; }
    
private:
    bool mTagDidRun;
    bool mSleep;
    TPlatformThreadID mYielderThreadId;
    };


    // ------------------------------------------------------------ Yield
TEST(UT_TPlatformThread, Yield)
    {
    MYielderThreadMainEntry threadEntry;
    TPlatformThreadHandle handle;
    threadEntry.SetSleepTag(true);
    ASSERT_FALSE( threadEntry.TagDidRun() );
    
    EThreadPriority aPriority = EThreadPriority_Normal;
    TThreadHandle threadhandle = TPlatformThread::Create(kStackSize, kJoinable, &threadEntry, &handle, aPriority);
    
        TPlatformThreadHandle joinhandle;
    if(handle.RawHandle() == 0)
        {
        //use threadhandle
        joinhandle.SetRawHandle( threadhandle );
        }
    else
        {
        joinhandle = handle;
        }
    TPlatformThread::Join(&joinhandle);

    //TPlatformThread::Join(&handle);
    ASSERT_TRUE( threadEntry.TagDidRun() );
    }
    
} //namespace vbase


