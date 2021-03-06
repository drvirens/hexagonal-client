//
//  semaphore_impl_compatible_POSIX.h
//  vClientTemplateLib
//
//  Created by Virendra Shakya on 5/12/14.
//  Copyright (c) 2014 Virendra Shakya. All rights reserved.
//

#ifndef __vClientTemplateLib__semaphore_impl_compatible_POSIX__
#define __vClientTemplateLib__semaphore_impl_compatible_POSIX__

#include "base/non_copyable.h"
#include "base/synchronize/semaphore_value.h"

namespace vbase
{
namespace detail
{

class TSemaphorePosixCompatibleData;

class TSemaphorePosixCompatible : private TNonCopyable<TSemaphorePosixCompatible>
    {
public:
    TSemaphorePosixCompatible(TSemaphoreValue aValue);
    ~TSemaphorePosixCompatible();
    bool DoWait();
    bool DoSignal();
    bool DoSignalAll();
    
private:
    TSemaphorePosixCompatibleData* iData;
    };

} //namespace detail
} //namespace vbase

#endif /* defined(__vClientTemplateLib__semaphore_impl_compatible_POSIX__) */
