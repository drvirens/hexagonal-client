//
//  http_method_get.h
//  vClientTemplateLib
//
//  Created by Virendra Shakya on 5/16/14.
//  Copyright (c) 2014 Virendra Shakya. All rights reserved.
//

#ifndef __vClientTemplateLib__http_method_get__
#define __vClientTemplateLib__http_method_get__

#include <string>
#include "net/http/core/http_core_request.h"

namespace vctl
{
namespace net
{
namespace http
{

class CHttpGet : public IHttpRequest
    {
public:
    virtual ~CHttpGet();
    explicit CHttpGet(const std::string& aUri);
    
    virtual EHttpMethodType HttpMethod() const;
    virtual IHttpEntity* HttpEntity() const;
    
    };

} //namespace http
} //namespace net
} //namespace vctl


#endif /* defined(__vClientTemplateLib__http_method_get__) */
