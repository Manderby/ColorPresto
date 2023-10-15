
#include "CMMachineGrayController.h"

#include "../CMColorMachineApplication.h"
#include "../CMDesign.h"
#include "../CMTranslations.h"
#include "CMMachineObserverController.h"

#include "NAApp.h"


struct CMMachineGrayController{
  NASpace* space;

  NALabel* grayColorSpaceLabel;
  NASelect* grayColorSpaceSelect;
};



NABool cmSelectGrayColorSpace(NAReaction reaction){
  CMMachineGrayController* con = (CMMachineGrayController*)reaction.controller;
  CMLColorMachine* cm = cmGetCurrentColorMachine();

  size_t index = naGetSelectItemIndex(con->grayColorSpaceSelect, reaction.uiElement);
  CMLGrayComputationType grayComputationType = (CMLGrayComputationType)index;
  cmlSetGrayComputationType(cm, grayComputationType);
  
  cmUpdateMachine();

  return NA_TRUE;
}



CMMachineGrayController* cmAllocMachineGrayController(void){
  CMMachineGrayController* con = naAlloc(CMMachineGrayController);

  con->space = naNewSpace(naMakeSize(1, 1));
  naSetSpaceAlternateBackground(con->space, NA_FALSE);

  con->grayColorSpaceLabel = naNewLabel(cmTranslate(CMGrayColorSpace), machineLabelWidth);
  con->grayColorSpaceSelect = naNewSelect(200);
  for(size_t i = 0; i < CML_GRAY_COUNT; ++i){
    CMLGrayComputationType grayComputationType = (CMLGrayComputationType)i;
    NAMenuItem* item = naNewMenuItem(cmlGetGrayComputationTypeString(grayComputationType));
    naAddSelectMenuItem(con->grayColorSpaceSelect, item, NA_NULL);
    naAddUIReaction(item, NA_UI_COMMAND_PRESSED, cmSelectGrayColorSpace, con);
  }

  // layout
  cmBeginUILayout(con->space, spaceBezel);
  cmAddUIRow(con->grayColorSpaceLabel, uiElemHeight);
  cmAddUICol(con->grayColorSpaceSelect, marginH);
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
  CMLColorMachine* cm = cmGetCurrentColorMachine();

  CMLGrayComputationType grayComputationType = cmlGetGrayComputationType(cm);
  naSetSelectIndexSelected(con->grayColorSpaceSelect, grayComputationType);
}
