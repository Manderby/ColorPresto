
#ifdef __cplusplus
  extern "C"{
#endif

#include "mainC.h"



CM_PROTOTYPE(NASpace);

typedef struct CMLuvColorController CMLuvColorController;

CMLuvColorController* cmAllocLuvColorController(void);
void cmDeallocLuvColorController(CMLuvColorController* con);

const void* cmGetLuvColorControllerColorData(const CMLuvColorController* con);
void cmSetLuvColorControllerColorData(CMLuvColorController* con, const void* data);

void cmUpdateLuvColorController(CMLuvColorController* con);

#ifdef __cplusplus
  }
#endif
