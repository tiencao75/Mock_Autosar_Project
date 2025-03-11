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
/* �?nh nghia Std_VersionInfoType theo AUTOSAR */
typedef struct {
    uint16 vendorID;         /* ID c?a nh� cung c?p */
    uint16 moduleID;         /* ID c?a module */
    uint8 sw_major_version;  /* Phi�n b?n ph?n m?m ch�nh */
    uint8 sw_minor_version;  /* Phi�n b?n ph?n m?m ph? */
    uint8 sw_patch_version;  /* Phi�n b?n ph?n m?m v� l?i */
} Std_VersionInfoType;

/* AUTOSAR Types */
typedef uint8 Std_ReturnType;

/* Message Types */
typedef struct {
    uint16 fanSpeed;       // T�n hi?u t?c d? qu?t
    uint16 pumpSpeed;      // T�n hi?u t?c d? bom
    uint8 warningStatus;   // T�n hi?u tr?ng th�i d�n c?nh b�o
} MessageType;

// �?nh nghia c?u tr�c d? g?p d? li?u FanSpeed, PumpSpeed v� warningStatus
typedef struct {
    uint16 FanSpeed;      // Gi? s? FanSpeed l� uint16, di?u ch?nh n?u c?n
    uint16 PumpSpeed;     // Gi? s? PumpSpeed l� uint16, di?u ch?nh n?u c?n
    uint8 warningStatus;  // Gi? s? warningStatus l� uint8 (v� d?: 0 = OK, 1 = Warning), di?u ch?nh n?u c?n
} CombinedSignalDataType;


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
