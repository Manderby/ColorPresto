
#define CM_PROTOTYPE(type) typedef struct type type

CM_PROTOTYPE(CMLColorMachine);


#ifdef __cplusplus
  extern "C"{
#endif


#include "CML.h"
#include "NABase.h"


CMLColorMachine* cmGetCurrentColorMachine(void);
CMLColorMachine* cmGetCurrentScreenMachine(void);
double cmGetUIScaleFactorForWindow(void* nativeWindowPtr);

void fillRGBFloatArrayWithArray(const CMLColorMachine* cm, const CMLColorMachine* sm, float* texdata, float* inputarray, CMLColorType inputColorType, CMLNormedConverter normedconverter, size_t count, NABool drawgridlines, NABool drawmask);


#ifdef __cplusplus
  }
#endif
