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
#include "memory/ref/rc_thread_safe.h"
#include "net/http/config/http_config_request.h"

namespace vctl
{
namespace net
{
namespace http
{


class IHttpActualSenderReceiver;
class IConnectionReuseStrategy;
class IConnectionKeepAliveStrategy;
class IAuthenticationStrategy;
class IHttpHooks;
class IRetryHandler;
class IRedirectStrategy;
class IConnectionBackoffStrategy;
class IServiceUnavailableRetryStrategy;
class IAuthSchemeProvider;
class ICredentialsProvider;
class THttpHeadersMap;


namespace detail
{

class CHttpServer : public vctl::CReferenceThreadSafe<CHttpServer>
    {
public:
    static CHttpServer* New();
    
protected:
    CHttpServer();
    void Construct();
    virtual ~CHttpServer();
    friend class vctl::CReferenceThreadSafe<CHttpServer>;
    
private:
    IHttpActualSenderReceiver* iHttpActualSenderReceiver;
    
    IConnectionReuseStrategy* iConnReuseStrategy;
    IConnectionKeepAliveStrategy* iConnKeepAliveStrategy;
    IAuthenticationStrategy* iAuthStrategy;
    IHttpHooks* iHttpHooks; //class that contains both both in-hook and out-hook
    IRetryHandler* iRetryHandler;
    IRedirectStrategy* iRedirectStrategy;
    IConnectionBackoffStrategy* iBackoffStrategy;
    IServiceUnavailableRetryStrategy* iServiceUnavailableRetryStrategy;
    IAuthSchemeProvider* iAuthSchemeProvider;
    ICredentialsProvider* iCredentialsProvider;
    
    std::string iUserAgent;
    THttpHeadersMap* iDefaultHeaders;
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
