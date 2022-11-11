
#include "CMMachineController.h"

#include "NAApp.h"
#include "CMDesign.h"


struct CMMachineController{
  NASpace* space;

  NALabel* observerTitleLabel;
  NAPopupButton* observerPopupButton;
  NALabel* observerStepsTitleLabel;
  NALabel* observerStepsLabel;

  NALabel* illuminationTitleLabel;
};



NABool cmSelectObserver(NAReaction reaction){
  CMMachineController* con = (CMMachineController*)reaction.controller;
  CMLColorMachine* cm = cmGetCurrentColorMachine();

  size_t index = naGetPopupButtonItemIndex(con->observerPopupButton, reaction.uiElement);
  cmlSetObserverType(cm, (CMLObserverType) index);
  
  cmUpdateMachine();

  return NA_TRUE;
}



CMMachineController* cmAllocMachineController(void){
  CMMachineController* con = naAlloc(CMMachineController);
  naZeron(con, sizeof(CMMachineController));

  con->space = naNewSpace(naMakeSize(400, 600));
  naSetSpaceAlternateBackground(con->space, NA_TRUE);

  con->observerTitleLabel = naNewLabel("Observer", 100);
  con->observerPopupButton = naNewPopupButton(200);
  for(size_t i = 0; i < CML_OBSERVER_COUNT; ++i){
    CMLObserverType observerType = (CMLObserverType)i;
    if(observerType == CML_OBSERVER_CUSTOM) {continue;}
    NAMenuItem* item = naNewMenuItem(cmlGetObserverTypeString(observerType));
    naAddPopupButtonMenuItem(con->observerPopupButton, item, NA_NULL);
    naAddUIReaction(item, NA_UI_COMMAND_PRESSED, cmSelectObserver, con);
  }
  con->observerStepsTitleLabel = naNewLabel("Steps:", 100);
  con->observerStepsLabel = naNewLabel("10nm", 100);

  con->illuminationTitleLabel = naNewLabel("Illumination", 100);


  cmBeginUILayout(con->space, spaceBezel);

  cmAddUIRow(con->observerTitleLabel, uiElemHeight);
  cmAddUICol(con->observerPopupButton, marginH);
  cmAddUIRow(con->observerStepsTitleLabel, uiElemHeight);
  cmAddUICol(con->observerStepsLabel, marginH);

  cmAddUIPos(0, 10);

  cmAddUIRow(con->illuminationTitleLabel, uiElemHeight);

  cmEndUILayout();

  return con;
}



void cmDeallocMachineController(CMMachineController* con){
  naFree(con);
}



NASpace* cmGetMachineUIElement(CMMachineController* con){
  return con->space;
}



void cmUpdateMachineController(CMMachineController* con){
  CMLColorMachine* cm = cmGetCurrentColorMachine();

  CMLObserverType observerType = cmlGetObserverType(cm);

  CMLFunction* specDistFunctions[3];
  CMLDefinitionRange defRange;
  cmlCreateSpecDistFunctions(specDistFunctions, observerType);
  cmlGetFunctionDefinitionRange(specDistFunctions[0], &defRange);

  naSetPopupButtonIndexSelected(con->observerPopupButton, observerType);
  naSetLabelText(con->observerStepsLabel, naAllocSprintf(NA_TRUE, "%d nm", (int)defRange.stepSize));
}
