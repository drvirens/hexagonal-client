//
//  lock_UNIT_TEST.cpp
//  vClientTemplateLib
//
//  Created by Virendra Shakya on 4/23/14.
//  Copyright (c) 2014 Virendra Shakya. All rights reserved.
//

#include "base/synchronize/lock.h"
#include "base/thread/thread_platform.h"
#include "3p/google/gtest/include/gtest/gtest.h"

namespace vbase
{
    
TEST(UT_TLock, Trivial)
    {
    int trivial = 0;
    TLock lock;
        {
        lock.Acquire();
        trivial = 10;
        lock.Release();
        }
    }
    
void TestDoubleLockDeath()
    {
    int trivial = 0;
    TLock lock;
        {
        lock.Acquire();
        trivial = 10;
        lock.Acquire();  // <--- expect assertion abort
        lock.Release();
        }
    }

    
TEST(UT_TLock, DoubleLockDeath)
    {
    EXPECT_DEATH(TestDoubleLockDeath(), "");
    }
    
class MLockTestThread
    : public IThreadMainEntryPoint
    , private TNonCopyable<MLockTestThread>
    {
public:
    explicit MLockTestThread(TLock& aLock)
        : mLock(aLock)
        , mCounter(0)
        {}
    
    virtual void MainEntry()
        {
        mLock.Acquire();
        mCounter++;
        mLock.Release();
        }
    
    int Counter() const { return mCounter; }
    void SetCounter(int aCounter) { mCounter = aCounter; }
    
private:
    TLock& mLock; // protects mCOunter
    int mCounter;
    };


TEST(UT_TLock, AcquireAndRelease)
    {
    TLock myLock;
    MLockTestThread t(myLock); // = new MLockTestThread(myLock);
    TPlatformThreadHandle h; // = new TPlatformThreadHandle();
    t.SetCounter(0);
    
    ASSERT_EQ(0, t.Counter());
    
    size_t aStackSize = 0;
    bool aJoinable = true;
    EThreadPriority aPriority = EThreadPriority_Normal;
    TThreadHandle threadhandle = TPlatformThread::Create(aStackSize, aJoinable, &t, &h, aPriority) ;
    //TPlatformThread::Join(&h);
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

    
    ASSERT_GT(t.Counter(), 0);
    }
} //vbase

