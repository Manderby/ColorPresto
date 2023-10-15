
#include "../mainC.h"



CP_PROTOTYPE(NASpace);

typedef struct CPYCbCrColorController CPYCbCrColorController;

CPYCbCrColorController* cmAllocYCbCrColorController(void);
void cmDeallocYCbCrColorController(CPYCbCrColorController* con);

const void* cmGetYCbCrColorControllerColorData(const CPYCbCrColorController* con);
void cmSetYCbCrColorControllerColorData(CPYCbCrColorController* con, const void* data);

void cmUpdateYCbCrColorController(CPYCbCrColorController* con);

