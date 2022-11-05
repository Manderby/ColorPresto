
#ifdef __cplusplus
  extern "C"{
#endif

#include "mainC.h"



CM_PROTOTYPE(NASpace);

typedef struct CMRGBColorController CMRGBColorController;

CMRGBColorController* cmAllocRGBColorController(void);
void cmDeallocRGBColorController(CMRGBColorController* con);

const void* cmGetRGBColorControllerColorData(const CMRGBColorController* con);
void cmSetRGBColorControllerColorData(CMRGBColorController* con, const void* data);

void cmUpdateRGBColorController(CMRGBColorController* con);

#ifdef __cplusplus
  }
#endif
