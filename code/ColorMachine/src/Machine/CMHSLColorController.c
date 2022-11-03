
#include "CMColorController.h"
#include "CMHSLColorController.h"
#include "NAApp.h"
#include "CMDesign.h"

struct CMHSLColorController{
  CMColorController baseController;
  
  NALabel* labelH;
  NALabel* labelS;
  NALabel* labelL;
  NATextField* textFieldH;
  NATextField* textFieldS;
  NATextField* textFieldL;
  
  CMLVec3 hslColor;
};



NABool cmHSLValueEdited(NAReaction reaction){
  CMHSLColorController* con = (CMHSLColorController*)reaction.controller;
  
  if(reaction.uiElement == con->textFieldH){
    NAString* string = naNewStringWithTextFieldText(con->textFieldH);
    con->hslColor[0] = atof(naGetStringUTF8Pointer(string));
    naDelete(string);
  }else if(reaction.uiElement == con->textFieldS){
    NAString* string = naNewStringWithTextFieldText(con->textFieldS);
    con->hslColor[1] = atof(naGetStringUTF8Pointer(string));
    naDelete(string);
  }else if(reaction.uiElement == con->textFieldL){
    NAString* string = naNewStringWithTextFieldText(con->textFieldL);
    con->hslColor[2] = atof(naGetStringUTF8Pointer(string));
    naDelete(string);
  }
  
  cmUpdateMachine();
  
  return NA_TRUE;
}


CMHSLColorController* cmAllocHSLColorController(void){
  CMHSLColorController* con = naAlloc(CMHSLColorController);
  
  cmInitColorController(&(con->baseController), CML_COLOR_HSL);
    
  con->labelH = naNewLabel("H", 20);
  con->labelS = naNewLabel("S", 20);
  con->labelL = naNewLabel("L", 20);
  con->textFieldH = naNewTextField(valueWidth);
  con->textFieldS = naNewTextField(valueWidth);
  con->textFieldL = naNewTextField(valueWidth);
  
  naAddUIReaction(con->textFieldH, NA_UI_COMMAND_EDIT_FINISHED, cmHSLValueEdited, con);
  naAddUIReaction(con->textFieldS, NA_UI_COMMAND_EDIT_FINISHED, cmHSLValueEdited, con);
  naAddUIReaction(con->textFieldL, NA_UI_COMMAND_EDIT_FINISHED, cmHSLValueEdited, con);
  
  NABezel4 colorWellBezel = {10, 10, 150, 10};
  cmBeginUILayout(con->baseController.space, colorWellBezel);
  cmAddUIPos(0, uiElemHeight);
  cmAddUIRow(con->labelH, uiElemHeight);
  cmAddUICol(con->textFieldH, 0);
  cmAddUIRow(con->labelS, uiElemHeight);
  cmAddUICol(con->textFieldS, 0);
  cmAddUIRow(con->labelL, uiElemHeight);
  cmAddUICol(con->textFieldL, 0);
  cmAddUIPos(0, uiElemHeight);
  
  cmEndUILayout();
  
  return con;
}



void cmDeallocHSLColorController(CMHSLColorController* con){
  cmClearColorController(&(con->baseController));
  naFree(con);
}



const void* cmGetHSLColorControllerColorData(const CMHSLColorController* con){
  return &(con->hslColor);
}



void cmUpdateHSLColorController(CMHSLColorController* con){
  cmUpdateColorController(&(con->baseController));
  
  CMLColorMachine* cm = cmGetCurrentColorMachine();
  CMLColorType currentColorType = cmGetCurrentColorType();
  const float* currentColorData = cmGetCurrentColorData();
  CMLColorConverter converter = cmlGetColorConverter(CML_COLOR_HSL, currentColorType);
  converter(cm, con->hslColor, currentColorData, 1);
  
  naSetTextFieldText(
    con->textFieldH,
    naAllocSprintf(NA_TRUE, "%3.03f", con->hslColor[0]));
  naSetTextFieldText(
    con->textFieldS,
    naAllocSprintf(NA_TRUE, "%1.05f", con->hslColor[1]));
  naSetTextFieldText(
    con->textFieldL,
    naAllocSprintf(NA_TRUE, "%1.05f", con->hslColor[2]));
}
