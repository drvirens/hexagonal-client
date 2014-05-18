//
//  htpp_client_curl.cpp
//  vClientTemplateLib
//
//  Created by Virendra Shakya on 5/16/14.
//  Copyright (c) 2014 Virendra Shakya. All rights reserved.
//

#include "net/http/curl/http_client_curl.h"
#include "net/http/curl/http_curl_impl.h"

namespace vctl
{
namespace net
{
namespace http
{

void CHttpClientCURL::Start()
    {
    }
    
void CHttpClientCURL::Stop()
    {
    }
    
void CHttpClientCURL::Execute(IHttpRequest& aHttpRequest,
        CFutureCallBack<IHttpResponse>& aFutureCallBack)
    {
    //todo: put this on a threadpool to execute
    curl::THttpCurl curl(aHttpRequest, aFutureCallBack);
    curl.Execute();
    }
    

} //namespace http
} //namespace net
} //namespace vctl
