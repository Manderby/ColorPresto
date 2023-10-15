
#include "../mainC.h"

CM_PROTOTYPE(NASpace);



typedef struct CPMachineController CPMachineController;

CPMachineController* cmAllocMachineController(void);
void cmDeallocMachineController(CPMachineController* con);

NASpace* cmGetMachineUIElement(CPMachineController* con);

void cmUpdateMachineController(CPMachineController* con);
