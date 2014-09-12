//
//  http_connection_reuse_strategy_default.h
//  vClientTemplateLib
//
//  Created by Virendra Shakya on 5/27/14.
//  Copyright (c) 2014 Virendra Shakya. All rights reserved.
//

#ifndef __vClientTemplateLib__http_connection_reuse_strategy_default__
#define __vClientTemplateLib__http_connection_reuse_strategy_default__

#include "net/http/decorate/http_connection_reuse_strategy.h"

namespace vctl
{
namespace net
{
namespace http
{

class CDefaultConnectionReuseStrategy : public IConnectionReuseStrategy
    {
public:
    static CDefaultConnectionReuseStrategy* New();
    virtual bool KeepAlive(const IHttpResponse& aResponse, CHttpContext& aContext);
    
protected:
    virtual ~CDefaultConnectionReuseStrategy();
    CDefaultConnectionReuseStrategy();
    void Construct();
    };

} //namespace http
} //namespace net
} //namespace vctl


#endif /* defined(__vClientTemplateLib__http_connection_reuse_strategy_default__) */
