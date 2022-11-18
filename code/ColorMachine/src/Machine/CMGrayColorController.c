
#include "CMColorController.h"
#include "CMColorWell1D.h"
#include "CMGrayColorController.h"
#include "NAApp.h"
#include "CMDesign.h"

struct CMGrayColorController{
  CMColorController baseController;
  
  NALabel* labelGray;
  NATextField* textFieldGray;
  CMColorWell1D* colorWell1DGray;

  float grayColor;
};



NABool cmGrayValueEdited(NAReaction reaction){
  CMGrayColorController* con = (CMGrayColorController*)reaction.controller;
  
  if(reaction.uiElement == con->textFieldGray){
    NAString* string = naNewStringWithTextFieldText(con->textFieldGray);
    con->grayColor = atof(naGetStringUTF8Pointer(string));
    naDelete(string);
  }
  
  cmSetCurrentColorController(&(con->baseController));
  cmUpdateColor();
  
  return NA_TRUE;
}



CMGrayColorController* cmAllocGrayColorController(void){
  CMGrayColorController* con = naAlloc(CMGrayColorController);
  
  cmInitColorController(&(con->baseController), CML_COLOR_Gray);
  
  con->labelGray = cmNewColorComponentLabel("Gray");
  con->textFieldGray = cmNewValueTextField(cmGrayValueEdited, con);
  con->colorWell1DGray = cmAllocColorWell1D(&(con->baseController), CML_COLOR_Gray, &(con->grayColor), 0);

  cmBeginUILayout(con->baseController.space, colorWellBezel);
  cmAddUIPos(0, 2 * colorValueCondensedRowHeight);
  cmAddUIRow(con->labelGray, colorValueCondensedRowHeight);
  cmAddUICol(con->textFieldGray, colorComponentMarginH);
  cmAddUIColV(cmGetColorWell1DUIElement(con->colorWell1DGray), 10, colorWell1DOffset);
  cmAddUIPos(0, 2 * colorValueCondensedRowHeight);
  cmEndUILayout();
  
//  naAddSpaceChild(
//    con->baseController.space,
//    cmGetColorWell2DUIElement(con->colorWell2D),
//    naMakePos(10, 5));

  return con;
}



void cmDeallocGrayColorController(CMGrayColorController* con){
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

  cmUpdateColorWell1D(con->colorWell1DGray);
}
