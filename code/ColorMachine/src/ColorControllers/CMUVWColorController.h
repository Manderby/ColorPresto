
#ifdef __cplusplus
  extern "C"{
#endif

#include "mainC.h"



CM_PROTOTYPE(NASpace);

typedef struct CMUVWColorController CMUVWColorController;

CMUVWColorController* cmAllocUVWColorController(void);
void cmDeallocUVWColorController(CMUVWColorController* con);

const void* cmGetUVWColorControllerColorData(const CMUVWColorController* con);
void cmSetUVWColorControllerColorData(CMUVWColorController* con, const void* data);

void cmUpdateUVWColorController(CMUVWColorController* con);

#ifdef __cplusplus
  }
#endif
