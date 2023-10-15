
#include "../mainC.h"



CM_PROTOTYPE(NASpace);

typedef struct CPYuvYupvpColorController CPYuvYupvpColorController;

CPYuvYupvpColorController* cmAllocYuvColorController(void);
void cmDeallocYuvColorController(CPYuvYupvpColorController* con);

const void* cmGetYuvColorControllerColorData(const CPYuvYupvpColorController* con);
void cmSetYuvColorControllerColorData(CPYuvYupvpColorController* con, const void* data);

void cmUpdateYuvColorController(CPYuvYupvpColorController* con);
