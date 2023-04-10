
#include "../mainC.h"



CM_PROTOTYPE(NASpace);

typedef struct CMYuvYupvpColorController CMYuvYupvpColorController;

CMYuvYupvpColorController* cmAllocYuvColorController(void);
void cmDeallocYuvColorController(CMYuvYupvpColorController* con);

const void* cmGetYuvColorControllerColorData(const CMYuvYupvpColorController* con);
void cmSetYuvColorControllerColorData(CMYuvYupvpColorController* con, const void* data);

void cmUpdateYuvColorController(CMYuvYupvpColorController* con);
