//
//  htpp_client.cpp
//  vClientTemplateLib
//
//  Created by Virendra Shakya on 5/16/14.
//  Copyright (c) 2014 Virendra Shakya. All rights reserved.
//

#include "3p/google/gtest/include/gtest/gtest.h"

#include "net/http/http_client_factory.h"
#include "net/http/http_method_get.h"
#include "net/http/core/http_core_header.h"

namespace vctl
{
namespace net
{
namespace http
{

TEST(UT_THttpClient, Trivial)
    {
    CHttpClient& httpclient = THttpClientsFactory::Instance().DefaultHttpClient();
    httpclient.Start();
    
    IHttpRequest* getrequest = new CHttpGet("http://www.google.com");
    THeader header; //("mimetype:image/png");
    getrequest->AddHeader(header);
    
    CFutureCallBack<IHttpResponse>* callback; // = new CLambdaMyCallbackRefCountedThreadSafe();
    httpclient.Execute(*getrequest, *callback);
    
    //get->Cancel();
    
    httpclient.Stop();
    };
    
}
}
}

