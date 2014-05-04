//
//  log_logger.h
//  vClientTemplateLib
//
//  Created by Virendra Shakya on 5/4/14.
//  Copyright (c) 2014 Virendra Shakya. All rights reserved.
//

#ifndef vClientTemplateLib_log_logger_h
#define vClientTemplateLib_log_logger_h

#include "logging/log.h"
#include "logging/log_level.h"



#define ENABLE_LOGGING 1

#define GET_FILE_NAME__ (strrchr(__FILE__, '/') ? strrchr(__FILE__, '/') + 1 : __FILE__)

#if defined ENABLE_LOGGING

    #define LOG( level )  \
                            if ( (logging::level) <= (logging::TLogConfig::GetLevel()) ) \
                                logging::TLog(logging::level, GET_FILE_NAME__, __LINE__, __func__).GetLogMetadata()

   // ------------------------ base code uses these macros
    #define LOG_INFO LOG(eInfo)

#else
    #define LOG( level )  std::cerr << std::endl
#endif




#endif
