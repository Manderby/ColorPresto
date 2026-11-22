
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



void cp_PressOptionsButton(NAReaction reaction) {
  CPThreeDeeOptionsController* con = (CPThreeDeeOptionsController*)reaction.controller;

  if(reaction.uiElement == con->spectrumCheckBox) {
    con->showSpectrum = naGetCheckBoxState(con->spectrumCheckBox);
  }else if(reaction.uiElement == con->axisCheckBox) {
    con->showAxis = naGetCheckBoxState(con->axisCheckBox);
  }

  cpUpdateThreeDeeController(con->parent);
}



void cp_ChangeOptionsSlider(NAReaction reaction) {
  CPThreeDeeOptionsController* con = (CPThreeDeeOptionsController*)reaction.controller;

  if(reaction.uiElement == con->backgroundSlider) {
    con->backgroundGray = (float)naGetSliderValue(con->backgroundSlider);
  }else if(reaction.uiElement == con->fovySlider) {
    con->fovy = (float)naGetSliderValue(con->fovySlider);
    if(con->fovy < 15.f) {con->fovy = 0.f;}
  }
  
  cpUpdateThreeDeeController(con->parent);
}



CPThreeDeeOptionsController* cpAllocThreeDeeOptionsController(CPThreeDeeController* parent) {
  CPThreeDeeOptionsController* con = naAlloc(CPThreeDeeOptionsController);

  con->parent = parent;

  con->space = naNewSpace();
  naSetSpaceAlternateBackground(con->space, NA_FALSE);

  con->axisLabel = naNewLabel(cpTranslate(CPAxis));
  con->axisCheckBox = naNewCheckBox("");
  naAddUIReaction(con->axisCheckBox, NA_UI_COMMAND_PRESSED, cp_PressOptionsButton, con);

  con->spectrumLabel = naNewLabel(cpTranslate(CPSpectrum));
  con->spectrumCheckBox = naNewCheckBox("");
  naAddUIReaction(con->spectrumCheckBox, NA_UI_COMMAND_PRESSED, cp_PressOptionsButton, con);

  con->backgroundLabel = naNewLabel(cpTranslate(CPBackground));
  con->backgroundSlider = naNewSlider();
  naSetSliderRange(con->backgroundSlider, 0., 1., 0);
  naAddUIReaction(con->backgroundSlider, NA_UI_COMMAND_EDITED, cp_ChangeOptionsSlider, con);

  con->fovyLabel = naNewLabel(cpTranslate(CPFovy));
  con->fovySlider = naNewSlider();
  naSetSliderRange(con->fovySlider, 90., 0., 0);
  naAddUIReaction(con->fovySlider, NA_UI_COMMAND_EDITED, cp_ChangeOptionsSlider, con);

  // layout
  
  NABorder2D zeroPadding = naMakeBorder2D(0., 0., 0., 0.);

  naBeginLayout(con->space, threeDeeBorder);
    naAddLayoutSection(uiElemHeight, zeroPadding);
      naAddLayoutElement(con->axisLabel, 0, threeDeeLabelWidth);
      naAddLayoutElement(con->axisCheckBox, marginH, 30);

    naAddLayoutSection(uiElemHeight, zeroPadding);
      naAddLayoutElement(con->spectrumLabel, 0, threeDeeLabelWidth);
      naAddLayoutElement(con->spectrumCheckBox, marginH, 30);

    naAddLayoutSection(uiElemHeight, zeroPadding);
      naAddLayoutElement(con->backgroundLabel, 0, threeDeeLabelWidth);
      naAddLayoutElement(con->backgroundSlider, marginH, threeDeeControlWidth);

    naAddLayoutSection(uiElemHeight, zeroPadding);
      naAddLayoutElement(con->fovyLabel, 0, threeDeeLabelWidth);
      naAddLayoutElement(con->fovySlider, marginH, threeDeeControlWidth);

  naEndLayout();
  
  // initial values
  con->showSpectrum = NA_FALSE;
  con->showAxis = NA_TRUE;
  con->backgroundGray = 0.3f;
  con->fovy = 50.f;

  return con;
}



void cpDeallocThreeDeeOptionsController(CPThreeDeeOptionsController* con) {
  naFree(con);
}



NASpace* cpGetThreeDeeOptionsControllerUIElement(CPThreeDeeOptionsController* con) {
  return con->space;
}



float cpGetThreeDeeOptionsControllerAxisGray(CPThreeDeeOptionsController* con) {
  float axisGray = con->backgroundGray + .5f;
  if(axisGray > 1.f) {axisGray -= 1.f;}
  return axisGray;
}
float cpGetThreeDeeOptionsControllerBackgroundGray(CPThreeDeeOptionsController* con) {
  return con->backgroundGray;
}
float cpGetThreeDeeOptionsControllerFovy(CPThreeDeeOptionsController* con) {
  return con->fovy;
}
NABool cpGetThreeDeeOptionsControllerShowAxis(CPThreeDeeOptionsController* con) {
  return con->showAxis;
}
NABool cpGetThreeDeeOptionsControllerShowSpectrum(CPThreeDeeOptionsController* con) {
  return con->showSpectrum;
}



void cpUpdateThreeDeeOptionsController(CPThreeDeeOptionsController* con)
{
  naSetCheckBoxState(con->spectrumCheckBox, con->showSpectrum);
  naSetCheckBoxState(con->axisCheckBox, con->showAxis);
  naSetSliderValue(con->backgroundSlider, con->backgroundGray);
  naSetSliderValue(con->fovySlider, con->fovy);
}
