
#include "CMColorController.h"

#include "../CMColorMachineApplication.h"
#include "../CMDesign.h"
#include "../CMTranslations.h"
#include "Displays/CMColorWell1D.h"
#include "Displays/CMColorWell2D.h"
#include "CMRGBColorController.h"

#include "NAApp.h"

#if NA_OS == NA_OS_WINDOWS
  #define cmsscanf sscanf_s
#else
  #define cmsscanf sscanf
#endif

struct CMRGBColorController{
  CMColorController baseController;
  
  CMColorWell2D* colorWell2D;
  
  NASpace* channelSpace;
  NALabel* labelR;
  NALabel* labelG;
  NALabel* labelB;
  NATextField* textFieldR;
  NATextField* textFieldG;
  NATextField* textFieldB;
  CMColorWell1D* colorWell1DR;
  CMColorWell1D* colorWell1DG;
  CMColorWell1D* colorWell1DB;

  NALabel* labelNum;
  NATextField* textFieldHex;
  NATextField* textFieldDec;

  CMLVec3 rgbColor;
};



NABool cmRGBValueEdited(NAReaction reaction){
  CMRGBColorController* con = (CMRGBColorController*)reaction.controller;
  CMLColorMachine* cm = cmGetCurrentColorMachine();

  if(reaction.uiElement == con->textFieldR){
    con->rgbColor[0] = (float)naGetTextFieldDouble(con->textFieldR);
  }else if(reaction.uiElement == con->textFieldG){
    con->rgbColor[1] = (float)naGetTextFieldDouble(con->textFieldG);
  }else if(reaction.uiElement == con->textFieldB){
    con->rgbColor[2] = (float)naGetTextFieldDouble(con->textFieldB);
  }else if(reaction.uiElement == con->textFieldHex){
    NAString* string = naNewStringWithTextFieldText(con->textFieldHex);
    int rgbbuf[3] = {0, 0, 0};
    cmsscanf(naGetStringUTF8Pointer(string), "%02x%02x%02x", &(rgbbuf[0]), &(rgbbuf[1]), &(rgbbuf[2]));
    uint8 rgbbuf2[3] = {rgbbuf[0], rgbbuf[1], rgbbuf[2]};
    cmlData8ToRGB(cm, con->rgbColor, rgbbuf2, 1);
    naDelete(string);
  }else if(reaction.uiElement == con->textFieldDec){
    NAString* string = naNewStringWithTextFieldText(con->textFieldDec);
    int rgbbuf[3] = {0, 0, 0};
    int assigned = cmsscanf(naGetStringUTF8Pointer(string), "%d, %d, %d", &(rgbbuf[0]), &(rgbbuf[1]), &(rgbbuf[2]));
    if(assigned < 3){
      cmsscanf(naGetStringUTF8Pointer(string), "%d %d %d", &(rgbbuf[0]), &(rgbbuf[1]), &(rgbbuf[2]));
    }
    uint8 rgbbuf2[3] = {rgbbuf[0], rgbbuf[1], rgbbuf[2]};
    cmlData8ToRGB(cm, con->rgbColor, rgbbuf2, 1);
    naDelete(string);
  }
  
  cmSetCurrentColorController(&(con->baseController));
  cmUpdateColor();
  
  return NA_TRUE;
}


CMRGBColorController* cmAllocRGBColorController(void){
  CMRGBColorController* con = naAlloc(CMRGBColorController);
  
  cmInitColorController(&(con->baseController), CML_COLOR_RGB);
  
  con->colorWell2D = cmAllocColorWell2D(&(con->baseController), 1);
  
  con->channelSpace = naNewSpace(naMakeSize(1, 1));
  con->labelR = cmNewColorComponentLabel(cmTranslate(CMRGBColorChannelR));
  con->labelG = cmNewColorComponentLabel(cmTranslate(CMRGBColorChannelG));
  con->labelB = cmNewColorComponentLabel(cmTranslate(CMRGBColorChannelB));
  con->textFieldR = cmNewValueTextField(cmRGBValueEdited, con);
  con->textFieldG = cmNewValueTextField(cmRGBValueEdited, con);
  con->textFieldB = cmNewValueTextField(cmRGBValueEdited, con);
  con->colorWell1DR = cmAllocColorWell1D(&(con->baseController), CML_COLOR_RGB, con->rgbColor, 0);
  con->colorWell1DG = cmAllocColorWell1D(&(con->baseController), CML_COLOR_RGB, con->rgbColor, 1);
  con->colorWell1DB = cmAllocColorWell1D(&(con->baseController), CML_COLOR_RGB, con->rgbColor, 2);
  
  con->labelNum = cmNewColorComponentLabel(cmTranslate(CMRGBColorChannelNum));
  con->textFieldHex = cmNewValueTextField(cmRGBValueEdited, con);
  con->textFieldDec = cmNewBigValueTextField(cmRGBValueEdited, con);

  naSetUIElementNextTabElement(con->textFieldR, con->textFieldG);
  naSetUIElementNextTabElement(con->textFieldG, con->textFieldB);
  naSetUIElementNextTabElement(con->textFieldB, con->textFieldR);
  naSetUIElementNextTabElement(con->textFieldHex, con->textFieldDec);
  naSetUIElementNextTabElement(con->textFieldDec, con->textFieldHex);

  cmBeginUILayout(con->channelSpace, naMakeBezel4Zero());
  cmAddUIPos(0, (int)((colorWell2DSize - (4 * 25. + 10.)) / 2.)); // center the channels
  cmAddUIRow(con->labelR, colorValueCondensedRowHeight);
  cmAddUICol(con->textFieldR, colorComponentMarginH);
  cmAddUIColV(cmGetColorWell1DUIElement(con->colorWell1DR), 10, colorWell1DOffset);
  cmAddUIRow(con->labelG, colorValueCondensedRowHeight);
  cmAddUICol(con->textFieldG, colorComponentMarginH);
  cmAddUIColV(cmGetColorWell1DUIElement(con->colorWell1DG), 10, colorWell1DOffset);
  cmAddUIRow(con->labelB, colorValueCondensedRowHeight);
  cmAddUICol(con->textFieldB, colorComponentMarginH);
  cmAddUIColV(cmGetColorWell1DUIElement(con->colorWell1DB), 10, colorWell1DOffset);

  cmAddUIPos(0, 10);
  cmAddUIRow(con->labelNum, colorValueCondensedRowHeight);
  cmAddUICol(con->textFieldHex, colorComponentMarginH);
  cmAddUICol(con->textFieldDec, 10);
  cmEndUILayout();

  cmBeginUILayout(con->baseController.space, colorWellBezel);
  cmAddUIRow(cmGetColorWell2DUIElement(con->colorWell2D), 0);
  cmAddUICol(con->channelSpace, 10);
  cmEndUILayout();
  
  return con;
}



void cmDeallocRGBColorController(CMRGBColorController* con){
  cmDeallocColorWell2D(con->colorWell2D);
  cmDeallocColorWell1D(con->colorWell1DR);
  cmDeallocColorWell1D(con->colorWell1DG);
  cmDeallocColorWell1D(con->colorWell1DB);
  cmClearColorController(&(con->baseController));
  naFree(con);
}



const void* cmGetRGBColorControllerColorData(const CMRGBColorController* con){
  return &(con->rgbColor);
}



void cmSetRGBColorControllerColorData(CMRGBColorController* con, const void* data){
  cmlCpy3(con->rgbColor, data);
}



void cmUpdateRGBColorController(CMRGBColorController* con){
  cmUpdateColorController(&(con->baseController));
  
  CMLColorMachine* cm = cmGetCurrentColorMachine();
  CMLColorType currentColorType = cmGetCurrentColorType();
  const float* currentColorData = cmGetCurrentColorData();
  CMLColorConverter converter = cmlGetColorConverter(CML_COLOR_RGB, currentColorType);
  converter(cm, con->rgbColor, currentColorData, 1);
  
  cmUpdateColorWell2D(con->colorWell2D);
  
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

  cmUpdateColorWell1D(con->colorWell1DR);
  cmUpdateColorWell1D(con->colorWell1DG);
  cmUpdateColorWell1D(con->colorWell1DB);
}
