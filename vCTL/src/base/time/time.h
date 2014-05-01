//
//  time.h
//  vClientTemplateLib
//
//  Created by Virendra Shakya on 4/24/14.
//  Copyright (c) 2014 Virendra Shakya. All rights reserved.
//

#ifndef vClientTemplateLib_time_h
#define vClientTemplateLib_time_h

#include <time.h>
#include <stdint.h>

namespace vbase
{
  
class TTime
    {
public:
    static const int64_t kMilliSecondsPerSecond = 1000;
    static const int64_t kMicroSecondsPerMilliSecond = 1000;
    static const int64_t kNanoSecondsPerMicroSecond = 1000;
    static const int64_t kMicroSecondsPerSecond = kMicroSecondsPerMilliSecond * kMilliSecondsPerSecond;
    static const int64_t kNanoSecondsPerSecond = kNanoSecondsPerMicroSecond * kMicroSecondsPerSecond;
    };

class TTimeDelta
    //
    // currently not used
    //
    {
public:
    explicit TTimeDelta(long aDelta)
    {}
    };
  
}

#endif
