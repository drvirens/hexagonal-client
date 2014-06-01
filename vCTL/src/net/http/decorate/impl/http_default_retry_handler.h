//
//  http_default_retry_handler.h
//  vClientTemplateLib
//
//  Created by Virendra Shakya on 5/30/14.
//  Copyright (c) 2014 Virendra Shakya. All rights reserved.
//

#ifndef __vClientTemplateLib__http_default_retry_handler__
#define __vClientTemplateLib__http_default_retry_handler__

#include "net/http/decorate/http_retry_handler.h"

namespace vctl
{
namespace net
{
namespace http
{

class CDefaultRetryHandler : public IRetryHandler
    //
    // This guy was written in Germany, Frankfurt airport :)
    //
    {
public:
    static CDefaultRetryHandler* New();
    virtual bool Retry(EHttpStatusCode aPreviousError, int aAttemptedRetries, IHttpContext& aContext);
    
protected:
    virtual ~CDefaultRetryHandler();
    CDefaultRetryHandler();
    void Construct();
    };

} //namespace http
} //namespace net
} //namespace vctl



#endif /* defined(__vClientTemplateLib__http_default_retry_handler__) */
