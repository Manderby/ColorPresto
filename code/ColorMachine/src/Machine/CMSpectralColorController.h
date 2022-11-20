
#ifdef __cplusplus
  extern "C"{
#endif

#include "mainC.h"



CM_PROTOTYPE(NASpace);

typedef struct CMSpectralColorController CMSpectralColorController;

CMSpectralColorController* cmAllocSpectralColorController(void);
void cmDeallocSpectralColorController(CMSpectralColorController* con);

const void* cmGetSpectralColorControllerColorData(const CMSpectralColorController* con);
void cmSetSpectralColorControllerColorData(CMSpectralColorController* con, const void* data);

void cmUpdateSpectralColorController(CMSpectralColorController* con);

#ifdef __cplusplus
  }
#endif
