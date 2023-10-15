
#include "../mainC.h"

CM_PROTOTYPE(NASpace);



typedef struct CMMachineGrayController CMMachineGrayController;

CMMachineGrayController* cmAllocMachineGrayController(void);
void cmDeallocMachineGrayController(CMMachineGrayController* con);

NASpace* cmGetMachineGrayControllerUIElement(CMMachineGrayController* con);

void cmUpdateMachineGrayController(CMMachineGrayController* con);
