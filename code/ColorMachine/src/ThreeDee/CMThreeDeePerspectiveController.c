
#include "CMThreeDeePerspectiveController.h"

#include "../CMDesign.h"
#include "../CMTranslations.h"

#include "CML.h"

#include "NAUtility/NABinaryData.h"
#include "NAUtility/NAMemory.h"
#include "NAUtility/NAString.h"

struct CMThreeDeePerspectiveController{
  NASpace* space;
  CMThreeDeeController* parent;

  NALabel* rotationLabel;
  NAButton* rotationButton;
  NASlider* rotationSlider;

  double rotationStep;
  double anglePol;
  double angleEqu;
  double zoom;
};



void cmStepRotation(void* data){
  CMThreeDeePerspectiveController* con = (CMThreeDeePerspectiveController*)data;
  
  if(con->rotationStep != 0.){
    con->angleEqu -= con->rotationStep * .015f;
    naCallApplicationFunctionInSeconds(cmStepRotation, data, 1./60.);
    cmUpdateThreeDeeController(con->parent);
  }
}



NABool cmPressRotationButton(NAReaction reaction){
  CMThreeDeePerspectiveController* con = (CMThreeDeePerspectiveController*)reaction.controller;

  if(reaction.uiElement == con->rotationButton){
    con->rotationStep = 0.;
  }

  cmUpdateThreeDeeController(con->parent);

  return TRUE;
}



NABool cmChangeRotationSlider(NAReaction reaction){
  CMThreeDeePerspectiveController* con = (CMThreeDeePerspectiveController*)reaction.controller;

  if(reaction.uiElement == con->rotationSlider){
    NABool needsRotationStart = (con->rotationStep == 0.);
    con->rotationStep = (float)naGetSliderValue(con->rotationSlider);
    if(con->rotationStep < .1 && con->rotationStep > -.1){con->rotationStep = 0.;}
    if(needsRotationStart){cmStepRotation(con);}
  }
  
  cmUpdateThreeDeeController(con->parent);

  return TRUE;
}



void cmFixThreeDeeViewParameters(CMThreeDeePerspectiveController* con){
  if(con->zoom <= .025f){con->zoom = .025f;}
  if(con->zoom >= 2.f){con->zoom = 2.f;}
  if(con->angleEqu < -NA_PIf){con->angleEqu += NA_PI2f;}
  if(con->angleEqu > NA_PIf){con->angleEqu -= NA_PI2f;}
  if(con->anglePol <= NA_SINGULARITYf){con->anglePol = NA_SINGULARITYf;}
  if(con->anglePol >= NA_PIf - NA_SINGULARITYf){con->anglePol = NA_PIf - NA_SINGULARITYf;}
}



NABool cmMoveRotationMouse(NAReaction reaction){
  CMThreeDeePerspectiveController* con = (CMThreeDeePerspectiveController*)reaction.controller;

  const NAMouseStatus* status = naGetMouseStatus();
  if(status->leftPressed){
    
    NAPos mouseDiff = naMakePos(status->pos.x - status->prevPos.x, status->pos.y - status->prevPos.y);
    double scaleFactor = cmGetUIScaleFactorForWindow(naGetUIElementNativePtr(con->space));

    con->angleEqu -= (float)(mouseDiff.x * .01 * scaleFactor);
    con->anglePol += (float)(mouseDiff.y * .01 * scaleFactor);

    cmFixThreeDeeViewParameters(con);
    cmRefreshThreeDeeDisplay(con->parent);
  }
  return NA_TRUE;
}



NABool cmScrollRotation(NAReaction reaction){
  CMThreeDeePerspectiveController* con = (CMThreeDeePerspectiveController*)reaction.controller;

  const NAMouseStatus* status = naGetMouseStatus();
  
  con->zoom *= 1.f + (float)(status->pos.y - status->prevPos.y) * .01f;
  cmFixThreeDeeViewParameters(con);
  cmRefreshThreeDeeDisplay(con->parent);

  return NA_TRUE;
}



CMThreeDeePerspectiveController* cmAllocThreeDeePerspectiveController(CMThreeDeeController* parent){
  CMThreeDeePerspectiveController* con = naAlloc(CMThreeDeePerspectiveController);

  con->parent = parent;

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
  float scaleFactor = (float)cmGetUIScaleFactorForWindow(naGetUIElementNativePtr(con->space));

  con->rotationStep = 0.;
  con->anglePol = 1.3f;
  con->angleEqu = NA_PIf / 4.f;
  con->zoom = 1.f / scaleFactor;

  return con;
}



void cmDeallocThreeDeePerspectiveController(CMThreeDeePerspectiveController* con){
  naFree(con);
}



NASpace* cmGetThreeDeePerspectiveControllerUIElement(CMThreeDeePerspectiveController* con){
  return con->space;
}



double cmGetThreeDeePerspectiveControllerRotationStep(CMThreeDeePerspectiveController* con){
  return con->rotationStep;
}
double cmGetThreeDeePerspectiveControllerRotationAnglePol(CMThreeDeePerspectiveController* con){
  return con->anglePol;
}
double cmGetThreeDeePerspectiveControllerRotationAngleEqu(CMThreeDeePerspectiveController* con){
  return con->angleEqu;
}
double cmGetThreeDeePerspectiveControllerZoom(CMThreeDeePerspectiveController* con){
  return con->zoom;
}
void cmSetThreeDeePerspectiveControllerZoom(CMThreeDeePerspectiveController* con, double zoom){
  con->zoom = zoom;
}



void cmUpdateThreeDeePerspectiveController(CMThreeDeePerspectiveController* con)
{
  naSetSliderValue(con->rotationSlider, con->rotationStep);
}
