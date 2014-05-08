//
//  atomic.cpp
//  vClientTemplateLib
//
//  Created by Virendra Shakya on 5/6/14.
//  Copyright (c) 2014 Virendra Shakya. All rights reserved.
//

#include "memory/atomic/detail/atomic_impl.h"
#include "memory/atomic/atomic.h"
#include "build/build_config.h"


namespace vctl
{

void TAtomicOperation::MemoryBarrier()
    {
    detail::DoMemoryBarrier();
    }
    
TAtomicInt32 TAtomicOperation::BarrieredAtomicIncrement(volatile TAtomicInt32* aValueToIncrement, TAtomicInt32 aIncrementByAmount)
    {
    return detail::DoBarrieredAtomicIncrement(aValueToIncrement, aIncrementByAmount);
    }
    

} //namespace vctl
