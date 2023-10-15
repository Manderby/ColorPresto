
#include "CMThreeDeeOpacityController.h"

#include "../CPDesign.h"
#include "../CPTranslations.h"

#include "CML.h"

#include "NAUtility/NABinaryData.h"
#include "NAUtility/NAMemory.h"
#include "NAUtility/NAString.h"

struct CMThreeDeeOpacityController{
  NASpace* space;
  CMThreeDeeController* parent;

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



NABool cmPressThreeDeeOpacityButton(NAReaction reaction){
  CMThreeDeeOpacityController* con = (CMThreeDeeOpacityController*)reaction.controller;

  if(reaction.uiElement == con->bodySolidCheckBox){
    con->bodySolid = naGetCheckBoxState(con->bodySolidCheckBox);
  }

  cmUpdateThreeDeeController(con->parent);

  return TRUE;
}



NABool cmChangeThreeDeeOpacitySlider(NAReaction reaction){
  CMThreeDeeOpacityController* con = (CMThreeDeeOpacityController*)reaction.controller;

  if(reaction.uiElement == con->pointsOpacitySlider){
    con->pointsOpacity = (float)naGetSliderValue(con->pointsOpacitySlider);
  }else if(reaction.uiElement == con->gridAlphaSlider){
    con->gridAlpha = (float)naGetSliderValue(con->gridAlphaSlider);
  }else if(reaction.uiElement == con->gridTintSlider){
    con->gridTint = (float)naGetSliderValue(con->gridTintSlider);
  }else if(reaction.uiElement == con->bodyAlphaSlider){
    con->bodyAlpha = (float)naGetSliderValue(con->bodyAlphaSlider);
  }
  
  cmUpdateThreeDeeController(con->parent);

  return TRUE;
}



CMThreeDeeOpacityController* cmAllocThreeDeeOpacityController(CMThreeDeeController* parent){
  CMThreeDeeOpacityController* con = naAlloc(CMThreeDeeOpacityController);

  con->parent = parent;

  con->space = naNewSpace(naMakeSize(1, 1));
  naSetSpaceAlternateBackground(con->space, NA_TRUE);

  con->pointsOpacityLabel = naNewLabel(cmTranslate(CMPointsOpacity), threeDeeLabelWidth);
  con->pointsOpacitySlider = naNewSlider(threeDeeControlWidth);
  naSetSliderRange(con->pointsOpacitySlider, 0., 1., 0);
  naAddUIReaction(con->pointsOpacitySlider, NA_UI_COMMAND_EDITED, cmChangeThreeDeeOpacitySlider, con);

  con->gridAlphaLabel = naNewLabel(cmTranslate(CMGridOpacity), threeDeeLabelWidth);
  con->gridAlphaSlider = naNewSlider(threeDeeControlWidth);
  naSetSliderRange(con->gridAlphaSlider, 0., 1., 0);
  naAddUIReaction(con->gridAlphaSlider, NA_UI_COMMAND_EDITED, cmChangeThreeDeeOpacitySlider, con);

  con->gridTintLabel = naNewLabel(cmTranslate(CMGridTint), threeDeeLabelWidth);
  con->gridTintSlider = naNewSlider(threeDeeControlWidth);
  naSetSliderRange(con->gridTintSlider, 0., 1., 0);
  naAddUIReaction(con->gridTintSlider, NA_UI_COMMAND_EDITED, cmChangeThreeDeeOpacitySlider, con);

  con->bodyAlphaLabel = naNewLabel(cmTranslate(CMBodyTint), threeDeeLabelWidth);
  con->bodyAlphaSlider = naNewSlider(threeDeeControlWidth);
  naSetSliderRange(con->bodyAlphaSlider, 0., 1., 0);
  naAddUIReaction(con->bodyAlphaSlider, NA_UI_COMMAND_EDITED, cmChangeThreeDeeOpacitySlider, con);

  con->bodySolidLabel = naNewLabel(cmTranslate(CMSolid), threeDeeLabelWidth);
  con->bodySolidCheckBox = naNewCheckBox("", 30);
  naAddUIReaction(con->bodySolidCheckBox, NA_UI_COMMAND_PRESSED, cmPressThreeDeeOpacityButton, con);

  // layout

  cmBeginUILayout(con->space, threeDeeBezel);
  
  cmAddUIRow(con->pointsOpacityLabel, uiElemHeight);
  cmAddUICol(con->pointsOpacitySlider, marginH);

  cmAddUIRow(con->gridAlphaLabel, uiElemHeight);
  cmAddUICol(con->gridAlphaSlider, marginH);

  cmAddUIRow(con->gridTintLabel, uiElemHeight);
  cmAddUICol(con->gridTintSlider, marginH);

  cmAddUIRow(con->bodyAlphaLabel, uiElemHeight);
  cmAddUICol(con->bodyAlphaSlider, marginH);

  cmAddUIRow(con->bodySolidLabel, uiElemHeight);
  cmAddUICol(con->bodySolidCheckBox, marginH);

  cmEndUILayout();

  // initial values

  con->pointsOpacity = 0.f;
  con->bodySolid = NA_TRUE;
  con->bodyAlpha = .2f;
  con->gridAlpha = 1.f;
  con->gridTint = .5f;

  return con;
}



void cmDeallocThreeDeeOpacityController(CMThreeDeeOpacityController* con){
  naFree(con);
}



NASpace* cmGetThreeDeeOpacityControllerUIElement(CMThreeDeeOpacityController* con){
  return con->space;
}


NABool cmGetThreeDeeOpacityControllerBodySolid(CMThreeDeeOpacityController* con){
  return con->bodySolid;
}
float cmGetThreeDeeOpacityControllerPointsOpacity(CMThreeDeeOpacityController* con){
  return con->pointsOpacity;
}
float cmGetThreeDeeOpacityControllerBodyAlpha(CMThreeDeeOpacityController* con){
  return con->bodyAlpha;
}
float cmGetThreeDeeOpacityControllerGridAlpha(CMThreeDeeOpacityController* con){
  return con->gridAlpha;
}
float cmGetThreeDeeOpacityControllerGridTint(CMThreeDeeOpacityController* con){
  return con->gridTint;
}


void cmUpdateThreeDeeOpacityController(CMThreeDeeOpacityController* con)
{
  naSetSliderValue(con->pointsOpacitySlider, con->pointsOpacity);
  naSetSliderValue(con->gridAlphaSlider, con->gridAlpha);
  naSetSliderValue(con->gridTintSlider, con->gridTint);
  naSetSliderValue(con->bodyAlphaSlider, con->bodyAlpha);
  naSetSliderValue(con->bodyAlphaSlider, con->bodyAlpha);
  naSetCheckBoxState(con->bodySolidCheckBox, con->bodySolid);
}
