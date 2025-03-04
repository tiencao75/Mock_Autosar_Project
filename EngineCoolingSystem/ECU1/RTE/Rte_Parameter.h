#ifndef RTE_PARAMETER_H
#define RTE_PARAMETER_H

#include "Std_Types.h"
#include "Compiler.h"
#include "Compiler_Cfg.h"

/*----------------------------------------------------------------------------*/
/* API Declarations                                                           */
/*----------------------------------------------------------------------------*/

/* API để ghi dữ liệu hiệu chỉnh */
FUNC(Std_ReturnType, RTE_CODE)
Rte_Write_PP_Parameter_ProvideCalibrationData(P2VAR(uint16, AUTOMATIC, RTE_APPL_DATA) calibrationData);

#endif /* RTE_PARAMETER_H */
