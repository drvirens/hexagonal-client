//
//  http_core_entity_inputstream.h
//  Discount
//
//  Created by Virendra Shakya on 6/9/14.
//  Copyright (c) 2014 Justin. All rights reserved.
//

#ifndef __Discount__http_core_entity_inputstream__
#define __Discount__http_core_entity_inputstream__

#include "net/http/detail/http_core_entity_base.h"

namespace vctl
{
namespace net
{
namespace http
{

class CHttpEntityInputStream : public CHttpEntityBase
    {
public:
    static CHttpEntityInputStream* New(IInputStream* aInputStream, long long aLen);
    
    virtual long long ContentLength() const;
    virtual bool IsRepeatable() const;
    virtual IInputStream* ReadContents();
    virtual void WriteContents(IOutputStream* aOutputStream);
    virtual bool IsStreaming() const;
protected:
    virtual ~CHttpEntityInputStream();
    CHttpEntityInputStream(IInputStream* aInputStream, long long aLen);
    void Construct(IInputStream* aInputStream, long long aLen);
protected:
    IInputStream* iContent;
    long long iContentLength;
    };

} //namespace http
} //namespace net
} //namespace vctl

#endif /* defined(__Discount__http_core_entity_inputstream__) */
