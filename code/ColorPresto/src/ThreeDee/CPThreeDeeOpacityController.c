
#include "CPThreeDeeOpacityController.h"

#include "../CPDesign.h"
#include "../CPTranslations.h"

#include "CML.h"

#include "NAUtility/NABinaryData.h"
#include "NAUtility/NAMemory.h"
#include "NAUtility/NAString.h"

struct CPThreeDeeOpacityController{
  NASpace* space;
  CPThreeDeeController* parent;

  NALabel* pointsOpacityLabel;
  NASlider* pointsOpacitySlider;
  NALabel* gridAlphaLabel;
  NASlider* gridAlphaSlider;
  NALabel* gridTintLabel;
  NASlider* gridTintSlider;
  NALabel* bodyAlphaLabel;
  NASlider* bodyAlphaSlider;
  NALabel* bodySolidLabel;
  NACheckBox* bodySolidCheckBox;

  float pointsOpacity;
  float gridAlpha;
  float gridTint;
  float bodyAlpha;
  NABool bodySolid;

};



NABool cp_PressThreeDeeOpacityButton(NAReaction reaction){
  CPThreeDeeOpacityController* con = (CPThreeDeeOpacityController*)reaction.controller;

  if(reaction.uiElement == con->bodySolidCheckBox){
    con->bodySolid = naGetCheckBoxState(con->bodySolidCheckBox);
  }

  cpUpdateThreeDeeController(con->parent);

  return TRUE;
}



NABool cp_ChangeThreeDeeOpacitySlider(NAReaction reaction){
  CPThreeDeeOpacityController* con = (CPThreeDeeOpacityController*)reaction.controller;

  if(reaction.uiElement == con->pointsOpacitySlider){
    con->pointsOpacity = (float)naGetSliderValue(con->pointsOpacitySlider);
  }else if(reaction.uiElement == con->gridAlphaSlider){
    con->gridAlpha = (float)naGetSliderValue(con->gridAlphaSlider);
  }else if(reaction.uiElement == con->gridTintSlider){
    con->gridTint = (float)naGetSliderValue(con->gridTintSlider);
  }else if(reaction.uiElement == con->bodyAlphaSlider){
    con->bodyAlpha = (float)naGetSliderValue(con->bodyAlphaSlider);
  }
  
  cpUpdateThreeDeeController(con->parent);

  return TRUE;
}



CPThreeDeeOpacityController* cpAllocThreeDeeOpacityController(CPThreeDeeController* parent){
  CPThreeDeeOpacityController* con = naAlloc(CPThreeDeeOpacityController);

  con->parent = parent;

  con->space = naNewSpace(naMakeSize(1, 1));
  naSetSpaceAlternateBackground(con->space, NA_TRUE);

  con->pointsOpacityLabel = naNewLabel(cpTranslate(CPPointsOpacity), threeDeeLabelWidth);
  con->pointsOpacitySlider = naNewSlider(threeDeeControlWidth);
  naSetSliderRange(con->pointsOpacitySlider, 0., 1., 0);
  naAddUIReaction(con->pointsOpacitySlider, NA_UI_COMMAND_EDITED, cp_ChangeThreeDeeOpacitySlider, con);

  con->gridAlphaLabel = naNewLabel(cpTranslate(CPGridOpacity), threeDeeLabelWidth);
  con->gridAlphaSlider = naNewSlider(threeDeeControlWidth);
  naSetSliderRange(con->gridAlphaSlider, 0., 1., 0);
  naAddUIReaction(con->gridAlphaSlider, NA_UI_COMMAND_EDITED, cp_ChangeThreeDeeOpacitySlider, con);

  con->gridTintLabel = naNewLabel(cpTranslate(CPGridTint), threeDeeLabelWidth);
  con->gridTintSlider = naNewSlider(threeDeeControlWidth);
  naSetSliderRange(con->gridTintSlider, 0., 1., 0);
  naAddUIReaction(con->gridTintSlider, NA_UI_COMMAND_EDITED, cp_ChangeThreeDeeOpacitySlider, con);

  con->bodyAlphaLabel = naNewLabel(cpTranslate(CPBodyTint), threeDeeLabelWidth);
  con->bodyAlphaSlider = naNewSlider(threeDeeControlWidth);
  naSetSliderRange(con->bodyAlphaSlider, 0., 1., 0);
  naAddUIReaction(con->bodyAlphaSlider, NA_UI_COMMAND_EDITED, cp_ChangeThreeDeeOpacitySlider, con);

  con->bodySolidLabel = naNewLabel(cpTranslate(CPSolid), threeDeeLabelWidth);
  con->bodySolidCheckBox = naNewCheckBox("", 30);
  naAddUIReaction(con->bodySolidCheckBox, NA_UI_COMMAND_PRESSED, cp_PressThreeDeeOpacityButton, con);

  // layout

  cpBeginUILayout(con->space, threeDeeBezel);
  
  cpAddUIRow(con->pointsOpacityLabel, uiElemHeight);
  cpAddUICol(con->pointsOpacitySlider, marginH);

  cpAddUIRow(con->gridAlphaLabel, uiElemHeight);
  cpAddUICol(con->gridAlphaSlider, marginH);

  cpAddUIRow(con->gridTintLabel, uiElemHeight);
  cpAddUICol(con->gridTintSlider, marginH);

  cpAddUIRow(con->bodyAlphaLabel, uiElemHeight);
  cpAddUICol(con->bodyAlphaSlider, marginH);

  cpAddUIRow(con->bodySolidLabel, uiElemHeight);
  cpAddUICol(con->bodySolidCheckBox, marginH);

  cpEndUILayout();

  // initial values

  con->pointsOpacity = 0.f;
  con->bodySolid = NA_TRUE;
  con->bodyAlpha = .2f;
  con->gridAlpha = 1.f;
  con->gridTint = .5f;

  return con;
}



void cpDeallocThreeDeeOpacityController(CPThreeDeeOpacityController* con){
  naFree(con);
}



NASpace* cpGetThreeDeeOpacityControllerUIElement(CPThreeDeeOpacityController* con){
  return con->space;
}


NABool cpGetThreeDeeOpacityControllerBodySolid(CPThreeDeeOpacityController* con){
  return con->bodySolid;
}
float cpGetThreeDeeOpacityControllerPointsOpacity(CPThreeDeeOpacityController* con){
  return con->pointsOpacity;
}
float cpGetThreeDeeOpacityControllerBodyAlpha(CPThreeDeeOpacityController* con){
  return con->bodyAlpha;
}
float cpGetThreeDeeOpacityControllerGridAlpha(CPThreeDeeOpacityController* con){
  return con->gridAlpha;
}
float cpGetThreeDeeOpacityControllerGridTint(CPThreeDeeOpacityController* con){
  return con->gridTint;
}


void cpUpdateThreeDeeOpacityController(CPThreeDeeOpacityController* con)
{
  naSetSliderValue(con->pointsOpacitySlider, con->pointsOpacity);
  naSetSliderValue(con->gridAlphaSlider, con->gridAlpha);
  naSetSliderValue(con->gridTintSlider, con->gridTint);
  naSetSliderValue(con->bodyAlphaSlider, con->bodyAlpha);
  naSetSliderValue(con->bodyAlphaSlider, con->bodyAlpha);
  naSetCheckBoxState(con->bodySolidCheckBox, con->bodySolid);
}
