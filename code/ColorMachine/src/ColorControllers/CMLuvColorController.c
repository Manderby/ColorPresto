
#include "CMColorController.h"

#include "../CMColorMachineApplication.h"
#include "../CMDesign.h"
#include "../CMTranslations.h"
#include "Displays/CMColorWell1D.h"
#include "Displays/CMColorWell2D.h"
#include "CMLuvColorController.h"

#include "NAApp.h"

struct CMLuvColorController{
  CMColorController baseController;
  
  CMColorWell2D* colorWell2D;

  NASpace* channelSpace;
  NALabel* labelL;
  NALabel* labelu;
  NALabel* labelv;
  NATextField* textFieldL;
  NATextField* textFieldu;
  NATextField* textFieldv;
  CMColorWell1D* colorWell1DL;
  CMColorWell1D* colorWell1Du;
  CMColorWell1D* colorWell1Dv;

  CMLVec3 luvColor;
};



NABool cmLuvValueEdited(NAReaction reaction){
  CMLuvColorController* con = (CMLuvColorController*)reaction.controller;
  
  if(reaction.uiElement == con->textFieldL){
    con->luvColor[0] = (float)naGetTextFieldDouble(con->textFieldL);
  }else if(reaction.uiElement == con->textFieldu){
    con->luvColor[1] = (float)naGetTextFieldDouble(con->textFieldu);
  }else if(reaction.uiElement == con->textFieldv){
    con->luvColor[2] = (float)naGetTextFieldDouble(con->textFieldv);
  }
  
  cmSetCurrentColorController(&(con->baseController));
  cmUpdateColor();
  
  return NA_TRUE;
}



CMLuvColorController* cmAllocLuvColorController(void){
  CMLuvColorController* con = naAlloc(CMLuvColorController);
  
  cmInitColorController(&(con->baseController), CML_COLOR_Luv);
  
  con->colorWell2D = cmAllocColorWell2D(&(con->baseController), 0);

  con->channelSpace = naNewSpace(naMakeSize(1, 1));
  con->labelL = cmNewColorComponentLabel(cmTranslate(CMLuvColorChannelL));
  con->labelu = cmNewColorComponentLabel(cmTranslate(CMLuvColorChannelu));
  con->labelv = cmNewColorComponentLabel(cmTranslate(CMLuvColorChannelv));
  con->textFieldL = cmNewValueTextField(cmLuvValueEdited, con);
  con->textFieldu = cmNewValueTextField(cmLuvValueEdited, con);
  con->textFieldv = cmNewValueTextField(cmLuvValueEdited, con);
  con->colorWell1DL = cmAllocColorWell1D(&(con->baseController), con->luvColor, 0);
  con->colorWell1Du = cmAllocColorWell1D(&(con->baseController), con->luvColor, 1);
  con->colorWell1Dv = cmAllocColorWell1D(&(con->baseController), con->luvColor, 2);

  naSetUIElementNextTabElement(con->textFieldL, con->textFieldu);
  naSetUIElementNextTabElement(con->textFieldu, con->textFieldv);
  naSetUIElementNextTabElement(con->textFieldv, con->textFieldL);

  cmBeginUILayout(con->channelSpace, naMakeBezel4Zero());
  cmAddUIPos(0, (int)((colorWell2DSize - (3 * 25.)) / 2.)); // center the channels
  cmAddUIRow(con->labelL, colorValueCondensedRowHeight);
  cmAddUICol(con->textFieldL, colorComponentMarginH);
  cmAddUIColV(cmGetColorWell1DUIElement(con->colorWell1DL), 10, colorWell1DOffset);
  cmAddUIRow(con->labelu, colorValueCondensedRowHeight);
  cmAddUICol(con->textFieldu, colorComponentMarginH);
  cmAddUIColV(cmGetColorWell1DUIElement(con->colorWell1Du), 10, colorWell1DOffset);
  cmAddUIRow(con->labelv, colorValueCondensedRowHeight);
  cmAddUICol(con->textFieldv, colorComponentMarginH);
  cmAddUIColV(cmGetColorWell1DUIElement(con->colorWell1Dv), 10, colorWell1DOffset);
  cmAddUIPos(0, colorValueCondensedRowHeight);
  cmEndUILayout();
  
  cmBeginUILayout(con->baseController.space, colorWellBezel);
  cmAddUIRow(cmGetColorWell2DUIElement(con->colorWell2D), 0);
  cmAddUICol(con->channelSpace, 10);
  cmEndUILayout();

  return con;
}



void cmDeallocLuvColorController(CMLuvColorController* con){
  cmDeallocColorWell2D(con->colorWell2D);
  cmDeallocColorWell1D(con->colorWell1DL);
  cmDeallocColorWell1D(con->colorWell1Du);
  cmDeallocColorWell1D(con->colorWell1Dv);
  cmClearColorController(&(con->baseController));
  naFree(con);
}



const void* cmGetLuvColorControllerColorData(const CMLuvColorController* con){
  return &(con->luvColor);
}



void cmSetLuvColorControllerColorData(CMLuvColorController* con, const void* data){
  cmlCpy3(con->luvColor, data);
}



void cmUpdateLuvColorController(CMLuvColorController* con){
  cmUpdateColorController(&(con->baseController));

  CMLColorMachine* cm = cmGetCurrentColorMachine();
  CMLColorType currentColorType = cmGetCurrentColorType();
  const float* currentColorData = cmGetCurrentColorData();
  CMLColorConverter converter = cmlGetColorConverter(CML_COLOR_Luv, currentColorType);
  converter(cm, con->luvColor, currentColorData, 1);
  
  cmUpdateColorWell2D(con->colorWell2D);

  naSetTextFieldText(
    con->textFieldL,
    naAllocSprintf(NA_TRUE, "%3.03f", con->luvColor[0]));
  naSetTextFieldText(
    con->textFieldu,
    naAllocSprintf(NA_TRUE, "%3.02f", con->luvColor[1]));
  naSetTextFieldText(
    con->textFieldv,
    naAllocSprintf(NA_TRUE, "%3.02f", con->luvColor[2]));

  cmUpdateColorWell1D(con->colorWell1DL);
  cmUpdateColorWell1D(con->colorWell1Du);
  cmUpdateColorWell1D(con->colorWell1Dv);
}
