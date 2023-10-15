
#include "../mainC.h"

CM_PROTOTYPE(NASpace);



typedef struct CPMachineRGBController CPMachineRGBController;

CPMachineRGBController* cmAllocMachineRGBController(void);
void cmDeallocMachineRGBController(CPMachineRGBController* con);

NASpace* cmGetMachineRGBControllerUIElement(CPMachineRGBController* con);

void cmUpdateMachineRGBController(CPMachineRGBController* con);
