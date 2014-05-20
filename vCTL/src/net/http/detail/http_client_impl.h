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

class CHttpClientImpl : public IHttpClient
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
    
void CHttpClientImpl::Start()
    {
    }
    
void CHttpClientImpl::Stop()
    {
    }
    
void CHttpClientImpl::DoExecute(CHttpContext* aHttpContext,
        IHttpRequest* aHttpRequest,
        IFutureCallBack* aFutureCallBack)
    {
    //transfer all the execution machinery on a different thread
    //get a thread from thread pool and execute on it
    //Post the lambda in threadworkerpool queue and signal the queue
    }

} //namespace http
} //namespace net
} //namespace vctl



#endif /* defined(__vClientTemplateLib__htpp_client_impl__) */
