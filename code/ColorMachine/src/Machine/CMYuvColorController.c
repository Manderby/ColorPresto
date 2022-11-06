
#include "CMColorController.h"
#include "CMColorWell1D.h"
#include "CMColorWell2D.h"
#include "CMYuvColorController.h"
#include "NAApp.h"
#include "CMDesign.h"

struct CMYuvColorController{
  CMColorController baseController;
  
  CMColorWell2D* colorWell2D;

  NALabel* labelY;
  NALabel* labelup;
  NALabel* labelvp;
  NALabel* labelu;
  NALabel* labelv;
  NATextField* textFieldY;
  NATextField* textFieldup;
  NATextField* textFieldvp;
  NATextField* textFieldu;
  NATextField* textFieldv;
  CMColorWell1D* colorWell1DY;
  CMColorWell1D* colorWell1Dup;
  CMColorWell1D* colorWell1Dvp;
  CMColorWell1D* colorWell1Du;
  CMColorWell1D* colorWell1Dv;

  CMLVec3 yupvpColor;
  CMLVec3 yuvColor;
};



NABool cmYuvValueEdited(NAReaction reaction){
  CMYuvColorController* con = (CMYuvColorController*)reaction.controller;
  
  if(reaction.uiElement == con->textFieldY){
    NAString* string = naNewStringWithTextFieldText(con->textFieldY);
    con->yupvpColor[0] = atof(naGetStringUTF8Pointer(string));
    naDelete(string);
  }else if(reaction.uiElement == con->textFieldup){
    NAString* string = naNewStringWithTextFieldText(con->textFieldup);
    con->yupvpColor[1] = atof(naGetStringUTF8Pointer(string));
    naDelete(string);
  }else if(reaction.uiElement == con->textFieldvp){
    NAString* string = naNewStringWithTextFieldText(con->textFieldvp);
    con->yupvpColor[2] = atof(naGetStringUTF8Pointer(string));
    naDelete(string);
  }
  
  cmSetCurrentColorController(&(con->baseController));
  cmUpdateColor();
  
  return NA_TRUE;
}



CMYuvColorController* cmAllocYuvColorController(void){
  CMYuvColorController* con = naAlloc(CMYuvColorController);
  
  cmInitColorController(&(con->baseController), CML_COLOR_Yupvp);
  
  con->colorWell2D = cmAllocColorWell2D(&(con->baseController), 0);

  con->labelY = cmNewColorComponentLabel("Y");
  con->labelup = cmNewColorComponentLabel("u'");
  con->labelvp = cmNewColorComponentLabel("v'");
  con->labelu = cmNewColorComponentLabel("u");
  con->labelv = cmNewColorComponentLabel("v");
  con->textFieldY = cmNewValueTextBox(cmYuvValueEdited, con);
  con->textFieldup = cmNewValueTextBox(cmYuvValueEdited, con);
  con->textFieldvp = cmNewValueTextBox(cmYuvValueEdited, con);
  con->textFieldu = cmNewValueTextBox(cmYuvValueEdited, con);
  con->textFieldv = cmNewValueTextBox(cmYuvValueEdited, con);
  con->colorWell1DY = cmAllocColorWell1D(&(con->baseController), CML_COLOR_Yupvp, con->yupvpColor, 0);
  con->colorWell1Dup = cmAllocColorWell1D(&(con->baseController), CML_COLOR_Yupvp, con->yupvpColor, 1);
  con->colorWell1Dvp = cmAllocColorWell1D(&(con->baseController), CML_COLOR_Yupvp, con->yupvpColor, 2);
  con->colorWell1Du = cmAllocColorWell1D(&(con->baseController), CML_COLOR_Yuv, con->yuvColor, 1);
  con->colorWell1Dv = cmAllocColorWell1D(&(con->baseController), CML_COLOR_Yuv, con->yuvColor, 2);

  NABezel4 colorWellBezel = {20 + colorWell1DSize, 5, colorWell2DSize + 15, 5};
  cmBeginUILayout(con->baseController.space, colorWellBezel);
  cmAddUIPos(0, colorValueCondensedRowHeight);
  cmAddUIRow(con->labelY, colorValueCondensedRowHeight);
  cmAddUICol(con->textFieldY, colorComponentMarginH);
  cmAddUIRow(con->labelup, colorValueCondensedRowHeight);
  cmAddUICol(con->textFieldup, colorComponentMarginH);
  cmAddUIRow(con->labelvp, colorValueCondensedRowHeight);
  cmAddUICol(con->textFieldvp, colorComponentMarginH);
  cmAddUIRow(con->labelu, colorValueCondensedRowHeight);
  cmAddUICol(con->textFieldu, colorComponentMarginH);
  cmAddUIRow(con->labelv, colorValueCondensedRowHeight);
  cmAddUICol(con->textFieldv, colorComponentMarginH);
  cmEndUILayout();
  
  naAddSpaceChild(
    con->baseController.space,
    cmGetColorWell2DUIElement(con->colorWell2D),
    naMakePos(10, 5));

  naAddSpaceChild(
    con->baseController.space,
    cmGetColorWell1DUIElement(con->colorWell1DY),
    naMakePos(colorWell1DMarginLeft, 90));
  naAddSpaceChild(
    con->baseController.space,
    cmGetColorWell1DUIElement(con->colorWell1Dup),
    naMakePos(colorWell1DMarginLeft, 70));
  naAddSpaceChild(
    con->baseController.space,
    cmGetColorWell1DUIElement(con->colorWell1Dvp),
    naMakePos(colorWell1DMarginLeft, 50));
  naAddSpaceChild(
    con->baseController.space,
    cmGetColorWell1DUIElement(con->colorWell1Du),
    naMakePos(colorWell1DMarginLeft, 30));
  naAddSpaceChild(
    con->baseController.space,
    cmGetColorWell1DUIElement(con->colorWell1Dv),
    naMakePos(colorWell1DMarginLeft, 10));

  return con;
}



void cmDeallocYuvColorController(CMYuvColorController* con){
  cmClearColorController(&(con->baseController));
  naFree(con);
}



const void* cmGetYuvColorControllerColorData(const CMYuvColorController* con){
  return &(con->yupvpColor);
}



void cmSetYuvColorControllerColorData(CMYuvColorController* con, const void* data){
  cmlCpy3(con->yupvpColor, data);
}



void cmUpdateYuvColorController(CMYuvColorController* con){
  cmUpdateColorController(&(con->baseController));

  CMLColorMachine* cm = cmGetCurrentColorMachine();
  CMLColorType currentColorType = cmGetCurrentColorType();
  const float* currentColorData = cmGetCurrentColorData();
  CMLColorConverter yupvpConverter = cmlGetColorConverter(CML_COLOR_Yupvp, currentColorType);
  yupvpConverter(cm, con->yupvpColor, currentColorData, 1);
  CMLColorConverter yuvConverter = cmlGetColorConverter(CML_COLOR_Yuv, currentColorType);
  yuvConverter(cm, con->yuvColor, currentColorData, 1);

  cmUpdateColorWell2D(con->colorWell2D);

  naSetTextFieldText(
    con->textFieldY,
    naAllocSprintf(NA_TRUE, "%1.05f", con->yupvpColor[0]));
  naSetTextFieldText(
    con->textFieldup,
    naAllocSprintf(NA_TRUE, "%1.05f", con->yupvpColor[1]));
  naSetTextFieldText(
    con->textFieldvp,
    naAllocSprintf(NA_TRUE, "%1.05f", con->yupvpColor[2]));
  naSetTextFieldText(
    con->textFieldu,
    naAllocSprintf(NA_TRUE, "%1.05f", con->yuvColor[1]));
  naSetTextFieldText(
    con->textFieldv,
    naAllocSprintf(NA_TRUE, "%1.05f", con->yuvColor[2]));

  cmUpdateColorWell1D(con->colorWell1DY);
  cmUpdateColorWell1D(con->colorWell1Dup);
  cmUpdateColorWell1D(con->colorWell1Dvp);
  cmUpdateColorWell1D(con->colorWell1Du);
  cmUpdateColorWell1D(con->colorWell1Dv);
}
