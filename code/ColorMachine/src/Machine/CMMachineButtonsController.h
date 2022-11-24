
#include "mainC.h"

CM_PROTOTYPE(NASpace);



typedef struct CMMachineButtonsController CMMachineButtonsController;

CMMachineButtonsController* cmAllocMachineButtonsController(void);
void cmDeallocMachineButtonsController(CMMachineButtonsController* con);

NASpace* cmGetMachineButtonsControllerUIElement(CMMachineButtonsController* con);

void cmUpdateMachineButtonsController(CMMachineButtonsController* con);
