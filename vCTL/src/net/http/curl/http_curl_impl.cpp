//
//  http_curl_impl.cpp
//  vClientTemplateLib
//
//  Created by Virendra Shakya on 5/17/14.
//  Copyright (c) 2014 Virendra Shakya. All rights reserved.
//

#include "net/http/curl/http_curl_impl.h"
#include "net/http/core/http_core_request.h"
#include "logging/log_logger.h"

namespace vctl
{
namespace net
{
namespace http
{
namespace curl
{

void THttpCurl::Execute(const IHttpRequest& aHttpRequest,
    CFutureCallBack<IHttpResponse>& aFutureCallBack)
    {
    }

THttpCurl::THttpCurl()
    : iCurl(0)
    {
    }

bool THttpCurl::Construct()
    {
    if( iCurl )
        {
        //already initialized
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
    
bool THttpCurl::EasySetUp()
    {
    bool r = true;
    iCurl = curl_easy_init();
    if( !iCurl )
        {
        r = false;
        return r;
        }
        
    CURLcode curlRet = curl_easy_setopt(iCurl, CURLOPT_HEADERFUNCTION, &THttpCurl::ResponseHeaderCB);
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



