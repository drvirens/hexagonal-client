//
//  semaphore.cpp
//  vClientTemplateLib
//
//  Created by Virendra Shakya on 5/11/14.
//  Copyright (c) 2014 Virendra Shakya. All rights reserved.
//

#include "base/synchronize/semaphore.h"

namespace vbase
{

TSemaphore::TSemaphore(TSemaphoreValue aValue)
    : iImpl(aValue)
    {
    }
    
TSemaphore::~TSemaphore()
    {
    }
    
void TSemaphore::Wait()
    {
    iImpl.DoWait();
    }
    
bool TSemaphore::TryWait()
    {
    return iImpl.DoTryWait();
    }
    
void TSemaphore::Signal()
    {
    iImpl.DoSignal();
    }
    
bool TSemaphore::Value(int& aValue) const
    {
    return iImpl.DoGetValue(aValue);
    }

} //namespace vbase
