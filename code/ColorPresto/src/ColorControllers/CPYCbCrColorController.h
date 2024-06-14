
#include "../mainC.h"



CP_PROTOTYPE(NASpace);

typedef struct CPYCbCrColorController CPYCbCrColorController;

CPYCbCrColorController* cpAllocYCbCrColorController(void);
void cpDeallocYCbCrColorController(CPYCbCrColorController* con);

const void* cpGetYCbCrColorControllerColorData(const CPYCbCrColorController* con);
void cpSetYCbCrColorControllerColorData(CPYCbCrColorController* con, const void* data);

void cpUpdateYCbCrColorController(CPYCbCrColorController* con);

