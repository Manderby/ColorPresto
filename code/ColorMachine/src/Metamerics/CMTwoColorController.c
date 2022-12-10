
#include "CMTwoColorController.h"

#include "NAApp.h"

#include "../CMDesign.h"

struct CMTwoColorController{
  NAOpenGLSpace* space;
  NAVec3f leftColor;
  NAVec3f rightColor;
};



void cmInitTwoColorDisplay(void* data){
  NA_UNUSED(data);
//  CMTwoColorController* con = (CMTwoColorController*)(data);
  glShadeModel(GL_FLAT);
  glEnable(GL_BLEND);
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
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

  NABabyColor color;
  naFillDefaultTextColorWithSkin(color, naGetSkinForCurrentAppearance());
  color[3] = .2f;

  glLineWidth(2);
  glBegin(GL_LINE_STRIP);
  glColor4fv(color);
  glVertex2d(-1., -1.);
  glVertex2d(-1., +1.);
  glVertex2d(+1., +1.);
  glVertex2d(+1., -1.);
  glVertex2d(-1., -1.);
  glEnd();
  
  naSwapOpenGLSpaceBuffer(con->space);
  
  return NA_TRUE;
}



CMTwoColorController* cmAllocTwoColorController(){
  CMTwoColorController* con = naAlloc(CMTwoColorController);

  con->space = naNewOpenGLSpace(naMakeSize(twoColorWidth, twoColorHeight), cmInitTwoColorDisplay, con);
  naAddUIReaction(con->space, NA_UI_COMMAND_REDRAW, cmRedrawTwoColorController, con);
  
  return con;
}



void cmDeallocTwoColorController(CMTwoColorController* con){
  naFree(con);
}



NAOpenGLSpace* cmGetTwoColorControllerUIElement(CMTwoColorController* con){
  return con->space;
}



void cmUpdateTwoColorController(CMTwoColorController* con, const float* leftColor, const float* rightColor){
  naCopyV3f(con->leftColor, leftColor);
  naCopyV3f(con->rightColor, rightColor);

  naRefreshUIElement(con->space, 0.);
}

