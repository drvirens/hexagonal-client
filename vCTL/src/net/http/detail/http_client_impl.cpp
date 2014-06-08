//
//  http_client_impl.cpp
//  vClientTemplateLib
//
//  Created by Virendra Shakya on 6/8/14.
//  Copyright (c) 2014 Virendra Shakya. All rights reserved.
//

#include "net/http/detail/http_client_impl.h"
#include "memory/ref/rc_thread_safe.h"
#include "net/http/detail/http_server.h"

namespace vctl
{
namespace net
{
namespace http
{

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
    
    vctl::TStrongPointer<detail::CHttpServer> server = iServerBuilder.Build();
    
    if( server.Get() == 0 )
        {
        LOG_ERROR << "error in creating server builder";
        return;
        }
        
    //MyHttpResponseHandler* myhttpresphandler = new MyHttpResponseHandler();
    
    std::string url = "http://www.google.com";
//    IHttpRequest* getrequest = new MyCHttpRequest(url);
//    THeader header;
//    aHttpRequest->AddHeader(header);
    server->Execute(aHttpRequest, aFutureCallBack);
    
    }
    
CHttpClientImpl* CHttpClientImpl::New()
    {
    CHttpClientImpl* obj = new CHttpClientImpl();
    if( obj )
        {
        obj->Construct();
        }
    return obj;
    }
    
CHttpClientImpl::~CHttpClientImpl()
    {
    }
    
CHttpClientImpl::CHttpClientImpl()
    {
    }
    
void CHttpClientImpl::Construct()
    {
    }
    

} //namespace http
} //namespace net
} //namespace vctl

