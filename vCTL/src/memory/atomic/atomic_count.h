//
//  atomic_count.h
//  vClientTemplateLib
//
//  Created by Virendra Shakya on 5/6/14.
//  Copyright (c) 2014 Virendra Shakya. All rights reserved.
//

#ifndef __vClientTemplateLib__atomic_count__
#define __vClientTemplateLib__atomic_count__

#include "memory/atomic/atomic.h"

namespace vctl
{

bool TAtomicCount_IsZero(volatile TAtomicInt32* aNumber);
void TAtomicCount_IncrementByOne(volatile TAtomicInt32* aNumber);
bool TAtomicCount_DecrementByOne(volatile TAtomicInt32* aNumber); //return if result is non-zero
    
} // namespace vctl

#endif /* defined(__vClientTemplateLib__atomic_count__) */
