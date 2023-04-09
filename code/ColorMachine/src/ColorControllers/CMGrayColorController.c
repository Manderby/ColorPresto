
#include "CMColorController.h"

#include "../CMColorMachineApplication.h"
#include "../CMDesign.h"
#include "../CMTranslations.h"
#include "CMGrayColorController.h"
#include "Displays/CMColorWell1D.h"
#include "Displays/CMGrayColorWell.h"

#include "NAApp.h"

struct CMGrayColorController{
  CMColorController baseController;
  
  CMGrayColorWell* display;
  
  NASpace* channelSpace;
  NALabel* labelGray;
  NATextField* textFieldGray;
  CMColorWell1D* colorWell1DGray;

  float grayColor;
};



NABool cmGrayValueEdited(NAReaction reaction){
  CMGrayColorController* con = (CMGrayColorController*)reaction.controller;
  
  if(reaction.uiElement == con->textFieldGray){
    con->grayColor = (float)naGetTextFieldDouble(con->textFieldGray);
  }
  
  cmSetCurrentColorController(&(con->baseController));
  cmUpdateColor();
  
  return NA_TRUE;
}



CMGrayColorController* cmAllocGrayColorController(void){
  CMGrayColorController* con = naAlloc(CMGrayColorController);
  
  cmInitColorController(&(con->baseController), CML_COLOR_Gray);
  
  con->display = cmAllocGrayColorWell(&(con->baseController));
  
  con->channelSpace = naNewSpace(naMakeSize(1, 1));
  con->labelGray = cmNewColorComponentLabel(cmTranslate(CMGrayColorChannelGr));
  con->textFieldGray = cmNewValueTextField(cmGrayValueEdited, con);
  con->colorWell1DGray = cmAllocColorWell1D(&(con->baseController), CML_COLOR_Gray, &(con->grayColor), 0);

  cmBeginUILayout(con->channelSpace, naMakeBezel4Zero());
  cmAddUIPos(0, (int)((colorWell2DSize - (1 * 25.)) / 2.)); // center the channels
  cmAddUIRow(con->labelGray, colorValueCondensedRowHeight);
  cmAddUICol(con->textFieldGray, colorComponentMarginH);
  cmAddUIColV(cmGetColorWell1DUIElement(con->colorWell1DGray), 10, colorWell1DOffset);
  cmAddUIPos(0, 2 * colorValueCondensedRowHeight);
  cmEndUILayout();
  
  cmBeginUILayout(con->baseController.space, colorWellBezel);
  cmAddUIRow(cmGetGrayColorWellUIElement(con->display), 0);
  cmAddUICol(con->channelSpace, 10);
  cmEndUILayout();

  con->grayColor = .5;

  return con;
}



void cmDeallocGrayColorController(CMGrayColorController* con){
  cmDeallocGrayColorWell(con->display);
  cmDeallocColorWell1D(con->colorWell1DGray);
  cmClearColorController(&(con->baseController));
  naFree(con);
}



const void* cmGetGrayColorControllerColorData(const CMGrayColorController* con){
  return &(con->grayColor);
}



void cmSetGrayColorControllerColorData(CMGrayColorController* con, const void* data){
  con->grayColor = *(const float*)data;
}



void cmUpdateGrayColorController(CMGrayColorController* con){
  cmUpdateColorController(&(con->baseController));

  CMLColorMachine* cm = cmGetCurrentColorMachine();
  CMLColorType currentColorType = cmGetCurrentColorType();
  const float* currentColorData = cmGetCurrentColorData();
  CMLColorConverter converter = cmlGetColorConverter(CML_COLOR_Gray, currentColorType);
  converter(cm, &(con->grayColor), currentColorData, 1);
  
  naSetTextFieldText(
    con->textFieldGray,
    naAllocSprintf(NA_TRUE, "%1.05f", con->grayColor));

  cmUpdateGrayColorWell(con->display);
  cmUpdateColorWell1D(con->colorWell1DGray);
}
