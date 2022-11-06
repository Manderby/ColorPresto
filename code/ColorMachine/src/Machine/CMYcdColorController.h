
#ifdef __cplusplus
  extern "C"{
#endif

#include "mainC.h"



CM_PROTOTYPE(NASpace);

typedef struct CMYcdColorController CMYcdColorController;

CMYcdColorController* cmAllocYcdColorController(void);
void cmDeallocYcdColorController(CMYcdColorController* con);

const void* cmGetYcdColorControllerColorData(const CMYcdColorController* con);
void cmSetYcdColorControllerColorData(CMYcdColorController* con, const void* data);

void cmUpdateYcdColorController(CMYcdColorController* con);

#ifdef __cplusplus
  }
#endif
