
#include "CPGammaDisplayController.h"

#include "../../CPColorPromptApplication.h"
#include "../../CPDesign.h"
#include "../CPColorController.h"

#include "NAApp.h"



struct CPGammaDisplayController{
  NAOpenGLSpace* display;
};



void cmInitGammaDisplayController(void* data){
  glEnable(GL_LINE_SMOOTH);
  glEnable(GL_BLEND);
  glEnable(GL_DEPTH_TEST);
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}



NABool cmDrawGammaDisplayController(NAReaction reaction){
  CPGammaDisplayController* con = (CPGammaDisplayController*)reaction.controller;
  CMLColorMachine* cm = cpGetCurrentColorMachine();

  double uiScale = naGetUIElementResolutionFactor(con->display);
  NASize viewSize = naGetUIElementRect(reaction.uiElement).size;
  glViewport(
    0,
    0,
    (GLsizei)(viewSize.width * uiScale),
    (GLsizei)(viewSize.height * uiScale));

  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  glMatrixMode(GL_PROJECTION);
  glPushMatrix();
  glLoadIdentity();
  glOrtho(0, 1, 0, 1, -1., 1.);

  float stripes = 10.f;

  const CMLFunction* (responses[3]) = {0};
  responses[0] = cmlGetResponseCurveFunc(cmlGetResponseR(cm));
  responses[1] = cmlGetResponseCurveFunc(cmlGetResponseG(cm));
  responses[2] = cmlGetResponseCurveFunc(cmlGetResponseB(cm));

  glBegin(GL_LINE_STRIP);
    glColor3f(1.f, .5f, .5f);
    for(uint32 x = 0; x < viewSize.width; ++x){
      float curX = (float)x / (float)viewSize.width;
      float y = cmlEval(responses[0], curX);
      float z = sinf(stripes * (curX * NA_PI2f + (0.f/3.f) * NA_PI2f));
      glVertex3f(curX, y, z);
    }
  glEnd();
  glBegin(GL_LINE_STRIP);
    glColor3f(.5f, 1.f, .5f);
    for(uint32 x = 0; x < viewSize.width; ++x){
      float curX = (float)x / (float)viewSize.width;
      float y = cmlEval(responses[1], curX);
      float z = sinf(stripes * (curX * NA_PI2f + (1.f/3.f) * NA_PI2f));
      glVertex3f(curX, y, z);
    }
  glEnd();
  glBegin(GL_LINE_STRIP);
    glColor3f(.5f, .5f, 1.f);
    for(uint32 x = 0; x < viewSize.width; ++x){
      float curX = (float)x / (float)viewSize.width;
      float y = cmlEval(responses[2], curX);
      float z = sinf(stripes * (curX * NA_PI2f + (2.f/3.f) * NA_PI2f));
      glVertex3f(curX, y, z);
    }
  glEnd();

  glMatrixMode(GL_PROJECTION);
  glPopMatrix();

  naSwapOpenGLSpaceBuffer(con->display);

  return NA_TRUE;
}



CPGammaDisplayController* cmAllocGammaDisplayController(){
  CPGammaDisplayController* con = naAlloc(CPGammaDisplayController);
  
  con->display = naNewOpenGLSpace(naMakeSize(gammaDisplaySize, gammaDisplaySize), cmInitGammaDisplayController, con);
  naAddUIReaction(con->display, NA_UI_COMMAND_REDRAW, cmDrawGammaDisplayController, con);
  
  return con;
}



void cmDeallocGammaDisplayController(CPGammaDisplayController* con){
}



NAOpenGLSpace* cmGetGammaDisplayControllerUIElement(CPGammaDisplayController* con){
  return con->display;
}



void cmUpdateGammaDisplayController(CPGammaDisplayController* con){
  naRefreshUIElement(con->display, 0.);
}
