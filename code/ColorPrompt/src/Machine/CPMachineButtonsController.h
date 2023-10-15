
#include "../mainC.h"

CM_PROTOTYPE(NASpace);



typedef struct CPMachineButtonsController CPMachineButtonsController;

CPMachineButtonsController* cmAllocMachineButtonsController(void);
void cmDeallocMachineButtonsController(CPMachineButtonsController* con);

NASpace* cmGetMachineButtonsControllerUIElement(CPMachineButtonsController* con);

void cmUpdateMachineButtonsController(CPMachineButtonsController* con);
