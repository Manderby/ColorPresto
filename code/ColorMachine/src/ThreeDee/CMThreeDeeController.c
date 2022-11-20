
#include "NAApp.h"
#include "NAVectorAlgebra.h"
#include "NA3DHelper.h"

#include "CMCoordinateController.h"
#include "CMOpacityController.h"
#include "CMOptionsController.h"
#include "CMRotationController.h"
#include "CMTranslations.h"

#include "mainC.h"
#include "CMDesign.h"
#include "CMThreeDeeController.h"
#include "CMThreeDeeView.h"
#include <CML.h>

static const double marginHMiddle = spaceMarginLeft3D + threeDeeLabelWidth + marginH;
static const double fullControlWidth = marginHMiddle + threeDeeControlWidth + spaceMarginRight;

struct CMThreeDeeController{
  NAWindow* window;
  NAOpenGLSpace* display;
  NASpace* controlSpace;

  CMCoordinateController* coordinateController;
  CMOpacityController* opacityController;
  CMOptionsController* optionsController;
  CMRotationController* rotationController;
    
  NAInt fontId;
  
};



void cmInitThreeDeeOpenGL(void* data){
  CMThreeDeeController* con = (CMThreeDeeController*)data;
  con->fontId = naStartupPixelFont();
  cmInitThreeDeeDisplay(con->display);
}


void cmRefreshThreeDeeDisplay(CMThreeDeeController* con){
  naRefreshUIElement(con->display, 0.);
}

NABool cmReshapeThreeDeeWindow(NAReaction reaction){
  CMThreeDeeController* con = (CMThreeDeeController*)reaction.controller;

  NARect windowRect = naGetUIElementRect(con->window, NA_NULL, NA_FALSE);
  NARect oldOpenGLRect = naGetUIElementRect(con->display, NA_NULL, NA_FALSE);
  NARect oldControlRect = naGetUIElementRect(con->controlSpace, NA_NULL, NA_FALSE);

  double controlHeight = oldControlRect.size.height;

  NARect openGLRect = naMakeRectS(
    0,
    0,
    windowRect.size.width - fullControlWidth,
    windowRect.size.height);
  NARect controlRect = naMakeRectS(
    windowRect.size.width - fullControlWidth,
    windowRect.size.height - controlHeight,
    fullControlWidth,
    controlHeight);
  naSetOpenGLSpaceInnerRect(con->display, openGLRect);
  naSetSpaceRect(con->controlSpace, controlRect);

  cmSetRotationZoom(con->rotationController, cmGetRotationZoom(con->rotationController) / (openGLRect.size.height / oldOpenGLRect.size.height));

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
  CMLNormedConverter normedOutputConverter;
  CoordSysType coordSysType = cmGetCoordinateCoordSysType(con->coordinateController);
  CMLColorType colorType = cmGetCoordinateColorSpaceType(con->coordinateController);

  switch(coordSysType){
  case COORD_SYS_HSL:
    coordSpace = CML_COLOR_HSL;
    primeAxis = 2;
    naFillV3d(scale, 2., 2., 1.);
    labels[0] = "";
    labels[1] = "S";
    labels[2] = "L";
    normedOutputConverter = cmlGetNormedCartesianOutputConverter(CML_COLOR_HSL);
    break;
  case COORD_SYS_HSL_CARTESIAN:
    coordSpace = CML_COLOR_HSL;
    primeAxis = 2;
    naFillV3d(scale, 3.60, -1., 1.);
    labels[0] = "H";
    labels[1] = "S";
    labels[2] = "L";
    normedOutputConverter = cmlGetNormedOutputConverter(CML_COLOR_HSL);
    break;
  case COORD_SYS_HSV:
    coordSpace = CML_COLOR_HSV;
    primeAxis = 2;
    naFillV3d(scale, 2., 2., 1.);
    labels[0] = "";
    labels[1] = "S";
    labels[2] = "V";
    normedOutputConverter = cmlGetNormedCartesianOutputConverter(CML_COLOR_HSV);
    break;
  case COORD_SYS_HSV_CARTESIAN:
    coordSpace = CML_COLOR_HSV;
    primeAxis = 2;
    naFillV3d(scale, 3.60, -1., 1.);
    labels[0] = "H";
    labels[1] = "S";
    labels[2] = "V";
    normedOutputConverter = cmlGetNormedOutputConverter(CML_COLOR_HSV);
    break;
  case COORD_SYS_Lab:
    coordSpace = CML_COLOR_Lab;
    primeAxis = 0;
    naFillV3d(scale, 1., 2.56, 2.56);
    labels[0] = "L";
    labels[1] = "a";
    labels[2] = "b";
    normedOutputConverter = cmlGetNormedOutputConverter(CML_COLOR_Lab);
    break;
  case COORD_SYS_Lch_CARTESIAN:
    coordSpace = CML_COLOR_Lch;
    primeAxis = 0;
    naFillV3d(scale, 1., 1., 3.60);
    labels[0] = "L";
    labels[1] = "c";
    labels[2] = "h";
    normedOutputConverter = cmlGetNormedOutputConverter(CML_COLOR_Lch);
    break;
  case COORD_SYS_Luv:
    coordSpace = CML_COLOR_Luv;
    primeAxis = 0;
    naFillV3d(scale, 1., 1., 1.);
    labels[0] = "L";
    labels[1] = "u";
    labels[2] = "v";
    normedOutputConverter = cmlGetNormedOutputConverter(CML_COLOR_Luv);
    break;
  case COORD_SYS_RGB:
    coordSpace = CML_COLOR_RGB;
    primeAxis = 1;
    naFillV3d(scale, 1., 1., 1.);
    labels[0] = "R";
    labels[1] = "G";
    labels[2] = "B";
    normedOutputConverter = cmlGetNormedOutputConverter(CML_COLOR_RGB);
    break;
  case COORD_SYS_UVW:
    coordSpace = CML_COLOR_UVW;
    primeAxis = 2;
    naFillV3d(scale, 2., 1., 1.);
    labels[0] = "U*";
    labels[1] = "V*";
    labels[2] = "W*";
    normedOutputConverter = cmlGetNormedOutputConverter(CML_COLOR_UVW);
    break;
  case COORD_SYS_XYZ:
    coordSpace = CML_COLOR_XYZ;
    primeAxis = 1;
    naFillV3d(scale, 1., 1., 1.);
    labels[0] = "X";
    labels[1] = "Y";
    labels[2] = "Z";
    normedOutputConverter = cmlGetNormedOutputConverter(CML_COLOR_XYZ);
    break;
  case COORD_SYS_Ycbcr:
    coordSpace = CML_COLOR_YCbCr;
    primeAxis = 0;
    naFillV3d(scale, 1., 1., 1.);
    labels[0] = "Y";
    labels[1] = "Cb";
    labels[2] = "Cr";
    normedOutputConverter = cmlGetNormedOutputConverter(CML_COLOR_YCbCr);
    break;
  case COORD_SYS_Ycd:
    coordSpace = CML_COLOR_Ycd;
    primeAxis = 0;
    naFillV3d(scale, 1., 1., 1.);
    labels[0] = "Y";
    labels[1] = "c";
    labels[2] = "d";
    normedOutputConverter = cmlGetNormedOutputConverter(CML_COLOR_Ycd);
    break;
  case COORD_SYS_Yupvp:
    coordSpace = CML_COLOR_Yupvp;
    primeAxis = 0;
    naFillV3d(scale, 1., (2.f / 3.f), (2.f / 3.f));
    labels[0] = "Y";
    labels[1] = "u'";
    labels[2] = "v'";
    normedOutputConverter = cmlGetNormedOutputConverter(CML_COLOR_Yupvp);
    break;
  case COORD_SYS_Yuv:
    coordSpace = CML_COLOR_Yuv;
    primeAxis = 0;
    naFillV3d(scale, 1., (2.f / 3.f), (4.f / 9.f));
    labels[0] = "Y";
    labels[1] = "u";
    labels[2] = "v";
    normedOutputConverter = cmlGetNormedOutputConverter(CML_COLOR_Yuv);
    break;
  case COORD_SYS_Yxy:
    coordSpace = CML_COLOR_Yxy;
    primeAxis = 0;
    naFillV3d(scale, 1., 1., 1.);
    labels[0] = "Y";
    labels[1] = "x";
    labels[2] = "y";
    normedOutputConverter = cmlGetNormedOutputConverter(CML_COLOR_Yxy);
    break;
  default:
    return NA_FALSE;
  }



  CMLNormedConverter normedInputConverter = cmlGetNormedInputConverter(colorType);
  CMLColorConverter coordConverter = cmlGetColorConverter(coordSpace, colorType);
  float min[3];
  float max[3];
  NASize viewSize;

  viewSize = naGetUIElementRect(con->display, NA_NULL, NA_FALSE).size;
  cmlGetMinBounds(min, coordSpace);
  cmlGetMaxBounds(max, coordSpace);

  CMLVec3 backgroundRGB;
  CMLVec3 axisRGB;
  double axisGray = cmGetOptionsAxisGray(con->optionsController);
  double backgroundGray = cmGetOptionsBackgroundGray(con->optionsController);
  NABool showAxis = cmGetOptionsShowAxis(con->optionsController);
  NABool showSpectrum = cmGetOptionsShowSpectrum(con->optionsController);
  double fovy = cmGetOptionsFovy(con->optionsController);
  double zoom = cmGetRotationZoom(con->rotationController);
  double curZoom;
  
  cmlSet3(backgroundRGB, backgroundGray, backgroundGray, backgroundGray);
  cmlSet3(axisRGB, axisGray, axisGray, axisGray);

  if(fovy == 0){
    curZoom = zoom;
  }else{
    curZoom = (viewSize.width / initial3DDisplayWidth) * zoom / (2. * (viewSize.width / viewSize.height) * tan(.5 * naDegToRad(fovy)));
  }

  NAInt hueIndex = -1;
  if((coordSysType == COORD_SYS_HSV_CARTESIAN) || (coordSysType == COORD_SYS_HSL_CARTESIAN)){
    hueIndex = 0;
  }else if(coordSysType == COORD_SYS_Lch_CARTESIAN){
    hueIndex = 2;
  }

  cmBeginThreeDeeDrawing(backgroundRGB);

  cmSetupThreeDeeProjection(
    viewSize,
    fovy,
    curZoom);
  cmSetupThreeDeeModelView(
    primeAxis,
    scale,
    curZoom,
    cmGetRotationViewPol(con->rotationController),
    cmGetRotationViewEqu(con->rotationController));
  NAInt steps3D = cmGetCoordinateSteps3D(con->coordinateController);

  if(1){
    cmDrawThreeDeeSurfaces(
      cm,
      sm,
      backgroundRGB,
      axisRGB,
      cmGetOpacityBodySolid(con->opacityController),
      cmGetOpacityBodyAlpha(con->opacityController),
      cmGetOpacityGridAlpha(con->opacityController),
      cmGetOpacityGridTint(con->opacityController),
      colorType,
      steps3D,
      normedInputConverter,
      coordConverter,
      normedOutputConverter,
      hueIndex);
  }
  
  const NABool isGrayColorSpace = colorType == CML_COLOR_Gray;
  double pointsOpacity = cmGetOpacityPointsOpacity(con->opacityController);
  if(pointsOpacity > 0.f || isGrayColorSpace){
    cmDrawThreeDeePointCloud(
      cm,
      sm,
      isGrayColorSpace ? 1. : pointsOpacity,
      colorType,
      steps3D,
      normedInputConverter,
      coordConverter,
      normedOutputConverter,
      curZoom);
  }

  if(showSpectrum){
    cmDrawThreeDeeSpectrum(
      cm,
      normedOutputConverter,
      coordSpace,
      hueIndex);
  }
  
  if(showAxis){
    cmDrawThreeDeeAxis(
      normedOutputConverter,
      min,
      max,
      labels,
      axisRGB,
      con->fontId);
  }

  cmEndThreeDeeDrawing(con->display);
    
  return NA_TRUE;
}



CMThreeDeeController* cmAllocThreeDeeController(void){
  CMThreeDeeController* con = naAlloc(CMThreeDeeController);
  naZeron(con, sizeof(CMThreeDeeController));
  
  con->coordinateController = cmAllocCoordinateController(con);
  con->rotationController = cmAllocRotationController(con);
  con->opacityController = cmAllocOpacityController(con);
  con->optionsController = cmAllocOptionsController(con);

  // The window
  con->window = naNewWindow(cmTranslate(CM3DView), naMakeRectS(40, 30, 1, 1), NA_WINDOW_RESIZEABLE, 0);
  naAddUIReaction(con->window, NA_UI_COMMAND_RESHAPE, cmReshapeThreeDeeWindow, con);

  // The 3D space
  con->display = naNewOpenGLSpace(naMakeSize(initial3DDisplayWidth, initial3DDisplayWidth), cmInitThreeDeeOpenGL, con);
  naAddUIReaction(con->display, NA_UI_COMMAND_REDRAW, cmUpdateThreeDeeDisplay, con);
  naAddUIReaction(con->display, NA_UI_COMMAND_MOUSE_MOVED, cmMoveRotationMouse, con->rotationController);
  naAddUIReaction(con->display, NA_UI_COMMAND_SCROLLED, cmScrollRotation, con->rotationController);
  
  // The control space
  con->controlSpace = naNewSpace(naMakeSize(fullControlWidth, 1));
    
  // layout

  cmBeginUILayout(con->controlSpace, naMakeBezel4Zero());
  cmAddUIRow(cmGetCoordinateUIElement(con->coordinateController), 0);
  cmAddUIRow(cmGetRotationUIElement(con->rotationController), 0);
  cmAddUIRow(cmGetOpacityUIElement(con->opacityController), 0);
  cmAddUIRow(cmGetOptionsUIElement(con->optionsController), 0);
  cmEndUILayout();

  // Add window childs
  NASpace* content = naGetWindowContentSpace(con->window);

  cmBeginUILayout(content, naMakeBezel4Zero());
  cmAddUIRow(con->display, 0);
  cmAddUICol(con->controlSpace, 0);
  cmEndUILayout();
  
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
  cmUpdateCoordinateController(con->coordinateController);
  cmUpdateRotationController(con->rotationController);
  cmUpdateOpacityController(con->opacityController);
  cmUpdateOptionsController(con->optionsController);

  naRefreshUIElement(con->display, 0.);
}
