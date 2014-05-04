//
//  log_output.h
//  vClientTemplateLib
//
//  Created by Virendra Shakya on 5/3/14.
//  Copyright (c) 2014 Virendra Shakya. All rights reserved.
//

#ifndef __vClientTemplateLib__log_output__
#define __vClientTemplateLib__log_output__

#include <string>

#include "logging/log_level.h"
#if defined(THREADSAFE_LOGGING)
#include "base/synchronize/lock.h"
#endif

namespace logging
{

// ------------------------------------- IOutput
class IOutput
    {
public:
    virtual ~IOutput() {}
    virtual void Dump(ELogLevel aLogLevel,
                     const std::string& aTimeStamp,
                     const std::string& aFileName,
                     int aLineNumber,
                     const std::string& aFunctionName,
                     const std::string& aMessage) = 0;
    };
    
// ------------------------------------- ISimpleBlockingOutput
class ISimpleBlockingOutput : public IOutput
    {
public:
    explicit ISimpleBlockingOutput(ELogLevel aLogLevel) : iLogLevel(aLogLevel) {}
    
    virtual ~ISimpleBlockingOutput() {}
    virtual void Dump(ELogLevel aLogLevel,
                     const std::string& aTimeStamp,
                     const std::string& aFileName,
                     int aLineNumber,
                     const std::string& aFunctionName,
                     const std::string& aMessage);
        
    virtual std::ostream& OutputTo() = 0;
    
private:
    ELogLevel iLogLevel;
#if defined(THREADSAFE_LOGGING)
    vbase::TLock iLock;
#endif
    };
    
// ------------------------------------- CConsoleOutput
class CConsoleOutput : public ISimpleBlockingOutput
    {
public:
    explicit CConsoleOutput(ELogLevel aLogLevel) : ISimpleBlockingOutput(aLogLevel) {}
    virtual ~CConsoleOutput() {}
private:
    virtual std::ostream& OutputTo();
    };
    
    
// ------------------------------------- CFileOutput
//TODO: do this after file abstraction is ready for iOS and Android
class CFileOutput : public ISimpleBlockingOutput
    {
public:
    explicit CFileOutput(ELogLevel aLogLevel) : ISimpleBlockingOutput(aLogLevel) {}
    virtual ~CFileOutput() {}
private:
    virtual std::ostream& OutputTo();
private:
    //std::ofstream iOutputFile;
    };


} //namespace logging

#endif /* defined(__vClientTemplateLib__log_output__) */
