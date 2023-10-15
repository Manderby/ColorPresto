
#include "CPMachineIlluminationController.h"

#include "../CPColorPromptApplication.h"
#include "../CPDesign.h"
#include "../CPTranslations.h"
#include "CPMachineObserverController.h"

#include "NAApp.h"


struct CPMachineIlluminationController{
  NASpace* space;

  NALabel* illuminationTitleLabel;
  NAPopupButton* illuminationPopupButton;
  NALabel* illuminationTemperatureTitleLabel;
  NATextField* illuminationTemperatureTextField;
  NALabel* illuminationKelvinLabel;
  NASlider* illuminationTemperatureSlider;
  NALabel* whitePointTitleLabel;
  NAButton* setWhitePointButton;
  NATextField* whitePointYTextField;
  NATextField* whitePointxTextField;
  NATextField* whitePointyTextField;
};



NABool cmSelectIllumination(NAReaction reaction){
  CPMachineIlluminationController* con = (CPMachineIlluminationController*)reaction.controller;
  CMLColorMachine* cm = cpGetCurrentColorMachine();

  size_t index = naGetPopupButtonItemIndex(con->illuminationPopupButton, reaction.uiElement);
  CMLIlluminationType illuminationType = (CMLIlluminationType)index;
  
  if(illuminationType == CML_ILLUMINATION_CUSTOM_WHITEPOINT){
    CMLVec3 wpyxy;
    cmlCpy3(wpyxy, cmlGetWhitePointYxy(cm));
    wpyxy[0] = 1.f;
    cmlSetReferenceWhitePointYxy(cm, wpyxy);
  }else{
    cmlSetIlluminationType(cm, (CMLIlluminationType)index);
  }
  
  cpUpdateMachine();

  return NA_TRUE;
}



NABool cpSetIlluminationTemperature(NAReaction reaction){
  CPMachineIlluminationController* con = (CPMachineIlluminationController*)reaction.controller;
  CMLColorMachine* cm = cpGetCurrentColorMachine();

  float temperature = 0.f;
  if(reaction.uiElement == con->illuminationTemperatureTextField){
    temperature = (float)naGetTextFieldDouble(con->illuminationTemperatureTextField);
  }else if(reaction.uiElement == con->illuminationTemperatureSlider){
    double sliderValue = naGetSliderValue(con->illuminationTemperatureSlider);
    temperature = (sliderValue == 1.f)
      ? CML_INFINITY
      : (2000.f + 6000.f * (-logf(1.f - (float)sliderValue)));
  }
  cmlSetIlluminationTemperature(cm, temperature);
  
  cpUpdateMachine();

  return NA_TRUE;
}



NABool cpSetWhitePoint(NAReaction reaction){
  CPMachineIlluminationController* con = (CPMachineIlluminationController*)reaction.controller;
  CMLColorMachine* cm = cpGetCurrentColorMachine();

  CMLVec3 whitePointYxy;
  cmlCpy3(whitePointYxy, cmlGetWhitePointYxy(cm));
  
  if(reaction.uiElement == con->setWhitePointButton){
    CMLColorConverter converter = cmlGetColorConverter(CML_COLOR_Yxy, cpGetCurrentColorType());
    converter(cm, whitePointYxy, cpGetCurrentColorData(), 1);
  }else if(reaction.uiElement == con->whitePointYTextField){
    whitePointYxy[0] = (float)naGetTextFieldDouble(con->whitePointYTextField);
  }else if(reaction.uiElement == con->whitePointxTextField){
    whitePointYxy[1] = (float)naGetTextFieldDouble(con->whitePointxTextField);
  }else if(reaction.uiElement == con->whitePointyTextField){
    whitePointYxy[2] = (float)naGetTextFieldDouble(con->whitePointyTextField);
  }
  cmlSetReferenceWhitePointYxy(cm, whitePointYxy);
  
  cpUpdateMachine();

  return NA_TRUE;
}



CPMachineIlluminationController* cpAllocMachineIlluminationController(void){
  CPMachineIlluminationController* con = naAlloc(CPMachineIlluminationController);

  con->space = naNewSpace(naMakeSize(1, 1));
  naSetSpaceAlternateBackground(con->space, NA_TRUE);

  con->illuminationTitleLabel = naNewLabel(cpTranslate(CPIlluminationTitle), machineLabelWidth);
  con->illuminationPopupButton = naNewPopupButton(200);
  for(size_t i = 0; i < CML_ILLUMINATION_COUNT; ++i){
    CMLIlluminationType illuminationType = (CMLIlluminationType)i;
    if(illuminationType == CML_ILLUMINATION_CUSTOM_SPECTRUM) {continue;}
    NAMenuItem* item = naNewMenuItem(cmlGetIlluminationTypeString(illuminationType));
    naAddPopupButtonMenuItem(con->illuminationPopupButton, item, NA_NULL);
    naAddUIReaction(item, NA_UI_COMMAND_PRESSED, cmSelectIllumination, con);
  }
  con->illuminationTemperatureTitleLabel = naNewLabel(cpTranslate(CPIlluminationTemperature), machineLabelWidth);
  con->illuminationTemperatureTextField = cpNewValueTextField(cpSetIlluminationTemperature, con);
  con->illuminationKelvinLabel = naNewLabel(cpTranslate(CPIlluminationKelvin), 20);
  con->illuminationTemperatureSlider = naNewSlider(100);
  naAddUIReaction(con->illuminationTemperatureSlider, NA_UI_COMMAND_EDITED, cpSetIlluminationTemperature, con);
  con->whitePointTitleLabel = naNewLabel(cpTranslate(CPIlluminationWhitePoint), machineLabelWidth - setButtonWidth + marginH);

  con->setWhitePointButton = naNewTextPushButton(cpTranslate(CPSetButton), setButtonWidth);
  naAddUIReaction(con->setWhitePointButton, NA_UI_COMMAND_PRESSED, cpSetWhitePoint, con);
  con->whitePointYTextField = cpNewValueTextField(cpSetWhitePoint, con);
  con->whitePointxTextField = cpNewValueTextField(cpSetWhitePoint, con);
  con->whitePointyTextField = cpNewValueTextField(cpSetWhitePoint, con);

  // layout
  cpBeginUILayout(con->space, spaceBezel);
  cpAddUIRow(con->illuminationTitleLabel, uiElemHeight);
  cpAddUICol(con->illuminationPopupButton, marginH);
  cpAddUIRow(con->illuminationTemperatureTitleLabel, uiElemHeight);
  cpAddUICol(con->illuminationTemperatureTextField, marginH);
  cpAddUICol(con->illuminationKelvinLabel, 0);
  cpAddUICol(con->illuminationTemperatureSlider, marginH);
  cpAddUIRow(con->whitePointTitleLabel, uiElemHeight);
  cpAddUICol(con->setWhitePointButton, 0);
  cpAddUICol(con->whitePointYTextField, 0);
  cpAddUICol(con->whitePointxTextField, 0);
  cpAddUICol(con->whitePointyTextField, 0);
  cpEndUILayout();

  return con;
}



void cpDeallocMachineIlluminationController(CPMachineIlluminationController* con){
  naFree(con);
}



NASpace* cpGetMachineIlluminationControllerUIElement(CPMachineIlluminationController* con){
  return con->space;
}



void cpUpdateMachineIlluminationController(CPMachineIlluminationController* con){
  CMLColorMachine* cm = cpGetCurrentColorMachine();

  CMLIlluminationType illuminationType = cmlGetIlluminationType(cm);
  double temperature = cmlGetIlluminationTemperature(cm);
  if(temperature == 0.f){
    CMLVec3 whitePointYuv = {0.f, 0.f, 0.f};
    cmlYupvpToYuv(cm, whitePointYuv, cmlGetWhitePointYupvp(cm), 1);
    temperature = cmlGetCorrelatedColorTemperature(whitePointYuv);
  }
  double temperatureSliderValue = (temperature == CML_INFINITY)
    ? 1.f
    : 1.f - naExp(-((temperature - 2000.f) / 6000.f));
  NABool temperatureActive = (illuminationType == CML_ILLUMINATION_BLACKBODY || illuminationType == CML_ILLUMINATION_D_ILLUMINANT);
  NABool whitePointActive = (illuminationType == CML_ILLUMINATION_CUSTOM_WHITEPOINT);
  const float* whitePointYxy = cmlGetWhitePointYxy(cm);
  
  naSetPopupButtonIndexSelected(con->illuminationPopupButton, illuminationType);
  naSetTextFieldText(
    con->illuminationTemperatureTextField,
    naAllocSprintf(NA_TRUE, "%5.01f", temperature));
  naSetSliderValue(con->illuminationTemperatureSlider, temperatureSliderValue);
  naSetTextFieldEnabled(con->illuminationTemperatureTextField, temperatureActive);
  naSetLabelEnabled(con->illuminationKelvinLabel, temperatureActive);
  naSetSliderEnabled(con->illuminationTemperatureSlider, temperatureActive);
  naSetTextFieldText(
    con->whitePointYTextField,
    naAllocSprintf(NA_TRUE, "%1.01f", whitePointYxy[0]));
  naSetTextFieldText(
    con->whitePointxTextField,
    naAllocSprintf(NA_TRUE, "%1.05f", whitePointYxy[1]));
  naSetTextFieldText(
    con->whitePointyTextField,
    naAllocSprintf(NA_TRUE, "%1.05f", whitePointYxy[2]));
  naSetTextFieldEnabled(con->whitePointYTextField, NA_FALSE);
  naSetTextFieldEnabled(con->whitePointxTextField, whitePointActive);
  naSetTextFieldEnabled(con->whitePointyTextField, whitePointActive);
}
