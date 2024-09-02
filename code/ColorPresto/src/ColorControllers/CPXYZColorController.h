
#include "../mainC.h"



CP_PROTOTYPE(NASpace);

typedef struct CPXYZColorController CPXYZColorController;

CPXYZColorController* cpAllocXYZColorController(void);
void cpDeallocXYZColorController(CPXYZColorController* con);

const void* cpGetXYZColorControllerColorData(const CPXYZColorController* con);
void cpSetXYZColorControllerColorData(CPXYZColorController* con, const void* data);

void cpComputeXYZColorController(CPXYZColorController* con);
void cpUpdateXYZColorController(CPXYZColorController* con);

