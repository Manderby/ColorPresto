
#include "CMMachineController.h"

#include "CMMachineButtonsController.h"
#include "CMMachineGrayController.h"
#include "CMMachineIlluminationController.h"
#include "CMMachineLabController.h"
#include "CMMachineObserverController.h"
#include "CMMachineRGBController.h"
#include "../ColorControllers/Displays/CMGammaDisplayController.h"
#include "../CMDesign.h"

#include "NAApp.h"


struct CMMachineController{
  NASpace* space;

  CMMachineGrayController* grayController;
  CMMachineIlluminationController* illuminationController;
  CMMachineLabController* labController;
  CMMachineObserverController* observerController;
  CMMachineRGBController* rgbController;

  CMMachineButtonsController* buttonsController;
};



CMMachineController* cmAllocMachineController(void){
  CMMachineController* con = naAlloc(CMMachineController);

  con->space = naNewSpace(naMakeSize(500, 500));

  con->observerController = cmAllocMachineObserverController();
  con->illuminationController = cmAllocMachineIlluminationController();
  con->rgbController = cmAllocMachineRGBController();
  con->labController = cmAllocMachineLabController();
  con->grayController = cmAllocMachineGrayController();

  con->buttonsController = cmAllocMachineButtonsController();

  // layout
  cmBeginUILayout(con->space, naMakeBezel4Zero());
  //cmAddUIRow(cmGetMachineObserverControllerUIElement(con->observerController), 0);
  cmAddUIRow(cmGetMachineIlluminationControllerUIElement(con->illuminationController), 0);
  //cmAddUIRow(cmGetMachineRGBControllerUIElement(con->rgbController), 0);
  //cmAddUIRow(cmGetMachineLabControllerUIElement(con->labController), 0);
  //cmAddUIRow(cmGetMachineGrayControllerUIElement(con->grayController), 0);
  //cmAddUIRow(cmGetMachineButtonsControllerUIElement(con->buttonsController), 0);
  //cmEndUILayout();

  return con;
}



void cmDeallocMachineController(CMMachineController* con){
  naFree(con);
}



NASpace* cmGetMachineUIElement(CMMachineController* con){
  return con->space;
}



void cmUpdateMachineController(CMMachineController* con){
  cmUpdateMachineObserverController(con->observerController);
  cmUpdateMachineIlluminationController(con->illuminationController);
  cmUpdateMachineRGBController(con->rgbController);
  cmUpdateMachineLabController(con->labController);
  cmUpdateMachineGrayController(con->grayController);
  cmUpdateMachineButtonsController(con->buttonsController);
}
