//
//  log_output.h
//  vClientTemplateLib
//
//  Created by Virendra Shakya on 5/3/14.
//  Copyright (c) 2014 Virendra Shakya. All rights reserved.
//

#ifndef __vClientTemplateLib__log_output__
#define __vClientTemplateLib__log_output__

#include <string>
#include "logging/log_level.h"

namespace logging
{

class IOutput
    {
public:
    virtual ~IOutput() {}
    virtual void Dump(ELogLevel aLogLevel,
                     const std::string& aTimeStamp,
                     const std::string& aFileName,
                     int aLineNumber,
                     const std::string& aFunctionName,
                     const std::string& aMessage) = 0;
    };
    
    
    

} //namespace logging

#endif /* defined(__vClientTemplateLib__log_output__) */
