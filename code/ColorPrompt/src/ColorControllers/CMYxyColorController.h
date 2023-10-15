
#include "../mainC.h"



CM_PROTOTYPE(NASpace);

typedef struct CMYxyColorController CMYxyColorController;

CMYxyColorController* cmAllocYxyColorController(void);
void cmDeallocYxyColorController(CMYxyColorController* con);

const void* cmGetYxyColorControllerColorData(const CMYxyColorController* con);
void cmSetYxyColorControllerColorData(CMYxyColorController* con, const void* data);

void cmUpdateYxyColorController(CMYxyColorController* con);

