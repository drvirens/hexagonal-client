//
//  rc.h
//  vClientTemplateLib
//
//  Created by Virendra Shakya on 5/6/14.
//  Copyright (c) 2014 Virendra Shakya. All rights reserved.
//

#ifndef __vClientTemplateLib__rc__
#define __vClientTemplateLib__rc__

#include "logging/log_logger.h"
#include "base/non_copyable.h"
#include "build/build_utils.h"

namespace vctl
{

class CReferenceBase : private TNonCopyable<CReferenceBase>
    //
    // not thread-safe.
    // use it on the same thread.
    // to use thread-safe rc, scroll down
    //
    {
protected:
    CReferenceBase()
        : iCount(0)
        , iIsCommitingSuicide(false)
        {}
        
    ~CReferenceBase()
        {
        ASSERT(true == iIsCommitingSuicide);
        }
        
    void Retain() const
        {
        ASSERT(false == iIsCommitingSuicide); //in our c++ objects, if an object wanna commits suicide, you dont stop him :)
        ++iCount;
        }
        
    bool Release() const
        {
        ASSERT(false == iIsCommitingSuicide); //if object is already ready to commit suicide, then you can't just shoot at such object.
        if(0 == iCount)
            {
            iIsCommitingSuicide = true;
            }
        return iIsCommitingSuicide;
        }
        
private:
    mutable int iCount;
    mutable bool iIsCommitingSuicide;
    };
    
// -------------
template <class CRTP>
class CReference : public CReferenceBase, private TNonCopyable<CReference<CRTP> >
    {
    //
    // Good practice: always make your derived class' destructor private to avoid accidental deletions.
    // The effect of doing so is compiler will emit errors which can be handled more efficiently
    //
    //      class Flower : public CReference<Flower>
    //          {
    //      public:
    //          // your interface shit here
    //      private:
    //          ~Flower();
    //          friend class CReference<Flower>;
    //          };
    //
public:
    CReference() {}
    
    void Retain() const
        {
        CReferenceBase::Retain();
        }
    
    void Release() const
        {
        if(CReferenceBase::Release()) //releasable, delete this
            {
            const CRTP* thiz = static_cast<const CRTP*>(this);
            delete thiz;
            }
        }
    
protected:
    ~CReference() {}
    };
    
} //namespace vctl

#endif /* defined(__vClientTemplateLib__rc__) */
