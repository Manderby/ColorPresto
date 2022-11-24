
#include "mainC.h"

CM_PROTOTYPE(NASpace);



typedef struct CMMachineObserverController CMMachineObserverController;

CMMachineObserverController* cmAllocMachineObserverController(void);
void cmDeallocMachineObserverController(CMMachineObserverController* con);

NASpace* cmGetMachineObserverControllerUIElement(CMMachineObserverController* con);

void cmUpdateMachineObserverController(CMMachineObserverController* con);
