//
//  http_server_builder.cpp
//  vClientTemplateLib
//
//  Created by Virendra Shakya on 5/21/14.
//  Copyright (c) 2014 Virendra Shakya. All rights reserved.
//

#include "net/http/detail/http_server_builder.h"
#include "net/http/detail/http_server.h"

namespace vctl
{
namespace net
{
namespace http
{
namespace detail
{

THttpServerBuilder::THttpServerBuilder()
    {
    }

THttpServerBuilder& THttpServerBuilder::SetHttpActualSenderReceiver(vctl::TStrongPointer<IHttpActualSenderReceiver> aIHttpActualSenderReceiver)
    {
    return *this;
    }
    
THttpServerBuilder& THttpServerBuilder::SetConnectionReuseStrategy(vctl::TStrongPointer<IConnectionReuseStrategy> aIConnectionReuseStrategy)
    {
    return *this;
    }
    
THttpServerBuilder& THttpServerBuilder::SetConnectionKeepAliveStrategy(vctl::TStrongPointer<IConnectionKeepAliveStrategy> aIConnectionKeepAliveStrategy)
    {
    return *this;
    }
    
THttpServerBuilder& THttpServerBuilder::SetAuthenticationStrategy(vctl::TStrongPointer<IAuthenticationStrategy> aIAuthenticationStrategy)
    {
    return *this;
    }
    
THttpServerBuilder& THttpServerBuilder::SetHttpHooks(vctl::TStrongPointer<IHttpHooks> aIHttpHooks)
    {
    return *this;
    }
    
THttpServerBuilder& THttpServerBuilder::SetRetryHandler(vctl::TStrongPointer<IRetryHandler> aIRetryHandler)
    {
    return *this;
    }
    
THttpServerBuilder& THttpServerBuilder::SetRedirectStrategy(vctl::TStrongPointer<IRedirectStrategy> aIRedirectStrategy)
    {
    return *this;
    }
    
THttpServerBuilder& THttpServerBuilder::SetConnectionBackoffStrategy(vctl::TStrongPointer<IConnectionBackoffStrategy> aIConnectionBackoffStrategy)
    {
    return *this;
    }
    
THttpServerBuilder& THttpServerBuilder::SetServiceUnavailableRetryStrategy(vctl::TStrongPointer<IServiceUnavailableRetryStrategy> aIServiceUnavailableRetryStrategy)
    {
    return *this;
    }
    
THttpServerBuilder& THttpServerBuilder::SetAuthSchemeProvider(vctl::TStrongPointer<IAuthSchemeProvider> aIAuthSchemeProvider)
    {
    return *this;
    }
    
THttpServerBuilder& THttpServerBuilder::SetCredentialsProvider(vctl::TStrongPointer<ICredentialsProvider> aICredentialsProvider)
    {
    return *this;
    }
    
THttpServerBuilder& THttpServerBuilder::SetDefaultHttpHeaders(vctl::TStrongPointer<THttpHeadersMap> aTHttpHeadersMap)
    {
    return *this;
    }
    
vctl::TStrongPointer<CHttpServer> THttpServerBuilder::Build()
    {
    CHttpServer* server = CHttpServer::New();
    return server;
    }
 
} //namespace detail
} //namespace http
} //namespace net
} //namespace vctl

