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

class CHttpClientCURL : public IHttpClient<CHttpClientCURL>
    {
public:
    void Start();
    void Stop();
    void Execute(IHttpRequest& aHttpRequest,
            CFutureCallBack<IHttpResponse>& aFutureCallBack);

private:
    
    };

} //namespace http
} //namespace net
} //namespace vctl


#endif /* defined(__vClientTemplateLib__htpp_client_curl__) */
