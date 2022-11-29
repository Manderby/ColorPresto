#ifndef CM_MACHINE_WINDOW_CONTROLLER_INCLUDED
#define CM_MACHINE_WINDOW_CONTROLLER_INCLUDED

#ifdef __cplusplus
  extern "C"{
#endif


#include "mainC.h"
CM_PROTOTYPE(CMColorController);



typedef struct CMMachineWindowController CMMachineWindowController;

CMMachineWindowController* cmAllocMachineWindowController(void);
void cmDeallocMachineWindowController(CMMachineWindowController* con);

void cmShowMachineWindowController(CMMachineWindowController* con);
CMColorController* cmGetInitialColorController(CMMachineWindowController* con);
void cmUpdateMachineWindowController(CMMachineWindowController* con);



#ifdef __cplusplus
  }
#endif

#endif // CM_MACHINE_WINDOW_CONTROLLER_INCLUDED
