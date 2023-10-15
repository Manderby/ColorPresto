
#include "CPColorController.h"

#include "../CPColorPromptApplication.h"
#include "../CPDesign.h"
#include "../CPTranslations.h"
#include "Displays/CPColorWell1D.h"
#include "Displays/CPColorWell2D.h"
#include "CPYxyColorController.h"

#include "NAApp.h"

struct CPYxyColorController{
  CPColorController baseController;
  
  CPColorWell2D* colorWell2D;

  NASpace* channelSpace;
  NALabel* labelY;
  NALabel* labelx;
  NALabel* labely;
  NATextField* textFieldY;
  NATextField* textFieldx;
  NATextField* textFieldy;
  CPColorWell1D* colorWell1DY;
  CPColorWell1D* colorWell1Dx;
  CPColorWell1D* colorWell1Dy;

  CMLVec3 yxyColor;
};



NABool cmYxyValueEdited(NAReaction reaction){
  CPYxyColorController* con = (CPYxyColorController*)reaction.controller;
  
  if(reaction.uiElement == con->textFieldY){
    con->yxyColor[0] = (float)naGetTextFieldDouble(con->textFieldY);
  }else if(reaction.uiElement == con->textFieldx){
    con->yxyColor[1] = (float)naGetTextFieldDouble(con->textFieldx);
  }else if(reaction.uiElement == con->textFieldy){
    con->yxyColor[2] = (float)naGetTextFieldDouble(con->textFieldy);
  }
  
  cmSetCurrentColorController(&(con->baseController));
  cmUpdateColor();
  
  return NA_TRUE;
}



CPYxyColorController* cmAllocYxyColorController(void){
  CPYxyColorController* con = naAlloc(CPYxyColorController);
  
  cmInitColorController(&(con->baseController), CML_COLOR_Yxy);
  
  con->colorWell2D = cmAllocColorWell2D(&(con->baseController), 0);

  con->channelSpace = naNewSpace(naMakeSize(1, 1));
  con->labelY = cmNewColorComponentLabel(cmTranslate(CMYxyColorChannelY));
  con->labelx = cmNewColorComponentLabel(cmTranslate(CMYxyColorChannelx));
  con->labely = cmNewColorComponentLabel(cmTranslate(CMYxyColorChannely));
  con->textFieldY = cmNewValueTextField(cmYxyValueEdited, con);
  con->textFieldx = cmNewValueTextField(cmYxyValueEdited, con);
  con->textFieldy = cmNewValueTextField(cmYxyValueEdited, con);
  con->colorWell1DY = cmAllocColorWell1D(&(con->baseController), con->yxyColor, 0);
  con->colorWell1Dx = cmAllocColorWell1D(&(con->baseController), con->yxyColor, 1);
  con->colorWell1Dy = cmAllocColorWell1D(&(con->baseController), con->yxyColor, 2);

  naSetUIElementNextTabElement(con->textFieldY, con->textFieldx);
  naSetUIElementNextTabElement(con->textFieldx, con->textFieldy);
  naSetUIElementNextTabElement(con->textFieldy, con->textFieldY);

  cmBeginUILayout(con->channelSpace, naMakeBezel4Zero());
  cmAddUIPos(0, (int)((colorWell2DSize - (3 * 25.)) / 2.)); // center the channels
  cmAddUIRow(con->labelY, colorValueCondensedRowHeight);
  cmAddUICol(con->textFieldY, colorComponentMarginH);
  cmAddUIColV(cmGetColorWell1DUIElement(con->colorWell1DY), 10, colorWell1DOffset);
  cmAddUIRow(con->labelx, colorValueCondensedRowHeight);
  cmAddUICol(con->textFieldx, colorComponentMarginH);
  cmAddUIColV(cmGetColorWell1DUIElement(con->colorWell1Dx), 10, colorWell1DOffset);
  cmAddUIRow(con->labely, colorValueCondensedRowHeight);
  cmAddUICol(con->textFieldy, colorComponentMarginH);
  cmAddUIColV(cmGetColorWell1DUIElement(con->colorWell1Dy), 10, colorWell1DOffset);
  cmAddUIPos(0, colorValueCondensedRowHeight);
  cmEndUILayout();
  
  cmBeginUILayout(con->baseController.space, colorWellBezel);
  cmAddUIRow(cmGetColorWell2DUIElement(con->colorWell2D), 0);
  cmAddUICol(con->channelSpace, colorWell2DRightMargin);
  cmEndUILayout();

  return con;
}



void cmDeallocYxyColorController(CPYxyColorController* con){
  cmDeallocColorWell2D(con->colorWell2D);
  cmDeallocColorWell1D(con->colorWell1DY);
  cmDeallocColorWell1D(con->colorWell1Dx);
  cmDeallocColorWell1D(con->colorWell1Dy);
  cmClearColorController(&(con->baseController));
  naFree(con);
}



const void* cmGetYxyColorControllerColorData(const CPYxyColorController* con){
  return &(con->yxyColor);
}



void cmSetYxyColorControllerColorData(CPYxyColorController* con, const void* data){
  cmlCpy3(con->yxyColor, data);
}



void cmUpdateYxyColorController(CPYxyColorController* con){
  cmUpdateColorController(&(con->baseController));

  CMLColorMachine* cm = cmGetCurrentColorMachine();
  CMLColorType currentColorType = cmGetCurrentColorType();
  const float* currentColorData = cmGetCurrentColorData();
  CMLColorConverter converter = cmlGetColorConverter(CML_COLOR_Yxy, currentColorType);
  converter(cm, con->yxyColor, currentColorData, 1);
  
  cmUpdateColorWell2D(con->colorWell2D);

  naSetTextFieldText(
    con->textFieldY,
    naAllocSprintf(NA_TRUE, "%1.05f", con->yxyColor[0]));
  naSetTextFieldText(
    con->textFieldx,
    naAllocSprintf(NA_TRUE, "%1.05f", con->yxyColor[1]));
  naSetTextFieldText(
    con->textFieldy,
    naAllocSprintf(NA_TRUE, "%1.05f", con->yxyColor[2]));

  cmUpdateColorWell1D(con->colorWell1DY);
  cmUpdateColorWell1D(con->colorWell1Dx);
  cmUpdateColorWell1D(con->colorWell1Dy);
}
