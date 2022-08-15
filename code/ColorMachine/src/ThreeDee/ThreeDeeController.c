
#include "NAApp.h"
#include "NAVectorAlgebra.h"
#include "NA3DHelper.h"

#include "mainC.h"
#include "ThreeDeeController.h"
#include <CML.h>

struct CMThreeDeeController{
  NAWindow* window;
  NAOpenGLSpace* display;
  NASpace* controlSpace;
  
  double fovy;
  double zoom;
};



void cmInitThreeDeeOpenGL(void* data){
  NA_UNUSED(data);
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
  
  CMLColorMachine* cm = cmGetCurrentColorMachine();
  
  // ////////////////
  // Setup the openGL view
  // ////////////////

//  NARect viewRect = naGetUIElementRect(con->display, NA_NULL, NA_FALSE);
//  glViewport(0, 0, (GLsizei)viewRect.size.width, (GLsizei)viewRect.size.height);
//  
//  float curZoom;
//  glMatrixMode(GL_PROJECTION);
//  glLoadIdentity();
//  if(con->fovy == 0){
//    glOrtho(
//      -(viewRect.size.width / 200.) * con->zoom,
//      (viewRect.size.width / 200.) * con->zoom,
//      -(viewRect.size.height / 200.) * con->zoom,
//      (viewRect.size.height / 200.) * con->zoom,
//      -50.,
//      50.);
//    curZoom = con->zoom;
//  }else{
//    NAMat44d projectionMatrix;
//    naFillMatrixPerspective(
//      projectionMatrix,
//      con->fovy,
//      viewRect.size.width / viewRect.size.height,
//      .1,
//      50.);
//    glLoadMatrixd(projectionMatrix);
//    curZoom = (viewRect.size.width / 300.) * con->zoom / (2. * (viewRect.size.width / viewRect.size.height) * naTan(.5 * naDegToRad(con->fovy)));
//  }
//
//  glMatrixMode(GL_MODELVIEW);
//	glLoadIdentity();






  glClearColor(0., 0., 0., 1.);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    
  naSwapOpenGLSpaceBuffer(con->display);
  
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
  con->display = naNewOpenGLSpace(naMakeSize(300, 300), cmInitThreeDeeOpenGL, NA_NULL);
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
  cmUpdateThreeDeeController(con);

  return con;
}



void cmFreeThreeDeeController(CMThreeDeeController* con){
  naFree(con);
}



void cmShowThreeDeeController(CMThreeDeeController* con){
  naShowWindow(con->window);
}
