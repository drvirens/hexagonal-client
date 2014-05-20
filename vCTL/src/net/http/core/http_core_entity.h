//
//  http_core_entity.h
//  vClientTemplateLib
//
//  Created by Virendra Shakya on 5/17/14.
//  Copyright (c) 2014 Virendra Shakya. All rights reserved.
//

#ifndef __vClientTemplateLib__http_core_entity__
#define __vClientTemplateLib__http_core_entity__

#include "net/http/core/http_core_header.h"
#include "memory/ref/rc_thread_safe.h"

namespace vctl
{
namespace net
{
namespace http
{

class IInputStream;
class IOutputStream;

/**
 * See: http://www.w3.org/Protocols/rfc2616/rfc2616-sec7.html
 * ALso: http://stackoverflow.com/questions/9197745/what-exactly-is-an-http-entity
 */

class IHttpEntity : public vctl::CReferenceThreadSafe<IHttpEntity>
    {
public:
    
    virtual bool IsRepeatable() const = 0;
    virtual bool IsChunked() const = 0;
    
    virtual long long ContentLength() const = 0;
    virtual THeader* ContentType() const = 0;
    virtual THeader* ContentEncoding() const = 0;
    virtual IInputStream* ReadContents() = 0;
    virtual void WriteContents(IOutputStream* aOutputStream) = 0;
    
    virtual bool IsStreaming() const = 0;
protected:
    virtual ~IHttpEntity() {}
    friend class vctl::CReferenceThreadSafe<IHttpEntity>;
    };

} //namespace http
} //namespace net
} //namespace vctl


#endif /* defined(__vClientTemplateLib__http_core_entity__) */
