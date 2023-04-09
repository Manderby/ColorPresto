
#include "CMColorController.h"

#include "../CMColorMachineApplication.h"
#include "../CMDesign.h"
#include "../CMTranslations.h"
#include "Displays/CMColorWell1D.h"
#include "Displays/CMColorWell2D.h"
#include "CMYcdColorController.h"

#include "NAApp.h"

struct CMYcdColorController{
  CMColorController baseController;
  
  CMColorWell2D* colorWell2D;
  
  NASpace* channelSpace;
  NALabel* labelY;
  NALabel* labelc;
  NALabel* labeld;
  NATextField* textFieldY;
  NATextField* textFieldc;
  NATextField* textFieldd;
  CMColorWell1D* colorWell1DY;
  CMColorWell1D* colorWell1Dc;
  CMColorWell1D* colorWell1Dd;

  CMLVec3 ycdColor;
};



NABool cmYcdValueEdited(NAReaction reaction){
  CMYcdColorController* con = (CMYcdColorController*)reaction.controller;

  if(reaction.uiElement == con->textFieldY){
    con->ycdColor[0] = (float)naGetTextFieldDouble(con->textFieldY);
  }else if(reaction.uiElement == con->textFieldc){
    con->ycdColor[1] = (float)naGetTextFieldDouble(con->textFieldc);
  }else if(reaction.uiElement == con->textFieldd){
    con->ycdColor[2] = (float)naGetTextFieldDouble(con->textFieldd);
  }
  
  cmSetCurrentColorController(&(con->baseController));
  cmUpdateColor();
  
  return NA_TRUE;
}


CMYcdColorController* cmAllocYcdColorController(void){
  CMYcdColorController* con = naAlloc(CMYcdColorController);
  
  cmInitColorController(&(con->baseController), CML_COLOR_Ycd);
  
  con->colorWell2D = cmAllocColorWell2D(&(con->baseController), 0);
  
  con->channelSpace = naNewSpace(naMakeSize(1, 1));
  con->labelY = cmNewColorComponentLabel(cmTranslate(CMYcdColorChannelY));
  con->labelc = cmNewColorComponentLabel(cmTranslate(CMYcdColorChannelc));
  con->labeld = cmNewColorComponentLabel(cmTranslate(CMYcdColorChanneld));
  con->textFieldY = cmNewValueTextField(cmYcdValueEdited, con);
  con->textFieldc = cmNewValueTextField(cmYcdValueEdited, con);
  con->textFieldd = cmNewValueTextField(cmYcdValueEdited, con);
  con->colorWell1DY = cmAllocColorWell1D(&(con->baseController), CML_COLOR_Ycd, con->ycdColor, 0);
  con->colorWell1Dc = cmAllocColorWell1D(&(con->baseController), CML_COLOR_Ycd, con->ycdColor, 1);
  con->colorWell1Dd = cmAllocColorWell1D(&(con->baseController), CML_COLOR_Ycd, con->ycdColor, 2);
  
  naSetUIElementNextTabElement(con->textFieldY, con->textFieldc);
  naSetUIElementNextTabElement(con->textFieldc, con->textFieldd);
  naSetUIElementNextTabElement(con->textFieldd, con->textFieldY);

  cmBeginUILayout(con->channelSpace, naMakeBezel4Zero());
  cmAddUIPos(0, (int)((colorWell2DSize - (3 * 25.)) / 2.)); // center the channels
  cmAddUIRow(con->labelY, colorValueCondensedRowHeight);
  cmAddUICol(con->textFieldY, colorComponentMarginH);
  cmAddUIColV(cmGetColorWell1DUIElement(con->colorWell1DY), 10, colorWell1DOffset);
  cmAddUIRow(con->labelc, colorValueCondensedRowHeight);
  cmAddUICol(con->textFieldc, colorComponentMarginH);
  cmAddUIColV(cmGetColorWell1DUIElement(con->colorWell1Dc), 10, colorWell1DOffset);
  cmAddUIRow(con->labeld, colorValueCondensedRowHeight);
  cmAddUICol(con->textFieldd, colorComponentMarginH);
  cmAddUIColV(cmGetColorWell1DUIElement(con->colorWell1Dd), 10, colorWell1DOffset);
  cmAddUIPos(0, colorValueCondensedRowHeight);

  cmEndUILayout();
  
  cmBeginUILayout(con->baseController.space, colorWellBezel);
  cmAddUIRow(cmGetColorWell2DUIElement(con->colorWell2D), 0);
  cmAddUICol(con->channelSpace, 10);
  cmEndUILayout();

  return con;
}



void cmDeallocYcdColorController(CMYcdColorController* con){
  cmDeallocColorWell2D(con->colorWell2D);
  cmDeallocColorWell1D(con->colorWell1DY);
  cmDeallocColorWell1D(con->colorWell1Dc);
  cmDeallocColorWell1D(con->colorWell1Dd);
  cmClearColorController(&(con->baseController));
  naFree(con);
}



const void* cmGetYcdColorControllerColorData(const CMYcdColorController* con){
  return &(con->ycdColor);
}



void cmSetYcdColorControllerColorData(CMYcdColorController* con, const void* data){
  cmlCpy3(con->ycdColor, data);
}



void cmUpdateYcdColorController(CMYcdColorController* con){
  cmUpdateColorController(&(con->baseController));
  
  CMLColorMachine* cm = cmGetCurrentColorMachine();
  CMLColorType currentColorType = cmGetCurrentColorType();
  const float* currentColorData = cmGetCurrentColorData();
  CMLColorConverter converter = cmlGetColorConverter(CML_COLOR_Ycd, currentColorType);
  converter(cm, con->ycdColor, currentColorData, 1);
  
  cmUpdateColorWell2D(con->colorWell2D);
  
  naSetTextFieldText(
    con->textFieldY,
    naAllocSprintf(NA_TRUE, "%1.05f", con->ycdColor[0]));
  naSetTextFieldText(
    con->textFieldc,
    naAllocSprintf(NA_TRUE, "%1.05f", con->ycdColor[1]));
  naSetTextFieldText(
    con->textFieldd,
    naAllocSprintf(NA_TRUE, "%1.05f", con->ycdColor[2]));

  cmUpdateColorWell1D(con->colorWell1DY);
  cmUpdateColorWell1D(con->colorWell1Dc);
  cmUpdateColorWell1D(con->colorWell1Dd);
}
