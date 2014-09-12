//
//  http_connection_keep_alive_strategy.h
//  vClientTemplateLib
//
//  Created by Virendra Shakya on 5/29/14.
//  Copyright (c) 2014 Virendra Shakya. All rights reserved.
//

#ifndef __vClientTemplateLib__http_connection_keep_alive_strategy__
#define __vClientTemplateLib__http_connection_keep_alive_strategy__


#include "memory/ref/rc_thread_safe.h"

namespace vctl
{
namespace net
{
namespace http
{

class IHttpResponse;
class CHttpContext;

class IConnectionKeepAliveStrategy : public vctl::CReferenceThreadSafe<IConnectionKeepAliveStrategy>
    {
public:
    virtual long GetKeepAliveDuration(const IHttpResponse& aResponse, CHttpContext& aContext) = 0;
    
protected:
    virtual ~IConnectionKeepAliveStrategy() {}
    friend class vctl::CReferenceThreadSafe<IConnectionKeepAliveStrategy>;
    };

} //namespace http
} //namespace net
} //namespace vctl


#endif /* defined(__vClientTemplateLib__http_connection_keep_alive_strategy__) */
