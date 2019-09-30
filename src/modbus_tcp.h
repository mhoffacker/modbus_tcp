/*
 * modbus_tcp.h
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

#ifndef MODBUS_TCP_H_
#define MODBUS_TCP_H_

#include <stdint.h>
#include <stddef.h>

#include "modbus_tcp_config.h"

typedef enum {
	MBT_OK = 0,					/* Everything went fine */
	MBT_ERR = 1,				/* General error */
	MBT_NO_SUPPORT = 2,			/* No support for this command */
	MBT_FRAME_ERR = 3,			/* Error in frame data */
	MBT_OUT_BUF_ERR = 4,		/* Output buffer too small */
	MBT_ERR_WRITING_REG = 5,	/* Register cannot be written */
	MBT_ERR_READING_REG = 6		/* Register cannot be read */
} mbt_ret_type;

#define MBT_READ_DISCRETE_COIL					2
#define MBT_READ_COILS							1
#define MBT_WRITE_SINGLE_COIL					5
#define MBT_WRITE_MULTIPLE_COILS				15
#define MBT_READ_INPUT_REGISTER					4
#define MBT_READ_MULTIPLE_HOLDING_REGISTERS		3
#define MBT_WRITE_SINGLE_HOLDING_REGISTER		6
#define MBT_WRITE_MULTIPLE_HOLDING_REGISTERS	16

mbt_ret_type ModBUS_TCP_handler(uint8_t *pu8_buf_in, uint16_t u16_buf_in_len, uint8_t *pu8_buf_out, uint16_t u16_buf_out_len, uint16_t *pu16_reply_len);

#endif /*MODBUS_TCP_H_*/
