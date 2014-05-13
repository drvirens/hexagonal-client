//
//  semaphore_impl_compatible_POSIX.cpp
//  vClientTemplateLib
//
//  Created by Virendra Shakya on 5/12/14.
//  Copyright (c) 2014 Virendra Shakya. All rights reserved.
//

#include <pthread.h>
#include "semaphore_impl_compatible_POSIX.h"

namespace vbase
{
namespace detail
{
#if !defined(NDEBUG)
#define LOG_IF_ERROR( error ) 
#endif

// ------------------ Futex
class Futex
    {
public:
    Futex();
    ~Futex();
    void Lock();
    void Unlock();
private:
    pthread_mutex_t iMutex;
    };

Futex::Futex()
    {
    int e = 0;
#if !defined(NDEBUG)
    pthread_mutexattr_t attributes;
    e = pthread_mutexattr_init(&attributes);
    LOG_IF_ERROR(e);
#else
    
#endif
    }
Futex::~Futex()
    {
    }
void Futex::Lock()
    {
    }
void Futex::Unlock()
    {
    }

// ------------------ CondVar
class CondVar
    {
public:
    CondVar();
    ~CondVar();
    template <class LOCK>
    void Wait(LOCK& aLock);
    void SignalOne();
    };

CondVar::CondVar()
    {
    }
    
CondVar::~CondVar()
    {
    }
    
template <class LOCK>
void CondVar::Wait(LOCK& aLock)
    {
    }
    
void CondVar::SignalOne()
    {
    }


class TSemaphorePosixCompatibleData
    {
friend class TSemaphorePosixCompatible;
public:
    TSemaphorePosixCompatibleData(TSemaphoreValue aCount)
        : iCount(aCount)
        {}

private:
    TSemaphoreValue iCount;
    Futex iLock;
    CondVar iCondVar;
    };


TSemaphorePosixCompatible::TSemaphorePosixCompatible(TSemaphoreValue aValue)
    : iData(0)
    {
    iData = new TSemaphorePosixCompatibleData(aValue);
    }
    
TSemaphorePosixCompatible::~TSemaphorePosixCompatible()
    {
    }
    
bool TSemaphorePosixCompatible::DoWait()
    {
    bool r = true;
        {
        iData->iLock.Lock();
        
            while(!iData->iCount)
                {
                iData->iCondVar.Wait( (iData->iLock) );
                }
            --(iData->iCount);
        
        }
        iData->iLock.Unlock();
    return r;
    }
    
bool TSemaphorePosixCompatible::DoSignal()
    {
    bool r = true;
        {
        iData->iLock.Lock();
        
            iData->iCount++;
            iData->iCondVar.SignalOne();
        
        iData->iLock.Unlock();
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

