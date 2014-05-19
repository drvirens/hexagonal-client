//
//  htpp_client_curl.h
//  vClientTemplateLib
//
//  Created by Virendra Shakya on 5/16/14.
//  Copyright (c) 2014 Virendra Shakya. All rights reserved.
//

#ifndef __vClientTemplateLib__htpp_client_curl__
#define __vClientTemplateLib__htpp_client_curl__


#include "net/http/htpp_client.h"

namespace vctl
{
namespace net
{
namespace http
{

template <class HTTP_RESPONSE>
class CHttpClientCURL : public IHttpClient<HTTP_RESPONSE>
    {
protected:
    virtual void Start()
        {
        }
        
    virtual void Stop()
        {
        }
        
private:
    virtual void Execute(vctl::TStrongPointer<CHttpContext> aHttpContext,
        vctl::TStrongPointer<IHttpRequest> aHttpRequest,
        vctl::TStrongPointer< IFutureCallBack< HTTP_RESPONSE > > aFutureCallBack)
        {
        //hookup with THttpCurl
        }
    };

} //namespace http
} //namespace net
} //namespace vctl


#endif /* defined(__vClientTemplateLib__htpp_client_curl__) */
