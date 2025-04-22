
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
#include "NAUtility/NAMemory.h"
#include "NAUtility/NAThreading.h"



void cpControllerWindowCloses(NAReaction reaction){
  naStopApplication();
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
    naMakeRectS(200, 200, 700, 500),
    0,
    CP_COLOR_PRESTO_STORAGE_TAG);
  naAddUIReaction(con->window, NA_UI_COMMAND_CLOSES, cpControllerWindowCloses, con);
    
  //naDebugUIElement(con->window);

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
  con->yuvyupvpColorController = cpAllocYuvYupvpColorController();
  con->ycbcrColorController = cpAllocYCbCrColorController();
  con->yxyColorController = cpAllocYxyColorController();

  cpBeginUILayout(con->radiometricColorsSpace, naMakeBorder2D(0., 0., 0., 0.));
  cpAddUIRow(cpGetColorControllerUIElement((CPColorController*)con->spectralColorController), 0);
  cpAddUIRow(cpGetColorControllerUIElement((CPColorController*)con->xyzColorController), 0);
  cpAddUIRow(cpGetColorControllerUIElement((CPColorController*)con->yxyColorController), 0);
  cpAddUIRow(cpGetColorControllerUIElement((CPColorController*)con->yuvyupvpColorController), 0);
  cpAddUIRow(cpGetColorControllerUIElement((CPColorController*)con->luvuvwColorController), 0);
  cpEndUILayout();

  cpBeginUILayout(con->perceptiveColorsSpace, naMakeBorder2D(0., 0., 0., 0.));
  cpAddUIRow(cpGetColorControllerUIElement((CPColorController*)con->grayColorController), 0);
  cpAddUIRow(cpGetColorControllerUIElement((CPColorController*)con->lablchColorController), 0);
  cpAddUIRow(cpGetColorControllerUIElement((CPColorController*)con->rgbColorController), 0);
  cpAddUIRow(cpGetColorControllerUIElement((CPColorController*)con->hsvhslColorController), 0);
  cpAddUIRow(cpGetColorControllerUIElement((CPColorController*)con->ycbcrColorController), 0);
  cpEndUILayout();

  cpBeginUILayout(con->rightSpace, naMakeBorder2D(0., 0., 0., 0.));
  cpAddUIRow(con->radiometricColorsSpace, 0);
  cpAddUICol(con->perceptiveColorsSpace, 0);
  cpAddUICol(con->RGBColorsSpace, 0);
  cpEndUILayout();

  cpBeginUILayout(contentSpace, naMakeBorder2D(0., 0., 0., 0.));
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
  cpDeallocYuvYupvpColorController(con->yuvyupvpColorController);
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



void cpUpdateColorWells(CPMachineWindowController* con) {
  // Compute the controller data with threads
  NAThread GrayThread     = naMakeThread("Compute Gray",      (NAMutator)cpComputeGrayColorController,     con->grayColorController);
  NAThread HSVHSLThread   = naMakeThread("Compute HSV/HSL",   (NAMutator)cpComputeHSVHSLColorController,   con->hsvhslColorController);
  NAThread LabLchThread   = naMakeThread("Compute Lab/Lch",   (NAMutator)cpComputeLabLchColorController,   con->lablchColorController);
  NAThread LuvUVWThread   = naMakeThread("Compute Luv/UVW",   (NAMutator)cpComputeLuvUVWColorController,   con->luvuvwColorController);
  NAThread RGBThread      = naMakeThread("Compute RGB",       (NAMutator)cpComputeRGBColorController,      con->rgbColorController);
  NAThread SpectralThread = naMakeThread("Compute Spectral",  (NAMutator)cpComputeSpectralColorController, con->spectralColorController);
  NAThread XYZThread      = naMakeThread("Compute XYZ",       (NAMutator)cpComputeXYZColorController,      con->xyzColorController);
  NAThread YCbCrThread    = naMakeThread("Compute YCbCr",     (NAMutator)cpComputeYCbCrColorController,    con->ycbcrColorController);
  NAThread YuvYupvpThread = naMakeThread("Compute Yuv/Yupvp", (NAMutator)cpComputeYuvYupvpColorController, con->yuvyupvpColorController);
  NAThread YyxThread      = naMakeThread("Compute Yxy",       (NAMutator)cpComputeYxyColorController,      con->yxyColorController);

  // Start all threads.
  naRunThread(GrayThread);
  naRunThread(HSVHSLThread);
  naRunThread(LabLchThread);
  naRunThread(LuvUVWThread);
  naRunThread(RGBThread);
  naRunThread(SpectralThread);
  naRunThread(XYZThread);
  naRunThread(YCbCrThread);
  naRunThread(YuvYupvpThread);
  naRunThread(YyxThread);

  // Await all threads before updating the color controller UIs
  naAwaitThread(GrayThread);
  naAwaitThread(HSVHSLThread);
  naAwaitThread(LabLchThread);
  naAwaitThread(LuvUVWThread);
  naAwaitThread(RGBThread);
  naAwaitThread(SpectralThread);
  naAwaitThread(XYZThread);
  naAwaitThread(YCbCrThread);
  naAwaitThread(YuvYupvpThread);
  naAwaitThread(YyxThread);

  cpUpdateGrayColorController(con->grayColorController);
  cpUpdateHSVHSLColorController(con->hsvhslColorController);
  cpUpdateLabLchColorController(con->lablchColorController);
  cpUpdateLuvUVWColorController(con->luvuvwColorController);
  cpUpdateRGBColorController(con->rgbColorController);
  cpUpdateSpectralColorController(con->spectralColorController);
  cpUpdateXYZColorController(con->xyzColorController);
  cpUpdateYCbCrColorController(con->ycbcrColorController);
  cpUpdateYuvYupvpColorController(con->yuvyupvpColorController);
  cpUpdateYxyColorController(con->yxyColorController);
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
}
