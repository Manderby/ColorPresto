
#include "CMRotationController.h"

#include "CMDesign.h"
#include "CMTranslations.h"
#include "CMWhitePoints.h"

#include "CML.h"

#include "NAUtility/NABinaryData.h"
#include "NAUtility/NAMemory.h"
#include "NAUtility/NAString.h"

struct CMRotationController{
  NASpace* space;

  NALabel* rotationLabel;
  NAButton* rotationButton;
  NASlider* rotationSlider;

  CMThreeDeeController* parentController;

  double rotationStep;
  double viewPol;
  double viewEqu;
  double zoom;
};



void cmStepRotation(void* data){
  CMRotationController* con = (CMRotationController*)data;
  if(con->rotationStep != 0.){
    con->viewEqu -= con->rotationStep * .015;
    naCallApplicationFunctionInSeconds(cmStepRotation, data, 1/60.);
    cmUpdateThreeDeeController(con->parentController);
  }
}



NABool cmPressRotationButton(NAReaction reaction){
  CMRotationController* con = (CMRotationController*)reaction.controller;

  if(reaction.uiElement == con->rotationButton){
    con->rotationStep = 0.;
  }

  cmUpdateThreeDeeController(con->parentController);

  return TRUE;
}



NABool cmChangeRotationSlider(NAReaction reaction){
  CMRotationController* con = (CMRotationController*)reaction.controller;

  if(reaction.uiElement == con->rotationSlider){
    NABool needsRotationStart = (con->rotationStep == 0.);
    con->rotationStep = naGetSliderValue(con->rotationSlider);
    if(con->rotationStep < .1 && con->rotationStep > -.1){con->rotationStep = 0.;}
    if(needsRotationStart){cmStepRotation(con);}
  }
  
  cmUpdateThreeDeeController(con->parentController);

  return TRUE;
}



void cmFixThreeDeeViewParameters(CMRotationController* con){
  if(con->zoom <= .025f){con->zoom = .025f;}
  if(con->zoom >= 2.f){con->zoom = 2.f;}
  if(con->viewEqu < -NA_PIf){con->viewEqu += NA_PI2f;}
  if(con->viewEqu > NA_PIf){con->viewEqu -= NA_PI2f;}
  if(con->viewPol <= NA_SINGULARITYf){con->viewPol = NA_SINGULARITYf;}
  if(con->viewPol >= NA_PIf - NA_SINGULARITYf){con->viewPol = NA_PIf - NA_SINGULARITYf;}
}



NABool cmMoveRotationMouse(NAReaction reaction){
  CMRotationController* con = (CMRotationController*)reaction.controller;

  const NAMouseStatus* status = naGetMouseStatus();
  if(status->leftPressed){
    
    NAPos mouseDiff = naMakePos(status->pos.x - status->prevPos.x, status->pos.y - status->prevPos.y);
    double scaleFactor = cmGetUIScaleFactorForWindow(naGetUIElementNativePtr(con->space));

    con->viewEqu -= mouseDiff.x * .01f * scaleFactor;
    con->viewPol += mouseDiff.y * .01f * scaleFactor;

    cmFixThreeDeeViewParameters(con);
    cmRefreshThreeDeeDisplay(con->parentController);
  }
  return NA_TRUE;
}



NABool cmScrollRotation(NAReaction reaction){
  CMRotationController* con = (CMRotationController*)reaction.controller;

  const NAMouseStatus* status = naGetMouseStatus();
  
  con->zoom *= 1. + (status->pos.y - status->prevPos.y) * .01;
  cmFixThreeDeeViewParameters(con);
  cmRefreshThreeDeeDisplay(con->parentController);

  return NA_TRUE;
}



CMRotationController* cmAllocRotationController(CMThreeDeeController* parentController){
  CMRotationController* con = naAlloc(CMRotationController);
  naZeron(con, sizeof(CMRotationController));

  con->parentController = parentController;

  con->space = naNewSpace(naMakeSize(1, 1));
  naSetSpaceAlternateBackground(con->space, NA_FALSE);

  con->rotationLabel = naNewLabel(cmTranslate(CMRotation), threeDeeRotationLabelWidth);
  con->rotationSlider = naNewSlider(threeDeeControlWidth);
  con->rotationButton = naNewTextButton(cmTranslate(CMStop), 70, NA_BUTTON_PUSH | NA_BUTTON_BORDERED);
  naSetSliderRange(con->rotationSlider, -1., +1., 0);
  naAddUIReaction(con->rotationButton, NA_UI_COMMAND_PRESSED, cmPressRotationButton, con);
  naAddUIReaction(con->rotationSlider, NA_UI_COMMAND_EDITED, cmChangeRotationSlider, con);

  // layout

  cmBeginUILayout(con->space, threeDeeBezel);
  
  cmAddUIRow(con->rotationLabel, uiElemHeight);
  cmAddUICol(con->rotationButton, 0.);
  cmAddUICol(con->rotationSlider, 0.);

  cmEndUILayout();

  // initial values
  double scaleFactor = cmGetUIScaleFactorForWindow(naGetUIElementNativePtr(con->space));

  con->rotationStep = 0.;
  con->viewPol = 1.3f;
  con->viewEqu = NA_PIf / 4.f;
  con->zoom = 1. / scaleFactor;

  return con;
}



void cmDeallocRotationController(CMRotationController* con){
  naFree(con);
}



NASpace* cmGetRotationUIElement(CMRotationController* con){
  return con->space;
}



double cmGetRotationStep(CMRotationController* con){
  return con->rotationStep;
}
double cmGetRotationViewPol(CMRotationController* con){
  return con->viewPol;
}
double cmGetRotationViewEqu(CMRotationController* con){
  return con->viewEqu;
}
double cmGetRotationZoom(CMRotationController* con){
  return con->zoom;
}
void cmSetRotationZoom(CMRotationController* con, double zoom){
  con->zoom = zoom;
}



void cmUpdateRotationController(CMRotationController* con)
{
  naSetSliderValue(con->rotationSlider, con->rotationStep);
}
