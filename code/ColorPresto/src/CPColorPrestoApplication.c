
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
  app->threeDeeController      = cpAllocThreeDeeController();
  app->metamericsController    = cpAllocMetamericsController();
  app->aboutController         = cpAllocAboutController();

  cpSetCurrentColorController(cpGetInitialColorController(app->machineWindowController));
  cpShowMachineWindowController(app->machineWindowController);
}



void cpShutdownColorPrestoApplication(){
  cpDeallocMetamericsController(app->metamericsController);
  cpDeallocThreeDeeController(app->threeDeeController);
  cpDeallocMachineWindowController(app->machineWindowController);
  cpDeallocAboutController(app->aboutController);

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

void cpUpdateMetamerics(){
  cpUpdateMetamericsController(app->metamericsController);
}
void cpShowMetamerics(){
  cpShowMetamericsController(app->metamericsController);
}
void cpShowThreeDee(){
  cpShowThreeDeeController(app->threeDeeController);
}
void cpShowAbout(){
  cpShowAboutController(app->aboutController);
}

void cpUpdateColor(){
  cpUpdateMetamerics();
  cpUpdateThreeDeeController(app->threeDeeController);
}
void cpUpdateMachine(){
  cpUpdateMachineWindowController(app->machineWindowController);
  cpUpdateMetamerics();
  cpUpdateThreeDeeController(app->threeDeeController);
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
