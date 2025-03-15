
#include "CPColorController.h"

#include "../CPColorPrestoApplication.h"
#include "../CPDesign.h"
#include "../CPTranslations.h"
#include "Displays/CPColorWell1D.h"
#include "Displays/CPColorWell2D.h"
#include "CPYxyColorController.h"

#include "NAApp/NAApp.h"
#include "NAUtility/NAString.h"

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



void cp_YxyValueEdited(NAReaction reaction){
  CPYxyColorController* con = (CPYxyColorController*)reaction.controller;
  
  if(reaction.uiElement == con->textFieldY){
    con->yxyColor[0] = (float)naGetTextFieldDouble(con->textFieldY);
  }else if(reaction.uiElement == con->textFieldx){
    con->yxyColor[1] = (float)naGetTextFieldDouble(con->textFieldx);
  }else if(reaction.uiElement == con->textFieldy){
    con->yxyColor[2] = (float)naGetTextFieldDouble(con->textFieldy);
  }
  
  cpSetCurrentColorController(&(con->baseController));
  cpUpdateColor();
}



CPYxyColorController* cpAllocYxyColorController(void){
  CPYxyColorController* con = naAlloc(CPYxyColorController);
  
  cpInitColorController(&(con->baseController), CML_COLOR_Yxy);
  
  con->colorWell2D = cpAllocColorWell2D(&(con->baseController), 0);

  con->channelSpace = naNewSpace(naMakeSize(1, 1));
  con->labelY = cpNewColorComponentLabel(cpTranslate(CPYxyColorChannelY));
  con->labelx = cpNewColorComponentLabel(cpTranslate(CPYxyColorChannelx));
  con->labely = cpNewColorComponentLabel(cpTranslate(CPYxyColorChannely));
  con->textFieldY = cpNewValueTextField(cp_YxyValueEdited, con);
  con->textFieldx = cpNewValueTextField(cp_YxyValueEdited, con);
  con->textFieldy = cpNewValueTextField(cp_YxyValueEdited, con);
  con->colorWell1DY = cpAllocColorWell1D(&(con->baseController), con->yxyColor, 0);
  con->colorWell1Dx = cpAllocColorWell1D(&(con->baseController), con->yxyColor, 1);
  con->colorWell1Dy = cpAllocColorWell1D(&(con->baseController), con->yxyColor, 2);

  naSetUIElementNextTabElement(con->textFieldY, con->textFieldx);
  naSetUIElementNextTabElement(con->textFieldx, con->textFieldy);
  naSetUIElementNextTabElement(con->textFieldy, con->textFieldY);

  cpBeginUILayout(con->channelSpace, naMakeBorder2D(0., 0., 0., 0.));
  cpAddUIPos(0, (int)((colorWell2DSize - (3 * 25.)) / 2.)); // center the channels
  cpAddUIRow(con->labelY, colorValueCondensedRowHeight);
  cpAddUICol(con->textFieldY, colorComponentMarginH);
  cpAddUIColV(cpGetColorWell1DUIElement(con->colorWell1DY), 10, colorWell1DOffset);
  cpAddUIRow(con->labelx, colorValueCondensedRowHeight);
  cpAddUICol(con->textFieldx, colorComponentMarginH);
  cpAddUIColV(cpGetColorWell1DUIElement(con->colorWell1Dx), 10, colorWell1DOffset);
  cpAddUIRow(con->labely, colorValueCondensedRowHeight);
  cpAddUICol(con->textFieldy, colorComponentMarginH);
  cpAddUIColV(cpGetColorWell1DUIElement(con->colorWell1Dy), 10, colorWell1DOffset);
  cpAddUIPos(0, colorValueCondensedRowHeight);
  cpEndUILayout();
  
  cpBeginUILayout(con->baseController.space, colorWellBorder);
  cpAddUIRow(cpGetColorWell2DUIElement(con->colorWell2D), 0);
  cpAddUICol(con->channelSpace, colorWell2DRightMargin);
  cpEndUILayout();

  return con;
}



void cpDeallocYxyColorController(CPYxyColorController* con){
  cpDeallocColorWell2D(con->colorWell2D);
  cpDeallocColorWell1D(con->colorWell1DY);
  cpDeallocColorWell1D(con->colorWell1Dx);
  cpDeallocColorWell1D(con->colorWell1Dy);
  cpClearColorController(&(con->baseController));
  naFree(con);
}



const void* cpGetYxyColorControllerColorData(const CPYxyColorController* con){
  return &(con->yxyColor);
}



void cpSetYxyColorControllerColorData(CPYxyColorController* con, const void* data){
  cmlCpy3(con->yxyColor, data);
}



void cpComputeYxyColorController(CPYxyColorController* con) {
  CMLColorMachine* cm = cpGetCurrentColorMachine();

  CMLColorType currentColorType = cpGetCurrentColorType();
  const float* currentColorData = cpGetCurrentColorData();
  CMLColorConverter converter = cmlGetColorConverter(CML_COLOR_Yxy, currentColorType);
  converter(cm, con->yxyColor, currentColorData, 1);

  cpComputeColorWell2D(con->colorWell2D);
  cpComputeColorWell1D(con->colorWell1DY);
  cpComputeColorWell1D(con->colorWell1Dx);
  cpComputeColorWell1D(con->colorWell1Dy);
}



void cpUpdateYxyColorController(CPYxyColorController* con){
  cpUpdateColorWell2D(con->colorWell2D);

  naSetTextFieldText(
    con->textFieldY,
    naAllocSprintf(NA_TRUE, "%1.05f", con->yxyColor[0]));
  naSetTextFieldText(
    con->textFieldx,
    naAllocSprintf(NA_TRUE, "%1.05f", con->yxyColor[1]));
  naSetTextFieldText(
    con->textFieldy,
    naAllocSprintf(NA_TRUE, "%1.05f", con->yxyColor[2]));

  cpUpdateColorWell1D(con->colorWell1DY);
  cpUpdateColorWell1D(con->colorWell1Dx);
  cpUpdateColorWell1D(con->colorWell1Dy);
}
