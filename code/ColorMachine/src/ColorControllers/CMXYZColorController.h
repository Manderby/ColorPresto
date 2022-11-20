
#ifdef __cplusplus
  extern "C"{
#endif

#include "mainC.h"



CM_PROTOTYPE(NASpace);

typedef struct CMXYZColorController CMXYZColorController;

CMXYZColorController* cmAllocXYZColorController(void);
void cmDeallocXYZColorController(CMXYZColorController* con);

const void* cmGetXYZColorControllerColorData(const CMXYZColorController* con);
void cmSetXYZColorControllerColorData(CMXYZColorController* con, const void* data);

void cmUpdateXYZColorController(CMXYZColorController* con);

#ifdef __cplusplus
  }
#endif
