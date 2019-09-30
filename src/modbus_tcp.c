/*
 * modbus_tcp.c
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


#include "modbus_tcp.h"


#ifdef MBT_USE_WEAK

#ifdef MBT_SUPPORT_HOLDING_REG
/*******************************************************************************
 * BMT_BeginReadHoldingRegister (weak)
 *
 * This will be called before starting to read any data from the holding register
 * You may return a pointer to any internal structure in void **pAny. Take care
 * that no space is reserved by ModBUS TCP Handler.
 *
 * @param u16_address 	Read starting address
 * @param slave			Unit identifier
 * @param **pAny		Pointer to a internal structure
 * @return MBT_OK on success
 ********************************************************************************/
__weak mbt_ret_type MBT_BeginReadHoldingRegister(uint16_t u16_address, uint8_t slave, void **pAny) {
	if ( pAny ) {
		 *pAny = NULL;
	}
	return MBT_OK;
}

/*******************************************************************************
 * MBT_EndReadHoldingRegister (weak)
 *
 * This will be called after all data is read to release the memory for internal
 * data structure
 *
 * @param **pAny		Pointer to a internal structure
 * @return MBT_OK on success
 ********************************************************************************/
__weak mbt_ret_type MBT_EndReadHoldingRegister(void **pAny) {
	if ( pAny != NULL ) {
		if ( *pAny != NULL ) {
			MBT_FREE(*pAny);
		}
	}
	return MBT_OK;
}

/*******************************************************************************
 * MBT_ReadHoldingRegister (weak)
 *
 * Reading the date for every address in a holding register
 *
 * @param u16_address 	Read starting address
 * @param slave			Unit identifier
 * @param pu16_data		Data on address u16_address
 * @param *pAny			Pointer to a internal structure
 * @return MBT_OK on success
 ********************************************************************************/
__weak mbt_ret_type MBT_ReadHoldingRegister(uint16_t u16_address, uint8_t slave, uint16_t *pu16_data, void *pAny) {
	*pu16_data = 0;
	return MBT_OK;
}

/*******************************************************************************
 * MBT_BeginWriteHoldingRegister (weak)
 *
 * This will be called before starting to write any data to a holding register
 * You may return a pointer to any internal structure in void **pAny. Take care
 * that no space is reserved by ModBUS TCP Handler.
 *
 * @param u16_address 	Read starting address
 * @param slave			Unit identifier
 * @param **pAny		Pointer to a internal structure
 * @return MBT_OK on success
 ********************************************************************************/
__weak mbt_ret_type MBT_BeginWriteHoldingRegister(uint16_t u16_address, uint8_t slave, void **pAny) {
	*pAny = MBT_MALLOC(sizeof(void*));
	*pAny = NULL;
	return MBT_OK;
}

/*******************************************************************************
 * MBT_EndWriteHoldingRegister (weak)
 *
 * This will be called after all data is written to release the memory for internal
 * data structure
 *
 * @param **pAny		Pointer to a internal structure
 * @return MBT_OK on success
 ********************************************************************************/
__weak mbt_ret_type MBT_EndWriteHoldingRegister(void **pAny) {
	if ( pAny != NULL ) {
		MBT_FREE(*pAny);
	}
	return MBT_OK;
}

/*******************************************************************************
 * MBT_WriteHoldingRegister (weak)
 *
 * Write the date for every address in a holding register
 *
 * @param u16_address 	Read starting address
 * @param value			Value to be written
 * @param slave			Unit identifier
  * @param *pAny			Pointer to a internal structure
 * @return MBT_OK on success
 ********************************************************************************/
__weak mbt_ret_type MBT_WriteHoldingRegister(uint16_t u16_address, uint16_t value, uint8_t slave, void *pAny) {
	return MBT_OK;
}


#endif /*MBT_SUPPORT_HOLDING_REG*/

#ifdef MBT_SUPPORT_INPUT_REG

/*******************************************************************************
 * MBT_BeginReadInputRegister (weak)
 *
 * This will be called before starting to read any data from the input register
 * You may return a pointer to any internal structure in void **pAny. Take care
 * that no space is reserved by ModBUS TCP Handler.
 *
 * @param u16_address 	Read starting address
 * @param slave			Unit identifier
 * @param **pAny		Pointer to a internal structure
 * @return MBT_OK on success
 ********************************************************************************/
__weak mbt_ret_type MBT_BeginReadInputRegister(uint16_t u16_address, uint8_t slave, void **pAny) {
	if ( pAny ) {
		 *pAny = NULL;
	}

	return MBT_OK;
}

/*******************************************************************************
 * MBT_EndReadInputRegister (weak)
 *
 * This will be called after all data is read to release the memory for internal
 * data structure
 *
 * @param **pAny		Pointer to a internal structure
 * @return MBT_OK on success
 ********************************************************************************/
__weak mbt_ret_type MBT_EndReadInputRegister(void **pAny) {
	if ( pAny != NULL ) {
		if ( *pAny != NULL ) {
			MBT_FREE(*pAny);
		}
	}
	return MBT_OK;
}

/*******************************************************************************
 * MBT_ReadHoldingRegister (weak)
 *
 * Reading the date for every address in an input register
 *
 * @param u16_address 	Read starting address
 * @param slave			Unit identifier
 * @param pu16_data		Data on address u16_address
 * @param *pAny			Pointer to a internal structure
 * @return MBT_OK on success
 ********************************************************************************/
__weak mbt_ret_type MBT_ReadInputRegister(uint16_t u16_address, uint8_t slave, uint16_t *pu16_data, void *pAny) {
	*pu16_data = 0;
	return MBT_OK;
}

#endif /*MBT_SUPPORT_INPUT_REG*/

#ifdef MBT_SUPPORT_DISCRETE_INPUT
#error Discrete input not yet supported
__weak mbt_ret_type MBT_ReadDiscreteInput(uint16_t u16_address, uint8_t slave, uint8_t *pu8_data, void *pAny) {
	*pu8_data = 0;
	return MBT_OK;
}

#endif /*MBT_SUPPORT_DISCRETE_INPUT*/

#ifdef MBT_SUPPORT_COILS
#error Coils not yet supported
__weak mbt_ret_type MBT_WriteCoil(uint16_t u16_address, uint8_t value, uint8_t slave, void *pAny) {
	return MBT_OK;
}

__weak mbt_ret_type MBT_ReadCoil(uint16_t u16_address, uint8_t slave, uint8_t *pu8_data, void *pAny) {
	*pu8_data = 0;
	return MBT_OK;
}
#endif /*MBT_SUPPORT_COILS*/

#else
/* If no weak calls are available, the coder needs to implement all routines. See comments above for details */
#ifdef MBT_SUPPORT_HOLDING_REG
	extern mbt_ret_type MBT_BeginReadHoldingRegister(uint16_t u16_address, uint8_t slave, void **pAny);
	extern mbt_ret_type MBT_ReadHoldingRegister(uint16_t u16_address, uint8_t slave, uint16_t *pu16_data, void *pAny);
	extern mbt_ret_type MBT_EndReadHoldingRegister(void **pAny);

	extern mbt_ret_type MBT_BeginWriteHoldingRegister(uint16_t u16_address, uint8_t slave, void **pAny);
	extern mbt_ret_type MBT_WriteHoldingRegister(uint16_t u16_address, uint16_t value, uint8_t slave, void *pAny);
	extern mbt_ret_type MBT_EndWriteHoldingRegister(void **pAny);
#endif /*MBT_SUPPORT_HOLDING_REG*/

#ifdef MBT_SUPPORT_INPUT_REG
	extern mbt_ret_type MBT_BeginReadInputRegister(uint16_t u16_address, uint8_t slave, void **pAny);
	extern mbt_ret_type MBT_ReadInputRegister(uint16_t u16_address, uint8_t slave, uint16_t *pu16_data, void *pAny);
	extern mbt_ret_type MBT_EndReadInputRegister(void **pAny);
#endif /*MBT_SUPPORT_INPUT_REG*/

#ifdef MBT_SUPPORT_DISCRETE_INPUT
#error Discrete input not yet supported
	extern mbt_ret_type MBT_ReadDiscreteInput(uint16_t u16_address, uint8_t slave, uint8_t *pu8_data, void *pAny);
#endif /*MBT_SUPPORT_DISCRETE_INPUT*/

#ifdef MBT_SUPPORT_COILS
#error Coils not yet supported
	extern mbt_ret_type MBT_WriteCoil(uint16_t u16_address, uint8_t value, uint8_t slave, void *pAny);
	extern mbt_ret_type MBT_ReadCoil(uint16_t u16_address, uint8_t slave, uint8_t *pu8_data, void *pAny);
#endif /*MBT_SUPPORT_COILS*/
#endif


/*******************************************************************************
 * ModBUS_TCP_handler Handler for ModBUS TCP Frames
 *
 * Parses the ModBUS TCP frame and calls the routines for accessing the register
 *
 * @param *pu8_buf_in 		Input buffer, coming for TCP socket
 * @param u16_buf_in_len	Input buffer length, can be longer than ModBUS frame
 * @param *pu8_buf_out		Output buffer for return on TCP socket
 * @param u16_buf_out_len	Output buffer length, can be longer than ModBUS frame
 * @param *pu16_reply_len	Real length to transmit by TCP socket
 * @return MBT_OK on success
 ********************************************************************************/

mbt_ret_type ModBUS_TCP_handler(uint8_t *pu8_buf_in, uint16_t u16_buf_in_len,
		                   uint8_t *pu8_buf_out, uint16_t u16_buf_out_len,
						   uint16_t *pu16_reply_len) {
	mbt_ret_type res = MBT_OK;

	uint16_t u16_transaction_ident;
	uint16_t u16_prot_ident;
	uint16_t u16_length;
	uint8_t u8_unit_ident;
	uint8_t u8_function_code;

	uint8_t *pu8_ptr;

	uint16_t u16_first_register, u16_number_of_register, u16_resp_length, u16_data;
	uint8_t u8_num_bytes;

	uint8_t *pu8_in, *pu8_out, *pu8_resp_len, *pu8_num_bytes_resp;

    if ( pu8_buf_in == NULL || pu8_buf_out == NULL || pu16_reply_len == NULL ) {
        res = MBT_ERR;
    } else if ( u16_buf_in_len < 10 ) {	/* Change this to a define, 10 is the minimum length of a transmission */
		res = MBT_ERR;
	} else if ( u16_buf_out_len < 8 ) {
        res = MBT_OUT_BUF_ERR;
	} else {
		pu8_in = pu8_buf_in;
		pu8_out = pu8_buf_out;

		u16_transaction_ident = ((int16_t)*pu8_in << 8);
		u16_transaction_ident |= ((int16_t)*(++pu8_in));

		u16_prot_ident = ((int16_t)*(++pu8_in) << 8);
		u16_prot_ident |=  ((int16_t)*(++pu8_in));

		u16_length = ((int16_t)*(++pu8_in) << 8);
		u16_length |= ((int16_t)*(++pu8_in));

		u8_unit_ident =*(++pu8_in);
		u8_function_code = *(++pu8_in);

		if ( u16_length + 6 > u16_buf_in_len ) {
			res = MBT_FRAME_ERR;
		} else if ( u16_prot_ident != 0x0000 ) {
			res = MBT_FRAME_ERR;
		} else {
			/* Build ModBUS reply header */

			/* Copy transaction id */
			*pu8_out = (uint8_t)(u16_transaction_ident >> 8);
			*(++pu8_out) = (uint8_t)(u16_transaction_ident & 0xFF);

			/* Set ModBUS protocol identifier to 0x0000 */
			*(++pu8_out) = 0x00;
			*(++pu8_out) = 0x00;

			/* Remember position for frame length  and set to two (unit identifier and function code follow in any case */
			pu8_resp_len = (++pu8_out);
			u16_resp_length = 2;
			++pu8_out;

			/* Set unit identifier */
			*(++pu8_out) = u8_unit_ident;

			/* Set function code */
			*(++pu8_out) = u8_function_code;

			switch ( u8_function_code ) {
#if defined(MBT_SUPPORT_DISCRETE_INPUT) || defined(MBT_SUPPORT_COILS)
#ifdef MBT_SUPPORT_DISCRETE_INPUT
			case MBT_READ_DISCRETE_COIL:
#endif /*MBT_SUPPORT_DISCRETE_INPUT*/
#ifdef MBT_SUPPORT_COILS
			case MBT_READ_COILS:
#endif /*MBT_SUPPORT_COILS*/
				res = MBT_NO_SUPPORT;
				break;
#endif /*defined(MBT_SUPPORT_DISCRETE_INPUT) || defined(MBT_SUPPORT_COILS)*/

#ifdef MBT_SUPPORT_COILS
			case MBT_WRITE_SINGLE_COIL:
				res = MBT_NO_SUPPORT;
				break;

			case MBT_WRITE_MULTIPLE_COILS:
				res = MBT_NO_SUPPORT;
				break;
#endif /*MBT_SUPPORT_COILS*/

#if defined(MBT_SUPPORT_HOLDING_REG) || defined(MBT_SUPPORT_INPUT_REG)
#ifdef MBT_SUPPORT_INPUT_REG
			case MBT_READ_INPUT_REGISTER:
#endif /*MBT_SUPPORT_INPUT_REG*/
#ifdef MBT_SUPPORT_HOLDING_REG
			case MBT_READ_MULTIPLE_HOLDING_REGISTERS:
#endif /*MBT_SUPPORT_HOLDING_REG*/
				/* Store pointer to number of bytes field */
				pu8_num_bytes_resp = (++pu8_out);
				*pu8_num_bytes_resp = 0;

				/* Increase length by 1 for number of bytes */
				u16_resp_length++;

				u16_first_register = ((int16_t)*(++pu8_in) << 8);
				u16_first_register |=  ((int16_t)*(++pu8_in));

				u16_number_of_register = ((int16_t)*(++pu8_in) << 8);
				u16_number_of_register |=  ((int16_t)*(++pu8_in));

				if ( u16_number_of_register > 123 ) {	/* Change this to a define */
					res = MBT_FRAME_ERR;
				} else if ( u16_buf_out_len < 8 + 1 + 2*u16_number_of_register ) { /* 8 bytes header + 1 num of bytes + data */
					res = MBT_OUT_BUF_ERR;
				} else {
					if ( u8_function_code == MBT_READ_MULTIPLE_HOLDING_REGISTERS ) {
#ifdef MBT_SUPPORT_HOLDING_REG
						MBT_BeginReadHoldingRegister(u16_first_register, u8_unit_ident, (void**)&pu8_ptr);
#endif /*MBT_SUPPORT_HOLDING_REG*/
					} else {
#ifdef MBT_SUPPORT_INPUT_REG
						MBT_BeginReadInputRegister(u16_first_register, u8_unit_ident, (void**)&pu8_ptr);
#endif /*MBT_SUPPORT_INPUT_REG*/
					}
					while (u16_number_of_register) {
						(*pu8_num_bytes_resp) += 2;	/* Increase response byte count by 2 */
						u16_resp_length += 2;			/* Increase response length by 2 */

						if ( u8_function_code == MBT_READ_MULTIPLE_HOLDING_REGISTERS ) {
#ifdef MBT_SUPPORT_HOLDING_REG
							if ( MBT_ReadHoldingRegister(u16_first_register, u8_unit_ident, &u16_data, (void*)pu8_ptr) != MBT_OK ) {
								res = MBT_ERR_READING_REG;
							}
#endif /*MBT_SUPPORT_HOLDING_REG*/
						} else {
#ifdef MBT_SUPPORT_INPUT_REG
							if ( MBT_ReadInputRegister(u16_first_register, u8_unit_ident, &u16_data, (void*)pu8_ptr) != MBT_OK ) {
								res = MBT_ERR_READING_REG;
							}
#endif /*MBT_SUPPORT_INPUT_REG*/
						}
						*(++pu8_out) = (uint8_t)(u16_data >> 8);
						*(++pu8_out) = (uint8_t)(u16_data & 0xFF);

						u16_first_register++;
						u16_number_of_register--;
					}
					if ( u8_function_code == MBT_READ_MULTIPLE_HOLDING_REGISTERS ) {
#ifdef MBT_SUPPORT_HOLDING_REG
						MBT_EndReadHoldingRegister((void**)&pu8_ptr);
#endif /*MBT_SUPPORT_HOLDING_REG*/
					} else {
#ifdef MBT_SUPPORT_INPUT_REG
						MBT_EndReadInputRegister((void**)&pu8_ptr);
#endif /*MBT_SUPPORT_INPUT_REG*/
					}
				}
				break;
#endif /*defined(MBT_SUPPORT_HOLDING_REG) || defined(MBT_SUPPORT_INPUT_REG)*/

#ifdef MBT_SUPPORT_HOLDING_REG
			case MBT_WRITE_SINGLE_HOLDING_REGISTER:
				u16_first_register = ((int16_t)*(++pu8_in) << 8);
				u16_first_register |=  ((int16_t)*(++pu8_in));

				u16_data = ((int16_t)*(++pu8_in) << 8);
				u16_data |=  ((int16_t)*(++pu8_in));
				if ( u16_buf_out_len < 14 ) { /* 10 bytes header + 2 bytes data */
					res = MBT_OUT_BUF_ERR;
				} else {
					*(++pu8_out) = (uint8_t)(u16_first_register >> 8);
					*(++pu8_out) = (uint8_t)(u16_first_register & 0xFF);

					*(++pu8_out) = (uint8_t)(u16_data >> 8);
					*(++pu8_out) = (uint8_t)(u16_data & 0xFF);

					u16_resp_length += 4;
					MBT_BeginWriteHoldingRegister(u16_first_register, u8_unit_ident, (void**)&pu8_ptr);
					if ( MBT_WriteHoldingRegister(u16_first_register, u16_data, u8_unit_ident, pu8_ptr) != MBT_OK ) {
						res = MBT_ERR_WRITING_REG;
					}
					MBT_EndWriteHoldingRegister((void**)&pu8_ptr);
				}
				break;

			case MBT_WRITE_MULTIPLE_HOLDING_REGISTERS:
				u16_first_register = ((int16_t)*(++pu8_in) << 8);
				u16_first_register |=  ((int16_t)*(++pu8_in));

				u16_number_of_register = ((int16_t)*(++pu8_in) << 8);
				u16_number_of_register |=  ((int16_t)*(++pu8_in));

				u8_num_bytes = *(++pu8_in);

				/* Only support even number of bytes */
				if ( u8_num_bytes != u16_number_of_register * 2 ) {
					res = MBT_FRAME_ERR;
				} else if ( u16_buf_out_len < 14 ) { /* 10 bytes header + 4 bytes data */
					res = MBT_OUT_BUF_ERR;
				} else {
					*(++pu8_out) = (uint8_t)(u16_first_register >> 8);
					*(++pu8_out) = (uint8_t)(u16_first_register & 0xFF);

					*(++pu8_out) = (uint8_t)(u16_number_of_register >> 8);
					*(++pu8_out) = (uint8_t)(u16_number_of_register & 0xFF);

					u16_resp_length += 4;
					MBT_BeginWriteHoldingRegister(u16_first_register, u8_unit_ident, (void**)&pu8_ptr);
					while ( u16_number_of_register ) {
						u16_data = ((int16_t)*(++pu8_in) << 8);
						u16_data |=  ((int16_t)*(++pu8_in));

						MBT_WriteHoldingRegister(u16_first_register, u16_data, u8_unit_ident, pu8_ptr);

						u16_first_register++;
						u16_number_of_register--;
					}
					MBT_EndWriteHoldingRegister((void**)&pu8_ptr);
				}

				break;
#endif /*MBT_SUPPORT_HOLDING_REG*/

			default:
				res = MBT_NO_SUPPORT;
			}
			*pu8_resp_len = (uint8_t)(u16_resp_length >> 8);
			*(++pu8_resp_len) = (uint8_t)(u16_resp_length & 0xFF);

			/* Calculate reply frame size in bytes */
			*pu16_reply_len = pu8_out - pu8_buf_out + 1;
		}
	}

	return res;
}



