//
//  http_curl_impl.cpp
//  vClientTemplateLib
//
//  Created by Virendra Shakya on 5/17/14.
//  Copyright (c) 2014 Virendra Shakya. All rights reserved.
//

#include "net/http/curl/http_curl_impl.h"
#include "net/http/core/http_core_request.h"
#include "net/http/config/http_config_request.h"
#include "logging/log_logger.h"

namespace vctl
{
namespace net
{
namespace http
{
namespace curl
{

THttpCurl::THttpCurl(IHttpRequest& aHttpRequest,
    CFutureCallBack<IHttpResponse>& aFutureCallBack)
    : iCurl(0)
    , iHttpRequest(aHttpRequest)
    , iFutureCallBack(aFutureCallBack)
    {
    iCurlErrorBuffer[0] = 0;
    Construct();
    }

bool THttpCurl::Construct()
    {
    if( iCurl )
        {
        return true;
        }
    
    bool r = EasySetUp();
    if( false == r )
        {
        curl_easy_cleanup(iCurl);
        iCurl = 0;
        }
    
    return true;
    }
    
void THttpCurl::Execute()
    {
    bool r = false;
    struct curl_slist* curlheaders = 0;
    
    r = SetupHttpHeaders(curlheaders);
    if(r)
        {
        CURLcode curlRet;
        curlRet = curl_easy_perform(iCurl);
        
        //do something with response
        }
        
    ResetCurl();
        
    if(curlheaders)
        {
        curl_slist_free_all(curlheaders);
        }
    
    }
    
bool THttpCurl::SetupHttpHeaders(struct curl_slist*& aList)
    {
    bool r = false;
    return r;
    }
    
void THttpCurl::ResetCurl()
    {
    curl_easy_setopt(iCurl, CURLOPT_HTTPGET, false);
    curl_easy_setopt(iCurl, CURLOPT_POST, false);
    curl_easy_setopt(iCurl, CURLOPT_PUT, false);
    curl_easy_setopt(iCurl, CURLOPT_UPLOAD, false);
    curl_easy_setopt(iCurl, CURLOPT_NOBODY, false);
    curl_easy_setopt(iCurl, CURLOPT_CUSTOMREQUEST, 0);
    curl_easy_setopt(iCurl, CURLOPT_POSTFIELDSIZE, -1);
    curl_easy_setopt(iCurl, CURLOPT_READFUNCTION, 0);
    curl_easy_setopt(iCurl, CURLOPT_HTTPHEADER, 0);
    curl_easy_setopt(iCurl, CURLOPT_TIMEOUT_MS, 0L);
    }
    
bool THttpCurl::EasySetUp()
    {
    bool r = true;
    CURLcode curlRet;
    
    iCurl = curl_easy_init();
    if( !iCurl )
        {
        r = false;
        return r;
        }
        
    curlRet = curl_easy_setopt(iCurl, CURLOPT_HEADERFUNCTION, &THttpCurl::ResponseHeaderCB);
    r = r && !curlRet;
    
    curlRet = curl_easy_setopt(iCurl, CURLOPT_WRITEHEADER, this);
    r = r && !curlRet;
    
    curlRet = curl_easy_setopt(iCurl, CURLOPT_WRITEFUNCTION, &THttpCurl::ResponseBodyCB);
    r = r && !curlRet;
    
    curlRet = curl_easy_setopt(iCurl, CURLOPT_WRITEDATA, this);
    r = r && !curlRet;
    
    //read-function will be set on-demand
    curlRet = curl_easy_setopt(iCurl, CURLOPT_READDATA, this);
    r = r && !curlRet;
    
    curlRet = curl_easy_setopt(iCurl, CURLOPT_ERRORBUFFER, iCurlErrorBuffer);
    r = r && !curlRet;
    if(false == r)
        {
        LOG_ERROR << "Basic setup error for CURL so return";
        return r;
        }
        
    r = EasySetupSSL();
    if(false == r)
        {
        LOG_ERROR << "SSL setup error for CURL so return";
        return r;
        }

    curlRet = curl_easy_setopt(iCurl, CURLOPT_NOSIGNAL, 1L);
    r = r && !curlRet;
    
    r = EasySetupTimeouts();
    if(false == r)
        {
        LOG_ERROR << "Timeout setup error for CURL so return";
        }
    
    return r;
    }
    
bool THttpCurl::EasySetupSSL()
    {
    bool r = true;
    CURLcode curlRet;
    
    TRequestConfig& requestconfig = iHttpRequest.GetConfig();
    if(requestconfig.IsSSLVerificationDisabled())
        {
        curl_easy_setopt(iCurl, CURLOPT_SSL_VERIFYPEER, false);
        }
    else
        {
        std::string cacertspath = requestconfig.CertificatesPath();
        if(cacertspath.empty())
            {
            r = false;
            LOG_ERROR << "SSL verification is enabled but Certification path is empty";
            return r;
            }
        
        curlRet = curl_easy_setopt(iCurl, CURLOPT_CAINFO, cacertspath.c_str());
        if( !curlRet )
            {
            r = false;
            LOG_ERROR << "SSL error in setting ca certs path from " << cacertspath;
            return r;
            }
        }
    return r;
    }
    
bool THttpCurl::EasySetupTimeouts()
    {
    bool r = true;
    CURLcode curlRet;
    
    TRequestConfig& requestconfig = iHttpRequest.GetConfig();
    
    long connecttimeout = requestconfig.ConnectTimeout();
    long dnscachetimeout = requestconfig.DnsCacheTimeout();
    long maxredirects = requestconfig.MaxRedirects();
    long followlocation = requestconfig.FollowLocation();
    
    
    curlRet = curl_easy_setopt(iCurl, CURLOPT_CONNECTTIMEOUT, connecttimeout);
    r = r && !curlRet;

    curlRet = curl_easy_setopt(iCurl, CURLOPT_DNS_CACHE_TIMEOUT, dnscachetimeout);
    r = r && !curlRet;

    curlRet = curl_easy_setopt(iCurl, CURLOPT_MAXREDIRS, maxredirects);
    r = r && !curlRet;

    curlRet = curl_easy_setopt(iCurl, CURLOPT_FOLLOWLOCATION, followlocation);
    r = r && !curlRet;

    return r;
    }
    
size_t THttpCurl::ResponseHeaderCB(void* aData, size_t aSizeInBytes, size_t aCount, void* aInstance)
    {
    size_t ret = 0;
    return ret;
    }
    
size_t THttpCurl::ResponseBodyCB(void* aData, size_t aSizeInBytes, size_t aCount, void* aInstance)
    {
    size_t ret = 0;
    return ret;
    }

THttpCurl::~THttpCurl()
    {
    if( iCurl )
        {
        curl_easy_cleanup(iCurl);
        }
    }


} //namespace curl
} //namespace http
} //namespace net
} //namespace vctl



