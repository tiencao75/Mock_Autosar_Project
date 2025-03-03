#ifndef OS_H
#define OS_H

#include "Std_Types.h"
#include <stdint.h>  
#include "Rte_EngineTemperatureControl.h"
// #include "osek.h"

/* Định nghĩa Task ID */
#define TASK_ReadSensor       0
#define TASK_ProcessData      1
#define TASK_SendData         2
#define TASK_COUNT            3

/* Định nghĩa Event ID */
#define BE_ReadSensor         (1 << 0)
#define BE_DataReady          (1 << 1)
#define BE_DataSent           (1 << 2)

/* Define EventMaskType if not already defined */
typedef uint32 EventMaskType; 

#endif /* OS_H */
