
#include "CMMachineWindowController.h"

#include "CMMachineController.h"
#include "../ColorControllers/CMColorController.h"
#include "../CMDesign.h"
#include "../CMTranslations.h"

#include "../ColorControllers/CMGrayColorController.h"
#include "../ColorControllers/CMHSVHSLColorController.h"
#include "../ColorControllers/CMLabLchColorController.h"
#include "../ColorControllers/CMLuvUVWColorController.h"
#include "../ColorControllers/CMRGBColorController.h"
#include "../ColorControllers/CMSpectralColorController.h"
#include "../ColorControllers/CMXYZColorController.h"
#include "../ColorControllers/CMYCbCrColorController.h"
#include "../ColorControllers/CMYuvYupvpColorController.h"
#include "../ColorControllers/CMYxyColorController.h"

#include "NAApp.h"



struct CMMachineWindowController{
  NAWindow* window;
  
  CMMachineController* machineController;
  
  NASpace* rightSpace;
  NASpace* radiometricColorsSpace;
  NASpace* perceptiveColorsSpace;
  NASpace* RGBColorsSpace;
  
  CMGrayColorController* grayColorController;
  CMHSVHSLColorController* hsvhslColorController;
  CMLabLchColorController* lablchColorController;
  CMLuvUVWColorController* luvuvwColorController;
  CMRGBColorController* rgbColorController;
  CMSpectralColorController* spectralColorController;
  CMXYZColorController* xyzColorController;
  CMYCbCrColorController* ycbcrColorController;
  CMYuvYupvpColorController* yuvyupvpColorController;
  CMYxyColorController* yxyColorController;
};



CMMachineWindowController* cmAllocMachineWindowController(void){
  CMMachineWindowController* con = naAlloc(CMMachineWindowController);

  con->window = naNewWindow(
    cmTranslate(CMApplicationName),
    naMakeRectS(200, 200, 500, 500),
    0,
    0);
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
  cmAddUIRow(cmGetColorControllerUIElement((CMColorController*)con->spectralColorController), 0);
  cmAddUIRow(cmGetColorControllerUIElement((CMColorController*)con->xyzColorController), 0);
  cmAddUIRow(cmGetColorControllerUIElement((CMColorController*)con->yxyColorController), 0);
  cmAddUIRow(cmGetColorControllerUIElement((CMColorController*)con->yuvyupvpColorController), 0);
  cmAddUIRow(cmGetColorControllerUIElement((CMColorController*)con->luvuvwColorController), 0);
  cmEndUILayout();

  cmBeginUILayout(con->perceptiveColorsSpace, naMakeBezel4Zero());
  cmAddUIRow(cmGetColorControllerUIElement((CMColorController*)con->grayColorController), 0);
  cmAddUIRow(cmGetColorControllerUIElement((CMColorController*)con->lablchColorController), 0);
  cmAddUIRow(cmGetColorControllerUIElement((CMColorController*)con->rgbColorController), 0);
  cmAddUIRow(cmGetColorControllerUIElement((CMColorController*)con->hsvhslColorController), 0);
  cmAddUIRow(cmGetColorControllerUIElement((CMColorController*)con->ycbcrColorController), 0);
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



void cmDeallocMachineWindowController(CMMachineWindowController* con){
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



void cmShowMachineWindowController(CMMachineWindowController* con){
  naShowWindow(con->window);
}



CMColorController* cmGetInitialColorController(CMMachineWindowController* con){
  return (CMColorController*)con->grayColorController;
}



void cmUpdateMachineWindowController(CMMachineWindowController* con){
  cmUpdateMachineController(con->machineController);
  
  cmSetColorControllerActive((CMColorController*)con->grayColorController, cmGetCurrentColorController() == (CMColorController*)con->grayColorController);
  cmSetColorControllerActive((CMColorController*)con->hsvhslColorController, cmGetCurrentColorController() == (CMColorController*)con->hsvhslColorController);
  cmSetColorControllerActive((CMColorController*)con->lablchColorController, cmGetCurrentColorController() == (CMColorController*)con->lablchColorController);
  cmSetColorControllerActive((CMColorController*)con->luvuvwColorController, cmGetCurrentColorController() == (CMColorController*)con->luvuvwColorController);
  cmSetColorControllerActive((CMColorController*)con->rgbColorController, cmGetCurrentColorController() == (CMColorController*)con->rgbColorController);
  cmSetColorControllerActive((CMColorController*)con->spectralColorController, cmGetCurrentColorController() == (CMColorController*)con->spectralColorController);
  cmSetColorControllerActive((CMColorController*)con->xyzColorController, cmGetCurrentColorController() == (CMColorController*)con->xyzColorController);
  cmSetColorControllerActive((CMColorController*)con->ycbcrColorController, cmGetCurrentColorController() == (CMColorController*)con->ycbcrColorController);
  cmSetColorControllerActive((CMColorController*)con->yuvyupvpColorController, cmGetCurrentColorController() == (CMColorController*)con->yuvyupvpColorController);
  cmSetColorControllerActive((CMColorController*)con->yxyColorController, cmGetCurrentColorController() == (CMColorController*)con->yxyColorController);

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
