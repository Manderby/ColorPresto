
#include "../mainC.h"

CM_PROTOTYPE(NASpace);



typedef struct CPMachineIlluminationController CPMachineIlluminationController;

CPMachineIlluminationController* cmAllocMachineIlluminationController(void);
void cmDeallocMachineIlluminationController(CPMachineIlluminationController* con);

NASpace* cmGetMachineIlluminationControllerUIElement(CPMachineIlluminationController* con);

void cmUpdateMachineIlluminationController(CPMachineIlluminationController* con);
