
#include "CMColorController.h"
#include "CMColorMachineApplication.h"
#include "CMColorWell1D.h"
#include "CMColorWell2D.h"
#include "CMYcdColorController.h"
#include "NAApp.h"
#include "CMDesign.h"

struct CMYcdColorController{
  CMColorController baseController;
  
  CMColorWell2D* colorWell2D;
  
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
    con->ycdColor[0] = naGetTextFieldDouble(con->textFieldY);
  }else if(reaction.uiElement == con->textFieldc){
    con->ycdColor[1] = naGetTextFieldDouble(con->textFieldc);
  }else if(reaction.uiElement == con->textFieldd){
    con->ycdColor[2] = naGetTextFieldDouble(con->textFieldd);
  }
  
  cmSetCurrentColorController(&(con->baseController));
  cmUpdateColor();
  
  return NA_TRUE;
}


CMYcdColorController* cmAllocYcdColorController(void){
  CMYcdColorController* con = naAlloc(CMYcdColorController);
  
  cmInitColorController(&(con->baseController), CML_COLOR_Ycd);
  
  con->colorWell2D = cmAllocColorWell2D(&(con->baseController), 0);
  
  con->labelY = cmNewColorComponentLabel("Y");
  con->labelc = cmNewColorComponentLabel("c");
  con->labeld = cmNewColorComponentLabel("d");
  con->textFieldY = cmNewValueTextField(cmYcdValueEdited, con);
  con->textFieldc = cmNewValueTextField(cmYcdValueEdited, con);
  con->textFieldd = cmNewValueTextField(cmYcdValueEdited, con);
  con->colorWell1DY = cmAllocColorWell1D(&(con->baseController), CML_COLOR_Ycd, con->ycdColor, 0);
  con->colorWell1Dc = cmAllocColorWell1D(&(con->baseController), CML_COLOR_Ycd, con->ycdColor, 1);
  con->colorWell1Dd = cmAllocColorWell1D(&(con->baseController), CML_COLOR_Ycd, con->ycdColor, 2);
  
  naSetUIElementNextTabElement(con->textFieldY, con->textFieldc);
  naSetUIElementNextTabElement(con->textFieldc, con->textFieldd);
  naSetUIElementNextTabElement(con->textFieldd, con->textFieldY);

  cmBeginUILayout(con->baseController.space, colorWellBezel);
  cmAddUIPos(0, colorValueCondensedRowHeight);
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
  
  naAddSpaceChild(
    con->baseController.space,
    cmGetColorWell2DUIElement(con->colorWell2D),
    naMakePos(10, 5));

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
