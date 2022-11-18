
#include "CMColorController.h"
#include "CMColorWell1D.h"
#include "CMColorWell2D.h"
#include "CMYxyColorController.h"
#include "NAApp.h"
#include "CMDesign.h"

struct CMYxyColorController{
  CMColorController baseController;
  
  CMColorWell2D* colorWell2D;

  NALabel* labelY;
  NALabel* labelx;
  NALabel* labely;
  NATextField* textFieldY;
  NATextField* textFieldx;
  NATextField* textFieldy;
  CMColorWell1D* colorWell1DY;
  CMColorWell1D* colorWell1Dx;
  CMColorWell1D* colorWell1Dy;

  CMLVec3 yxyColor;
};



NABool cmYxyValueEdited(NAReaction reaction){
  CMYxyColorController* con = (CMYxyColorController*)reaction.controller;
  
  if(reaction.uiElement == con->textFieldY){
    NAString* string = naNewStringWithTextFieldText(con->textFieldY);
    con->yxyColor[0] = atof(naGetStringUTF8Pointer(string));
    naDelete(string);
  }else if(reaction.uiElement == con->textFieldx){
    NAString* string = naNewStringWithTextFieldText(con->textFieldx);
    con->yxyColor[1] = atof(naGetStringUTF8Pointer(string));
    naDelete(string);
  }else if(reaction.uiElement == con->textFieldy){
    NAString* string = naNewStringWithTextFieldText(con->textFieldy);
    con->yxyColor[2] = atof(naGetStringUTF8Pointer(string));
    naDelete(string);
  }
  
  cmSetCurrentColorController(&(con->baseController));
  cmUpdateColor();
  
  return NA_TRUE;
}



CMYxyColorController* cmAllocYxyColorController(void){
  CMYxyColorController* con = naAlloc(CMYxyColorController);
  
  cmInitColorController(&(con->baseController), CML_COLOR_Yxy);
  
  con->colorWell2D = cmAllocColorWell2D(&(con->baseController), 0);

  con->labelY = cmNewColorComponentLabel("Y");
  con->labelx = cmNewColorComponentLabel("x");
  con->labely = cmNewColorComponentLabel("y");
  con->textFieldY = cmNewValueTextBox(cmYxyValueEdited, con);
  con->textFieldx = cmNewValueTextBox(cmYxyValueEdited, con);
  con->textFieldy = cmNewValueTextBox(cmYxyValueEdited, con);
  con->colorWell1DY = cmAllocColorWell1D(&(con->baseController), CML_COLOR_Yxy, con->yxyColor, 0);
  con->colorWell1Dx = cmAllocColorWell1D(&(con->baseController), CML_COLOR_Yxy, con->yxyColor, 1);
  con->colorWell1Dy = cmAllocColorWell1D(&(con->baseController), CML_COLOR_Yxy, con->yxyColor, 2);

  naSetUIElementNextTabElement(con->textFieldY, con->textFieldx);
  naSetUIElementNextTabElement(con->textFieldx, con->textFieldy);
  naSetUIElementNextTabElement(con->textFieldy, con->textFieldY);

  cmBeginUILayout(con->baseController.space, colorWellBezel);
  cmAddUIPos(0, colorValueCondensedRowHeight);
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
  
  naAddSpaceChild(
    con->baseController.space,
    cmGetColorWell2DUIElement(con->colorWell2D),
    naMakePos(10, 5));

  return con;
}



void cmDeallocYxyColorController(CMYxyColorController* con){
  cmClearColorController(&(con->baseController));
  naFree(con);
}



const void* cmGetYxyColorControllerColorData(const CMYxyColorController* con){
  return &(con->yxyColor);
}



void cmSetYxyColorControllerColorData(CMYxyColorController* con, const void* data){
  cmlCpy3(con->yxyColor, data);
}



void cmUpdateYxyColorController(CMYxyColorController* con){
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
