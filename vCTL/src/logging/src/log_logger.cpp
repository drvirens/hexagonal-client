//
//  log_logger.cpp
//  vClientTemplateLib
//
//  Created by Virendra Shakya on 5/14/14.
//  Copyright (c) 2014 Virendra Shakya. All rights reserved.
//

#include "logging/log_logger.h"


CdmLogMessage::CdmLogMessage(const char* file, int line) {
  std::string filename(file);
  size_t last_slash_pos = filename.find_last_of("\\/");
  if (last_slash_pos != std::string::npos)
    filename = filename.substr(last_slash_pos + 1);

  stream_ << '[';

  // Process and thread ID.
//  stream_ << CurrentProcessId() << ':';
//  stream_ << CurrentThreadId() << ':';

  // Time and tick count.
  time_t t = time(NULL);
  struct tm local_time = {0};
#if _MSC_VER >= 1400
  localtime_s(&local_time, &t);
#else
  localtime_r(&t, &local_time);
#endif
//  struct tm* tm_time = &local_time;
//  stream_ << std::setfill('0')
//          << std::setw(2) << 1 + tm_time->tm_mon
//          << std::setw(2) << tm_time->tm_mday
//          << '/'
//          << std::setw(2) << tm_time->tm_hour
//          << std::setw(2) << tm_time->tm_min
//          << std::setw(2) << tm_time->tm_sec
//          << ':';
//  stream_ << TickCount() << ':';

  // File name.
  stream_ << filename << "(" << line << ")] ";
}

CdmLogMessage::~CdmLogMessage() {
  // Use std::cout explicitly for the line break. This limits the use of this
  // class only to the definition of DLOG() (which also uses std::cout).
  //
  // This appends "std::endl" after all other messages appended to DLOG(),
  // which relies on the C++ standard ISO/IEC 14882:1998(E) $12.2.3:
  // "Temporary objects are destroyed as the last step in evaluating the
  // full-expression (1.9) that (lexically) contains the point where they were
  // created."
  std::cout << std::endl;
}


