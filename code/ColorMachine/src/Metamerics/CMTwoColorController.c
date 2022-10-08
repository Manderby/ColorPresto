
#include "CMTwoColorController.h"
#include "NAApp.h"

struct CMTwoColorController{
  NAOpenGLSpace* space;
  NAVec3f leftColor;
  NAVec3f rightColor;
};



void cmInitTwoColorDisplay(void* data){
  NA_UNUSED(data);
//  CMTwoColorController* con = (CMTwoColorController*)(data);
  glShadeModel(GL_FLAT);
}



NABool cmRedrawTwoColorController(NAReaction reaction){
  CMTwoColorController* con = (CMTwoColorController*)(reaction.controller);

  glBegin(GL_TRIANGLE_STRIP);
  glColor3fv(con->leftColor);
  glVertex2d(-1., -1.);
  glVertex2d(-1., +1.);
  glVertex2d( 0., -1.);
  glVertex2d( 0., +1.);
  glColor3fv(con->rightColor);
  glVertex2d(+1., -1.);
  glVertex2d(+1., +1.);
  glEnd();
  
  naSwapOpenGLSpaceBuffer(con->space);
  
  return NA_TRUE;
}



CMTwoColorController* cmAllocTwoColorController(NASize size){
  CMTwoColorController* con = naAlloc(CMTwoColorController);
  naZeron(con, sizeof(CMTwoColorController));

  con->space = naNewOpenGLSpace(size, cmInitTwoColorDisplay, con);
  naAddUIReaction(con->space, NA_UI_COMMAND_REDRAW, cmRedrawTwoColorController, con);
  
  return con;
}



void cmDeallocTwoColorController(CMTwoColorController* con){
  naFree(con);
}



NAOpenGLSpace* cmGetTwoColorControllerUIElement(CMTwoColorController* con){
  return con->space;
}



void cmSetTwoColorControllerColors(CMTwoColorController* con, NAVec3f leftColor, NAVec3f rightColor){
  naCopyV3f(con->leftColor, leftColor);
  naCopyV3f(con->rightColor, rightColor);
}



void cmUpdateTwoColorController(const CMTwoColorController* con){
  naRefreshUIElement(con->space, 0.);
}
