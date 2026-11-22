
#include "CPMachineButtonsController.h"

#include "../CPColorPrestoApplication.h"
#include "../CPDesign.h"
#include "../CPTranslations.h"

#include "NAApp/NAApp.h"
#include "NAUtility/NAMemory.h"


struct CPMachineButtonsController{
  NASpace* space;

  NAButton* resetMachineButton;
  NAButton* metamericsButton;
  NAButton* threeDeeButton;

  NAButton* aboutButton;
  NAButton* preferencesButton;
};



void cp_PressMachineButton(NAReaction reaction) {
  CPMachineButtonsController* con = (CPMachineButtonsController*)reaction.controller;
  
  if(reaction.uiElement == con->resetMachineButton) {
    cpResetColorMachine();
    cpUpdateMachine();
  }else if(reaction.uiElement == con->metamericsButton) {
    cpShowMetamerics();
  }else if(reaction.uiElement == con->threeDeeButton) {
    cpShowThreeDee();
  }else if(reaction.uiElement == con->aboutButton) {
    cpShowAbout();
  }else if(reaction.uiElement == con->preferencesButton) {
    cpShowPreferences();
  }
}



CPMachineButtonsController* cpAllocMachineButtonsController(void) {
  CPMachineButtonsController* con = naAlloc(CPMachineButtonsController);

  con->space = naNewSpace(naMakeSize(1, 1));
  naSetSpaceAlternateBackground(con->space, NA_TRUE);

  con->resetMachineButton = naNewTextPushButton(cpTranslate(CPResetButton), setBigButtonWidth);
  con->metamericsButton = naNewTextPushButton(cpTranslate(CPMetamericsButton), setBigButtonWidth);
  con->threeDeeButton = naNewTextPushButton(cpTranslate(CPThreeDeeButton), setBigButtonWidth);
  naAddUIReaction(con->resetMachineButton, NA_UI_COMMAND_PRESSED, cp_PressMachineButton, con);
  naAddUIReaction(con->metamericsButton, NA_UI_COMMAND_PRESSED, cp_PressMachineButton, con);
  naAddUIReaction(con->threeDeeButton, NA_UI_COMMAND_PRESSED, cp_PressMachineButton, con);

  con->aboutButton = naNewTextPushButton(cpTranslate(CPAboutButton), setBigButtonWidth);
  con->preferencesButton = naNewTextPushButton(cpTranslate(CPPreferencesButton), setBigButtonWidth);
  naAddUIReaction(con->aboutButton, NA_UI_COMMAND_PRESSED, cp_PressMachineButton, con);
  naAddUIReaction(con->preferencesButton, NA_UI_COMMAND_PRESSED, cp_PressMachineButton, con);

  // layout
  
  NABorder2D zeroPadding = naMakeBorder2D(0., 0., 0., 0.);

  naBeginLayout(con->space, spaceBorder);
    naAddLayoutSection(uiElemHeight, naMakeBorder2D(0., 0., 0., 0.));
      naAddLayoutElement(con->resetMachineButton, 0, setBigButtonWidth);
      naAddLayoutElement(con->metamericsButton, marginH, setBigButtonWidth);
      naAddLayoutElement(con->threeDeeButton, marginH, setBigButtonWidth);
    naAddLayoutSection(uiElemHeight, naMakeBorder2D(0., 0., spaceMarginTop, 0.));
      naAddLayoutElement(con->aboutButton, 0, setBigButtonWidth);
      naAddLayoutElement(con->preferencesButton, marginH, setBigButtonWidth);
  naEndLayout();
  
  return con;
}



void cpDeallocMachineButtonsController(CPMachineButtonsController* con) {
  naFree(con);
}



NASpace* cpGetMachineButtonsControllerUIElement(CPMachineButtonsController* con) {
  return con->space;
}



void cpUpdateMachineButtonsController(CPMachineButtonsController* con) {
}
