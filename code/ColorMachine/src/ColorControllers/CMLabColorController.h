
#include "mainC.h"



CM_PROTOTYPE(NASpace);

typedef struct CMLabColorController CMLabColorController;

CMLabColorController* cmAllocLabColorController(void);
void cmDeallocLabColorController(CMLabColorController* con);

const void* cmGetLabColorControllerColorData(const CMLabColorController* con);
void cmSetLabColorControllerColorData(CMLabColorController* con, const void* data);

void cmUpdateLabColorController(CMLabColorController* con);

