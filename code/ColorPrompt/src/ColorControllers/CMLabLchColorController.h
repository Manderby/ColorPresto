
#include "../mainC.h"



CM_PROTOTYPE(NASpace);

typedef struct CMLabLchColorController CMLabLchColorController;

CMLabLchColorController* cmAllocLabLchColorController(void);
void cmDeallocLabLchColorController(CMLabLchColorController* con);

const void* cmGetLabLchColorControllerColorData(const CMLabLchColorController* con);
void cmSetLabLchColorControllerColorData(CMLabLchColorController* con, const void* data);

void cmUpdateLabLchColorController(CMLabLchColorController* con);

