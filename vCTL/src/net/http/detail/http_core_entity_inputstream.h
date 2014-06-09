//
//  http_core_entity_inputstream.h
//  Discount
//
//  Created by Virendra Shakya on 6/9/14.
//  Copyright (c) 2014 Justin. All rights reserved.
//

#ifndef __Discount__http_core_entity_inputstream__
#define __Discount__http_core_entity_inputstream__


#include "net/http/core/http_core_entity.h"

namespace vctl
{
namespace net
{
namespace http
{

class CHttpEntityInputStream : public CHttpEntityBase
    {
protected:
    CHttpEntityInputStream() {}
    
    virtual long long ContentLength() const = 0;
    virtual bool IsRepeatable() const = 0;
    virtual IInputStream* ReadContents() = 0;
    virtual void WriteContents(IOutputStream* aOutputStream) = 0;
    virtual bool IsStreaming() const = 0;
    
protected:
    virtual ~CHttpEntityInputStream() {}
    
protected:
    };

} //namespace http
} //namespace net
} //namespace vctl

#endif /* defined(__Discount__http_core_entity_inputstream__) */
