//
//  log_UT.cpp
//  vClientTemplateLib
//
//  Created by Virendra Shakya on 5/4/14.
//  Copyright (c) 2014 Virendra Shakya. All rights reserved.
//

#include "3p/google/gtest/include/gtest/gtest.h"
#include "logging/log.h"
#include "logging/log_output.h"
#include "logging/log_logger.h"

namespace logging
{

TEST(UT_Logger, Trivial)
    {
    //TLogConfig::SetLevel(logging::eDebug);
    logging::TLogConfig::AddOutput(new logging::CConsoleOutput(logging::eDebug));
    
    LOG(eDebug) << "test";
    
    LOG_INFO << "plain test";
    }

} //namespace logging
