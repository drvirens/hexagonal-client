//
//  http_server.cpp
//  vClientTemplateLib
//
//  Created by Virendra Shakya on 5/19/14.
//  Copyright (c) 2014 Virendra Shakya. All rights reserved.
//

#include "net/http/detail/http_server.h"
#include "net/http/context/http_context.h"

namespace vctl
{
namespace net
{
namespace http
{
namespace detail
{

void CHttpServer::Execute(
        IHttpRequest* aHttpRequest,
        IFutureCallBack* aFutureCallBack)
    {
    //TODO: if config is not setup, set it up for httprequest here
    //TRequestConfig config = aHttpRequest->GetConfig();
    CHttpContext* context = new CHttpContext();
    iIHttpRequestExecutionChain->ExecuteOrPassOn(context, aHttpRequest, aFutureCallBack);
    }

CHttpServer* CHttpServer::New()
    {
    CHttpServer* obj = new CHttpServer();
    if( obj )
        {
        obj->Construct();
        }
    return obj;
    }
    
CHttpServer* CHttpServer::New(IHttpRequestExecutionChain* aIHttpRequestExecutionChain,
                            ICredentialsProvider* aICredentialsProvider,
                            IAuthSchemeProvider* aIAuthSchemeProvider)
    {
    CHttpServer* obj = new CHttpServer(aIHttpRequestExecutionChain,
                                aICredentialsProvider,
                                aIAuthSchemeProvider);
    if( obj )
        {
        obj->Construct();
        }
    return obj;
    }
    
CHttpServer::CHttpServer()
    {
    }
    
CHttpServer::CHttpServer(IHttpRequestExecutionChain* aIHttpRequestExecutionChain,
                            ICredentialsProvider* aICredentialsProvider,
                            IAuthSchemeProvider* aIAuthSchemeProvider)
    : iIAuthSchemeProvider(aIAuthSchemeProvider)
    , iICredentialsProvider(aICredentialsProvider)
    , iIHttpRequestExecutionChain(aIHttpRequestExecutionChain)
    {
    }
    
void CHttpServer::Construct()
    {
    }
    
CHttpServer::~CHttpServer()
    {
    }


} //namespace detail
} //namespace http
} //namespace net
} //namespace vctl