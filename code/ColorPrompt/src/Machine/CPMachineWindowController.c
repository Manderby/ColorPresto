
#include "CPMachineWindowController.h"

#include "CPMachineController.h"
#include "../ColorControllers/CPColorController.h"
#include "../CPDesign.h"
#include "../CPTranslations.h"

#include "../ColorControllers/CPGrayColorController.h"
#include "../ColorControllers/CPHSVHSLColorController.h"
#include "../ColorControllers/CPLabLchColorController.h"
#include "../ColorControllers/CPLuvUVWColorController.h"
#include "../ColorControllers/CPRGBColorController.h"
#include "../ColorControllers/CPSpectralColorController.h"
#include "../ColorControllers/CPXYZColorController.h"
#include "../ColorControllers/CPYCbCrColorController.h"
#include "../ColorControllers/CPYuvYupvpColorController.h"
#include "../ColorControllers/CPYxyColorController.h"

#include "NAApp/NAApp.h"


#define CP_MACHINE_PROMPT_STORAGE_TAG 1


NABool cpControllerWindowCloses(NAReaction reaction){
  naStopApplication();
  return NA_TRUE;
}


struct CPMachineWindowController{
  NAWindow* window;
  
  CPMachineController* machineController;
  
  NASpace* rightSpace;
  NASpace* radiometricColorsSpace;
  NASpace* perceptiveColorsSpace;
  NASpace* RGBColorsSpace;
  
  CPGrayColorController* grayColorController;
  CPHSVHSLColorController* hsvhslColorController;
  CPLabLchColorController* lablchColorController;
  CPLuvUVWColorController* luvuvwColorController;
  CPRGBColorController* rgbColorController;
  CPSpectralColorController* spectralColorController;
  CPXYZColorController* xyzColorController;
  CPYCbCrColorController* ycbcrColorController;
  CPYuvYupvpColorController* yuvyupvpColorController;
  CPYxyColorController* yxyColorController;
};



CPMachineWindowController* cpAllocMachineWindowController(void){
  CPMachineWindowController* con = naAlloc(CPMachineWindowController);

  con->window = naNewWindow(
    cpTranslate(CPApplicationName),
    naMakeRectS(200, 200, 500, 500),
    0,
    CP_MACHINE_PROMPT_STORAGE_TAG);
  naAddUIReaction(con->window, NA_UI_COMMAND_CLOSES, cpControllerWindowCloses, con);
    
  NASpace* contentSpace = naGetWindowContentSpace(con->window);

  con->machineController = cpAllocMachineController();

  con->rightSpace = naNewSpace(naMakeSize(1, 1));

  con->radiometricColorsSpace = naNewSpace(naMakeSize(1, 1));
  con->perceptiveColorsSpace = naNewSpace(naMakeSize(1, 1));
  con->RGBColorsSpace = naNewSpace(naMakeSize(1, 1));

  con->grayColorController = cpAllocGrayColorController();
  con->hsvhslColorController = cpAllocHSVHSLColorController();
  con->lablchColorController = cpAllocLabLchColorController();
  con->luvuvwColorController = cpAllocLuvUVWColorController();
  con->rgbColorController = cpAllocRGBColorController();
  con->spectralColorController = cpAllocSpectralColorController();
  con->xyzColorController = cpAllocXYZColorController();
  con->yuvyupvpColorController = cpAllocYuvColorController();
  con->ycbcrColorController = cpAllocYCbCrColorController();
  con->yxyColorController = cpAllocYxyColorController();

  cpBeginUILayout(con->radiometricColorsSpace, naMakeBezel4Zero());
  cpAddUIRow(cpGetColorControllerUIElement((CPColorController*)con->spectralColorController), 0);
  cpAddUIRow(cpGetColorControllerUIElement((CPColorController*)con->xyzColorController), 0);
  cpAddUIRow(cpGetColorControllerUIElement((CPColorController*)con->yxyColorController), 0);
  cpAddUIRow(cpGetColorControllerUIElement((CPColorController*)con->yuvyupvpColorController), 0);
  cpAddUIRow(cpGetColorControllerUIElement((CPColorController*)con->luvuvwColorController), 0);
  cpEndUILayout();

  cpBeginUILayout(con->perceptiveColorsSpace, naMakeBezel4Zero());
  cpAddUIRow(cpGetColorControllerUIElement((CPColorController*)con->grayColorController), 0);
  cpAddUIRow(cpGetColorControllerUIElement((CPColorController*)con->lablchColorController), 0);
  cpAddUIRow(cpGetColorControllerUIElement((CPColorController*)con->rgbColorController), 0);
  cpAddUIRow(cpGetColorControllerUIElement((CPColorController*)con->hsvhslColorController), 0);
  cpAddUIRow(cpGetColorControllerUIElement((CPColorController*)con->ycbcrColorController), 0);
  cpEndUILayout();

  cpBeginUILayout(con->rightSpace, naMakeBezel4Zero());
  cpAddUIRow(con->radiometricColorsSpace, 0);
  cpAddUICol(con->perceptiveColorsSpace, 0);
  cpAddUICol(con->RGBColorsSpace, 0);
  cpEndUILayout();

  cpBeginUILayout(contentSpace, naMakeBezel4Zero());
  cpAddUIRow(cpGetMachineUIElement(con->machineController), 0);
  cpAddUICol(con->rightSpace, 0);
  cpEndUILayout();

  return con;
}



void cpDeallocMachineWindowController(CPMachineWindowController* con){
  cpDeallocGrayColorController(con->grayColorController);
  cpDeallocHSVHSLColorController(con->hsvhslColorController);
  cpDeallocLabLchColorController(con->lablchColorController);
  cpDeallocLuvUVWColorController(con->luvuvwColorController);
  cpDeallocRGBColorController(con->rgbColorController);
  cpDeallocSpectralColorController(con->spectralColorController);
  cpDeallocXYZColorController(con->xyzColorController);
  cpDeallocYuvColorController(con->yuvyupvpColorController);
  cpDeallocYCbCrColorController(con->ycbcrColorController);
  cpDeallocYxyColorController(con->yxyColorController);
  naFree(con);
}



void cpShowMachineWindowController(CPMachineWindowController* con){
  naShowWindow(con->window);
}



CPColorController* cpGetInitialColorController(CPMachineWindowController* con){
  return (CPColorController*)con->grayColorController;
}



void cpUpdateMachineWindowController(CPMachineWindowController* con){
  cpUpdateMachineController(con->machineController);
  
  cpSetColorControllerActive((CPColorController*)con->grayColorController, cpGetCurrentColorController() == (CPColorController*)con->grayColorController);
  cpSetColorControllerActive((CPColorController*)con->hsvhslColorController, cpGetCurrentColorController() == (CPColorController*)con->hsvhslColorController);
  cpSetColorControllerActive((CPColorController*)con->lablchColorController, cpGetCurrentColorController() == (CPColorController*)con->lablchColorController);
  cpSetColorControllerActive((CPColorController*)con->luvuvwColorController, cpGetCurrentColorController() == (CPColorController*)con->luvuvwColorController);
  cpSetColorControllerActive((CPColorController*)con->rgbColorController, cpGetCurrentColorController() == (CPColorController*)con->rgbColorController);
  cpSetColorControllerActive((CPColorController*)con->spectralColorController, cpGetCurrentColorController() == (CPColorController*)con->spectralColorController);
  cpSetColorControllerActive((CPColorController*)con->xyzColorController, cpGetCurrentColorController() == (CPColorController*)con->xyzColorController);
  cpSetColorControllerActive((CPColorController*)con->ycbcrColorController, cpGetCurrentColorController() == (CPColorController*)con->ycbcrColorController);
  cpSetColorControllerActive((CPColorController*)con->yuvyupvpColorController, cpGetCurrentColorController() == (CPColorController*)con->yuvyupvpColorController);
  cpSetColorControllerActive((CPColorController*)con->yxyColorController, cpGetCurrentColorController() == (CPColorController*)con->yxyColorController);

  cpUpdateGrayColorController(con->grayColorController);
  cpUpdateHSVHSLColorController(con->hsvhslColorController);
  cpUpdateLabLchColorController(con->lablchColorController);
  cpUpdateLuvUVWColorController(con->luvuvwColorController);
  cpUpdateRGBColorController(con->rgbColorController);
  cpUpdateSpectralColorController(con->spectralColorController);
  cpUpdateXYZColorController(con->xyzColorController);
  cpUpdateYCbCrColorController(con->ycbcrColorController);
  cpUpdateYuvColorController(con->yuvyupvpColorController);
  cpUpdateYxyColorController(con->yxyColorController);
}
