
#include "../mainC.h"



CM_PROTOTYPE(NASpace);

typedef struct CMHSVHSLColorController CMHSVHSLColorController;

CMHSVHSLColorController* cmAllocHSVHSLColorController(void);
void cmDeallocHSVHSLColorController(CMHSVHSLColorController* con);

const void* cmGetHSVHSLColorControllerColorData(const CMHSVHSLColorController* con);
void cmSetHSVHSLColorControllerColorData(CMHSVHSLColorController* con, const void* data);

void cmUpdateHSVHSLColorController(CMHSVHSLColorController* con);

