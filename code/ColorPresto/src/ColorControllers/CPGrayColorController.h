
#include "../main.h"



CP_PROTOTYPE(NASpace);

typedef struct CPGrayColorController CPGrayColorController;

CPGrayColorController* cpAllocGrayColorController(void);
void cpDeallocGrayColorController(CPGrayColorController* con);

const void* cpGetGrayColorControllerColorData(const CPGrayColorController* con);
void cpSetGrayColorControllerColorData(CPGrayColorController* con, const void* data);

void cpComputeGrayColorController(CPGrayColorController* con);
void cpUpdateGrayColorController(CPGrayColorController* con);


