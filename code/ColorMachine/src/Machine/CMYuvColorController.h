
#ifdef __cplusplus
  extern "C"{
#endif

#include "mainC.h"



CM_PROTOTYPE(NASpace);

typedef struct CMYuvColorController CMYuvColorController;

CMYuvColorController* cmAllocYuvColorController(void);
void cmDeallocYuvColorController(CMYuvColorController* con);

const void* cmGetYuvColorControllerColorData(const CMYuvColorController* con);
void cmSetYuvColorControllerColorData(CMYuvColorController* con, const void* data);

void cmUpdateYuvColorController(CMYuvColorController* con);

#ifdef __cplusplus
  }
#endif
