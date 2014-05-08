//
//  atomic_count.cpp
//  vClientTemplateLib
//
//  Created by Virendra Shakya on 5/6/14.
//  Copyright (c) 2014 Virendra Shakya. All rights reserved.
//

#include "memory/atomic/atomic_count.h"
#include "memory/atomic/atomic.h"

namespace vctl
{

static bool TAtomicCount_DoDecrement(volatile TAtomicInt32* aNumber, TAtomicInt32 aDecrementBy);

bool TAtomicCount_IsZero(volatile TAtomicInt32* aNumber)
    {
    bool r = false;
    TAtomicInt32 value = TAtomicOperation::AcquireLoad(aNumber);
    if( 0 == value )
        {
        r = true;
        }
    return r;
    }
    
void TAtomicCount_IncrementByOne(volatile TAtomicInt32* aNumber)
    {
    TAtomicOperation::BarrieredAtomicIncrement(aNumber, 1);
    }
    
bool TAtomicCount_DecrementByOne(volatile TAtomicInt32* aNumber)
    {
    return TAtomicCount_DoDecrement(aNumber, 1);
    }
    
bool TAtomicCount_DoDecrement(volatile TAtomicInt32* aNumber, TAtomicInt32 aDecrementBy)
    {
    bool iszero = false;
    TAtomicInt32 r = TAtomicOperation::BarrieredAtomicIncrement(aNumber, -aDecrementBy);
    if(r == 0)
        {
        iszero = true;
        }
    return iszero;
    }
    
    
} // namespace vctl

