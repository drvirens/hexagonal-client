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
    }
    
    bool TagDidRun() const { return mTagDidRun; }
    
  private:
    bool mTagDidRun;
  };
  
  
  TEST(UT_TPlatformThread, CreatePlatformThread)
  {
    MMyThreadMainEntry t; // = new MMyThreadMainEntry();
    TPlatformThreadHandle h; // = new TPlatformThreadHandle();
    ASSERT_FALSE( t.TagDidRun() );
    size_t aStackSize = 0;
    bool aJoinable = true;
    EThreadPriority aPriority = EThreadPriority_Normal;
    ASSERT_TRUE( TPlatformThread::Create(aStackSize, aJoinable, &t, &h, aPriority) );
    TPlatformThread::Join(&h);
    ASSERT_TRUE( t.TagDidRun() );
  }
} //vbase

