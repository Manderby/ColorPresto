
#include "CPThreeDeePerspectiveController.h"

#include "../CPDesign.h"
#include "../CPTranslations.h"

#include "CML.h"

#include "NAUtility/NABinaryData.h"
#include "NAUtility/NAMemory.h"
#include "NAUtility/NAString.h"
#include "NAMath/NAVectorAlgebra.h"

struct CPThreeDeePerspectiveController{
  NASpace* space;
  CPThreeDeeController* parent;

  NALabel* rotationLabel;
  NAButton* rotationButton;
  NASlider* rotationSlider;

  double rotationStep;
  double anglePol;
  double angleEqu;
  double zoom;
};



void cp_StepRotation(void* data){
  CPThreeDeePerspectiveController* con = (CPThreeDeePerspectiveController*)data;
  
  if(con->rotationStep != 0.){
    con->angleEqu -= con->rotationStep * .015f;
    naCallApplicationFunctionInSeconds(cp_StepRotation, data, 1./60.);
    cpUpdateThreeDeeController(con->parent);
  }
}



void cp_PressRotationButton(NAReaction reaction){
  CPThreeDeePerspectiveController* con = (CPThreeDeePerspectiveController*)reaction.controller;

  if(reaction.uiElement == con->rotationButton){
    con->rotationStep = 0.;
  }

  cpUpdateThreeDeeController(con->parent);
}



void cp_ChangeRotationSlider(NAReaction reaction){
  CPThreeDeePerspectiveController* con = (CPThreeDeePerspectiveController*)reaction.controller;

  if(reaction.uiElement == con->rotationSlider){
    NABool needsRotationStart = (con->rotationStep == 0.);
    con->rotationStep = (float)naGetSliderValue(con->rotationSlider);
    if(con->rotationStep < .1 && con->rotationStep > -.1){con->rotationStep = 0.;}
    if(needsRotationStart){cp_StepRotation(con);}
  }
  
  cpUpdateThreeDeeController(con->parent);
}



void cp_FixThreeDeeViewParameters(CPThreeDeePerspectiveController* con){
  if(con->zoom <= .025f){con->zoom = .025f;}
  if(con->zoom >= 2.f){con->zoom = 2.f;}
  if(con->angleEqu < -NA_PIf){con->angleEqu += NA_PI2f;}
  if(con->angleEqu > NA_PIf){con->angleEqu -= NA_PI2f;}
  if(con->anglePol <= NA_SINGULARITYf){con->anglePol = NA_SINGULARITYf;}
  if(con->anglePol >= NA_PIf - NA_SINGULARITYf){con->anglePol = NA_PIf - NA_SINGULARITYf;}
}



void cpMoveRotationMouse(NAReaction reaction){
  CPThreeDeePerspectiveController* con = (CPThreeDeePerspectiveController*)reaction.controller;

  const NAMouseStatus* mouseStatus = naGetCurrentMouseStatus();
  if(naGetMouseButtonPressed(mouseStatus, NA_MOUSE_BUTTON_LEFT) || naGetMouseButtonPressed(mouseStatus, NA_MOUSE_BUTTON_MIDDLE)){
    
    NAPos mouseDiff = naGetMouseDelta(mouseStatus);
    double uiScale = naGetUIElementResolutionScale(con->space);

    con->angleEqu -= (float)(mouseDiff.x * .01 * uiScale);
    con->anglePol += (float)(mouseDiff.y * .01 * uiScale);

    cp_FixThreeDeeViewParameters(con);
    cpRefreshThreeDeeDisplay(con->parent);
  }
}



void cpScrollRotation(NAReaction reaction){
  CPThreeDeePerspectiveController* con = (CPThreeDeePerspectiveController*)reaction.controller;

  const double* transform = naGetOpenGLSpaceTransformation(reaction.uiElement);
  NAPos translation = naGetMat33dTranslation(transform);
  con->zoom *= naPow(2., -translation.y * .01f);

  cp_FixThreeDeeViewParameters(con);
  cpRefreshThreeDeeDisplay(con->parent);
}



CPThreeDeePerspectiveController* cpAllocThreeDeePerspectiveController(CPThreeDeeController* parent){
  CPThreeDeePerspectiveController* con = naAlloc(CPThreeDeePerspectiveController);

  con->parent = parent;

  con->space = naNewSpace(naMakeSize(1, 1));
  naSetSpaceAlternateBackground(con->space, NA_FALSE);

  con->rotationLabel = naNewLabel(cpTranslate(CPRotation), threeDeeLabelWidth - setButtonWidth + marginH - marginHSmall);
  con->rotationSlider = naNewSlider(threeDeeControlWidth);
  con->rotationButton = naNewTextPushButton(cpTranslate(CPStop), setButtonWidth);
  naSetSliderRange(con->rotationSlider, -1., +1., 0);
  naAddUIReaction(con->rotationButton, NA_UI_COMMAND_PRESSED, cp_PressRotationButton, con);
  naAddUIReaction(con->rotationSlider, NA_UI_COMMAND_EDITED, cp_ChangeRotationSlider, con);

  // layout

  cpBeginUILayout(con->space, threeDeeBorder);
  
  cpAddUIRow(con->rotationLabel, uiElemHeight);
  cpAddUICol(con->rotationButton, 0.);
  cpAddUICol(con->rotationSlider, marginHSmall);

  cpEndUILayout();

  // initial values
  double uiScale = naGetUIElementResolutionScale(con->space);

  con->rotationStep = 0.;
  con->anglePol = 1.3f;
  con->angleEqu = NA_PIf / 4.f;
  con->zoom = 1.f / (float)uiScale;

  return con;
}



void cpDeallocThreeDeePerspectiveController(CPThreeDeePerspectiveController* con){
  naFree(con);
}



NASpace* cpGetThreeDeePerspectiveControllerUIElement(CPThreeDeePerspectiveController* con){
  return con->space;
}



double cpGetThreeDeePerspectiveControllerRotationStep(CPThreeDeePerspectiveController* con){
  return con->rotationStep;
}
double cpGetThreeDeePerspectiveControllerRotationAnglePol(CPThreeDeePerspectiveController* con){
  return con->anglePol;
}
double cpGetThreeDeePerspectiveControllerRotationAngleEqu(CPThreeDeePerspectiveController* con){
  return con->angleEqu;
}
double cpGetThreeDeePerspectiveControllerZoom(CPThreeDeePerspectiveController* con){
  return con->zoom;
}
void cpSetThreeDeePerspectiveControllerZoom(CPThreeDeePerspectiveController* con, double zoom){
  con->zoom = zoom;
}



void cpUpdateThreeDeePerspectiveController(CPThreeDeePerspectiveController* con)
{
  naSetSliderValue(con->rotationSlider, con->rotationStep);
}
