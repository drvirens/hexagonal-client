//
//  http_redirect_strategy.h
//  vClientTemplateLib
//
//  Created by Virendra Shakya on 5/20/14.
//  Copyright (c) 2014 Virendra Shakya. All rights reserved.
//

#ifndef vClientTemplateLib_http_redirect_strategy_h
#define vClientTemplateLib_http_redirect_strategy_h

#include "memory/ref/rc_thread_safe.h"

namespace vctl
{
namespace net
{
namespace http
{
class IHttpContext;
class IHttpResponse;

class IRedirectStrategy : public vctl::CReferenceThreadSafe<IRedirectStrategy>
    {
public:
    virtual bool CanRedirect(IHttpResponse& aResponse,
                            IHttpRequest& aRequest,
                            IHttpContext& aContext) = 0;
        
    virtual bool RedirectTo(IHttpResponse& aResponse,
                            IHttpRequest& aRequest,
                            IHttpContext& aContext,
                            IHttpRequest*& aRedirectTo) = 0;
        
protected:
    virtual ~IRedirectStrategy() {}
    friend class vctl::CReferenceThreadSafe<IRedirectStrategy>;
    };

} //namespace http
} //namespace net
} //namespace vctl



#endif
