/*
 * modbus_tcp_config_free_rtos.h
 * Version 0.0.2
 * 
 * MIT License
 * 
 * Copyright (c) 2019 Michael Hoffacker (michael@hoffacker.bayern)
 * 
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *  
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 * 
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 *
 * History:
 * 2019-09-29
 * First version for testing
 * 
 * 2019-09-30
 * Initial tests passed for reading holding register
 */
#ifndef MODBUS_TCP_CONFIG_H
#define MODBUS_TCP_CONFIG_H

#define MBT_USE_WEAK					/* Create weak function prototypes, so no need to implement unused functions */
//#define MBT_SUPPORT_HOLDING_REG
//#define MBT_SUPPORT_INPUT_REG
//#define MBT_SUPPORT_COILS
//#define MBT_SUPPORT_DISCRETE_INPUT

#ifdef MBT_USE_WEAK
	#ifndef __weak
		#define __weak __attribute__((weak))
	#endif
#endif

/*****User includes for malloc and free*****/
#include "FreeRTOS.h"
/*******************************************/

#define MBT_MALLOC			pvPortMalloc
#define MBT_FREE			vPortFree
#define MBT_BUFFER_SIZE 	260

#endif /*MODBUS_TCP_CONFIG_H*/
