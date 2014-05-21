//
//  http_service_unavailable_retry_strategy.h
//  vClientTemplateLib
//
//  Created by Virendra Shakya on 5/20/14.
//  Copyright (c) 2014 Virendra Shakya. All rights reserved.
//

#ifndef vClientTemplateLib_http_service_unavailable_retry_strategy_h
#define vClientTemplateLib_http_service_unavailable_retry_strategy_h

#include "base/thread/thread_un_safe.h"

namespace vctl
{
namespace net
{
namespace http
{
class IHttpContext;
class IHttpResponse;

class IServiceUnavailableRetryStrategy : private vbase::TNotThreadSafe
    {
public:
    virtual ~IServiceUnavailableRetryStrategy() {}
    virtual bool ShouldRetry(const IHttpResponse& aHttpResponse, int aAttemptedRetries, IHttpContext& aContext) = 0;
    virtual long RetryInterval() const = 0;
    };

} //namespace http
} //namespace net
} //namespace vctl


#endif
