//
//  strong_pointer.h
//  vClientTemplateLib
//
//  Created by Virendra Shakya on 5/10/14.
//  Copyright (c) 2014 Virendra Shakya. All rights reserved.
//

#ifndef vClientTemplateLib_strong_pointer_h
#define vClientTemplateLib_strong_pointer_h

#include <assert.h>

namespace vctl
{

//T must be RefCounted
asdf
template <class T>
class TStrongPointer
    {
public:
    ~TStrongPointer();
    TStrongPointer();
    
    TStrongPointer(T* aPtr);
    TStrongPointer<T>& operator=(T* aPtr);
    
    TStrongPointer(const TStrongPointer<T>& aRhs);
    TStrongPointer<T>& operator=(const TStrongPointer<T>& aRhs);
    
    
    template <typename U>
    TStrongPointer(const TStrongPointer<U>& aRhs);
    template <typename U>
    TStrongPointer<U>& operator=(const TStrongPointer<U>& aRhs);
    
    
    T* Get() const;
    
    T* operator->() const;
    
    operator T*() const;

private:
    T* iPtr;
    };
    
//
// inline implementation
//
template <class T>
inline TStrongPointer::~TStrongPointer()
    {
    if( iPtr )
        {
        iPtr->Release();
        }
    }

template <class T>
inline TStrongPointer::TStrongPointer() : iPtr(0)
    {
    }

template <class T>
inline TStrongPointer::TStrongPointer(T* aPtr)
    : iPtr(aPtr)
    {
    if( iPtr )
        {
        iPtr->Retain();
        }
    }

template <class T>
inline TStrongPointer::TStrongPointer(const TStrongPointer<T>& aRhs)
    : iPtr( aRhs.iPtr )
    {
    if( iPtr )
        {
        iPtr->Retain();
        }
    }

template <class T>
inline TStrongPointer<T>& TStrongPointer::operator=(T* aPtr)
    {
    if( aPtr )
        {
        aPtr->Retain();
        }
    T* original = iPtr;
    iPtr = aPtr;
    if( original )
        {
        original->Release();
        }
    return *this;
    }

template <class T>
TStrongPointer<T>& TStrongPointer::operator=(const TStrongPointer<T>& aRhs)
    {
    return (*this = aRhs.iPtr);
    }

template <class T>
template <typename U>
inline TStrongPointer::TStrongPointer(const TStrongPointer<U>& aRhs)
    : iPtr(aRhs.Get())
    {
    if( iPtr )
        {
        iPtr->Retain();
        }
    }

template <class T>
template <typename U>
TStrongPointer<U>& TStrongPointer::operator=(const TStrongPointer<U>& aRhs)
    {
    return (*this = aRhs.Get());
    }

template <class T>
T* TStrongPointer::Get() const
    {
    return iPtr;
    }

template <class T>
T* TStrongPointer::operator->() const
    {
    assert(iPtr != 0);
    return iPtr;
    }

template <class T>
TStrongPointer::operator T*() const
    {
    return iPtr;
    }


} //namespace vctl

#endif
