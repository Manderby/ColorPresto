
#include "../mainC.h"



CP_PROTOTYPE(NASpace);

typedef struct CPHSVHSLColorController CPHSVHSLColorController;

CPHSVHSLColorController* cmAllocHSVHSLColorController(void);
void cmDeallocHSVHSLColorController(CPHSVHSLColorController* con);

const void* cmGetHSVHSLColorControllerColorData(const CPHSVHSLColorController* con);
void cmSetHSVHSLColorControllerColorData(CPHSVHSLColorController* con, const void* data);

void cmUpdateHSVHSLColorController(CPHSVHSLColorController* con);

