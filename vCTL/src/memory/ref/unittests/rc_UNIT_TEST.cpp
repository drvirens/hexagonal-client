//
//  rc_UNIT_TEST.cpp
//  vClientTemplateLib
//
//  Created by Virendra Shakya on 5/7/14.
//  Copyright (c) 2014 Virendra Shakya. All rights reserved.
//

#include "memory/ref/rc.h"
#include "memory/ref/rc_thread_safe.h"
#include "build/build_config.h"

#include "3p/google/gtest/include/gtest/gtest.h"

namespace vctl
{

class CMyRefCountedClass : public CReference<CMyRefCountedClass>
    {
friend class CReference<CMyRefCountedClass>; //dtor is private and we wanna be dead sure that only CReference<> will delete it when count becomes 0
public:
    CMyRefCountedClass() : iSomeNumber(68)
        {}
        
    int iSomeNumber;
        
private:
    ~CMyRefCountedClass()
        {
        }
    
    };

TEST(UT_CReference, DISABLED_Trivial)
    {
    CMyRefCountedClass* ref = new CMyRefCountedClass();
    ref->Retain(); // count = 1
    ref->Release(); //count = 0 --> will delete ref
    }

void UnMatchedRetainRelease()
    {
    CMyRefCountedClass* ref = new CMyRefCountedClass();
    ref->Retain(); // count = 1
    
    //ref->Release(); //count = 0
    ref->Release(); //should assert for debug build
    }

    
#if defined( __i386__)
    //assert_death is not compiling on arm
    TEST(UT_CReference, DISABLED_UnMatchedRetainReleaseTest)
    {
        EXPECT_DEATH({ UnMatchedRetainRelease(); }, "Retain and Release did not match");
    }
#endif

} //namespace vbase

