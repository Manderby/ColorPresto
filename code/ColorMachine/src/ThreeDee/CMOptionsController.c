
#include "CMOptionsController.h"

#include "CMDesign.h"
#include "CMTranslations.h"
#include "CMWhitePoints.h"

#include "CML.h"

#include "NAUtility/NABinaryData.h"
#include "NAUtility/NAMemory.h"
#include "NAUtility/NAString.h"

struct CMOptionsController{
  NASpace* space;

  NALabel* axisLabel;
  NACheckBox* axisCheckBox;
  NALabel* spectrumLabel;
  NACheckBox* spectrumCheckBox;
  NALabel* backgroundLabel;
  NASlider* backgroundSlider;
  NALabel* fovyLabel;
  NASlider* fovySlider;

  CMThreeDeeController* parentController;

  NABool showSpectrum;
  NABool showAxis;
  double backgroundGray;
  double fovy;
};



NABool cmPressOptionsButton(NAReaction reaction){
  CMOptionsController* con = (CMOptionsController*)reaction.controller;

  if(reaction.uiElement == con->spectrumCheckBox){
    con->showSpectrum = naGetCheckBoxState(con->spectrumCheckBox);
  }else if(reaction.uiElement == con->axisCheckBox){
    con->showAxis = naGetCheckBoxState(con->axisCheckBox);
  }

  cmUpdateThreeDeeController(con->parentController);

  return TRUE;
}



NABool cmChangeOptionsSlider(NAReaction reaction){
  CMOptionsController* con = (CMOptionsController*)reaction.controller;

  if(reaction.uiElement == con->backgroundSlider){
    con->backgroundGray = naGetSliderValue(con->backgroundSlider);
  }else if(reaction.uiElement == con->fovySlider){
    con->fovy = naGetSliderValue(con->fovySlider);
    if(con->fovy < 15.f){con->fovy = 0.f;}
  }
  
  cmUpdateThreeDeeController(con->parentController);

  return TRUE;
}



CMOptionsController* cmAllocOptionsController(CMThreeDeeController* parentController){
  CMOptionsController* con = naAlloc(CMOptionsController);
  naZeron(con, sizeof(CMOptionsController));

  con->parentController = parentController;

  con->space = naNewSpace(naMakeSize(1, 1));
  naSetSpaceAlternateBackground(con->space, NA_FALSE);

  con->axisLabel = naNewLabel(cmTranslate(CMAxis), threeDeeLabelWidth);
  con->axisCheckBox = naNewCheckBox("", 30);
  naAddUIReaction(con->axisCheckBox, NA_UI_COMMAND_PRESSED, cmPressOptionsButton, con);

  con->spectrumLabel = naNewLabel(cmTranslate(CMSpectrum), threeDeeLabelWidth);
  con->spectrumCheckBox = naNewCheckBox("", 30);
  naAddUIReaction(con->spectrumCheckBox, NA_UI_COMMAND_PRESSED, cmPressOptionsButton, con);

  con->backgroundLabel = naNewLabel(cmTranslate(CMBackground), threeDeeLabelWidth);
  con->backgroundSlider = naNewSlider(threeDeeControlWidth);
  naSetSliderRange(con->backgroundSlider, 0., 1., 0);
  naAddUIReaction(con->backgroundSlider, NA_UI_COMMAND_EDITED, cmChangeOptionsSlider, con);

  con->fovyLabel = naNewLabel(cmTranslate(CMFovy), threeDeeLabelWidth);
  con->fovySlider = naNewSlider(threeDeeControlWidth);
  naSetSliderRange(con->fovySlider, 90., 0., 0);
  naAddUIReaction(con->fovySlider, NA_UI_COMMAND_EDITED, cmChangeOptionsSlider, con);

  // layout

  cmBeginUILayout(con->space, threeDeeBezel);
  
  cmAddUIRow(con->axisLabel, uiElemHeight);
  cmAddUICol(con->axisCheckBox, marginH);

  cmAddUIRow(con->spectrumLabel, uiElemHeight);
  cmAddUICol(con->spectrumCheckBox, marginH);

  cmAddUIRow(con->backgroundLabel, uiElemHeight);
  cmAddUICol(con->backgroundSlider, marginH);

  cmAddUIRow(con->fovyLabel, uiElemHeight);
  cmAddUICol(con->fovySlider, marginH);

  cmEndUILayout();

  // initial values

  con->showSpectrum = NA_FALSE;
  con->showAxis = NA_TRUE;
  con->backgroundGray = 0.3;
  con->fovy = 50.;

  return con;
}



void cmDeallocOptionsController(CMOptionsController* con){
  naFree(con);
}



NASpace* cmGetOptionsUIElement(CMOptionsController* con){
  return con->space;
}



double cmGetOptionsAxisGray(CMOptionsController* con){
  float axisGray = con->backgroundGray + .5f;
  if(axisGray > 1.f){axisGray -= 1.f;}
  return axisGray;
}
double cmGetOptionsBackgroundGray(CMOptionsController* con){
  return con->backgroundGray;
}
double cmGetOptionsFovy(CMOptionsController* con){
  return con->fovy;
}
NABool cmGetOptionsShowAxis(CMOptionsController* con){
  return con->showAxis;
}
NABool cmGetOptionsShowSpectrum(CMOptionsController* con){
  return con->showSpectrum;
}


void cmUpdateOptionsController(CMOptionsController* con)
{
  naSetCheckBoxState(con->spectrumCheckBox, con->showSpectrum);
  naSetCheckBoxState(con->axisCheckBox, con->showAxis);
  naSetSliderValue(con->backgroundSlider, con->backgroundGray);
  naSetSliderValue(con->fovySlider, con->fovy);
}
