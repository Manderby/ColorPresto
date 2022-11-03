
#ifdef __cplusplus
  extern "C"{
#endif

#include "mainC.h"



CM_PROTOTYPE(NASpace);

typedef struct CMHSLColorController CMHSLColorController;

CMHSLColorController* cmAllocHSLColorController(void);
void cmDeallocHSLColorController(CMHSLColorController* con);

const void* cmGetHSLColorControllerColorData(const CMHSLColorController* con);

void cmUpdateHSLColorController(CMHSLColorController* con);

#ifdef __cplusplus
  }
#endif
