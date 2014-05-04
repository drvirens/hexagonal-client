//
//  thread_loopless_UNIT_TEST.c
//  vClientTemplateLib
//
//  Created by Virendra Shakya on 4/27/14.
//  Copyright (c) 2014 Virendra Shakya. All rights reserved.
//

#include <string>
#include "base/thread/thread_loopless.h"
#include "base/non_copyable.h"
#include "3p/google/gtest/include/gtest/gtest.h"

namespace vbase
{

class MyLooplessThread
  : public TLooplessThread
  , private TNonCopyable<MyLooplessThread>
{
public:
  explicit MyLooplessThread(std::string& aThreadName)
    : TLooplessThread(aThreadName)
    , mDidRun(false)
  {}
  
  virtual void Run()
  {
    mDidRun = true;
  }
  
  bool GetDidRunTag() const { return mDidRun; }
private:
  bool mDidRun;
};

TEST(UT_TLooplessThread, DISABLED_Trivial)
{
  std::string threadName = "viren-loopless-thread";
  MyLooplessThread looplessThread(threadName);
  EXPECT_TRUE(looplessThread.GetDidRunTag() == false);
  looplessThread.Start();
  looplessThread.Join();
  EXPECT_TRUE(looplessThread.GetDidRunTag() == true);
}

} //namespace vbase
