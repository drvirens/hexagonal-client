//
//  atomic_impl.cpp
//  vClientTemplateLib
//
//  Created by Virendra Shakya on 5/7/14.
//  Copyright (c) 2014 Virendra Shakya. All rights reserved.
//

#include "memory/atomic/detail/atomic_impl.h"
#include "build/build_config.h"

namespace vctl
{
namespace detail
{

#if defined(V_PLATFORM_DARWIN)

#include <libkern/OSAtomic.h>

void DoMemoryBarrier()
    {
    OSMemoryBarrier();
    }
    
TAtomicInt32 DoBarrieredAtomicIncrement(volatile TAtomicInt32* aValueToIncrement, TAtomicInt32 aIncrementByAmount)
    {
/*! @abstract Atomically adds two 32-bit values.
    @discussion
	This function adds the value given by <code>__theAmount</code> to the
	value in the memory location referenced by <code>__theValue</code>,
	storing the result back to that memory location atomically.

	This function is equivalent to {@link OSAtomicAdd32}
	except that it also introduces a barrier.
    @result Returns the new value.
*/

    TAtomicInt32 r = OSAtomicAdd32Barrier(aIncrementByAmount, aValueToIncrement);
    return r;
    }
    
#else

#error DoMemoryBarrier and DoBarrieredAtomicIncrement not funcking implemented in atomic_impl.cpp go figure!

#endif

} // namespace detail
} // namespace vctl

