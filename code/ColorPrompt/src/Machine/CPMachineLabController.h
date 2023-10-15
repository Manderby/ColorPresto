
#include "../mainC.h"

CM_PROTOTYPE(NASpace);



typedef struct CPMachineLabController CPMachineLabController;

CPMachineLabController* cmAllocMachineLabController(void);
void cmDeallocMachineLabController(CPMachineLabController* con);

NASpace* cmGetMachineLabControllerUIElement(CPMachineLabController* con);

void cmUpdateMachineLabController(CPMachineLabController* con);
