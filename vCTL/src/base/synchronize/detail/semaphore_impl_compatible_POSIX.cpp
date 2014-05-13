//
//  semaphore_impl_compatible_POSIX.cpp
//  vClientTemplateLib
//
//  Created by Virendra Shakya on 5/12/14.
//  Copyright (c) 2014 Virendra Shakya. All rights reserved.
//

#include "semaphore_impl_compatible_POSIX.h"

namespace vbase
{
namespace detail
{

TSemaphorePosixCompatible::TSemaphorePosixCompatible(TSemaphoreValue aValue)
    : iLock()
    , iCount(aValue)
    , iCondVar(&iLock)
    {
    }
    
TSemaphorePosixCompatible::~TSemaphorePosixCompatible()
    {
    }
    
bool TSemaphorePosixCompatible::DoWait()
    {
    bool r = true;
        {
        TAutoLock guard(iLock);
        while(!iCount)
            {
            iCondVar.Wait();
            }
        --iCount;
        }
    return r;
    }
    
bool TSemaphorePosixCompatible::DoSignal()
    {
    bool r = true;
        {
        TAutoLock guard(iLock);
        iCount++;
        iCondVar.NotifyOne();
        }
    return r;
    }
    
bool TSemaphorePosixCompatible::DoSignalAll()
    {
    bool r = true;
    return r;
    }
    

} //namespace detail
} //namespace vbase

