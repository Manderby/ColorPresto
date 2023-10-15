
#include "../mainC.h"



CP_PROTOTYPE(NASpace);

typedef struct CPLuvUVWColorController CPLuvUVWColorController;

CPLuvUVWColorController* cmAllocLuvUVWColorController(void);
void cmDeallocLuvUVWColorController(CPLuvUVWColorController* con);

const void* cmGetLuvUVWColorControllerColorData(const CPLuvUVWColorController* con);
void cmSetLuvUVWColorControllerColorData(CPLuvUVWColorController* con, const void* data);

void cmUpdateLuvUVWColorController(CPLuvUVWColorController* con);

