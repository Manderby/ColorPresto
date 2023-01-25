
#include "NAApp.h"
#include "NAMath/NAVectorAlgebra.h"
#include "NAVisual/NA3DHelper.h"

#include "../CMColorMachineApplication.h"
#include "../mainC.h"
#include "../CMDesign.h"
#include "../CMTranslations.h"
#include "CMThreeDeeCoordinateController.h"
#include "CMThreeDeeOpacityController.h"
#include "CMThreeDeeOptionsController.h"
#include "CMThreeDeePerspectiveController.h"
#include "CMThreeDeeController.h"
#include "CMThreeDeeView.h"

#include <CML.h>

#define marginHMiddle (spaceMarginLeft3D + threeDeeLabelWidth + marginH)
#define fullControlWidth (marginHMiddle + threeDeeControlWidth + spaceMarginRight)

struct CMThreeDeeController{
  NAWindow* window;
  NAOpenGLSpace* display;
  NASpace* controlSpace;

  CMThreeDeeCoordinateController* coordinateController;
  CMThreeDeeOpacityController* opacityController;
  CMThreeDeeOptionsController* optionsController;
  CMThreeDeePerspectiveController* perspectiveController;
    
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

  NARect windowRect = naGetUIElementRect(con->window);
  NARect oldOpenGLRect = naGetUIElementRect(con->display);
  NARect oldControlRect = naGetUIElementRect(con->controlSpace);

  double controlHeight = oldControlRect.size.height;

  NARect openGLRect = naMakeRectSE(
    0,
    0,
    windowRect.size.width - fullControlWidth,
    windowRect.size.height);
  NARect controlRect = naMakeRectSE(
    windowRect.size.width - fullControlWidth,
    windowRect.size.height - controlHeight,
    fullControlWidth,
    controlHeight);
  naSetUIElementRect(con->controlSpace, controlRect);

  cmSetThreeDeePerspectiveControllerZoom(con->perspectiveController, cmGetThreeDeePerspectiveControllerZoom(con->perspectiveController) / (openGLRect.size.height / oldOpenGLRect.size.height));

  return NA_TRUE;
}



NABool cmUpdateThreeDeeDisplay(NAReaction reaction){
  CMThreeDeeController* con = (CMThreeDeeController*)reaction.controller;
  
  CMLColorMachine* cm = cmGetCurrentColorMachine();
  CMLColorMachine* sm = cmGetCurrentScreenMachine();
  
  CMLColorType coordSpace;
  int primeAxis;
  double scale[3];
  const NAUTF8Char* labels[3] = {0};
  CMLNormedConverter normedOutputConverter;
  CoordSysType coordSysType = cmGetThreeDeeCoordinateControllerCoordSysType(con->coordinateController);
  CMLColorType colorType = cmGetThreeDeeCoordinateControllerColorSpaceType(con->coordinateController);

  switch(coordSysType){
  case COORD_SYS_HSL:
    coordSpace = CML_COLOR_HSL;
    primeAxis = 2;
    naFillV3d(scale, 2., 2., 1.);
    labels[0] = "";
    labels[1] = cmTranslate(CMHSLColorChannelS);
    labels[2] = cmTranslate(CMHSLColorChannelL);
    normedOutputConverter = cmlGetNormedCartesianOutputConverter(CML_COLOR_HSL);
    break;
  case COORD_SYS_HSL_CARTESIAN:
    coordSpace = CML_COLOR_HSL;
    primeAxis = 2;
    naFillV3d(scale, 3.60, -1., 1.);
    labels[0] = cmTranslate(CMHSLColorChannelH);
    labels[1] = cmTranslate(CMHSLColorChannelS);
    labels[2] = cmTranslate(CMHSLColorChannelL);
    normedOutputConverter = cmlGetNormedOutputConverter(CML_COLOR_HSL);
    break;
  case COORD_SYS_HSV:
    coordSpace = CML_COLOR_HSV;
    primeAxis = 2;
    naFillV3d(scale, 2., 2., 1.);
    labels[0] = "";
    labels[1] = cmTranslate(CMHSVColorChannelS);
    labels[2] = cmTranslate(CMHSVColorChannelV);
    normedOutputConverter = cmlGetNormedCartesianOutputConverter(CML_COLOR_HSV);
    break;
  case COORD_SYS_HSV_CARTESIAN:
    coordSpace = CML_COLOR_HSV;
    primeAxis = 2;
    naFillV3d(scale, 3.60, -1., 1.);
    labels[0] = cmTranslate(CMHSVColorChannelH);
    labels[1] = cmTranslate(CMHSVColorChannelS);
    labels[2] = cmTranslate(CMHSVColorChannelV);
    normedOutputConverter = cmlGetNormedOutputConverter(CML_COLOR_HSV);
    break;
  case COORD_SYS_Lab:
    coordSpace = CML_COLOR_Lab;
    primeAxis = 0;
    naFillV3d(scale, 1., 2.56, 2.56);
    labels[0] = cmTranslate(CMLabColorChannelL);
    labels[1] = cmTranslate(CMLabColorChannela);
    labels[2] = cmTranslate(CMLabColorChannelb);
    normedOutputConverter = cmlGetNormedOutputConverter(CML_COLOR_Lab);
    break;
  case COORD_SYS_Lch_CARTESIAN:
    coordSpace = CML_COLOR_Lch;
    primeAxis = 0;
    naFillV3d(scale, 1., 1., 3.60);
    labels[0] = cmTranslate(CMLabColorChannelL);
    labels[1] = cmTranslate(CMLchColorChannelc);
    labels[2] = cmTranslate(CMLchColorChannelh);
    normedOutputConverter = cmlGetNormedOutputConverter(CML_COLOR_Lch);
    break;
  case COORD_SYS_Luv:
    coordSpace = CML_COLOR_Luv;
    primeAxis = 0;
    naFillV3d(scale, 1., 1., 1.);
    labels[0] = cmTranslate(CMLuvColorChannelL);
    labels[1] = cmTranslate(CMLuvColorChannelu);
    labels[2] = cmTranslate(CMLuvColorChannelv);
    normedOutputConverter = cmlGetNormedOutputConverter(CML_COLOR_Luv);
    break;
  case COORD_SYS_RGB:
    coordSpace = CML_COLOR_RGB;
    primeAxis = 1;
    naFillV3d(scale, 1., 1., 1.);
    labels[0] = cmTranslate(CMRGBColorChannelR);
    labels[1] = cmTranslate(CMRGBColorChannelG);
    labels[2] = cmTranslate(CMRGBColorChannelB);
    normedOutputConverter = cmlGetNormedOutputConverter(CML_COLOR_RGB);
    break;
  case COORD_SYS_UVW:
    coordSpace = CML_COLOR_UVW;
    primeAxis = 2;
    naFillV3d(scale, 2., 1., 1.);
    labels[0] = cmTranslate(CMUVWColorChannelU);
    labels[1] = cmTranslate(CMUVWColorChannelV);
    labels[2] = cmTranslate(CMUVWColorChannelW);
    normedOutputConverter = cmlGetNormedOutputConverter(CML_COLOR_UVW);
    break;
  case COORD_SYS_XYZ:
    coordSpace = CML_COLOR_XYZ;
    primeAxis = 1;
    naFillV3d(scale, 1., 1., 1.);
    labels[0] = cmTranslate(CMXYZColorChannelX);
    labels[1] = cmTranslate(CMXYZColorChannelY);
    labels[2] = cmTranslate(CMXYZColorChannelZ);
    normedOutputConverter = cmlGetNormedOutputConverter(CML_COLOR_XYZ);
    break;
  case COORD_SYS_Ycbcr:
    coordSpace = CML_COLOR_YCbCr;
    primeAxis = 0;
    naFillV3d(scale, 1., 1., 1.);
    labels[0] = cmTranslate(CMYCbCrColorChannelY);
    labels[1] = cmTranslate(CMYCbCrColorChannelCb);
    labels[2] = cmTranslate(CMYCbCrColorChannelCr);
    normedOutputConverter = cmlGetNormedOutputConverter(CML_COLOR_YCbCr);
    break;
  case COORD_SYS_Ycd:
    coordSpace = CML_COLOR_Ycd;
    primeAxis = 0;
    naFillV3d(scale, 1., 1., 1.);
    labels[0] = cmTranslate(CMYcdColorChannelY);
    labels[1] = cmTranslate(CMYcdColorChannelc);
    labels[2] = cmTranslate(CMYcdColorChanneld);
    normedOutputConverter = cmlGetNormedOutputConverter(CML_COLOR_Ycd);
    break;
  case COORD_SYS_Yupvp:
    coordSpace = CML_COLOR_Yupvp;
    primeAxis = 0;
    naFillV3d(scale, 1., (2.f / 3.f), (2.f / 3.f));
    labels[0] = cmTranslate(CMYuvColorChannelY);
    labels[1] = cmTranslate(CMYuvColorChannelup);
    labels[2] = cmTranslate(CMYuvColorChannelvp);
    normedOutputConverter = cmlGetNormedOutputConverter(CML_COLOR_Yupvp);
    break;
  case COORD_SYS_Yuv:
    coordSpace = CML_COLOR_Yuv;
    primeAxis = 0;
    naFillV3d(scale, 1., (2.f / 3.f), (4.f / 9.f));
    labels[0] = cmTranslate(CMYuvColorChannelY);
    labels[1] = cmTranslate(CMYuvColorChannelu);
    labels[2] = cmTranslate(CMYuvColorChannelv);
    normedOutputConverter = cmlGetNormedOutputConverter(CML_COLOR_Yuv);
    break;
  case COORD_SYS_Yxy:
    coordSpace = CML_COLOR_Yxy;
    primeAxis = 0;
    naFillV3d(scale, 1., 1., 1.);
    labels[0] = cmTranslate(CMYxyColorChannelY);
    labels[1] = cmTranslate(CMYxyColorChannelx);
    labels[2] = cmTranslate(CMYxyColorChannely);
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

  viewSize = naGetUIElementRect(con->display).size;
  cmlGetMinBounds(min, coordSpace);
  cmlGetMaxBounds(max, coordSpace);

  CMLVec3 backgroundRGB;
  CMLVec3 axisRGB;
  float axisGray = (float)cmGetThreeDeeOptionsControllerAxisGray(con->optionsController);
  float backgroundGray = (float)cmGetThreeDeeOptionsControllerBackgroundGray(con->optionsController);
  NABool showAxis = cmGetThreeDeeOptionsControllerShowAxis(con->optionsController);
  NABool showSpectrum = cmGetThreeDeeOptionsControllerShowSpectrum(con->optionsController);
  double fovy = cmGetThreeDeeOptionsControllerFovy(con->optionsController);
  double zoom = cmGetThreeDeePerspectiveControllerZoom(con->perspectiveController);
  double curZoom;
  
  cmlSet3(backgroundRGB, backgroundGray, backgroundGray, backgroundGray);
  cmlSet3(axisRGB, axisGray, axisGray, axisGray);

  if(fovy == 0){
    curZoom = zoom;
  }else{
    curZoom = (viewSize.width / initial3DDisplayWidth) * zoom / (2. * (viewSize.width / viewSize.height) * naTan(.5 * naDegToRad(fovy)));
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
    cmGetThreeDeePerspectiveControllerRotationAnglePol(con->perspectiveController),
    cmGetThreeDeePerspectiveControllerRotationAngleEqu(con->perspectiveController));
  NAInt steps3D = cmGetThreeDeeCoordinateControllerSteps3D(con->coordinateController);

  if(1){
    cmDrawThreeDeeSurfaces(
      cm,
      sm,
      backgroundRGB,
      axisRGB,
      cmGetThreeDeeOpacityControllerBodySolid(con->opacityController),
      cmGetThreeDeeOpacityControllerBodyAlpha(con->opacityController),
      cmGetThreeDeeOpacityControllerGridAlpha(con->opacityController),
      cmGetThreeDeeOpacityControllerGridTint(con->opacityController),
      colorType,
      steps3D,
      normedInputConverter,
      coordConverter,
      normedOutputConverter,
      hueIndex);
  }
  
  const NABool isGrayColorSpace = colorType == CML_COLOR_Gray;
  float pointsOpacity = cmGetThreeDeeOpacityControllerPointsOpacity(con->opacityController);
  if(pointsOpacity > 0.f || isGrayColorSpace){
    cmDrawThreeDeePointCloud(
      cm,
      sm,
      isGrayColorSpace ? 1.f : pointsOpacity,
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
  
  con->coordinateController = cmAllocThreeDeeCoordinateController(con);
  con->perspectiveController = cmAllocThreeDeePerspectiveController(con);
  con->opacityController = cmAllocThreeDeeOpacityController(con);
  con->optionsController = cmAllocThreeDeeOptionsController(con);

  // The window
  con->window = naNewWindow(cmTranslate(CM3DView), naMakeRectS(40, 30, 1, 1), NA_WINDOW_RESIZEABLE, 0);
  naAddUIReaction(con->window, NA_UI_COMMAND_RESHAPE, cmReshapeThreeDeeWindow, con);

  // The 3D space
  con->display = naNewOpenGLSpace(naMakeSize(initial3DDisplayWidth, initial3DDisplayWidth), cmInitThreeDeeOpenGL, con);
  naAddUIReaction(con->display, NA_UI_COMMAND_REDRAW, cmUpdateThreeDeeDisplay, con);
  naAddUIReaction(con->display, NA_UI_COMMAND_MOUSE_MOVED, cmMoveRotationMouse, con->perspectiveController);
  naAddUIReaction(con->display, NA_UI_COMMAND_SCROLLED, cmScrollRotation, con->perspectiveController);
  
  // The control space
  con->controlSpace = naNewSpace(naMakeSize(fullControlWidth, 1));
    
  // layout
  cmBeginUILayout(con->controlSpace, naMakeBezel4Zero());
  cmAddUIRow(cmGetThreeDeeCoordinateControllerUIElement(con->coordinateController), 0);
  cmAddUIRow(cmGetThreeDeePerspectiveControllerUIElement(con->perspectiveController), 0);
  cmAddUIRow(cmGetThreeDeeOpacityControllerUIElement(con->opacityController), 0);
  cmAddUIRow(cmGetThreeDeeOptionsControllerUIElement(con->optionsController), 0);
  cmEndUILayout();

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
  cmUpdateThreeDeeCoordinateController(con->coordinateController);
  cmUpdateThreeDeePerspectiveController(con->perspectiveController);
  cmUpdateThreeDeeOpacityController(con->opacityController);
  cmUpdateThreeDeeOptionsController(con->optionsController);

  naRefreshUIElement(con->display, 0.);
}
