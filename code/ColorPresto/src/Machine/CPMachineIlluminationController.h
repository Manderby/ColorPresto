
#include "../main.h"

CP_PROTOTYPE(NASpace);



typedef struct CPMachineIlluminationController CPMachineIlluminationController;

CPMachineIlluminationController* cpAllocMachineIlluminationController(void);
void cpDeallocMachineIlluminationController(CPMachineIlluminationController* con);

NASpace* cpGetMachineIlluminationControllerUIElement(CPMachineIlluminationController* con);

void cpUpdateMachineIlluminationController(CPMachineIlluminationController* con);
