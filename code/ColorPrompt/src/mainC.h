
#define CM_PROTOTYPE(type) typedef struct type type

#define cmError naError

CM_PROTOTYPE(CMLColorMachine);

CM_PROTOTYPE(CMColorController);
CM_PROTOTYPE(CMHSLColorController);


#include "CML.h"
#include "NABase.h"




void cmSetCurrentColorController(const CMColorController* con);
const CMColorController* cmGetCurrentColorController(void);

const float* cmGetCurrentColorData(void);
CMLColorType cmGetCurrentColorType(void);


double cmGetUIScaleFactorForWindow(void* nativeWindowPtr);

void fillRGBFloatArrayWithArray(const CMLColorMachine* cm, const CMLColorMachine* sm, float* texdata, const float* inputarray, CMLColorType inputColorType, CMLNormedConverter normedConverter, size_t count);


