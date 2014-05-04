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
#include <vector>

#include "logging/log_level.h"

//replacement for old logging system: we need our own logging system

namespace logging
{

//#define ENABLE_LOGGING 1
//
//#define GET_FILE_NAME__ (strrchr(__FILE__, '/') ? strrchr(__FILE__, '/') + 1 : __FILE__)
//
//#if defined ENABLE_LOGGING
//
//    #define LOG( level )  \
//                            if ( (logging::level) <= (logging::TLogConfig::GetLevel()) ) \
//                                logging::TLog(logging::level, GET_FILE_NAME__, __LINE__, __func__).GetLogMetadata()
//#else
//    #define LOG( level )  std::cerr << std::endl
//#endif

// -------------------------- forward
class IOutput;
class TLog;

// --------------------------- Global config
class TLogConfig
    {
friend class TLog;

public:
    static void SetLevel(ELogLevel aLevel);
    static ELogLevel GetLevel();
    static int AddOutput(IOutput* aOutput);
    static void RemoveOutput(int aOutputId);

private:
    static ELogLevel iLogLevel;
    static std::vector<IOutput*> iOutputs;
    };

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
