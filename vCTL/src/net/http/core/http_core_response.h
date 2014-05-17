//
//  http_core_response.h
//  vClientTemplateLib
//
//  Created by Virendra Shakya on 5/16/14.
//  Copyright (c) 2014 Virendra Shakya. All rights reserved.
//

#ifndef __vClientTemplateLib__http_core_response__
#define __vClientTemplateLib__http_core_response__

#include "net/http/core/http_core_message.h"
#include "net/http/core/http_core_method_type.h"

namespace vctl
{
namespace net
{
namespace http
{

class TStatusLine;

class IHttpResponse : public IHttpMessage
    {
public:
    virtual ~IHttpResponse() {}
    
    virtual void StatusLine(TStatusLine& aStatusLine) = 0;
    virtual void SetStatusLine(const TStatusLine& aStatusLine) = 0;
    
    //from IHttpMessage
    virtual TProtocolVersion Version() const = 0;
    virtual void AddHeader(const THeader& aHeader) = 0;
    virtual void RemoveHeader(const THeader& aHeader) = 0;

    };

} //namespace http
} //namespace net
} //namespace vctl


#endif /* defined(__vClientTemplateLib__http_core_response__) */
