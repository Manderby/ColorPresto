
#include "CMColorController.h"
#include "CMColorWell1D.h"
#include "CMColorWell2D.h"
#include "CMXYZColorController.h"
#include "NAApp.h"
#include "CMDesign.h"

struct CMXYZColorController{
  CMColorController baseController;
  
  CMColorWell2D* colorWell2D;

  NALabel* labelX;
  NALabel* labelY;
  NALabel* labelZ;
  NATextField* textFieldX;
  NATextField* textFieldY;
  NATextField* textFieldZ;
  CMColorWell1D* colorWell1DX;
  CMColorWell1D* colorWell1DY;
  CMColorWell1D* colorWell1DZ;

  CMLVec3 XYZColor;
};



NABool cmXYZValueEdited(NAReaction reaction){
  CMXYZColorController* con = (CMXYZColorController*)reaction.controller;
  
  if(reaction.uiElement == con->textFieldX){
    NAString* string = naNewStringWithTextFieldText(con->textFieldX);
    con->XYZColor[0] = atof(naGetStringUTF8Pointer(string));
    naDelete(string);
  }else if(reaction.uiElement == con->textFieldY){
    NAString* string = naNewStringWithTextFieldText(con->textFieldY);
    con->XYZColor[1] = atof(naGetStringUTF8Pointer(string));
    naDelete(string);
  }else if(reaction.uiElement == con->textFieldZ){
    NAString* string = naNewStringWithTextFieldText(con->textFieldZ);
    con->XYZColor[2] = atof(naGetStringUTF8Pointer(string));
    naDelete(string);
  }
  
  cmSetCurrentColorController(&(con->baseController));
  cmUpdateColor();
  
  return NA_TRUE;
}



CMXYZColorController* cmAllocXYZColorController(void){
  CMXYZColorController* con = naAlloc(CMXYZColorController);
  
  cmInitColorController(&(con->baseController), CML_COLOR_XYZ);
  
  con->colorWell2D = cmAllocColorWell2D(&(con->baseController), 1);

  con->labelX = cmNewColorComponentLabel("X");
  con->labelY = cmNewColorComponentLabel("Y");
  con->labelZ = cmNewColorComponentLabel("Z");
  con->textFieldX = cmNewValueTextBox(cmXYZValueEdited, con);
  con->textFieldY = cmNewValueTextBox(cmXYZValueEdited, con);
  con->textFieldZ = cmNewValueTextBox(cmXYZValueEdited, con);
  con->colorWell1DX = cmAllocColorWell1D(&(con->baseController), CML_COLOR_XYZ, con->XYZColor, 0);
  con->colorWell1DY = cmAllocColorWell1D(&(con->baseController), CML_COLOR_XYZ, con->XYZColor, 1);
  con->colorWell1DZ = cmAllocColorWell1D(&(con->baseController), CML_COLOR_XYZ, con->XYZColor, 2);

  NABezel4 colorWellBezel = {20 + colorWell1DSize, 5, colorWell2DSize + 15, 5};
  cmBeginUILayout(con->baseController.space, colorWellBezel);
  cmAddUIPos(0, colorValueCondensedRowHeight);
  cmAddUIRow(con->labelX, colorValueCondensedRowHeight);
  cmAddUICol(con->textFieldX, colorComponentMarginH);
  cmAddUIRow(con->labelY, colorValueCondensedRowHeight);
  cmAddUICol(con->textFieldY, colorComponentMarginH);
  cmAddUIRow(con->labelZ, colorValueCondensedRowHeight);
  cmAddUICol(con->textFieldZ, colorComponentMarginH);
  cmAddUIPos(0, colorValueCondensedRowHeight);
  cmEndUILayout();
  
  naAddSpaceChild(
    con->baseController.space,
    cmGetColorWell2DUIElement(con->colorWell2D),
    naMakePos(10, 5));

  naAddSpaceChild(
    con->baseController.space,
    cmGetColorWell1DUIElement(con->colorWell1DX),
    naMakePos(colorWell1DMarginLeft, 70));
  naAddSpaceChild(
    con->baseController.space,
    cmGetColorWell1DUIElement(con->colorWell1DY),
    naMakePos(colorWell1DMarginLeft, 50));
  naAddSpaceChild(
    con->baseController.space,
    cmGetColorWell1DUIElement(con->colorWell1DZ),
    naMakePos(colorWell1DMarginLeft, 30));

  return con;
}



void cmDeallocXYZColorController(CMXYZColorController* con){
  cmClearColorController(&(con->baseController));
  naFree(con);
}



const void* cmGetXYZColorControllerColorData(const CMXYZColorController* con){
  return &(con->XYZColor);
}



void cmSetXYZColorControllerColorData(CMXYZColorController* con, const void* data){
  cmlCpy3(con->XYZColor, data);
}



void cmUpdateXYZColorController(CMXYZColorController* con){
  cmUpdateColorController(&(con->baseController));

  CMLColorMachine* cm = cmGetCurrentColorMachine();
  CMLColorType currentColorType = cmGetCurrentColorType();
  const float* currentColorData = cmGetCurrentColorData();
  CMLColorConverter converter = cmlGetColorConverter(CML_COLOR_XYZ, currentColorType);
  converter(cm, con->XYZColor, currentColorData, 1);
  
  cmUpdateColorWell2D(con->colorWell2D);

  naSetTextFieldText(
    con->textFieldX,
    naAllocSprintf(NA_TRUE, "%1.05f", con->XYZColor[0]));
  naSetTextFieldText(
    con->textFieldY,
    naAllocSprintf(NA_TRUE, "%1.05f", con->XYZColor[1]));
  naSetTextFieldText(
    con->textFieldZ,
    naAllocSprintf(NA_TRUE, "%1.05f", con->XYZColor[2]));

  cmUpdateColorWell1D(con->colorWell1DX);
  cmUpdateColorWell1D(con->colorWell1DY);
  cmUpdateColorWell1D(con->colorWell1DZ);
}
