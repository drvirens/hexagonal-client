//
//  log.cpp
//  vClientTemplateLib
//
//  Created by Virendra Shakya on 5/3/14.
//  Copyright (c) 2014 Virendra Shakya. All rights reserved.
//

#include <iostream>
#include <stdio.h>
#include <sys/time.h>

#include "logging/log_output.h"
#include "logging/log.h"
#include "build/build_utils.h"

namespace logging
{

static const int kPrettyTimeBufferSize = 15;

// ----------------------- TLogConfig class statics
ELogLevel TLogConfig::iLogLevel = eDebug;
std::vector<IOutput*> TLogConfig::iOutputs;

// ----------------------- TLogTimeStamp
class TLogTimeStamp
    {
public:
    TLogTimeStamp()
        {
    #if defined(_MSC_VER)
        _tzset();
    #endif
        }
    char* const PrettyTimeStamp();
    
private:
    char iBuffer[kPrettyTimeBufferSize];
    };
    
char* const TLogTimeStamp::PrettyTimeStamp()
    {
#if defined(_MSC_VER)
    _strtime_s(iBuffer, sizeof(iBuffer));
#else
    struct timeval tv;
    
    time_t timevalue = time(0);
    struct tm now;
    localtime_r(&timevalue, &now);
    
    gettimeofday(&tv, 0);
    
    int n = snprintf(iBuffer, sizeof(iBuffer), "%02d:%02d:%02d.%06d",
                        now.tm_hour, now.tm_min, now.tm_sec, tv.tv_usec);
    ASSERT(n == sizeof(iBuffer));
    iBuffer[n] = 0;
#endif
    return iBuffer;
    }
    


void TLogConfig::SetLevel(ELogLevel aLevel)
    {
    iLogLevel = aLevel;
    }

ELogLevel TLogConfig::GetLevel()
    {
    return iLogLevel;
    }

int TLogConfig::AddOutput(IOutput* aOutput)
    {
    iOutputs.push_back(aOutput);
    return 0;
    }

void TLogConfig::RemoveOutput(int aOutputId)
    {
    }

//

TLog::TLog(ELogLevel aLogLevel, const std::string& aFileName, int aLineNumber, const std::string& aFunctionName)
    : iLogLevel(aLogLevel)
    , iTimeStamp( "" )
    , iFileName(aFileName)
    , iLineNumber(aLineNumber)
    , iFunctionName(aFunctionName)
    {
    TLogTimeStamp timestamp;
    iTimeStamp = timestamp.PrettyTimeStamp();
    }
        
TLog::~TLog()
    {
    std::vector<IOutput*> v = TLogConfig::iOutputs;
    for( std::vector<IOutput*>::iterator it = v.begin(); it != v.end(); ++it)
        {
        IOutput* output = *it;
        output->Dump(iLogLevel, iTimeStamp, iFileName, iLineNumber, iFunctionName, iMessage.str());
        }
    }

// --------

} //namespace logging
