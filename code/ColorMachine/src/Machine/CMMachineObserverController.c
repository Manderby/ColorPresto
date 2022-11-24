
#include "CMMachineObserverController.h"

#include "NAApp.h"
#include "CMDesign.h"


struct CMMachineObserverController{
  NASpace* space;

  NALabel* observerTitleLabel;
  NAPopupButton* observerPopupButton;
  NALabel* observerStepsTitleLabel;
  NALabel* observerStepsLabel;
};



NABool cmSelectObserver(NAReaction reaction){
  CMMachineObserverController* con = (CMMachineObserverController*)reaction.controller;
  CMLColorMachine* cm = cmGetCurrentColorMachine();

  size_t index = naGetPopupButtonItemIndex(con->observerPopupButton, reaction.uiElement);
  cmlSetObserverType(cm, (CMLObserverType)index);
  
  cmUpdateMachine();

  return NA_TRUE;
}



CMMachineObserverController* cmAllocMachineObserverController(void){
  CMMachineObserverController* con = naAlloc(CMMachineObserverController);

  con->space = naNewSpace(naMakeSize(1, 1));
naSetSpaceAlternateBackground(con->space, NA_FALSE);

  con->observerTitleLabel = naNewLabel("Observer", machineLabelWidth);
  con->observerPopupButton = naNewPopupButton(200);
  for(size_t i = 0; i < CML_OBSERVER_COUNT; ++i){
    CMLObserverType observerType = (CMLObserverType)i;
    if(observerType == CML_OBSERVER_CUSTOM) {continue;}
    NAMenuItem* item = naNewMenuItem(cmlGetObserverTypeString(observerType));
    naAddPopupButtonMenuItem(con->observerPopupButton, item, NA_NULL);
    naAddUIReaction(item, NA_UI_COMMAND_PRESSED, cmSelectObserver, con);
  }
  con->observerStepsTitleLabel = naNewLabel("Steps:", machineLabelWidth);
  con->observerStepsLabel = naNewLabel("10nm", 100);
  
  // layout
  cmBeginUILayout(con->space, spaceBezel);
  cmAddUIRow(con->observerTitleLabel, uiElemHeight);
  cmAddUICol(con->observerPopupButton, marginH);
  cmAddUIRow(con->observerStepsTitleLabel, uiElemHeight);
  cmAddUICol(con->observerStepsLabel, marginH);
  cmEndUILayout();

  return con;
}



void cmDeallocMachineObserverController(CMMachineObserverController* con){
  naFree(con);
}



NASpace* cmGetMachineObserverControllerUIElement(CMMachineObserverController* con){
  return con->space;
}



void cmUpdateMachineObserverController(CMMachineObserverController* con){
  CMLColorMachine* cm = cmGetCurrentColorMachine();

  CMLObserverType observerType = cmlGetObserverType(cm);
  CMLFunction* specDistFunctions[3];
  CMLDefinitionRange defRange;
  cmlCreateSpecDistFunctions(specDistFunctions, observerType);
  cmlGetFunctionDefinitionRange(specDistFunctions[0], &defRange);

  naSetPopupButtonIndexSelected(con->observerPopupButton, observerType);
  naSetLabelText(
    con->observerStepsLabel,
    naAllocSprintf(NA_TRUE, "%d nm", (int)defRange.stepSize));
}
