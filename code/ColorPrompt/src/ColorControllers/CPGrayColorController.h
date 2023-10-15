
#include "../mainC.h"



CP_PROTOTYPE(NASpace);

typedef struct CPGrayColorController CPGrayColorController;

CPGrayColorController* cmAllocGrayColorController(void);
void cmDeallocGrayColorController(CPGrayColorController* con);

const void* cmGetGrayColorControllerColorData(const CPGrayColorController* con);
void cmSetGrayColorControllerColorData(CPGrayColorController* con, const void* data);

void cmUpdateGrayColorController(CPGrayColorController* con);


