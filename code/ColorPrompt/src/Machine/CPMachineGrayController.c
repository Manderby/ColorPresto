
#include "CPMachineGrayController.h"

#include "../CPColorPromptApplication.h"
#include "../CPDesign.h"
#include "../CPTranslations.h"
#include "CPMachineObserverController.h"

#include "NAApp.h"


struct CPMachineGrayController{
  NASpace* space;

  NALabel* grayColorSpaceLabel;
  NAPopupButton* grayColorSpacePopupButton;
};



NABool cmSelectGrayColorSpace(NAReaction reaction){
  CPMachineGrayController* con = (CPMachineGrayController*)reaction.controller;
  CMLColorMachine* cm = cmGetCurrentColorMachine();

  size_t index = naGetPopupButtonItemIndex(con->grayColorSpacePopupButton, reaction.uiElement);
  CMLGrayComputationType grayComputationType = (CMLGrayComputationType)index;
  cmlSetGrayComputationType(cm, grayComputationType);
  
  cmUpdateMachine();

  return NA_TRUE;
}



CPMachineGrayController* cmAllocMachineGrayController(void){
  CPMachineGrayController* con = naAlloc(CPMachineGrayController);

  con->space = naNewSpace(naMakeSize(1, 1));
  naSetSpaceAlternateBackground(con->space, NA_FALSE);

  con->grayColorSpaceLabel = naNewLabel(cmTranslate(CMGrayColorSpace), machineLabelWidth);
  con->grayColorSpacePopupButton = naNewPopupButton(200);
  for(size_t i = 0; i < CML_GRAY_COUNT; ++i){
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



void cmDeallocMachineGrayController(CPMachineGrayController* con){
  naFree(con);
}



NASpace* cmGetMachineGrayControllerUIElement(CPMachineGrayController* con){
  return con->space;
}



void cmUpdateMachineGrayController(CPMachineGrayController* con){
  CMLColorMachine* cm = cmGetCurrentColorMachine();

  CMLGrayComputationType grayComputationType = cmlGetGrayComputationType(cm);
  naSetPopupButtonIndexSelected(con->grayColorSpacePopupButton, grayComputationType);
}
