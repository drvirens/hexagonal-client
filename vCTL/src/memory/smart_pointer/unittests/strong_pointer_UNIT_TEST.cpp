//
//  strong_pointer_UNIT_TEST.cpp
//  vClientTemplateLib
//
//  Created by Virendra Shakya on 5/10/14.
//  Copyright (c) 2014 Virendra Shakya. All rights reserved.
//

#ifndef vClientTemplateLib_strong_pointer_UNIT_TEST_cpp
#define vClientTemplateLib_strong_pointer_UNIT_TEST_cpp

#include "memory/smart_pointer/strong_pointer.h"
#include "memory/ref/rc.h"
#include "3p/google/gtest/include/gtest/gtest.h"

namespace vctl
{

class Foo : public CReference<Foo>
    {
public:
    int iValue;
    int GetValue() const { return iValue; }
    
    ~Foo()
        {
        }
    };

TEST(UT_StrongPointer, Trivial)
    {
    TStrongPointer<Foo> f = new Foo();
    f->iValue = 69;
    
    EXPECT_EQ(69, f->GetValue());
    }
    
TEST(UT_StrongPointer, ConversionOperatorTest)
    {
    TStrongPointer<Foo> f1 = new Foo();
    TStrongPointer<Foo> f2;
    
    EXPECT_TRUE(f1);
    EXPECT_FALSE(!f1);
    
    EXPECT_FALSE(f2);
    EXPECT_TRUE(!f2);
    
    EXPECT_NE(f1, f2);
    
    f2 = f1;
    
    EXPECT_EQ(f1, f2);
    }

} //namespace vctl

#endif
