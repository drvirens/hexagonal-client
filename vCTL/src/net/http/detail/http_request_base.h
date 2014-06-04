//
//  http_request_base.h
//  vClientTemplateLib
//
//  Created by Virendra Shakya on 6/4/14.
//  Copyright (c) 2014 Virendra Shakya. All rights reserved.
//

#ifndef __vClientTemplateLib__http_request_base__
#define __vClientTemplateLib__http_request_base__


#include <string>
#include "base/synchronize/lock.h"
#include "net/http/core/http_core_request.h"
#include "memory/smart_pointer/strong_pointer.h"

namespace vctl
{
namespace net
{
namespace http
{

class CHttpRequestBase : public IHttpRequest
    {
public:
    virtual ~CHttpRequestBase();
    explicit CHttpRequestBase(const std::string& aUri);
    
    virtual void Cancel();
    virtual bool IsCancelled() const;
    virtual EHttpMethodType HttpMethod() const = 0;
    virtual IHttpEntity* HttpEntity() const;
    
    virtual void GetConfig(TRequestConfig& aTRequestConfig) const;
    
    //from IHttpMessage
    virtual TProtocolVersion Version() const;
    virtual void AddHeader(const THeader& aHeader);
    virtual void RemoveHeader(const THeader& aHeader);
    virtual vctl::TStrongPointer<CHttpHeadersMap> GetAllHeaders() const;

private:
    TProtocolVersion iProtocolVersion;
    bool iIsCancelledTag;
    
    vbase::TLock iLock; //protects access to iHttpHeadersMap
    vctl::TStrongPointer<CHttpHeadersMap> iHttpHeadersMap;
    };

} //namespace http
} //namespace net
} //namespace vctl

#endif /* defined(__vClientTemplateLib__http_request_base__) */
