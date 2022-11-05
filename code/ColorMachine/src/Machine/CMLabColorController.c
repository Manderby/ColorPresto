
#include "CMColorController.h"
#include "CMColorWell1D.h"
#include "CMColorWell2D.h"
#include "CMLabColorController.h"
#include "NAApp.h"
#include "CMDesign.h"

struct CMLabColorController{
  CMColorController baseController;
  
  CMColorWell2D* colorWell2D;

  NALabel* labelL;
  NALabel* labela;
  NALabel* labelb;
  NALabel* labelc;
  NALabel* labelh;
  NATextField* textFieldL;
  NATextField* textFielda;
  NATextField* textFieldb;
  NATextField* textFieldc;
  NATextField* textFieldh;
  CMColorWell1D* colorWell1DL;
  CMColorWell1D* colorWell1Da;
  CMColorWell1D* colorWell1Db;
  CMColorWell1D* colorWell1Dc;
  CMColorWell1D* colorWell1Dh;

  CMLVec3 labColor;
  CMLVec3 lchColor;
};



NABool cmLabValueEdited(NAReaction reaction){
  CMLabColorController* con = (CMLabColorController*)reaction.controller;
  
  if(reaction.uiElement == con->textFieldL){
    NAString* string = naNewStringWithTextFieldText(con->textFieldL);
    con->labColor[0] = atof(naGetStringUTF8Pointer(string));
    naDelete(string);
  }else if(reaction.uiElement == con->textFielda){
    NAString* string = naNewStringWithTextFieldText(con->textFielda);
    con->labColor[1] = atof(naGetStringUTF8Pointer(string));
    naDelete(string);
  }else if(reaction.uiElement == con->textFieldb){
    NAString* string = naNewStringWithTextFieldText(con->textFieldb);
    con->labColor[2] = atof(naGetStringUTF8Pointer(string));
    naDelete(string);
  }
  
  cmSetCurrentColorController(&(con->baseController));
  cmUpdateColor();
  
  return NA_TRUE;
}



CMLabColorController* cmAllocLabColorController(void){
  CMLabColorController* con = naAlloc(CMLabColorController);
  
  cmInitColorController(&(con->baseController), CML_COLOR_Lab);
  
  con->colorWell2D = cmAllocColorWell2D(&(con->baseController), 0);

  con->labelL = cmNewColorComponentLabel("L");
  con->labela = cmNewColorComponentLabel("a");
  con->labelb = cmNewColorComponentLabel("b");
  con->labelc = cmNewColorComponentLabel("c");
  con->labelh = cmNewColorComponentLabel("h");
  con->textFieldL = cmNewValueTextBox(cmLabValueEdited, con);
  con->textFielda = cmNewValueTextBox(cmLabValueEdited, con);
  con->textFieldb = cmNewValueTextBox(cmLabValueEdited, con);
  con->textFieldc = cmNewValueTextBox(cmLabValueEdited, con);
  con->textFieldh = cmNewValueTextBox(cmLabValueEdited, con);
  con->colorWell1DL = cmAllocColorWell1D(&(con->baseController), CML_COLOR_Lab, con->labColor, 0);
  con->colorWell1Da = cmAllocColorWell1D(&(con->baseController), CML_COLOR_Lab, con->labColor, 1);
  con->colorWell1Db = cmAllocColorWell1D(&(con->baseController), CML_COLOR_Lab, con->labColor, 2);
  con->colorWell1Dc = cmAllocColorWell1D(&(con->baseController), CML_COLOR_Lch, con->lchColor, 1);
  con->colorWell1Dh = cmAllocColorWell1D(&(con->baseController), CML_COLOR_Lch, con->lchColor, 2);

  NABezel4 colorWellBezel = {20 + colorWell1DSize, 5, colorWell2DSize + 15, 5};
  cmBeginUILayout(con->baseController.space, colorWellBezel);
  cmAddUIRow(con->labelL, colorValueCondensedRowHeight);
  cmAddUICol(con->textFieldL, colorComponentMarginH);
  cmAddUIRow(con->labela, colorValueCondensedRowHeight);
  cmAddUICol(con->textFielda, colorComponentMarginH);
  cmAddUIRow(con->labelb, colorValueCondensedRowHeight);
  cmAddUICol(con->textFieldb, colorComponentMarginH);
  cmAddUIRow(con->labelc, colorValueCondensedRowHeight);
  cmAddUICol(con->textFieldc, colorComponentMarginH);
  cmAddUIRow(con->labelh, colorValueCondensedRowHeight);
  cmAddUICol(con->textFieldh, colorComponentMarginH);
  cmEndUILayout();
  
  naAddSpaceChild(
    con->baseController.space,
    cmGetColorWell2DUIElement(con->colorWell2D),
    naMakePos(10, 5));

  naAddSpaceChild(
    con->baseController.space,
    cmGetColorWell1DUIElement(con->colorWell1DL),
    naMakePos(colorWell1DMarginLeft, 90));
  naAddSpaceChild(
    con->baseController.space,
    cmGetColorWell1DUIElement(con->colorWell1Da),
    naMakePos(colorWell1DMarginLeft, 70));
  naAddSpaceChild(
    con->baseController.space,
    cmGetColorWell1DUIElement(con->colorWell1Db),
    naMakePos(colorWell1DMarginLeft, 50));
  naAddSpaceChild(
    con->baseController.space,
    cmGetColorWell1DUIElement(con->colorWell1Dc),
    naMakePos(colorWell1DMarginLeft, 30));
  naAddSpaceChild(
    con->baseController.space,
    cmGetColorWell1DUIElement(con->colorWell1Dh),
    naMakePos(colorWell1DMarginLeft, 10));

  return con;
}



void cmDeallocLabColorController(CMLabColorController* con){
  cmClearColorController(&(con->baseController));
  naFree(con);
}



const void* cmGetLabColorControllerColorData(const CMLabColorController* con){
  return &(con->labColor);
}



void cmSetLabColorControllerColorData(CMLabColorController* con, const void* data){
  cmlCpy3(con->labColor, data);
}



void cmUpdateLabColorController(CMLabColorController* con){
  cmUpdateColorController(&(con->baseController));

  CMLColorMachine* cm = cmGetCurrentColorMachine();
  CMLColorType currentColorType = cmGetCurrentColorType();
  const float* currentColorData = cmGetCurrentColorData();
  CMLColorConverter labConverter = cmlGetColorConverter(CML_COLOR_Lab, currentColorType);
  labConverter(cm, con->labColor, currentColorData, 1);
  CMLColorConverter lchConverter = cmlGetColorConverter(CML_COLOR_Lch, currentColorType);
  lchConverter(cm, con->lchColor, currentColorData, 1);
  
  cmUpdateColorWell2D(con->colorWell2D);

  switch(cmlGetLabColorSpace(cm)){
  case CML_LAB_CIELAB:
    naSetLabelText(con->labelL, "L*");
    naSetLabelText(con->labela, "a*");
    naSetLabelText(con->labelb, "b*");
    break;
  default:
    naSetLabelText(con->labelL, "L");
    naSetLabelText(con->labela, "a");
    naSetLabelText(con->labelb, "b");
  }

  naSetTextFieldText(
    con->textFieldL,
    naAllocSprintf(NA_TRUE, "%3.03f", con->labColor[0]));
  naSetTextFieldText(
    con->textFielda,
    naAllocSprintf(NA_TRUE, "%3.02f", con->labColor[1]));
  naSetTextFieldText(
    con->textFieldb,
    naAllocSprintf(NA_TRUE, "%3.02f", con->labColor[2]));
  naSetTextFieldText(
    con->textFieldc,
    naAllocSprintf(NA_TRUE, "%3.02f", con->lchColor[1]));
  naSetTextFieldText(
    con->textFieldh,
    naAllocSprintf(NA_TRUE, "%3.02f", con->lchColor[2]));

  cmUpdateColorWell1D(con->colorWell1DL);
  cmUpdateColorWell1D(con->colorWell1Da);
  cmUpdateColorWell1D(con->colorWell1Db);
  cmUpdateColorWell1D(con->colorWell1Dc);
  cmUpdateColorWell1D(con->colorWell1Dh);
}
