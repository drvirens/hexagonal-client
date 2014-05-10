//
//  thread_bootstrap_params.h
//  vClientTemplateLib
//
//  Created by Virendra Shakya on 5/8/14.
//  Copyright (c) 2014 Virendra Shakya. All rights reserved.
//

#ifndef __vClientTemplateLib__thread_bootstrap_params__
#define __vClientTemplateLib__thread_bootstrap_params__

#include "base/non_copyable.h"
#include "base/thread/thread_priority.h"

namespace vbase
{
class IThreadMainEntryPoint;
class TLock;
class TConditionVariable;
class TPlatformThreadHandle;

namespace detail
{

class CThreadBootstrapParams : private TNonCopyable<CThreadBootstrapParams>
    {
public:
    static CThreadBootstrapParams* New(IThreadMainEntryPoint* aMainEntry,
                            bool aJoinable,
                            EThreadPriority aThreadPriority,
                            TPlatformThreadHandle* aHandle);
    
    ~CThreadBootstrapParams();
    
    static void* ThreadEntryFunction(void* aTThreadParamsPtr);
//    
//    void Wait();
//    void Signal();
    
private:
    CThreadBootstrapParams(IThreadMainEntryPoint* aMainEntry,
                            bool aJoinable,
                            EThreadPriority aThreadPriority,
                            TPlatformThreadHandle* aHandle);
    void Construct();
    
private:
    IThreadMainEntryPoint* mMainEntry;
    bool mJoinable;
    EThreadPriority mThreadPriority;
    TPlatformThreadHandle* mHandle;
    
//    TLock* mLock; //locks access to mConditionVariable & mWaitCondition
//    TConditionVariable* mConditionVariable; //waits on mWaitCondition
//    bool mWaitCondition;
    };


} //namespace detail
} //namespace vbase


#endif /* defined(__vClientTemplateLib__thread_bootstrap_params__) */
