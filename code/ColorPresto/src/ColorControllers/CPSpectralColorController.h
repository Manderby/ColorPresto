
#include "../main.h"



CP_PROTOTYPE(NASpace);

typedef struct CPSpectralColorController CPSpectralColorController;

CPSpectralColorController* cpAllocSpectralColorController(void);
void cpDeallocSpectralColorController(CPSpectralColorController* con);

const void* cpGetSpectralColorControllerColorData(const CPSpectralColorController* con);
void cpSetSpectralColorControllerColorData(CPSpectralColorController* con, const void* data);

void cpComputeSpectralColorController(CPSpectralColorController* con);
void cpUpdateSpectralColorController(CPSpectralColorController* con);
