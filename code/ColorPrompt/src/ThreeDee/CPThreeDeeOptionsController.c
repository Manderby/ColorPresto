
#include "CPThreeDeeOptionsController.h"

#include "../CPDesign.h"
#include "../CPTranslations.h"

#include "CML.h"

#include "NAUtility/NABinaryData.h"
#include "NAUtility/NAMemory.h"
#include "NAUtility/NAString.h"

struct CPThreeDeeOptionsController{
  NASpace* space;
  CPThreeDeeController* parent;

  NALabel* axisLabel;
  NACheckBox* axisCheckBox;
  NALabel* spectrumLabel;
  NACheckBox* spectrumCheckBox;
  NALabel* backgroundLabel;
  NASlider* backgroundSlider;
  NALabel* fovyLabel;
  NASlider* fovySlider;

  NABool showSpectrum;
  NABool showAxis;
  float backgroundGray;
  float fovy;
};



NABool cmPressOptionsButton(NAReaction reaction){
  CPThreeDeeOptionsController* con = (CPThreeDeeOptionsController*)reaction.controller;

  if(reaction.uiElement == con->spectrumCheckBox){
    con->showSpectrum = naGetCheckBoxState(con->spectrumCheckBox);
  }else if(reaction.uiElement == con->axisCheckBox){
    con->showAxis = naGetCheckBoxState(con->axisCheckBox);
  }

  cpUpdateThreeDeeController(con->parent);

  return TRUE;
}



NABool cmChangeOptionsSlider(NAReaction reaction){
  CPThreeDeeOptionsController* con = (CPThreeDeeOptionsController*)reaction.controller;

  if(reaction.uiElement == con->backgroundSlider){
    con->backgroundGray = (float)naGetSliderValue(con->backgroundSlider);
  }else if(reaction.uiElement == con->fovySlider){
    con->fovy = (float)naGetSliderValue(con->fovySlider);
    if(con->fovy < 15.f){con->fovy = 0.f;}
  }
  
  cpUpdateThreeDeeController(con->parent);

  return TRUE;
}



CPThreeDeeOptionsController* cpAllocThreeDeeOptionsController(CPThreeDeeController* parent){
  CPThreeDeeOptionsController* con = naAlloc(CPThreeDeeOptionsController);

  con->parent = parent;

  con->space = naNewSpace(naMakeSize(1, 1));
  naSetSpaceAlternateBackground(con->space, NA_FALSE);

  con->axisLabel = naNewLabel(cpTranslate(CPAxis), threeDeeLabelWidth);
  con->axisCheckBox = naNewCheckBox("", 30);
  naAddUIReaction(con->axisCheckBox, NA_UI_COMMAND_PRESSED, cmPressOptionsButton, con);

  con->spectrumLabel = naNewLabel(cpTranslate(CPSpectrum), threeDeeLabelWidth);
  con->spectrumCheckBox = naNewCheckBox("", 30);
  naAddUIReaction(con->spectrumCheckBox, NA_UI_COMMAND_PRESSED, cmPressOptionsButton, con);

  con->backgroundLabel = naNewLabel(cpTranslate(CPBackground), threeDeeLabelWidth);
  con->backgroundSlider = naNewSlider(threeDeeControlWidth);
  naSetSliderRange(con->backgroundSlider, 0., 1., 0);
  naAddUIReaction(con->backgroundSlider, NA_UI_COMMAND_EDITED, cmChangeOptionsSlider, con);

  con->fovyLabel = naNewLabel(cpTranslate(CPFovy), threeDeeLabelWidth);
  con->fovySlider = naNewSlider(threeDeeControlWidth);
  naSetSliderRange(con->fovySlider, 90., 0., 0);
  naAddUIReaction(con->fovySlider, NA_UI_COMMAND_EDITED, cmChangeOptionsSlider, con);

  // layout
  cpBeginUILayout(con->space, threeDeeBezel);
  
  cpAddUIRow(con->axisLabel, uiElemHeight);
  cpAddUICol(con->axisCheckBox, marginH);

  cpAddUIRow(con->spectrumLabel, uiElemHeight);
  cpAddUICol(con->spectrumCheckBox, marginH);

  cpAddUIRow(con->backgroundLabel, uiElemHeight);
  cpAddUICol(con->backgroundSlider, marginH);

  cpAddUIRow(con->fovyLabel, uiElemHeight);
  cpAddUICol(con->fovySlider, marginH);

  cpEndUILayout();

  // initial values
  con->showSpectrum = NA_FALSE;
  con->showAxis = NA_TRUE;
  con->backgroundGray = 0.3f;
  con->fovy = 50.f;

  return con;
}



void cpDeallocThreeDeeOptionsController(CPThreeDeeOptionsController* con){
  naFree(con);
}



NASpace* cpGetThreeDeeOptionsControllerUIElement(CPThreeDeeOptionsController* con){
  return con->space;
}



float cpGetThreeDeeOptionsControllerAxisGray(CPThreeDeeOptionsController* con){
  float axisGray = con->backgroundGray + .5f;
  if(axisGray > 1.f){axisGray -= 1.f;}
  return axisGray;
}
float cpGetThreeDeeOptionsControllerBackgroundGray(CPThreeDeeOptionsController* con){
  return con->backgroundGray;
}
float cpGetThreeDeeOptionsControllerFovy(CPThreeDeeOptionsController* con){
  return con->fovy;
}
NABool cpGetThreeDeeOptionsControllerShowAxis(CPThreeDeeOptionsController* con){
  return con->showAxis;
}
NABool cpGetThreeDeeOptionsControllerShowSpectrum(CPThreeDeeOptionsController* con){
  return con->showSpectrum;
}



void cpUpdateThreeDeeOptionsController(CPThreeDeeOptionsController* con)
{
  naSetCheckBoxState(con->spectrumCheckBox, con->showSpectrum);
  naSetCheckBoxState(con->axisCheckBox, con->showAxis);
  naSetSliderValue(con->backgroundSlider, con->backgroundGray);
  naSetSliderValue(con->fovySlider, con->fovy);
}
