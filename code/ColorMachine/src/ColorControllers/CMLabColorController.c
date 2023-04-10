
#include "CMColorController.h"

#include "../CMColorMachineApplication.h"
#include "../CMDesign.h"
#include "../CMTranslations.h"
#include "Displays/CMColorWell1D.h"
#include "Displays/CMColorWell2D.h"
#include "CMLabColorController.h"

#include "NAApp.h"

struct CMLabColorController{
  CMColorController baseController;
  
  CMColorWell2D* colorWell2D;

  NASpace* channelSpace;
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
    con->labColor[0] = (float)naGetTextFieldDouble(con->textFieldL);
  }else if(reaction.uiElement == con->textFielda){
    con->labColor[1] = (float)naGetTextFieldDouble(con->textFielda);
  }else if(reaction.uiElement == con->textFieldb){
    con->labColor[2] = (float)naGetTextFieldDouble(con->textFieldb);
  }else if(reaction.uiElement == con->textFieldc){
    con->lchColor[1] = (float)naGetTextFieldDouble(con->textFieldc);
    cmlConvertLchToLab(con->labColor, con->lchColor);
  }else if(reaction.uiElement == con->textFieldh){
    con->lchColor[2] = (float)naGetTextFieldDouble(con->textFieldh);
    cmlConvertLchToLab(con->labColor, con->lchColor);
  }
  
  cmSetCurrentColorController(&(con->baseController));
  cmUpdateColor();
  
  return NA_TRUE;
}



CMLabColorController* cmAllocLabColorController(void){
  CMLabColorController* con = naAlloc(CMLabColorController);
  
  cmInitColorController(&(con->baseController), CML_COLOR_Lab);
  
  con->colorWell2D = cmAllocColorWell2D(&(con->baseController), 0);

  con->channelSpace = naNewSpace(naMakeSize(1, 1));
  con->labelL = cmNewColorComponentLabel("");
  con->labela = cmNewColorComponentLabel("");
  con->labelb = cmNewColorComponentLabel("");
  con->labelc = cmNewColorComponentLabel(cmTranslate(CMLchColorChannelc));
  con->labelh = cmNewColorComponentLabel(cmTranslate(CMLchColorChannelh));
  con->textFieldL = cmNewValueTextField(cmLabValueEdited, con);
  con->textFielda = cmNewValueTextField(cmLabValueEdited, con);
  con->textFieldb = cmNewValueTextField(cmLabValueEdited, con);
  con->textFieldc = cmNewValueTextField(cmLabValueEdited, con);
  con->textFieldh = cmNewValueTextField(cmLabValueEdited, con);
  con->colorWell1DL = cmAllocColorWell1D(&(con->baseController), con->labColor, 0);
  con->colorWell1Da = cmAllocColorWell1D(&(con->baseController), con->labColor, 1);
  con->colorWell1Db = cmAllocColorWell1D(&(con->baseController), con->labColor, 2);
  con->colorWell1Dc = cmAllocColorWell1D(&(con->baseController), con->lchColor, 1);
  con->colorWell1Dh = cmAllocColorWell1D(&(con->baseController), con->lchColor, 2);

  naSetUIElementNextTabElement(con->textFieldL, con->textFielda);
  naSetUIElementNextTabElement(con->textFielda, con->textFieldb);
  naSetUIElementNextTabElement(con->textFieldb, con->textFieldc);
  naSetUIElementNextTabElement(con->textFieldc, con->textFieldh);
  naSetUIElementNextTabElement(con->textFieldh, con->textFieldL);

  cmBeginUILayout(con->channelSpace, naMakeBezel4Zero());
  cmAddUIPos(0, (int)((colorWell2DSize - (5 * 25.)) / 2.)); // center the channels
  cmAddUIRow(con->labelL, colorValueCondensedRowHeight);
  cmAddUICol(con->textFieldL, colorComponentMarginH);
  cmAddUIColV(cmGetColorWell1DUIElement(con->colorWell1DL), 10, colorWell1DOffset);
  cmAddUIRow(con->labela, colorValueCondensedRowHeight);
  cmAddUICol(con->textFielda, colorComponentMarginH);
  cmAddUIColV(cmGetColorWell1DUIElement(con->colorWell1Da), 10, colorWell1DOffset);
  cmAddUIRow(con->labelb, colorValueCondensedRowHeight);
  cmAddUICol(con->textFieldb, colorComponentMarginH);
  cmAddUIColV(cmGetColorWell1DUIElement(con->colorWell1Db), 10, colorWell1DOffset);
  cmAddUIRow(con->labelc, colorValueCondensedRowHeight);
  cmAddUICol(con->textFieldc, colorComponentMarginH);
  cmAddUIColV(cmGetColorWell1DUIElement(con->colorWell1Dc), 10, colorWell1DOffset);
  cmAddUIRow(con->labelh, colorValueCondensedRowHeight);
  cmAddUICol(con->textFieldh, colorComponentMarginH);
  cmAddUIColV(cmGetColorWell1DUIElement(con->colorWell1Dh), 10, colorWell1DOffset);
  cmEndUILayout();
  
  cmBeginUILayout(con->baseController.space, colorWellBezel);
  cmAddUIRow(cmGetColorWell2DUIElement(con->colorWell2D), 0);
  cmAddUICol(con->channelSpace, 10);
  cmEndUILayout();

  return con;
}



void cmDeallocLabColorController(CMLabColorController* con){
  cmDeallocColorWell2D(con->colorWell2D);
  cmDeallocColorWell1D(con->colorWell1DL);
  cmDeallocColorWell1D(con->colorWell1Da);
  cmDeallocColorWell1D(con->colorWell1Db);
  cmDeallocColorWell1D(con->colorWell1Dc);
  cmDeallocColorWell1D(con->colorWell1Dh);
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
    naSetLabelText(con->labelL, cmTranslate(CMLabColorChannelLStar));
    naSetLabelText(con->labela, cmTranslate(CMLabColorChannelaStar));
    naSetLabelText(con->labelb, cmTranslate(CMLabColorChannelbStar));
    break;
  default:
    naSetLabelText(con->labelL, cmTranslate(CMLabColorChannelL));
    naSetLabelText(con->labela, cmTranslate(CMLabColorChannela));
    naSetLabelText(con->labelb, cmTranslate(CMLabColorChannelb));
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
