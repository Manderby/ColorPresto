
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



CPMachineController* cpAllocMachineController(void) {
  CPMachineController* con = naAlloc(CPMachineController);

  con->space = naNewSpace();
  naSetSpaceAlternateBackground(con->space, NA_TRUE);

  con->observerController = cpAllocMachineObserverController();
  con->illuminationController = cpAllocMachineIlluminationController();
  con->rgbController = cpAllocMachineRGBController();
  con->labController = cpAllocMachineLabController();
  con->grayController = cpAllocMachineGrayController();

  con->buttonsController = cpAllocMachineButtonsController();

  // layout
  naSetSpaceLayoutDirections(con->space, NA_LAYOUT_DIRECTIONS_TBLR);
  
  NABorder2D zeroPadding = naMakeBorder2D(0., 0., 0., 0.);
  
  naBeginLayout(con->space, zeroPadding);
    naAddLayoutSection(NA_LAYOUT_MIN, zeroPadding);
      naAddLayoutElement(cpGetMachineObserverControllerUIElement(con->observerController), 0, NA_LAYOUT_MIN);
      naAddLayoutElement(cpGetMachineIlluminationControllerUIElement(con->illuminationController), 0, NA_LAYOUT_MIN);
      naAddLayoutElement(cpGetMachineRGBControllerUIElement(con->rgbController), 0, NA_LAYOUT_MIN);
      naAddLayoutElement(cpGetMachineLabControllerUIElement(con->labController), 0, NA_LAYOUT_MIN);
      naAddLayoutElement(cpGetMachineGrayControllerUIElement(con->grayController), 0, NA_LAYOUT_MIN);
      naAddLayoutElement(cpGetMachineButtonsControllerUIElement(con->buttonsController), 0, NA_LAYOUT_MIN);
  naEndLayout();

  return con;
}



void cpDeallocMachineController(CPMachineController* con) {
  naFree(con);
}



NASpace* cpGetMachineUIElement(CPMachineController* con) {
  return con->space;
}



void cpUpdateMachineController(CPMachineController* con) {
  cpUpdateMachineObserverController(con->observerController);
  cpUpdateMachineIlluminationController(con->illuminationController);
  cpUpdateMachineRGBController(con->rgbController);
  cpUpdateMachineLabController(con->labController);
  cpUpdateMachineGrayController(con->grayController);
  cpUpdateMachineButtonsController(con->buttonsController);
}
