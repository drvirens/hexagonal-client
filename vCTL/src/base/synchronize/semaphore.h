//
//  semaphore.h
//  vClientTemplateLib
//
//  Created by Virendra Shakya on 5/11/14.
//  Copyright (c) 2014 Virendra Shakya. All rights reserved.
//

#ifndef __vClientTemplateLib__semaphore__
#define __vClientTemplateLib__semaphore__

#include "base/non_copyable.h"
#include "base/synchronize/detail/semaphore_impl.h"
#include "base/synchronize/semaphore_value.h"

namespace vbase
{

class TSemaphore : private TNonCopyable<TSemaphore>
    {
public:
    explicit TSemaphore(TSemaphoreValue aValue);
    ~TSemaphore();
    
    /**
      * If the value of the semaphore is greater than 0, Wait() decreases it
      * by 1 and returns immediately. Otherwise, the thread is blocked.
      */
    void Wait();
    
    bool TryWait();
    
    /**
      * Increments the value of the semaphore . 
      * If the value becomes greater than 0, a thread may be unblocked.
      */
    void Signal();
    
    bool Value(int& aValue) const;
    
private:
    detail::TSemaphoreImpl iImpl;
    };

} //namespace vbase

#endif /* defined(__vClientTemplateLib__semaphore__) */
