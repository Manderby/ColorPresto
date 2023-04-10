
#include "CMColorController.h"

#include "../CMColorMachineApplication.h"
#include "../CMDesign.h"
#include "../CMTranslations.h"
#include "Displays/CMColorWell1D.h"
#include "Displays/CMColorWell2D.h"
#include "CMUVWColorController.h"

#include "NAApp.h"

struct CMUVWColorController{
  CMColorController baseController;
  
  CMColorWell2D* colorWell2D;

  NASpace* channelSpace;
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
    con->uvwColor[0] = (float)naGetTextFieldDouble(con->textFieldU);
  }else if(reaction.uiElement == con->textFieldV){
    con->uvwColor[1] = (float)naGetTextFieldDouble(con->textFieldV);
  }else if(reaction.uiElement == con->textFieldW){
    con->uvwColor[2] = (float)naGetTextFieldDouble(con->textFieldW);
  }
  
  cmSetCurrentColorController(&(con->baseController));
  cmUpdateColor();
  
  return NA_TRUE;
}



CMUVWColorController* cmAllocUVWColorController(void){
  CMUVWColorController* con = naAlloc(CMUVWColorController);
  
  cmInitColorController(&(con->baseController), CML_COLOR_UVW);
  
  con->colorWell2D = cmAllocColorWell2D(&(con->baseController), 2);

  con->channelSpace = naNewSpace(naMakeSize(1, 1));
  con->labelU = cmNewColorComponentLabel(cmTranslate(CMUVWColorChannelU));
  con->labelV = cmNewColorComponentLabel(cmTranslate(CMUVWColorChannelV));
  con->labelW = cmNewColorComponentLabel(cmTranslate(CMUVWColorChannelW));
  con->textFieldU = cmNewValueTextField(cmUVWValueEdited, con);
  con->textFieldV = cmNewValueTextField(cmUVWValueEdited, con);
  con->textFieldW = cmNewValueTextField(cmUVWValueEdited, con);
  con->colorWell1DU = cmAllocColorWell1D(&(con->baseController), con->uvwColor, 0);
  con->colorWell1DV = cmAllocColorWell1D(&(con->baseController), con->uvwColor, 1);
  con->colorWell1DW = cmAllocColorWell1D(&(con->baseController), con->uvwColor, 2);

  naSetUIElementNextTabElement(con->textFieldU, con->textFieldV);
  naSetUIElementNextTabElement(con->textFieldV, con->textFieldW);
  naSetUIElementNextTabElement(con->textFieldW, con->textFieldU);

  cmBeginUILayout(con->channelSpace, naMakeBezel4Zero());
  cmAddUIPos(0, (int)((colorWell2DSize - (3 * 25.)) / 2.)); // center the channels
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
  
  cmBeginUILayout(con->baseController.space, colorWellBezel);
  cmAddUIRow(cmGetColorWell2DUIElement(con->colorWell2D), 0);
  cmAddUICol(con->channelSpace, 10);
  cmEndUILayout();

  return con;
}



void cmDeallocUVWColorController(CMUVWColorController* con){
  cmDeallocColorWell2D(con->colorWell2D);
  cmDeallocColorWell1D(con->colorWell1DU);
  cmDeallocColorWell1D(con->colorWell1DV);
  cmDeallocColorWell1D(con->colorWell1DW);
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
