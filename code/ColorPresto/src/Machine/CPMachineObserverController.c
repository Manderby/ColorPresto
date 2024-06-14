
#include "CPMachineObserverController.h"

#include "../CPColorPrestoApplication.h"
#include "../CPDesign.h"
#include "../CPTranslations.h"

#include "NAApp/NAApp.h"


struct CPMachineObserverController{
  NASpace* space;

  NALabel* observerTitleLabel;
  NASelect* observerSelect;
  NALabel* observerStepsTitleLabel;
  NALabel* observerStepsLabel;
};



NABool cp_SelectObserver(NAReaction reaction){
  CPMachineObserverController* con = (CPMachineObserverController*)reaction.controller;
  CMLColorMachine* cm = cpGetCurrentColorMachine();

  size_t index = naGetSelectItemIndex(con->observerSelect, reaction.uiElement);
  cmlSetObserverType(cm, (CMLObserverType)index);
  
  cpUpdateMachine();

  return NA_TRUE;
}



CPMachineObserverController* cpAllocMachineObserverController(void){
  CPMachineObserverController* con = naAlloc(CPMachineObserverController);

  con->space = naNewSpace(naMakeSize(1, 1));
naSetSpaceAlternateBackground(con->space, NA_FALSE);

  con->observerTitleLabel = naNewLabel(cpTranslate(CPObserverTitle), machineLabelWidth);
  con->observerSelect = naNewSelect(200);
  for(size_t i = 0; i < CML_OBSERVER_COUNT; ++i){
    CMLObserverType observerType = (CMLObserverType)i;
    if(observerType == CML_OBSERVER_CUSTOM) {continue;}
    NAMenuItem* item = naNewMenuItem(cmlGetObserverTypeString(observerType));
    naAddSelectMenuItem(con->observerSelect, item, NA_NULL);
    naAddUIReaction(item, NA_UI_COMMAND_PRESSED, cp_SelectObserver, con);
  }
  con->observerStepsTitleLabel = naNewLabel(cpTranslate(CPObserverSteps), machineLabelWidth);
  con->observerStepsLabel = naNewLabel("", 100);
  
  // layout
  cpBeginUILayout(con->space, spaceBezel);
  cpAddUIRow(con->observerTitleLabel, uiElemHeight);
  cpAddUICol(con->observerSelect, marginH);
  cpAddUIRow(con->observerStepsTitleLabel, uiElemHeight);
  cpAddUICol(con->observerStepsLabel, marginH);
  cpEndUILayout();

  return con;
}



void cpDeallocMachineObserverController(CPMachineObserverController* con){
  naFree(con);
}



NASpace* cpGetMachineObserverControllerUIElement(CPMachineObserverController* con){
  return con->space;
}



void cpUpdateMachineObserverController(CPMachineObserverController* con){
  CMLColorMachine* cm = cpGetCurrentColorMachine();

  CMLObserverType observerType = cmlGetObserverType(cm);
  CMLFunction* specDistFunctions[3];
  CMLDefinitionRange defRange;
  cmlCreateSpecDistFunctions(specDistFunctions, observerType);
  cmlGetFunctionDefinitionRange(specDistFunctions[0], &defRange);

  naSetSelectIndexSelected(con->observerSelect, observerType);
  naSetLabelText(
    con->observerStepsLabel,
    naAllocSprintf(NA_TRUE, cpTranslate(CPObserverNanoMeterSteps), (int)defRange.stepSize));
}
