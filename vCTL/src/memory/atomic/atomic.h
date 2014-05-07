//
//  atomic.h
//  vClientTemplateLib
//
//  Created by Virendra Shakya on 5/6/14.
//  Copyright (c) 2014 Virendra Shakya. All rights reserved.
//

#ifndef __vClientTemplateLib__atomic__
#define __vClientTemplateLib__atomic__

#include <stdint.h>

namespace vctl
{

class TAtomic
    {
public:
    static int32_t BarrieredAtomicAdd();
    static int32_t BarrieredAtomicIncrement();
    };

} //namespace vctl

#endif /* defined(__vClientTemplateLib__atomic__) */
