//
//  http_server_builder.cpp
//  vClientTemplateLib
//
//  Created by Virendra Shakya on 5/21/14.
//  Copyright (c) 2014 Virendra Shakya. All rights reserved.
//

#include "net/http/detail/http_server_builder.h"
#include "net/http/detail/http_server.h"
#include "net/http/exec_chain/http_executor_interface.h"

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
    iIHttpActualSenderReceiver = aIHttpActualSenderReceiver;
    return *this;
    }
    
THttpServerBuilder& THttpServerBuilder::SetConnectionReuseStrategy(vctl::TStrongPointer<IConnectionReuseStrategy> aIConnectionReuseStrategy)
    {
    iIConnectionReuseStrategy = aIConnectionReuseStrategy;
    return *this;
    }
    
THttpServerBuilder& THttpServerBuilder::SetConnectionKeepAliveStrategy(vctl::TStrongPointer<IConnectionKeepAliveStrategy> aIConnectionKeepAliveStrategy)
    {
    iIConnectionKeepAliveStrategy = aIConnectionKeepAliveStrategy;
    return *this;
    }
    
THttpServerBuilder& THttpServerBuilder::SetAuthenticationStrategy(vctl::TStrongPointer<IAuthenticationStrategy> aIAuthenticationStrategy)
    {
    iIAuthenticationStrategy = aIAuthenticationStrategy;
    return *this;
    }
    
THttpServerBuilder& THttpServerBuilder::SetHttpHooks(vctl::TStrongPointer<IHttpHooks> aIHttpHooks)
    {
    iIHttpHooks = aIHttpHooks;
    return *this;
    }
    
THttpServerBuilder& THttpServerBuilder::SetRetryHandler(vctl::TStrongPointer<IRetryHandler> aIRetryHandler)
    {
    iIRetryHandler = aIRetryHandler;
    return *this;
    }
    
THttpServerBuilder& THttpServerBuilder::SetRedirectStrategy(vctl::TStrongPointer<IRedirectStrategy> aIRedirectStrategy)
    {
    iIRedirectStrategy = aIRedirectStrategy;
    return *this;
    }
    
THttpServerBuilder& THttpServerBuilder::SetConnectionBackoffStrategy(vctl::TStrongPointer<IConnectionBackoffStrategy> aIConnectionBackoffStrategy)
    {
    iIConnectionBackoffStrategy = aIConnectionBackoffStrategy;
    return *this;
    }
    
THttpServerBuilder& THttpServerBuilder::SetServiceUnavailableRetryStrategy(vctl::TStrongPointer<IServiceUnavailableRetryStrategy> aIServiceUnavailableRetryStrategy)
    {
    iIServiceUnavailableRetryStrategy = aIServiceUnavailableRetryStrategy;
    return *this;
    }
    
THttpServerBuilder& THttpServerBuilder::SetAuthSchemeProvider(vctl::TStrongPointer<IAuthSchemeProvider> aIAuthSchemeProvider)
    {
    iIAuthSchemeProvider = aIAuthSchemeProvider;
    return *this;
    }
    
THttpServerBuilder& THttpServerBuilder::SetCredentialsProvider(vctl::TStrongPointer<ICredentialsProvider> aICredentialsProvider)
    {
    iICredentialsProvider = aICredentialsProvider;
    return *this;
    }
    
THttpServerBuilder& THttpServerBuilder::SetDefaultHttpHeaders(vctl::TStrongPointer<THttpHeadersMap> aTHttpHeadersMap)
    {
    iTHttpHeadersMap = aTHttpHeadersMap;
    return *this;
    }
    
vctl::TStrongPointer<CHttpServer> THttpServerBuilder::Build()
    {
    if(!iIHttpActualSenderReceiver.Get())
        {
        iIHttpActualSenderReceiver = CCurlHttpActualSenderReceiver::New();
        }
        
    if(!iIConnectionReuseStrategy.Get())
        {
        if(iGeneralHttpConfig.IsKeepAliveEnabled())
            {
            iIConnectionReuseStrategy = CDefaultConnectionReuseStrategy::New();
            }
        else
            {
            iIConnectionReuseStrategy = CNopeConnectionReuseStrategy::New();
            }
        }
        
    if(!iIConnectionKeepAliveStrategy.Get())
        {
        iIConnectionKeepAliveStrategy = CDefaultConnectionKeepAliveStrategy::New();
        }
        
    if(!iIAuthenticationStrategy.Get())
        {
        if(iGeneralHttpConfig.IsAuthenticaionNeeded())
            {
            //todo: read auth details from config and create auth class accordingly
            //iIAuthenticationStrategy = CAuthenticationStrategy();
            }
        else
            {
            iIAuthenticationStrategy = CNopeAuthenticationStrategy::New();
            }
        }
    
    IHttpRequestExecutionChain* bossexecutor =
        CHttpRequestExecutorBoss::New(iIHttpActualSenderReceiver,
                                          iIConnectionReuseStrategy,
                                          iIConnectionKeepAliveStrategy,
                                          iIAuthenticationStrategy);

    if(!iIHttpHooks.Get())
        {
        iIHttpHooks = CDefaultHttpHooks::New();
        
        if(iTHttpHeadersMap.Get()) //we have some default headers hooks set by clients
            {
            iIHttpHooks->Add(iTHttpHeadersMap);
            }
            
        IHttpHookOutgoingPacket* content = CHttpHookOutgoingContent::New();
        iIHttpHooks->Add(content); //transfers ownership
        
        IHttpHookOutgoingPacket* targethost = CHttpHookOutgoingTargetHost::New();
        iIHttpHooks->Add(targethost);
        
        IHttpHookOutgoingPacket* useragent = CHttpHookOutgoingUserAgent::New();
        iIHttpHooks->Add(useragent);
        
        //todo:
        //accept-encoding
        //auth-cache
        }
        
        //create chaining based on Chain-of-responsibility
    CHooksExecutor* hooks = CHooksExecutor::New(bossexecutor);
    
    
    
    CHttpServer* server = CHttpServer::New();
    return server;
    }
 
} //namespace detail
} //namespace http
} //namespace net
} //namespace vctl

