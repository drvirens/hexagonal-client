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

#include "base/lambda/lambda.h"

namespace vbase
{

class TTask
    {
public:
    TTask(CLambda& aLambda);
    ~TTask();
    //TODO: TTask(const TTask& aRhs);
    void SetUniqueId(int aUniqueId) { iUniqueId = aUniqueId; }
    int UniqueId() const { return iUniqueId; }
    void Execute();
        
private:
    int iUniqueId;
    std::string iTaskName;
    CLambda& iLambda; //lambda us ref-counted
    };

} //namespace vbase

#endif /* defined(__vClientTemplateLib__task__) */
