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
#include "memory/ref/rc_thread_safe.h"

namespace vctl
{
namespace net
{
namespace http
{

typedef std::string CryptoString;

class ICredentials : public vctl::CReferenceThreadSafe<ICredentials>
    {
public:
    virtual const std::string& UserName() const = 0;
    virtual const CryptoString& Password() const = 0;
    
protected:
    virtual ~ICredentials() {}
    friend class vctl::CReferenceThreadSafe<ICredentials>;
    };

} //namespace http
} //namespace net
} //namespace vctl


#endif
