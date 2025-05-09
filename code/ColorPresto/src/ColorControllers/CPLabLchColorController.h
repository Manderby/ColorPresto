
#include "../main.h"



CP_PROTOTYPE(NASpace);

typedef struct CPLabLchColorController CPLabLchColorController;

CPLabLchColorController* cpAllocLabLchColorController(void);
void cpDeallocLabLchColorController(CPLabLchColorController* con);

const void* cpGetLabLchColorControllerColorData(const CPLabLchColorController* con);
void cpSetLabLchColorControllerColorData(CPLabLchColorController* con, const void* data);

void cpComputeLabLchColorController(CPLabLchColorController* con);
void cpUpdateLabLchColorController(CPLabLchColorController* con);

