//
//  strong_pointer_UNIT_TEST.cpp
//  vClientTemplateLib
//
//  Created by Virendra Shakya on 5/10/14.
//  Copyright (c) 2014 Virendra Shakya. All rights reserved.
//

#ifndef vClientTemplateLib_strong_pointer_UNIT_TEST_cpp
#define vClientTemplateLib_strong_pointer_UNIT_TEST_cpp

#include "memory/smart_pointer/smart_pointer.h"
#include "memory/ref/rc.h"
#include "3p/google/gtest/include/gtest/gtest.h"

namespace vctl
{

class Foo : public CReference<Foo>
    {
    };

TEST(UT_StrongPointer, Trivial)
    {
    TStrongPointer<Foo> f = new Foo();
    }

} //namespace vctl

#endif
