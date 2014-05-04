//
//  log.cpp
//  vClientTemplateLib
//
//  Created by Virendra Shakya on 5/3/14.
//  Copyright (c) 2014 Virendra Shakya. All rights reserved.
//

#include <iostream>
#include "logging/log_output.h"
#include "logging/log.h"

namespace logging
{

ELogLevel TLogConfig::iLogLevel = eDebug;
std::vector<IOutput*> TLogConfig::iOutputs;

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
TLog::~TLog()
    {
    std::vector<IOutput*> v = TLogConfig::iOutputs;
    for( std::vector<IOutput*>::iterator it = v.begin(); it != v.end(); ++it)
        {
        IOutput* output = *it;
        output->Dump(iLogLevel, iTimeStamp, iFileName, iLineNumber, iFunctionName, iMessage.str());
        }
    }


} //namespace logging
