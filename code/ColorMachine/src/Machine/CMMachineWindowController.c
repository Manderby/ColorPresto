
#include "CMMachineWindowController.h"

#include "../ColorCOntrollers/CMColorController.h"
#include "CMMachineController.h"
#include "../CMDesign.h"
#include "../CMTranslations.h"

#include "../ColorCOntrollers/CMGrayColorController.h"
#include "../ColorCOntrollers/CMHSLColorController.h"
#include "../ColorCOntrollers/CMHSVColorController.h"
#include "../ColorCOntrollers/CMLabColorController.h"
#include "../ColorCOntrollers/CMLuvColorController.h"
#include "../ColorCOntrollers/CMRGBColorController.h"
#include "../ColorCOntrollers/CMSpectralColorController.h"
#include "../ColorCOntrollers/CMUVWColorController.h"
#include "../ColorCOntrollers/CMXYZColorController.h"
#include "../ColorCOntrollers/CMYCbCrColorController.h"
#include "../ColorCOntrollers/CMYuvColorController.h"
#include "../ColorCOntrollers/CMYxyColorController.h"

#include "NAApp.h"



struct CMMachineWindowController{
  NAWindow* window;
  
  CMMachineController* machineController;
  
  NASpace* radiometricColorsSpace;
  NASpace* perceptiveColorsSpace;
  NASpace* RGBColorsSpace;
  
  CMGrayColorController* grayColorController;
  CMHSLColorController* hslColorController;
  CMHSVColorController* hsvColorController;
  CMLabColorController* labColorController;
  CMLuvColorController* luvColorController;
  CMRGBColorController* rgbColorController;
  CMSpectralColorController* spectralColorController;
  CMUVWColorController* uvwColorController;
  CMXYZColorController* xyzColorController;
  CMYCbCrColorController* ycbcrColorController;
  CMYuvColorController* yuvColorController;
  CMYxyColorController* yxyColorController;
};



CMMachineWindowController* cmAllocMachineWindowController(void){
  CMMachineWindowController* con = naAlloc(CMMachineWindowController);

  con->window = naNewWindow(
    cmTranslate(CMApplicationName),
    naMakeRectS(200, 500, 500, 500),
    0,
    0);
  NASpace* contentSpace = naGetWindowContentSpace(con->window);

  con->machineController = cmAllocMachineController();

  con->radiometricColorsSpace = naNewSpace(naMakeSize(1, 1));
  con->perceptiveColorsSpace = naNewSpace(naMakeSize(1, 1));
  con->RGBColorsSpace = naNewSpace(naMakeSize(1, 1));

  con->grayColorController = cmAllocGrayColorController();
  con->hslColorController = cmAllocHSLColorController();
  con->hsvColorController = cmAllocHSVColorController();
  con->labColorController = cmAllocLabColorController();
  con->luvColorController = cmAllocLuvColorController();
  con->rgbColorController = cmAllocRGBColorController();
  con->spectralColorController = cmAllocSpectralColorController();
  con->uvwColorController = cmAllocUVWColorController();
  con->xyzColorController = cmAllocXYZColorController();
  con->yuvColorController = cmAllocYuvColorController();
  con->ycbcrColorController = cmAllocYCbCrColorController();
  con->yxyColorController = cmAllocYxyColorController();

  cmBeginUILayout(con->radiometricColorsSpace, naMakeBezel4Zero());
  cmAddUIRow(cmGetColorControllerUIElement((CMColorController*)con->spectralColorController), 0);
  cmAddUIRow(cmGetColorControllerUIElement((CMColorController*)con->xyzColorController), 0);
  cmAddUIRow(cmGetColorControllerUIElement((CMColorController*)con->yxyColorController), 0);
  cmAddUIRow(cmGetColorControllerUIElement((CMColorController*)con->yuvColorController), 0);
  cmEndUILayout();

  cmBeginUILayout(con->perceptiveColorsSpace, naMakeBezel4Zero());
  cmAddUIRow(cmGetColorControllerUIElement((CMColorController*)con->grayColorController), 0);
  cmAddUIRow(cmGetColorControllerUIElement((CMColorController*)con->labColorController), 0);
  cmAddUIRow(cmGetColorControllerUIElement((CMColorController*)con->luvColorController), 0);
  cmAddUIRow(cmGetColorControllerUIElement((CMColorController*)con->uvwColorController), 0);
  cmEndUILayout();
  
  cmBeginUILayout(con->RGBColorsSpace, naMakeBezel4(10, 0, 0, 0));
  cmAddUIRow(cmGetColorControllerUIElement((CMColorController*)con->rgbColorController), 0);
  cmAddUIRow(cmGetColorControllerUIElement((CMColorController*)con->hsvColorController), 0);
  cmAddUIRow(cmGetColorControllerUIElement((CMColorController*)con->hslColorController), 0);
  cmAddUIRow(cmGetColorControllerUIElement((CMColorController*)con->ycbcrColorController), 0);
  cmEndUILayout();

  cmBeginUILayout(contentSpace, naMakeBezel4Zero());
  cmAddUIRow(cmGetMachineUIElement(con->machineController), 0);
  cmAddUICol(con->radiometricColorsSpace, 0);
  cmAddUICol(con->perceptiveColorsSpace, 0);
  cmAddUICol(con->RGBColorsSpace, 0);
  cmEndUILayout();

  return con;
}



void cmDeallocMachineWindowController(CMMachineWindowController* con){
  cmDeallocGrayColorController(con->grayColorController);
  cmDeallocHSLColorController(con->hslColorController);
  cmDeallocHSVColorController(con->hsvColorController);
  cmDeallocLabColorController(con->labColorController);
  cmDeallocLuvColorController(con->luvColorController);
  cmDeallocRGBColorController(con->rgbColorController);
  cmDeallocSpectralColorController(con->spectralColorController);
  cmDeallocUVWColorController(con->uvwColorController);
  cmDeallocXYZColorController(con->xyzColorController);
  cmDeallocYuvColorController(con->yuvColorController);
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
  cmSetColorControllerActive((CMColorController*)con->hslColorController, cmGetCurrentColorController() == (CMColorController*)con->hslColorController);
  cmSetColorControllerActive((CMColorController*)con->hsvColorController, cmGetCurrentColorController() == (CMColorController*)con->hsvColorController);
  cmSetColorControllerActive((CMColorController*)con->labColorController, cmGetCurrentColorController() == (CMColorController*)con->labColorController);
  cmSetColorControllerActive((CMColorController*)con->luvColorController, cmGetCurrentColorController() == (CMColorController*)con->luvColorController);
  cmSetColorControllerActive((CMColorController*)con->rgbColorController, cmGetCurrentColorController() == (CMColorController*)con->rgbColorController);
  cmSetColorControllerActive((CMColorController*)con->spectralColorController, cmGetCurrentColorController() == (CMColorController*)con->spectralColorController);
  cmSetColorControllerActive((CMColorController*)con->uvwColorController, cmGetCurrentColorController() == (CMColorController*)con->uvwColorController);
  cmSetColorControllerActive((CMColorController*)con->xyzColorController, cmGetCurrentColorController() == (CMColorController*)con->xyzColorController);
  cmSetColorControllerActive((CMColorController*)con->ycbcrColorController, cmGetCurrentColorController() == (CMColorController*)con->ycbcrColorController);
  cmSetColorControllerActive((CMColorController*)con->yuvColorController, cmGetCurrentColorController() == (CMColorController*)con->yuvColorController);
  cmSetColorControllerActive((CMColorController*)con->yxyColorController, cmGetCurrentColorController() == (CMColorController*)con->yxyColorController);

  cmUpdateGrayColorController(con->grayColorController);
  cmUpdateHSLColorController(con->hslColorController);
  cmUpdateHSVColorController(con->hsvColorController);
  cmUpdateLabColorController(con->labColorController);
  cmUpdateLuvColorController(con->luvColorController);
  cmUpdateRGBColorController(con->rgbColorController);
  cmUpdateSpectralColorController(con->spectralColorController);
  cmUpdateUVWColorController(con->uvwColorController);
  cmUpdateXYZColorController(con->xyzColorController);
  cmUpdateYCbCrColorController(con->ycbcrColorController);
  cmUpdateYuvColorController(con->yuvColorController);
  cmUpdateYxyColorController(con->yxyColorController);
}
