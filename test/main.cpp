/*
 * main.cpp
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
  * 2019-09-30
 * Initial tests for reading holding register
 */

#define CATCH_CONFIG_MAIN
#include "catch.hpp"

/* Place in own namespace */
#include "../src/modbus_tcp.c"

using namespace std;

uint16_t holding_register[10000];
bool check_1234_reg_on_read = false;
bool hit_1234_reg_on_read = false;

/* Callback functions for reading and writing holding register */
mbt_ret_type MBT_BeginReadHoldingRegister(uint16_t u16_address, uint8_t slave, void **pAny) {
	if ( pAny ) {
		 *pAny = MBT_MALLOC(sizeof(uint16_t));
		 *((uint16_t*)(*pAny)) = 1234;  /* Test for passing parameters from BeginRead... to Read... and EndRead... */
	}
	return MBT_OK;
}

mbt_ret_type MBT_EndReadHoldingRegister(void **pAny) {
	if ( pAny != NULL ) {
		if ( *pAny != NULL ) {
			MBT_FREE(*pAny);
		}
	}
	return MBT_OK;
}

mbt_ret_type MBT_ReadHoldingRegister(uint16_t u16_address, uint8_t slave, uint16_t *pu16_data, void *pAny) {
    if ( check_1234_reg_on_read ) {
        if ( u16_address == *((uint16_t*)pAny) ) {
            hit_1234_reg_on_read = true;
        }
    }
	if ( u16_address <= 9999 ) {
        *pu16_data = holding_register[u16_address];
        return MBT_OK;
	} else {
        *pu16_data = 0;
        return MBT_ERR;
	}
}

mbt_ret_type MBT_BeginWriteHoldingRegister(uint16_t u16_address, uint8_t slave, void **pAny) {
	*pAny = MBT_MALLOC(sizeof(void*));
	*pAny = NULL;
	return MBT_OK;
}

mbt_ret_type MBT_EndWriteHoldingRegister(void **pAny) {
	if ( pAny != NULL ) {
		MBT_FREE(*pAny);
	}
	return MBT_OK;
}

mbt_ret_type MBT_WriteHoldingRegister(uint16_t u16_address, uint16_t value, uint8_t slave, void *pAny) {
    if ( u16_address <= 9999 ) {
        holding_register[u16_address] = value;
        return MBT_OK;
	} else {
        return MBT_ERR;
	}
}


/*Helper functions*/

uint8_t buffer[MBT_BUFFER_SIZE];
uint8_t response[MBT_BUFFER_SIZE];

#ifdef MBT_SUPPORT_HOLDING_REG

uint16_t build_frame_read_holding(uint16_t transmission, uint16_t from, uint16_t length, uint8_t slave) {
    buffer[0] = (uint8_t)(transmission >> 8);
    buffer[1] = (uint8_t)(transmission & 0xFF);

    buffer[2] = 0;
    buffer[3] = 0;

    buffer[4] = 0;
    buffer[5] = 6;


    buffer[6] = slave;

    buffer[7] = 3;

    buffer[8] = (uint8_t)(from >> 8);
    buffer[9] = (uint8_t)(from & 0xFF);

    buffer[10] = (uint8_t)(length >> 8);
    buffer[11] = (uint8_t)(length & 0xFF);

    return 12;
}
#ifdef EXCESSIVE_READ_TEST
TEST_CASE( "Check read holding register", "[read_holding_correct_params]" ) {

    {
        //Init all the register with a random number and buffer it locally
        uint16_t local_buf[10000];
        for ( int i=0; i<10000; ++i) {
            uint16_t r = std::rand() / RAND_MAX * 65535;
            holding_register[i] = r;
            local_buf[i] = r;
        }

        uint16_t len;
        uint16_t reply_len;

        uint16_t transmission;
        uint16_t from;
        uint16_t length;
        uint16_t slave;
        mbt_ret_type res;


            for ( from=0; from<9999; from++ ) {
                cout << "From " << from << " out of 9998\r";
                int max_len = 9999 - from + 1;
                if ( max_len > 123 ) {
                    max_len = 123;
                }
                for ( length = 1; length <= max_len; ++length ) {
                        transmission = std::rand() / RAND_MAX * 65535;
                        slave = std::rand() / RAND_MAX * 255;
                        len = build_frame_read_holding(transmission, from, length, slave);
                        res = ModBUS_TCP_handler(buffer, len, response, MBT_BUFFER_SIZE, &reply_len);
                        REQUIRE(res == MBT_OK);
                        REQUIRE(reply_len == 8 + 1 + length*2);
                        /* Check if transaction number is correct */
                        REQUIRE(response[0] == (transmission >> 8));
                        REQUIRE(response[1] == (transmission & 0xFF));
                        /* Check if protocol ID is 0x0000 */
                        REQUIRE(response[2] == 0 );
                        REQUIRE(response[3] == 0 );
                        /* Check if response length field is correct */
                        REQUIRE(response[4] == ((2+1+length*2) >> 8 ));
                        REQUIRE(response[5] == ((2+1+length*2) & 0xFF));
                        /* Check if slave id is correct */
                        REQUIRE(response[6] == slave );
                        /* Check if function code is correct (3 = read holding register) */
                        REQUIRE(response[7] == 3 );
                        /* Check if response length in bytes is correct */
                        REQUIRE(response[8] == length*2);

                        for ( int i=0; i<length; i++ ) {
                            REQUIRE(response[9+2*i] == (local_buf[from+i] >> 8));
                            REQUIRE(response[9+2*i+1] == (local_buf[from+i] & 0xFF));
                            REQUIRE(local_buf[from+i] == holding_register[from+i]);
                        }
                }
            }

    }
}
#endif

TEST_CASE( "Check read holding register with wrong parameter", "[read_holding_wrong_params]" ) {
    /* Transmission does not matter, it will be returned */
    const uint16_t transmission = 0xA5A5;
    /* Slave does not matter, it will be returned */
    const uint8_t slave = 0;

    /*Parameters, which can be wrong */
    uint16_t from;  /* Start address */
    uint16_t length; /* Read len */
    uint16_t out_buf_len; /* Output buffer length */

    /* Needed for response */
    uint8_t response[MBT_BUFFER_SIZE];
    mbt_ret_type res;
    uint16_t reply_len;

    /* This should be a valid request */
    from = 3;
    length = 2;
    out_buf_len = MBT_BUFFER_SIZE;


    uint16_t len;

    SECTION("Verify with known-good-frame before") {
        len = build_frame_read_holding(transmission, from, length, slave);
        res = ModBUS_TCP_handler(buffer, len, response, out_buf_len, &reply_len);
        REQUIRE(res == MBT_OK);
    }


    SECTION("Setting pointer parameters to NULL") {
        /* Input and/or output buffer == NULL */
        len = build_frame_read_holding(transmission, from, length, slave);
        res = ModBUS_TCP_handler(NULL, len, response, out_buf_len, &reply_len);
        REQUIRE(res == MBT_ERR);

        len = build_frame_read_holding(transmission, from, length, slave);
        res = ModBUS_TCP_handler(buffer, len, NULL, out_buf_len, &reply_len);
        REQUIRE(res == MBT_ERR);

        len = build_frame_read_holding(transmission, from, length, slave);
        res = ModBUS_TCP_handler(NULL, len, NULL, out_buf_len, &reply_len);
        REQUIRE(res == MBT_ERR);

        /* Reply len == NULL */
        len = build_frame_read_holding(transmission, from, length, slave);
        res = ModBUS_TCP_handler(buffer, len, response, out_buf_len, NULL);
        REQUIRE(res == MBT_ERR);
    }

    SECTION("Wrong protocol identifier") {
        /* Modify protocol ID, should give a MBT_FRAME_ERR */
        len = build_frame_read_holding(transmission, from, length, slave);
        buffer[2] = 0x01;
        res = ModBUS_TCP_handler(buffer, len, response, out_buf_len, &reply_len);
        REQUIRE(res == MBT_FRAME_ERR);
        buffer[2] = 0x00;
    }

    SECTION("Wrong input buffer size") {
        /* Input buffer too small for header */
        len = build_frame_read_holding(transmission, from, length, slave);
        res = ModBUS_TCP_handler(buffer, 8, response, out_buf_len, &reply_len);
        REQUIRE(res == MBT_ERR);

        /* Input buffer too small compared with length field */
        len = build_frame_read_holding(transmission, from, length, slave);
        res = ModBUS_TCP_handler(buffer, len-1, response, out_buf_len, &reply_len);
        REQUIRE(res == MBT_FRAME_ERR);
    }

    SECTION("Wrong output buffer size") {
        /* Need two test cases for output buffer.
         * 1: Too small in general for 8 byte header
         * 2: Too small for response */

        /* Output buffer too small for header */
        len = build_frame_read_holding(transmission, from, length, slave);
        res = ModBUS_TCP_handler(buffer, len, response, 8-1, &reply_len);
        REQUIRE(res == MBT_OUT_BUF_ERR);

        /* Output buffer big enough for header, but not for response */
        len = build_frame_read_holding(transmission, from, length, slave);
        res = ModBUS_TCP_handler(buffer, len, response, (8 + 1 + 2*length) - 1, &reply_len);
        REQUIRE(res == MBT_OUT_BUF_ERR);

        /* Output buffer matches exactly the response length */
        len = build_frame_read_holding(transmission, from, length, slave);
        res = ModBUS_TCP_handler(buffer, len, response, 8 + 1 + 2*length, &reply_len);
        REQUIRE(res == MBT_OK);
        REQUIRE(reply_len == (8+1+2*length));   /* And validate that the reply is also counted the right way */
    }

    SECTION("Wrong reading length") {
        /* Attempt to read to many register at once */
        len = build_frame_read_holding(transmission, from, 124, slave);
        res = ModBUS_TCP_handler(buffer, len, response, MBT_BUFFER_SIZE, &reply_len);
        REQUIRE(res == MBT_FRAME_ERR);

        /* Attempt to read to read out of bounce */
        len = build_frame_read_holding(transmission, 9995, 7, slave);
        res = ModBUS_TCP_handler(buffer, len, response, MBT_BUFFER_SIZE, &reply_len);
        REQUIRE(res == MBT_ERR_READING_REG);
    }

}

/*Pointer passing is implemented in BeginRead... Read... and EndRead... */
TEST_CASE( "Check read holding register pointer passing", "[read_holding_pointer]" ) {
    check_1234_reg_on_read = true;

    /* Needed for response */
    uint8_t response[MBT_BUFFER_SIZE];
    mbt_ret_type res;
    uint16_t reply_len;
    uint16_t len;

    SECTION("Check hit on register") {
        hit_1234_reg_on_read = false;
        len = build_frame_read_holding(0xAFFE, 1230, 10, 2);
        res = ModBUS_TCP_handler(buffer, len, response, MBT_BUFFER_SIZE, &reply_len);
        REQUIRE(res == MBT_OK);
        REQUIRE(hit_1234_reg_on_read == true);
    }

    SECTION("Check no-hit on register") {
        hit_1234_reg_on_read = false;
        len = build_frame_read_holding(0xAFFE, 1230, 4, 2); /* Read 4 regs starting from 1230 */
        res = ModBUS_TCP_handler(buffer, len, response, MBT_BUFFER_SIZE, &reply_len);
        REQUIRE(res == MBT_OK);
        REQUIRE(hit_1234_reg_on_read == false);
    }

}

#endif /*MBT_SUPPORT_HOLDING_REG*/
