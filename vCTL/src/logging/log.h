//
//  log.h
//  vClientTemplateLib
//
//  Created by Virendra Shakya on 5/3/14.
//  Copyright (c) 2014 Virendra Shakya. All rights reserved.
//

#ifndef __vClientTemplateLib__log__
#define __vClientTemplateLib__log__

#include <string>
#include <sstream>
#include "logging/log_level.h"

//replacement for old logging system: we need our own logging system

namespace logging
{

#define ENABLE_LOGGING 1

#if defined ENABLE_LOGGING

    #define LOG( level )  \
                            if ( (logging::level) <= (logging::CurrentLevel()) ) \
                                { \
                                logging::TLog log(logging::level, __FILENAME__, __LINE__, __func__); \
                                log.GetLogMetadata(); \
                                }
    
#else
    #define LOG( level )  std::cerr << std::endl
#endif

// -------------------------- forward
class IOutput;

// --------------------------- Global config
void SetLevel(ELogLevel aLevel);
ELogLevel GetLevel();
int AddOutput(IOutput* aOutput);
void RemoveOutput(int aOutputId);

// --------------------------- TLog
class TLog
    {
public:
    TLog(ELogLevel aLogLevel, const std::string& aFileName, int aLineNumber, const std::string& aFunctionName)
        : iLogLevel(aLogLevel)
        , iTimeStamp( "" )
        , iFileName(aFileName)
        , iLineNumber(aLineNumber)
        , iFunctionName(aFunctionName)
        {}
        
    ~TLog();
    std::ostringstream& GetLogMetadata() { return iMessage; }
    
private:
    ELogLevel iLogLevel;
    std::string iTimeStamp;
    const std::string iFileName;
    int iLineNumber;
    const std::string iFunctionName;
    
    std::ostringstream iMessage;
    };
    

} //namespace logging

#endif /* defined(__vClientTemplateLib__log__) */
