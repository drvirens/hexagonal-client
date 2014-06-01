//
//  http_server.cpp
//  vClientTemplateLib
//
//  Created by Virendra Shakya on 5/19/14.
//  Copyright (c) 2014 Virendra Shakya. All rights reserved.
//

#include "http_server.h"

namespace vctl
{
namespace net
{
namespace http
{
namespace detail
{

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