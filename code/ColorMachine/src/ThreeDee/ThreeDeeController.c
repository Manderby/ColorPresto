
#include "NAApp.h"
#include "NAVectorAlgebra.h"
#include "NA3DHelper.h"

#include "mainC.h"
#include "ThreeDeeController.h"
#include "ThreeDeeView.h"
#include <CML.h>

typedef enum{
  COORD_SYS_XYZ,
  COORD_SYS_YXY,
  COORD_SYS_Yuv,
  COORD_SYS_YCBCR,
  COORD_SYS_LAB,
  COORD_SYS_LCH_CARTESIAN,
  COORD_SYS_LUV,
  COORD_SYS_RGB,
  COORD_SYS_HSV,
  COORD_SYS_HSV_CARTESIAN,
  COORD_SYS_HSL,
  COORD_SYS_HSL_CARTESIAN,
  COORD_SYS_COUNT
} CoordSysType;

const char* cm_coordSysNames[COORD_SYS_COUNT] = {
  "XYZ",
  "Yxy",
  "Yuv",
  "YCbCr",
  "Lab",
  "Lch Cartesian",
  "Luv",
  "RGB",
  "HSV",
  "HSV Cartesian",
  "HSL",
  "HSL Cartesian",
};

struct CMThreeDeeController{
  NAWindow* window;
  NAOpenGLSpace* display;
  NASpace* controlSpace;
  
  NALabel* colorSpaceLabel;
  NAPopupButton* colorSpacePopupButton;
  NALabel* coordSysLabel;
  NAPopupButton* coordSysPopupButton;

  NALabel* stepsLabel;
  NASlider* stepsSlider;

  NALabel* rotationLabel;
  NAButton* rotationButton;
  NASlider* rotationSlider;

  NALabel* pointsOpacityLabel;
  NASlider* pointsOpacitySlider;
  NALabel* gridAlphaLabel;
  NASlider* gridAlphaSlider;
  NALabel* gridTintLabel;
  NASlider* gridTintSlider;
  NALabel* bodyAlphaLabel;
  NASlider* bodyAlphaSlider;
  NALabel* bodySolidLabel;
  NACheckBox* bodySolidCheckBox;

  NALabel* axisLabel;
  NACheckBox* axisCheckBox;
  NALabel* spectrumLabel;
  NACheckBox* spectrumCheckBox;
  NALabel* fovyLabel;
  NASlider* fovySlider;
  NALabel* backgroundLabel;
  NASlider* backgroundSlider;
  
  NAInt fontId;
  
  CMLColorType colorSpace;
  CoordSysType coordSys;
  NAInt steps3D;

  double rotationStep;

  double pointsOpacity;
  double gridAlpha;
  double gridTint;
  double bodyAlpha;
  NABool bodySolid;

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
  cmInitThreeDeeDisplay(con->display);
}



NABool cmReshapeThreeDeeWindow(NAReaction reaction){
  CMThreeDeeController* con = (CMThreeDeeController*)reaction.controller;

  double controlWidth = 230;
  double controlHeight = 425;

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



void cmStepRotation(void* data){
  CMThreeDeeController* con = (CMThreeDeeController*)data;
  if(con->rotationStep != 0.){
    con->viewEqu -= con->rotationStep * .03;
    naCallApplicationFunctionInSeconds(cmStepRotation, data, 1/60.);
    cmUpdateThreeDeeController(con);
  }
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
  CMLColorMachine* sm = cmGetCurrentScreenMachine();
  
  CMLColorType coordSpace;
  int primeAxis;
  double scale[3];
  const NAUTF8Char* labels[3];
  CMLNormedConverter normedCoordConverter;

  switch(con->coordSys){
  case COORD_SYS_XYZ:
    coordSpace = CML_COLOR_XYZ;
    primeAxis = 1;
    naFillV3d(scale, 1., 1., 1.);
    labels[0] = "X";
    labels[1] = "Y";
    labels[2] = "Z";
    normedCoordConverter = cmlGetNormedOutputConverter(CML_COLOR_XYZ);
    break;
  case COORD_SYS_YXY:
    coordSpace = CML_COLOR_Yxy;
    primeAxis = 0;
    naFillV3d(scale, 1., 1., 1.);
    labels[0] = "Y";
    labels[1] = "x";
    labels[2] = "y";
    normedCoordConverter = cmlGetNormedOutputConverter(CML_COLOR_Yxy);
    break;
  case COORD_SYS_Yuv:
    coordSpace = CML_COLOR_Yuv;
    primeAxis = 0;
    naFillV3d(scale, 1., 1., 1.);
    labels[0] = "Y";
    labels[1] = "u";
    labels[2] = "v";
    normedCoordConverter = cmlGetNormedOutputConverter(CML_COLOR_Yuv);
    break;
  case COORD_SYS_YCBCR:
    coordSpace = CML_COLOR_YCbCr;
    primeAxis = 0;
    naFillV3d(scale, 1., 1., 1.);
    labels[0] = "Y";
    labels[1] = "Cb";
    labels[2] = "Cr";
    normedCoordConverter = cmlGetNormedOutputConverter(CML_COLOR_YCbCr);
    break;
  case COORD_SYS_LAB:
    coordSpace = CML_COLOR_Lab;
    primeAxis = 0;
    naFillV3d(scale, 1., 2.56, 2.56);
    labels[0] = "L";
    labels[1] = "a";
    labels[2] = "b";
    normedCoordConverter = cmlGetNormedOutputConverter(CML_COLOR_Lab);
    break;
  case COORD_SYS_LCH_CARTESIAN:
    coordSpace = CML_COLOR_Lch;
    primeAxis = 0;
    naFillV3d(scale, 1., 1., 3.60);
    labels[0] = "L";
    labels[1] = "c";
    labels[2] = "h";
    normedCoordConverter = cmlGetNormedOutputConverter(CML_COLOR_Lch);
    break;
  case COORD_SYS_LUV:
    coordSpace = CML_COLOR_Luv;
    primeAxis = 0;
    naFillV3d(scale, 1., 1., 1.);
    labels[0] = "L";
    labels[1] = "u";
    labels[2] = "v";
    normedCoordConverter = cmlGetNormedOutputConverter(CML_COLOR_Luv);
    break;
  case COORD_SYS_RGB:
    coordSpace = CML_COLOR_RGB;
    primeAxis = 1;
    naFillV3d(scale, 1., 1., 1.);
    labels[0] = "R";
    labels[1] = "G";
    labels[2] = "B";
    normedCoordConverter = cmlGetNormedOutputConverter(CML_COLOR_RGB);
    break;
  case COORD_SYS_HSV:
    coordSpace = CML_COLOR_HSV;
    primeAxis = 2;
    naFillV3d(scale, 2., 2., 1.);
    labels[0] = "";
    labels[1] = "S";
    labels[2] = "V";
    normedCoordConverter = cmlGetNormedCartesianOutputConverter(CML_COLOR_HSV);
    break;
  case COORD_SYS_HSV_CARTESIAN:
    coordSpace = CML_COLOR_HSV;
    primeAxis = 2;
    naFillV3d(scale, 3.60, -1., 1.);
    labels[0] = "H";
    labels[1] = "S";
    labels[2] = "V";
    normedCoordConverter = cmlGetNormedOutputConverter(CML_COLOR_HSV);
    break;
  case COORD_SYS_HSL:
    coordSpace = CML_COLOR_HSL;
    primeAxis = 2;
    naFillV3d(scale, 2., 2., 1.);
    labels[0] = "";
    labels[1] = "S";
    labels[2] = "L";
    normedCoordConverter = cmlGetNormedCartesianOutputConverter(CML_COLOR_HSL);
    break;
  case COORD_SYS_HSL_CARTESIAN:
    coordSpace = CML_COLOR_HSL;
    primeAxis = 2;
    naFillV3d(scale, 3.60, -1., 1.);
    labels[0] = "H";
    labels[1] = "S";
    labels[2] = "L";
    normedCoordConverter = cmlGetNormedOutputConverter(CML_COLOR_HSL);
    break;
  default:
    return NA_FALSE;
  }




  CMLNormedConverter normedInputConverter = cmlGetNormedInputConverter(con->colorSpace);
  CMLColorConverter coordConverter = cmlGetColorConverter(coordSpace, con->colorSpace);
  float min[3];
  float max[3];
  NASize viewSize;

  viewSize = naGetUIElementRect(con->display, NA_NULL, NA_FALSE).size;
  cmlGetMinBounds(min, coordSpace);
  cmlGetMaxBounds(max, coordSpace);

  CMLVec3 backgroundRGB;
  CMLVec3 axisRGB;
  double axisGray = cmGetAxisGray(con);
  cmlSet3(backgroundRGB, con->backgroundGray, con->backgroundGray, con->backgroundGray);
  cmlSet3(axisRGB, axisGray, axisGray, axisGray);

  double curZoom;
  if(con->fovy == 0){
    curZoom = con->zoom;
  }else{
    curZoom = (viewSize.width / 300.) * con->zoom / (2. * (viewSize.width / viewSize.height) * tan(.5 * naDegToRad(con->fovy)));
  }

  NAInt hueIndex = -1;
  if((con->coordSys == COORD_SYS_HSV_CARTESIAN) || (con->coordSys == COORD_SYS_HSL_CARTESIAN)){
    hueIndex = 0;
  }else if(con->coordSys == COORD_SYS_LCH_CARTESIAN){
    hueIndex = 2;
  }

  cmBeginThreeDeeDrawing(backgroundRGB);

  cmSetupThreeDeeProjection(viewSize, con->fovy, con->zoom);
  cmSetupThreeDeeModelView(primeAxis, scale, curZoom, con->viewPol, con->viewEqu);

  if(1){
    cmDrawThreeDeeSurfaces(
      cm,
      sm,
      backgroundRGB,
      axisRGB,
      con->bodySolid,
      con->bodyAlpha,
      con->gridAlpha,
      con->gridTint,
      con->colorSpace,
      con->steps3D,
      normedInputConverter,
      coordConverter,
      normedCoordConverter,
      hueIndex);
  }
  
  if(con->pointsOpacity > 0.f){
    cmDrawThreeDeePointCloud(
      cm,
      sm,
      con->pointsOpacity,
      con->colorSpace,
      con->steps3D,
      normedInputConverter,
      coordConverter,
      normedCoordConverter,
      con->zoom);
  }

  if(con->showSpectrum){
    cmDrawThreeDeeSpectrum(
      cm,
      normedCoordConverter,
      coordSpace,
      hueIndex);
  }
  
  if(con->showAxis){
    cmDrawThreeDeeAxis(
      normedCoordConverter,
      min,
      max,
      labels,
      axisRGB,
      con->fontId);
  }

  cmEndThreeDeeDrawing(con->display);
    
  return NA_TRUE;
}



NABool cmPressThreeDeeDisplayButton(NAReaction reaction){
  CMThreeDeeController* con = (CMThreeDeeController*)reaction.controller;

  if(reaction.uiElement == con->rotationButton){
    con->rotationStep = 0.;
  }else if(reaction.uiElement == con->bodySolidCheckBox){
    con->bodySolid = naGetCheckBoxState(con->bodySolidCheckBox);
  }else if(reaction.uiElement == con->spectrumCheckBox){
    con->showSpectrum = naGetCheckBoxState(con->spectrumCheckBox);
  }else if(reaction.uiElement == con->axisCheckBox){
    con->showAxis = naGetCheckBoxState(con->axisCheckBox);
  }

  cmUpdateThreeDeeController(con);

  return TRUE;
}



NABool cmSelectColorSpace(NAReaction reaction){
  CMThreeDeeController* con = (CMThreeDeeController*)reaction.controller;

  size_t index = naGetPopupButtonItemIndex(con->colorSpacePopupButton, reaction.uiElement);
  if(index < CML_COLOR_CMYK){
    con->colorSpace = (CMLColorType)index;
  }
  
  cmUpdateThreeDeeController(con);

  return TRUE;
}



NABool cmSelectCoordSys(NAReaction reaction){
  CMThreeDeeController* con = (CMThreeDeeController*)reaction.controller;

  size_t index = naGetPopupButtonItemIndex(con->coordSysPopupButton, reaction.uiElement);
  con->coordSys = (CoordSysType)index;
  
  cmUpdateThreeDeeController(con);

  return TRUE;
}



NABool cmChangeThreeDeeDisplaySlider(NAReaction reaction){
  CMThreeDeeController* con = (CMThreeDeeController*)reaction.controller;

  if(reaction.uiElement == con->stepsSlider){
    con->steps3D = (NAInt)naGetSliderValue(con->stepsSlider);
  }else if(reaction.uiElement == con->rotationSlider){
    NABool needsRotationStart = (con->rotationStep == 0.);
    con->rotationStep = naGetSliderValue(con->rotationSlider);
    if(con->rotationStep < .1 && con->rotationStep > -.1){con->rotationStep = 0.;}
    if(needsRotationStart){cmStepRotation(con);}
  }else if(reaction.uiElement == con->pointsOpacitySlider){
    con->pointsOpacity = naGetSliderValue(con->pointsOpacitySlider);
  }else if(reaction.uiElement == con->gridAlphaSlider){
    con->gridAlpha = naGetSliderValue(con->gridAlphaSlider);
  }else if(reaction.uiElement == con->gridTintSlider){
    con->gridTint = naGetSliderValue(con->gridTintSlider);
  }else if(reaction.uiElement == con->bodyAlphaSlider){
    con->bodyAlpha = naGetSliderValue(con->bodyAlphaSlider);
  }else if(reaction.uiElement == con->backgroundSlider){
    con->backgroundGray = naGetSliderValue(con->backgroundSlider);
  }else if(reaction.uiElement == con->fovySlider){
    con->fovy = naGetSliderValue(con->fovySlider);
    if(con->fovy < 10.f){con->fovy = 0.f;}
  }
  
  cmUpdateThreeDeeController(con);

  return TRUE;
}



CMThreeDeeController* cmAllocThreeDeeController(void){
  CMThreeDeeController* con = naAlloc(CMThreeDeeController);
  naZeron(con, sizeof(CMThreeDeeController));
  
  // The window
  con->window = naNewWindow("3D", naMakeRectS(40, 30, 700, 500), NA_WINDOW_RESIZEABLE, 0);
  naAddUIReaction(con->window, NA_UI_COMMAND_RESHAPE, cmReshapeThreeDeeWindow, con);

  // The 3D space
  con->display = naNewOpenGLSpace(naMakeSize(300, 300), cmInitThreeDeeOpenGL, con);
  naAddUIReaction(con->display, NA_UI_COMMAND_REDRAW, cmUpdateThreeDeeDisplay, con);
  naAddUIReaction(con->display, NA_UI_COMMAND_MOUSE_MOVED, cmMoveThreeDeeDisplayMouse, con);
  naAddUIReaction(con->display, NA_UI_COMMAND_SCROLLED, cmScrollThreeDeeDisplay, con);

  // The control space
  con->controlSpace = naNewSpace(naMakeSize(230, 425));
//  naSetSpaceAlternateBackground(con->controlSpace, NA_TRUE);

  con->colorSpaceLabel = naNewLabel("Color Space", 100);
  con->colorSpacePopupButton = naNewPopupButton(100);
  for(size_t i = 0; i < CML_COLOR_CMYK; ++i){
    NAMenuItem* item = naNewMenuItem(cmlGetColorTypeString((CMLColorType)i));
    naAddPopupButtonMenuItem(con->colorSpacePopupButton, item, NA_NULL);
    naAddUIReaction(item, NA_UI_COMMAND_PRESSED, cmSelectColorSpace, con);
  }

  con->coordSysLabel = naNewLabel("Coordinates", 100);
  con->coordSysPopupButton = naNewPopupButton(100);
  for(size_t i = 0; i < COORD_SYS_COUNT; ++i){
    NAMenuItem* item = naNewMenuItem(cm_coordSysNames[(CoordSysType)i]);
    naAddPopupButtonMenuItem(con->coordSysPopupButton, item, NA_NULL);
    naAddUIReaction(item, NA_UI_COMMAND_PRESSED, cmSelectCoordSys, con);
  }

  con->stepsLabel = naNewLabel("Steps", 100);
  con->stepsSlider = naNewSlider(100);
  naSetSliderRange(con->stepsSlider, 2., 40., 0);
  naAddUIReaction(con->stepsSlider, NA_UI_COMMAND_EDITED, cmChangeThreeDeeDisplaySlider, con);

  con->rotationLabel = naNewLabel("Rotate", 50);
  con->rotationButton = naNewTextButton("Stop", 60, NA_BUTTON_PUSH | NA_BUTTON_BORDERED);
  con->rotationSlider = naNewSlider(100);
  naSetSliderRange(con->rotationSlider, -1., +1., 0);
  naAddUIReaction(con->rotationButton, NA_UI_COMMAND_PRESSED, cmPressThreeDeeDisplayButton, con);
  naAddUIReaction(con->rotationSlider, NA_UI_COMMAND_EDITED, cmChangeThreeDeeDisplaySlider, con);

  con->pointsOpacityLabel = naNewLabel("Points Opacity", 100);
  con->pointsOpacitySlider = naNewSlider(100);
  naSetSliderRange(con->pointsOpacitySlider, 0., 1., 0);
  naAddUIReaction(con->pointsOpacitySlider, NA_UI_COMMAND_EDITED, cmChangeThreeDeeDisplaySlider, con);

  con->gridAlphaLabel = naNewLabel("Grid Opacity", 100);
  con->gridAlphaSlider = naNewSlider(100);
  naSetSliderRange(con->gridAlphaSlider, 0., 1., 0);
  naAddUIReaction(con->gridAlphaSlider, NA_UI_COMMAND_EDITED, cmChangeThreeDeeDisplaySlider, con);

  con->gridTintLabel = naNewLabel("Grid Tint", 100);
  con->gridTintSlider = naNewSlider(100);
  naSetSliderRange(con->gridTintSlider, 0., 1., 0);
  naAddUIReaction(con->gridTintSlider, NA_UI_COMMAND_EDITED, cmChangeThreeDeeDisplaySlider, con);

  con->bodyAlphaLabel = naNewLabel("Body Tint", 100);
  con->bodyAlphaSlider = naNewSlider(100);
  naSetSliderRange(con->bodyAlphaSlider, 0., 1., 0);
  naAddUIReaction(con->bodyAlphaSlider, NA_UI_COMMAND_EDITED, cmChangeThreeDeeDisplaySlider, con);

  con->bodySolidLabel = naNewLabel("Solid", 100);
  con->bodySolidCheckBox = naNewCheckBox("", 30);
  naAddUIReaction(con->bodySolidCheckBox, NA_UI_COMMAND_PRESSED, cmPressThreeDeeDisplayButton, con);

  con->axisLabel = naNewLabel("Axis", 100);
  con->axisCheckBox = naNewCheckBox("", 30);
  naAddUIReaction(con->axisCheckBox, NA_UI_COMMAND_PRESSED, cmPressThreeDeeDisplayButton, con);

  con->spectrumLabel = naNewLabel("Spectrum", 100);
  con->spectrumCheckBox = naNewCheckBox("", 30);
  naAddUIReaction(con->spectrumCheckBox, NA_UI_COMMAND_PRESSED, cmPressThreeDeeDisplayButton, con);

  con->fovyLabel = naNewLabel("Fovy", 100);
  con->fovySlider = naNewSlider(100);
  naSetSliderRange(con->fovySlider, 0., 90., 0);
  naAddUIReaction(con->fovySlider, NA_UI_COMMAND_EDITED, cmChangeThreeDeeDisplaySlider, con);

  con->backgroundLabel = naNewLabel("Background", 100);
  con->backgroundSlider = naNewSlider(100);
  naSetSliderRange(con->backgroundSlider, 0., 1., 0);
  naAddUIReaction(con->backgroundSlider, NA_UI_COMMAND_EDITED, cmChangeThreeDeeDisplaySlider, con);

  // Add childs
  NASpace* content = naGetWindowContentSpace(con->window);
  naAddSpaceChild(content, con->display, naMakePos(0, 0));
  naAddSpaceChild(content, con->controlSpace, naMakePos(300, 0));

  NASize controlSpaceSize = naGetUIElementRect(con->controlSpace, NA_NULL, NA_FALSE).size;

  NAInt y = controlSpaceSize.height - 30;
  naAddSpaceChild(con->controlSpace, con->colorSpaceLabel, naMakePos(10, y));
  naAddSpaceChild(con->controlSpace, con->colorSpacePopupButton, naMakePos(115, y));
  y -= 25;
  naAddSpaceChild(con->controlSpace, con->coordSysLabel, naMakePos(10, y));
  naAddSpaceChild(con->controlSpace, con->coordSysPopupButton, naMakePos(115, y));
  y -= 25;
  naAddSpaceChild(con->controlSpace, con->stepsLabel, naMakePos(10, y));
  naAddSpaceChild(con->controlSpace, con->stepsSlider, naMakePos(115, y));
  y -= 50;

  naAddSpaceChild(con->controlSpace, con->rotationLabel, naMakePos(10, y));
  naAddSpaceChild(con->controlSpace, con->rotationButton, naMakePos(55, y));
  naAddSpaceChild(con->controlSpace, con->rotationSlider, naMakePos(115, y));
  y -= 50;

  naAddSpaceChild(con->controlSpace, con->pointsOpacityLabel, naMakePos(10, y));
  naAddSpaceChild(con->controlSpace, con->pointsOpacitySlider, naMakePos(115, y));
  y -= 25;
  naAddSpaceChild(con->controlSpace, con->gridAlphaLabel, naMakePos(10, y));
  naAddSpaceChild(con->controlSpace, con->gridAlphaSlider, naMakePos(115, y));
  y -= 25;
  naAddSpaceChild(con->controlSpace, con->gridTintLabel, naMakePos(10, y));
  naAddSpaceChild(con->controlSpace, con->gridTintSlider, naMakePos(115, y));
  y -= 25;
  naAddSpaceChild(con->controlSpace, con->bodyAlphaLabel, naMakePos(10, y));
  naAddSpaceChild(con->controlSpace, con->bodyAlphaSlider, naMakePos(115, y));
  y -= 25;
  naAddSpaceChild(con->controlSpace, con->bodySolidLabel, naMakePos(10, y));
  naAddSpaceChild(con->controlSpace, con->bodySolidCheckBox, naMakePos(115, y));
  y -= 50;
  
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
  


  // Set initial values
  float scaleFactor = cmGetUIScaleFactorForWindow(naGetUIElementNativePtr(con->window));

  con->colorSpace = CML_COLOR_RGB;
  con->coordSys = COORD_SYS_LAB;
  con->steps3D = 25;

  con->rotationStep = 0.;
 
  con->pointsOpacity = 0.;
  con->bodySolid = NA_TRUE;
  con->bodyAlpha = .2;
  con->gridAlpha = 1.;
  con->gridTint = .5;

  con->showSpectrum = NA_FALSE;
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
  naSetPopupButtonIndexSelected(con->colorSpacePopupButton, con->colorSpace);
  naSetPopupButtonIndexSelected(con->coordSysPopupButton, con->coordSys);
  naSetSliderValue(con->stepsSlider, con->steps3D);

  naSetSliderValue(con->rotationSlider, con->rotationStep);

  naSetSliderValue(con->pointsOpacitySlider, con->pointsOpacity);
  naSetSliderValue(con->gridAlphaSlider, con->gridAlpha);
  naSetSliderValue(con->gridTintSlider, con->gridTint);
  naSetSliderValue(con->bodyAlphaSlider, con->bodyAlpha);
  naSetSliderValue(con->bodyAlphaSlider, con->bodyAlpha);
  naSetCheckBoxState(con->bodySolidCheckBox, con->bodySolid);

  naSetCheckBoxState(con->spectrumCheckBox, con->showSpectrum);
  naSetCheckBoxState(con->axisCheckBox, con->showAxis);
  naSetSliderValue(con->backgroundSlider, con->backgroundGray);
  naSetSliderValue(con->fovySlider, con->fovy);

  naRefreshUIElement(con->display, 0.);
}
