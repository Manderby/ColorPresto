
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
  
  NAInt fontId;
  
  double fovy;
  double zoom;
};



void cmInitThreeDeeOpenGL(void* data){
  CMThreeDeeController* con = (CMThreeDeeController*)data;
  con->fontId = naStartupPixelFont();
}



NABool cmReshapeThreeDeeWindow(NAReaction reaction){
  CMThreeDeeController* con = (CMThreeDeeController*)reaction.controller;

  double controlWidth = 200;
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



NABool cmUpdateThreeDeeDisplay(NAReaction reaction){
  CMThreeDeeController* con = (CMThreeDeeController*)reaction.controller;
  
//  CMLColorMachine* cm = cmGetCurrentColorMachine();
  
  CMLColorType coordSpace = CML_COLOR_XYZ;
  NABool showAxis = NA_TRUE;
  CMLNormedConverter normedCoordConverter = cmlGetNormedOutputConverter(CML_COLOR_XYZ);
  float min[3];
  float max[3];
  const char* labels[3];
  CMLVec3 axisRGB;
  NARect viewRect;
  int primeAxis;
  double scale[3];
  double curZoom;
  double viewPol;
  double viewEqu;

  viewRect = naGetUIElementRect(con->display, NA_NULL, NA_FALSE);
  cmlGetMinBounds(min, coordSpace);
  cmlGetMaxBounds(max, coordSpace);
  labels[0] = "X";
  labels[1] = "Y";
  labels[2] = "Z";
  axisRGB[0] = 1.;
  axisRGB[1] = 0.;
  axisRGB[2] = 1.;
  primeAxis = 1;
  naFillV3d(scale, 1.f, 1.f, 1.f);
  curZoom = 1.;
  viewPol = 1.3f;
  viewEqu = NA_PIf / 4.f;





  cmBeginThreeDeeDrawing();

  cmSetupThreeDeeProjection(viewRect, con->fovy);
  cmSetupThreeDeeModelView(primeAxis, scale, curZoom, viewPol, viewEqu);

  if(showAxis){ cmDrawThreeDeeAxis(normedCoordConverter, min, max, labels, axisRGB, con->fontId);}

  cmEndThreeDeeDrawing(con->display);
    
  return NA_TRUE;
}



void cmUpdateThreeDeeController(CMThreeDeeController* con){
  NAReaction dummyReaction = {con->display, NA_UI_COMMAND_REDRAW, con};
  cmUpdateThreeDeeDisplay(dummyReaction);
}



CMThreeDeeController* cmAllocThreeDeeController(void){
  CMThreeDeeController* con = naAlloc(CMThreeDeeController);
  naZeron(con, sizeof(CMThreeDeeController));
  
  // Create childs
  con->window = naNewWindow("3D", naMakeRectS(40, 30, 500, 500), NA_WINDOW_RESIZEABLE, 0);
  con->display = naNewOpenGLSpace(naMakeSize(300, 300), cmInitThreeDeeOpenGL, con);
  con->controlSpace = naNewSpace(naMakeSize(200, 400));
  naSetSpaceAlternateBackground(con->controlSpace, NA_TRUE);
   
  // Add childs
  NASpace* content = naGetWindowContentSpace(con->window);
  naAddSpaceChild(content, con->display, naMakePos(0, 0));
  naAddSpaceChild(content, con->controlSpace, naMakePos(300, 0));
  
  // Add reactions
  naAddUIReaction(con->window, NA_UI_COMMAND_RESHAPE, cmReshapeThreeDeeWindow, con);
  naAddUIReaction(con->display, NA_UI_COMMAND_REDRAW, cmUpdateThreeDeeDisplay, con);
  
  // Set initial values
  float scaleFactor = cmGetUIScaleFactorForWindow(naGetUIElementNativePtr(con->window));
  con->fovy = 50.;
  con->zoom = 1. / scaleFactor;

  // Update the whole window
  NAReaction dummyReaction = {con->window, NA_UI_COMMAND_RESHAPE, con};
  cmReshapeThreeDeeWindow(dummyReaction);

  return con;
}



void cmFreeThreeDeeController(CMThreeDeeController* con){
  naShutdownPixelFont(con->fontId);
  naFree(con);
}



void cmShowThreeDeeController(CMThreeDeeController* con){
  naShowWindow(con->window);
}
