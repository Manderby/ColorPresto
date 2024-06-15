
#ifndef CP_COLOR_PRESTO_APPLICATION_DEFINED
#define CP_COLOR_PRESTO_APPLICATION_DEFINED

#include "mainC.h"

typedef struct CPColorPrestoApplication CPColorPrestoApplication;

extern CPColorPrestoApplication* app;

CP_PROTOTYPE(CPColorsManager);



void cpStartupColorPrestoApplication(void);
void cpStartupColorPrestoApplicationUI(void);
void cpShutdownColorPrestoApplication(void);

CMLColorMachine* cpGetCurrentColorMachine(void);
void cpResetColorMachine(void);
CMLColorMachine* cpGetCurrentScreenMachine(void);
CPColorsManager* cpGetColorsManager(void);

void cpShowMetamerics(void);
void cpUpdateMetamerics(void);

void cpShowThreeDee(void);
void cpUpdateThreeDee(void);

void cpShowAbout(void);

void cpUpdateColor(void);
void cpUpdateMachine(void);

#endif // CP_COLOR_PRESTO_APPLICATION_DEFINED
