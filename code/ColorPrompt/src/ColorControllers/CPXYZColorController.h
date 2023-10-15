
#include "../mainC.h"



CM_PROTOTYPE(NASpace);

typedef struct CPXYZColorController CPXYZColorController;

CPXYZColorController* cmAllocXYZColorController(void);
void cmDeallocXYZColorController(CPXYZColorController* con);

const void* cmGetXYZColorControllerColorData(const CPXYZColorController* con);
void cmSetXYZColorControllerColorData(CPXYZColorController* con, const void* data);

void cmUpdateXYZColorController(CPXYZColorController* con);

