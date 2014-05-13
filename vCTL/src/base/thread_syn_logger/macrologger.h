/*
 * Copyright (c) 2012 David Rodrigues
 *
 * Permission is hereby granted, free of charge, to any person obtaining a
 * copy of this software and associated documentation files (the "Software"),
 * to deal in the Software without restriction, including without limitation
 * the rights to use, copy, modify, merge, publish, distribute, sublicense,
 * and/or sell copies of the Software, and to permit persons to whom the
 * Software is furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included
 * in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS
 * OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS
 * IN THE SOFTWARE.
 */

#ifndef __MACROLOGGER_H__
#define __MACROLOGGER_H__

#include <stdio.h>
#include <string.h>

//
//Common - we always print errors even on production build
//

#define ERROR_TAG   "ERROR"

extern char* PleaseGetTheTimeNow();
extern const char* PleaseGetStrRChr(const char* aStr, int aChar);

#define _FILE PleaseGetStrRChr(__FILE__, '/') ? PleaseGetStrRChr(__FILE__, '/') + 1 : __FILE__


#define PRINTFUNCTION(format, ...)      printf(format, __VA_ARGS__)
#define LOG_FMT             "\n%s | %-7s | %-15s | %s:%d | "
#define LOG_ARGS(LOG_TAG)   PleaseGetTheTimeNow(), LOG_TAG, _FILE, __FUNCTION__, __LINE__
#define NEWLINE     "\n"


#if !defined(ENABLE_KERNEL_LOGGING)

#define KERNEL_LOG_DEBUG(message, args...)
#define KERNEL_LOG_INFO(message, args...)
//#define KERNEL_LOG_ERROR(message, args...)
//Always print the error messages
#define KERNEL_LOG_ERROR(message, args...)     PRINTFUNCTION(LOG_FMT message NEWLINE, LOG_ARGS(ERROR_TAG), ## args)

#else //ENABLE_KERNEL_LOGGING


////#ifdef __OBJC__
////#import <Foundation/Foundation.h>
////#else
//#include <time.h>
//#include <string.h>
//#include <stdio.h>
////#include <sys/time.h>
////#include <stdexcept> //for assert
////#include <assert.h>
////#endif

/*
extern char* PleaseGetTheTimeNow();
extern const char* PleaseGetStrRChr(const char* aStr, int aChar);

#define _FILE PleaseGetStrRChr(__FILE__, '/') ? PleaseGetStrRChr(__FILE__, '/') + 1 : __FILE__
*/

#define NO_LOG          0x00
#define ERROR_LEVEL     0x01
#define INFO_LEVEL      0x02
#define DEBUG_LEVEL     0x03

#ifndef LOG_LEVEL
#define LOG_LEVEL   DEBUG_LEVEL
#endif

//#ifdef __OBJC__
//
//#if __has_feature(objc_arc)
//#define AUTORELEASEPOOL_BEGIN   @autoreleasepool {
//#define AUTORELEASEPOOL_END     }
//#define RELEASE(OBJ)            OBJ = nil
//#else
//#define AUTORELEASEPOOL_BEGIN   NSAutoreleasePool *_pool = [[NSAutoreleasePool alloc] init];
//#define AUTORELEASEPOOL_END     [_pool release];
//#define RELEASE(OBJ)            [OBJ release];
//#endif
//
//#define PRINTFUNCTION(format, ...)      objc_print(@format, __VA_ARGS__)
//#else

/*
//#define PRINTFUNCTION(format, ...)      fprintf(stderr, format, __VA_ARGS__)
#define PRINTFUNCTION(format, ...)      printf(format, __VA_ARGS__)

//#endif

#define LOG_FMT             "\n%s | %-7s | %-15s | %s:%d | "
#define LOG_ARGS(LOG_TAG)   PleaseGetTheTimeNow(), LOG_TAG, _FILE, __FUNCTION__, __LINE__

#define NEWLINE     "\n"
*/

/* #define ERROR_TAG   "ERROR" */
#define INFO_TAG    "INFO"
#define DEBUG_TAG   "DEBUG"

#if LOG_LEVEL >= DEBUG_LEVEL
#define KERNEL_LOG_DEBUG(message, args...)     PRINTFUNCTION(LOG_FMT message NEWLINE, LOG_ARGS(DEBUG_TAG), ## args)
#else
#define KERNEL_LOG_DEBUG(message, args...)
#endif

#if LOG_LEVEL >= INFO_LEVEL
#define KERNEL_LOG_INFO(message, args...)      PRINTFUNCTION(LOG_FMT message NEWLINE, LOG_ARGS(INFO_TAG), ## args)
#else
#define KERNEL_LOG_INFO(message, args...)
#endif

#if LOG_LEVEL >= ERROR_LEVEL
#define KERNEL_LOG_ERROR(message, args...)     PRINTFUNCTION(LOG_FMT message NEWLINE, LOG_ARGS(ERROR_TAG), ## args)
#else
#define KERNEL_LOG_ERROR(message, args...)
#endif

#if LOG_LEVEL >= NO_LOGS
#define KERNEL_LOG_IF_ERROR(condition, message, args...) if (condition) PRINTFUNCTION(LOG_FMT message NEWLINE, LOG_ARGS(ERROR_TAG), ## args)
#else
#define KERNEL_LOG_IF_ERROR(condition, message, args...)
#endif

//#ifdef __OBJC__
//
//static inline void objc_print(NSString *format, ...) {
//    AUTORELEASEPOOL_BEGIN
//    va_list args;
//    va_start(args, format);
//    NSString *logStr = [[NSString alloc] initWithFormat:format arguments:args];
//    fprintf(stderr, "%s", [logStr UTF8String]);
//    RELEASE(logStr);
//    va_end(args);
//    AUTORELEASEPOOL_END
//}
//
//#endif

#endif // ENABLE_KERNEL_LOGGING

#endif