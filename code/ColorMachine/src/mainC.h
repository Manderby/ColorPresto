
#define CM_PROTOTYPE(type) typedef struct type type

CM_PROTOTYPE(CMLColorMachine);

CM_PROTOTYPE(CMColorController);
CM_PROTOTYPE(CMHSLColorController);


#ifdef __cplusplus
  extern "C"{
#endif


#include "CML.h"
#include "NABase.h"


void showThreeDee(void);
void showMetamerics(void);

CMLColorMachine* cmGetCurrentColorMachine(void);
CMLColorMachine* cmGetCurrentScreenMachine(void);

void cmUpdateColor(void);
void cmUpdateMachine(void);

void cmSetCurrentColorController(const CMColorController* con);
const CMColorController* cmGetCurrentColorController(void);

const float* cmGetCurrentColorData(void);
CMLColorType cmGetCurrentColorType(void);

void cmUpdateMetamerics(void);

double cmGetUIScaleFactorForWindow(void* nativeWindowPtr);

void fillRGBFloatArrayWithArray(const CMLColorMachine* cm, const CMLColorMachine* sm, float* texdata, const float* inputarray, CMLColorType inputColorType, CMLNormedConverter normedConverter, size_t count, NABool drawgridlines, NABool drawmask);


#ifdef __cplusplus
  }
#endif
