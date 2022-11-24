
#include "CMMachineRGBController.h"

#include "CMMachineObserverController.h"
#include "CMGammaDisplayController.h"

#include "NAApp.h"
#include "CMDesign.h"


struct CMMachineRGBController{
  NASpace* space;

  NALabel* rgbColorSpaceLabel;
  NAPopupButton* rgbColorSpacePopupButton;

  NALabel* redPointTitleLabel;
  NATextField* redPointYTextField;
  NATextField* redPointxTextField;
  NATextField* redPointyTextField;
  NALabel* greenPointTitleLabel;
  NATextField* greenPointYTextField;
  NATextField* greenPointxTextField;
  NATextField* greenPointyTextField;
  NALabel* bluePointTitleLabel;
  NATextField* bluePointYTextField;
  NATextField* bluePointxTextField;
  NATextField* bluePointyTextField;

  NALabel* rgbResponseTitleLabel;
  NAPopupButton* rgbResponseChannelsPopupButton;
  NAPopupButton* rgbResponsePopupButton;

  NALabel* responseLinearTitleLabel;
  NATextField* responseLinearTextField;
  NASlider* responseLinearSlider;
  NALabel* responseSplitTitleLabel;
  NATextField* responseSplitTextField;
  NASlider* responseSplitSlider;
  NALabel* responseGammaTitleLabel;
  NATextField* responseGammaTextField;
  NASlider* responseGammaSlider;
  NALabel* responseOffsetTitleLabel;
  NATextField* responseOffsetTextField;
  NASlider* responseOffsetSlider;
  
  CMGammaDisplayController* gammaDisplayController;
};



NABool cmSelectRGBColorSpace(NAReaction reaction){
  CMMachineRGBController* con = (CMMachineRGBController*)reaction.controller;
  CMLColorMachine* cm = cmGetCurrentColorMachine();

  size_t index = naGetPopupButtonItemIndex(con->rgbColorSpacePopupButton, reaction.uiElement);
  CMLRGBColorSpaceType rgbColorSpaceType = (CMLRGBColorSpaceType)index;
  cmlSetRGBColorSpaceType(cm, rgbColorSpaceType);
  
  cmUpdateMachine();

  return NA_TRUE;
}



NABool cmSetRGBYxy(NAReaction reaction){
  CMMachineRGBController* con = (CMMachineRGBController*)reaction.controller;
  CMLColorMachine* cm = cmGetCurrentColorMachine();

  CMLVec3 primaries[3];
  cmlGetRGBPrimariesYxy(cm, primaries);

  if(reaction.uiElement == con->redPointxTextField){
    primaries[0][1] = naGetTextFieldDouble(con->redPointxTextField);
  }else if(reaction.uiElement == con->redPointyTextField){
    primaries[0][2] = naGetTextFieldDouble(con->redPointyTextField);
  }else if(reaction.uiElement == con->greenPointxTextField){
    primaries[1][1] = naGetTextFieldDouble(con->greenPointxTextField);
  }else if(reaction.uiElement == con->greenPointyTextField){
    primaries[1][2] = naGetTextFieldDouble(con->greenPointyTextField);
  }else if(reaction.uiElement == con->bluePointxTextField){
    primaries[2][1] = naGetTextFieldDouble(con->bluePointxTextField);
  }else if(reaction.uiElement == con->bluePointyTextField){
    primaries[2][2] = naGetTextFieldDouble(con->bluePointyTextField);
  }
  cmlSetRGBPrimariesYxy(cm, primaries);
  
  cmUpdateMachine();

  return NA_TRUE;
}



NABool cmSelectRGBResponse(NAReaction reaction){
  // CML_RESPONSE_UNDEFINED must be overjumped

//  CMMachineRGBController* con = (CMMachineRGBController*)reaction.controller;
//  CMLColorMachine* cm = cmGetCurrentColorMachine();
//
//  size_t index = naGetPopupButtonItemIndex(con->rgbColorSpacePopupButton, reaction.uiElement);
//  CMLResponseCurveType rgbResponse = (CMLResponseCurveType)index;
//  cmlSetResponseRGB(cm, rgbResponse);
//  
//  cmUpdateMachine();

  return NA_TRUE;
}



NABool cmSetResponseValue(NAReaction reaction){
//  CMMachineRGBController* con = (CMMachineRGBController*)reaction.controller;
//  CMLColorMachine* cm = cmGetCurrentColorMachine();
//
//  size_t index = naGetPopupButtonItemIndex(con->rgbColorSpacePopupButton, reaction.uiElement);
//  CMLResponseCurveType rgbResponse = (CMLResponseCurveType)index;
//  cmlSetResponseRGB(cm, rgbResponse);
//  
//  cmUpdateMachine();

  return NA_TRUE;
}



CMMachineRGBController* cmAllocMachineRGBController(void){
  CMMachineRGBController* con = naAlloc(CMMachineRGBController);

  con->space = naNewSpace(naMakeSize(1, 1));
  naSetSpaceAlternateBackground(con->space, NA_FALSE);

  con->rgbColorSpaceLabel = naNewLabel("RGB Colorspace", machineLabelWidth);
  con->rgbColorSpacePopupButton = naNewPopupButton(200);
  for(size_t i = 0; i < CML_RGB_COUNT; ++i){
    CMLRGBColorSpaceType rgbColorSpaceType = (CMLRGBColorSpaceType)i;
    NAMenuItem* item = naNewMenuItem(cmlGetRGBColorSpaceTypeString(rgbColorSpaceType));
    naAddPopupButtonMenuItem(con->rgbColorSpacePopupButton, item, NA_NULL);
    naAddUIReaction(item, NA_UI_COMMAND_PRESSED, cmSelectRGBColorSpace, con);
  }

  con->redPointTitleLabel = naNewLabel("Red", machineLabelWidth);
  con->redPointYTextField = cmNewValueTextField(cmSetRGBYxy, con);
  con->redPointxTextField = cmNewValueTextField(cmSetRGBYxy, con);
  con->redPointyTextField = cmNewValueTextField(cmSetRGBYxy, con);
  con->greenPointTitleLabel = naNewLabel("Green", machineLabelWidth);
  con->greenPointYTextField = cmNewValueTextField(cmSetRGBYxy, con);
  con->greenPointxTextField = cmNewValueTextField(cmSetRGBYxy, con);
  con->greenPointyTextField = cmNewValueTextField(cmSetRGBYxy, con);
  con->bluePointTitleLabel = naNewLabel("Blue", machineLabelWidth);
  con->bluePointYTextField = cmNewValueTextField(cmSetRGBYxy, con);
  con->bluePointxTextField = cmNewValueTextField(cmSetRGBYxy, con);
  con->bluePointyTextField = cmNewValueTextField(cmSetRGBYxy, con);

  naSetTextFieldEnabled(con->redPointYTextField, NA_FALSE);
  naSetTextFieldEnabled(con->greenPointYTextField, NA_FALSE);
  naSetTextFieldEnabled(con->bluePointYTextField, NA_FALSE);

  con->rgbResponseTitleLabel = naNewLabel("Response", machineLabelWidth);
  con->rgbResponseChannelsPopupButton = naNewPopupButton(80);
  for(size_t i = 0; i < CML_RGB_COUNT; ++i){
//    CMLRGBColorSpaceType rgbColorSpaceType = (CMLRGBColorSpaceType)i;
//    NAMenuItem* item = naNewMenuItem(cmlGetRGBColorSpaceTypeString(rgbColorSpaceType));
//    naAddPopupButtonMenuItem(con->rgbColorSpacePopupButton, item, NA_NULL);
//    naAddUIReaction(item, NA_UI_COMMAND_PRESSED, cmSelectRGBColorSpace, con);
  }
  con->rgbResponsePopupButton = naNewPopupButton(100);
  for(size_t i = 0; i < CML_RESPONSE_COUNT; ++i){
    CMLResponseCurveType responseCurveType = (CMLResponseCurveType)i;
    if(responseCurveType == CML_RESPONSE_UNDEFINED){continue;}
    NAMenuItem* item = naNewMenuItem(cmlGetRGBResponseTypeString(responseCurveType));
    naAddPopupButtonMenuItem(con->rgbResponsePopupButton, item, NA_NULL);
    naAddUIReaction(item, NA_UI_COMMAND_PRESSED, cmSelectRGBResponse, con);
  }

  con->responseLinearTitleLabel = naNewLabel("Linear", 60);
  con->responseLinearTextField = cmNewValueTextField(cmSetResponseValue, con);
  con->responseLinearSlider = naNewSlider(60);
  con->responseSplitTitleLabel = naNewLabel("Split", 60);
  con->responseSplitTextField = cmNewValueTextField(cmSetResponseValue, con);
  con->responseSplitSlider = naNewSlider(60);
  con->responseGammaTitleLabel = naNewLabel("Gamma", 60);
  con->responseGammaTextField = cmNewValueTextField(cmSetResponseValue, con);
  con->responseGammaSlider = naNewSlider(60);
  con->responseOffsetTitleLabel = naNewLabel("Offset", 60);
  con->responseOffsetTextField = cmNewValueTextField(cmSetResponseValue, con);
  con->responseOffsetSlider = naNewSlider(60);

  con->gammaDisplayController = cmAllocGammaDisplayController();

  // layout
  cmBeginUILayout(con->space, spaceBezel);
  cmAddUIRow(con->rgbColorSpaceLabel, uiElemHeight);
  cmAddUICol(con->rgbColorSpacePopupButton, marginH);

  cmAddUIRow(con->redPointTitleLabel, uiElemHeight);
  cmAddUICol(con->redPointYTextField, marginH);
  cmAddUICol(con->redPointxTextField, 0);
  cmAddUICol(con->redPointyTextField, 0);
  cmAddUIRow(con->greenPointTitleLabel, uiElemHeight);
  cmAddUICol(con->greenPointYTextField, marginH);
  cmAddUICol(con->greenPointxTextField, 0);
  cmAddUICol(con->greenPointyTextField, 0);
  cmAddUIRow(con->bluePointTitleLabel, uiElemHeight);
  cmAddUICol(con->bluePointYTextField, marginH);
  cmAddUICol(con->bluePointxTextField, 0);
  cmAddUICol(con->bluePointyTextField, 0);

  cmAddUIRow(con->rgbResponseTitleLabel, uiElemHeight);
  cmAddUICol(con->rgbResponseChannelsPopupButton, marginH);
  cmAddUICol(con->rgbResponsePopupButton, marginH);

  cmAddUIRow(con->responseLinearTitleLabel, uiElemHeight);
  cmAddUICol(con->responseLinearTextField, marginH);
  cmAddUICol(con->responseLinearSlider, marginH);
  cmAddUIRow(con->responseSplitTitleLabel, uiElemHeight);
  cmAddUICol(con->responseSplitTextField, marginH);
  cmAddUICol(con->responseSplitSlider, marginH);
  cmAddUIRow(con->responseGammaTitleLabel, uiElemHeight);
  cmAddUICol(con->responseGammaTextField, marginH);
  cmAddUICol(con->responseGammaSlider, marginH);
  cmAddUIRow(con->responseOffsetTitleLabel, uiElemHeight);
  cmAddUICol(con->responseOffsetTextField, marginH);
  cmAddUICol(con->responseOffsetSlider, marginH);
  cmEndUILayout();

  naAddSpaceChild(
    con->space,
    cmGetGammaDisplayControllerUIElement(con->gammaDisplayController),
    naMakePos(250, 10));

  return con;
}



void cmDeallocMachineRGBController(CMMachineRGBController* con){
  naFree(con);
}



NASpace* cmGetMachineRGBControllerUIElement(CMMachineRGBController* con){
  return con->space;
}



void cmUpdateMachineRGBController(CMMachineRGBController* con){
  CMLColorMachine* cm = cmGetCurrentColorMachine();

  CMLRGBColorSpaceType rgbColorSpaceType = cmlGetRGBColorSpaceType(cm);
  naSetPopupButtonIndexSelected(con->rgbColorSpacePopupButton, rgbColorSpaceType);
  
  NABool isCustomRGB = rgbColorSpaceType == CML_RGB_CUSTOM;
  CMLVec3 primaries[3];
  cmlGetRGBPrimariesYxy(cm, primaries);
  
  naSetTextFieldText(
    con->redPointYTextField,
    naAllocSprintf(NA_TRUE, "%1.05f", primaries[0][0]));
  naSetTextFieldText(
    con->redPointxTextField,
    naAllocSprintf(NA_TRUE, "%1.05f", primaries[0][1]));
  naSetTextFieldText(
    con->redPointyTextField,
    naAllocSprintf(NA_TRUE, "%1.05f", primaries[0][2]));
  naSetTextFieldText(
    con->greenPointYTextField,
    naAllocSprintf(NA_TRUE, "%1.05f", primaries[1][0]));
  naSetTextFieldText(
    con->greenPointxTextField,
    naAllocSprintf(NA_TRUE, "%1.05f", primaries[1][1]));
  naSetTextFieldText(
    con->greenPointyTextField,
    naAllocSprintf(NA_TRUE, "%1.05f", primaries[1][2]));
  naSetTextFieldText(
    con->bluePointYTextField,
    naAllocSprintf(NA_TRUE, "%1.05f", primaries[2][0]));
  naSetTextFieldText(
    con->bluePointxTextField,
    naAllocSprintf(NA_TRUE, "%1.05f", primaries[2][1]));
  naSetTextFieldText(
    con->bluePointyTextField,
    naAllocSprintf(NA_TRUE, "%1.05f", primaries[2][2]));
  
  naSetTextFieldEnabled(con->redPointxTextField, isCustomRGB);
  naSetTextFieldEnabled(con->redPointyTextField, isCustomRGB);
  naSetTextFieldEnabled(con->greenPointxTextField, isCustomRGB);
  naSetTextFieldEnabled(con->greenPointyTextField, isCustomRGB);
  naSetTextFieldEnabled(con->bluePointxTextField, isCustomRGB);
  naSetTextFieldEnabled(con->bluePointyTextField, isCustomRGB);

  CMLResponseCurveType rgbResponseTypes[3];
  cmlGetRGBResponseTypes(cm, rgbResponseTypes);
  naSetPopupButtonIndexSelected(con->rgbResponsePopupButton, rgbResponseTypes[0]);
}
