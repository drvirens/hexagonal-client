//
//  semaphore_impl.cpp
//  vClientTemplateLib
//
//  Created by Virendra Shakya on 5/11/14.
//  Copyright (c) 2014 Virendra Shakya. All rights reserved.
//

#include "semaphore_impl.h"

namespace vbase
{
namespace detail
{

TSemaphoreImpl::TSemaphoreImpl(TSemaphoreValue aValue)
    {
    }
    
TSemaphoreImpl::~TSemaphoreImpl()
    {
    }
    
void TSemaphoreImpl::DoWait()
    {
    }
    
bool TSemaphoreImpl::DoTryWait()
    {
    return false;
    }
    
void TSemaphoreImpl::DoSignal()
    {
    }
    

} //namespace vbase
} //namespace detail
