
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
  cpBeginUILayout(con->space, naMakeBezel4Zero());
  cpAddUIRow(cmGetMachineObserverControllerUIElement(con->observerController), 0);
  cpAddUIRow(cmGetMachineIlluminationControllerUIElement(con->illuminationController), 0);
  cpAddUIRow(cmGetMachineRGBControllerUIElement(con->rgbController), 0);
  cpAddUIRow(cmGetMachineLabControllerUIElement(con->labController), 0);
  cpAddUIRow(cmGetMachineGrayControllerUIElement(con->grayController), 0);
  cpAddUIRow(cmGetMachineButtonsControllerUIElement(con->buttonsController), 0);
  cpEndUILayout();

  return con;
}



void cmDeallocMachineController(CPMachineController* con){
  naFree(con);
}



NASpace* cmGetMachineUIElement(CPMachineController* con){
  return con->space;
}



void cpUpdateMachineController(CPMachineController* con){
  cpUpdateMachineObserverController(con->observerController);
  cpUpdateMachineIlluminationController(con->illuminationController);
  cpUpdateMachineRGBController(con->rgbController);
  cpUpdateMachineLabController(con->labController);
  cpUpdateMachineGrayController(con->grayController);
  cpUpdateMachineButtonsController(con->buttonsController);
}
