
#include "../mainC.h"



CP_PROTOTYPE(NASpace);

typedef struct CPYuvYupvpColorController CPYuvYupvpColorController;

CPYuvYupvpColorController* cpAllocYuvYupvpColorController(void);
void cpDeallocYuvYupvpColorController(CPYuvYupvpColorController* con);

const void* cpGetYuvYupvpColorControllerColorData(const CPYuvYupvpColorController* con);
void cpSetYuvYupvpColorControllerColorData(CPYuvYupvpColorController* con, const void* data);

void cpComputeYuvYupvpColorController(CPYuvYupvpColorController* con);
void cpUpdateYuvYupvpColorController(CPYuvYupvpColorController* con);
