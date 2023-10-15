
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

#include "NAApp.h"


#define CP_MACHINE_PROMPT_STORAGE_TAG 1


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
  NASpace* contentSpace = naGetWindowContentSpace(con->window);

  con->machineController = cmAllocMachineController();

  con->rightSpace = naNewSpace(naMakeSize(1, 1));

  con->radiometricColorsSpace = naNewSpace(naMakeSize(1, 1));
  con->perceptiveColorsSpace = naNewSpace(naMakeSize(1, 1));
  con->RGBColorsSpace = naNewSpace(naMakeSize(1, 1));

  con->grayColorController = cmAllocGrayColorController();
  con->hsvhslColorController = cmAllocHSVHSLColorController();
  con->lablchColorController = cmAllocLabLchColorController();
  con->luvuvwColorController = cmAllocLuvUVWColorController();
  con->rgbColorController = cmAllocRGBColorController();
  con->spectralColorController = cmAllocSpectralColorController();
  con->xyzColorController = cmAllocXYZColorController();
  con->yuvyupvpColorController = cmAllocYuvColorController();
  con->ycbcrColorController = cmAllocYCbCrColorController();
  con->yxyColorController = cmAllocYxyColorController();

  cpBeginUILayout(con->radiometricColorsSpace, naMakeBezel4Zero());
  cpAddUIRow(cmGetColorControllerUIElement((CPColorController*)con->spectralColorController), 0);
  cpAddUIRow(cmGetColorControllerUIElement((CPColorController*)con->xyzColorController), 0);
  cpAddUIRow(cmGetColorControllerUIElement((CPColorController*)con->yxyColorController), 0);
  cpAddUIRow(cmGetColorControllerUIElement((CPColorController*)con->yuvyupvpColorController), 0);
  cpAddUIRow(cmGetColorControllerUIElement((CPColorController*)con->luvuvwColorController), 0);
  cpEndUILayout();

  cpBeginUILayout(con->perceptiveColorsSpace, naMakeBezel4Zero());
  cpAddUIRow(cmGetColorControllerUIElement((CPColorController*)con->grayColorController), 0);
  cpAddUIRow(cmGetColorControllerUIElement((CPColorController*)con->lablchColorController), 0);
  cpAddUIRow(cmGetColorControllerUIElement((CPColorController*)con->rgbColorController), 0);
  cpAddUIRow(cmGetColorControllerUIElement((CPColorController*)con->hsvhslColorController), 0);
  cpAddUIRow(cmGetColorControllerUIElement((CPColorController*)con->ycbcrColorController), 0);
  cpEndUILayout();

  cpBeginUILayout(con->rightSpace, naMakeBezel4Zero());
  cpAddUIRow(con->radiometricColorsSpace, 0);
  cpAddUICol(con->perceptiveColorsSpace, 0);
  cpAddUICol(con->RGBColorsSpace, 0);
  cpEndUILayout();

  cpBeginUILayout(contentSpace, naMakeBezel4Zero());
  cpAddUIRow(cmGetMachineUIElement(con->machineController), 0);
  cpAddUICol(con->rightSpace, 0);
  cpEndUILayout();

  return con;
}



void cpDeallocMachineWindowController(CPMachineWindowController* con){
  cmDeallocGrayColorController(con->grayColorController);
  cmDeallocHSVHSLColorController(con->hsvhslColorController);
  cmDeallocLabLchColorController(con->lablchColorController);
  cmDeallocLuvUVWColorController(con->luvuvwColorController);
  cmDeallocRGBColorController(con->rgbColorController);
  cmDeallocSpectralColorController(con->spectralColorController);
  cmDeallocXYZColorController(con->xyzColorController);
  cmDeallocYuvColorController(con->yuvyupvpColorController);
  cmDeallocYCbCrColorController(con->ycbcrColorController);
  cmDeallocYxyColorController(con->yxyColorController);
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
  
  cmSetColorControllerActive((CPColorController*)con->grayColorController, cpGetCurrentColorController() == (CPColorController*)con->grayColorController);
  cmSetColorControllerActive((CPColorController*)con->hsvhslColorController, cpGetCurrentColorController() == (CPColorController*)con->hsvhslColorController);
  cmSetColorControllerActive((CPColorController*)con->lablchColorController, cpGetCurrentColorController() == (CPColorController*)con->lablchColorController);
  cmSetColorControllerActive((CPColorController*)con->luvuvwColorController, cpGetCurrentColorController() == (CPColorController*)con->luvuvwColorController);
  cmSetColorControllerActive((CPColorController*)con->rgbColorController, cpGetCurrentColorController() == (CPColorController*)con->rgbColorController);
  cmSetColorControllerActive((CPColorController*)con->spectralColorController, cpGetCurrentColorController() == (CPColorController*)con->spectralColorController);
  cmSetColorControllerActive((CPColorController*)con->xyzColorController, cpGetCurrentColorController() == (CPColorController*)con->xyzColorController);
  cmSetColorControllerActive((CPColorController*)con->ycbcrColorController, cpGetCurrentColorController() == (CPColorController*)con->ycbcrColorController);
  cmSetColorControllerActive((CPColorController*)con->yuvyupvpColorController, cpGetCurrentColorController() == (CPColorController*)con->yuvyupvpColorController);
  cmSetColorControllerActive((CPColorController*)con->yxyColorController, cpGetCurrentColorController() == (CPColorController*)con->yxyColorController);

  cmUpdateGrayColorController(con->grayColorController);
  cmUpdateHSVHSLColorController(con->hsvhslColorController);
  cmUpdateLabLchColorController(con->lablchColorController);
  cmUpdateLuvUVWColorController(con->luvuvwColorController);
  cmUpdateRGBColorController(con->rgbColorController);
  cmUpdateSpectralColorController(con->spectralColorController);
  cmUpdateXYZColorController(con->xyzColorController);
  cmUpdateYCbCrColorController(con->ycbcrColorController);
  cmUpdateYuvColorController(con->yuvyupvpColorController);
  cmUpdateYxyColorController(con->yxyColorController);
}
