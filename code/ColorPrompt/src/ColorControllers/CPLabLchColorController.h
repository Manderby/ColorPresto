
#include "../mainC.h"



CM_PROTOTYPE(NASpace);

typedef struct CPLabLchColorController CPLabLchColorController;

CPLabLchColorController* cmAllocLabLchColorController(void);
void cmDeallocLabLchColorController(CPLabLchColorController* con);

const void* cmGetLabLchColorControllerColorData(const CPLabLchColorController* con);
void cmSetLabLchColorControllerColorData(CPLabLchColorController* con, const void* data);

void cmUpdateLabLchColorController(CPLabLchColorController* con);

