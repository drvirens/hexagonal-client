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
    TLog(ELogLevel aLogLevel, const std::string& aFileName, int aLineNumber, const std::string& aFunctionName);
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
