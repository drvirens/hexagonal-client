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
    CReferenceBaseThreadSafe();
    ~CReferenceBaseThreadSafe();
    void Retain() const;
    bool Release() const;
    
private:
    mutable TAtomicCount iCount;
    mutable bool iIsCommitingSuicide;
    };

} //namespace vctl

#endif /* defined(__vClientTemplateLib__rc_thread_safe__) */
