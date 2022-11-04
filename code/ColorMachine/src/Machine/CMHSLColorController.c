
#include "CMColorController.h"
#include "CMColorWell2D.h"
#include "CMHSLColorController.h"
#include "NAApp.h"
#include "CMDesign.h"

struct CMHSLColorController{
  CMColorController baseController;
  
  CMColorWell2D* colorWell2D;
  
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
  
  cmSetCurrentColorController(&(con->baseController));
  cmUpdateColor();
  
  return NA_TRUE;
}


CMHSLColorController* cmAllocHSLColorController(void){
  CMHSLColorController* con = naAlloc(CMHSLColorController);
  
  cmInitColorController(&(con->baseController), CML_COLOR_HSL);
  
  con->colorWell2D = cmAllocColorWell2D(&(con->baseController), 2);
  
  con->labelH = naNewLabel("H", 20);
  con->labelS = naNewLabel("S", 20);
  con->labelL = naNewLabel("L", 20);
  con->textFieldH = cmNewValueTextBox();
  con->textFieldS = cmNewValueTextBox();
  con->textFieldL = cmNewValueTextBox();
  
  naAddUIReaction(con->textFieldH, NA_UI_COMMAND_EDIT_FINISHED, cmHSLValueEdited, con);
  naAddUIReaction(con->textFieldS, NA_UI_COMMAND_EDIT_FINISHED, cmHSLValueEdited, con);
  naAddUIReaction(con->textFieldL, NA_UI_COMMAND_EDIT_FINISHED, cmHSLValueEdited, con);
  
  NABezel4 colorWellBezel = {10, 10, colorWellSize + 20, 10};
  cmBeginUILayout(con->baseController.space, colorWellBezel);
  cmAddUIPos(0, colorValueCondensedRowHeight);
  cmAddUIRow(con->labelH, colorValueCondensedRowHeight);
  cmAddUICol(con->textFieldH, 0);
  cmAddUIRow(con->labelS, colorValueCondensedRowHeight);
  cmAddUICol(con->textFieldS, 0);
  cmAddUIRow(con->labelL, colorValueCondensedRowHeight);
  cmAddUICol(con->textFieldL, 0);
  cmAddUIPos(0, colorValueCondensedRowHeight);
  cmEndUILayout();
  
  naAddSpaceChild(
    con->baseController.space,
    cmGetColorWell2DUIElement(con->colorWell2D),
    naMakePos(10, 10));
  
  return con;
}



void cmDeallocHSLColorController(CMHSLColorController* con){
  cmClearColorController(&(con->baseController));
  naFree(con);
}



const void* cmGetHSLColorControllerColorData(const CMHSLColorController* con){
  return &(con->hslColor);
}



void cmSetHSLColorControllerColorData(CMHSLColorController* con, const void* data){
  cmlCpy3(con->hslColor, data);
}



void cmUpdateHSLColorController(CMHSLColorController* con){
  cmUpdateColorController(&(con->baseController));
  
  CMLColorMachine* cm = cmGetCurrentColorMachine();
  CMLColorType currentColorType = cmGetCurrentColorType();
  const float* currentColorData = cmGetCurrentColorData();
  CMLColorConverter converter = cmlGetColorConverter(CML_COLOR_HSL, currentColorType);
  converter(cm, con->hslColor, currentColorData, 1);
  
  cmUpdateColorWell2d(con->colorWell2D);
  
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
