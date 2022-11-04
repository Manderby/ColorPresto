
#include "CMColorController.h"
#include "CMColorWell1D.h"
#include "CMColorWell2D.h"
#include "CMHSVColorController.h"
#include "NAApp.h"
#include "CMDesign.h"

struct CMHSVColorController{
  CMColorController baseController;
  
  CMColorWell2D* colorWell2D;

  NALabel* labelH;
  NALabel* labelS;
  NALabel* labelV;
  NATextField* textFieldH;
  NATextField* textFieldS;
  NATextField* textFieldV;
  CMColorWell1D* colorWell1DH;
  CMColorWell1D* colorWell1DS;
  CMColorWell1D* colorWell1DV;

  CMLVec3 hsvColor;
};



NABool cmHSVValueEdited(NAReaction reaction){
  CMHSVColorController* con = (CMHSVColorController*)reaction.controller;
  
  if(reaction.uiElement == con->textFieldH){
    NAString* string = naNewStringWithTextFieldText(con->textFieldH);
    con->hsvColor[0] = atof(naGetStringUTF8Pointer(string));
    naDelete(string);
  }else if(reaction.uiElement == con->textFieldS){
    NAString* string = naNewStringWithTextFieldText(con->textFieldS);
    con->hsvColor[1] = atof(naGetStringUTF8Pointer(string));
    naDelete(string);
  }else if(reaction.uiElement == con->textFieldV){
    NAString* string = naNewStringWithTextFieldText(con->textFieldV);
    con->hsvColor[2] = atof(naGetStringUTF8Pointer(string));
    naDelete(string);
  }
  
  cmSetCurrentColorController(&(con->baseController));
  cmUpdateColor();
  
  return NA_TRUE;
}



CMHSVColorController* cmAllocHSVColorController(void){
  CMHSVColorController* con = naAlloc(CMHSVColorController);
  
  cmInitColorController(&(con->baseController), CML_COLOR_HSV);
  
  con->colorWell2D = cmAllocColorWell2D(&(con->baseController), 2);

  con->labelH = naNewLabel("H", 20);
  con->labelS = naNewLabel("S", 20);
  con->labelV = naNewLabel("V", 20);
  con->textFieldH = cmNewValueTextBox(cmHSVValueEdited, con);
  con->textFieldS = cmNewValueTextBox(cmHSVValueEdited, con);
  con->textFieldV = cmNewValueTextBox(cmHSVValueEdited, con);
  con->colorWell1DH = cmAllocColorWell1D(&(con->baseController), 0);
  con->colorWell1DS = cmAllocColorWell1D(&(con->baseController), 1);
  con->colorWell1DV = cmAllocColorWell1D(&(con->baseController), 2);

  NABezel4 colorWellBezel = {20 + colorWellSize, 5, colorWellSize + 20, 5};
  cmBeginUILayout(con->baseController.space, colorWellBezel);
  cmAddUIPos(0, colorValueCondensedRowHeight);
  cmAddUIRow(con->labelH, colorValueCondensedRowHeight);
  cmAddUICol(con->textFieldH, 0);
  cmAddUIRow(con->labelS, colorValueCondensedRowHeight);
  cmAddUICol(con->textFieldS, 0);
  cmAddUIRow(con->labelV, colorValueCondensedRowHeight);
  cmAddUICol(con->textFieldV, 0);
  cmAddUIPos(0, colorValueCondensedRowHeight);
  cmEndUILayout();
  
  naAddSpaceChild(
    con->baseController.space,
    cmGetColorWell2DUIElement(con->colorWell2D),
    naMakePos(10, 5));

  naAddSpaceChild(
    con->baseController.space,
    cmGetColorWell1DUIElement(con->colorWell1DH),
    naMakePos(215, 70));
  naAddSpaceChild(
    con->baseController.space,
    cmGetColorWell1DUIElement(con->colorWell1DS),
    naMakePos(215, 50));
  naAddSpaceChild(
    con->baseController.space,
    cmGetColorWell1DUIElement(con->colorWell1DV),
    naMakePos(215, 30));

  return con;
}



void cmDeallocHSVColorController(CMHSVColorController* con){
  cmClearColorController(&(con->baseController));
  naFree(con);
}



const void* cmGetHSVColorControllerColorData(const CMHSVColorController* con){
  return &(con->hsvColor);
}



void cmSetHSVColorControllerColorData(CMHSVColorController* con, const void* data){
  cmlCpy3(con->hsvColor, data);
}



void cmUpdateHSVColorController(CMHSVColorController* con){
  cmUpdateColorController(&(con->baseController));

  CMLColorMachine* cm = cmGetCurrentColorMachine();
  CMLColorType currentColorType = cmGetCurrentColorType();
  const float* currentColorData = cmGetCurrentColorData();
  CMLColorConverter converter = cmlGetColorConverter(CML_COLOR_HSV, currentColorType);
  converter(cm, con->hsvColor, currentColorData, 1);
  
  cmUpdateColorWell2D(con->colorWell2D);

  naSetTextFieldText(
    con->textFieldH,
    naAllocSprintf(NA_TRUE, "%3.03f", con->hsvColor[0]));
  naSetTextFieldText(
    con->textFieldS,
    naAllocSprintf(NA_TRUE, "%1.05f", con->hsvColor[1]));
  naSetTextFieldText(
    con->textFieldV,
    naAllocSprintf(NA_TRUE, "%1.05f", con->hsvColor[2]));

  cmUpdateColorWell1D(con->colorWell1DH);
  cmUpdateColorWell1D(con->colorWell1DS);
  cmUpdateColorWell1D(con->colorWell1DV);
}
