//
//  http_core_header_map.h
//  vClientTemplateLib
//
//  Created by Virendra Shakya on 5/17/14.
//  Copyright (c) 2014 Virendra Shakya. All rights reserved.
//

#ifndef __vClientTemplateLib__http_core_header_group__
#define __vClientTemplateLib__http_core_header_group__

#include <string>
#include "base/thread/thread_un_safe.h"
#include "memory/ref/rc_thread_safe.h"
#include "base/collect/map_thread_safe.h"

namespace vctl
{
namespace net
{
namespace http
{

class THeader;
    
    //must be thread safe
class CHttpHeadersMap : public vctl::CReferenceThreadSafe<CHttpHeadersMap>
    {
public:
    static CHttpHeadersMap* New();
    
    void Add(const THeader& aHeader);
    
    int Size() const;
    bool GetHeader(int aIndex, THeader& aHeaderReturn);
    
protected:
    void Construct();
    CHttpHeadersMap();
    
    virtual ~CHttpHeadersMap();
    friend class vctl::CReferenceThreadSafe<CHttpHeadersMap>;
    
private:
    vbase::CMapThreadSafe<int, THeader> iMap;
    int iHeaderId;
    };

} //namespace http
} //namespace net
} //namespace vctl

#endif /* defined(__vClientTemplateLib__http_core_header_group__) */
