
#include "../mainC.h"

CM_PROTOTYPE(NASpace);



typedef struct CPMachineObserverController CPMachineObserverController;

CPMachineObserverController* cmAllocMachineObserverController(void);
void cmDeallocMachineObserverController(CPMachineObserverController* con);

NASpace* cmGetMachineObserverControllerUIElement(CPMachineObserverController* con);

void cmUpdateMachineObserverController(CPMachineObserverController* con);
