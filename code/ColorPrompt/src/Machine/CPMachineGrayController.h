
#include "../mainC.h"

CM_PROTOTYPE(NASpace);



typedef struct CPMachineGrayController CPMachineGrayController;

CPMachineGrayController* cmAllocMachineGrayController(void);
void cmDeallocMachineGrayController(CPMachineGrayController* con);

NASpace* cmGetMachineGrayControllerUIElement(CPMachineGrayController* con);

void cmUpdateMachineGrayController(CPMachineGrayController* con);
