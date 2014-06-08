//
//  http_request_get.h
//  Discount
//
//  Created by Virendra Shakya on 6/8/14.
//  Copyright (c) 2014 Justin. All rights reserved.
//

#ifndef __Discount__http_request_get__
#define __Discount__http_request_get__

#include "net/http/detail/http_request_base.h"
#include "net/http/core/http_core_method_type.h"

namespace vctl
{
namespace net
{
namespace http
{

class CHttpRequestGet : public CHttpRequestBase
    {
public:
    explicit CHttpRequestGet(const std::string& aUri)
        : CHttpRequestBase(aUri)
        {}
        
    virtual EHttpMethodType HttpMethod() const
        {
        return kHttpMethodGet;
        }
    };
    
} //namespace http
} //namespace net
} //namespace vctl

#endif /* defined(__Discount__http_request_get__) */
