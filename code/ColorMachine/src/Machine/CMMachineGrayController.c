
#include "CMMachineGrayController.h"

#include "CMMachineObserverController.h"

#include "NAApp.h"
#include "CMDesign.h"


struct CMMachineGrayController{
  NASpace* space;

  NALabel* grayColorSpaceLabel;
  NAPopupButton* grayColorSpacePopupButton;
};



NABool cmSelectGrayColorSpace(NAReaction reaction){
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



CMMachineGrayController* cmAllocMachineGrayController(void){
  CMMachineGrayController* con = naAlloc(CMMachineGrayController);

  con->space = naNewSpace(naMakeSize(1, 1));
  naSetSpaceAlternateBackground(con->space, NA_FALSE);

  con->grayColorSpaceLabel = naNewLabel("Gray Colorspace", machineLabelWidth);
  con->grayColorSpacePopupButton = naNewPopupButton(200);
  for(size_t i = 0; i < CML_LAB_COUNT; ++i){
    CMLGrayComputationType grayComputationType = (CMLGrayComputationType)i;
    NAMenuItem* item = naNewMenuItem(cmlGetGrayComputationTypeString(grayComputationType));
    naAddPopupButtonMenuItem(con->grayColorSpacePopupButton, item, NA_NULL);
    naAddUIReaction(item, NA_UI_COMMAND_PRESSED, cmSelectGrayColorSpace, con);
  }

  // layout
  cmBeginUILayout(con->space, spaceBezel);
  cmAddUIRow(con->grayColorSpaceLabel, uiElemHeight);
  cmAddUICol(con->grayColorSpacePopupButton, marginH);
  cmEndUILayout();

  return con;
}



void cmDeallocMachineGrayController(CMMachineGrayController* con){
  naFree(con);
}



NASpace* cmGetMachineGrayControllerUIElement(CMMachineGrayController* con){
  return con->space;
}



void cmUpdateMachineGrayController(CMMachineGrayController* con){
//  CMLColorMachine* cm = cmGetCurrentColorMachine();

}
