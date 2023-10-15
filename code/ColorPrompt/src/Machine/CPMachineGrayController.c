
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
  CMLColorMachine* cm = cpGetCurrentColorMachine();

  size_t index = naGetPopupButtonItemIndex(con->grayColorSpacePopupButton, reaction.uiElement);
  CMLGrayComputationType grayComputationType = (CMLGrayComputationType)index;
  cmlSetGrayComputationType(cm, grayComputationType);
  
  cpUpdateMachine();

  return NA_TRUE;
}



CPMachineGrayController* cpAllocMachineGrayController(void){
  CPMachineGrayController* con = naAlloc(CPMachineGrayController);

  con->space = naNewSpace(naMakeSize(1, 1));
  naSetSpaceAlternateBackground(con->space, NA_FALSE);

  con->grayColorSpaceLabel = naNewLabel(cpTranslate(CPGrayColorSpace), machineLabelWidth);
  con->grayColorSpacePopupButton = naNewPopupButton(200);
  for(size_t i = 0; i < CML_GRAY_COUNT; ++i){
    CMLGrayComputationType grayComputationType = (CMLGrayComputationType)i;
    NAMenuItem* item = naNewMenuItem(cmlGetGrayComputationTypeString(grayComputationType));
    naAddPopupButtonMenuItem(con->grayColorSpacePopupButton, item, NA_NULL);
    naAddUIReaction(item, NA_UI_COMMAND_PRESSED, cmSelectGrayColorSpace, con);
  }

  // layout
  cpBeginUILayout(con->space, spaceBezel);
  cpAddUIRow(con->grayColorSpaceLabel, uiElemHeight);
  cpAddUICol(con->grayColorSpacePopupButton, marginH);
  cpEndUILayout();

  return con;
}



void cpDeallocMachineGrayController(CPMachineGrayController* con){
  naFree(con);
}



NASpace* cpGetMachineGrayControllerUIElement(CPMachineGrayController* con){
  return con->space;
}



void cpUpdateMachineGrayController(CPMachineGrayController* con){
  CMLColorMachine* cm = cpGetCurrentColorMachine();

  CMLGrayComputationType grayComputationType = cmlGetGrayComputationType(cm);
  naSetPopupButtonIndexSelected(con->grayColorSpacePopupButton, grayComputationType);
}
