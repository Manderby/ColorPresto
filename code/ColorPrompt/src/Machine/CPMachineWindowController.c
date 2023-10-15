
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


#define CM_MACHINE_PROMPT_STORAGE_TAG 1


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



CPMachineWindowController* cmAllocMachineWindowController(void){
  CPMachineWindowController* con = naAlloc(CPMachineWindowController);

  con->window = naNewWindow(
    cmTranslate(CMApplicationName),
    naMakeRectS(200, 200, 500, 500),
    0,
    CM_MACHINE_PROMPT_STORAGE_TAG);
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

  cmBeginUILayout(con->radiometricColorsSpace, naMakeBezel4Zero());
  cmAddUIRow(cmGetColorControllerUIElement((CPColorController*)con->spectralColorController), 0);
  cmAddUIRow(cmGetColorControllerUIElement((CPColorController*)con->xyzColorController), 0);
  cmAddUIRow(cmGetColorControllerUIElement((CPColorController*)con->yxyColorController), 0);
  cmAddUIRow(cmGetColorControllerUIElement((CPColorController*)con->yuvyupvpColorController), 0);
  cmAddUIRow(cmGetColorControllerUIElement((CPColorController*)con->luvuvwColorController), 0);
  cmEndUILayout();

  cmBeginUILayout(con->perceptiveColorsSpace, naMakeBezel4Zero());
  cmAddUIRow(cmGetColorControllerUIElement((CPColorController*)con->grayColorController), 0);
  cmAddUIRow(cmGetColorControllerUIElement((CPColorController*)con->lablchColorController), 0);
  cmAddUIRow(cmGetColorControllerUIElement((CPColorController*)con->rgbColorController), 0);
  cmAddUIRow(cmGetColorControllerUIElement((CPColorController*)con->hsvhslColorController), 0);
  cmAddUIRow(cmGetColorControllerUIElement((CPColorController*)con->ycbcrColorController), 0);
  cmEndUILayout();

  cmBeginUILayout(con->rightSpace, naMakeBezel4Zero());
  cmAddUIRow(con->radiometricColorsSpace, 0);
  cmAddUICol(con->perceptiveColorsSpace, 0);
  cmAddUICol(con->RGBColorsSpace, 0);
  cmEndUILayout();

  cmBeginUILayout(contentSpace, naMakeBezel4Zero());
  cmAddUIRow(cmGetMachineUIElement(con->machineController), 0);
  cmAddUICol(con->rightSpace, 0);
  cmEndUILayout();

  return con;
}



void cmDeallocMachineWindowController(CPMachineWindowController* con){
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



void cmShowMachineWindowController(CPMachineWindowController* con){
  naShowWindow(con->window);
}



CPColorController* cmGetInitialColorController(CPMachineWindowController* con){
  return (CPColorController*)con->grayColorController;
}



void cmUpdateMachineWindowController(CPMachineWindowController* con){
  cmUpdateMachineController(con->machineController);
  
  cmSetColorControllerActive((CPColorController*)con->grayColorController, cmGetCurrentColorController() == (CPColorController*)con->grayColorController);
  cmSetColorControllerActive((CPColorController*)con->hsvhslColorController, cmGetCurrentColorController() == (CPColorController*)con->hsvhslColorController);
  cmSetColorControllerActive((CPColorController*)con->lablchColorController, cmGetCurrentColorController() == (CPColorController*)con->lablchColorController);
  cmSetColorControllerActive((CPColorController*)con->luvuvwColorController, cmGetCurrentColorController() == (CPColorController*)con->luvuvwColorController);
  cmSetColorControllerActive((CPColorController*)con->rgbColorController, cmGetCurrentColorController() == (CPColorController*)con->rgbColorController);
  cmSetColorControllerActive((CPColorController*)con->spectralColorController, cmGetCurrentColorController() == (CPColorController*)con->spectralColorController);
  cmSetColorControllerActive((CPColorController*)con->xyzColorController, cmGetCurrentColorController() == (CPColorController*)con->xyzColorController);
  cmSetColorControllerActive((CPColorController*)con->ycbcrColorController, cmGetCurrentColorController() == (CPColorController*)con->ycbcrColorController);
  cmSetColorControllerActive((CPColorController*)con->yuvyupvpColorController, cmGetCurrentColorController() == (CPColorController*)con->yuvyupvpColorController);
  cmSetColorControllerActive((CPColorController*)con->yxyColorController, cmGetCurrentColorController() == (CPColorController*)con->yxyColorController);

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
