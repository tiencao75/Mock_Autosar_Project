#ifndef NVM_H
#define NVM_H

#include "Compiler.h"    // Thêm Compiler.h
#include "Std_Types.h"   // Kiểu dữ liệu chuẩn AUTOSAR

#define NVM_E_PARAM_BLOCK_ID 0x01  /* Example error code for invalid block ID */
/* Định nghĩa mã DTC dưới dạng hex */
#define B1C02 0x1C02  /* Engine Temperature Sensor Signal Out of Range */
#define B1C03 0x1C03  /* Engine Temperature Sensor No Response */
#define U1001 0x1001  /* Lost Communication with Engine Temperature Sensor via CAN */
#define U1002 0x1002  /* Lost Communication with Actuator ECU via CAN */
#define C1E01 0x1E01  /* Cooling System ECU Memory Failure */

#define MAX_ERRORS 5
typedef uint16 Nvm_BockIdType;
typedef uint16 Nvm_DataBuffer_Type;

typedef struct {
    Nvm_BockIdType BlockId;
    Nvm_DataBuffer_Type DataBuffer;
} Nvm_Error_Type;

FUNC(Std_ReturnType, NVM_CODE) NvM_ReadBlock(VAR(uint16 , NvM_BlockIdType) BlockId, 
                                P2VAR(void, AUTOMATIC, NVM_APPL_DATA) DataBuffer);
FUNC(Std_ReturnType, NVM_CODE) NvM_WriteBlock(VAR(uint16 , NvM_BlockIdType) BlockId, 
                                CONSTP2VAR(void, AUTOMATIC, NVM_APPL_DATA) DataBuffer);

#endif /* NVM_H */