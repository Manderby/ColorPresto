
#define CP_PROTOTYPE(type) typedef struct type type

#define cpError naError

CP_PROTOTYPE(CMLColorMachine);

CP_PROTOTYPE(CPColorController);
CP_PROTOTYPE(CPHSLColorController);


#include "CML.h"
#include "NABase.h"




void cpSetCurrentColorController(const CPColorController* con);
const CPColorController* cpGetCurrentColorController(void);

const float* cpGetCurrentColorData(void);
CMLColorType cpGetCurrentColorType(void);


double cpGetUIScaleFactorForWindow(void* nativeWindowPtr);

void fillRGBFloatArrayWithArray(const CMLColorMachine* cm, const CMLColorMachine* sm, float* texdata, const float* inputarray, CMLColorType inputColorType, CMLNormedConverter normedConverter, size_t count);


