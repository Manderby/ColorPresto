
#include "CPMachineController.h"

#include "CPMachineButtonsController.h"
#include "CPMachineGrayController.h"
#include "CPMachineIlluminationController.h"
#include "CPMachineLabController.h"
#include "CPMachineObserverController.h"
#include "CPMachineRGBController.h"
#include "../ColorControllers/Displays/CPGammaDisplayController.h"
#include "../CPDesign.h"

#include "NAApp/NAApp.h"
#include "NAUtility/NAMemory.h"


struct CPMachineController{
  NASpace* space;

  CPMachineGrayController* grayController;
  CPMachineIlluminationController* illuminationController;
  CPMachineLabController* labController;
  CPMachineObserverController* observerController;
  CPMachineRGBController* rgbController;

  CPMachineButtonsController* buttonsController;
};



CPMachineController* cpAllocMachineController(void){
  CPMachineController* con = naAlloc(CPMachineController);

  con->space = naNewSpace(naMakeSize(500, 300));

  con->observerController = cpAllocMachineObserverController();
  con->illuminationController = cpAllocMachineIlluminationController();
  con->rgbController = cpAllocMachineRGBController();
  con->labController = cpAllocMachineLabController();
  con->grayController = cpAllocMachineGrayController();

  con->buttonsController = cpAllocMachineButtonsController();

  // layout
  cpBeginUILayout(con->space, naMakeBorder2D(0., 0., 0., 0.));
  cpAddUIRow(cpGetMachineObserverControllerUIElement(con->observerController), 0);
  cpAddUIRow(cpGetMachineIlluminationControllerUIElement(con->illuminationController), 0);
  cpAddUIRow(cpGetMachineRGBControllerUIElement(con->rgbController), 0);
  cpAddUIRow(cpGetMachineLabControllerUIElement(con->labController), 0);
  cpAddUIRow(cpGetMachineGrayControllerUIElement(con->grayController), 0);
  cpAddUIRow(cpGetMachineButtonsControllerUIElement(con->buttonsController), 0);
  cpEndUILayout();

  return con;
}



void cpDeallocMachineController(CPMachineController* con){
  naFree(con);
}



NASpace* cpGetMachineUIElement(CPMachineController* con){
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
