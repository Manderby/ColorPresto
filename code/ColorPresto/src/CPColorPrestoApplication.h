
#ifndef CP_COLOR_PRESTO_APPLICATION_DEFINED
#define CP_COLOR_PRESTO_APPLICATION_DEFINED

#include "main.h"

CP_PROTOTYPE(CPColorsManager);



void cpPreStartupApplication(void* arg);
void cpPostStartupApplication(void* arg);
void cpShutdownApplication(void* arg);

CMLColorMachine* cpGetCurrentColorMachine(void);
void cpResetColorMachine(void);
CMLColorMachine* cpGetCurrentScreenMachine(void);
CPColorsManager* cpGetColorsManager(void);

void cpShowMetamerics(void);
void cpUpdateMetamerics(void);

void cpShowThreeDee(void);
void cpUpdateThreeDee(void);

void cpShowAbout(void);

void cpShowPreferences(void);

void cpUpdateColor(void);
void cpUpdateMachine(void);

#endif // CP_COLOR_PRESTO_APPLICATION_DEFINED
