
#include "../mainC.h"



CM_PROTOTYPE(NASpace);

typedef struct CMGrayColorController CMGrayColorController;

CMGrayColorController* cmAllocGrayColorController(void);
void cmDeallocGrayColorController(CMGrayColorController* con);

const void* cmGetGrayColorControllerColorData(const CMGrayColorController* con);
void cmSetGrayColorControllerColorData(CMGrayColorController* con, const void* data);

void cmUpdateGrayColorController(CMGrayColorController* con);


