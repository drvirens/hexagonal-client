//
//  htpp_client.cpp
//  vClientTemplateLib
//
//  Created by Virendra Shakya on 5/16/14.
//  Copyright (c) 2014 Virendra Shakya. All rights reserved.
//

#include "3p/google/gtest/include/gtest/gtest.h"

#include "net/http/http_client_factory.h"
#include "net/http/http_method_get.h"
#include "net/http/core/http_core_header.h"
#include "net/http/context/http_context.h"
#include "memory/ref/rc_thread_safe.h"

namespace vctl
{
namespace net
{
namespace http
{

class MyHttpResponseObject : public vctl::CReferenceThreadSafe<MyHttpResponseObject>
    {
public:
    void ProcessResponse()
        {
        }
private:
    ~MyHttpResponseObject()
        {
        }
        
    friend class vctl::CReferenceThreadSafe<MyHttpResponseObject>;
    };

template <class HTTP_RESPONSE>
class MyHttpResponseHandler : public IFutureCallBack<HTTP_RESPONSE>
    {
public:
    virtual void Failed(int aError)
        {
        }
        //aResponse ownership is transferred to us
    virtual void Succeeded(vctl::TStrongPointer<HTTP_RESPONSE> aResponse)
        {
        //do something with response and then delete it (by setting NULL)
        aResponse->ProcessResponse();
        aResponse = NULL; //deleted
        }
        
    virtual void Cancelled()
        {
        }
    
    };
    


TEST(UT_THttpClient, Trivial)
    {
    TStrongPointer<IHttpClient <MyHttpResponseObject> > httpclient = 0;
    THttpClientsFactory factory = THttpClientsFactory::Instance();
    
    httpclient = factory.DefaultHttpClient<MyHttpResponseHandler<MyHttpResponseObject> >();
    
    httpclient->Start();
    
    IHttpRequest* getrequest; // = new CHttpGet("http://www.google.com");
    THeader header; //("mimetype:image/png");
    getrequest->AddHeader(header);
    
    IFutureCallBack< MyHttpResponseObject >* callback = 0;
    callback = new MyHttpResponseHandler<MyHttpResponseObject>();
    
    //IFutureCallBack<MyHttpResponseObject> cb;
    CHttpContext* context = new CHttpContext();
    
    httpclient->Execute(context, getrequest, callback);
    //&cb);
    //get->Cancel();
    
    httpclient->Stop();
     
    };
    
}
}
}

