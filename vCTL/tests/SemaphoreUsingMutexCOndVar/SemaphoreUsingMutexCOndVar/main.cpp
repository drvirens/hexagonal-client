//
//  main.cpp
//  SemaphoreUsingMutexCOndVar
//
//  Created by Virendra Shakya on 5/14/14.
//  Copyright (c) 2014 Virendra Shakya. All rights reserved.
//

#include <iostream>

typedef int TSemaphoreValue;

class TSemaphorePosixCompatible;

template <class CRTP>
class TNonCopyable
    {
protected:
    TNonCopyable() {}
    ~TNonCopyable() {} //non-virtual
    
private:
    TNonCopyable(const TNonCopyable&);
    TNonCopyable& operator=(const TNonCopyable&);
    };

// interface


class TSemaphoreImpl : private TNonCopyable<TSemaphoreImpl>
    {
friend class TSemaphore;
private:
    explicit TSemaphoreImpl(TSemaphoreValue aValue);
    ~TSemaphoreImpl();
    
    void DoWait();
    bool DoTryWait();
    void DoSignal();
    
    bool DoGetValue(int& aValue) const;
    
private:
//#if defined(V_PLATFORM_DARWIN)
    mutable TSemaphorePosixCompatible* iPosixSemaphore;
//#else // #if defined(V_PLATFORM_DARWIN)
//    mutable TNativeSemaphore iSemaphore;
//#endif
    };



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
    TSemaphoreImpl iImpl;
    };

//

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

//implementation


TSemaphoreImpl::TSemaphoreImpl(TSemaphoreValue aValue)
    : iPosixSemaphore(0)
    {
    iPosixSemaphore = new TSemaphorePosixCompatible(aValue);
    }
    
TSemaphoreImpl::~TSemaphoreImpl()
    {
    delete iPosixSemaphore; iPosixSemaphore = 0;
    }
    
void TSemaphoreImpl::DoWait()
    {
    iPosixSemaphore->DoWait();
    }

// sem_trywait() is similar to sem_wait() except that if the
// semaphore value is not greater than 0, it returns an error.
bool TSemaphoreImpl::DoTryWait()
    {
    //return ( sem_trywait(&iSemaphore) == 0 );
    return false;
    }
    
void TSemaphoreImpl::DoSignal()
    {
    iPosixSemaphore->DoSignal();
    }

bool TSemaphoreImpl::DoGetValue(int& aValue) const
    {
//    int e; // = sem_getvalue(&iSemaphore, &aValue);
//    if( e != 0 )
//        {
////        KERNEL_LOG_ERROR("sem_post ERROR: %s", strerror(errno));
//        return false;
//        }
//    return true;
    
    return false;
    }


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


// ----

#define LOG_IF_ERROR( error ) \
                    if( 0 != (error) ) \
                        { \
                        printf(" error = [%s]", strerror(errno)); \
                        }


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
    void SignalAll();
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
    
void CondVar::SignalAll()
    {
    int e = pthread_cond_broadcast(&iCondition);
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
        
            //while(!iData->iCount)
            while(iData->iCount == 0)
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
            //iData->iCondVar.SignalOne();
            iData->iCondVar.SignalAll();
        
        iData->iLock.Unlock();
        }
    return r;
    }
    
bool TSemaphorePosixCompatible::DoSignalAll()
    {
    bool r = true;
    return r;
    }

// unit testing

//
//test description:
//
/*
create 2 threads with 2 statements in each:

Thread A               Thread B

statement a1            statement b1
statement a2            statement b2

Write a program such that : we want to guarantee that a1 happens before b2 and b1 happens before a2.
Hint: this synchronization pattern is called Rendezvous

*/

static void* thread_A(void* aData);
static void* thread_B(void* aData);

enum EStatementType
    {
    kStatement_NotInitialized,
    kStatementA1,
    kStatementB1,
    kStatementA2,
    kStatementB2,
    kStatement_MaxValue
    };
    
class SharedData
    {
public:
    SharedData(TSemaphore* aSemaA, TSemaphore* aSemaB)
        : iSemaphoreA(aSemaA)
        , iSemaphoreB(aSemaB)
        {}
        
    ~SharedData()
        {
        }
        
public:
    static EStatementType iCurrentStatement;
    TSemaphore* iSemaphoreA;
    TSemaphore* iSemaphoreB;
    };
    
EStatementType SharedData::iCurrentStatement = kStatement_NotInitialized;



void* thread_A(void* aData)
    {
    SharedData* thiz = static_cast<SharedData*>(aData);
    TSemaphore* aArrived = thiz->iSemaphoreA;
    TSemaphore* bArrived = thiz->iSemaphoreB;
    
    
    thiz->iCurrentStatement = kStatementA1;
    
    printf("---------------- Statement A1 \n");
    
    aArrived->Signal();
    bArrived->Wait();
    
    if(thiz->iCurrentStatement < kStatementA2)
        {
        printf("PASSEED in threadA \n");
        }
    else
        {
        printf("FAILED in threadA \n");
        }
    
    thiz->iCurrentStatement = kStatementA2;
    
    printf("---------------- Statement A2 \n");
    
    return NULL;
    }
    
void* thread_B(void* aData)
    {
    SharedData* thiz = static_cast<SharedData*>(aData);
    TSemaphore* aArrived = thiz->iSemaphoreA;
    TSemaphore* bArrived = thiz->iSemaphoreB;
    
    thiz->iCurrentStatement = kStatementB1;
    printf("---------------- Statement B1 \n");
    
    bArrived->Signal();
    aArrived->Wait();
//
    
//    EXPECT_LE(thiz->iCurrentStatement, kStatementA2);
    if(thiz->iCurrentStatement < kStatementA2)
        {
        printf("PASSEED in threadB \n");
        }
    else
        {
        printf("FAILED in threadB \n");
        }
    
    thiz->iCurrentStatement = kStatementB2;
    printf("---------------- Statement B2 \n");
    
    return NULL;
    }

void TEST_UT_TSemaphore_Rendezvous()
    {
    
    TSemaphore aArrivedSemaphore(0);
    TSemaphore bArrivedSemaphore(0);
    
    SharedData data(&aArrivedSemaphore, &bArrivedSemaphore);
    
    pthread_t handleA;
    pthread_t handleB;
    
    pthread_create(&handleA, 0, thread_A, &data );
    pthread_create(&handleB, 0, thread_B, &data );
    
    pthread_join(handleA, NULL);
    pthread_join(handleB, NULL);
    
    if(data.iCurrentStatement == kStatementB2)
        {
        printf("PASSEED overall \n");
        }
    else
        {
        printf("FAILED overall \n");
        }
    
    }

// -------------- rendezvous
//intended to work with 2 threads only
class TRendezvous : private TNonCopyable<TRendezvous>
    {
public:
    enum ECheckpointType
        {
        ECheckpoint_First_Arrived,
        ECheckpoint_Second_Arrived
        };
    TRendezvous();
    ~TRendezvous();
    
    void Rendezvous(const ECheckpointType& aCheckpoint);
    
private:
    TSemaphore iSemaphoreA;
    TSemaphore iSemaphoreB;
    };


static const TSemaphoreValue kRendezvousSimpleValue = 0;

TRendezvous::TRendezvous()
    : iSemaphoreA(kRendezvousSimpleValue)
    , iSemaphoreB(kRendezvousSimpleValue)
    {
    }
    
TRendezvous::~TRendezvous()
    {
    }
    
void TRendezvous::Rendezvous(const ECheckpointType& aCheckpoint)
    {
    
    switch (aCheckpoint) {
    
    case ECheckpoint_First_Arrived: //first == A
        {
        iSemaphoreA.Signal();
        iSemaphoreB.Wait();
        } break;
        
    case ECheckpoint_Second_Arrived: //second == B
        {
        iSemaphoreB.Signal();
        iSemaphoreA.Wait();
        } break;

    default:
        {
        //KERNEL_LOG_ERROR("ERROR: Wrong value passed to Rendezvous");
        } break;
    }
    }

// ------
//rendezvous test

    
//
//test description:
//
/*
create 2 threads with 2 statements in each:

Thread A               Thread B

statement a1            statement b1
statement a2            statement b2

Write a program such that : we want to guarantee that a1 happens before b2 and b1 happens before a2.
Hint: this synchronization pattern is called Rendezvous

*/

static void* thread_A(void* aData);
static void* thread_B(void* aData);

enum EStatementRendezvousType
    {
    kStatementRendezvous_NotInitialized,
    kStatementRendezvousA1,
    kStatementRendezvousB1,
    kStatementRendezvousA2,
    kStatementRendezvousB2,
    kStatementRendezvous_MaxValue
    };
    
class RendezvousSharedData
    {
public:
    RendezvousSharedData(TRendezvous& aRendezvous)
        : iRendezvous(aRendezvous)
         {}
        
    ~RendezvousSharedData()
        {
        }
        
public:
    static EStatementRendezvousType iCurrentStatement;
    TRendezvous& iRendezvous;
    };
    
EStatementRendezvousType RendezvousSharedData::iCurrentStatement = kStatementRendezvous_NotInitialized;



void* thread_A_rendezvous(void* aData)
    {
    RendezvousSharedData* thiz = static_cast<RendezvousSharedData*>(aData);
    TRendezvous& rendezvous = thiz->iRendezvous;
    
    
    thiz->iCurrentStatement = kStatementRendezvousA1;
    
    printf("[ rendezvous statement A1 ]\n");
    
//    aArrived->Signal();
//    bArrived->Wait();
    rendezvous.Rendezvous(TRendezvous::ECheckpoint_First_Arrived);
    
    if(thiz->iCurrentStatement < kStatementRendezvousA2)
        {
        printf("PASSEED in thread_A_rendezvous \n");
        }
    else
        {
        printf("FAILED in thread_A_rendezvous \n");
        }
        
    
    thiz->iCurrentStatement = kStatementRendezvousA2;
    
    printf("[ rendezvous statement A2 ]\n");
    
    return NULL;
    }
    
void* thread_B_rendezvous(void* aData)
    {
    RendezvousSharedData* thiz = static_cast<RendezvousSharedData*>(aData);
    TRendezvous& rendezvous = thiz->iRendezvous;
    
    thiz->iCurrentStatement = kStatementRendezvousB1;
    
    printf("[ rendezvous statement B1 ]\n");
    
//    bArrived->Signal();
//    aArrived->Wait();
    rendezvous.Rendezvous(TRendezvous::ECheckpoint_Second_Arrived);
    
    if(thiz->iCurrentStatement < kStatementRendezvousA2)
        {
        printf("PASSEED in thread_B_rendezvous \n");
        }
    else
        {
        printf("FAILED in thread_B_rendezvous \n");
        }
    
    thiz->iCurrentStatement = kStatementRendezvousB2;
    
    printf("[ rendezvous statement B2 ]\n");
    
    return NULL;
    }

void TEST_UT_TRendezvous_SynchronizeTwoThreads()
    {
    
    TRendezvous rendezvous;
    
    RendezvousSharedData data(rendezvous);
    
    pthread_t handleA;
    pthread_t handleB;
    
    pthread_create(&handleA, 0, thread_A_rendezvous, &data );
    pthread_create(&handleB, 0, thread_B_rendezvous, &data );
    
    pthread_join(handleA, NULL);
    pthread_join(handleB, NULL);
    
    if(data.iCurrentStatement, kStatementRendezvousB2)
      {
        printf("PASSEED rendezvous overall \n");
        }
    else
        {
        printf("FAILED rendezvous  overall \n");
        }

    }


// ------



int main(int argc, const char * argv[])
{

    // insert code here...
    std::cout << " \n\n 2 semaphores test \n\n";
    
    //TEST_UT_TSemaphore_Rendezvous();
    
    std::cout << " \n\n rendezvous test \n\n";
    
    TEST_UT_TRendezvous_SynchronizeTwoThreads();
    
//    for(int i = 0; i < 5; i++)
//        {
//        TEST_UT_TRendezvous_SynchronizeTwoThreads();
//        }
    
    return 0;
}

