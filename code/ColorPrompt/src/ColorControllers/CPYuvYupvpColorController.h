
#include "../mainC.h"



CP_PROTOTYPE(NASpace);

typedef struct CPYuvYupvpColorController CPYuvYupvpColorController;

CPYuvYupvpColorController* cpAllocYuvColorController(void);
void cpDeallocYuvColorController(CPYuvYupvpColorController* con);

const void* cpGetYuvColorControllerColorData(const CPYuvYupvpColorController* con);
void cpSetYuvColorControllerColorData(CPYuvYupvpColorController* con, const void* data);

void cpUpdateYuvColorController(CPYuvYupvpColorController* con);
