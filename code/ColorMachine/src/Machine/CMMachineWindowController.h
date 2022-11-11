#ifndef CM_MACHINE_WINDOW_CONTROLLER_INCLUDED
#define CM_MACHINE_WINDOW_CONTROLLER_INCLUDED

#ifdef __cplusplus
  extern "C"{
#endif



typedef struct CMMachineWindowController CMMachineWindowController;

CMMachineWindowController* cmAllocMachineWindowController(void);
void cmDeallocMachineWindowController(CMMachineWindowController* con);

void cmShowMachineWindowController(CMMachineWindowController* con);
void cmUpdateMachineWindowController(CMMachineWindowController* con);



#ifdef __cplusplus
  }
#endif

#endif // CM_MACHINE_WINDOW_CONTROLLER_INCLUDED
