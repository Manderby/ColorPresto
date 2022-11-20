
#include "CMOpacityController.h"

#include "CMDesign.h"
#include "CMTranslations.h"
#include "CMWhitePoints.h"

#include "CML.h"

#include "NAUtility/NABinaryData.h"
#include "NAUtility/NAMemory.h"
#include "NAUtility/NAString.h"

struct CMOpacityController{
  NASpace* space;

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

  CMThreeDeeController* parentController;

  double pointsOpacity;
  double gridAlpha;
  double gridTint;
  double bodyAlpha;
  NABool bodySolid;

};



NABool cmPressOpacityButton(NAReaction reaction){
  CMOpacityController* con = (CMOpacityController*)reaction.controller;

  if(reaction.uiElement == con->bodySolidCheckBox){
    con->bodySolid = naGetCheckBoxState(con->bodySolidCheckBox);
  }

  cmUpdateThreeDeeController(con->parentController);

  return TRUE;
}



NABool cmChangeOpacitySlider(NAReaction reaction){
  CMOpacityController* con = (CMOpacityController*)reaction.controller;

  if(reaction.uiElement == con->pointsOpacitySlider){
    con->pointsOpacity = naGetSliderValue(con->pointsOpacitySlider);
  }else if(reaction.uiElement == con->gridAlphaSlider){
    con->gridAlpha = naGetSliderValue(con->gridAlphaSlider);
  }else if(reaction.uiElement == con->gridTintSlider){
    con->gridTint = naGetSliderValue(con->gridTintSlider);
  }else if(reaction.uiElement == con->bodyAlphaSlider){
    con->bodyAlpha = naGetSliderValue(con->bodyAlphaSlider);
  }
  
  cmUpdateThreeDeeController(con->parentController);

  return TRUE;
}



CMOpacityController* cmAllocOpacityController(CMThreeDeeController* parentController){
  CMOpacityController* con = naAlloc(CMOpacityController);
  naZeron(con, sizeof(CMOpacityController));

  con->parentController = parentController;

  con->space = naNewSpace(naMakeSize(1, 1));
  naSetSpaceAlternateBackground(con->space, NA_TRUE);

  con->pointsOpacityLabel = naNewLabel(cmTranslate(CMPointsOpacity), threeDeeLabelWidth);
  con->pointsOpacitySlider = naNewSlider(threeDeeControlWidth);
  naSetSliderRange(con->pointsOpacitySlider, 0., 1., 0);
  naAddUIReaction(con->pointsOpacitySlider, NA_UI_COMMAND_EDITED, cmChangeOpacitySlider, con);

  con->gridAlphaLabel = naNewLabel(cmTranslate(CMGridOpacity), threeDeeLabelWidth);
  con->gridAlphaSlider = naNewSlider(threeDeeControlWidth);
  naSetSliderRange(con->gridAlphaSlider, 0., 1., 0);
  naAddUIReaction(con->gridAlphaSlider, NA_UI_COMMAND_EDITED, cmChangeOpacitySlider, con);

  con->gridTintLabel = naNewLabel(cmTranslate(CMGridTint), threeDeeLabelWidth);
  con->gridTintSlider = naNewSlider(threeDeeControlWidth);
  naSetSliderRange(con->gridTintSlider, 0., 1., 0);
  naAddUIReaction(con->gridTintSlider, NA_UI_COMMAND_EDITED, cmChangeOpacitySlider, con);

  con->bodyAlphaLabel = naNewLabel(cmTranslate(CMBodyTint), threeDeeLabelWidth);
  con->bodyAlphaSlider = naNewSlider(threeDeeControlWidth);
  naSetSliderRange(con->bodyAlphaSlider, 0., 1., 0);
  naAddUIReaction(con->bodyAlphaSlider, NA_UI_COMMAND_EDITED, cmChangeOpacitySlider, con);

  con->bodySolidLabel = naNewLabel(cmTranslate(CMSolid), threeDeeLabelWidth);
  con->bodySolidCheckBox = naNewCheckBox("", 30);
  naAddUIReaction(con->bodySolidCheckBox, NA_UI_COMMAND_PRESSED, cmPressOpacityButton, con);

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

  con->pointsOpacity = 0.;
  con->bodySolid = NA_TRUE;
  con->bodyAlpha = .2;
  con->gridAlpha = 1.;
  con->gridTint = .5;

  return con;
}



void cmDeallocOpacityController(CMOpacityController* con){
  naFree(con);
}



NASpace* cmGetOpacityUIElement(CMOpacityController* con){
  return con->space;
}


NABool cmGetOpacityBodySolid(CMOpacityController* con){
  return con->bodySolid;
}
double cmGetOpacityPointsOpacity(CMOpacityController* con){
  return con->pointsOpacity;
}
double cmGetOpacityBodyAlpha(CMOpacityController* con){
  return con->bodyAlpha;
}
double cmGetOpacityGridAlpha(CMOpacityController* con){
  return con->gridAlpha;
}
double cmGetOpacityGridTint(CMOpacityController* con){
  return con->gridTint;
}


void cmUpdateOpacityController(CMOpacityController* con)
{
  naSetSliderValue(con->pointsOpacitySlider, con->pointsOpacity);
  naSetSliderValue(con->gridAlphaSlider, con->gridAlpha);
  naSetSliderValue(con->gridTintSlider, con->gridTint);
  naSetSliderValue(con->bodyAlphaSlider, con->bodyAlpha);
  naSetSliderValue(con->bodyAlphaSlider, con->bodyAlpha);
  naSetCheckBoxState(con->bodySolidCheckBox, con->bodySolid);
}
