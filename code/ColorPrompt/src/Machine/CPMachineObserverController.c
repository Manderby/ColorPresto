
#include "CPMachineObserverController.h"

#include "../CPColorPromptApplication.h"
#include "../CPDesign.h"
#include "../CPTranslations.h"

#include "NAApp.h"


struct CPMachineObserverController{
  NASpace* space;

  NALabel* observerTitleLabel;
  NAPopupButton* observerPopupButton;
  NALabel* observerStepsTitleLabel;
  NALabel* observerStepsLabel;
};



NABool cmSelectObserver(NAReaction reaction){
  CPMachineObserverController* con = (CPMachineObserverController*)reaction.controller;
  CMLColorMachine* cm = cpGetCurrentColorMachine();

  size_t index = naGetPopupButtonItemIndex(con->observerPopupButton, reaction.uiElement);
  cmlSetObserverType(cm, (CMLObserverType)index);
  
  cpUpdateMachine();

  return NA_TRUE;
}



CPMachineObserverController* cmAllocMachineObserverController(void){
  CPMachineObserverController* con = naAlloc(CPMachineObserverController);

  con->space = naNewSpace(naMakeSize(1, 1));
naSetSpaceAlternateBackground(con->space, NA_FALSE);

  con->observerTitleLabel = naNewLabel(cpTranslate(CPObserverTitle), machineLabelWidth);
  con->observerPopupButton = naNewPopupButton(200);
  for(size_t i = 0; i < CML_OBSERVER_COUNT; ++i){
    CMLObserverType observerType = (CMLObserverType)i;
    if(observerType == CML_OBSERVER_CUSTOM) {continue;}
    NAMenuItem* item = naNewMenuItem(cmlGetObserverTypeString(observerType));
    naAddPopupButtonMenuItem(con->observerPopupButton, item, NA_NULL);
    naAddUIReaction(item, NA_UI_COMMAND_PRESSED, cmSelectObserver, con);
  }
  con->observerStepsTitleLabel = naNewLabel(cpTranslate(CPObserverSteps), machineLabelWidth);
  con->observerStepsLabel = naNewLabel("", 100);
  
  // layout
  cpBeginUILayout(con->space, spaceBezel);
  cpAddUIRow(con->observerTitleLabel, uiElemHeight);
  cpAddUICol(con->observerPopupButton, marginH);
  cpAddUIRow(con->observerStepsTitleLabel, uiElemHeight);
  cpAddUICol(con->observerStepsLabel, marginH);
  cpEndUILayout();

  return con;
}



void cmDeallocMachineObserverController(CPMachineObserverController* con){
  naFree(con);
}



NASpace* cmGetMachineObserverControllerUIElement(CPMachineObserverController* con){
  return con->space;
}



void cpUpdateMachineObserverController(CPMachineObserverController* con){
  CMLColorMachine* cm = cpGetCurrentColorMachine();

  CMLObserverType observerType = cmlGetObserverType(cm);
  CMLFunction* specDistFunctions[3];
  CMLDefinitionRange defRange;
  cmlCreateSpecDistFunctions(specDistFunctions, observerType);
  cmlGetFunctionDefinitionRange(specDistFunctions[0], &defRange);

  naSetPopupButtonIndexSelected(con->observerPopupButton, observerType);
  naSetLabelText(
    con->observerStepsLabel,
    naAllocSprintf(NA_TRUE, cpTranslate(CPObserverNanoMeterSteps), (int)defRange.stepSize));
}
