
#include "../mainC.h"



CM_PROTOTYPE(NASpace);

typedef struct CPSpectralColorController CPSpectralColorController;

CPSpectralColorController* cmAllocSpectralColorController(void);
void cmDeallocSpectralColorController(CPSpectralColorController* con);

const void* cmGetSpectralColorControllerColorData(const CPSpectralColorController* con);
void cmSetSpectralColorControllerColorData(CPSpectralColorController* con, const void* data);

void cmUpdateSpectralColorController(CPSpectralColorController* con);
