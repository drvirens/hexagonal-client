//
//  http_core_message.h
//  vClientTemplateLib
//
//  Created by Virendra Shakya on 5/16/14.
//  Copyright (c) 2014 Virendra Shakya. All rights reserved.
//

#ifndef __vClientTemplateLib__http_core_message__
#define __vClientTemplateLib__http_core_message__

#include "net/http/core/http_core_protocol_version.h"

namespace vctl
{
namespace net
{
namespace http
{

class THeader;

class IHttpMessage
    {
public:
    virtual ~IHttpMessage() {}
    
    virtual TProtocolVersion Version() const = 0;
    virtual void AddHeader(const THeader& aHeader) = 0;
    virtual void RemoveHeader(const THeader& aHeader) = 0;
    
    //virtual void GetAllHeaders(std::vector<THeader>*& aHeaders) const = 0;
    };

} //namespace http
} //namespace net
} //namespace vctl


#endif /* defined(__vClientTemplateLib__http_core_message__) */
