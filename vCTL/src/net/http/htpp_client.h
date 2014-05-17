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

namespace vctl
{
namespace net
{
namespace http
{

template <class T>
class IHttpClient
    {
public:
    void Start()
        {
        T* thiz = static_cast<T*>(this);
        thiz->Start();
        }
        
    void Stop()
        {
        T* thiz = static_cast<T*>(this);
        thiz->Stop();
        }
    
    void Execute(const IHttpRequest& aHttpRequest,
            CFutureCallBack<IHttpResponse>& aFutureCallBack)
        {
        T* thiz = static_cast<T*>(this);
        thiz->Execute(aHttpRequest, aFutureCallBack);
        }
    };

} //namespace http
} //namespace net
} //namespace vctl

#endif /* defined(__vClientTemplateLib__htpp_client__) */
