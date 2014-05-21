//
//  http_credentials_provider.h
//  vClientTemplateLib
//
//  Created by Virendra Shakya on 5/21/14.
//  Copyright (c) 2014 Virendra Shakya. All rights reserved.
//

#ifndef vClientTemplateLib_http_credentials_provider_h
#define vClientTemplateLib_http_credentials_provider_h

#include "base/thread/thread_un_safe.h"

namespace vctl
{
namespace net
{
namespace http
{

class TAuthScope;
class ICredentials;

class ICredentialsProvider : private vbase::TNotThreadSafe
    {
public:
    //we received this response...should we backoff?
    //touch the res
    virtual void SetCredentials(const TAuthScope& aAuthScope, const ICredentials& aCredentials) = 0;
    virtual const ICredentials& Credentials(const TAuthScope& aAuthScope) const = 0;
    virtual void Clear() = 0;
    };

} //namespace http
} //namespace net
} //namespace vctl



#endif
