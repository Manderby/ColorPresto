
#include "CPColorController.h"

#include "../CPColorPromptApplication.h"
#include "../CPDesign.h"
#include "../CPTranslations.h"
#include "Displays/CPColorWell1D.h"
#include "Displays/CPColorWell2D.h"
#include "CPYCbCrColorController.h"

#include "NAApp.h"

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



NABool cmYCbCrValueEdited(NAReaction reaction){
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
  
  return NA_TRUE;
}



CPYCbCrColorController* cmAllocYCbCrColorController(void){
  CPYCbCrColorController* con = naAlloc(CPYCbCrColorController);
  
  cmInitColorController(&(con->baseController), CML_COLOR_YCbCr);
  
  con->colorWell2D = cmAllocColorWell2D(&(con->baseController), 0);

  con->channelSpace = naNewSpace(naMakeSize(1, 1));
  con->labelY = cpNewColorComponentLabel(cpTranslate(CPYCbCrColorChannelY));
  con->labelCb = cpNewColorComponentLabel(cpTranslate(CPYCbCrColorChannelCb));
  con->labelCr = cpNewColorComponentLabel(cpTranslate(CPYCbCrColorChannelCr));
  con->textFieldY = cpNewValueTextField(cmYCbCrValueEdited, con);
  con->textFieldCb = cpNewValueTextField(cmYCbCrValueEdited, con);
  con->textFieldCr = cpNewValueTextField(cmYCbCrValueEdited, con);
  con->colorWell1DY = cmAllocColorWell1D(&(con->baseController), con->ycbcrColor, 0);
  con->colorWell1DCb = cmAllocColorWell1D(&(con->baseController), con->ycbcrColor, 1);
  con->colorWell1DCr = cmAllocColorWell1D(&(con->baseController), con->ycbcrColor, 2);

  naSetUIElementNextTabElement(con->textFieldY, con->textFieldCb);
  naSetUIElementNextTabElement(con->textFieldCb, con->textFieldCr);
  naSetUIElementNextTabElement(con->textFieldCr, con->textFieldY);

  cpBeginUILayout(con->channelSpace, naMakeBezel4Zero());
  cpAddUIPos(0, (int)((colorWell2DSize - (3 * 25.)) / 2.)); // center the channels
  cpAddUIRow(con->labelY, colorValueCondensedRowHeight);
  cpAddUICol(con->textFieldY, colorComponentMarginH);
  cpAddUIColV(cmGetColorWell1DUIElement(con->colorWell1DY), 10, colorWell1DOffset);
  cpAddUIRow(con->labelCb, colorValueCondensedRowHeight);
  cpAddUICol(con->textFieldCb, colorComponentMarginH);
  cpAddUIColV(cmGetColorWell1DUIElement(con->colorWell1DCb), 10, colorWell1DOffset);
  cpAddUIRow(con->labelCr, colorValueCondensedRowHeight);
  cpAddUICol(con->textFieldCr, colorComponentMarginH);
  cpAddUIColV(cmGetColorWell1DUIElement(con->colorWell1DCr), 10, colorWell1DOffset);
  cpAddUIPos(0, colorValueCondensedRowHeight);
  cpEndUILayout();
  
  cpBeginUILayout(con->baseController.space, colorWellBezel);
  cpAddUIRow(cmGetColorWell2DUIElement(con->colorWell2D), 0);
  cpAddUICol(con->channelSpace, colorWell2DRightMargin);
  cpEndUILayout();

  return con;
}



void cmDeallocYCbCrColorController(CPYCbCrColorController* con){
  cmDeallocColorWell2D(con->colorWell2D);
  cmDeallocColorWell1D(con->colorWell1DY);
  cmDeallocColorWell1D(con->colorWell1DCb);
  cmDeallocColorWell1D(con->colorWell1DCr);
  cmClearColorController(&(con->baseController));
  naFree(con);
}



const void* cmGetYCbCrColorControllerColorData(const CPYCbCrColorController* con){
  return &(con->ycbcrColor);
}



void cmSetYCbCrColorControllerColorData(CPYCbCrColorController* con, const void* data){
  cmlCpy3(con->ycbcrColor, data);
}



void cmUpdateYCbCrColorController(CPYCbCrColorController* con){
  cpUpdateColorController(&(con->baseController));

  CMLColorMachine* cm = cpGetCurrentColorMachine();
  CMLColorType currentColorType = cpGetCurrentColorType();
  const float* currentColorData = cpGetCurrentColorData();
  CMLColorConverter converter = cmlGetColorConverter(CML_COLOR_YCbCr, currentColorType);
  converter(cm, con->ycbcrColor, currentColorData, 1);
  
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
