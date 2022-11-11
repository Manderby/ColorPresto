
#include "CMMachineWindowController.h"

#include "CMMachineController.h"

#include "NAApp.h"



struct CMMachineWindowController{
  NAWindow* window;
  
  CMMachineController* machineController;
  
  NASpace* radiometricColorsSpace;
  NASpace* perceptiveColrosSpace;
  NASpace* RGBColorsSpace;
  
};



CMMachineWindowController* cmAllocMachineWindowController(void){
  CMMachineWindowController* con = naAlloc(CMMachineWindowController);
  naZeron(con, sizeof(CMMachineWindowController));

  con->window = naNewWindow(
    "Color Machine",
    naMakeRectS(400, 500, 1000, 600),
    0,
    0);
  NASpace* contentSpace = naGetWindowContentSpace(con->window);

  con->machineController = cmAllocMachineController();

  con->radiometricColorsSpace = naNewSpace(naMakeSize(200, 500));
  con->perceptiveColrosSpace = naNewSpace(naMakeSize(200, 500));
  con->RGBColorsSpace = naNewSpace(naMakeSize(200, 500));

  naSetSpaceAlternateBackground(con->radiometricColorsSpace, NA_TRUE);
  naSetSpaceAlternateBackground(con->RGBColorsSpace, NA_TRUE);

  naAddSpaceChild(contentSpace, cmGetMachineUIElement(con->machineController), naMakePos(0,0));
  naAddSpaceChild(contentSpace, con->radiometricColorsSpace, naMakePos(400,0));
  naAddSpaceChild(contentSpace, con->perceptiveColrosSpace, naMakePos(600,0));
  naAddSpaceChild(contentSpace, con->RGBColorsSpace, naMakePos(800,0));

  return con;
}



void cmDeallocMachineWindowController(CMMachineWindowController* con){
  naFree(con);
}



void cmShowMachineWindowController(CMMachineWindowController* con){
  naShowWindow(con->window);
}



void cmUpdateMachineWindowController(CMMachineWindowController* con){
  cmUpdateMachineController(con->machineController);
}
