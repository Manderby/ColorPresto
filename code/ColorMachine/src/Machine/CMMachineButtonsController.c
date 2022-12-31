
#include "CMMachineButtonsController.h"

#include "../CMColorMachineApplication.h"
#include "../CMDesign.h"
#include "../CMTranslations.h"

#include "NAApp.h"


struct CMMachineButtonsController{
  NASpace* space;

  NAButton* resetMachineButton;
  NAButton* metamericsButton;
  NAButton* threeDeeButton;
};



NABool cmPressMachineButton(NAReaction reaction){
  CMMachineButtonsController* con = (CMMachineButtonsController*)reaction.controller;
  
  if(reaction.uiElement == con->resetMachineButton){
    cmResetColorMachine();
    cmUpdateMachine();
  }else if(reaction.uiElement == con->metamericsButton){
    cmShowMetamerics();
  }else if(reaction.uiElement == con->threeDeeButton){
    cmShowThreeDee();
  }

  return NA_TRUE;
}



CMMachineButtonsController* cmAllocMachineButtonsController(void){
  CMMachineButtonsController* con = naAlloc(CMMachineButtonsController);

  con->space = naNewSpace(naMakeSize(1, 1));
  naSetSpaceAlternateBackground(con->space, NA_TRUE);

  con->resetMachineButton = naNewTextButton("Reset", 110, NA_BUTTON_PUSH | NA_BUTTON_BORDERED);
  con->metamericsButton = naNewTextButton(cmTranslate(CMMetamericsButton), 110, NA_BUTTON_PUSH | NA_BUTTON_BORDERED);
  con->threeDeeButton = naNewTextButton(cmTranslate(CMThreeDeeButton), 110, NA_BUTTON_PUSH | NA_BUTTON_BORDERED);
  naAddUIReaction(con->resetMachineButton, NA_UI_COMMAND_PRESSED, cmPressMachineButton, con);
  naAddUIReaction(con->metamericsButton, NA_UI_COMMAND_PRESSED, cmPressMachineButton, con);
  naAddUIReaction(con->threeDeeButton, NA_UI_COMMAND_PRESSED, cmPressMachineButton, con);

  // layout
  cmBeginUILayout(con->space, spaceBezel);
  cmAddUIRow(con->resetMachineButton, uiElemHeight);
  cmAddUICol(con->metamericsButton, 0);
  cmAddUICol(con->threeDeeButton, 0);
  cmEndUILayout();

  return con;
}



void cmDeallocMachineButtonsController(CMMachineButtonsController* con){
  naFree(con);
}



NASpace* cmGetMachineButtonsControllerUIElement(CMMachineButtonsController* con){
  return con->space;
}



void cmUpdateMachineButtonsController(CMMachineButtonsController* con){
}
