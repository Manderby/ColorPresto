
#include "../mainC.h"

CP_PROTOTYPE(NASpace);



typedef struct CPMachineObserverController CPMachineObserverController;

CPMachineObserverController* cpAllocMachineObserverController(void);
void cpDeallocMachineObserverController(CPMachineObserverController* con);

NASpace* cpGetMachineObserverControllerUIElement(CPMachineObserverController* con);

void cpUpdateMachineObserverController(CPMachineObserverController* con);
