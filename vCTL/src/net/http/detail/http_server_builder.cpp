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
#include "net/http/exec_chain/http_executor_boss.h"
#include "net/http/exec_chain/http_executor_hooks.h"

#include "net/http/hooks/impl/http_hooks_default.h"
#include "net/http/hooks/impl/http_hook_out_defaultheaders.h"
#include "net/http/decorate/impl/http_default_retry_handler.h"
#include "net/http/exec_chain/http_executor_retry.h"

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

THttpServerBuilder::~THttpServerBuilder()
    {
    LOG_INFO << "Destructor for THttpServerBuilder called";
    }

//THttpServerBuilder& THttpServerBuilder::SetHttpActualSenderReceiver(vctl::TStrongPointer<IHttpActualSenderReceiver> aIHttpActualSenderReceiver)
//    {
//    iIHttpActualSenderReceiver = aIHttpActualSenderReceiver;
//    return *this;
//    }
    
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
    
THttpServerBuilder& THttpServerBuilder::SetDefaultHttpHeaders(vctl::TStrongPointer<CHttpHeadersMap> aCHttpHeadersMap)
    {
    iCHttpHeadersMap = aCHttpHeadersMap;
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
    
    IHttpRequestExecutionChain* executorchain =
        CHttpRequestExecutorBoss::New(iIHttpActualSenderReceiver,
                                          iIConnectionReuseStrategy,
                                          iIConnectionKeepAliveStrategy,
                                          iIAuthenticationStrategy);

    if(!iIHttpHooks.Get())
        {
        iIHttpHooks = CDefaultHttpHooks::New();
        
        IHttpHookOutgoingPacket* defaultheaders = CHttpHookOutgoingDefaultHeaders::New(iCHttpHeadersMap);
        iIHttpHooks->Add(defaultheaders);
            
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
        //TODO: CHeck if chain is created correctly
    executorchain = CHooksExecutor::New(executorchain, iIHttpHooks);
    
    if(iGeneralHttpConfig.IsAutomaticRetriesEnabled())
        {
        if(!iIRetryHandler)
            {
            iIRetryHandler = CDefaultRetryHandler::New();
            }
        executorchain = CRetryExecutor::New(executorchain, iIRetryHandler);
        }
        
    if(iGeneralHttpConfig.IsRedirectEnabled())
        {
        //TODO: Enable redirection executor
        }
        
    if(iIServiceUnavailableRetryStrategy)
        {
        //TODO: Enable service unavailable executor
        }
    
    //TODO: backoff strategy
    
    //TODO: Create AuthSchemeProvider registry here
    if(!iIAuthSchemeProvider.Get())
        {
        LOG_INFO << "----> No AuthSceme Provider provided. this will not authorize any http requests ";
        }
    
    //TODO: create default ICredentialsProvider?
    if( !iICredentialsProvider )
        {
        }
    
    CHttpServer* server = CHttpServer::New(executorchain,
                                           iICredentialsProvider,
                                           iIAuthSchemeProvider
                                           );
    vctl::TStrongPointer<detail::CHttpServer> retserver;
    retserver = server;
    return retserver;
    }
 
} //namespace detail
} //namespace http
} //namespace net
} //namespace vctl

