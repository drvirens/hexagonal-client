//
//  http_actual_CURL.cpp
//  vClientTemplateLib
//
//  Created by Virendra Shakya on 5/26/14.
//  Copyright (c) 2014 Virendra Shakya. All rights reserved.
//

#include "net/http/decorate/impl/http_actual_CURL.h"
#include "net/http/core/http_core_response.h"
#include "net/http/core/http_core_request.h"
#include "net/http/config/http_config_request.h"
#include "curl/curl.h"

namespace vctl
{
namespace net
{
namespace http
{
namespace detail
{

class TCurlExecutor
    {
public:
    IHttpResponse* Send(IHttpRequest* aHttpRequest);
    ~TCurlExecutor();
    
private:
    int PrepareCurlRequest(IHttpRequest* aHttpRequest, struct curl_slist** aCurlList);
    int InitCurl(bool aDisableSsl);
    int InitCurlOptions(bool aDisableSsl);
    
    static size_t CurlHeaderCallback(void* aData, size_t aSize, size_t aNmemb, void* aInstance);
    static size_t CurlBodyCallback(void* aData, size_t aSize, size_t aNmemb, void* aInstance);
    
private:
    char iCurlErrorBuffer[CURL_ERROR_SIZE];
    CURL* iCurl;
    };

IHttpResponse* TCurlExecutor::Send(IHttpRequest* aHttpRequest)
    {
    IHttpResponse* response = 0;
    iCurlErrorBuffer[0] = 0;
    
    struct curl_slist* curlheaders = 0;
    PrepareCurlRequest(aHttpRequest, &curlheaders);
    
    return response;
    }
    
int TCurlExecutor::PrepareCurlRequest(IHttpRequest* aHttpRequest, struct curl_slist** aCurlList)
    {
    TRequestConfig config;
    aHttpRequest->GetConfig(config);
    
    bool ssldisabled = config.IsSSLVerificationDisabled();
    
    int ret = InitCurl(ssldisabled);
    if( !ret )
        {
        return ret;
        }
        
    CHttpHeadersMap* headers = aHttpRequest->GetAllHeaders();
    if( !headers )
        {
        return 1; //error
        }
        
    int headerssize = headers->Size();
    for(int i = 0; i < headerssize; i++)
        {
        THeader h = headers->GetHeader(i);
        *aCurlList = curl_slist_append(*aCurlList, h.Describe());
        }
    
    return ret;
    }
    
int TCurlExecutor::InitCurl(bool aDisableSsl)
    {
    int e = 1;
    if( iCurl ) //already initialised
        {
        e = 0; //success
        return e;
        }
    iCurl = curl_easy_init();
    if( !iCurl )
        {
        return e;
        }
    e = InitCurlOptions(aDisableSsl);
    if( !e )
        {
        curl_easy_cleanup(iCurl);
        iCurl = 0;
        return e;
        }
    e = 0;
    return e;
    }
    
int TCurlExecutor::InitCurlOptions(bool aDisableSsl)
    {
    int e = 0; //success
    int curlerr;
    
    curlerr = curl_easy_setopt( iCurl, CURLOPT_HEADERFUNCTION, CurlHeaderCallback);
    e = e && !curlerr;
    
    curlerr = curl_easy_setopt( iCurl, CURLOPT_WRITEHEADER, this);
    e = e && !curlerr;
    
    curlerr = curl_easy_setopt( iCurl, CURLOPT_WRITEFUNCTION, CurlBodyCallback);
    e = e && !curlerr;
    
    curlerr = curl_easy_setopt( iCurl, CURLOPT_WRITEDATA, this);
    e = e && !curlerr;
    
    curlerr = curl_easy_setopt( iCurl, CURLOPT_READDATA, this);
    e = e && !curlerr;
    
    curlerr = curl_easy_setopt( iCurl, CURLOPT_ERRORBUFFER, iCurlErrorBuffer);
    e = e && !curlerr;
    
    if(!e)
        {
        return 1; //error
        }
    
    if(aDisableSsl)
        {
        curlerr = curl_easy_setopt( iCurl, CURLOPT_SSL_VERIFYPEER, false);
        }
    else
        {
        //curl_easy_setopt(curl_, CURLOPT_CAINFO, cacerts_path.c_str());
        }
    
    //TODO: read all timeouts from config
    curlerr = curl_easy_setopt( iCurl, CURLOPT_NOSIGNAL, 1L);
    e = e && !curlerr;
    
    curlerr = curl_easy_setopt( iCurl, CURLOPT_CONNECTTIMEOUT, 10L);
    e = e && !curlerr;
    
    curlerr = curl_easy_setopt( iCurl, CURLOPT_DNS_CACHE_TIMEOUT, 60L);
    e = e && !curlerr;
    
    curlerr = curl_easy_setopt( iCurl, CURLOPT_FOLLOWLOCATION, 1);
    e = e && !curlerr;
    
    curlerr = curl_easy_setopt( iCurl, CURLOPT_MAXREDIRS, 5);
    e = e && !curlerr;
    
    curlerr = curl_easy_setopt( iCurl, CURLOPT_FOLLOWLOCATION, 0);
    e = e && !curlerr;

    return e;
    }
    
size_t TCurlExecutor::CurlHeaderCallback(void* aData, size_t aSize, size_t aNmemb, void* aInstance)
    {
    return 0;
    }
    
// ------------------------

void CCurlHttpActualSenderReceiver::DoSend(CHttpContext* aHttpContext,
        IHttpRequest* aHttpRequest)
    {
    LOG_INFO << "CCurlHttpActualSenderReceiver::DoSend";
    
    TCurlExecutor curl;
    IHttpResponse* response = curl.Send(aHttpRequest);
    }
    
void CCurlHttpActualSenderReceiver::DoReceive()
    {
    }
    
void CCurlHttpActualSenderReceiver::Execute()
    {
    }
    
void CCurlHttpActualSenderReceiver::PreProcess()
    {
    }
    
void CCurlHttpActualSenderReceiver::PostProcess()
    {
    }
    
CCurlHttpActualSenderReceiver::~CCurlHttpActualSenderReceiver()
    {
    }
    
void CCurlHttpActualSenderReceiver::Construct()
    {
    }
    
CCurlHttpActualSenderReceiver::CCurlHttpActualSenderReceiver()
    {
    }
    
CCurlHttpActualSenderReceiver* CCurlHttpActualSenderReceiver::New()
    {
    CCurlHttpActualSenderReceiver* obj = new CCurlHttpActualSenderReceiver();
    if( obj )
        {
        obj->Construct();
        }
    return obj;
    }
    
    

} //namespace detail
} //namespace http
} //namespace net
} //namespace vctl
