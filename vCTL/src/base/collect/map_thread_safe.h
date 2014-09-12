//
//  map_thread_safe.h
//  vClientTemplateLib
//
//  Created by Virendra Shakya on 6/4/14.
//  Copyright (c) 2014 Virendra Shakya. All rights reserved.
//

#ifndef __vClientTemplateLib__map_thread_safe__
#define __vClientTemplateLib__map_thread_safe__

#include <map>

#include "base/synchronize/lock.h"

namespace vbase
{

template <class KEY, class VALUE>
class CMapThreadSafe
    {
public:
    void Add(const KEY& aKey, const VALUE& aItem)
        {
        vbase::TAutoLock guard(iLock);
        iMap.insert( std::make_pair(aKey, aItem) );
        }
        
    VALUE Remove(const KEY& aItem);
    
    VALUE Get(const KEY& aKey)
        {
        VALUE v = iMap[ aKey ];
        return v;
        }
    
    int Size() const
        {
        return iMap.size();
        }
        
private:
    vbase::TLock iLock; //protects access to iHttpHeadersMap
    std::map<KEY, VALUE> iMap;
    };

} //namespace vbase

#endif /* defined(__vClientTemplateLib__map_thread_safe__) */
