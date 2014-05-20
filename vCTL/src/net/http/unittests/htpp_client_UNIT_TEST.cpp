//
//  htpp_client.cpp
//  vClientTemplateLib
//
//  Created by Virendra Shakya on 5/16/14.
//  Copyright (c) 2014 Virendra Shakya. All rights reserved.
//

#include "3p/google/gtest/include/gtest/gtest.h"

#include "memory/ref/rc_thread_safe.h"

#include "net/http/http_client_factory.h"
#include "net/http/http_method_get.h"
#include "net/http/core/http_core_header.h"
#include "net/http/context/http_context.h"
#include "net/http/core/http_core_entity.h"
#include "net/http/config/http_config_request.h"
#include "net/http/core/http_core_protocol_version.h"

namespace vctl
{
namespace net
{
namespace http
{

class MyHttpResponseObject //: public vctl::CReferenceThreadSafe<MyHttpResponseObject>
    {
public:
    void ProcessResponse()
        {
        }
//private:
    ~MyHttpResponseObject()
        {
        }
        
    //friend class vctl::CReferenceThreadSafe<MyHttpResponseObject>;
    };

class MyHttpResponseHandler : public IFutureCallBack
    {
public:
    MyHttpResponseHandler() : iMyHttpStatus(0)
        {}
        
    virtual void Failed(int aError)
        {
        }
        //aResponse ownership is transferred to us
    virtual void Succeeded(IHttpResponse* aResponse)
        {
        iMyHttpStatus = 200;
        //do something with response and then delete it (by setting NULL)
//        aResponse->ProcessResponse();
        aResponse = NULL; //deleted
        }
        
    virtual void Cancelled()
        {
        }
    
    int Status() const { return iMyHttpStatus; }
        
private:
    int iMyHttpStatus;
    };
    
// Mock http-client
class MyMockHttpClient : public IHttpClient
    {
public:
    virtual ~MyMockHttpClient() {}
    virtual void Start()
        {
        }
    virtual void Stop()
        {
        }
     virtual void DoExecute(CHttpContext* aHttpContext,
        IHttpRequest* aHttpRequest,
        IFutureCallBack* aFutureCallBack)
        {
        }
     };
    
//mock httpentity
class MyMockIHttpEntity : public IHttpEntity
    {
public:
    virtual bool IsRepeatable() const
        {
        return false;
        }
    virtual bool IsChunked() const
        {
        return false;
        }
    
    virtual long long ContentLength() const
        {
        return 0;
        }
    virtual THeader* ContentType() const
        {
        return 0;
        }
    virtual THeader* ContentEncoding() const
        {
        return 0;
        }
    virtual IInputStream* ReadContents()
        {
        return 0;
        }
    virtual void WriteContents(IOutputStream* aOutputStream)
        {
        }
    
    virtual bool IsStreaming() const
        {
        return false;
        }
protected:
    virtual ~MyMockIHttpEntity() {}
    };


//mock IHttpRequest
class MyMockHttpRequest : public IHttpRequest
    {
public:
    virtual ~MyMockHttpRequest() {}
    
    virtual void Cancel()
        {
        }
    virtual bool IsCancelled() const
        {
        return false;
        }
    virtual EHttpMethodType HttpMethod() const
        {
        return kHttpMethodGet;
        }
    virtual IHttpEntity* HttpEntity() const
        {
        return new MyMockIHttpEntity();
        }
        
    virtual TRequestConfig& GetConfig() const
        {
        TRequestConfig rconfig;
        return rconfig;
        }
    virtual TProtocolVersion Version() const
        {
        std::string protoname = "http";
        TProtocolVersion v(protoname, 1, 1);
        return v;
        }
    virtual void AddHeader(const THeader& aHeader)
        {
        }
    virtual void RemoveHeader(const THeader& aHeader)
        {
        }
    virtual THttpHeadersMap* GetAllHeaders() const
        {
        return 0;
        }
    };

TEST(UT_THttpClient, Trivial)
    {
    
    IHttpClient* httpclient = new MyMockHttpClient();
    
//    THttpClientsFactory factory = THttpClientsFactory::Instance();    
//    httpclient = factory.DefaultHttpClient<MyHttpResponseObject>();
    
    httpclient->Start();
    
    IHttpRequest* getrequest = new MyMockHttpRequest();
    THeader header; //("mimetype:image/png");
    getrequest->AddHeader(header);
    
//    IFutureCallBack< MyHttpResponseObject >* callback = 0;
//    callback = new MyHttpResponseHandler<MyHttpResponseObject>();
    
    //IFutureCallBack<MyHttpResponseObject> cb;
    
    MyHttpResponseHandler* myhttpresphandler = new MyHttpResponseHandler();
    
    CHttpContext* context = new CHttpContext();
    
    httpclient->Execute(context, getrequest, myhttpresphandler);
    
    //get->Cancel();
    
    EXPECT_EQ(myhttpresphandler->Status(), 200);
    
    httpclient->Stop();
     
    };
    
}
}
}

