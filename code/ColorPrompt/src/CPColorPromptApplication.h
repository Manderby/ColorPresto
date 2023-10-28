
#ifndef CP_COLOR_PROMPT_APPLICATION_DEFINED
#define CP_COLOR_PROMPT_APPLICATION_DEFINED

#include "mainC.h"

typedef struct CPColorPromptApplication CPColorPromptApplication;

extern CPColorPromptApplication* app;

CP_PROTOTYPE(CPColorsManager);



void cpStartupColorPromptApplication(void);
void cpStartupColorPromptApplicationUI(void);
void cpShutdownColorPromptApplication(void);

CMLColorMachine* cpGetCurrentColorMachine(void);
void cpResetColorMachine(void);
CMLColorMachine* cpGetCurrentScreenMachine(void);
CPColorsManager* cpGetColorsManager(void);

void cpUpdateMetamerics(void);
void cpShowMetamerics(void);
void cpShowThreeDee(void);
void cpShowAbout(void);

void cpUpdateColor(void);
void cpUpdateMachine(void);

#endif // CP_COLOR_PROMPT_APPLICATION_DEFINED
