
#ifndef CM_COLOR_PROMPT_APPLICATION_DEFINED
#define CM_COLOR_PROMPT_APPLICATION_DEFINED

#include "mainC.h"

typedef struct CPColorPromptApplication CPColorPromptApplication;

extern CPColorPromptApplication* app;

CM_PROTOTYPE(CPColorsManager);



void cmStartupColorPromptApplication(void);
void cmStartupColorPromptApplicationUI(void);
void cmShutdownColorPromptApplication(void);

CMLColorMachine* cmGetCurrentColorMachine(void);
void cmResetColorMachine(void);
CMLColorMachine* cmGetCurrentScreenMachine(void);
CPColorsManager* cmGetColorsManager(void);

void cmUpdateMetamerics(void);
void cmShowMetamerics(void);
void cmShowThreeDee(void);

void cmUpdateColor(void);
void cmUpdateMachine(void);

#endif // CM_COLOR_PROMPT_APPLICATION_DEFINED
