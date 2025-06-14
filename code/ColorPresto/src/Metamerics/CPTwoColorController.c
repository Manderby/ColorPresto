
#include "CPTwoColorController.h"
#include "../CPOpenGLHelper.h"

#include "NAApp/NAApp.h"

#include "../CPDesign.h"

struct CPTwoColorController{
  NAOpenGLSpace* space;
  NAVec3f leftColor;
  NAVec3f rightColor;
};



void cp_InitTwoColorDisplay(void* data){
  NA_UNUSED(data);
  glShadeModel(GL_FLAT);
  glEnable(GL_BLEND);
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}



void cp_RedrawTwoColorController(NAReaction reaction){
  CPTwoColorController* con = (CPTwoColorController*)(reaction.controller);

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

  double uiScale = naGetUIElementResolutionScale(con->space);
  cpDrawBorder(uiScale);
  
  naSwapOpenGLSpaceBuffer(con->space);
}



CPTwoColorController* cpAllocTwoColorController(){
  CPTwoColorController* con = naAlloc(CPTwoColorController);

  con->space = naNewOpenGLSpace(naMakeSize(twoColorWidth, twoColorHeight), cp_InitTwoColorDisplay, con);
  naAddUIReaction(con->space, NA_UI_COMMAND_REDRAW, cp_RedrawTwoColorController, con);
  
  return con;
}



void cpDeallocTwoColorController(CPTwoColorController* con){
  naFree(con);
}



NAOpenGLSpace* cpGetTwoColorControllerUIElement(CPTwoColorController* con){
  return con->space;
}



void cpUpdateTwoColorController(CPTwoColorController* con, const float* leftColor, const float* rightColor){
  naFillV3fWithCopy(con->leftColor, leftColor);
  naFillV3fWithCopy(con->rightColor, rightColor);

  naRefreshUIElement(con->space, 0.);
}

