
#include "CPColorPrestoApplication.h"

#include "CPAboutController.h"
#include "CPColorsManager.h"
#include "CPDesign.h"
#include "Machine/CPMachineWindowController.h"
#include "Metamerics/CPMetamericsController.h"
#include "ThreeDee/CPThreeDeeController.h"

#include "NAUtility/NAMemory.h"

struct CPColorPrestoApplication{
  CMLColorMachine* cm; // current ColorMachine
  CMLColorMachine* sm; // current ScreenMachine
  CPColorsManager* colorsManager;

  CPMachineWindowController* machineWindowController;
  CPMetamericsController* metamericsController;
  CPThreeDeeController* threeDeeController;
  CPAboutController* aboutController;
};



void cpStartupColorPrestoApplication(){
  app = naAlloc(CPColorPrestoApplication);
  
  app->cm = cmlCreateColorMachine();
  app->sm = cmlCreateColorMachine();
  app->colorsManager = cpAllocColorsController();
}



void cpStartupColorPrestoApplicationUI(){
  cpStartupDesign();

  app->machineWindowController = cpAllocMachineWindowController();
  app->threeDeeController      = NA_NULL;
  app->metamericsController    = NA_NULL;
  app->aboutController         = NA_NULL;

  cpSetCurrentColorController(cpGetInitialColorController(app->machineWindowController));
  cpShowMachineWindowController(app->machineWindowController);
}



void cpShutdownColorPrestoApplication(){
  if(app->metamericsController) {
    cpDeallocMetamericsController(app->metamericsController);
  }
  if(app->threeDeeController) {
    cpDeallocThreeDeeController(app->threeDeeController);
  }
  if(app->aboutController) {
    cpDeallocAboutController(app->aboutController);
  }
  cpDeallocMachineWindowController(app->machineWindowController);

  cpShutdownDesign();

  cpDeallocColorsController(app->colorsManager);
  cmlReleaseColorMachine(app->sm);
  cmlReleaseColorMachine(app->cm);

  naFree(app);
}



CMLColorMachine* cpGetCurrentColorMachine(){
  return app->cm;
}

void cpResetColorMachine(){
  cmlReleaseColorMachine(app->cm);
  app->cm = cmlCreateColorMachine();
}

CMLColorMachine* cpGetCurrentScreenMachine(){
  return app->sm;
}

CPColorsManager* cpGetColorsManager(){
  return app->colorsManager;
}



void cpShowMetamerics(){
  NABool newlyCreated = NA_FALSE;
  if(!app->metamericsController) {
    app->metamericsController = cpAllocMetamericsController();
    newlyCreated = NA_TRUE;
  }
  cpShowMetamericsController(app->metamericsController);
  if(newlyCreated) {
    cpUpdateMetamericsController(app->metamericsController);
  }
}
void cpUpdateMetamerics(){
  if(app->metamericsController) {
    cpUpdateMetamericsController(app->metamericsController);
  }
}



void cpShowThreeDee(){
  NABool newlyCreated = NA_FALSE;
  if(!app->threeDeeController) {
    app->threeDeeController = cpAllocThreeDeeController();
    newlyCreated = NA_TRUE;
  }
  cpShowThreeDeeController(app->threeDeeController);
  if(newlyCreated) {
    cpUpdateThreeDeeController(app->threeDeeController);
  }
}
void cpUpdateThreeDee(){
  if(app->threeDeeController) {
    cpUpdateThreeDeeController(app->threeDeeController);
  }
}



void cpShowAbout(){
  if(!app->aboutController) {
    app->aboutController = cpAllocAboutController();
  }
  cpShowAboutController(app->aboutController);
}



void cpUpdateColor(){
  cpUpdateMetamerics();
  cpUpdateThreeDee();
}
void cpUpdateMachine(){
  cpUpdateMachineWindowController(app->machineWindowController);
  cpUpdateMetamerics();
  cpUpdateThreeDee();
}



void cpSetCurrentColorController(const CPColorController* con){
  cpSetColorsManagerCurrentColorController(cpGetColorsManager(), con);
  cpUpdateMachine();
}

const CPColorController* cpGetCurrentColorController(){
  return cpGetColorsManagerCurrentColorController(cpGetColorsManager());
}

const float* cpGetCurrentColorData(){
  return cpGetColorsManagerCurrentColorData(cpGetColorsManager());
}

CMLColorType cpGetCurrentColorType(){
  return cpGetColorsManagerCurrentColorType(cpGetColorsManager());
}
