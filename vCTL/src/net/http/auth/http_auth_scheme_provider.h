//
//  http_auth_scheme_provider.h
//  vClientTemplateLib
//
//  Created by Virendra Shakya on 5/20/14.
//  Copyright (c) 2014 Virendra Shakya. All rights reserved.
//

#ifndef vClientTemplateLib_http_auth_scheme_provider_h
#define vClientTemplateLib_http_auth_scheme_provider_h

#include "memory/ref/rc_thread_safe.h"
//#include "memory/smart_pointer/strong_pointer.h"

namespace vctl
{
namespace net
{
namespace http
{
class IAuthScheme;

class IAuthSchemeProvider : public vctl::CReferenceThreadSafe<IAuthSchemeProvider>
    {
public:
    virtual IAuthScheme* Create(IHttpContext& aContext) = 0;
    
protected:
    virtual ~IAuthSchemeProvider() {}
    friend class vctl::CReferenceThreadSafe<IAuthSchemeProvider>;
    };

} //namespace http
} //namespace net
} //namespace vctl



#endif
