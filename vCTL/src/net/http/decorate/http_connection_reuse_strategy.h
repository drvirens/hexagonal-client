//
//  http_connection_reuse_strategy.h
//  vClientTemplateLib
//
//  Created by Virendra Shakya on 5/20/14.
//  Copyright (c) 2014 Virendra Shakya. All rights reserved.
//

#ifndef __vClientTemplateLib__http_connection_reuse_strategy__
#define __vClientTemplateLib__http_connection_reuse_strategy__

#include "base/thread/thread_un_safe.h"

namespace vctl
{
namespace net
{
namespace http
{

class IHttpResponse;

class IConnectionReuseStrategy : private vbase::TNotThreadSafe
    {
public:
    virtual ~IConnectionReuseStrategy() {}
    
    virtual bool KeepAlive(const IHttpResponse& aResponse, const CHttpContext& aContext) = 0;
    };

} //namespace http
} //namespace net
} //namespace vctl


#endif /* defined(__vClientTemplateLib__http_connection_reuse_strategy__) */
