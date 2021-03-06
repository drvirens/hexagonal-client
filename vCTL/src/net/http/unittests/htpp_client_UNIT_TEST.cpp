//
//  htpp_client.cpp
//  vClientTemplateLib
//
//  Created by Virendra Shakya on 5/16/14.
//  Copyright (c) 2014 Virendra Shakya. All rights reserved.
//

#include "3p/google/gtest/include/gtest/gtest.h"
#include "memory/ref/rc_thread_safe.h"
#include "net/http/async/http_future_callback.h"

#include "net/http/core/http_core_header.h"
#include "net/http/context/http_context.h"
#include "net/http/core/http_core_entity.h"
#include "net/http/config/http_config_request.h"
#include "net/http/core/http_core_protocol_version.h"
#include "net/http/detail/http_server.h"
#include "net/http/detail/http_server_builder.h"
#include "net/http/decorate/http_connection_reuse_strategy.h"
#include "net/http/htpp_client.h"
#include "net/http/detail/http_request_base.h"

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
    virtual std::string GetUrl() const
        {
        std::string url = "www.google.com";
        return url;
        }
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
    virtual void SetHttpEntity(IHttpEntity* aIHttpEntity) {}
        
    virtual void GetConfig(TRequestConfig& aTRequestConfig) const
        {
        TRequestConfig rconfig;
        aTRequestConfig = rconfig;
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
    virtual vctl::TStrongPointer<CHttpHeadersMap> GetAllHeaders() const
        {
        CHttpHeadersMap* headers = CHttpHeadersMap::New();
        return headers;
        }
    bool HasHeader(const std::string& aHeaderName) const
        {
        return false;
        }
private:
    CHttpHeadersMap* iHeaders;
    };

TEST(UT_THttpClient, Trivial)
    {
    IHttpClient* httpclient = new MyMockHttpClient();
    
    httpclient->Start();
    
    IHttpRequest* getrequest = new MyMockHttpRequest();
    THeader header;
    getrequest->AddHeader(header);
    
    MyHttpResponseHandler* myhttpresphandler = new MyHttpResponseHandler();
    
    CHttpContext* context = new CHttpContext();
    
    httpclient->Execute(context, getrequest, myhttpresphandler);
    
    EXPECT_EQ(myhttpresphandler->Status(), 200);
    
    httpclient->Stop();
    };
    
//
// mocked IConnectionReuseStrategy
//
class MyIConnectionReuseStrategy : public IConnectionReuseStrategy
    {
public:
    virtual bool KeepAlive(const IHttpResponse& aResponse, CHttpContext& aContext)
        {
        return true;
        }
    };
    
TEST(UT_THttpClient, CreateServerTrivial)
    {
    //every worker should create like below
    detail::THttpServerBuilder builder;
    IConnectionReuseStrategy* reusestrategy = new MyIConnectionReuseStrategy();
    builder.SetConnectionReuseStrategy(reusestrategy);
    vctl::TStrongPointer<detail::CHttpServer> server = builder.Build();
    
    EXPECT_TRUE(server.Get() != 0);
    
    MyHttpResponseHandler* myhttpresphandler = new MyHttpResponseHandler();
    CHttpContext* context = new CHttpContext();
    IHttpRequest* getrequest = new MyMockHttpRequest();
    server->Execute(getrequest, myhttpresphandler);
    }
    
// -----
class MyCHttpRequest : public CHttpRequestBase
    {
public:
    explicit MyCHttpRequest(const std::string& aUri)
        : CHttpRequestBase(aUri)
        {}
        
    virtual EHttpMethodType HttpMethod() const
        {
        return kHttpMethodGet;
        }
    };
    
TEST(UT_THttpClient, CurlTrivial)
    {
    detail::THttpServerBuilder builder;
    vctl::TStrongPointer<detail::CHttpServer> server = builder.Build();
    EXPECT_TRUE(server.Get() != 0);
    MyHttpResponseHandler* myhttpresphandler = new MyHttpResponseHandler();
    
    std::string url = "http://www.google.com";
    IHttpRequest* getrequest = new MyCHttpRequest(url);
    THeader header;
    getrequest->AddHeader(header);
    server->Execute(getrequest, myhttpresphandler);
    }
    
}
}
}

