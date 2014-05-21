//
//  http_backoff_strategy.h
//  vClientTemplateLib
//
//  Created by Virendra Shakya on 5/20/14.
//  Copyright (c) 2014 Virendra Shakya. All rights reserved.
//

#ifndef __vClientTemplateLib__http_backoff_strategy__
#define __vClientTemplateLib__http_backoff_strategy__

#include "base/thread/thread_un_safe.h"

namespace vctl
{
namespace net
{
namespace http
{

class IHttpResponse;

class IConnectionBackoffStrategy : private vbase::TNotThreadSafe
    {
public:
    virtual ~IConnectionBackoffStrategy() {}
    
    //we received this response...should we backoff?
    //touch the res
    virtual bool ShouldBackOff(const IHttpResponse& aResponse) = 0;
    };

} //namespace http
} //namespace net
} //namespace vctl

#endif /* defined(__vClientTemplateLib__http_backoff_strategy__) */
