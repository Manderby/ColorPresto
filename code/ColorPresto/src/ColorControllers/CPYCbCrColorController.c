
#include "CPColorController.h"

#include "../CPColorPrestoApplication.h"
#include "../CPDesign.h"
#include "../CPTranslations.h"
#include "Displays/CPColorWell1D.h"
#include "Displays/CPColorWell2D.h"
#include "CPYCbCrColorController.h"

#include "NAApp/NAApp.h"
#include "NAUtility/NAString.h"

struct CPYCbCrColorController{
  CPColorController baseController;
  
  CPColorWell2D* colorWell2D;

  NASpace* channelSpace;
  NALabel* labelY;
  NALabel* labelCb;
  NALabel* labelCr;
  NATextField* textFieldY;
  NATextField* textFieldCb;
  NATextField* textFieldCr;
  CPColorWell1D* colorWell1DY;
  CPColorWell1D* colorWell1DCb;
  CPColorWell1D* colorWell1DCr;

  CMLVec3 ycbcrColor;
};



void cp_YCbCrValueEdited(NAReaction reaction){
  CPYCbCrColorController* con = (CPYCbCrColorController*)reaction.controller;
  
  if(reaction.uiElement == con->textFieldY){
    con->ycbcrColor[0] = (float)naGetTextFieldDouble(con->textFieldY);
  }else if(reaction.uiElement == con->textFieldCb){
    con->ycbcrColor[1] = (float)naGetTextFieldDouble(con->textFieldCb);
  }else if(reaction.uiElement == con->textFieldCr){
    con->ycbcrColor[2] = (float)naGetTextFieldDouble(con->textFieldCr);
  }
  
  cpSetCurrentColorController(&(con->baseController));
  cpUpdateColor();
}



CPYCbCrColorController* cpAllocYCbCrColorController(void){
  CPYCbCrColorController* con = naAlloc(CPYCbCrColorController);
  
  cpInitColorController(&(con->baseController), CML_COLOR_YCbCr);
  
  con->colorWell2D = cpAllocColorWell2D(&(con->baseController), 0);

  con->channelSpace = naNewSpace(naMakeSize(1, 1));
  con->labelY = cpNewColorComponentLabel(cpTranslate(CPYCbCrColorChannelY));
  con->labelCb = cpNewColorComponentLabel(cpTranslate(CPYCbCrColorChannelCb));
  con->labelCr = cpNewColorComponentLabel(cpTranslate(CPYCbCrColorChannelCr));
  con->textFieldY = cpNewValueTextField(cp_YCbCrValueEdited, con);
  con->textFieldCb = cpNewValueTextField(cp_YCbCrValueEdited, con);
  con->textFieldCr = cpNewValueTextField(cp_YCbCrValueEdited, con);
  con->colorWell1DY = cpAllocColorWell1D(&(con->baseController), con->ycbcrColor, 0);
  con->colorWell1DCb = cpAllocColorWell1D(&(con->baseController), con->ycbcrColor, 1);
  con->colorWell1DCr = cpAllocColorWell1D(&(con->baseController), con->ycbcrColor, 2);

  naSetUIElementNextTabElement(con->textFieldY, con->textFieldCb);
  naSetUIElementNextTabElement(con->textFieldCb, con->textFieldCr);
  naSetUIElementNextTabElement(con->textFieldCr, con->textFieldY);

  cpBeginUILayout(con->channelSpace, naMakeBorder2D(0., 0., 0., 0.));
  cpAddUIPos(0, (int)((colorWell2DSize - (3 * 25.)) / 2.)); // center the channels
  cpAddUIRow(con->labelY, colorValueCondensedRowHeight);
  cpAddUICol(con->textFieldY, colorComponentMarginH);
  cpAddUIColV(cpGetColorWell1DUIElement(con->colorWell1DY), 10, colorWell1DOffset);
  cpAddUIRow(con->labelCb, colorValueCondensedRowHeight);
  cpAddUICol(con->textFieldCb, colorComponentMarginH);
  cpAddUIColV(cpGetColorWell1DUIElement(con->colorWell1DCb), 10, colorWell1DOffset);
  cpAddUIRow(con->labelCr, colorValueCondensedRowHeight);
  cpAddUICol(con->textFieldCr, colorComponentMarginH);
  cpAddUIColV(cpGetColorWell1DUIElement(con->colorWell1DCr), 10, colorWell1DOffset);
  cpAddUIPos(0, colorValueCondensedRowHeight);
  cpEndUILayout();
  
  cpBeginUILayout(con->baseController.space, colorWellBorder);
  cpAddUIRow(cpGetColorWell2DUIElement(con->colorWell2D), 0);
  cpAddUICol(con->channelSpace, colorWell2DRightMargin);
  cpEndUILayout();

  return con;
}



void cpDeallocYCbCrColorController(CPYCbCrColorController* con){
  cpDeallocColorWell2D(con->colorWell2D);
  cpDeallocColorWell1D(con->colorWell1DY);
  cpDeallocColorWell1D(con->colorWell1DCb);
  cpDeallocColorWell1D(con->colorWell1DCr);
  cpClearColorController(&(con->baseController));
  naFree(con);
}



const void* cpGetYCbCrColorControllerColorData(const CPYCbCrColorController* con){
  return &(con->ycbcrColor);
}



void cpSetYCbCrColorControllerColorData(CPYCbCrColorController* con, const void* data){
  cmlCpy3(con->ycbcrColor, data);
}



void cpComputeYCbCrColorController(CPYCbCrColorController* con) {
  CMLColorMachine* cm = cpGetCurrentColorMachine();

  CMLColorType currentColorType = cpGetCurrentColorType();
  const float* currentColorData = cpGetCurrentColorData();
  CMLColorConverter converter = cmlGetColorConverter(CML_COLOR_YCbCr, currentColorType);
  converter(cm, con->ycbcrColor, currentColorData, 1);

  cpComputeColorWell2D(con->colorWell2D);
  cpComputeColorWell1D(con->colorWell1DY);
  cpComputeColorWell1D(con->colorWell1DCb);
  cpComputeColorWell1D(con->colorWell1DCr);
}



void cpUpdateYCbCrColorController(CPYCbCrColorController* con){
  cpUpdateColorWell2D(con->colorWell2D);

  naSetTextFieldText(
    con->textFieldY,
    naAllocSprintf(NA_TRUE, "%1.05f", con->ycbcrColor[0]));
  naSetTextFieldText(
    con->textFieldCb,
    naAllocSprintf(NA_TRUE, "%1.04f", con->ycbcrColor[1]));
  naSetTextFieldText(
    con->textFieldCr,
    naAllocSprintf(NA_TRUE, "%1.04f", con->ycbcrColor[2]));

  cpUpdateColorWell1D(con->colorWell1DY);
  cpUpdateColorWell1D(con->colorWell1DCb);
  cpUpdateColorWell1D(con->colorWell1DCr);
}
