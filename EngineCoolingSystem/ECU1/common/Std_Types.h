/**
 *
 * \brief Electric Memory Seat
 * \author Group1B
 *
 */

#ifndef STD_TYPES_H
#define STD_TYPES_H

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
typedef uint16 Com_SignalIdType;
/* Ð?nh nghia Std_VersionInfoType theo AUTOSAR */
typedef struct {
    uint16 vendorID;         /* ID c?a nhà cung c?p */
    uint16 moduleID;         /* ID c?a module */
    uint8 sw_major_version;  /* Phiên b?n ph?n m?m chính */
    uint8 sw_minor_version;  /* Phiên b?n ph?n m?m ph? */
    uint8 sw_patch_version;  /* Phiên b?n ph?n m?m vá l?i */
} Std_VersionInfoType;

/* AUTOSAR Types */
typedef uint8 Std_ReturnType;

/* Message Types */
typedef struct {
    uint16 fanSpeed;       // Tín hi?u t?c d? qu?t
    uint16 pumpSpeed;      // Tín hi?u t?c d? bom
    uint8 warningStatus;   // Tín hi?u tr?ng thái dèn c?nh báo
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

/* Test Types */
typedef struct {
    uint16 engineTemp;
    uint16 airTemp;
    uint16 FanSpeed;
    uint16 PumpSpeed;
    uint8 WarningLight;
} CoolingData;

#endif /* STD_TYPE_H */
