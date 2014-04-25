//
//  error_handler.h
//  vClientTemplateLib
//
//  Created by Virendra Shakya on 4/24/14.
//  Copyright (c) 2014 Virendra Shakya. All rights reserved.
//

#ifndef vClientTemplateLib_error_handler_h
#define vClientTemplateLib_error_handler_h

#define V_PTHREAD_CALL( expr ) \
                              do \
                                { \
                                  int thePThreadCallError = ( expr ); \
                                  if ( 0 != thePThreadCallError ) \
                                  { \
                                    LOG_ERROR << #expr << " : " << strerror(thePThreadCallError); \
                                  } \
                              } while (false)

#define V_PTHREAD_CALL_RET_ERROR( expr, err ) \
                              do \
                              { \
                                ( err ) = ( expr ); \
                                if ( 0 != ( err ) ) \
                                { \
                                  LOG_ERROR << #expr << " : " << strerror( ( err ) ); \
                                } \
                              } while (false)

#endif
