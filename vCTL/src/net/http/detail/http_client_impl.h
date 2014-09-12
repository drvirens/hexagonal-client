//
//  htpp_client_impl.h
//  vClientTemplateLib
//
//  Created by Virendra Shakya on 5/19/14.
//  Copyright (c) 2014 Virendra Shakya. All rights reserved.
//

#ifndef __vClientTemplateLib__htpp_client_impl__
#define __vClientTemplateLib__htpp_client_impl__

#include "net/http/htpp_client.h"
#include "net/http/detail/http_server_builder.h"

namespace vctl
{
namespace net
{
namespace http
{

class CHttpClientImpl : public IHttpClient
    {
public:
    static CHttpClientImpl* New();
    virtual ~CHttpClientImpl();
protected:
    
    virtual void Start();
    virtual void Stop();
    
private:
    virtual void DoExecute(CHttpContext* aHttpContext,
        IHttpRequest* aHttpRequest,
        IFutureCallBack* aFutureCallBack);
        
    CHttpClientImpl();
    void Construct();
        
private:
    detail::THttpServerBuilder iServerBuilder;
    };


} //namespace http
} //namespace net
} //namespace vctl



#endif /* defined(__vClientTemplateLib__htpp_client_impl__) */
