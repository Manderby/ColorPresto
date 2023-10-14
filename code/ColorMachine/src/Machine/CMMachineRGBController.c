
#include "CMMachineRGBController.h"

#include "../CMColorMachineApplication.h"
#include "CMMachineObserverController.h"
#include "../ColorControllers/Displays/CMGammaDisplayController.h"
#include "../CMDesign.h"
#include "../CMTranslations.h"

#include "NAApp.h"


struct CMMachineRGBController{
  NASpace* space;

  NALabel* rgbColorSpaceLabel;
  NAPopupButton* rgbColorSpacePopupButton;

  NALabel* redPointTitleLabel;
  NAButton* setPrimaryRButton;
  NATextField* redPointYTextField;
  NATextField* redPointxTextField;
  NATextField* redPointyTextField;
  NALabel* greenPointTitleLabel;
  NAButton* setPrimaryGButton;
  NATextField* greenPointYTextField;
  NATextField* greenPointxTextField;
  NATextField* greenPointyTextField;
  NALabel* bluePointTitleLabel;
  NAButton* setPrimaryBButton;
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

  size_t lastSelectedChannel;
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

  if(reaction.uiElement == con->setPrimaryRButton){
    CMLColorConverter converter = cmlGetColorConverter(CML_COLOR_Yxy, cmGetCurrentColorType());
    converter(cm, primaries[0], cmGetCurrentColorData(), 1);
  }else if(reaction.uiElement == con->redPointxTextField){
    primaries[0][1] = (float)naGetTextFieldDouble(con->redPointxTextField);
  }else if(reaction.uiElement == con->redPointyTextField){
    primaries[0][2] = (float)naGetTextFieldDouble(con->redPointyTextField);
  }else if(reaction.uiElement == con->setPrimaryGButton){
    CMLColorConverter converter = cmlGetColorConverter(CML_COLOR_Yxy, cmGetCurrentColorType());
    converter(cm, primaries[1], cmGetCurrentColorData(), 1);
  }else if(reaction.uiElement == con->greenPointxTextField){
    primaries[1][1] = (float)naGetTextFieldDouble(con->greenPointxTextField);
  }else if(reaction.uiElement == con->greenPointyTextField){
    primaries[1][2] = (float)naGetTextFieldDouble(con->greenPointyTextField);
  }else if(reaction.uiElement == con->setPrimaryBButton){
    CMLColorConverter converter = cmlGetColorConverter(CML_COLOR_Yxy, cmGetCurrentColorType());
    converter(cm, primaries[2], cmGetCurrentColorData(), 1);
  }else if(reaction.uiElement == con->bluePointxTextField){
    primaries[2][1] = (float)naGetTextFieldDouble(con->bluePointxTextField);
  }else if(reaction.uiElement == con->bluePointyTextField){
    primaries[2][2] = (float)naGetTextFieldDouble(con->bluePointyTextField);
  }
  cmlSetRGBPrimariesYxy(cm, primaries);
  
  cmUpdateMachine();

  return NA_TRUE;
}



NABool cmSelectRGBChannel(NAReaction reaction){
  CMMachineRGBController* con = (CMMachineRGBController*)reaction.controller;
  CMLColorMachine* cm = cmGetCurrentColorMachine();

  size_t newSelectedChannel = naGetPopupButtonItemIndex(con->rgbResponseChannelsPopupButton, reaction.uiElement);

  if(con->lastSelectedChannel > 0 && newSelectedChannel == 0){
    GammaLinearInputParameters params[3];
    cmlGetCustomGammaLinearParametersRGB(cm, params);
    size_t prevIndex = 0;
    
    CMLResponseCurve* newResponse = cmlAllocResponseCurve();
    switch(con->lastSelectedChannel){
    case 0:
      cmlInitResponseCurveWithCopy(newResponse, cmlGetResponseR(cm));
      prevIndex = 0;
      break;
    case 1:
      cmlInitResponseCurveWithCopy(newResponse, cmlGetResponseR(cm));
      prevIndex = 0;
      break;
    case 2:
      cmlInitResponseCurveWithCopy(newResponse, cmlGetResponseG(cm));
      prevIndex = 1;
      break;
    case 3:
      cmlInitResponseCurveWithCopy(newResponse, cmlGetResponseB(cm));
      prevIndex = 2;
      break;
    }
    cmlSetResponseRGB(cm, newResponse);
    params[0] = params[prevIndex];
    params[1] = params[prevIndex];
    params[2] = params[prevIndex];
    cmlSetCustomGammaLinearParametersRGB(cm, params);
  }
  con->lastSelectedChannel = newSelectedChannel;
    
  cmUpdateMachine();

  return NA_TRUE;
}



NABool cmSelectRGBResponse(NAReaction reaction){
  CMMachineRGBController* con = (CMMachineRGBController*)reaction.controller;
  CMLColorMachine* cm = cmGetCurrentColorMachine();

  size_t index = naGetPopupButtonItemIndex(con->rgbResponsePopupButton, reaction.uiElement);
  // CML_RESPONSE_UNDEFINED must be overjumped
  CMLResponseCurveType rgbResponse = (CMLResponseCurveType)(index + 1);

  CMLResponseCurve* newResponse = cmlAllocResponseCurve();
  if(rgbResponse == CML_RESPONSE_CUSTOM_GAMMA){
    const GammaLinearInputParameters* inputParams = cmlGetCustomGammaLinearParametersR(cm);
    cmlInitResponseCurveWithCustomGamma(newResponse, inputParams->gamma);
  }else if(rgbResponse == CML_RESPONSE_CUSTOM_GAMMA_LINEAR){
    const GammaLinearInputParameters* inputParams = cmlGetCustomGammaLinearParametersR(cm);
    cmlInitResponseCurveWithCustomGammaLinear(newResponse, inputParams->gamma, inputParams->offset, inputParams->linScale, inputParams->split);
  }else{
    cmlInitResponseCurveWithType(newResponse, rgbResponse);
  }

  switch(con->lastSelectedChannel){
  case 0: cmlSetResponseRGB(cm, newResponse); break;
  case 1: cmlSetResponseR(cm, newResponse); break;
  case 2: cmlSetResponseG(cm, newResponse); break;
  case 3: cmlSetResponseB(cm, newResponse); break;
  }

  cmlClearResponseCurve(newResponse);
  free(newResponse);
  
  cmUpdateMachine();

  return NA_TRUE;
}



NABool cmSetResponseValue(NAReaction reaction){
  CMMachineRGBController* con = (CMMachineRGBController*)reaction.controller;
  CMLColorMachine* cm = cmGetCurrentColorMachine();

  size_t colorIndex = con->lastSelectedChannel;
  if(colorIndex > 0){ colorIndex--; }

  CMLResponseCurveType rgbResponseTypes[3];
  cmlGetRGBResponseTypes(cm, rgbResponseTypes);

  GammaLinearInputParameters params[3];
  cmlGetCustomGammaLinearParametersRGB(cm, params);
  if(reaction.uiElement == con->responseLinearTextField){
    params[colorIndex].linScale = (float)naGetTextFieldDouble(con->responseLinearTextField);
  }else if(reaction.uiElement == con->responseLinearSlider){
    params[colorIndex].linScale = (float)naGetSliderValue(con->responseLinearSlider);
  }else if(reaction.uiElement == con->responseSplitTextField){
    params[colorIndex].split = (float)naGetTextFieldDouble(con->responseSplitTextField);
  }else if(reaction.uiElement == con->responseSplitSlider){
    params[colorIndex].split = (float)naGetSliderValue(con->responseSplitSlider);
  }else if(reaction.uiElement == con->responseGammaTextField){
    params[colorIndex].gamma = (float)naGetTextFieldDouble(con->responseGammaTextField);
  }else if(reaction.uiElement == con->responseGammaSlider){
    params[colorIndex].gamma = (float)naGetSliderValue(con->responseGammaSlider);
  }else if(reaction.uiElement == con->responseOffsetTextField){
    params[colorIndex].offset = (float)naGetTextFieldDouble(con->responseOffsetTextField);
  }else if(reaction.uiElement == con->responseOffsetSlider){
    params[colorIndex].offset = (float)naGetSliderValue(con->responseOffsetSlider);
  }

  if(con->lastSelectedChannel == 0){
    params[1] = params[0];
    params[2] = params[0];
  }

  cmlSetCustomGammaLinearParametersRGB(cm, params);

  CMLResponseCurve* newResponseR = cmlAllocResponseCurve();
  CMLResponseCurve* newResponseG = cmlAllocResponseCurve();
  CMLResponseCurve* newResponseB = cmlAllocResponseCurve();
  if(rgbResponseTypes[0] == CML_RESPONSE_CUSTOM_GAMMA_LINEAR){
    cmlInitResponseCurveWithCustomGammaLinear(newResponseR, params[0].gamma, params[0].offset, params[0].linScale, params[0].split);
    cmlInitResponseCurveWithCustomGammaLinear(newResponseG, params[1].gamma, params[1].offset, params[1].linScale, params[1].split);
    cmlInitResponseCurveWithCustomGammaLinear(newResponseB, params[2].gamma, params[2].offset, params[2].linScale, params[2].split);
  }else{
    cmlInitResponseCurveWithCustomGamma(newResponseR, params[0].gamma);
    cmlInitResponseCurveWithCustomGamma(newResponseG, params[1].gamma);
    cmlInitResponseCurveWithCustomGamma(newResponseB, params[2].gamma);
  }
  cmlSetResponseR(cm, newResponseR);
  cmlSetResponseG(cm, newResponseG);
  cmlSetResponseB(cm, newResponseB);
  cmlClearResponseCurve(newResponseR);
  cmlClearResponseCurve(newResponseG);
  cmlClearResponseCurve(newResponseB);
  free(newResponseR);
  free(newResponseG);
  free(newResponseB);

  cmUpdateMachine();

  return NA_TRUE;
}



CMMachineRGBController* cmAllocMachineRGBController(void){
  CMMachineRGBController* con = naAlloc(CMMachineRGBController);

  con->space = naNewSpace(naMakeSize(1, 1));
  naSetSpaceAlternateBackground(con->space, NA_FALSE);

  con->rgbColorSpaceLabel = naNewLabel(cmTranslate(CMRGBColorSpaceTitle), machineLabelWidth);
  con->rgbColorSpacePopupButton = naNewPopupButton(200);
  for(size_t i = 0; i < CML_RGB_COUNT; ++i){
    CMLRGBColorSpaceType rgbColorSpaceType = (CMLRGBColorSpaceType)i;
    NAMenuItem* item = naNewMenuItem(cmlGetRGBColorSpaceTypeString(rgbColorSpaceType));
    naAddPopupButtonMenuItem(con->rgbColorSpacePopupButton, item, NA_NULL);
    naAddUIReaction(item, NA_UI_COMMAND_PRESSED, cmSelectRGBColorSpace, con);
  }

  con->redPointTitleLabel = naNewLabel(cmTranslate(CMRGBColorSpaceRed), machineLabelWidth - setButtonWidth + marginH);

  con->setPrimaryRButton = naNewTextPushButton(cmTranslate(CMSetButton), setButtonWidth);
  naAddUIReaction(con->setPrimaryRButton, NA_UI_COMMAND_PRESSED, cmSetRGBYxy, con);
  con->redPointYTextField = cmNewValueTextField(cmSetRGBYxy, con);
  con->redPointxTextField = cmNewValueTextField(cmSetRGBYxy, con);
  con->redPointyTextField = cmNewValueTextField(cmSetRGBYxy, con);
  con->greenPointTitleLabel = naNewLabel(cmTranslate(CMRGBColorSpaceGreen), machineLabelWidth - setButtonWidth + marginH);

  con->setPrimaryGButton = naNewTextPushButton(cmTranslate(CMSetButton), setButtonWidth);
  naAddUIReaction(con->setPrimaryGButton, NA_UI_COMMAND_PRESSED, cmSetRGBYxy, con);
  con->greenPointYTextField = cmNewValueTextField(cmSetRGBYxy, con);
  con->greenPointxTextField = cmNewValueTextField(cmSetRGBYxy, con);
  con->greenPointyTextField = cmNewValueTextField(cmSetRGBYxy, con);
  con->bluePointTitleLabel = naNewLabel(cmTranslate(CMRGBColorSpaceBlue), machineLabelWidth - setButtonWidth + marginH);

  con->setPrimaryBButton = naNewTextPushButton(cmTranslate(CMSetButton), setButtonWidth);
  naAddUIReaction(con->setPrimaryBButton, NA_UI_COMMAND_PRESSED, cmSetRGBYxy, con);
  con->bluePointYTextField = cmNewValueTextField(cmSetRGBYxy, con);
  con->bluePointxTextField = cmNewValueTextField(cmSetRGBYxy, con);
  con->bluePointyTextField = cmNewValueTextField(cmSetRGBYxy, con);

  naSetTextFieldEnabled(con->redPointYTextField, NA_FALSE);
  naSetTextFieldEnabled(con->greenPointYTextField, NA_FALSE);
  naSetTextFieldEnabled(con->bluePointYTextField, NA_FALSE);

  con->rgbResponseTitleLabel = naNewLabel(cmTranslate(CMRGBColorResponse), machineLabelWidth);
  con->rgbResponseChannelsPopupButton = naNewPopupButton(80);
  NAMenuItem* rgbMenuItem = naNewMenuItem(cmTranslate(CMRGBColorChannelRGB));
  naAddPopupButtonMenuItem(con->rgbResponseChannelsPopupButton, rgbMenuItem, NA_NULL);
  naAddUIReaction(rgbMenuItem, NA_UI_COMMAND_PRESSED, cmSelectRGBChannel, con);
  NAMenuItem* rMenuItem = naNewMenuItem(cmTranslate(CMRGBColorChannelR));
  naAddPopupButtonMenuItem(con->rgbResponseChannelsPopupButton, rMenuItem, NA_NULL);
  naAddUIReaction(rMenuItem, NA_UI_COMMAND_PRESSED, cmSelectRGBChannel, con);
  NAMenuItem* gMenuItem = naNewMenuItem(cmTranslate(CMRGBColorChannelG));
  naAddPopupButtonMenuItem(con->rgbResponseChannelsPopupButton, gMenuItem, NA_NULL);
  naAddUIReaction(gMenuItem, NA_UI_COMMAND_PRESSED, cmSelectRGBChannel, con);
  NAMenuItem* bMenuItem = naNewMenuItem(cmTranslate(CMRGBColorChannelB));
  naAddPopupButtonMenuItem(con->rgbResponseChannelsPopupButton, bMenuItem, NA_NULL);
  naAddUIReaction(bMenuItem, NA_UI_COMMAND_PRESSED, cmSelectRGBChannel, con);

  con->rgbResponsePopupButton = naNewPopupButton(100);
  for(size_t i = 0; i < CML_RESPONSE_COUNT; ++i){
    CMLResponseCurveType responseCurveType = (CMLResponseCurveType)i;
    if(responseCurveType == CML_RESPONSE_UNDEFINED){continue;}
    NAMenuItem* item = naNewMenuItem(cmlGetRGBResponseTypeString(responseCurveType));
    naAddPopupButtonMenuItem(con->rgbResponsePopupButton, item, NA_NULL);
    naAddUIReaction(item, NA_UI_COMMAND_PRESSED, cmSelectRGBResponse, con);
  }

  con->responseLinearTitleLabel = naNewLabel(cmTranslate(CMRGBColorChannelLinear), machineLabelWidth);
  con->responseLinearTextField = cmNewValueTextField(cmSetResponseValue, con);
  con->responseLinearSlider = naNewSlider(60);
  naSetSliderRange(con->responseLinearSlider, 1., 10., 0);
  naAddUIReaction(con->responseLinearSlider, NA_UI_COMMAND_EDITED, cmSetResponseValue, con);
  
  con->responseSplitTitleLabel = naNewLabel(cmTranslate(CMRGBColorChannelSplit), machineLabelWidth);
  con->responseSplitTextField = cmNewValueTextField(cmSetResponseValue, con);
  con->responseSplitSlider = naNewSlider(60);
  naSetSliderRange(con->responseSplitSlider, 0., 1., 0);
  naAddUIReaction(con->responseSplitSlider, NA_UI_COMMAND_EDITED, cmSetResponseValue, con);
  
  con->responseGammaTitleLabel = naNewLabel(cmTranslate(CMRGBColorChannelGamma), machineLabelWidth);
  con->responseGammaTextField = cmNewValueTextField(cmSetResponseValue, con);
  con->responseGammaSlider = naNewSlider(60);
  naSetSliderRange(con->responseGammaSlider, 1., 4., 0);
  naAddUIReaction(con->responseGammaSlider, NA_UI_COMMAND_EDITED, cmSetResponseValue, con);
  
  con->responseOffsetTitleLabel = naNewLabel(cmTranslate(CMRGBColorChannelOffset), machineLabelWidth);
  con->responseOffsetTextField = cmNewValueTextField(cmSetResponseValue, con);
  con->responseOffsetSlider = naNewSlider(60);
  naSetSliderRange(con->responseOffsetSlider, 0., 1., 0);
  naAddUIReaction(con->responseOffsetSlider, NA_UI_COMMAND_EDITED, cmSetResponseValue, con);

  con->gammaDisplayController = cmAllocGammaDisplayController();

  // layout
  cmBeginUILayout(con->space, spaceBezel);
  cmAddUIRow(con->rgbColorSpaceLabel, uiElemHeight);
  cmAddUICol(con->rgbColorSpacePopupButton, marginH);

  cmAddUIRow(con->redPointTitleLabel, uiElemHeight);
  cmAddUICol(con->setPrimaryRButton, 0);
  cmAddUICol(con->redPointYTextField, 0);
  cmAddUICol(con->redPointxTextField, 0);
  cmAddUICol(con->redPointyTextField, 0);
  cmAddUIRow(con->greenPointTitleLabel, uiElemHeight);
  cmAddUICol(con->setPrimaryGButton, 0);
  cmAddUICol(con->greenPointYTextField, 0);
  cmAddUICol(con->greenPointxTextField, 0);
  cmAddUICol(con->greenPointyTextField, 0);
  cmAddUIRow(con->bluePointTitleLabel, uiElemHeight);
  cmAddUICol(con->setPrimaryBButton, 0);
  cmAddUICol(con->bluePointYTextField, 0);
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
    naMakePos(300, 37));

  // Initialization

  con->lastSelectedChannel = 0;
  
  return con;
}



void cmDeallocMachineRGBController(CMMachineRGBController* con){
  cmDeallocGammaDisplayController(con->gammaDisplayController);
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

  naSetPopupButtonIndexSelected(con->rgbResponseChannelsPopupButton, con->lastSelectedChannel);
  naSetPopupButtonEnabled(con->rgbResponseChannelsPopupButton, isCustomRGB);
  
  size_t colorIndex = con->lastSelectedChannel;
  if(colorIndex > 0){ colorIndex--; }

  CMLResponseCurveType rgbResponseTypes[3];
  cmlGetRGBResponseTypes(cm, rgbResponseTypes);
  naSetPopupButtonIndexSelected(con->rgbResponsePopupButton, rgbResponseTypes[colorIndex] - 1);
  naSetPopupButtonEnabled(con->rgbResponsePopupButton, isCustomRGB);
  
  NABool customAllEnabled = rgbResponseTypes[colorIndex] == CML_RESPONSE_CUSTOM_GAMMA_LINEAR;
  NABool customGammaEnabled = rgbResponseTypes[colorIndex] == CML_RESPONSE_CUSTOM_GAMMA || customAllEnabled;
  
  GammaLinearInputParameters params[3];
  cmlGetCustomGammaLinearParametersRGB(cm, params);

  float gamma = -1.;
  float offset = -1.;
  float linScale = -1.;
  float split = -1.;

  switch(rgbResponseTypes[colorIndex]){
  case CML_RESPONSE_LINEAR:
    gamma = 1.0f;
    break;
  case CML_RESPONSE_GAMMA_1_8:
    gamma = 1.8f;
    break;
  case CML_RESPONSE_GAMMA_1_9:
    gamma = 1.9f;
    break;
  case CML_RESPONSE_GAMMA_2_0:
    gamma = 2.0f;
    break;
  case CML_RESPONSE_GAMMA_ADOBE_98:
    gamma = 2.f + 51.f / 256.f;
    break;
  case CML_RESPONSE_GAMMA_2_2:
    gamma = 2.2f;
    break;
  case CML_RESPONSE_GAMMA_LINEAR_REC_BT_10BIT:
    gamma = 1.f / 0.45f;
    offset = 0.099f;
    linScale = 4.5f;
    split = 0.018f;
    break;
  case CML_RESPONSE_GAMMA_LINEAR_REC_BT_12BIT:
    gamma = 1.f / 0.45f;
    offset = 0.0993f;
    linScale = 4.5f;
    split = 0.0181f;
    break;
  case CML_RESPONSE_SRGB:
    break;
  case CML_RESPONSE_LSTAR:
    break;
  case CML_RESPONSE_LSTAR_STANDARD:
    break;
  case CML_RESPONSE_CUSTOM_GAMMA: {
    gamma = params[colorIndex].gamma;
    break; }
  case CML_RESPONSE_CUSTOM_GAMMA_LINEAR: {
    gamma = params[colorIndex].gamma;
    offset = params[colorIndex].offset;
    linScale = params[colorIndex].linScale;
    split = params[colorIndex].split;
    break; }
  default:
    break;
  }

  naSetTextFieldText(
    con->responseLinearTextField,
    linScale == -1 ? "" : naAllocSprintf(NA_TRUE, "%1.05f", linScale));
  naSetSliderValue(con->responseLinearSlider, linScale == -1 ? 0 : linScale);
  naSetTextFieldText(
    con->responseSplitTextField,
    split == -1 ? "" : naAllocSprintf(NA_TRUE, "%1.05f", split));
  naSetSliderValue(con->responseSplitSlider, split == -1 ? 0 : split);
  naSetTextFieldText(
    con->responseGammaTextField,
    gamma == -1 ? "" : naAllocSprintf(NA_TRUE, "%1.05f", gamma));
  naSetSliderValue(con->responseGammaSlider, gamma == -1 ? 0 : gamma);
  naSetTextFieldText(
    con->responseOffsetTextField,
    offset == -1 ? "" : naAllocSprintf(NA_TRUE, "%1.05f", offset));
  naSetSliderValue(con->responseOffsetSlider, offset == -1 ? 0 : offset);

  naSetLabelEnabled(con->responseLinearTitleLabel, customAllEnabled);
  naSetTextFieldEnabled(con->responseLinearTextField, customAllEnabled);
  naSetSliderEnabled(con->responseLinearSlider, customAllEnabled);
  naSetLabelEnabled(con->responseSplitTitleLabel, customAllEnabled);
  naSetTextFieldEnabled(con->responseSplitTextField, customAllEnabled);
  naSetSliderEnabled(con->responseSplitSlider, customAllEnabled);
  naSetLabelEnabled(con->responseGammaTitleLabel, customGammaEnabled);
  naSetTextFieldEnabled(con->responseGammaTextField, customGammaEnabled);
  naSetSliderEnabled(con->responseGammaSlider, customGammaEnabled);
  naSetLabelEnabled(con->responseOffsetTitleLabel, customAllEnabled);
  naSetTextFieldEnabled(con->responseOffsetTextField, customAllEnabled);
  naSetSliderEnabled(con->responseOffsetSlider, customAllEnabled);

  cmUpdateGammaDisplayController(con->gammaDisplayController);
}
