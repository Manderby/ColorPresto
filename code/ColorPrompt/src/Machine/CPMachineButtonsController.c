
#include "CPMachineButtonsController.h"

#include "../CPColorPromptApplication.h"
#include "../CPDesign.h"
#include "../CPTranslations.h"

#include "NAApp.h"


struct CPMachineButtonsController{
  NASpace* space;

  NAButton* resetMachineButton;
  NAButton* metamericsButton;
  NAButton* threeDeeButton;
};



NABool cmPressMachineButton(NAReaction reaction){
  CPMachineButtonsController* con = (CPMachineButtonsController*)reaction.controller;
  
  if(reaction.uiElement == con->resetMachineButton){
    cpResetColorMachine();
    cpUpdateMachine();
  }else if(reaction.uiElement == con->metamericsButton){
    cpShowMetamerics();
  }else if(reaction.uiElement == con->threeDeeButton){
    cpShowThreeDee();
  }

  return NA_TRUE;
}



CPMachineButtonsController* cpAllocMachineButtonsController(void){
  CPMachineButtonsController* con = naAlloc(CPMachineButtonsController);

  con->space = naNewSpace(naMakeSize(1, 1));
  naSetSpaceAlternateBackground(con->space, NA_TRUE);

  con->resetMachineButton = naNewTextPushButton(cpTranslate(CPResetButton), 102);
  con->metamericsButton = naNewTextPushButton(cpTranslate(CPMetamericsButton), 102);
  con->threeDeeButton = naNewTextPushButton(cpTranslate(CPThreeDeeButton), 102);
  naAddUIReaction(con->resetMachineButton, NA_UI_COMMAND_PRESSED, cmPressMachineButton, con);
  naAddUIReaction(con->metamericsButton, NA_UI_COMMAND_PRESSED, cmPressMachineButton, con);
  naAddUIReaction(con->threeDeeButton, NA_UI_COMMAND_PRESSED, cmPressMachineButton, con);

  // layout
  cpBeginUILayout(con->space, spaceBezel);
  cpAddUIRow(con->resetMachineButton, uiElemHeight);
  cpAddUICol(con->metamericsButton, 0);
  cpAddUICol(con->threeDeeButton, 0);
  cpEndUILayout();

  return con;
}



void cpDeallocMachineButtonsController(CPMachineButtonsController* con){
  naFree(con);
}



NASpace* cpGetMachineButtonsControllerUIElement(CPMachineButtonsController* con){
  return con->space;
}



void cpUpdateMachineButtonsController(CPMachineButtonsController* con){
}
