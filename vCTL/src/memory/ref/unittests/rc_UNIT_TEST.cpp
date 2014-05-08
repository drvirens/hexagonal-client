//
//  rc_UNIT_TEST.cpp
//  vClientTemplateLib
//
//  Created by Virendra Shakya on 5/7/14.
//  Copyright (c) 2014 Virendra Shakya. All rights reserved.
//

#include "memory/ref/rc.h"
#include "memory/ref/rc_thread_safe.h"
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

TEST(UT_CReference, Trivial)
    {
    CMyRefCountedClass* ref = new CMyRefCountedClass();
    ref->Retain(); // count = 1
    
    ref->Release(); //count = 0
    //ref->iSomeNumber = 90; //undefined since ref is deleted here
    ref->Release(); //should assert for debug build
    }

} //namespace vbase

