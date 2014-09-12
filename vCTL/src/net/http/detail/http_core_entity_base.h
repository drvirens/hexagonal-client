//
//  http_core_entity_base.h
//  Discount
//
//  Created by Virendra Shakya on 6/9/14.
//  Copyright (c) 2014 Justin. All rights reserved.
//

#ifndef __Discount__http_core_entity_base__
#define __Discount__http_core_entity_base__

#include "net/http/core/http_core_entity.h"

namespace vctl
{
namespace net
{
namespace http
{

class CHttpEntityBase : public IHttpEntity
    {
protected:
    CHttpEntityBase() {}
    
    virtual bool IsChunked() const
        {
        return iIsChunked;
        }
    
    virtual THeader* ContentType() const
        {
        return &iContentType;
        }
        
    virtual THeader* ContentEncoding() const
        {
        return &iContentEncoding;
        }
    
    virtual long long ContentLength() const = 0;
    virtual bool IsRepeatable() const = 0;
    virtual IInputStream* ReadContents() = 0;
    virtual void WriteContents(IOutputStream* aOutputStream) = 0;
    virtual bool IsStreaming() const = 0;
    
protected:
    virtual ~CHttpEntityBase() {}
    
protected:
    mutable THeader iContentType;
    mutable THeader iContentEncoding;
    bool iIsChunked;
    
    static const int kOutputBufferSize = 4096;
    };

} //namespace http
} //namespace net
} //namespace vctl



#endif /* defined(__Discount__http_core_entity_base__) */
