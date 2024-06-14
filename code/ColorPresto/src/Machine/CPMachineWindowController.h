#ifndef CP_MACHINE_WINDOW_CONTROLLER_INCLUDED
#define CP_MACHINE_WINDOW_CONTROLLER_INCLUDED

#include "../mainC.h"
CP_PROTOTYPE(CPColorController);



typedef struct CPMachineWindowController CPMachineWindowController;

CPMachineWindowController* cpAllocMachineWindowController(void);
void cpDeallocMachineWindowController(CPMachineWindowController* con);

void cpShowMachineWindowController(CPMachineWindowController* con);
CPColorController* cpGetInitialColorController(CPMachineWindowController* con);
void cpUpdateMachineWindowController(CPMachineWindowController* con);


#endif // CP_MACHINE_WINDOW_CONTROLLER_INCLUDED
