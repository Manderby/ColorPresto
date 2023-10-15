
#include "../mainC.h"

CP_PROTOTYPE(NASpace);



typedef struct CPMachineLabController CPMachineLabController;

CPMachineLabController* cmAllocMachineLabController(void);
void cmDeallocMachineLabController(CPMachineLabController* con);

NASpace* cmGetMachineLabControllerUIElement(CPMachineLabController* con);

void cpUpdateMachineLabController(CPMachineLabController* con);
