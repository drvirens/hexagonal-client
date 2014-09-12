//
//  http_default_connection_keep_alive_strategy.h
//  vClientTemplateLib
//
//  Created by Virendra Shakya on 5/29/14.
//  Copyright (c) 2014 Virendra Shakya. All rights reserved.
//

#ifndef __vClientTemplateLib__http_default_connection_keep_alive_strategy__
#define __vClientTemplateLib__http_default_connection_keep_alive_strategy__

#include "net/http/decorate/http_connection_keep_alive_strategy.h"

namespace vctl
{
namespace net
{
namespace http
{

class CDefaultConnectionKeepAliveStrategy : public IConnectionKeepAliveStrategy
    {
public:
    static CDefaultConnectionKeepAliveStrategy* New();
    virtual long GetKeepAliveDuration(const IHttpResponse& aResponse, CHttpContext& aContext);
    
protected:
    virtual ~CDefaultConnectionKeepAliveStrategy();
    CDefaultConnectionKeepAliveStrategy();
    void Construct();
    };

} //namespace http
} //namespace net
} //namespace vctl



#endif /* defined(__vClientTemplateLib__http_default_connection_keep_alive_strategy__) */
