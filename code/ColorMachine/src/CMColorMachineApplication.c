
#include "CMColorMachineApplication.h"

#include "CMColorsManager.h"
#include "CMDesign.h"
#include "CMMachineWindowController.h"
#include "CMMetamericsController.h"
#include "CMThreeDeeController.h"

#include "NAUtility/NAMemory.h"

struct CMColorMachineApplication{
  CMLColorMachine* cm; // current ColorMachine
  CMLColorMachine* sm; // current ScreenMachine
  CMColorsManager* colorsManager;

  CMMachineWindowController* machineWindowController;
  CMMetamericsController* metamericsController;
  CMThreeDeeController* threeDeeController;
};



void cmStartupColorMachineApplication(){
  app = naAlloc(CMColorMachineApplication);
  
  app->cm = cmlCreateColorMachine();
  app->sm = cmlCreateColorMachine();
  app->colorsManager = cmAllocColorsController();
}



void cmStartupColorMachineApplicationUI(){
  cmStartupDesign();

  app->machineWindowController = cmAllocMachineWindowController();
  app->threeDeeController      = cmAllocThreeDeeController();
  app->metamericsController    = cmAllocMetamericsController();

  cmSetCurrentColorController(cmGetInitialColorController(app->machineWindowController));
  cmShowMachineWindowController(app->machineWindowController);
}



void cmShutdownColorMachineApplication(){
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

CMLColorMachine* cmGetCurrentScreenMachine(){
  return app->sm;
}

CMColorsManager* cmGetColorsManager(){
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



void cmSetCurrentColorController(const CMColorController* con){
  cmSetColorsManagerCurrentColorController(cmGetColorsManager(), con);
  cmUpdateMachine();
}

const CMColorController* cmGetCurrentColorController(){
  return cmGetColorsManagerCurrentColorController(cmGetColorsManager());
}

const float* cmGetCurrentColorData(){
  return cmGetColorsManagerCurrentColorData(cmGetColorsManager());
}

CMLColorType cmGetCurrentColorType(){
  return cmGetColorsManagerCurrentColorType(cmGetColorsManager());
}
