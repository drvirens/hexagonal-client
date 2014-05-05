//
//  lambda_assign.h
//  vClientTemplateLib
//
//  Created by Virendra Shakya on 5/5/14.
//  Copyright (c) 2014 Virendra Shakya. All rights reserved.
//

#ifndef vClientTemplateLib_lambda_assign_h
#define vClientTemplateLib_lambda_assign_h

namespace vbase
{

// Actual work is done by an independent class: for e.g
/*

template <class T>
class Increment //Task
{
public:
    T iArg;
    Increment( T a ) : iArg( a ) {}
    
    template <typename OutIt>
    T operator() ( T& aValue, OutIt aOut )
    {
        aValue += iArg;
        *aOut++ = aValue;
        return 1;
    }
};

*/

template
    <
    //template structure of the derived class
    template
        <
            // an operator
        template < typename > class,
            // a type
        typename
        >
        class CRTP,
    
        //template structure of operator
    template <typename> class OPERATOR,
    
        //simple value type
    typename T
    >
class TFunctor
    {
public:
    TFunctor( OPERATOR<T>& aOperator )
        : iOperator( aOperator )
        {}

public:
    template <typename OUTPUT>
    int operator() ( int& aValue, OUTPUT aOutput )
        {
        CRTP< OPERATOR, T>* thiz = static_cast< CRTP< OPERATOR, T> * >(this);
        return thiz->functor( aValue, aOutput );
        }
    
protected:
    OPERATOR<T>& iOperator;
    };
    

// ---------
//uses CRTP
template <template <typename> class OPERATOR, class T>
class TAssign : public TFunctor< TAssign, OPERATOR, T >
    {
public:
    TAssign( OPERATOR<T>& aOperator )
        : TFunctor< vbase::TAssign, OPERATOR, T >(aOperator)
        {}
        
    template<typename OUTPUT>
    int functor( int& aValue, OUTPUT aOutput )
        {
        return this->iOperator( aValue, aOutput );
        }
    };



} //namespace vbase


#endif
