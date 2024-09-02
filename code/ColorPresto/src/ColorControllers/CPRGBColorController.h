
#include "../mainC.h"



CP_PROTOTYPE(NASpace);

typedef struct CPRGBColorController CPRGBColorController;

CPRGBColorController* cpAllocRGBColorController(void);
void cpDeallocRGBColorController(CPRGBColorController* con);

const void* cpGetRGBColorControllerColorData(const CPRGBColorController* con);
void cpSetRGBColorControllerColorData(CPRGBColorController* con, const void* data);

void cpComputeRGBColorController(CPRGBColorController* con);
void cpUpdateRGBColorController(CPRGBColorController* con);

