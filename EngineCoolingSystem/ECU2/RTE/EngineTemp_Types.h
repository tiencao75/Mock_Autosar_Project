#ifndef ENGINETEMP_TYPES_H
#define ENGINETEMP_TYPES_H

#include "Std_Types.h"
#include "Compiler.h"

typedef struct {
    VAR(uint16, AUTOMATIC) fanSpeed;
    VAR(uint16, AUTOMATIC) pumpSpeed;
    VAR(uint8, AUTOMATIC) warningStatus;
} EngineTemp_ControlDataType;

#endif /* ENGINETEMP_TYPES_H */