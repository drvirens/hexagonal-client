//
//  http_retry_handler.h
//  vClientTemplateLib
//
//  Created by Virendra Shakya on 5/20/14.
//  Copyright (c) 2014 Virendra Shakya. All rights reserved.
//

#ifndef vClientTemplateLib_http_retry_handler_h
#define vClientTemplateLib_http_retry_handler_h

#include "memory/ref/rc_thread_safe.h"
#include "net/http/core/http_core_status.h"

namespace vctl
{
namespace net
{
namespace http
{
class IHttpContext;

class IRetryHandler : public vctl::CReferenceThreadSafe<IRetryHandler>
    {
public:
    virtual bool Retry(EHttpStatusCode aPreviousError, int aAttemptedRetries, IHttpContext& aContext) = 0;
    
protected:
    virtual ~IRetryHandler() {}
    friend class vctl::CReferenceThreadSafe<IRetryHandler>;
    };

} //namespace http
} //namespace net
} //namespace vctl



#endif
