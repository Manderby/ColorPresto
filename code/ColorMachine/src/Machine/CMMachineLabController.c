
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
//  CMMachineRGBController* con = (CMMachineRGBController*)reaction.controller;
//  CMLColorMachine* cm = cmGetCurrentColorMachine();
//
//  size_t index = naGetPopupButtonItemIndex(con->rgbColorSpacePopupButton, reaction.uiElement);
//  CMLRGBColorSpaceType rgbColorSpaceType = (CMLRGBColorSpaceType)index;
//  cmlSetRGBColorSpaceType(cm, rgbColorSpaceType);
//  
//  cmUpdateMachine();

  return NA_TRUE;
}



NABool cmSetLabValue(NAReaction reaction){
//  CMMachineRGBController* con = (CMMachineRGBController*)reaction.controller;
//  CMLColorMachine* cm = cmGetCurrentColorMachine();
//
//  size_t index = naGetPopupButtonItemIndex(con->rgbColorSpacePopupButton, reaction.uiElement);
//  CMLRGBColorSpaceType rgbColorSpaceType = (CMLRGBColorSpaceType)index;
//  cmlSetRGBColorSpaceType(cm, rgbColorSpaceType);
//  
//  cmUpdateMachine();

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
    NAMenuItem* item = naNewMenuItem(cmlGetLabColorSpaceTypeString(labColorSpaceType));
    naAddPopupButtonMenuItem(con->labColorSpacePopupButton, item, NA_NULL);
    naAddUIReaction(item, NA_UI_COMMAND_PRESSED, cmSelectLabColorSpace, con);
  }

  con->valueKTitleLabel = naNewLabel("K", 60);
  con->valueKTextField = cmNewValueTextField(cmSetLabValue, con);
  con->valueKSlider = naNewSlider(60);
  con->valuekeTitleLabel = naNewLabel("ke", 60);
  con->valuekeTextField = cmNewValueTextField(cmSetLabValue, con);
  con->valuekeSlider = naNewSlider(60);

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
//  CMLColorMachine* cm = cmGetCurrentColorMachine();

}
