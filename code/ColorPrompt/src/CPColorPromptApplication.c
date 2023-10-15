
#include "CPColorPromptApplication.h"

#include "CPColorsManager.h"
#include "CPDesign.h"
#include "Machine/CPMachineWindowController.h"
#include "Metamerics/CPMetamericsController.h"
#include "ThreeDee/CPThreeDeeController.h"

#include "NAUtility/NAMemory.h"

struct CPColorPromptApplication{
  CMLColorMachine* cm; // current ColorMachine
  CMLColorMachine* sm; // current ScreenMachine
  CPColorsManager* colorsManager;

  CPMachineWindowController* machineWindowController;
  CPMetamericsController* metamericsController;
  CPThreeDeeController* threeDeeController;
};



void cmStartupColorPromptApplication(){
  app = naAlloc(CPColorPromptApplication);
  
  app->cm = cmlCreateColorMachine();
  app->sm = cmlCreateColorMachine();
  app->colorsManager = cmAllocColorsController();
}



void cmStartupColorPromptApplicationUI(){
  cmStartupDesign();

  app->machineWindowController = cmAllocMachineWindowController();
  app->threeDeeController      = cmAllocThreeDeeController();
  app->metamericsController    = cmAllocMetamericsController();

  cmSetCurrentColorController(cmGetInitialColorController(app->machineWindowController));
  cmShowMachineWindowController(app->machineWindowController);
}



void cmShutdownColorPromptApplication(){
  cmDeallocMetamericsController(app->metamericsController);
  cmDeallocThreeDeeController(app->threeDeeController);
  cmDeallocMachineWindowController(app->machineWindowController);

  cmShutdownDesign();

  cmDeallocColorsController(app->colorsManager);
  cmlReleaseColorMachine(app->sm);
  cmlReleaseColorMachine(app->cm);

  naFree(app);
}



CMLColorMachine* cmGetCurrentColorMachine(){
  return app->cm;
}

void cmResetColorMachine(){
  cmlReleaseColorMachine(app->cm);
  app->cm = cmlCreateColorMachine();
}

CMLColorMachine* cmGetCurrentScreenMachine(){
  return app->sm;
}

CPColorsManager* cmGetColorsManager(){
  return app->colorsManager;
}

void cmUpdateMetamerics(){
  cmUpdateMetamericsController(app->metamericsController);
}
void cmShowMetamerics(){
  cmShowMetamericsController(app->metamericsController);
}
void cmShowThreeDee(){
  cmShowThreeDeeController(app->threeDeeController);
}

void cmUpdateColor(){
  cmUpdateMetamerics();
  cmUpdateThreeDeeController(app->threeDeeController);
}
void cmUpdateMachine(){
  cmUpdateMachineWindowController(app->machineWindowController);
  cmUpdateMetamerics();
  cmUpdateThreeDeeController(app->threeDeeController);
}



void cmSetCurrentColorController(const CPColorController* con){
  cmSetColorsManagerCurrentColorController(cmGetColorsManager(), con);
  cmUpdateMachine();
}

const CPColorController* cmGetCurrentColorController(){
  return cmGetColorsManagerCurrentColorController(cmGetColorsManager());
}

const float* cmGetCurrentColorData(){
  return cmGetColorsManagerCurrentColorData(cmGetColorsManager());
}

CMLColorType cmGetCurrentColorType(){
  return cmGetColorsManagerCurrentColorType(cmGetColorsManager());
}
