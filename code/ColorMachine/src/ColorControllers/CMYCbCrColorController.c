
#include "CMColorController.h"

#include "../CMColorMachineApplication.h"
#include "../CMDesign.h"
#include "../CMTranslations.h"
#include "Displays/CMColorWell1D.h"
#include "Displays/CMColorWell2D.h"
#include "CMYCbCrColorController.h"

#include "NAApp.h"

struct CMYCbCrColorController{
  CMColorController baseController;
  
  CMColorWell2D* colorWell2D;

  NALabel* labelY;
  NALabel* labelCb;
  NALabel* labelCr;
  NATextField* textFieldY;
  NATextField* textFieldCb;
  NATextField* textFieldCr;
  CMColorWell1D* colorWell1DY;
  CMColorWell1D* colorWell1DCb;
  CMColorWell1D* colorWell1DCr;

  CMLVec3 ycbcrColor;
};



NABool cmYCbCrValueEdited(NAReaction reaction){
  CMYCbCrColorController* con = (CMYCbCrColorController*)reaction.controller;
  
  if(reaction.uiElement == con->textFieldY){
    con->ycbcrColor[0] = (float)naGetTextFieldDouble(con->textFieldY);
  }else if(reaction.uiElement == con->textFieldCb){
    con->ycbcrColor[1] = (float)naGetTextFieldDouble(con->textFieldCb);
  }else if(reaction.uiElement == con->textFieldCr){
    con->ycbcrColor[2] = (float)naGetTextFieldDouble(con->textFieldCr);
  }
  
  cmSetCurrentColorController(&(con->baseController));
  cmUpdateColor();
  
  return NA_TRUE;
}



CMYCbCrColorController* cmAllocYCbCrColorController(void){
  CMYCbCrColorController* con = naAlloc(CMYCbCrColorController);
  
  cmInitColorController(&(con->baseController), CML_COLOR_YCbCr);
  
  con->colorWell2D = cmAllocColorWell2D(&(con->baseController), 0);

  con->labelY = cmNewColorComponentLabel(cmTranslate(CMYCbCrColorChannelY));
  con->labelCb = cmNewColorComponentLabel(cmTranslate(CMYCbCrColorChannelCb));
  con->labelCr = cmNewColorComponentLabel(cmTranslate(CMYCbCrColorChannelCr));
  con->textFieldY = cmNewValueTextField(cmYCbCrValueEdited, con);
  con->textFieldCb = cmNewValueTextField(cmYCbCrValueEdited, con);
  con->textFieldCr = cmNewValueTextField(cmYCbCrValueEdited, con);
  con->colorWell1DY = cmAllocColorWell1D(&(con->baseController), CML_COLOR_YCbCr, con->ycbcrColor, 0);
  con->colorWell1DCb = cmAllocColorWell1D(&(con->baseController), CML_COLOR_YCbCr, con->ycbcrColor, 1);
  con->colorWell1DCr = cmAllocColorWell1D(&(con->baseController), CML_COLOR_YCbCr, con->ycbcrColor, 2);

  naSetUIElementNextTabElement(con->textFieldY, con->textFieldCb);
  naSetUIElementNextTabElement(con->textFieldCb, con->textFieldCr);
  naSetUIElementNextTabElement(con->textFieldCr, con->textFieldY);

  cmBeginUILayout(con->baseController.space, colorWellBezel);
  cmAddUIPos(0, colorValueCondensedRowHeight);
  cmAddUIRow(con->labelY, colorValueCondensedRowHeight);
  cmAddUICol(con->textFieldY, colorComponentMarginH);
  cmAddUIColV(cmGetColorWell1DUIElement(con->colorWell1DY), 10, colorWell1DOffset);
  cmAddUIRow(con->labelCb, colorValueCondensedRowHeight);
  cmAddUICol(con->textFieldCb, colorComponentMarginH);
  cmAddUIColV(cmGetColorWell1DUIElement(con->colorWell1DCb), 10, colorWell1DOffset);
  cmAddUIRow(con->labelCr, colorValueCondensedRowHeight);
  cmAddUICol(con->textFieldCr, colorComponentMarginH);
  cmAddUIColV(cmGetColorWell1DUIElement(con->colorWell1DCr), 10, colorWell1DOffset);
  cmAddUIPos(0, colorValueCondensedRowHeight);
  cmEndUILayout();
  
  naAddSpaceChild(
    con->baseController.space,
    cmGetColorWell2DUIElement(con->colorWell2D),
    naMakePos(10, 5));

  return con;
}



void cmDeallocYCbCrColorController(CMYCbCrColorController* con){
  cmDeallocColorWell2D(con->colorWell2D);
  cmDeallocColorWell1D(con->colorWell1DY);
  cmDeallocColorWell1D(con->colorWell1DCb);
  cmDeallocColorWell1D(con->colorWell1DCr);
  cmClearColorController(&(con->baseController));
  naFree(con);
}



const void* cmGetYCbCrColorControllerColorData(const CMYCbCrColorController* con){
  return &(con->ycbcrColor);
}



void cmSetYCbCrColorControllerColorData(CMYCbCrColorController* con, const void* data){
  cmlCpy3(con->ycbcrColor, data);
}



void cmUpdateYCbCrColorController(CMYCbCrColorController* con){
  cmUpdateColorController(&(con->baseController));

  CMLColorMachine* cm = cmGetCurrentColorMachine();
  CMLColorType currentColorType = cmGetCurrentColorType();
  const float* currentColorData = cmGetCurrentColorData();
  CMLColorConverter converter = cmlGetColorConverter(CML_COLOR_YCbCr, currentColorType);
  converter(cm, con->ycbcrColor, currentColorData, 1);
  
  cmUpdateColorWell2D(con->colorWell2D);

  naSetTextFieldText(
    con->textFieldY,
    naAllocSprintf(NA_TRUE, "%1.05f", con->ycbcrColor[0]));
  naSetTextFieldText(
    con->textFieldCb,
    naAllocSprintf(NA_TRUE, "%1.04f", con->ycbcrColor[1]));
  naSetTextFieldText(
    con->textFieldCr,
    naAllocSprintf(NA_TRUE, "%1.04f", con->ycbcrColor[2]));

  cmUpdateColorWell1D(con->colorWell1DY);
  cmUpdateColorWell1D(con->colorWell1DCb);
  cmUpdateColorWell1D(con->colorWell1DCr);
}
