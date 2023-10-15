
#include "../mainC.h"

CP_PROTOTYPE(NASpace);



typedef struct CPMachineIlluminationController CPMachineIlluminationController;

CPMachineIlluminationController* cmAllocMachineIlluminationController(void);
void cmDeallocMachineIlluminationController(CPMachineIlluminationController* con);

NASpace* cmGetMachineIlluminationControllerUIElement(CPMachineIlluminationController* con);

void cpUpdateMachineIlluminationController(CPMachineIlluminationController* con);
