//
//  http_curl_impl.h
//  vClientTemplateLib
//
//  Created by Virendra Shakya on 5/17/14.
//  Copyright (c) 2014 Virendra Shakya. All rights reserved.
//

#ifndef __vClientTemplateLib__http_curl_impl__
#define __vClientTemplateLib__http_curl_impl__

#include "curl/curl.h"
#include "base/thread/thread_un_safe.h"

namespace vctl
{
namespace net
{
namespace http
{
class IHttpRequest;
template <class T> class CFutureCallBack;
class IHttpResponse;

namespace curl
{

class THttpCurl : private vbase::TNotThreadSafe
    //
    // This is thread-unsafe class so use it on the same
    // thread where you are going to create it
    //
    {
public:
    void Execute();
        
    THttpCurl(IHttpRequest& aHttpRequest,
        CFutureCallBack<IHttpResponse>& aFutureCallBack);
    
    ~THttpCurl();
    
private:
    bool Construct();
    bool EasySetUp();
    bool EasySetupSSL();
    bool EasySetupTimeouts();
    void ResetCurl();
    bool SetupHttpHeaders(struct curl_slist*& aList);
    
    static size_t ResponseHeaderCB(void* aData, size_t aSizeInBytes,
        size_t aCount, void* aInstance);
    static size_t ResponseBodyCB  (void* aData, size_t aSizeInBytes,
        size_t aCount, void* aInstance);
        
private:
    CURL* iCurl;
    char iCurlErrorBuffer[CURL_ERROR_SIZE];
    IHttpRequest& iHttpRequest;
    CFutureCallBack<IHttpResponse>& iFutureCallBack;
    };

} //namespace curl

} //namespace http
} //namespace net
} //namespace vctl


#endif /* defined(__vClientTemplateLib__http_curl_impl__) */
