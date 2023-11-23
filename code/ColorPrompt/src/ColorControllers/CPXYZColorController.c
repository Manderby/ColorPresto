
#include "CPColorController.h"

#include "../CPColorPromptApplication.h"
#include "../CPDesign.h"
#include "../CPTranslations.h"
#include "Displays/CPColorWell1D.h"
#include "Displays/CPColorWell2D.h"
#include "CPXYZColorController.h"

#include "NAApp/NAApp.h"

struct CPXYZColorController{
  CPColorController baseController;
  
  CPColorWell2D* colorWell2D;

  NASpace* channelSpace;
  NALabel* labelX;
  NALabel* labelY;
  NALabel* labelZ;
  NATextField* textFieldX;
  NATextField* textFieldY;
  NATextField* textFieldZ;
  CPColorWell1D* colorWell1DX;
  CPColorWell1D* colorWell1DY;
  CPColorWell1D* colorWell1DZ;

  CMLVec3 XYZColor;
};



NABool cp_XYZValueEdited(NAReaction reaction){
  CPXYZColorController* con = (CPXYZColorController*)reaction.controller;
  
  if(reaction.uiElement == con->textFieldX){
    con->XYZColor[0] = (float)naGetTextFieldDouble(con->textFieldX);
  }else if(reaction.uiElement == con->textFieldY){
    con->XYZColor[1] = (float)naGetTextFieldDouble(con->textFieldY);
  }else if(reaction.uiElement == con->textFieldZ){
    con->XYZColor[2] = (float)naGetTextFieldDouble(con->textFieldZ);
  }
  
  cpSetCurrentColorController(&(con->baseController));
  cpUpdateColor();
  
  return NA_TRUE;
}



CPXYZColorController* cpAllocXYZColorController(void){
  CPXYZColorController* con = naAlloc(CPXYZColorController);
  
  cpInitColorController(&(con->baseController), CML_COLOR_XYZ);
  
  con->colorWell2D = cpAllocColorWell2D(&(con->baseController), 1);

  con->channelSpace = naNewSpace(naMakeSize(1, 1));
  con->labelX = cpNewColorComponentLabel(cpTranslate(CPXYZColorChannelX));
  con->labelY = cpNewColorComponentLabel(cpTranslate(CPXYZColorChannelY));
  con->labelZ = cpNewColorComponentLabel(cpTranslate(CPXYZColorChannelZ));
  con->textFieldX = cpNewValueTextField(cp_XYZValueEdited, con);
  con->textFieldY = cpNewValueTextField(cp_XYZValueEdited, con);
  con->textFieldZ = cpNewValueTextField(cp_XYZValueEdited, con);
  con->colorWell1DX = cpAllocColorWell1D(&(con->baseController), con->XYZColor, 0);
  con->colorWell1DY = cpAllocColorWell1D(&(con->baseController), con->XYZColor, 1);
  con->colorWell1DZ = cpAllocColorWell1D(&(con->baseController), con->XYZColor, 2);

  naSetUIElementNextTabElement(con->textFieldX, con->textFieldY);
  naSetUIElementNextTabElement(con->textFieldY, con->textFieldZ);
  naSetUIElementNextTabElement(con->textFieldZ, con->textFieldX);

  cpBeginUILayout(con->channelSpace, naMakeBezel4Zero());
  cpAddUIPos(0, (int)((colorWell2DSize - (3 * 25.)) / 2.)); // center the channels
  cpAddUIRow(con->labelX, colorValueCondensedRowHeight);
  cpAddUICol(con->textFieldX, colorComponentMarginH);
  cpAddUIColV(cpGetColorWell1DUIElement(con->colorWell1DX), 10, colorWell1DOffset);
  cpAddUIRow(con->labelY, colorValueCondensedRowHeight);
  cpAddUICol(con->textFieldY, colorComponentMarginH);
  cpAddUIColV(cpGetColorWell1DUIElement(con->colorWell1DY), 10, colorWell1DOffset);
  cpAddUIRow(con->labelZ, colorValueCondensedRowHeight);
  cpAddUICol(con->textFieldZ, colorComponentMarginH);
  cpAddUIColV(cpGetColorWell1DUIElement(con->colorWell1DZ), 10, colorWell1DOffset);
  cpAddUIPos(0, colorValueCondensedRowHeight);
  cpEndUILayout();
  
  cpBeginUILayout(con->baseController.space, colorWellBezel);
  cpAddUIRow(cpGetColorWell2DUIElement(con->colorWell2D), 0);
  cpAddUICol(con->channelSpace, colorWell2DRightMargin);
  cpEndUILayout();

  return con;
}



void cpDeallocXYZColorController(CPXYZColorController* con){
  cpDeallocColorWell2D(con->colorWell2D);
  cpDeallocColorWell1D(con->colorWell1DX);
  cpDeallocColorWell1D(con->colorWell1DY);
  cpDeallocColorWell1D(con->colorWell1DZ);
  cpClearColorController(&(con->baseController));
  naFree(con);
}



const void* cpGetXYZColorControllerColorData(const CPXYZColorController* con){
  return &(con->XYZColor);
}



void cpSetXYZColorControllerColorData(CPXYZColorController* con, const void* data){
  cmlCpy3(con->XYZColor, data);
}



void cpUpdateXYZColorController(CPXYZColorController* con){
  cpUpdateColorController(&(con->baseController));

  CMLColorMachine* cm = cpGetCurrentColorMachine();
  CMLColorType currentColorType = cpGetCurrentColorType();
  const float* currentColorData = cpGetCurrentColorData();
  CMLColorConverter converter = cmlGetColorConverter(CML_COLOR_XYZ, currentColorType);
  converter(cm, con->XYZColor, currentColorData, 1);
  
  cpUpdateColorWell2D(con->colorWell2D);

  naSetTextFieldText(
    con->textFieldX,
    naAllocSprintf(NA_TRUE, "%1.05f", con->XYZColor[0]));
  naSetTextFieldText(
    con->textFieldY,
    naAllocSprintf(NA_TRUE, "%1.05f", con->XYZColor[1]));
  naSetTextFieldText(
    con->textFieldZ,
    naAllocSprintf(NA_TRUE, "%1.05f", con->XYZColor[2]));

  cpUpdateColorWell1D(con->colorWell1DX);
  cpUpdateColorWell1D(con->colorWell1DY);
  cpUpdateColorWell1D(con->colorWell1DZ);
}
