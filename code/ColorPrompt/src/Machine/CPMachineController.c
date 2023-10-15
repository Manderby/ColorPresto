
#include "CPMachineController.h"

#include "CPMachineButtonsController.h"
#include "CPMachineGrayController.h"
#include "CPMachineIlluminationController.h"
#include "CPMachineLabController.h"
#include "CPMachineObserverController.h"
#include "CPMachineRGBController.h"
#include "../ColorControllers/Displays/CPGammaDisplayController.h"
#include "../CPDesign.h"

#include "NAApp.h"


struct CPMachineController{
  NASpace* space;

  CPMachineGrayController* grayController;
  CPMachineIlluminationController* illuminationController;
  CPMachineLabController* labController;
  CPMachineObserverController* observerController;
  CPMachineRGBController* rgbController;

  CPMachineButtonsController* buttonsController;
};



CPMachineController* cmAllocMachineController(void){
  CPMachineController* con = naAlloc(CPMachineController);

  con->space = naNewSpace(naMakeSize(500, 300));

  con->observerController = cmAllocMachineObserverController();
  con->illuminationController = cmAllocMachineIlluminationController();
  con->rgbController = cmAllocMachineRGBController();
  con->labController = cmAllocMachineLabController();
  con->grayController = cmAllocMachineGrayController();

  con->buttonsController = cmAllocMachineButtonsController();

  // layout
  cmBeginUILayout(con->space, naMakeBezel4Zero());
  cmAddUIRow(cmGetMachineObserverControllerUIElement(con->observerController), 0);
  cmAddUIRow(cmGetMachineIlluminationControllerUIElement(con->illuminationController), 0);
  cmAddUIRow(cmGetMachineRGBControllerUIElement(con->rgbController), 0);
  cmAddUIRow(cmGetMachineLabControllerUIElement(con->labController), 0);
  cmAddUIRow(cmGetMachineGrayControllerUIElement(con->grayController), 0);
  cmAddUIRow(cmGetMachineButtonsControllerUIElement(con->buttonsController), 0);
  cmEndUILayout();

  return con;
}



void cmDeallocMachineController(CPMachineController* con){
  naFree(con);
}



NASpace* cmGetMachineUIElement(CPMachineController* con){
  return con->space;
}



void cmUpdateMachineController(CPMachineController* con){
  cmUpdateMachineObserverController(con->observerController);
  cmUpdateMachineIlluminationController(con->illuminationController);
  cmUpdateMachineRGBController(con->rgbController);
  cmUpdateMachineLabController(con->labController);
  cmUpdateMachineGrayController(con->grayController);
  cmUpdateMachineButtonsController(con->buttonsController);
}
