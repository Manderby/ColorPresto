
#include "CPColorPrestoApplication.h"

#include "CPColorsManager.h"
#include "CPDesign.h"
#include "About/CPAboutController.h"
#include "Machine/CPMachineWindowController.h"
#include "Metamerics/CPMetamericsController.h"
#include "Preferences/CPPreferencesController.h"
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
  CPPreferencesController* preferencesController;
};



void cpStartupColorPrestoApplication(){
  app = naAlloc(CPColorPrestoApplication);
  
  app->cm = cmlCreateColorMachine();
  app->sm = cmlCreateColorMachine();
  app->colorsManager = cpAllocColorsController();
}



void cpStartupColorPrestoApplicationUI(){
  cpStartupDesign();

  app->aboutController         = NA_NULL;
  app->machineWindowController = cpAllocMachineWindowController();
  app->metamericsController    = NA_NULL;
  app->preferencesController   = NA_NULL;
  app->threeDeeController      = NA_NULL;

  cpSetCurrentColorController(cpGetInitialColorController(app->machineWindowController));
  cpShowMachineWindowController(app->machineWindowController);
}



void cpShutdownColorPrestoApplication(){
  if(app->threeDeeController) {
    cpDeallocThreeDeeController(app->threeDeeController);
  }
  if(app->preferencesController) {
    cpDeallocPreferencesController(app->preferencesController);
  }
  if(app->metamericsController) {
    cpDeallocMetamericsController(app->metamericsController);
  }
  cpDeallocMachineWindowController(app->machineWindowController);
  if(app->aboutController) {
    cpDeallocAboutController(app->aboutController);
  }

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



void cpShowPreferences(){
  NABool newlyCreated = NA_FALSE;
  if(!app->preferencesController) {
    app->preferencesController = cpAllocPreferencesController();
    newlyCreated = NA_TRUE;
  }
  cpShowPreferencesController(app->preferencesController);
  if(newlyCreated) {
    cpUpdatePreferencesController(app->preferencesController);
  }
}



void cpUpdateColor(){
  cpUpdateColorWells(app->machineWindowController);
  cpUpdateMetamerics();
  cpUpdateThreeDee();
}
void cpUpdateMachine(){
  cpUpdateMachineWindowController(app->machineWindowController);
  cpUpdateColor();
}



void cpSetCurrentColorController(const CPColorController* con){
  if(cpSetColorsManagerCurrentColorController(cpGetColorsManager(), con)) {
    cpUpdateMachine();
  }
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
