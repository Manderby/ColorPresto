
#include "CPColorController.h"

#include "../CPColorPrestoApplication.h"
#include "../CPDesign.h"
#include "../CPTranslations.h"
#include "Displays/CPColorWell1D.h"
#include "Displays/CPColorWell2D.h"
#include "CPRGBColorController.h"

#include "NAApp/NAApp.h"
#include "NAUtility/NAString.h"

#if NA_OS == NA_OS_WINDOWS
  #define cpsscanf sscanf_s
#else
  #define cpsscanf sscanf
#endif

struct CPRGBColorController{
  CPColorController baseController;
  
  CPColorWell2D* colorWell2D;
  
  NASpace* channelSpace;
  NALabel* labelR;
  NALabel* labelG;
  NALabel* labelB;
  NATextField* textFieldR;
  NATextField* textFieldG;
  NATextField* textFieldB;
  CPColorWell1D* colorWell1DR;
  CPColorWell1D* colorWell1DG;
  CPColorWell1D* colorWell1DB;

  NALabel* labelNum;
  NATextField* textFieldHex;
  NATextField* textFieldDec;

  CMLVec3 rgbColor;
};



void cp_RGBValueEdited(NAReaction reaction){
  CPRGBColorController* con = (CPRGBColorController*)reaction.controller;
  CMLColorMachine* cm = cpGetCurrentColorMachine();

  if(reaction.uiElement == con->textFieldR){
    con->rgbColor[0] = (float)naGetTextFieldDouble(con->textFieldR);
  }else if(reaction.uiElement == con->textFieldG){
    con->rgbColor[1] = (float)naGetTextFieldDouble(con->textFieldG);
  }else if(reaction.uiElement == con->textFieldB){
    con->rgbColor[2] = (float)naGetTextFieldDouble(con->textFieldB);
  }else if(reaction.uiElement == con->textFieldHex){
    NAString* string = naNewStringWithTextFieldText(con->textFieldHex);
    int rgbbuf[3] = {0, 0, 0};
    cpsscanf(naGetStringUTF8Pointer(string), "%02x%02x%02x", &(rgbbuf[0]), &(rgbbuf[1]), &(rgbbuf[2]));
    uint8 rgbbuf2[3] = {rgbbuf[0], rgbbuf[1], rgbbuf[2]};
    cmlData8ToRGB(cm, con->rgbColor, rgbbuf2, 1);
    naDelete(string);
  }else if(reaction.uiElement == con->textFieldDec){
    NAString* string = naNewStringWithTextFieldText(con->textFieldDec);
    int rgbbuf[3] = {0, 0, 0};
    int assigned = cpsscanf(naGetStringUTF8Pointer(string), "%d, %d, %d", &(rgbbuf[0]), &(rgbbuf[1]), &(rgbbuf[2]));
    if(assigned < 3){
      cpsscanf(naGetStringUTF8Pointer(string), "%d %d %d", &(rgbbuf[0]), &(rgbbuf[1]), &(rgbbuf[2]));
    }
    uint8 rgbbuf2[3] = {rgbbuf[0], rgbbuf[1], rgbbuf[2]};
    cmlData8ToRGB(cm, con->rgbColor, rgbbuf2, 1);
    naDelete(string);
  }
  
  cpSetCurrentColorController(&(con->baseController));
  cpUpdateColor();
}


CPRGBColorController* cpAllocRGBColorController(void){
  CPRGBColorController* con = naAlloc(CPRGBColorController);
  
  cpInitColorController(&(con->baseController), CML_COLOR_RGB);
  
  con->colorWell2D = cpAllocColorWell2D(&(con->baseController), 1);
  
  con->channelSpace = naNewSpace(naMakeSize(1, 1));
  con->labelR = cpNewColorComponentLabel(cpTranslate(CPRGBColorChannelR));
  con->labelG = cpNewColorComponentLabel(cpTranslate(CPRGBColorChannelG));
  con->labelB = cpNewColorComponentLabel(cpTranslate(CPRGBColorChannelB));
  con->textFieldR = cpNewValueTextField(cp_RGBValueEdited, con);
  con->textFieldG = cpNewValueTextField(cp_RGBValueEdited, con);
  con->textFieldB = cpNewValueTextField(cp_RGBValueEdited, con);
  con->colorWell1DR = cpAllocColorWell1D(&(con->baseController), con->rgbColor, 0);
  con->colorWell1DG = cpAllocColorWell1D(&(con->baseController), con->rgbColor, 1);
  con->colorWell1DB = cpAllocColorWell1D(&(con->baseController), con->rgbColor, 2);
  
  con->labelNum = cpNewColorComponentLabel(cpTranslate(CPRGBColorChannelNum));
  con->textFieldHex = cpNewValueTextField(cp_RGBValueEdited, con);
  con->textFieldDec = cpNewBigValueTextField(cp_RGBValueEdited, con);

  naSetUIElementNextTabElement(con->textFieldR, con->textFieldG);
  naSetUIElementNextTabElement(con->textFieldG, con->textFieldB);
  naSetUIElementNextTabElement(con->textFieldB, con->textFieldR);
  naSetUIElementNextTabElement(con->textFieldHex, con->textFieldDec);
  naSetUIElementNextTabElement(con->textFieldDec, con->textFieldHex);

  cpBeginUILayout(con->channelSpace, naMakeBorder2D(0., 0., 0., 0.));
  cpAddUIPos(0, (int)((colorWell2DSize - (4 * 25. + 10.)) / 2.)); // center the channels
  cpAddUIRow(con->labelR, colorValueCondensedRowHeight);
  cpAddUICol(con->textFieldR, colorComponentMarginH);
  cpAddUIColV(cpGetColorWell1DUIElement(con->colorWell1DR), 10, colorWell1DOffset);
  cpAddUIRow(con->labelG, colorValueCondensedRowHeight);
  cpAddUICol(con->textFieldG, colorComponentMarginH);
  cpAddUIColV(cpGetColorWell1DUIElement(con->colorWell1DG), 10, colorWell1DOffset);
  cpAddUIRow(con->labelB, colorValueCondensedRowHeight);
  cpAddUICol(con->textFieldB, colorComponentMarginH);
  cpAddUIColV(cpGetColorWell1DUIElement(con->colorWell1DB), 10, colorWell1DOffset);

  cpAddUIPos(0, 10);
  cpAddUIRow(con->labelNum, colorValueCondensedRowHeight);
  cpAddUICol(con->textFieldHex, colorComponentMarginH);
  cpAddUICol(con->textFieldDec, 10);
  cpEndUILayout();

  cpBeginUILayout(con->baseController.space, colorWellBorder);
  cpAddUIRow(cpGetColorWell2DUIElement(con->colorWell2D), 0);
  cpAddUICol(con->channelSpace, colorWell2DRightMargin);
  cpEndUILayout();
  
  return con;
}



void cpDeallocRGBColorController(CPRGBColorController* con){
  cpDeallocColorWell2D(con->colorWell2D);
  cpDeallocColorWell1D(con->colorWell1DR);
  cpDeallocColorWell1D(con->colorWell1DG);
  cpDeallocColorWell1D(con->colorWell1DB);
  cpClearColorController(&(con->baseController));
  naFree(con);
}



const void* cpGetRGBColorControllerColorData(const CPRGBColorController* con){
  return &(con->rgbColor);
}



void cpSetRGBColorControllerColorData(CPRGBColorController* con, const void* data){
  cmlCpy3(con->rgbColor, data);
}



void cpComputeRGBColorController(CPRGBColorController* con) {
  CMLColorMachine* cm = cpGetCurrentColorMachine();

  CMLColorType currentColorType = cpGetCurrentColorType();
  const float* currentColorData = cpGetCurrentColorData();
  CMLColorConverter converter = cmlGetColorConverter(CML_COLOR_RGB, currentColorType);
  converter(cm, con->rgbColor, currentColorData, 1);

  cpComputeColorWell2D(con->colorWell2D);
  cpComputeColorWell1D(con->colorWell1DR);
  cpComputeColorWell1D(con->colorWell1DG);
  cpComputeColorWell1D(con->colorWell1DB);
}



void cpUpdateRGBColorController(CPRGBColorController* con){
  cpUpdateColorController(&(con->baseController));
  
  CMLColorMachine* cm = cpGetCurrentColorMachine();
  
  cpUpdateColorWell2D(con->colorWell2D);
  
  naSetTextFieldText(
    con->textFieldR,
    naAllocSprintf(NA_TRUE, "%1.05f", con->rgbColor[0]));
  naSetTextFieldText(
    con->textFieldG,
    naAllocSprintf(NA_TRUE, "%1.05f", con->rgbColor[1]));
  naSetTextFieldText(
    con->textFieldB,
    naAllocSprintf(NA_TRUE, "%1.05f", con->rgbColor[2]));

  CMLVec3 clamped;
  cmlCpy3(clamped, con->rgbColor);
  cmlClampRGB(clamped, 1);
  uint8 rgbbuf[3] = {0, 0, 0};
  cmlRGBToData8(cm, rgbbuf, clamped, 1);
  naSetTextFieldText(
    con->textFieldHex,
    naAllocSprintf(NA_TRUE, "%02x%02x%02x", (int)rgbbuf[0], (int)rgbbuf[1], (int)rgbbuf[2]));
  naSetTextFieldText(
    con->textFieldDec,
    naAllocSprintf(NA_TRUE, "%d, %d, %d", (int)rgbbuf[0], (int)rgbbuf[1], (int)rgbbuf[2]));

  cpUpdateColorWell1D(con->colorWell1DR);
  cpUpdateColorWell1D(con->colorWell1DG);
  cpUpdateColorWell1D(con->colorWell1DB);
}
