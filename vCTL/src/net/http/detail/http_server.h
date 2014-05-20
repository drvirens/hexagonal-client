//
//  http_server.h
//  vClientTemplateLib
//
//  Created by Virendra Shakya on 5/19/14.
//  Copyright (c) 2014 Virendra Shakya. All rights reserved.
//

#ifndef __vClientTemplateLib__http_server__
#define __vClientTemplateLib__http_server__

#include <string>
#include "base/thread/thread_un_safe.h"

namespace vctl
{
namespace net
{
namespace http
{
namespace detail
{

class IHttpActualSenderReceiver;

class CHttpServer : private vbase::TNotThreadSafe
    //
    //this guy executes entirely on given single thread
    //
    {
public:
    
private:
    IHttpActualSenderReceiver* iHttp;
    IConnectionReuseStrategy* iConnReuseStrategy;
    IConnectionKeepAliveStrategy* iConnKeepAliveStrategy;
    IAuthenticationStrategy* iAuthStrategy;
    IHttpHooks* iHttpHooks; //class that contains both both in-hook and out-hook
    IRetryHandler* iRetryHandler;
    IRedirectStrategy* iRedirectStrategy;
    IBackoffStrategy* iBackoffStrategy;
    IServiceUnavailableRetryStrategy* iServiceUnavailableRetryStrategy;
    IAuthSchemeProvider* iAuthSchemeProvider;
    ICredentialsProvider* iCredentialsProvider;
    
    std::string iUserAgent;
    THeadersMap* iDefaultHeaders;
    TRequestConfig iRequestConfig;
    
    bool iIsRedirectHandlingDisabled;
    bool iIsAutoRetryDisabled;
    bool iIsContentCompressionDisabled;
    bool iIsCookieDisabled;
    bool iIsAuthCachingDisabled;
    };

} //namespace detail
} //namespace http
} //namespace net
} //namespace vctl



#endif /* defined(__vClientTemplateLib__http_server__) */
