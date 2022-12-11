
#include "CMColorController.h"

#include "../CMColorMachineApplication.h"
#include "../CMDesign.h"
#include "Displays/CMColorWell1D.h"
#include "Displays/CMColorWell2D.h"
#include "CMXYZColorController.h"

#include "NAApp.h"

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
    con->XYZColor[0] = (float)naGetTextFieldDouble(con->textFieldX);
  }else if(reaction.uiElement == con->textFieldY){
    con->XYZColor[1] = (float)naGetTextFieldDouble(con->textFieldY);
  }else if(reaction.uiElement == con->textFieldZ){
    con->XYZColor[2] = (float)naGetTextFieldDouble(con->textFieldZ);
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
  con->textFieldX = cmNewValueTextField(cmXYZValueEdited, con);
  con->textFieldY = cmNewValueTextField(cmXYZValueEdited, con);
  con->textFieldZ = cmNewValueTextField(cmXYZValueEdited, con);
  con->colorWell1DX = cmAllocColorWell1D(&(con->baseController), CML_COLOR_XYZ, con->XYZColor, 0);
  con->colorWell1DY = cmAllocColorWell1D(&(con->baseController), CML_COLOR_XYZ, con->XYZColor, 1);
  con->colorWell1DZ = cmAllocColorWell1D(&(con->baseController), CML_COLOR_XYZ, con->XYZColor, 2);

  naSetUIElementNextTabElement(con->textFieldX, con->textFieldY);
  naSetUIElementNextTabElement(con->textFieldY, con->textFieldZ);
  naSetUIElementNextTabElement(con->textFieldZ, con->textFieldX);

  cmBeginUILayout(con->baseController.space, colorWellBezel);
  cmAddUIPos(0, colorValueCondensedRowHeight);
  cmAddUIRow(con->labelX, colorValueCondensedRowHeight);
  cmAddUICol(con->textFieldX, colorComponentMarginH);
  cmAddUIColV(cmGetColorWell1DUIElement(con->colorWell1DX), 10, colorWell1DOffset);
  cmAddUIRow(con->labelY, colorValueCondensedRowHeight);
  cmAddUICol(con->textFieldY, colorComponentMarginH);
  cmAddUIColV(cmGetColorWell1DUIElement(con->colorWell1DY), 10, colorWell1DOffset);
  cmAddUIRow(con->labelZ, colorValueCondensedRowHeight);
  cmAddUICol(con->textFieldZ, colorComponentMarginH);
  cmAddUIColV(cmGetColorWell1DUIElement(con->colorWell1DZ), 10, colorWell1DOffset);
  cmAddUIPos(0, colorValueCondensedRowHeight);
  cmEndUILayout();
  
  naAddSpaceChild(
    con->baseController.space,
    cmGetColorWell2DUIElement(con->colorWell2D),
    naMakePos(10, 5));

  return con;
}



void cmDeallocXYZColorController(CMXYZColorController* con){
  cmDeallocColorWell2D(con->colorWell2D);
  cmDeallocColorWell1D(con->colorWell1DX);
  cmDeallocColorWell1D(con->colorWell1DY);
  cmDeallocColorWell1D(con->colorWell1DZ);
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
