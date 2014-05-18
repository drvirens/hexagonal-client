//
//  http_core_header_group.h
//  vClientTemplateLib
//
//  Created by Virendra Shakya on 5/17/14.
//  Copyright (c) 2014 Virendra Shakya. All rights reserved.
//

#ifndef __vClientTemplateLib__http_core_header_group__
#define __vClientTemplateLib__http_core_header_group__

#include "base/thread/thread_un_safe.h"

namespace vctl
{
namespace net
{
namespace http
{

class THeaderGroup : private vbase::TThreadUnSafe<THeaderGroup>
    {
public:
    };

} //namespace http
} //namespace net
} //namespace vctl

#endif /* defined(__vClientTemplateLib__http_core_header_group__) */
