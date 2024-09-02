
#include "../mainC.h"



CP_PROTOTYPE(NASpace);

typedef struct CPYxyColorController CPYxyColorController;

CPYxyColorController* cpAllocYxyColorController(void);
void cpDeallocYxyColorController(CPYxyColorController* con);

const void* cpGetYxyColorControllerColorData(const CPYxyColorController* con);
void cpSetYxyColorControllerColorData(CPYxyColorController* con, const void* data);

void cpComputeYxyColorController(CPYxyColorController* con);
void cpUpdateYxyColorController(CPYxyColorController* con);

