
#include "CMMachineController.h"

#include "CMMachineButtonsController.h"
#include "CMMachineIlluminationController.h"
#include "CMMachineObserverController.h"
#include "CMMachineRGBController.h"
#include "CMGammaDisplayController.h"

#include "NAApp.h"
#include "CMDesign.h"


struct CMMachineController{
  NASpace* space;

  CMMachineButtonsController* buttonsController;
  CMMachineIlluminationController* illuminationController;
  CMMachineObserverController* observerController;
  CMMachineRGBController* rgbController;

  CMGammaDisplayController* gammaDisplayController;
};



CMMachineController* cmAllocMachineController(void){
  CMMachineController* con = naAlloc(CMMachineController);

  con->space = naNewSpace(naMakeSize(1, 1));

  con->observerController = cmAllocMachineObserverController();
  con->illuminationController = cmAllocMachineIlluminationController();
  con->rgbController = cmAllocMachineRGBController();
  con->buttonsController = cmAllocMachineButtonsController();

  con->gammaDisplayController = cmAllocGammaDisplayController();

  // layout
  cmBeginUILayout(con->space, naMakeBezel4Zero());
  cmAddUIRow(cmGetMachineObserverControllerUIElement(con->observerController), 0);
  cmAddUIRow(cmGetMachineIlluminationControllerUIElement(con->illuminationController), 0);
  cmAddUIRow(cmGetMachineRGBControllerUIElement(con->rgbController), 0);
  cmAddUIRow(cmGetMachineButtonsControllerUIElement(con->buttonsController), 0);

  cmEndUILayout();

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
  cmUpdateMachineButtonsController(con->buttonsController);

  cmUpdateGammaDisplayController(con->gammaDisplayController);
}
