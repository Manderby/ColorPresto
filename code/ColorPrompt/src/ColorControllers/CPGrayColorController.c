
#include "CPColorController.h"

#include "../CPColorPromptApplication.h"
#include "../CPDesign.h"
#include "../CPTranslations.h"
#include "CPGrayColorController.h"
#include "Displays/CPColorWell1D.h"
#include "Displays/CPGrayColorWell.h"

#include "NAApp.h"

struct CPGrayColorController{
  CPColorController baseController;
  
  CPGrayColorWell* display;
  
  NASpace* channelSpace;
  NALabel* labelGray;
  NATextField* textFieldGray;
  CPColorWell1D* colorWell1DGray;

  float grayColor;
};



NABool cmGrayValueEdited(NAReaction reaction){
  CPGrayColorController* con = (CPGrayColorController*)reaction.controller;
  
  if(reaction.uiElement == con->textFieldGray){
    con->grayColor = (float)naGetTextFieldDouble(con->textFieldGray);
  }
  
  cpSetCurrentColorController(&(con->baseController));
  cpUpdateColor();
  
  return NA_TRUE;
}



CPGrayColorController* cmAllocGrayColorController(void){
  CPGrayColorController* con = naAlloc(CPGrayColorController);
  
  cmInitColorController(&(con->baseController), CML_COLOR_Gray);
  
  con->display = cmAllocGrayColorWell(&(con->baseController));
  
  con->channelSpace = naNewSpace(naMakeSize(1, 1));
  con->labelGray = cpNewColorComponentLabel(cpTranslate(CPGrayColorChannelGr));
  con->textFieldGray = cpNewValueTextField(cmGrayValueEdited, con);
  con->colorWell1DGray = cmAllocColorWell1D(&(con->baseController), &(con->grayColor), 0);

  cpBeginUILayout(con->channelSpace, naMakeBezel4Zero());
  cpAddUIPos(0, (int)((colorWell2DSize - (1 * 25.)) / 2.)); // center the channels
  cpAddUIRow(con->labelGray, colorValueCondensedRowHeight);
  cpAddUICol(con->textFieldGray, colorComponentMarginH);
  cpAddUIColV(cmGetColorWell1DUIElement(con->colorWell1DGray), 10, colorWell1DOffset);
  cpAddUIPos(0, 2 * colorValueCondensedRowHeight);
  cpEndUILayout();
  
  cpBeginUILayout(con->baseController.space, colorWellBezel);
  cpAddUIRow(cmGetGrayColorWellUIElement(con->display), 0);
  cpAddUICol(con->channelSpace, colorWell2DRightMargin);
  cpEndUILayout();

  con->grayColor = .5;

  return con;
}



void cmDeallocGrayColorController(CPGrayColorController* con){
  cmDeallocGrayColorWell(con->display);
  cmDeallocColorWell1D(con->colorWell1DGray);
  cmClearColorController(&(con->baseController));
  naFree(con);
}



const void* cmGetGrayColorControllerColorData(const CPGrayColorController* con){
  return &(con->grayColor);
}



void cmSetGrayColorControllerColorData(CPGrayColorController* con, const void* data){
  con->grayColor = *(const float*)data;
}



void cmUpdateGrayColorController(CPGrayColorController* con){
  cpUpdateColorController(&(con->baseController));

  CMLColorMachine* cm = cpGetCurrentColorMachine();
  CMLColorType currentColorType = cpGetCurrentColorType();
  const float* currentColorData = cpGetCurrentColorData();
  CMLColorConverter converter = cmlGetColorConverter(CML_COLOR_Gray, currentColorType);
  converter(cm, &(con->grayColor), currentColorData, 1);
  
  naSetTextFieldText(
    con->textFieldGray,
    naAllocSprintf(NA_TRUE, "%1.05f", con->grayColor));

  cmUpdateGrayColorWell(con->display);
  cpUpdateColorWell1D(con->colorWell1DGray);
}
