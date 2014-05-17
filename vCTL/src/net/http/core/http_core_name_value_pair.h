//
//  http_core_name_value_pair.h
//  vClientTemplateLib
//
//  Created by Virendra Shakya on 5/16/14.
//  Copyright (c) 2014 Virendra Shakya. All rights reserved.
//

#ifndef __vClientTemplateLib__http_core_name_value_pair__
#define __vClientTemplateLib__http_core_name_value_pair__

#include <string>

namespace vctl
{
namespace net
{
namespace http
{

class TNameValuePair
    {
public:
    TNameValuePair(std::string& aName, std::string& aValue);
    const std::string& Name() const;
    const std::string& Value() const;
    
private:
    std::string iName;
    std::string iValue;
    };

} //namespace http
} //namespace net
} //namespace vctl


#endif /* defined(__vClientTemplateLib__http_core_name_value_pair__) */
