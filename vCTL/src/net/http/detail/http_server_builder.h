//
//  http_server_builder.h
//  vClientTemplateLib
//
//  Created by Virendra Shakya on 5/21/14.
//  Copyright (c) 2014 Virendra Shakya. All rights reserved.
//

#ifndef __vClientTemplateLib__http_server_builder__
#define __vClientTemplateLib__http_server_builder__

#include "base/thread/thread_un_safe.h"
#include "memory/smart_pointer/strong_pointer.h"

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

class CHttpServer;

class THttpServerBuilder : private vbase::TNotThreadSafe
    {
public:
    THttpServerBuilder();
    
    THttpServerBuilder& SetHttpActualSenderReceiver(vctl::TStrongPointer<IHttpActualSenderReceiver> aIHttpActualSenderReceiver);
    THttpServerBuilder& SetConnectionReuseStrategy(vctl::TStrongPointer<IConnectionReuseStrategy> aIConnectionReuseStrategy);
    THttpServerBuilder& SetConnectionKeepAliveStrategy(vctl::TStrongPointer<IConnectionKeepAliveStrategy> aIConnectionKeepAliveStrategy);
    THttpServerBuilder& SetAuthenticationStrategy(vctl::TStrongPointer<IAuthenticationStrategy> aIAuthenticationStrategy);
    THttpServerBuilder& SetHttpHooks(vctl::TStrongPointer<IHttpHooks> aIHttpHooks);
    THttpServerBuilder& SetRetryHandler(vctl::TStrongPointer<IRetryHandler> aIRetryHandler);
    THttpServerBuilder& SetRedirectStrategy(vctl::TStrongPointer<IRedirectStrategy> aIRedirectStrategy);
    THttpServerBuilder& SetConnectionBackoffStrategy(vctl::TStrongPointer<IConnectionBackoffStrategy> aIConnectionBackoffStrategy);
    THttpServerBuilder& SetServiceUnavailableRetryStrategy(vctl::TStrongPointer<IServiceUnavailableRetryStrategy> aIServiceUnavailableRetryStrategy);
    THttpServerBuilder& SetAuthSchemeProvider(vctl::TStrongPointer<IAuthSchemeProvider> aIAuthSchemeProvider);
    THttpServerBuilder& SetCredentialsProvider(vctl::TStrongPointer<ICredentialsProvider> aICredentialsProvider);
    THttpServerBuilder& SetDefaultHttpHeaders(vctl::TStrongPointer<THttpHeadersMap> aTHttpHeadersMap);
    
    vctl::TStrongPointer<CHttpServer> Build();
    
protected:
    };

} //namespace detail
} //namespace http
} //namespace net
} //namespace vctl

#endif /* defined(__vClientTemplateLib__http_server_builder__) */
