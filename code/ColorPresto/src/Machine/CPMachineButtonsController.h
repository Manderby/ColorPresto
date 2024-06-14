
#include "../mainC.h"

CP_PROTOTYPE(NASpace);



typedef struct CPMachineButtonsController CPMachineButtonsController;

CPMachineButtonsController* cpAllocMachineButtonsController(void);
void cpDeallocMachineButtonsController(CPMachineButtonsController* con);

NASpace* cpGetMachineButtonsControllerUIElement(CPMachineButtonsController* con);

void cpUpdateMachineButtonsController(CPMachineButtonsController* con);
