
#ifdef __cplusplus
  extern "C"{
#endif

#include "mainC.h"



CM_PROTOTYPE(NASpace);

typedef struct CMYCbCrColorController CMYCbCrColorController;

CMYCbCrColorController* cmAllocYCbCrColorController(void);
void cmDeallocYCbCrColorController(CMYCbCrColorController* con);

const void* cmGetYCbCrColorControllerColorData(const CMYCbCrColorController* con);
void cmSetYCbCrColorControllerColorData(CMYCbCrColorController* con, const void* data);

void cmUpdateYCbCrColorController(CMYCbCrColorController* con);

#ifdef __cplusplus
  }
#endif
