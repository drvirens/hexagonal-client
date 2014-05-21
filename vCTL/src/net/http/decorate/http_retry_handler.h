//
//  http_retry_handler.h
//  vClientTemplateLib
//
//  Created by Virendra Shakya on 5/20/14.
//  Copyright (c) 2014 Virendra Shakya. All rights reserved.
//

#ifndef vClientTemplateLib_http_retry_handler_h
#define vClientTemplateLib_http_retry_handler_h

#include "base/thread/thread_un_safe.h"

namespace vctl
{
namespace net
{
namespace http
{
class IHttpContext;

class IRetryHandler : private vbase::TNotThreadSafe
    {
public:
    virtual ~IRetryHandler() {}
    virtual bool Retry(EHttpStatusCode aPreviousError, int aAttemptedRetries, IHttpContext& aContext) = 0;
    };

} //namespace http
} //namespace net
} //namespace vctl



#endif
