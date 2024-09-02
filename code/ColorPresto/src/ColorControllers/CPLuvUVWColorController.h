
#include "../mainC.h"



CP_PROTOTYPE(NASpace);

typedef struct CPLuvUVWColorController CPLuvUVWColorController;

CPLuvUVWColorController* cpAllocLuvUVWColorController(void);
void cpDeallocLuvUVWColorController(CPLuvUVWColorController* con);

const void* cpGetLuvUVWColorControllerColorData(const CPLuvUVWColorController* con);
void cpSetLuvUVWColorControllerColorData(CPLuvUVWColorController* con, const void* data);

void cpComputeLuvUVWColorController(CPLuvUVWColorController* con);
void cpUpdateLuvUVWColorController(CPLuvUVWColorController* con);

