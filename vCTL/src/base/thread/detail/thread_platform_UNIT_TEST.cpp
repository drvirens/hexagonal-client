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
    {}
    
    virtual void MainEntry()
    {
      mTagDidRun = true;
      for(int i = 0; i < 10; i++) //infinite
      {
        TPlatformThread::Sleep(5);
      }
      
    }
    
    bool TagDidRun() const { return mTagDidRun; }
    
  private:
    bool mTagDidRun;
  };
  
  
  static const size_t kStackSize = 0;
  static const bool kJoinable = true;
// ------------------------------------------------------------ CreatePlatformThread
  TEST(UT_TPlatformThread, DISABLED_CreatePlatformThread)
  {
    MMyThreadMainEntry t;
    TPlatformThreadHandle h;
    ASSERT_FALSE( t.TagDidRun() );
    
    EThreadPriority aPriority = EThreadPriority_Normal;
    ASSERT_TRUE( TPlatformThread::Create(kStackSize, kJoinable, &t, &h, aPriority) );
    TPlatformThread::Join(&h);
    ASSERT_TRUE( t.TagDidRun() );
  }

// ------------------------------------------------------------ SleepForNSeconds
  TEST(UT_TPlatformThread, SleepForNSeconds)
  {
    MMyThreadMainEntry thread;
    TPlatformThreadHandle handle;
    ASSERT_FALSE( thread.TagDidRun() );
    
    EThreadPriority aPriority = EThreadPriority_Normal;
    ASSERT_TRUE( TPlatformThread::Create(kStackSize, kJoinable, &thread, &handle, aPriority) );
    
//    TPlatformThread::Sleep(5);
    
    TPlatformThread::Join(&handle);
    ASSERT_TRUE( thread.TagDidRun() );
  }
} //vbase

