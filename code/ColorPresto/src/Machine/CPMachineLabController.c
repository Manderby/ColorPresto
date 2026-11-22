
#include "CPMachineLabController.h"

#include "../CPColorPrestoApplication.h"
#include "../CPDesign.h"
#include "../CPTranslations.h"
#include "CPMachineObserverController.h"

#include "NAApp/NAApp.h"
#include "NAUtility/NAMemory.h"
#include "NAUtility/NAString.h"


struct CPMachineLabController{
  NASpace* space;

  NALabel* labColorSpaceLabel;
  NASelect* labColorSpaceSelect;

  NALabel* valueKTitleLabel;
  NATextField* valueKTextField;
  NASlider* valueKSlider;
  NALabel* valuekeTitleLabel;
  NATextField* valuekeTextField;
  NASlider* valuekeSlider;
};



void cp_SelectLabColorSpace(NAReaction reaction) {
  CPMachineLabController* con = (CPMachineLabController*)reaction.controller;
  CMLColorMachine* cm = cpGetCurrentColorMachine();

  size_t index = naGetSelectItemIndex(con->labColorSpaceSelect, reaction.uiElement);
  CMLLabColorSpaceType labColorSpaceType = (CMLLabColorSpaceType)index;
  if(labColorSpaceType >= CML_LAB_CUSTOM_L) {++labColorSpaceType;}
  cmlSetLabColorSpace(cm, labColorSpaceType);
  
  cpUpdateMachine();
}



void cpSetLabValue(NAReaction reaction) {
  CPMachineLabController* con = (CPMachineLabController*)reaction.controller;
  CMLColorMachine* cm = cpGetCurrentColorMachine();

  float K;
  float ke;
  cmlGetAdamsChromaticityValenceParameters(cm, &K, &ke);

  if(reaction.uiElement == con->valueKTextField) {
    K = (float)naGetTextFieldDouble(con->valueKTextField);
  }else if(reaction.uiElement == con->valueKSlider) {
    K = (float)naGetSliderValue(con->valueKSlider);
  }else if(reaction.uiElement == con->valuekeTextField) {
    ke = (float)naGetTextFieldDouble(con->valuekeTextField);
  }else if(reaction.uiElement == con->valuekeSlider) {
    ke = (float)naGetSliderValue(con->valuekeSlider);
  }
  cmlSetAdamsChromaticityValenceParameters(cm, K, ke);
  
  cpUpdateMachine();
}



CPMachineLabController* cpAllocMachineLabController(void) {
  CPMachineLabController* con = naAlloc(CPMachineLabController);

  con->space = naNewSpace();
  naSetSpaceAlternateBackground(con->space, NA_TRUE);

  con->labColorSpaceLabel = naNewLabel(cpTranslate(CPLabColorSpaceTitle));
  con->labColorSpaceSelect = naNewSelect();
  for(size_t i = 0; i < CML_LAB_COUNT; ++i) {
    CMLLabColorSpaceType labColorSpaceType = (CMLLabColorSpaceType)i;
    if(labColorSpaceType == CML_LAB_CUSTOM_L) {continue;}
    NAMenuItem* item = naNewMenuItem(cmlGetLabColorSpaceTypeString(labColorSpaceType), NA_NULL);
    naAddSelectMenuItem(con->labColorSpaceSelect, item, NA_NULL);
    naAddUIReaction(item, NA_UI_COMMAND_PRESSED, cp_SelectLabColorSpace, con);
  }

  con->valueKTitleLabel = naNewLabel(cpTranslate(CPLabColorSpaceK));
  con->valueKTextField = cpNewValueTextField(cpSetLabValue, con);
  con->valueKSlider = naNewSlider();
  naSetSliderRange(con->valueKSlider, 1., 2., 0);
  naAddUIReaction(con->valueKSlider, NA_UI_COMMAND_EDITED, cpSetLabValue, con);
  
  con->valuekeTitleLabel = naNewLabel(cpTranslate(CPLabColorSpaceke));
  con->valuekeTextField = cpNewValueTextField(cpSetLabValue, con);
  con->valuekeSlider = naNewSlider();
  naSetSliderRange(con->valuekeSlider, .1, 1., 0);
  naAddUIReaction(con->valuekeSlider, NA_UI_COMMAND_EDITED, cpSetLabValue, con);

  // layout
  
  naBeginLayout(con->space, spaceBorder);
    naAddLayoutSection(uiElemHeight, naMakeBorder2D(0., 0., 0., 0.));
      naAddLayoutElement(con->labColorSpaceLabel, 0, machineLabelWidth);
      naAddLayoutElement(con->labColorSpaceSelect, marginH, 200);
    naAddLayoutSection(uiElemHeight, naMakeBorder2D(0., 0., 0., 0.));
      naAddLayoutElement(con->valueKTitleLabel, 0, machineLabelWidth);
      naAddLayoutElement(con->valueKTextField, marginH, textFieldValueWidth);
      naAddLayoutElement(con->valueKSlider, marginH, 60);
    naAddLayoutSection(uiElemHeight, naMakeBorder2D(0., 0., 0., 0.));
      naAddLayoutElement(con->valuekeTitleLabel, 0, machineLabelWidth);
      naAddLayoutElement(con->valuekeTextField, marginH, textFieldValueWidth);
      naAddLayoutElement(con->valuekeSlider, marginH, 60);
  naEndLayout();

  return con;
}



void cpDeallocMachineLabController(CPMachineLabController* con) {
  naFree(con);
}



NASpace* cpGetMachineLabControllerUIElement(CPMachineLabController* con) {
  return con->space;
}



void cpUpdateMachineLabController(CPMachineLabController* con) {
  CMLColorMachine* cm = cpGetCurrentColorMachine();

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
