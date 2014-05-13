//
//  macrologger.cpp
//  vClientTemplateLib
//
//  Created by Virendra Shakya on 5/12/14.
//  Copyright (c) 2014 Virendra Shakya. All rights reserved.
//

#include "base/thread_syn_logger/macrologger.h"

//#ifdef __OBJC__
//#import <Foundation/Foundation.h>
//#else
#include <time.h>
#include <string.h>
#include <stdio.h>
#include <sys/time.h>
//#include <stdexcept> //for assert
//#include <assert.h>
//#endif


static const int kPrettyTimeBufferSize = 15;
char* PleaseGetTheTimeNow()
    {
    static char iBuffer[kPrettyTimeBufferSize];
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
    //assert(n == sizeof(iBuffer));
    iBuffer[n] = 0;
#endif
    return iBuffer;
    }

const char* PleaseGetStrRChr(const char* aStr, int aChar)
    {
    return strrchr(aStr, aChar);
    }


