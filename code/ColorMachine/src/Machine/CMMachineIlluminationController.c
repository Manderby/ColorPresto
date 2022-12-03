
#include "CMMachineIlluminationController.h"

#include "CMColorMachineApplication.h"
#include "CMMachineObserverController.h"

#include "NAApp.h"
#include "CMDesign.h"
#include "CMTranslations.h"


struct CMMachineIlluminationController{
  NASpace* space;

  NALabel* illuminationTitleLabel;
  NAPopupButton* illuminationPopupButton;
  NALabel* illuminationTemperatureTitleLabel;
  NATextField* illuminationTemperatureTextField;
  NALabel* illuminationKelvinLabel;
  NASlider* illuminationTemperatureSlider;
  NALabel* whitePointTitleLabel;
  NATextField* whitePointYTextField;
  NATextField* whitePointxTextField;
  NATextField* whitePointyTextField;
};



NABool cmSelectIllumination(NAReaction reaction){
  CMMachineIlluminationController* con = (CMMachineIlluminationController*)reaction.controller;
  CMLColorMachine* cm = cmGetCurrentColorMachine();

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
  
  cmUpdateMachine();

  return NA_TRUE;
}



NABool cmSetIlluminationTemperature(NAReaction reaction){
  CMMachineIlluminationController* con = (CMMachineIlluminationController*)reaction.controller;
  CMLColorMachine* cm = cmGetCurrentColorMachine();

  double temperature = 0.;
  if(reaction.uiElement == con->illuminationTemperatureTextField){
    temperature = naGetTextFieldDouble(con->illuminationTemperatureTextField);
  }else if(reaction.uiElement == con->illuminationTemperatureSlider){
    double sliderValue = naGetSliderValue(con->illuminationTemperatureSlider);
    temperature = (sliderValue == 1.f)
      ? CML_INFINITY
      : (2000.f + 6000.f * (-logf(1.f - sliderValue)));
  }
  cmlSetIlluminationTemperature(cm, temperature);
  
  cmUpdateMachine();

  return NA_TRUE;
}



NABool cmSetWhitePoint(NAReaction reaction){
  CMMachineIlluminationController* con = (CMMachineIlluminationController*)reaction.controller;
  CMLColorMachine* cm = cmGetCurrentColorMachine();

  CMLVec3 whitePointYxy;
  cmlCpy3(whitePointYxy, cmlGetWhitePointYxy(cm));
  
  if(reaction.uiElement == con->whitePointYTextField){
    whitePointYxy[0] = naGetTextFieldDouble(con->whitePointYTextField);
  }else if(reaction.uiElement == con->whitePointxTextField){
    whitePointYxy[1] = naGetTextFieldDouble(con->whitePointxTextField);
  }else if(reaction.uiElement == con->whitePointyTextField){
    whitePointYxy[2] = naGetTextFieldDouble(con->whitePointyTextField);
  }
  cmlSetReferenceWhitePointYxy(cm, whitePointYxy);
  
  cmUpdateMachine();

  return NA_TRUE;
}



CMMachineIlluminationController* cmAllocMachineIlluminationController(void){
  CMMachineIlluminationController* con = naAlloc(CMMachineIlluminationController);

  con->space = naNewSpace(naMakeSize(1, 1));
  naSetSpaceAlternateBackground(con->space, NA_TRUE);

  con->illuminationTitleLabel = naNewLabel(cmTranslate(CMIlluminationTitle), machineLabelWidth);
  con->illuminationPopupButton = naNewPopupButton(200);
  for(size_t i = 0; i < CML_ILLUMINATION_COUNT; ++i){
    CMLIlluminationType illuminationType = (CMLIlluminationType)i;
    if(illuminationType == CML_ILLUMINATION_CUSTOM_SPECTRUM) {continue;}
    NAMenuItem* item = naNewMenuItem(cmlGetIlluminationTypeString(illuminationType));
    naAddPopupButtonMenuItem(con->illuminationPopupButton, item, NA_NULL);
    naAddUIReaction(item, NA_UI_COMMAND_PRESSED, cmSelectIllumination, con);
  }
  con->illuminationTemperatureTitleLabel = naNewLabel(cmTranslate(CMIlluminationTemperature), machineLabelWidth);
  con->illuminationTemperatureTextField = cmNewValueTextField(cmSetIlluminationTemperature, con);
  con->illuminationKelvinLabel = naNewLabel(cmTranslate(CMIlluminationKelvin), 20);
  con->illuminationTemperatureSlider = naNewSlider(100);
  naAddUIReaction(con->illuminationTemperatureSlider, NA_UI_COMMAND_EDITED, cmSetIlluminationTemperature, con);
  con->whitePointTitleLabel = naNewLabel(cmTranslate(CMIlluminationWhitePoint), machineLabelWidth);
  con->whitePointYTextField = cmNewValueTextField(cmSetWhitePoint, con);
  con->whitePointxTextField = cmNewValueTextField(cmSetWhitePoint, con);
  con->whitePointyTextField = cmNewValueTextField(cmSetWhitePoint, con);

  // layout
  cmBeginUILayout(con->space, spaceBezel);
  cmAddUIRow(con->illuminationTitleLabel, uiElemHeight);
  cmAddUICol(con->illuminationPopupButton, marginH);
  cmAddUIRow(con->illuminationTemperatureTitleLabel, uiElemHeight);
  cmAddUICol(con->illuminationTemperatureTextField, marginH);
  cmAddUICol(con->illuminationKelvinLabel, 0);
  cmAddUICol(con->illuminationTemperatureSlider, marginH);
  cmAddUIRow(con->whitePointTitleLabel, uiElemHeight);
  cmAddUICol(con->whitePointYTextField, marginH);
  cmAddUICol(con->whitePointxTextField, 0);
  cmAddUICol(con->whitePointyTextField, 0);
  cmEndUILayout();

  return con;
}



void cmDeallocMachineIlluminationController(CMMachineIlluminationController* con){
  naFree(con);
}



NASpace* cmGetMachineIlluminationControllerUIElement(CMMachineIlluminationController* con){
  return con->space;
}



void cmUpdateMachineIlluminationController(CMMachineIlluminationController* con){
  CMLColorMachine* cm = cmGetCurrentColorMachine();

  CMLIlluminationType illuminationType = cmlGetIlluminationType(cm);
  double temperature = cmlGetIlluminationTemperature(cm);
  if(temperature == 0.f){
    CMLVec3 whitePointYuv;
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
