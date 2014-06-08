//
//  htpp_client_factory.cpp
//  vClientTemplateLib
//
//  Created by Virendra Shakya on 6/8/14.
//  Copyright (c) 2014 Virendra Shakya. All rights reserved.
//

#include "net/http/detail/http_client_impl.h"

namespace vctl
{
namespace net
{
namespace http
{

IHttpClient* THttpClientFactory::GetDefaultHttpClient()
    {
    IHttpClient* client = CHttpClientImpl::New();
    if( client )
        {
        }
    return client;
    }
    
} //namespace http
} //namespace net
} //namespace vctl


