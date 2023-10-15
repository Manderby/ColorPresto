#ifndef CM_MACHINE_WINDOW_CONTROLLER_INCLUDED
#define CM_MACHINE_WINDOW_CONTROLLER_INCLUDED

#include "../mainC.h"
CM_PROTOTYPE(CPColorController);



typedef struct CPMachineWindowController CPMachineWindowController;

CPMachineWindowController* cmAllocMachineWindowController(void);
void cmDeallocMachineWindowController(CPMachineWindowController* con);

void cmShowMachineWindowController(CPMachineWindowController* con);
CPColorController* cmGetInitialColorController(CPMachineWindowController* con);
void cmUpdateMachineWindowController(CPMachineWindowController* con);


#endif // CM_MACHINE_WINDOW_CONTROLLER_INCLUDED
