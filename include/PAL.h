/**
 * @file PAL.h
 * @author William Lowther (william.e.lowther@gmail.com)
 * @brief PAL to separate the platform from the application 
 * @version 0.1
 * @date 2020-03-11
 * 
 * @copyright Copyright (c) 2020
 * 
 */

#ifndef _PAL_H_
#define _PAL_H_

#ifdef INC_FREERTOS_H
#error "Do not include the RTOD header files instead include the PAL abstracted versions of the RTOS (PAL_*.h)"
#endif

#include "FreeRTOS.h"



#endif // _PAL_H_