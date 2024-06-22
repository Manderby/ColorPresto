
#include "NAApp/NAApp.h"
#include "NAMath/NAVectorAlgebra.h"
#include "NAVisual/NA3DHelper.h"

#include "../CPColorPrestoApplication.h"
#include "../mainC.h"
#include "../CPDesign.h"
#include "../CPTranslations.h"
#include "CPThreeDeeCoordinateController.h"
#include "CPThreeDeeOpacityController.h"
#include "CPThreeDeeOptionsController.h"
#include "CPThreeDeePerspectiveController.h"
#include "CPThreeDeeController.h"
#include "CPThreeDeeView.h"

#include "CML.h"



#define marginHMiddle (spaceMarginLeft3D + threeDeeLabelWidth + marginH)
#define fullControlWidth (marginHMiddle + threeDeeControlWidth + spaceMarginRight)

struct CPThreeDeeController{
  NAWindow* window;
  NAOpenGLSpace* display;
  NASpace* controlSpace;

  CPThreeDeeCoordinateController* coordinateController;
  CPThreeDeeOpacityController* opacityController;
  CPThreeDeeOptionsController* optionsController;
  CPThreeDeePerspectiveController* perspectiveController;
    
  NAInt fontId;
  
};



void cp_InitThreeDeeOpenGL(void* data){
  CPThreeDeeController* con = (CPThreeDeeController*)data;
  con->fontId = naStartupPixelFont();
  cpInitThreeDeeDisplay(con->display);
}


void cpRefreshThreeDeeDisplay(CPThreeDeeController* con){
  naRefreshUIElement(con->display, 0.);
}

void cp_ReshapeThreeDeeWindow(NAReaction reaction){
  CPThreeDeeController* con = (CPThreeDeeController*)reaction.controller;

  NARect windowRect = naGetUIElementRect(con->window);
  NARect oldOpenGLRect = naGetUIElementRect(con->display);
  NARect oldControlRect = naGetUIElementRect(con->controlSpace);

  double controlHeight = oldControlRect.size.height;

  NARect openGLRect = naMakeRectSE(
    0,
    0,
    windowRect.size.width - fullControlWidth,
    windowRect.size.height);
  naSetUIElementRect(con->display, openGLRect);
  NARect controlRect = naMakeRectSE(
    windowRect.size.width - fullControlWidth,
    windowRect.size.height - controlHeight,
    fullControlWidth,
    controlHeight);
  naSetUIElementRect(con->controlSpace, controlRect);

  cpSetThreeDeePerspectiveControllerZoom(con->perspectiveController, cpGetThreeDeePerspectiveControllerZoom(con->perspectiveController) / (openGLRect.size.height / oldOpenGLRect.size.height));
}



void cpUpdateThreeDeeDisplay(NAReaction reaction){
  CPThreeDeeController* con = (CPThreeDeeController*)reaction.controller;
  
  CMLColorMachine* cm = cpGetCurrentColorMachine();
  CMLColorMachine* sm = cpGetCurrentScreenMachine();
  
  CMLColorType coordSpace;
  int primeAxis;
  double scale[3];
  const NAUTF8Char* labels[3] = {0};
  CMLNormedConverter normedOutputConverter;
  CoordSysType coordSysType = cpGetThreeDeeCoordinateControllerCoordSysType(con->coordinateController);
  CMLColorType colorType = cpGetThreeDeeCoordinateControllerColorSpaceType(con->coordinateController);

  switch(coordSysType){
  case COORD_SYS_HSL:
    coordSpace = CML_COLOR_HSL;
    primeAxis = 2;
    naFillV3d(scale, 2., 2., 1.);
    labels[0] = "";
    labels[1] = cpTranslate(CPHSLColorChannelS);
    labels[2] = cpTranslate(CPHSLColorChannelL);
    normedOutputConverter = cmlGetNormedCartesianOutputConverter(CML_COLOR_HSL);
    break;
  case COORD_SYS_HSL_CARTESIAN:
    coordSpace = CML_COLOR_HSL;
    primeAxis = 2;
    naFillV3d(scale, 3.60, -1., 1.);
    labels[0] = cpTranslate(CPHSLColorChannelH);
    labels[1] = cpTranslate(CPHSLColorChannelS);
    labels[2] = cpTranslate(CPHSLColorChannelL);
    normedOutputConverter = cmlGetNormedOutputConverter(CML_COLOR_HSL);
    break;
  case COORD_SYS_HSV:
    coordSpace = CML_COLOR_HSV;
    primeAxis = 2;
    naFillV3d(scale, 2., 2., 1.);
    labels[0] = "";
    labels[1] = cpTranslate(CPHSVColorChannelS);
    labels[2] = cpTranslate(CPHSVColorChannelV);
    normedOutputConverter = cmlGetNormedCartesianOutputConverter(CML_COLOR_HSV);
    break;
  case COORD_SYS_HSV_CARTESIAN:
    coordSpace = CML_COLOR_HSV;
    primeAxis = 2;
    naFillV3d(scale, 3.60, -1., 1.);
    labels[0] = cpTranslate(CPHSVColorChannelH);
    labels[1] = cpTranslate(CPHSVColorChannelS);
    labels[2] = cpTranslate(CPHSVColorChannelV);
    normedOutputConverter = cmlGetNormedOutputConverter(CML_COLOR_HSV);
    break;
  case COORD_SYS_Lab:
    coordSpace = CML_COLOR_Lab;
    primeAxis = 0;
    naFillV3d(scale, 1., 2.56, 2.56);
    labels[0] = cpTranslate(CPLabColorChannelL);
    labels[1] = cpTranslate(CPLabColorChannela);
    labels[2] = cpTranslate(CPLabColorChannelb);
    normedOutputConverter = cmlGetNormedOutputConverter(CML_COLOR_Lab);
    break;
  case COORD_SYS_Lch_CARTESIAN:
    coordSpace = CML_COLOR_Lch;
    primeAxis = 0;
    naFillV3d(scale, 1., 1., 3.60);
    labels[0] = cpTranslate(CPLabColorChannelL);
    labels[1] = cpTranslate(CPLchColorChannelc);
    labels[2] = cpTranslate(CPLchColorChannelh);
    normedOutputConverter = cmlGetNormedOutputConverter(CML_COLOR_Lch);
    break;
  case COORD_SYS_Luv:
    coordSpace = CML_COLOR_Luv;
    primeAxis = 0;
    naFillV3d(scale, 1., 1., 1.);
    labels[0] = cpTranslate(CPLuvColorChannelL);
    labels[1] = cpTranslate(CPLuvColorChannelu);
    labels[2] = cpTranslate(CPLuvColorChannelv);
    normedOutputConverter = cmlGetNormedOutputConverter(CML_COLOR_Luv);
    break;
  case COORD_SYS_RGB:
    coordSpace = CML_COLOR_RGB;
    primeAxis = 1;
    naFillV3d(scale, 1., 1., 1.);
    labels[0] = cpTranslate(CPRGBColorChannelR);
    labels[1] = cpTranslate(CPRGBColorChannelG);
    labels[2] = cpTranslate(CPRGBColorChannelB);
    normedOutputConverter = cmlGetNormedOutputConverter(CML_COLOR_RGB);
    break;
  case COORD_SYS_UVW:
    coordSpace = CML_COLOR_UVW;
    primeAxis = 2;
    naFillV3d(scale, 2., 1., 1.);
    labels[0] = cpTranslate(CPUVWColorChannelU);
    labels[1] = cpTranslate(CPUVWColorChannelV);
    labels[2] = cpTranslate(CPUVWColorChannelW);
    normedOutputConverter = cmlGetNormedOutputConverter(CML_COLOR_UVW);
    break;
  case COORD_SYS_XYZ:
    coordSpace = CML_COLOR_XYZ;
    primeAxis = 1;
    naFillV3d(scale, 1., 1., 1.);
    labels[0] = cpTranslate(CPXYZColorChannelX);
    labels[1] = cpTranslate(CPXYZColorChannelY);
    labels[2] = cpTranslate(CPXYZColorChannelZ);
    normedOutputConverter = cmlGetNormedOutputConverter(CML_COLOR_XYZ);
    break;
  case COORD_SYS_Ycbcr:
    coordSpace = CML_COLOR_YCbCr;
    primeAxis = 0;
    naFillV3d(scale, 1., 1., 1.);
    labels[0] = cpTranslate(CPYCbCrColorChannelY);
    labels[1] = cpTranslate(CPYCbCrColorChannelCb);
    labels[2] = cpTranslate(CPYCbCrColorChannelCr);
    normedOutputConverter = cmlGetNormedOutputConverter(CML_COLOR_YCbCr);
    break;
  case COORD_SYS_Ycd:
    coordSpace = CML_COLOR_Ycd;
    primeAxis = 0;
    naFillV3d(scale, 1., 1., 1.);
    labels[0] = cpTranslate(CPYcdColorChannelY);
    labels[1] = cpTranslate(CPYcdColorChannelc);
    labels[2] = cpTranslate(CPYcdColorChanneld);
    normedOutputConverter = cmlGetNormedOutputConverter(CML_COLOR_Ycd);
    break;
  case COORD_SYS_Yupvp:
    coordSpace = CML_COLOR_Yupvp;
    primeAxis = 0;
    naFillV3d(scale, 1., (2.f / 3.f), (2.f / 3.f));
    labels[0] = cpTranslate(CPYuvColorChannelY);
    labels[1] = cpTranslate(CPYuvColorChannelup);
    labels[2] = cpTranslate(CPYuvColorChannelvp);
    normedOutputConverter = cmlGetNormedOutputConverter(CML_COLOR_Yupvp);
    break;
  case COORD_SYS_Yuv:
    coordSpace = CML_COLOR_Yuv;
    primeAxis = 0;
    naFillV3d(scale, 1., (2.f / 3.f), (4.f / 9.f));
    labels[0] = cpTranslate(CPYuvColorChannelY);
    labels[1] = cpTranslate(CPYuvColorChannelu);
    labels[2] = cpTranslate(CPYuvColorChannelv);
    normedOutputConverter = cmlGetNormedOutputConverter(CML_COLOR_Yuv);
    break;
  case COORD_SYS_Yxy:
    coordSpace = CML_COLOR_Yxy;
    primeAxis = 0;
    naFillV3d(scale, 1., 1., 1.);
    labels[0] = cpTranslate(CPYxyColorChannelY);
    labels[1] = cpTranslate(CPYxyColorChannelx);
    labels[2] = cpTranslate(CPYxyColorChannely);
    normedOutputConverter = cmlGetNormedOutputConverter(CML_COLOR_Yxy);
    break;
  default:
    return;
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
  float axisGray = (float)cpGetThreeDeeOptionsControllerAxisGray(con->optionsController);
  float backgroundGray = (float)cpGetThreeDeeOptionsControllerBackgroundGray(con->optionsController);
  NABool showAxis = cpGetThreeDeeOptionsControllerShowAxis(con->optionsController);
  NABool showSpectrum = cpGetThreeDeeOptionsControllerShowSpectrum(con->optionsController);
  double fovy = cpGetThreeDeeOptionsControllerFovy(con->optionsController);
  double zoom = cpGetThreeDeePerspectiveControllerZoom(con->perspectiveController);
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

  cpBeginThreeDeeDrawing(backgroundRGB);

  cpSetupThreeDeeProjection(
    con->display,
    viewSize,
    fovy,
    curZoom);
  cpSetupThreeDeeModelView(
    primeAxis,
    scale,
    curZoom,
    cpGetThreeDeePerspectiveControllerRotationAnglePol(con->perspectiveController),
    cpGetThreeDeePerspectiveControllerRotationAngleEqu(con->perspectiveController));
  NAInt steps3D = cpGetThreeDeeCoordinateControllerSteps3D(con->coordinateController);

  if(1){
    cpDrawThreeDeeSurfaces(
      cm,
      sm,
      backgroundRGB,
      axisRGB,
      cpGetThreeDeeOpacityControllerBodySolid(con->opacityController),
      cpGetThreeDeeOpacityControllerBodyAlpha(con->opacityController),
      cpGetThreeDeeOpacityControllerGridAlpha(con->opacityController),
      cpGetThreeDeeOpacityControllerGridTint(con->opacityController),
      colorType,
      steps3D,
      normedInputConverter,
      coordConverter,
      normedOutputConverter,
      hueIndex);
  }
  
  const NABool isGrayColorSpace = colorType == CML_COLOR_Gray;
  float pointsOpacity = cpGetThreeDeeOpacityControllerPointsOpacity(con->opacityController);
  if(pointsOpacity > 0.f || isGrayColorSpace){
    cpDrawThreeDeePointCloud(
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
    cpDrawThreeDeeSpectrum(
      cm,
      normedOutputConverter,
      coordSpace,
      hueIndex);
  }
  
  if(showAxis){
    cpDrawThreeDeeAxis(
      normedOutputConverter,
      min,
      max,
      labels,
      axisRGB,
      con->fontId);
  }

  cpEndThreeDeeDrawing(con->display);
}



CPThreeDeeController* cpAllocThreeDeeController(void){
  CPThreeDeeController* con = naAlloc(CPThreeDeeController);
  
  con->coordinateController = cpAllocThreeDeeCoordinateController(con);
  con->perspectiveController = cpAllocThreeDeePerspectiveController(con);
  con->opacityController = cpAllocThreeDeeOpacityController(con);
  con->optionsController = cpAllocThreeDeeOptionsController(con);

  // The window
  con->window = naNewWindow(
    cpTranslate(CP3DView),
    naMakeRectS(40, 30, 1, 1),
    NA_WINDOW_RESIZEABLE,
    CP_THREEDEE_WINDOW_STORAGE_TAG);
  naAddUIReaction(con->window, NA_UI_COMMAND_RESHAPE, cp_ReshapeThreeDeeWindow, con);

  // The 3D space
  con->display = naNewOpenGLSpace(naMakeSize(initial3DDisplayWidth, initial3DDisplayWidth), cp_InitThreeDeeOpenGL, con);
  naAddUIReaction(con->display, NA_UI_COMMAND_REDRAW, cpUpdateThreeDeeDisplay, con);
  naAddUIReaction(con->display, NA_UI_COMMAND_MOUSE_MOVED, cpMoveRotationMouse, con->perspectiveController);
  naAddUIReaction(con->display, NA_UI_COMMAND_SCROLLED, cpScrollRotation, con->perspectiveController);
  
  // The control space
  con->controlSpace = naNewSpace(naMakeSize(fullControlWidth, 1));
    
  // layout
  cpBeginUILayout(con->controlSpace, naMakeBorder2D(0., 0., 0., 0.));
  cpAddUIRow(cpGetThreeDeeCoordinateControllerUIElement(con->coordinateController), 0);
  cpAddUIRow(cpGetThreeDeePerspectiveControllerUIElement(con->perspectiveController), 0);
  cpAddUIRow(cpGetThreeDeeOpacityControllerUIElement(con->opacityController), 0);
  cpAddUIRow(cpGetThreeDeeOptionsControllerUIElement(con->optionsController), 0);
  cpEndUILayout();

  NASpace* content = naGetWindowContentSpace(con->window);
  cpBeginUILayout(content, naMakeBorder2D(0., 0., 0., 0.));
  cpAddUIRow(con->display, 0);
  cpAddUICol(con->controlSpace, 0);
  cpEndUILayout();
  
  return con;
}



void cpDeallocThreeDeeController(CPThreeDeeController* con){
  naShutdownPixelFont(con->fontId);
  naFree(con);
}



void cpShowThreeDeeController(CPThreeDeeController* con){
  naShowWindow(con->window);
}



void cpUpdateThreeDeeController(CPThreeDeeController* con){
  cpUpdateThreeDeeCoordinateController(con->coordinateController);
  cpUpdateThreeDeePerspectiveController(con->perspectiveController);
  cpUpdateThreeDeeOpacityController(con->opacityController);
  cpUpdateThreeDeeOptionsController(con->optionsController);

  naRefreshUIElement(con->display, 0.);
}
