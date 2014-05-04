//
//  log_output.cpp
//  vClientTemplateLib
//
//  Created by Virendra Shakya on 5/3/14.
//  Copyright (c) 2014 Virendra Shakya. All rights reserved.
//

#include <iostream>

#include "logging/log_output.h"


namespace logging
{
// -----------------------

void ISimpleBlockingOutput::Dump(ELogLevel aLogLevel,
                     const std::string& aTimeStamp,
                     const std::string& aFileName,
                     int aLineNumber,
                     const std::string& aFunctionName,
                     const std::string& aMessage)
    {
    if(aLogLevel > iLogLevel)
        {
        return;
        }
        
#if defined(THREADSAFE_LOGGING)
    vbase::TAutoLock guard(iLock);
#endif
    
    std::ostream& out = OutputTo();
    
    switch (aLogLevel)
        {
        case eDebug:
            {
            out << "DEBUG";
            } break;
        case eInfo:
            {
            out << "INFO";
            } break;
        case eWarning:
            {
            out << "WARNING";
            } break;
        case eFatal:
            {
            out << "FATAL";
            } break;
        default:
            {
            out << "ERROR";
            } break;
        } //switch
     
    //timestamp
    out << "[" << aTimeStamp << "]";
    
    out << " : " << aFileName << ":" << aLineNumber << ":"
        << aFunctionName << "() = "
        << aMessage << "\n";
    }
    
    
std::ostream& CConsoleOutput::OutputTo()
    {
    return std::cout;
    }

} //namespace logging
