
#include "../mainC.h"

CP_PROTOTYPE(NASpace);



typedef struct CPMachineRGBController CPMachineRGBController;

CPMachineRGBController* cpAllocMachineRGBController(void);
void cpDeallocMachineRGBController(CPMachineRGBController* con);

NASpace* cpGetMachineRGBControllerUIElement(CPMachineRGBController* con);

void cpUpdateMachineRGBController(CPMachineRGBController* con);
