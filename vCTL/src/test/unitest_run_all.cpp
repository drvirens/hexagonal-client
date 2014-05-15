    //
    //  CUnitTests_All.cpp
    //  vSocialClient
    //
    //  Created by Virendra Shakya on 4/13/14.
    //  Copyright (c) 2014 TV LLC. All rights reserved.
    //

#include "test/unitest_run_all.h"
#include "gtest/gtest.h"
#include "logging/log.h"
#include "logging/log_output.h"
#include "logging/log_logger.h"

void RunUnitTests()
    {
    //for unit tests using gtest, disable logs so that they dont interfere with tests
    //and also gtest unit tests results are easy to read
    logging::ELogLevel loglevel = logging::eFatal; //logging::eDebug to print all logs
    logging::TLogConfig::AddOutput(new logging::CConsoleOutput(loglevel));
    
    LOG(eInfo) << "Running the unit tests...";
    
    CUnitTests_All* all = CUnitTests_All::New();
    if( all )
        {
        all->RunAllUnitTests();
        }
        
        //delete all; //wait for all gtests to run then delete
    }

CUnitTests_All::~CUnitTests_All()
    {
    
    }

CUnitTests_All* CUnitTests_All::New()
    {
    CUnitTests_All* obj = new CUnitTests_All();
    if( obj )
        {
        obj->Construct();
        }
    return obj;
    }

void CUnitTests_All::RunAllUnitTests()
    {
    (void)::testing::UnitTest::GetInstance()->Run();
    }

CUnitTests_All::CUnitTests_All()
    : iArgC(0)
    , iArgV(0)
    {}

void CUnitTests_All::Construct()
    {
    testing::InitGoogleTest(&iArgC, iArgV);
    }
    
