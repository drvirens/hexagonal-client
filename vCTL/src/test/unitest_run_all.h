    //
    //  CUnitTests_All.h
    //  vSocialClient
    //
    //  Created by Virendra Shakya on 4/13/14.
    //  Copyright (c) 2014 TV LLC. All rights reserved.
    //

#ifndef __vSocialClient__CUnitTests_All__
#define __vSocialClient__CUnitTests_All__

void RunUnitTests();

class CUnitTests_All
    {
public:
    virtual ~CUnitTests_All();
    static CUnitTests_All* New();
    void RunAllUnitTests();
    
private:
    CUnitTests_All();
    void Construct();
    
private:
    int iArgC;
    char** iArgV;
    };

#endif /* defined(__vSocialClient__CUnitTests_All__) */
