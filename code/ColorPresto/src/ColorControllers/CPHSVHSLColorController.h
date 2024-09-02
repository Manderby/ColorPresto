
#include "../mainC.h"



CP_PROTOTYPE(NASpace);

typedef struct CPHSVHSLColorController CPHSVHSLColorController;

CPHSVHSLColorController* cpAllocHSVHSLColorController(void);
void cpDeallocHSVHSLColorController(CPHSVHSLColorController* con);

const void* cpGetHSVHSLColorControllerColorData(const CPHSVHSLColorController* con);
void cpSetHSVHSLColorControllerColorData(CPHSVHSLColorController* con, const void* data);

void cpComputeHSVHSLColorController(CPHSVHSLColorController* con);
void cpUpdateHSVHSLColorController(CPHSVHSLColorController* con);

