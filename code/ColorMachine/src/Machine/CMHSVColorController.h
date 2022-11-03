
#ifdef __cplusplus
  extern "C"{
#endif

#include "mainC.h"



CM_PROTOTYPE(NASpace);

typedef struct CMHSVColorController CMHSVColorController;

CMHSVColorController* cmAllocHSVColorController(void);
void cmDeallocHSVColorController(CMHSVColorController* con);

const void* cmGetHSVColorControllerColorData(const CMHSVColorController* con);

void cmUpdateHSVColorController(CMHSVColorController* con);

#ifdef __cplusplus
  }
#endif
