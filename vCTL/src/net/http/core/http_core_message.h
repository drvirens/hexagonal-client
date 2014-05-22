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
//#include "memory/smart_pointer/strong_pointer.h"
#include "memory/ref/rc_thread_safe.h"

namespace vctl
{
namespace net
{
namespace http
{

class THeader;
class THttpHeadersMap;

class IHttpMessage : public vctl::CReferenceThreadSafe<IHttpMessage>
    {
public:
    virtual TProtocolVersion Version() const = 0;
    virtual void AddHeader(const THeader& aHeader) = 0;
    virtual void RemoveHeader(const THeader& aHeader) = 0;
    virtual bool HasHeader(const std::string& aHeaderName) const = 0;
    virtual THttpHeadersMap* GetAllHeaders() const = 0;
    
protected:
    virtual ~IHttpMessage() {}
    friend class vctl::CReferenceThreadSafe<IHttpMessage>;
    };

} //namespace http
} //namespace net
} //namespace vctl


#endif /* defined(__vClientTemplateLib__http_core_message__) */
