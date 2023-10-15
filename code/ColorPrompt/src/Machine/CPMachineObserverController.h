
#include "../mainC.h"

CP_PROTOTYPE(NASpace);



typedef struct CPMachineObserverController CPMachineObserverController;

CPMachineObserverController* cmAllocMachineObserverController(void);
void cmDeallocMachineObserverController(CPMachineObserverController* con);

NASpace* cmGetMachineObserverControllerUIElement(CPMachineObserverController* con);

void cpUpdateMachineObserverController(CPMachineObserverController* con);
