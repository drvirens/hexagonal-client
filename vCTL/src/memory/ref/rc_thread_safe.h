//
//  rc_thread_safe.h
//  vClientTemplateLib
//
//  Created by Virendra Shakya on 5/6/14.
//  Copyright (c) 2014 Virendra Shakya. All rights reserved.
//

#ifndef __vClientTemplateLib__rc_thread_safe__
#define __vClientTemplateLib__rc_thread_safe__


#include "logging/log_logger.h"
#include "base/non_copyable.h"
#include "build/build_utils.h"
#include "memory/atomic/atomic_count.h"

namespace vctl
{
// -----------
class CReferenceBaseThreadSafe : private TNonCopyable<CReferenceBaseThreadSafe>
    {
protected:
    CReferenceBaseThreadSafe()
        : iCount(0)
        , iIsCommitingSuicide(false)
        {}

    ~CReferenceBaseThreadSafe()
        {
        ASSERT(true == iIsCommitingSuicide);
        }

    void Retain() const
        {
        ASSERT(false == iIsCommitingSuicide);
        TAtomicCount_IncrementByOne(&iCount);
        }

    bool Release() const
        {
        ASSERT(false == iIsCommitingSuicide);
        ASSERT(false == TAtomicCount_IsZero(&iCount));
        bool retisnonzero = TAtomicCount_DecrementByOne(&iCount);
        if(!retisnonzero)
            {
            iIsCommitingSuicide = true;
            }
        return iIsCommitingSuicide;
        }

    
private:
    mutable TAtomicInt32 iCount;
    mutable bool iIsCommitingSuicide;
    };
    
    
// -----------
template <class POINTER_TYPE>
class TDefaultDeletionPolicy
    {
public:
    static void Delete(const POINTER_TYPE* aThis)
        {
        delete aThis;
        }
    };

template <class CRTP, typename DELETE_POLICY>
class CReferenceThreadSafe
    : public CReferenceBaseThreadSafe
    , private TNonCopyable< CReferenceThreadSafe<CRTP, DELETE_POLICY> >
    {
public:
    CReferenceThreadSafe() {}
    
    void Retain() const
        {
        CReferenceBaseThreadSafe::Retain();
        }
        
    bool Release() const
        {
        if(CReferenceBaseThreadSafe::Release())
            {
            CRTP* thiz = static_cast<CRTP*>(this);
            DELETE_POLICY::Delete(thiz);
            }
        }
        
protected:
    ~CReferenceThreadSafe() {}
    };

} //namespace vctl

#endif /* defined(__vClientTemplateLib__rc_thread_safe__) */