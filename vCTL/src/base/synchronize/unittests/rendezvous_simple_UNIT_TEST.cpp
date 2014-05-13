//
//  rendezvous_simple_UNIT_TEST.cpp
//  vClientTemplateLib
//
//  Created by Virendra Shakya on 5/11/14.
//  Copyright (c) 2014 Virendra Shakya. All rights reserved.
//

#include "build/build_config.h"

#if defined(V_PLATFORM_POSIX)
#include <pthread.h>
#elif defined(V_PLATFORM_WIN)
#include <windows.h>
#endif

#include "base/synchronize/rendezvous_simple.h"
#include "3p/google/gtest/include/gtest/gtest.h"

namespace vbase
{

TEST(UT_TRendezvous, Trivial)
    {
    TRendezvous t;
    }
    
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



void* thread_A(void* aData)
    {
    RendezvousSharedData* thiz = static_cast<RendezvousSharedData*>(aData);
    TRendezvous& rendezvous = thiz->iRendezvous;
    
    
    thiz->iCurrentStatement = kStatementRendezvousA1;
    
//    aArrived->Signal();
//    bArrived->Wait();
    rendezvous.Rendezvous(TRendezvous::ECheckpoint_First_Arrived);
    
    EXPECT_LE(thiz->iCurrentStatement, kStatementRendezvousA2);
    
    thiz->iCurrentStatement = kStatementRendezvousA2;
    
    return NULL;
    }
    
void* thread_B(void* aData)
    {
    RendezvousSharedData* thiz = static_cast<RendezvousSharedData*>(aData);
    TRendezvous& rendezvous = thiz->iRendezvous;
    
    thiz->iCurrentStatement = kStatementRendezvousB1;
    
//    bArrived->Signal();
//    aArrived->Wait();
    rendezvous.Rendezvous(TRendezvous::ECheckpoint_Second_Arrived);
    
    EXPECT_LE(thiz->iCurrentStatement, kStatementRendezvousA2);
    
    thiz->iCurrentStatement = kStatementRendezvousB2;
    
    return NULL;
    }

TEST(UT_TRendezvous, DISABLED_SynchronizeTwoThreads)
    {
    
    TRendezvous rendezvous;
    
    RendezvousSharedData data(rendezvous);
    
    pthread_t handleA;
    pthread_t handleB;
    
    pthread_create(&handleA, 0, thread_A, &data );
    pthread_create(&handleB, 0, thread_B, &data );
    
    pthread_join(handleA, NULL);
    pthread_join(handleB, NULL);
    
    EXPECT_EQ(data.iCurrentStatement, kStatementRendezvousB2);
    
    }
    
} //namespace vbase


