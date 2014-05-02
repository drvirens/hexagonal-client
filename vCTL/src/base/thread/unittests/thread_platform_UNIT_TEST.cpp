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
  class MMyThreadMainEntry
    : public IThreadMainEntryPoint
    , private TNonCopyable<MMyThreadMainEntry>
  {
  public:
    MMyThreadMainEntry()
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
      
      if(mSleep)
      {
        for(int i = 0; i < 1; i++) //infinite
        {
          TPlatformThread::Sleep(1);
        }
      }
      
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
  TEST(UT_TPlatformThread, CreatePlatformThread)
  {
    MMyThreadMainEntry threadEntry;
    TPlatformThreadHandle h;
    threadEntry.SetSleepTag(false);
    ASSERT_FALSE( threadEntry.TagDidRun() );
    
    EThreadPriority aPriority = EThreadPriority_Normal;
    ASSERT_TRUE( TPlatformThread::Create(kStackSize, kJoinable, &threadEntry, &h, aPriority) );
    TPlatformThread::Join(&h);
    ASSERT_TRUE( threadEntry.TagDidRun() );
  }

// ------------------------------------------------------------ SleepForNSeconds
  TEST(UT_TPlatformThread, SleepForNSeconds)
  {
    MMyThreadMainEntry threadEntry;
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
    
    MMyThreadMainEntry threadEntry;
    TPlatformThreadHandle h;
    threadEntry.SetSleepTag(false);
    ASSERT_FALSE( threadEntry.TagDidRun() );
    
    EThreadPriority aPriority = EThreadPriority_Normal;
    ASSERT_TRUE( TPlatformThread::Create(kStackSize, kJoinable, &threadEntry, &h, aPriority) );
    TPlatformThread::Join(&h);
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
      
      TPlatformThread::SetName("viren-thread");
      const char* name = TPlatformThread::Name();
      int ret = strcmp(name, "viren-thread");
      EXPECT_EQ(0, ret);
      
      TPlatformThread::Yield();
      TPlatformThread::Sleep(100);
      
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
    ASSERT_TRUE( TPlatformThread::Create(kStackSize, kJoinable, &threadEntry, &handle, aPriority) );
    
    TPlatformThread::Join(&handle);
    ASSERT_TRUE( threadEntry.TagDidRun() );
  }

} //namespace vbase


