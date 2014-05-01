//
//  task.h
//  vClientTemplateLib
//
//  Created by Virendra Shakya on 4/30/14.
//  Copyright (c) 2014 Virendra Shakya. All rights reserved.
//

#ifndef __vClientTemplateLib__task__
#define __vClientTemplateLib__task__

#include <queue>
#include <string>

namespace vbase
{

class TTask
    {
public:
    TTask();
    ~TTask();
    TTask(const TTask& aRhs);
private:
    int iUniqueId;
    std::string iTaskName;
    };
    
typedef std::queue<TTask> TTaskQueue;

}

#endif /* defined(__vClientTemplateLib__task__) */
