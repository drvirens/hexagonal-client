//
//  semaphore_UNIT_TEST.cpp
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

#include "base/synchronize/semaphore.h"
#include "3p/google/gtest/include/gtest/gtest.h"

namespace vbase
{

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
    
    aArrived->Signal();
    bArrived->Wait();
    
    EXPECT_LE(thiz->iCurrentStatement, kStatementA2);
    
    thiz->iCurrentStatement = kStatementA2;
    
    return NULL;
    }
    
void* thread_B(void* aData)
    {
    SharedData* thiz = static_cast<SharedData*>(aData);
    TSemaphore* aArrived = thiz->iSemaphoreA;
    TSemaphore* bArrived = thiz->iSemaphoreB;
    
    thiz->iCurrentStatement = kStatementB1;
    
    bArrived->Signal();
    aArrived->Wait();
    
    EXPECT_LE(thiz->iCurrentStatement, kStatementA2);
    
    thiz->iCurrentStatement = kStatementB2;
    
    return NULL;
    }

TEST(UT_TSemaphore, DISABLED_Rendezvous)
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
    
    EXPECT_EQ(data.iCurrentStatement, kStatementB2);
    
    }

} //namespace vbase
