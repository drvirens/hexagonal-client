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

#else //ENABLE_LOGGING

// ===================================


#include <iostream>
#include <sstream>
#include <string>

// The following classes/macros are adapted from base/logging.h.

// This class is used to explicitly ignore values in the conditional
// logging macros.  This avoids compiler warnings like "value computed
// is not used" and "statement has no effect".
class LogMessageVoidify {
 public:
  LogMessageVoidify() {}
  // This has to be an operator with a precedence lower than << but
  // higher than ?:
  void operator&(std::ostream&) {}
};

// This class serves two purposes:
// (1) It adds common headers to the log message, e.g. timestamp, process ID.
// (2) It adds a line break at the end of the log message.
// This class is copied and modified from base/logging.* but is quite different
// in terms of how things work. This class is designed to work only with the
// CDM_DLOG() defined below and should not be used for other purposes.
class CdmLogMessage {
 public:
  CdmLogMessage(const char* file, int line);
  ~CdmLogMessage();

  std::string message() { return stream_.str(); }

 private:
  std::ostringstream stream_;
};

// Helper macro which avoids evaluating the arguments to a stream if
// the condition doesn't hold.
#define CDM_LAZY_STREAM(stream, condition) \
  !(condition) ? (void) 0 : LogMessageVoidify() & (stream)

#define CDM_DLOG() CDM_LAZY_STREAM(std::cout, CDM_DLOG_IS_ON()) \
  << CdmLogMessage(__FILE__, __LINE__).message()

//#if defined(NDEBUG)
#define CDM_DLOG_IS_ON() false
//#else
//#define CDM_DLOG_IS_ON() true
//#endif


// ----

  #define LOG( level )  CDM_DLOG()

   #define LOG_INFO LOG(eInfo)
    #define LOG_ERROR LOG(eError)
    #define LOG_FATAL LOG(eFatal)


#endif




#endif
