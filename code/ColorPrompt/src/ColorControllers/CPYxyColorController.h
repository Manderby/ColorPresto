
#include "../mainC.h"



CP_PROTOTYPE(NASpace);

typedef struct CPYxyColorController CPYxyColorController;

CPYxyColorController* cmAllocYxyColorController(void);
void cmDeallocYxyColorController(CPYxyColorController* con);

const void* cmGetYxyColorControllerColorData(const CPYxyColorController* con);
void cmSetYxyColorControllerColorData(CPYxyColorController* con, const void* data);

void cmUpdateYxyColorController(CPYxyColorController* con);

