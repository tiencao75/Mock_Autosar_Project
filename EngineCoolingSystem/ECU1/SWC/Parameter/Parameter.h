#ifndef PARAMETER_H
#define PARAMETER_H

#include "Common/Std_Types.h"
#include "Common/Compiler.h"
#include "Common/Compiler_Cfg.h"

/*----------------------------------------------------------------------------*/
/* API Declarations                                                           */
/*----------------------------------------------------------------------------*/

/* API cung cấp dữ liệu hiệu chỉnh */
FUNC(void, RTE_CODE) ProvideCalibrationData(void);

#endif /* PARAMETER_H */
