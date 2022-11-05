
#include "CMColorController.h"
#include "CMColorWell1D.h"
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
  CMColorWell1D* colorWell1DH;
  CMColorWell1D* colorWell1DS;
  CMColorWell1D* colorWell1DL;

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
  
  con->labelH = cmNewColorComponentLabel("H");
  con->labelS = cmNewColorComponentLabel("S");
  con->labelL = cmNewColorComponentLabel("L");
  con->textFieldH = cmNewValueTextBox(cmHSLValueEdited, con);
  con->textFieldS = cmNewValueTextBox(cmHSLValueEdited, con);
  con->textFieldL = cmNewValueTextBox(cmHSLValueEdited, con);
  con->colorWell1DH = cmAllocColorWell1D(&(con->baseController), 0);
  con->colorWell1DS = cmAllocColorWell1D(&(con->baseController), 1);
  con->colorWell1DL = cmAllocColorWell1D(&(con->baseController), 2);
  
  NABezel4 colorWellBezel = {20 + colorWell1DSize, 5, colorWell2DSize + 10, 5};
  cmBeginUILayout(con->baseController.space, colorWellBezel);
  cmAddUIPos(0, colorValueCondensedRowHeight);
  cmAddUIRow(con->labelH, colorValueCondensedRowHeight);
  cmAddUICol(con->textFieldH, colorComponentMarginH);
  cmAddUIRow(con->labelS, colorValueCondensedRowHeight);
  cmAddUICol(con->textFieldS, colorComponentMarginH);
  cmAddUIRow(con->labelL, colorValueCondensedRowHeight);
  cmAddUICol(con->textFieldL, colorComponentMarginH);
  cmAddUIPos(0, colorValueCondensedRowHeight);
  cmEndUILayout();
  
  naAddSpaceChild(
    con->baseController.space,
    cmGetColorWell2DUIElement(con->colorWell2D),
    naMakePos(10, 5));

  naAddSpaceChild(
    con->baseController.space,
    cmGetColorWell1DUIElement(con->colorWell1DH),
    naMakePos(colorWell1DMarginLeft, 70));
  naAddSpaceChild(
    con->baseController.space,
    cmGetColorWell1DUIElement(con->colorWell1DS),
    naMakePos(colorWell1DMarginLeft, 50));
  naAddSpaceChild(
    con->baseController.space,
    cmGetColorWell1DUIElement(con->colorWell1DL),
    naMakePos(colorWell1DMarginLeft, 30));
  
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
  
  cmUpdateColorWell2D(con->colorWell2D);
  
  naSetTextFieldText(
    con->textFieldH,
    naAllocSprintf(NA_TRUE, "%3.03f", con->hslColor[0]));
  naSetTextFieldText(
    con->textFieldS,
    naAllocSprintf(NA_TRUE, "%1.05f", con->hslColor[1]));
  naSetTextFieldText(
    con->textFieldL,
    naAllocSprintf(NA_TRUE, "%1.05f", con->hslColor[2]));

  cmUpdateColorWell1D(con->colorWell1DH);
  cmUpdateColorWell1D(con->colorWell1DS);
  cmUpdateColorWell1D(con->colorWell1DL);
}
