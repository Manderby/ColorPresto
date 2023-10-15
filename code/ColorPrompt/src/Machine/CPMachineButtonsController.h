
#include "../mainC.h"

CP_PROTOTYPE(NASpace);



typedef struct CPMachineButtonsController CPMachineButtonsController;

CPMachineButtonsController* cmAllocMachineButtonsController(void);
void cmDeallocMachineButtonsController(CPMachineButtonsController* con);

NASpace* cmGetMachineButtonsControllerUIElement(CPMachineButtonsController* con);

void cpUpdateMachineButtonsController(CPMachineButtonsController* con);
