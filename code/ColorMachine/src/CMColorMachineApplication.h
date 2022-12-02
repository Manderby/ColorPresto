
#ifndef CM_COLOR_MACHINE_APPLICATION_DEFINED
#define CM_COLOR_MACHINE_APPLICATION_DEFINED

#include "mainC.h"

typedef struct CMColorMachineApplication CMColorMachineApplication;

extern CMColorMachineApplication* app;

CM_PROTOTYPE(CMColorsManager);



void cmStartupColorMachineApplication(void);
void cmStartupColorMachineApplicationUI(void);
void cmShutdownColorMachineApplication(void);

CMLColorMachine* cmGetCurrentColorMachine(void);
CMLColorMachine* cmGetCurrentScreenMachine(void);
CMColorsManager* cmGetColorsManager(void);

void cmUpdateMetamerics(void);
void cmShowMetamerics(void);
void cmShowThreeDee(void);

void cmUpdateColor(void);
void cmUpdateMachine(void);

#endif // CM_COLOR_MACHINE_APPLICATION_DEFINED
