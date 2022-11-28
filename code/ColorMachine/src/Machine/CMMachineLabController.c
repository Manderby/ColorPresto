
#include "CMMachineLabController.h"

#include "CMMachineObserverController.h"

#include "NAApp.h"
#include "CMDesign.h"


struct CMMachineLabController{
  NASpace* space;

  NALabel* labColorSpaceLabel;
  NAPopupButton* labColorSpacePopupButton;

  NALabel* valueKTitleLabel;
  NATextField* valueKTextField;
  NASlider* valueKSlider;
  NALabel* valuekeTitleLabel;
  NATextField* valuekeTextField;
  NASlider* valuekeSlider;
};



NABool cmSelectLabColorSpace(NAReaction reaction){
  CMMachineLabController* con = (CMMachineLabController*)reaction.controller;
  CMLColorMachine* cm = cmGetCurrentColorMachine();

  size_t index = naGetPopupButtonItemIndex(con->labColorSpacePopupButton, reaction.uiElement);
  CMLLabColorSpaceType labColorSpaceType = (CMLLabColorSpaceType)index;
  if(labColorSpaceType >= CML_LAB_CUSTOM_L){++labColorSpaceType;}
  cmlSetLabColorSpace(cm, labColorSpaceType);
  
  cmUpdateMachine();

  return NA_TRUE;
}



NABool cmSetLabValue(NAReaction reaction){
  CMMachineLabController* con = (CMMachineLabController*)reaction.controller;
  CMLColorMachine* cm = cmGetCurrentColorMachine();

  float K;
  float ke;
  cmlGetAdamsChromaticityValenceParameters(cm, &K, &ke);

  if(reaction.uiElement == con->valueKTextField){
    K = naGetTextFieldDouble(con->valueKTextField);
  }else if(reaction.uiElement == con->valueKSlider){
    K = naGetSliderValue(con->valueKSlider);
  }else if(reaction.uiElement == con->valuekeTextField){
    ke = naGetTextFieldDouble(con->valuekeTextField);
  }else if(reaction.uiElement == con->valuekeSlider){
    ke = naGetSliderValue(con->valuekeSlider);
  }
  cmlSetAdamsChromaticityValenceParameters(cm, K, ke);
  
  cmUpdateMachine();

  return NA_TRUE;
}



CMMachineLabController* cmAllocMachineLabController(void){
  CMMachineLabController* con = naAlloc(CMMachineLabController);

  con->space = naNewSpace(naMakeSize(1, 1));
  naSetSpaceAlternateBackground(con->space, NA_TRUE);

  con->labColorSpaceLabel = naNewLabel("Lab Colorspace", machineLabelWidth);
  con->labColorSpacePopupButton = naNewPopupButton(200);
  for(size_t i = 0; i < CML_LAB_COUNT; ++i){
    CMLLabColorSpaceType labColorSpaceType = (CMLLabColorSpaceType)i;
    if(labColorSpaceType == CML_LAB_CUSTOM_L){continue;}
    NAMenuItem* item = naNewMenuItem(cmlGetLabColorSpaceTypeString(labColorSpaceType));
    naAddPopupButtonMenuItem(con->labColorSpacePopupButton, item, NA_NULL);
    naAddUIReaction(item, NA_UI_COMMAND_PRESSED, cmSelectLabColorSpace, con);
  }

  con->valueKTitleLabel = naNewLabel("K", machineLabelWidth);
  con->valueKTextField = cmNewValueTextField(cmSetLabValue, con);
  con->valueKSlider = naNewSlider(60);
  naSetSliderRange(con->valueKSlider, 1., 2., 0);
  naAddUIReaction(con->valueKSlider, NA_UI_COMMAND_EDITED, cmSetLabValue, con);
  
  con->valuekeTitleLabel = naNewLabel("ke", machineLabelWidth);
  con->valuekeTextField = cmNewValueTextField(cmSetLabValue, con);
  con->valuekeSlider = naNewSlider(60);
  naSetSliderRange(con->valuekeSlider, .1, 1., 0);
  naAddUIReaction(con->valuekeSlider, NA_UI_COMMAND_EDITED, cmSetLabValue, con);

  // layout
  cmBeginUILayout(con->space, spaceBezel);
  cmAddUIRow(con->labColorSpaceLabel, uiElemHeight);
  cmAddUICol(con->labColorSpacePopupButton, marginH);

  cmAddUIRow(con->valueKTitleLabel, uiElemHeight);
  cmAddUICol(con->valueKTextField, marginH);
  cmAddUICol(con->valueKSlider, marginH);

  cmAddUIRow(con->valuekeTitleLabel, uiElemHeight);
  cmAddUICol(con->valuekeTextField, marginH);
  cmAddUICol(con->valuekeSlider, marginH);
  cmEndUILayout();

  return con;
}



void cmDeallocMachineLabController(CMMachineLabController* con){
  naFree(con);
}



NASpace* cmGetMachineLabControllerUIElement(CMMachineLabController* con){
  return con->space;
}



void cmUpdateMachineLabController(CMMachineLabController* con){
  CMLColorMachine* cm = cmGetCurrentColorMachine();

  CMLLabColorSpaceType labColorSpace = cmlGetLabColorSpace(cm);

  NABool enableCoefficients = labColorSpace == CML_LAB_ADAMS_CROMATIC_VALENCE; 
  NABool showCoefficients = labColorSpace != CML_LAB_CIELAB; 

  float K;
  float ke;
  cmlGetAdamsChromaticityValenceParameters(cm, &K, &ke);
  naSetTextFieldText(
    con->valueKTextField,
    showCoefficients ? naAllocSprintf(NA_TRUE, "%1.03f", K) : "");
  naSetSliderValue(con->valueKSlider, K);
  naSetTextFieldText(
    con->valuekeTextField,
    showCoefficients ? naAllocSprintf(NA_TRUE, "%1.03f", ke) : "");
  naSetSliderValue(con->valuekeSlider, ke);
  
  naSetLabelEnabled(con->valueKTitleLabel, enableCoefficients);
  naSetLabelEnabled(con->valuekeTitleLabel, enableCoefficients);
  naSetTextFieldEnabled(con->valueKTextField, enableCoefficients);
  naSetTextFieldEnabled(con->valuekeTextField, enableCoefficients);
  naSetSliderEnabled(con->valueKSlider, enableCoefficients);
  naSetSliderEnabled(con->valuekeSlider, enableCoefficients);
}
