//
//  http_core_request.h
//  vClientTemplateLib
//
//  Created by Virendra Shakya on 5/16/14.
//  Copyright (c) 2014 Virendra Shakya. All rights reserved.
//

#ifndef __vClientTemplateLib__http_core_request__
#define __vClientTemplateLib__http_core_request__

#include "net/http/core/http_core_message.h"
#include "net/http/core/http_core_method_type.h"

namespace vctl
{
namespace net
{
namespace http
{

class IHttpEntity;

class IHttpRequest : public IHttpMessage
    {
public:
    virtual ~IHttpRequest() {}
    
    virtual void Cancel() = 0;
    virtual bool IsCancelled() const = 0;
    virtual EHttpMethodType HttpMethod() const = 0;
    virtual IHttpEntity* HttpEntity() const = 0;
    
    //from IHttpMessage
    virtual TProtocolVersion Version() const = 0;
    virtual void AddHeader(const THeader& aHeader) = 0;
    virtual void RemoveHeader(const THeader& aHeader) = 0;

    };

} //namespace http
} //namespace net
} //namespace vctl


#endif /* defined(__vClientTemplateLib__http_core_request__) */
