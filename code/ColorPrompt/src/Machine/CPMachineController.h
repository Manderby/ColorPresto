
#include "../mainC.h"

CP_PROTOTYPE(NASpace);



typedef struct CPMachineController CPMachineController;

CPMachineController* cpAllocMachineController(void);
void cpDeallocMachineController(CPMachineController* con);

NASpace* cpGetMachineUIElement(CPMachineController* con);

void cpUpdateMachineController(CPMachineController* con);
