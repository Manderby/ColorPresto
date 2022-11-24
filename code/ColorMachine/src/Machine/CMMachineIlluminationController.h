
#include "mainC.h"

CM_PROTOTYPE(NASpace);



typedef struct CMMachineIlluminationController CMMachineIlluminationController;

CMMachineIlluminationController* cmAllocMachineIlluminationController(void);
void cmDeallocMachineIlluminationController(CMMachineIlluminationController* con);

NASpace* cmGetMachineIlluminationControllerUIElement(CMMachineIlluminationController* con);

void cmUpdateMachineIlluminationController(CMMachineIlluminationController* con);
