
#include "../mainC.h"

CP_PROTOTYPE(NASpace);



typedef struct CPMachineGrayController CPMachineGrayController;

CPMachineGrayController* cpAllocMachineGrayController(void);
void cpDeallocMachineGrayController(CPMachineGrayController* con);

NASpace* cpGetMachineGrayControllerUIElement(CPMachineGrayController* con);

void cpUpdateMachineGrayController(CPMachineGrayController* con);
