//
//  htpp_client_default.h
//  vClientTemplateLib
//
//  Created by Virendra Shakya on 5/16/14.
//  Copyright (c) 2014 Virendra Shakya. All rights reserved.
//

#ifndef __vClientTemplateLib__htpp_client_default__
#define __vClientTemplateLib__htpp_client_default__

#include "net/http/htpp_client.h"
#include "net/http/curl/htpp_client_curl.h"
#include "memory/ref/rc_thread_safe.h"

namespace vctl
{
namespace net
{
namespace http
{

class CHttpClient : public CReferenceThreadSafe<CHttpClient>
    {
public:
    void Start()
        {
        iHttpClient.Start();
        }
        
    void Stop()
        {
        iHttpClient.Stop();
        }
    
    void Execute(const IHttpRequest& aHttpRequest,
            CFutureCallBack<IHttpResponse>& aFutureCallBack)
        {
        }

private:
    IHttpClient<CHttpClientCURL> iHttpClient;
    };

} //namespace http
} //namespace net
} //namespace vctl


#endif /* defined(__vClientTemplateLib__htpp_client_default__) */
