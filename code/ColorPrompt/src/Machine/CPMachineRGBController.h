
#include "../mainC.h"

CP_PROTOTYPE(NASpace);



typedef struct CPMachineRGBController CPMachineRGBController;

CPMachineRGBController* cmAllocMachineRGBController(void);
void cmDeallocMachineRGBController(CPMachineRGBController* con);

NASpace* cmGetMachineRGBControllerUIElement(CPMachineRGBController* con);

void cpUpdateMachineRGBController(CPMachineRGBController* con);
