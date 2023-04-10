
#include "../mainC.h"



CM_PROTOTYPE(NASpace);

typedef struct CMLuvUVWColorController CMLuvUVWColorController;

CMLuvUVWColorController* cmAllocLuvUVWColorController(void);
void cmDeallocLuvUVWColorController(CMLuvUVWColorController* con);

const void* cmGetLuvUVWColorControllerColorData(const CMLuvUVWColorController* con);
void cmSetLuvUVWColorControllerColorData(CMLuvUVWColorController* con, const void* data);

void cmUpdateLuvUVWColorController(CMLuvUVWColorController* con);

