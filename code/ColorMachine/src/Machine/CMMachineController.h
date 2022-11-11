
#include "mainC.h"

CM_PROTOTYPE(CMWhitePoints);
CM_PROTOTYPE(NASpace);



typedef struct CMMachineController CMMachineController;

CMMachineController* cmAllocMachineController(void);
void cmDeallocMachineController(CMMachineController* con);

NASpace* cmGetMachineUIElement(CMMachineController* con);

void cmUpdateMachineController(CMMachineController* con);
