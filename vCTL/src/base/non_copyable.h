//
//  non_copyable.h
//  vClientTemplateLib
//
//  Created by Virendra Shakya on 4/22/14.
//  Copyright (c) 2014 Virendra Shakya. All rights reserved.
//

#ifndef vClientTemplateLib_non_copyable_h
#define vClientTemplateLib_non_copyable_h

//based on CRTP : curiously recursive template pattern
template <class T>
class TNonCopyable
    {
protected:
    TNonCopyable() {}
    ~TNonCopyable() {} //non-virtual
    
private:
    TNonCopyable(const TNonCopyable&);
    TNonCopyable& operator=(const TNonCopyable&);
    };

#endif
