
#include "CMColorController.h"
#include "CMColorWell1D.h"
#include "CMColorWell2D.h"
#include "CMUVWColorController.h"
#include "NAApp.h"
#include "CMDesign.h"

struct CMUVWColorController{
  CMColorController baseController;
  
  CMColorWell2D* colorWell2D;

  NALabel* labelU;
  NALabel* labelV;
  NALabel* labelW;
  NATextField* textFieldU;
  NATextField* textFieldV;
  NATextField* textFieldW;
  CMColorWell1D* colorWell1DU;
  CMColorWell1D* colorWell1DV;
  CMColorWell1D* colorWell1DW;

  CMLVec3 uvwColor;
};



NABool cmUVWValueEdited(NAReaction reaction){
  CMUVWColorController* con = (CMUVWColorController*)reaction.controller;
  
  if(reaction.uiElement == con->textFieldU){
    con->uvwColor[0] = naGetTextFieldDouble(con->textFieldU);
  }else if(reaction.uiElement == con->textFieldV){
    con->uvwColor[1] = naGetTextFieldDouble(con->textFieldV);
  }else if(reaction.uiElement == con->textFieldW){
    con->uvwColor[2] = naGetTextFieldDouble(con->textFieldW);
  }
  
  cmSetCurrentColorController(&(con->baseController));
  cmUpdateColor();
  
  return NA_TRUE;
}



CMUVWColorController* cmAllocUVWColorController(void){
  CMUVWColorController* con = naAlloc(CMUVWColorController);
  
  cmInitColorController(&(con->baseController), CML_COLOR_UVW);
  
  con->colorWell2D = cmAllocColorWell2D(&(con->baseController), 2);

  con->labelU = cmNewColorComponentLabel("U*");
  con->labelV = cmNewColorComponentLabel("V*");
  con->labelW = cmNewColorComponentLabel("W*");
  con->textFieldU = cmNewValueTextField(cmUVWValueEdited, con);
  con->textFieldV = cmNewValueTextField(cmUVWValueEdited, con);
  con->textFieldW = cmNewValueTextField(cmUVWValueEdited, con);
  con->colorWell1DU = cmAllocColorWell1D(&(con->baseController), CML_COLOR_UVW, con->uvwColor, 0);
  con->colorWell1DV = cmAllocColorWell1D(&(con->baseController), CML_COLOR_UVW, con->uvwColor, 1);
  con->colorWell1DW = cmAllocColorWell1D(&(con->baseController), CML_COLOR_UVW, con->uvwColor, 2);

  naSetUIElementNextTabElement(con->textFieldU, con->textFieldU);
  naSetUIElementNextTabElement(con->textFieldV, con->textFieldV);
  naSetUIElementNextTabElement(con->textFieldW, con->textFieldW);

  cmBeginUILayout(con->baseController.space, colorWellBezel);
  cmAddUIPos(0, colorValueCondensedRowHeight);
  cmAddUIRow(con->labelU, colorValueCondensedRowHeight);
  cmAddUICol(con->textFieldU, colorComponentMarginH);
  cmAddUIColV(cmGetColorWell1DUIElement(con->colorWell1DU), 10, colorWell1DOffset);
  cmAddUIRow(con->labelV, colorValueCondensedRowHeight);
  cmAddUICol(con->textFieldV, colorComponentMarginH);
  cmAddUIColV(cmGetColorWell1DUIElement(con->colorWell1DV), 10, colorWell1DOffset);
  cmAddUIRow(con->labelW, colorValueCondensedRowHeight);
  cmAddUICol(con->textFieldW, colorComponentMarginH);
  cmAddUIColV(cmGetColorWell1DUIElement(con->colorWell1DW), 10, colorWell1DOffset);
  cmAddUIPos(0, colorValueCondensedRowHeight);
  cmEndUILayout();
  
  naAddSpaceChild(
    con->baseController.space,
    cmGetColorWell2DUIElement(con->colorWell2D),
    naMakePos(10, 5));

  return con;
}



void cmDeallocUVWColorController(CMUVWColorController* con){
  cmClearColorController(&(con->baseController));
  naFree(con);
}



const void* cmGetUVWColorControllerColorData(const CMUVWColorController* con){
  return &(con->uvwColor);
}



void cmSetUVWColorControllerColorData(CMUVWColorController* con, const void* data){
  cmlCpy3(con->uvwColor, data);
}



void cmUpdateUVWColorController(CMUVWColorController* con){
  cmUpdateColorController(&(con->baseController));

  CMLColorMachine* cm = cmGetCurrentColorMachine();
  CMLColorType currentColorType = cmGetCurrentColorType();
  const float* currentColorData = cmGetCurrentColorData();
  CMLColorConverter converter = cmlGetColorConverter(CML_COLOR_UVW, currentColorType);
  converter(cm, con->uvwColor, currentColorData, 1);
  
  cmUpdateColorWell2D(con->colorWell2D);

  naSetTextFieldText(
    con->textFieldU,
    naAllocSprintf(NA_TRUE, "%3.03f", con->uvwColor[0]));
  naSetTextFieldText(
    con->textFieldV,
    naAllocSprintf(NA_TRUE, "%3.02f", con->uvwColor[1]));
  naSetTextFieldText(
    con->textFieldW,
    naAllocSprintf(NA_TRUE, "%3.02f", con->uvwColor[2]));

  cmUpdateColorWell1D(con->colorWell1DU);
  cmUpdateColorWell1D(con->colorWell1DV);
  cmUpdateColorWell1D(con->colorWell1DW);
}
