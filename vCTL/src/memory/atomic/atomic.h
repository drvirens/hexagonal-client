//
//  atomic.h
//  vClientTemplateLib
//
//  Created by Virendra Shakya on 5/6/14.
//  Copyright (c) 2014 Virendra Shakya. All rights reserved.
//

#ifndef __vClientTemplateLib__atomic__
#define __vClientTemplateLib__atomic__


#include "memory/atomic/atomic_type.h"

namespace vctl
{

class TAtomicOperation
    {
public:
    // see http://en.wikipedia.org/wiki/Memory_barrier
    static void MemoryBarrier();
    
    //
    // Increment "*aValueToIncrement" by "aIncrementByAmount" and return the value
    //
    static TAtomicInt32 BarrieredAtomicIncrement(volatile TAtomicInt32* aValueToIncrement, TAtomicInt32 aIncrementByAmount);
    
    static TAtomicInt32 AcquireLoad(volatile const TAtomicInt32* aPtr);
    };

} //namespace vctl

#endif /* defined(__vClientTemplateLib__atomic__) */
