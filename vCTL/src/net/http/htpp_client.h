//
//  htpp_client.h
//  vClientTemplateLib
//
//  Created by Virendra Shakya on 5/16/14.
//  Copyright (c) 2014 Virendra Shakya. All rights reserved.
//

#ifndef __vClientTemplateLib__htpp_client__
#define __vClientTemplateLib__htpp_client__

#include "net/http/core/http_core_request.h"
#include "net/http/core/http_core_response.h"
#include "net/http/async/http_future_callback.h"

namespace vctl
{
namespace net
{
namespace http
{

class CHttpContext;

class IHttpClient 
    {
public:
    virtual ~IHttpClient() {}
    virtual void Start() = 0;
    virtual void Stop() = 0;
    
    //
    //aHttpRequest: user allocates it AND transfers ownership of aHttpRequest to http-module
    //aFutureCallBack: user allocates it AND transfers ownership to http-module.
    //
    void Execute(CHttpContext* aHttpContext, //TODO: remove this. server will create it internally
        IHttpRequest* aHttpRequest,
        IFutureCallBack* aFutureCallBack)
        {
        DoExecute(aHttpContext, aHttpRequest, aFutureCallBack);
        }
        
protected:
    virtual void DoExecute(CHttpContext* aHttpContext,
        IHttpRequest* aHttpRequest,
        IFutureCallBack* aFutureCallBack) = 0;
     };
    

//
// class HttpClient factory
//
class THttpClientFactory
    {
public:
    static IHttpClient* GetDefaultHttpClient();
    };
    
} //namespace http
} //namespace net
} //namespace vctl

#endif /* defined(__vClientTemplateLib__htpp_client__) */
