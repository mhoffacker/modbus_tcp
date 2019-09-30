# ModBUS TCP Handler

##Functionality

The ModBUS TCP Handler library provides a handler for parsing a ModBUS TCP frame and calling user defined callback functions for reading and writing internal register.

Currently the reading and writing of holding register is implemented. The reading is already roughly tested.

The reading of input register is implemented.

Coils and discrete inputs are not yet implemented.

##Usage
The library consists of three files:

- modbus_tcp.c
- modbus_tcp.h
- modbus_tcp_config.h

To use ModBUS TCP just add these files to your project

The function

 `mbt_ret_type ModBUS_TCP_handler(uint8_t  *pu8_buf_in, uint16_t u16_buf_in_len, uint8_t *pu8_buf_out, uint16_t u16_buf_out_len, uint16_t *pu16_reply_len)`

handles the incoming TCP package and creates a response. 

- `*pu8_buf_in` Pointer to the incoming package
- `u16_buf_in_len` Length of received data (not of complete buffer)
- `*pu8_buf_out` Pointer to the outgoing package
- `u16_buf_out_len` Total length of outgoing buffer
- `*pu16_reply_len` Length of reply to be sent

Return values:

- `MBT_OK` No problem occured
- `MBT_ERR` General error
- `MBT_NO_SUPPORT` No support for the received command
- `MBT_FRAME_ERR` Error in frame data
- `MBT_OUT_BUF_ERR` Output buffer error - most likely to small
- `MBT_ERR_WRITING_REG` The callback returned an error
- `MBT_ERR_READING_REG` The callback returned an error

When receiving a read or write, the frame is parsed and the callback functions implemented by the user are called.

##Configuration
In the file modbus_tcp_config.h you can find the following configuration options:

###`MBT_USE_WEAK`
Creates weak function prototypes for all callback functions. The macro `__week` can be adapted.

###`MBT_SUPPORT_HOLDING_REG`
Enables support for reading/writing holding register

###`MBT_SUPPORT_INPUT_REG`
Enables support for reading input register

###`MBT_SUPPORT_COILS`
Enables support for reading/writing coils. Currently not implemented and will throw a error during compling.

###`MBT_SUPPORT_DISCRETE_INPUT`
Enables support for reading discrete inputs. Currently not implemented and will throw a error during compling.

###`MBT_MALLOC` and `MBT_FREE`
Definition for malloc and free on your system. E.g. in FreeRTOS you would use pvPortMalloc and vPortFree. 

`MBT_MALLOC` is currently not used.

`MBT_FREE` is used in the weak MBT_End.... function to release the `pAny` parameter (if not NULL). If no dynamic allocated memory is used, define `MBT_FREE` as empty.

##Callbacks

###Weak vs. External
If `MBT_USE_WEAK` is defined, all necessary callbacks are defined with weak attribute. You can overwrite it by defining a strong version with the same prototype. Without the weak definition, all callbacks for a particular read or write process need to be implemented, even if empty.

###Return values
On success, all callbacks must return `MBT_OK`. Every other value will be interpreted as an error.

###Reading a holding register
After the read command was decoded, the callback 

`mbt_ret_type MBT_BeginReadHoldingRegister(uint16_t u16_address, uint8_t slave, void **pAny);` 

is called. `**pAny` is a pointer to a pointer. You can define a parameter, which is passed to 

`mbt_ret_type MBT_ReadHoldingRegister(uint16_t u16_address, uint8_t slave, uint16_t *pu16_data, void *pAny);`

which is called for every address. After the last address is read

`mbt_ret_type MBT_EndReadHoldingRegister(void **pAny);` 

which has to release the memory reserved in BeginReadHoldingRegister. The weak definition performs the release. 

###Reading an input register
Same procedure as reading a holding register with prototypes

`mbt_ret_type MBT_BeginReadInputRegister(uint16_t u16_address, uint8_t slave, void **pAny);`

`mbt_ret_type MBT_ReadInputRegister(uint16_t u16_address, uint8_t slave, uint16_t *pu16_data, void *pAny);`

`mbt_ret_type MBT_EndReadInputRegister(void **pAny);`

###Writing a holding register
Same procedure as reading a holding register with prototypes

`mbt_ret_type MBT_BeginWriteHoldingRegister(uint16_t u16_address, uint8_t slave, void **pAny);`

`mbt_ret_type MBT_WriteHoldingRegister(uint16_t u16_address, uint16_t value, uint8_t slave, void *pAny);`

The difference is, that the value is passed for writing in `uin16_t value`

`mbt_ret_type MBT_EndWriteHoldingRegister(void **pAny);`

###Coils and Descrete input
The procedure is planed the same way, but not yet implemented.

##Testing
In the folder test is a small testsuite written with Catch2.

Test status:

- Reading holding register: Rougly tested - everything passed up to now.
- Writing holding register: Not tested
- Reading input register: Not tested
- Reading coils: Not implemented
- Writing coils: Not implemented
- Reading discrete input: Not implemented




