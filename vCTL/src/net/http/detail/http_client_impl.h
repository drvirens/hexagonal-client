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

namespace vctl
{
namespace net
{
namespace http
{

template <class HTTP_RESPONSE>
class CHttpClientImpl : public IHttpClient<HTTP_RESPONSE>
    {
protected:
    virtual void Start();
    virtual void Stop();
    
private:
    virtual void DoExecute(CHttpContext* aHttpContext,
        IHttpRequest* aHttpRequest,
        IFutureCallBack* aFutureCallBack);
        
private:
    
    };
    
void CHttpClientImpl<HTTP_RESPONSE>::Start()
    {
    }
    
void CHttpClientImpl<HTTP_RESPONSE>::Stop()
    {
    }
    
void CHttpClientImpl<HTTP_RESPONSE>::DoExecute(CHttpContext* aHttpContext,
        IHttpRequest* aHttpRequest,
        IFutureCallBack* aFutureCallBack)
    {
    //transfer all the execution machinery on a different thread
    //get a thread from thread pool and execute on it
    
    }

} //namespace http
} //namespace net
} //namespace vctl



#endif /* defined(__vClientTemplateLib__htpp_client_impl__) */
