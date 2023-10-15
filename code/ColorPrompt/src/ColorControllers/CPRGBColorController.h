
#include "../mainC.h"



CP_PROTOTYPE(NASpace);

typedef struct CPRGBColorController CPRGBColorController;

CPRGBColorController* cmAllocRGBColorController(void);
void cmDeallocRGBColorController(CPRGBColorController* con);

const void* cmGetRGBColorControllerColorData(const CPRGBColorController* con);
void cmSetRGBColorControllerColorData(CPRGBColorController* con, const void* data);

void cmUpdateRGBColorController(CPRGBColorController* con);

