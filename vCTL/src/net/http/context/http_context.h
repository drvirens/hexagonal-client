//
//  http_context.h
//  vClientTemplateLib
//
//  Created by Virendra Shakya on 5/18/14.
//  Copyright (c) 2014 Virendra Shakya. All rights reserved.
//

#ifndef __vClientTemplateLib__http_context__
#define __vClientTemplateLib__http_context__

#include "memory/ref/rc_thread_safe.h"

namespace vctl
{
namespace net
{
namespace http
{

class CHttpContext : public vctl::CReferenceThreadSafe<CHttpContext>
    {
protected:
    virtual ~CHttpContext() {} //purposefully private so others cant delete it accidentally
    
    friend class vctl::CReferenceThreadSafe<CHttpContext>; //allow it to delete us
    };

} //namespace http
} //namespace net
} //namespace vctl


#endif /* defined(__vClientTemplateLib__http_context__) */
