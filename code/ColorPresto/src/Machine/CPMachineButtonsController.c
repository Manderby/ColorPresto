
#include "CPMachineButtonsController.h"

#include "../CPColorPrestoApplication.h"
#include "../CPDesign.h"
#include "../CPTranslations.h"

#include "NAApp/NAApp.h"


struct CPMachineButtonsController{
  NASpace* space;

  NAButton* resetMachineButton;
  NAButton* metamericsButton;
  NAButton* threeDeeButton;

  NAButton* aboutButton;
  NAButton* preferencesButton;
};



NABool cp_PressMachineButton(NAReaction reaction){
  CPMachineButtonsController* con = (CPMachineButtonsController*)reaction.controller;
  
  if(reaction.uiElement == con->resetMachineButton){
    cpResetColorMachine();
    cpUpdateMachine();
  }else if(reaction.uiElement == con->metamericsButton){
    cpShowMetamerics();
  }else if(reaction.uiElement == con->threeDeeButton){
    cpShowThreeDee();
  }else if(reaction.uiElement == con->aboutButton){
    cpShowAbout();
  }else if(reaction.uiElement == con->preferencesButton){
    cpShowPreferences();
  }

  return NA_TRUE;
}



CPMachineButtonsController* cpAllocMachineButtonsController(void){
  CPMachineButtonsController* con = naAlloc(CPMachineButtonsController);

  con->space = naNewSpace(naMakeSize(1, 1));
  naSetSpaceAlternateBackground(con->space, NA_TRUE);

  con->resetMachineButton = naNewTextPushButton(cpTranslate(CPResetButton), 100);
  con->metamericsButton = naNewTextPushButton(cpTranslate(CPMetamericsButton), 100);
  con->threeDeeButton = naNewTextPushButton(cpTranslate(CPThreeDeeButton), 100);
  naAddUIReaction(con->resetMachineButton, NA_UI_COMMAND_PRESSED, cp_PressMachineButton, con);
  naAddUIReaction(con->metamericsButton, NA_UI_COMMAND_PRESSED, cp_PressMachineButton, con);
  naAddUIReaction(con->threeDeeButton, NA_UI_COMMAND_PRESSED, cp_PressMachineButton, con);

  con->aboutButton = naNewTextPushButton(cpTranslate(CPAboutButton), 100);
  con->preferencesButton = naNewTextPushButton(cpTranslate(CPPreferencesButton), 100);
  naAddUIReaction(con->aboutButton, NA_UI_COMMAND_PRESSED, cp_PressMachineButton, con);
  naAddUIReaction(con->preferencesButton, NA_UI_COMMAND_PRESSED, cp_PressMachineButton, con);

  // layout
  cpBeginUILayout(con->space, spaceBezel);
  cpAddUIRow(con->resetMachineButton, uiElemHeight);
  cpAddUICol(con->metamericsButton, 0);
  cpAddUICol(con->threeDeeButton, 0);

  cpAddUIRow(con->aboutButton, 2 * uiElemHeight);
  cpAddUICol(con->preferencesButton, 0);
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
