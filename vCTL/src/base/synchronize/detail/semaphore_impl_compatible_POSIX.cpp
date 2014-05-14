//
//  semaphore_impl_compatible_POSIX.cpp
//  vClientTemplateLib
//
//  Created by Virendra Shakya on 5/12/14.
//  Copyright (c) 2014 Virendra Shakya. All rights reserved.
//

#include <errno.h>
#include <pthread.h>
#include "base/synchronize/detail/semaphore_impl_compatible_POSIX.h"
#include "base/thread_syn_logger/macrologger.h"

namespace vbase
{
namespace detail
{

#if !defined(NDEBUG)
#define LOG_IF_ERROR( error ) \
                    if( 0 != (error) ) \
                        { \
                        KERNEL_LOG_ERROR(" error = [%s]", strerror(errno)); \
                        }

#endif

class CondVar;
// ------------------ Futex
class Futex
    {
friend class CondVar;
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
    
    e = pthread_mutexattr_settype(&attributes, PTHREAD_MUTEX_ERRORCHECK);
    LOG_IF_ERROR(e);
    
    e = pthread_mutex_init(&iMutex, &attributes);
    LOG_IF_ERROR(e);
    
    e = pthread_mutexattr_destroy(&attributes);
    LOG_IF_ERROR(e);
#else
    e = pthread_mutex_init(&iMutex, 0);
    LOG_IF_ERROR(e);
#endif
    }
    
Futex::~Futex()
    {
    int e = pthread_mutex_destroy(&iMutex);
    LOG_IF_ERROR(e);
    }
    
void Futex::Lock()
    {
    int e = pthread_mutex_lock(&iMutex);
    LOG_IF_ERROR(e);
    }
    
void Futex::Unlock()
    {
    int e = pthread_mutex_unlock(&iMutex);
    LOG_IF_ERROR(e);
    }

// ------------------ CondVar
class CondVar
    {
public:
    CondVar();
    ~CondVar();
    void Wait(Futex& aLock);
    void SignalOne();
private:
    pthread_cond_t iCondition;
    };

CondVar::CondVar()
    {
    int e = pthread_cond_init(&iCondition, 0);
    LOG_IF_ERROR(e);
    }
    
CondVar::~CondVar()
    {
    int e = pthread_cond_destroy(&iCondition);
    LOG_IF_ERROR(e);
    }
    
void CondVar::Wait(Futex& aLock)
    {
    int e = pthread_cond_wait(&iCondition, &aLock.iMutex);
    LOG_IF_ERROR(e);
    }
    
void CondVar::SignalOne()
    {
    int e = pthread_cond_signal(&iCondition);
    LOG_IF_ERROR(e);
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

