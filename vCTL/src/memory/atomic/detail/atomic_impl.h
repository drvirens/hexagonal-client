//
//  atomic_impl.h
//  vClientTemplateLib
//
//  Created by Virendra Shakya on 5/7/14.
//  Copyright (c) 2014 Virendra Shakya. All rights reserved.
//

#ifndef vClientTemplateLib_atomic_impl_h
#define vClientTemplateLib_atomic_impl_h

#include "memory/atomic/atomic_type.h"

namespace vctl
{
namespace detail
{

void DoMemoryBarrier();
    
TAtomicInt32 DoBarrieredAtomicIncrement(volatile TAtomicInt32* aValueToIncrement, TAtomicInt32 aIncrementByAmount);

} // namespace detail
} // namespace vctl

#endif 

