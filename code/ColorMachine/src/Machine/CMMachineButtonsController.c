
#include "CMMachineButtonsController.h"

#include "CMMachineIlluminationController.h"
#include "CMMachineObserverController.h"
#include "CMGammaDisplayController.h"

#include "NAApp.h"
#include "CMDesign.h"


struct CMMachineButtonsController{
  NASpace* space;

  NAButton* threeDeeButton;
  NAButton* metamericsButton;
};



NABool cmPressMachineButton(NAReaction reaction){
  CMMachineButtonsController* con = (CMMachineButtonsController*)reaction.controller;
  
  if(reaction.uiElement == con->threeDeeButton){
    showThreeDee();
  }else if(reaction.uiElement == con->metamericsButton){
    showMetamerics();
  }

  return NA_TRUE;
}



CMMachineButtonsController* cmAllocMachineButtonsController(void){
  CMMachineButtonsController* con = naAlloc(CMMachineButtonsController);

  con->space = naNewSpace(naMakeSize(1, 1));
  naSetSpaceAlternateBackground(con->space, NA_FALSE);

  con->threeDeeButton = naNewTextButton("3D View", 120, NA_BUTTON_PUSH | NA_BUTTON_BORDERED);
  con->metamericsButton = naNewTextButton("Metamerics", 120, NA_BUTTON_PUSH | NA_BUTTON_BORDERED);
  naAddUIReaction(con->threeDeeButton, NA_UI_COMMAND_PRESSED, cmPressMachineButton, con);
  naAddUIReaction(con->metamericsButton, NA_UI_COMMAND_PRESSED, cmPressMachineButton, con);

  // layout
  cmBeginUILayout(con->space, spaceBezel);
  cmAddUIRow(con->threeDeeButton, uiElemHeight);
  cmAddUICol(con->metamericsButton, marginH);
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
