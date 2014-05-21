//
//  http_credentials.h
//  vClientTemplateLib
//
//  Created by Virendra Shakya on 5/21/14.
//  Copyright (c) 2014 Virendra Shakya. All rights reserved.
//

#ifndef vClientTemplateLib_http_credentials_h
#define vClientTemplateLib_http_credentials_h

#include <string>
#include "base/thread/thread_un_safe.h"

namespace vctl
{
namespace net
{
namespace http
{

typedef std::string CryptoString;

class ICredentials //: private vbase::TNotThreadSafe
    {
public:
    //we received this response...should we backoff?
    //touch the res
    virtual const std::string& UserName() const = 0;
    virtual const CryptoString& Password() const = 0;
    };

} //namespace http
} //namespace net
} //namespace vctl


#endif
