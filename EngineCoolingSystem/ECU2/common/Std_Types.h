/**
 *
 * \brief Electric Memory Seat
 * \author Group1B
 *
 */

#ifndef STD_TYPES_H
#define STD_TYPES_H

#include <stdint.h>

/* Platform Types */

typedef signed char         sint8;
typedef unsigned char       uint8;
typedef signed short        sint16;
typedef unsigned short      uint16;
typedef signed long         sint32;
typedef unsigned long       uint32;
typedef float               float32;
typedef double              float64;
typedef unsigned char       boolean;
typedef uint16 PduIdType;


typedef uint16 Com_SignalIdType;
/* Định nghĩa Std_VersionInfoType theo AUTOSAR */
typedef struct {
    uint16 vendorID;         /* ID của nhà cung cấp */
    uint16 moduleID;         /* ID của module */
    uint8 sw_major_version;  /* Phiên bản phần mềm chính */
    uint8 sw_minor_version;  /* Phiên bản phần mềm phụ */
    uint8 sw_patch_version;  /* Phiên bản phần mềm vá lỗi */
} Std_VersionInfoType;

/* AUTOSAR Types */
typedef uint8 Std_ReturnType;

/* Message Types */
typedef struct {
    uint16 fanSpeed;       // Tín hiệu tốc độ quạt
    uint16 pumpSpeed;      // Tín hiệu tốc độ bơm
    uint8 warningStatus;   // Tín hiệu trạng thái đèn cảnh báo
} MessageType;


/* AUTOSAR Defines */
#define TRUE      			1U
#define FALSE     			0U
#define E_NOT_OK    		1U
#define E_OK      			0U
#define STD_HIGH    		1U
#define STD_LOW     		0U
#define E_OK			    0U
#define E_NOK		    	1U

#endif /* STD_TYPE_H */
