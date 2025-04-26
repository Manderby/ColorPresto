
#include "../main.h"

CP_PROTOTYPE(NASpace);



typedef struct CPMachineLabController CPMachineLabController;

CPMachineLabController* cpAllocMachineLabController(void);
void cpDeallocMachineLabController(CPMachineLabController* con);

NASpace* cpGetMachineLabControllerUIElement(CPMachineLabController* con);

void cpUpdateMachineLabController(CPMachineLabController* con);
