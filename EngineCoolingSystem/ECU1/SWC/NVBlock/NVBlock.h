#ifndef NVBLOCK_H
#define NVBLOCK_H

#include "Common/Std_Types.h"
#include "Common/Compiler.h"
#include "Common/Compiler_Cfg.h"

/*----------------------------------------------------------------------------*/
/* API Declarations                                                           */
/*----------------------------------------------------------------------------*/

/* API ghi lỗi vào NVM */
FUNC(void, RTE_CODE) HandleErrorToNVM(void);


#endif /* NVBLOCK_H */
