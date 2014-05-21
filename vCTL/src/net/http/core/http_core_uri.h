//
//  http_core_uri.h
//  vClientTemplateLib
//
//  Created by Virendra Shakya on 5/20/14.
//  Copyright (c) 2014 Virendra Shakya. All rights reserved.
//

#ifndef __vClientTemplateLib__http_core_uri__
#define __vClientTemplateLib__http_core_uri__

#include <string>

namespace vctl
{
namespace net
{
namespace http
{

class TUri
    {
public:
    TUri(std::string& aUri);
    
    const std::string& Uri() const { return iUri; }
    
private:
    std::string iUri;
    };

} //namespace http
} //namespace net
} //namespace vctl



#endif /* defined(__vClientTemplateLib__http_core_uri__) */
