
#include "NAApp.h"
#include "NAVectorAlgebra.h"
#include "NA3DHelper.h"

#include "mainC.h"
#include "ThreeDeeController.h"
#include "ThreeDeeView.h"
#include <CML.h>

struct CMThreeDeeController{
  NAWindow* window;
  NAOpenGLSpace* display;
  NASpace* controlSpace;
  
  NALabel* axisLabel;
  NACheckBox* axisCheckBox;
  NALabel* spectrumLabel;
  NACheckBox* spectrumCheckBox;
  NALabel* fovyLabel;
  NASlider* fovySlider;
  NALabel* backgroundLabel;
  NASlider* backgroundSlider;
  
  NAInt fontId;
  
  NABool showSpectrum;
  NABool showAxis;
  double backgroundGray;
  
  double fovy;
  double viewPol;
  double viewEqu;
  double zoom;
};



void cmFixThreeDeeViewParameters(CMThreeDeeController* con){
  if(con->zoom <= .025f){con->zoom = .025f;}
  if(con->zoom >= 2.f){con->zoom = 2.f;}
  if(con->viewEqu < -NA_PIf){con->viewEqu += NA_PI2f;}
  if(con->viewEqu > NA_PIf){con->viewEqu -= NA_PI2f;}
  if(con->viewPol <= NA_SINGULARITYf){con->viewPol = NA_SINGULARITYf;}
  if(con->viewPol >= NA_PIf - NA_SINGULARITYf){con->viewPol = NA_PIf - NA_SINGULARITYf;}
}


double cmGetAxisGray(CMThreeDeeController* con){
  float axisGray = con->backgroundGray + .5f;
  if(axisGray > 1.f){axisGray -= 1.f;}
  return axisGray;
}



void cmInitThreeDeeOpenGL(void* data){
  CMThreeDeeController* con = (CMThreeDeeController*)data;
  con->fontId = naStartupPixelFont();
}



NABool cmReshapeThreeDeeWindow(NAReaction reaction){
  CMThreeDeeController* con = (CMThreeDeeController*)reaction.controller;

  double controlWidth = 230;
  double controlHeight = 300;

  NARect windowRect = naGetUIElementRect(con->window, NA_NULL, NA_FALSE);
  NARect openGLRect = naMakeRectS(
    0,
    0,
    windowRect.size.width - controlWidth,
    windowRect.size.height);
  NARect controlRect = naMakeRectS(
    windowRect.size.width - controlWidth,
    windowRect.size.height - controlHeight,
    controlWidth,
    controlHeight);
  naSetOpenGLSpaceInnerRect(con->display, openGLRect);
  naSetSpaceRect(con->controlSpace, controlRect);

  return NA_TRUE;
}



NABool cmMoveThreeDeeDisplayMouse(NAReaction reaction){
  CMThreeDeeController* con = (CMThreeDeeController*)reaction.controller;

  const NAMouseStatus* status = naGetMouseStatus();
  if(status->leftPressed){
    
    NAPos mouseDiff = naMakePos(status->pos.x - status->prevPos.x, status->pos.y - status->prevPos.y);
    double scaleFactor = cmGetUIScaleFactorForWindow(naGetUIElementNativePtr(con->window));

    con->viewEqu -= mouseDiff.x * .01f * scaleFactor;
    con->viewPol += mouseDiff.y * .01f * scaleFactor;

    cmFixThreeDeeViewParameters(con);
    naRefreshUIElement(con->display, 0.);
  }
  return NA_TRUE;
}



NABool cmScrollThreeDeeDisplay(NAReaction reaction){
  CMThreeDeeController* con = (CMThreeDeeController*)reaction.controller;

  const NAMouseStatus* status = naGetMouseStatus();
  
  con->zoom *= 1. + (status->pos.y - status->prevPos.y) * .01;
  cmFixThreeDeeViewParameters(con);
  naRefreshUIElement(con->display, 0.);

  return NA_TRUE;
}



NABool cmUpdateThreeDeeDisplay(NAReaction reaction){
  CMThreeDeeController* con = (CMThreeDeeController*)reaction.controller;
  
  CMLColorMachine* cm = cmGetCurrentColorMachine();
  
  CMLColorType coordSpace = CML_COLOR_XYZ;
  CMLNormedConverter normedCoordConverter = cmlGetNormedOutputConverter(CML_COLOR_XYZ);
  float min[3];
  float max[3];
  const char* labels[3];
  NASize viewSize;
  int primeAxis;
  double scale[3];
  NAInt hueIndex;

  viewSize = naGetUIElementRect(con->display, NA_NULL, NA_FALSE).size;
  cmlGetMinBounds(min, coordSpace);
  cmlGetMaxBounds(max, coordSpace);
  labels[0] = "X";
  labels[1] = "Y";
  labels[2] = "Z";
  primeAxis = 1;
  naFillV3d(scale, 1.f, 1.f, 1.f);

  CMLVec3 backgroupRGB;
  CMLVec3 axisRGB;
  double axisGray = cmGetAxisGray(con);
  cmlSet3(backgroupRGB, con->backgroundGray, con->backgroundGray, con->backgroundGray);
  cmlSet3(axisRGB, axisGray, axisGray, axisGray);

  double curZoom;
  if(con->fovy == 0){
    curZoom = con->zoom;
  }else{
    curZoom = (viewSize.width / 300.) * con->zoom / (2. * (viewSize.width / viewSize.height) * tan(.5 * naDegToRad(con->fovy)));
  }

  hueIndex = -1;
//  if((coord3d == COORDSYSTEM_HSV_CARTESIAN) || (coord3d == COORDSYSTEM_HSL_CARTESIAN)){
//    hueIndex = 0;
//  }else if(coord3d == COORDSYSTEM_LCH_CARTESIAN){
//    hueIndex = 2;
//  }




  cmBeginThreeDeeDrawing(backgroupRGB);

  cmSetupThreeDeeProjection(viewSize, con->fovy, con->zoom);
  cmSetupThreeDeeModelView(primeAxis, scale, curZoom, con->viewPol, con->viewEqu);

  if(con->showSpectrum){cmDrawThreeDeeSpectrum(cm, normedCoordConverter, coordSpace, hueIndex);}
  if(con->showAxis){cmDrawThreeDeeAxis(normedCoordConverter, min, max, labels, axisRGB, con->fontId);}

  cmEndThreeDeeDrawing(con->display);
    
  return NA_TRUE;
}



NABool cmPressThreeDeeDisplayButton(NAReaction reaction){
  CMThreeDeeController* con = (CMThreeDeeController*)reaction.controller;

  if(reaction.uiElement == con->spectrumCheckBox){
    con->showSpectrum = naGetCheckBoxState(con->spectrumCheckBox);
  }else if(reaction.uiElement == con->axisCheckBox){
    con->showAxis = naGetCheckBoxState(con->axisCheckBox);
  }

  cmUpdateThreeDeeController(con);

  return TRUE;
}



NABool cmChangeThreeDeeDisplaySlider(NAReaction reaction){
  CMThreeDeeController* con = (CMThreeDeeController*)reaction.controller;

  if(reaction.uiElement == con->fovySlider){
    con->fovy = naGetSliderValue(con->fovySlider);
    if(con->fovy < 10.f){con->fovy = 0.f;}
  }else if(reaction.uiElement == con->backgroundSlider){
    con->backgroundGray = naGetSliderValue(con->backgroundSlider);
  }
  
  cmUpdateThreeDeeController(con);

  return TRUE;
}



CMThreeDeeController* cmAllocThreeDeeController(void){
  CMThreeDeeController* con = naAlloc(CMThreeDeeController);
  naZeron(con, sizeof(CMThreeDeeController));
  
  // Create childs
  con->window = naNewWindow("3D", naMakeRectS(40, 30, 700, 500), NA_WINDOW_RESIZEABLE, 0);
  con->display = naNewOpenGLSpace(naMakeSize(300, 300), cmInitThreeDeeOpenGL, con);
  con->controlSpace = naNewSpace(naMakeSize(230, 400));
  naSetSpaceAlternateBackground(con->controlSpace, NA_TRUE);

  con->axisLabel = naNewLabel("Axis", 100);
  con->axisCheckBox = naNewCheckBox("", 30);
  con->spectrumLabel = naNewLabel("Spectrum", 100);
  con->spectrumCheckBox = naNewCheckBox("", 30);

  con->fovyLabel = naNewLabel("Fovy", 100);
  con->fovySlider = naNewSlider(100);
  naSetSliderRange(con->fovySlider, 0., 90., 0);
  con->backgroundLabel = naNewLabel("Background", 100);
  con->backgroundSlider = naNewSlider(100);
  naSetSliderRange(con->backgroundSlider, 0., 1., 0);

  // Add childs
  NASpace* content = naGetWindowContentSpace(con->window);
  naAddSpaceChild(content, con->display, naMakePos(0, 0));
  naAddSpaceChild(content, con->controlSpace, naMakePos(300, 0));

  NAInt y = 100;
  naAddSpaceChild(con->controlSpace, con->axisLabel, naMakePos(10, y));
  naAddSpaceChild(con->controlSpace, con->axisCheckBox, naMakePos(115, y));
  y -= 25;
  naAddSpaceChild(con->controlSpace, con->spectrumLabel, naMakePos(10, y));
  naAddSpaceChild(con->controlSpace, con->spectrumCheckBox, naMakePos(115, y));
  y -= 25;
  naAddSpaceChild(con->controlSpace, con->backgroundLabel, naMakePos(10, y));
  naAddSpaceChild(con->controlSpace, con->backgroundSlider, naMakePos(115, y));
  y -= 25;
  naAddSpaceChild(con->controlSpace, con->fovyLabel, naMakePos(10, y));
  naAddSpaceChild(con->controlSpace, con->fovySlider, naMakePos(115, y));
  
  // Add reactions
  naAddUIReaction(con->window, NA_UI_COMMAND_RESHAPE, cmReshapeThreeDeeWindow, con);
  naAddUIReaction(con->display, NA_UI_COMMAND_REDRAW, cmUpdateThreeDeeDisplay, con);
  naAddUIReaction(con->display, NA_UI_COMMAND_MOUSE_MOVED, cmMoveThreeDeeDisplayMouse, con);
  naAddUIReaction(con->display, NA_UI_COMMAND_SCROLLED, cmScrollThreeDeeDisplay, con);
  naAddUIReaction(con->axisCheckBox, NA_UI_COMMAND_PRESSED, cmPressThreeDeeDisplayButton, con);
  naAddUIReaction(con->spectrumCheckBox, NA_UI_COMMAND_PRESSED, cmPressThreeDeeDisplayButton, con);
  naAddUIReaction(con->fovySlider, NA_UI_COMMAND_EDITED, cmChangeThreeDeeDisplaySlider, con);
  naAddUIReaction(con->backgroundSlider, NA_UI_COMMAND_EDITED, cmChangeThreeDeeDisplaySlider, con);
  
  // Set initial values
  float scaleFactor = cmGetUIScaleFactorForWindow(naGetUIElementNativePtr(con->window));

  con->showSpectrum = NA_TRUE;
  con->showAxis = NA_TRUE;
  con->backgroundGray = 0.3;
  con->fovy = 50.;
  con->viewPol = 1.3f;
  con->viewEqu = NA_PIf / 4.f;
  con->zoom = 1. / scaleFactor;

  // Reshape the whole window
  NAReaction dummyReaction = {con->window, NA_UI_COMMAND_RESHAPE, con};
  cmReshapeThreeDeeWindow(dummyReaction);

  return con;
}



void cmDeallocThreeDeeController(CMThreeDeeController* con){
  naShutdownPixelFont(con->fontId);
  naFree(con);
}



void cmShowThreeDeeController(CMThreeDeeController* con){
  naShowWindow(con->window);
}



void cmUpdateThreeDeeController(CMThreeDeeController* con){
  naSetCheckBoxState(con->spectrumCheckBox, con->showSpectrum);
  naSetCheckBoxState(con->axisCheckBox, con->showAxis);
  naSetSliderValue(con->backgroundSlider, con->backgroundGray);
  naSetSliderValue(con->fovySlider, con->fovy);

  naRefreshUIElement(con->display, 0.);
}
