//
//  http_connection_reuse_strategy_nope.h
//  vClientTemplateLib
//
//  Created by Virendra Shakya on 5/27/14.
//  Copyright (c) 2014 Virendra Shakya. All rights reserved.
//

#ifndef __vClientTemplateLib__http_connection_reuse_strategy_nope__
#define __vClientTemplateLib__http_connection_reuse_strategy_nope__


#include "net/http/decorate/http_connection_reuse_strategy.h"

namespace vctl
{
namespace net
{
namespace http
{

class CNopeConnectionReuseStrategy : public IConnectionReuseStrategy
    {
public:
    static CNopeConnectionReuseStrategy* New();
    virtual bool KeepAlive(const IHttpResponse& aResponse, CHttpContext& aContext);
    
protected:
    virtual ~CNopeConnectionReuseStrategy();
    CNopeConnectionReuseStrategy();
    void Construct();
    };

} //namespace http
} //namespace net
} //namespace vctl


#endif /* defined(__vClientTemplateLib__http_connection_reuse_strategy_nope__) */
