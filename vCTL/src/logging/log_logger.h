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


//#define THREADSAFE_LOGGING 1
//#define ENABLE_LOGGING 1

#define GET_FILE_NAME__ (strrchr(__FILE__, '/') ? strrchr(__FILE__, '/') + 1 : __FILE__)

#if defined ENABLE_LOGGING

    #define LOG( level )  \
                            if ( (logging::level) <= (logging::TLogConfig::GetLevel()) ) \
                                logging::TLog(logging::level, GET_FILE_NAME__, __LINE__, __func__).GetLogMetadata()

   // ------------------------ base/legacy code uses these macros
    #define LOG_INFO LOG(eInfo)
    #define LOG_ERROR LOG(eError)
    #define LOG_FATAL LOG(eFatal)

#else

#include <iostream>

    #define LOG( level )  std::cerr << std::endl

    #define LOG_INFO LOG(eInfo)
    #define LOG_ERROR LOG(eError)
    #define LOG_FATAL LOG(eFatal)
    
#endif




#endif
