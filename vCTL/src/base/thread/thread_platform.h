//
//  thread_platform.h
//  vClientTemplateLib
//
//  Created by Virendra Shakya on 4/21/14.
//  Copyright (c) 2014 Virendra Shakya. All rights reserved.
//

#ifndef __vClientTemplateLib__thread_platform__
#define __vClientTemplateLib__thread_platform__

#include "build/build_config.h"

#if defined(V_PLATFORM_POSIX)
#include <pthread.h>
#if defined(V_PLATFORM_IOS)
#include <sys/types.h> //for pid_t
#endif
#elif defined(V_PLATFORM_WIN)
#include <windows.h>
#endif

#include "base/non_copyable.h"
#include "base/thread/thread_priority.h"

namespace vbase
{

    // -------------------------------------------------------------- typedefs
#if defined(V_PLATFORM_POSIX)
    //typedef pid_t TPlatformThreadID;
    typedef unsigned int TPlatformThreadID;
    typedef pthread_t TThreadHandle;
#elif defined(V_PLATFORM_WIN)
    typedef DWORD TPlatformThreadID;
    typedef void* TThreadHandle;
#endif

    // -------------------------------------------------------------- TPlatformThreadHandle
/**
 * Simple abstraction for thread-handle
 */
class TPlatformThreadHandle
    {
public:
    TPlatformThreadHandle()
        : mRawHandle(0)
        , mThreadId(0)
        {}
    
//    explicit TPlatformThreadHandle(TThreadHandle aRawHandle)
//        : mRawHandle(aRawHandle)
//        , mThreadId(0)
//        {}
    
    TPlatformThreadHandle(TThreadHandle aRawHandle, TPlatformThreadID aThreadID)
        : mRawHandle(aRawHandle)
        , mThreadId(aThreadID)
        {}
    
    bool IsEqual(const TPlatformThreadHandle& aThreadHandle) const
        {
        return (mRawHandle == aThreadHandle.mRawHandle);
        }
    
    bool IsNull() const
        {
        return !mRawHandle;
        }
    
    TThreadHandle RawHandle() const
        {
        return mRawHandle;
        }
    
private:
    TThreadHandle mRawHandle;
    TPlatformThreadID mThreadId;
};

    // --------------------------------------------------------------
const TPlatformThreadID kInvalidThreadID(0);


    // -------------------------------------------------------------- IThreadMainEntryPoint
class IThreadMainEntryPoint
    {
public:
    virtual void MainEntry() = 0;
protected:
    virtual ~IThreadMainEntryPoint() {}
    };

    // -------------------------------------------------------------- IThreadTrivialInterface
template <class PLATFORM>
class IThreadOptionalInterface
    {
public:
    static void OnPreThreadCreate()
        {
        PLATFORM::OnPreThreadCreate();
        }
    static void OnThreadMainEnter()
        {
        PLATFORM::OnThreadMainEnter();
        }
    static void OnThreadMainExit()
        {
        PLATFORM::OnThreadMainExit();
        }
        
#if defined(V_PLATFORM_POSIX)
    static size_t GetDefaultStackSize(const pthread_attr_t& aAttributes)
        {
        return PLATFORM::GetDefaultStackSize(aAttributes);
        }
#endif
    };


    // -------------------------------------------------------------- TPlatformThread
class TPlatformThread : private TNonCopyable<TPlatformThread>
    {
public:
    static TPlatformThreadHandle CurrentHandle();
    static TPlatformThreadID CurrentID();
    static bool Create(size_t aStackSize,
                       bool aJoinable,
                       IThreadMainEntryPoint* aMainENtry,
                       TPlatformThreadHandle* aThreadHandle,
                       EThreadPriority aPriority);
    static void Join(TPlatformThreadHandle* aThreadHandle);
    static void SetPriority(TPlatformThreadHandle aThreadHandle, EThreadPriority aPriority);
    static void Yield();
    static void Sleep(int64_t aSeconds);
    
        //debug aid
    static void SetName(const char* aName); //not copied
    static const char* Name();
    };

} //namespace vbase


#endif /* defined(__vClientTemplateLib__thread_platform__) */
