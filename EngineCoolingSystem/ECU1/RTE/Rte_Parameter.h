#ifndef RTE_PARAMETER_H
#define RTE_PARAMETER_H

#include "Std_Types.h"
#include "Compiler.h"
#include "Compiler_Cfg.h"

/*----------------------------------------------------------------------------*/
/* API Declarations                                                           */
/*----------------------------------------------------------------------------*/
extern uint16 CalibrationDataEngine;  //  giá trị hiệu chỉnh cho nhiệt độ động cơ 
extern uint16 CalibrationDataAir;     // giá trị hiệu chỉnh cho nhiệt độ không khí
/* API để ghi dữ liệu hiệu chỉnh */
FUNC(Std_ReturnType, RTE_CODE)
Rte_Write_PP_Parameter_ProvideCalibrationData(P2VAR(uint16, AUTOMATIC, RTE_APPL_DATA) calibrationDataEngine, 
                                             P2VAR(uint16, AUTOMATIC, RTE_APPL_DATA) calibrationDataAir);
FUNC(void, RTE_CODE) Rte_Call_PP_Calibration_CalibrationData(void);
#endif /* RTE_PARAMETER_H */
