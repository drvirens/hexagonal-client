//
//  http_client_factory.cpp
//  vClientTemplateLib
//
//  Created by Virendra Shakya on 5/16/14.
//  Copyright (c) 2014 Virendra Shakya. All rights reserved.
//

#include "net/http/http_client_builder.h"


namespace vctl
{
namespace net
{
namespace http
{

THttpClientBuilder& THttpClientBuilder::Instance()
    {
    }
    
IHttpClient* THttpClientBuilder::DefaultHttpClient()
    {
    //return CHttpClientImpl
    }

} //namespace http
} //namespace net
} //namespace vctl
