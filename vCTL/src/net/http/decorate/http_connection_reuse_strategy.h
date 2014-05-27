//
//  http_connection_reuse_strategy.h
//  vClientTemplateLib
//
//  Created by Virendra Shakya on 5/20/14.
//  Copyright (c) 2014 Virendra Shakya. All rights reserved.
//

#ifndef __vClientTemplateLib__http_connection_reuse_strategy__
#define __vClientTemplateLib__http_connection_reuse_strategy__

#include "memory/ref/rc_thread_safe.h"

namespace vctl
{
namespace net
{
namespace http
{

class IHttpResponse;
class CHttpContext;

class IConnectionReuseStrategy : public vctl::CReferenceThreadSafe<IConnectionReuseStrategy>
    {
public:
    virtual bool KeepAlive(const IHttpResponse& aResponse, CHttpContext& aContext) = 0;
    
protected:
    virtual ~IConnectionReuseStrategy() {}
    friend class vctl::CReferenceThreadSafe<IConnectionReuseStrategy>;
    };

} //namespace http
} //namespace net
} //namespace vctl


#endif /* defined(__vClientTemplateLib__http_connection_reuse_strategy__) */
