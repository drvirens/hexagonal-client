//
//  htpp_client.h
//  vClientTemplateLib
//
//  Created by Virendra Shakya on 5/16/14.
//  Copyright (c) 2014 Virendra Shakya. All rights reserved.
//

#ifndef __vClientTemplateLib__htpp_client__
#define __vClientTemplateLib__htpp_client__

#include "net/http/http_method_get.h"
#include "net/http/core/http_core_request.h"
#include "net/http/core/http_core_response.h"
#include "net/http/async/http_future_callback.h"
#include "memory/smart_pointer/strong_pointer.h"

namespace vctl
{
namespace net
{
namespace http
{

class CHttpContext;

template <class HTTP_RESPONSE>
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
    virtual void Execute(vctl::TStrongPointer<CHttpContext> aHttpContext,
        vctl::TStrongPointer<IHttpRequest> aHttpRequest,
        vctl::TStrongPointer< IFutureCallBack< HTTP_RESPONSE > > aFutureCallBack) = 0;
     };


} //namespace http
} //namespace net
} //namespace vctl

#endif /* defined(__vClientTemplateLib__htpp_client__) */
