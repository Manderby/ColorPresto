
#include "CPColorController.h"

#include "../CPColorPromptApplication.h"
#include "../CPDesign.h"
#include "../CPPreferences.h"
#include "../CPTranslations.h"
#include "Displays/CPColorWell1D.h"
#include "Displays/CPColorWell2D.h"
#include "CPHSVHSLColorController.h"

#include "NAApp/NAApp.h"



struct CPHSVHSLColorController{
  CPColorController baseController;
  
  CPColorWell2D* colorWell2D;

  NASpace* channelSpace;
  NARadio* radioHSV;
  NARadio* radioHSL;
  NALabel* label0;
  NALabel* label1;
  NALabel* label2;
  NATextField* textField0;
  NATextField* textField1;
  NATextField* textField2;
  CPColorWell1D* colorWell1D0;
  CPColorWell1D* colorWell1D1;
  CPColorWell1D* colorWell1D2;

  CMLVec3 color;
};



typedef enum {
  HSV,
  HSL,
  HSVHSLSelectCount
} HSVHSLSelect;



NABool cp_HSVHSLSelectionChanged(NAReaction reaction){
  CPHSVHSLColorController* con = (CPHSVHSLColorController*)reaction.controller;
  
  HSVHSLSelect hsvhslSelect = (HSVHSLSelect)naGetPreferencesEnum(cpPrefs[CPHSVHSLSelect]);
  CMLColorType oldColorType = (hsvhslSelect == HSV) ? CML_COLOR_HSV : CML_COLOR_HSL;
  CMLColorType newColorType = oldColorType;

  if(reaction.uiElement == con->radioHSV){
    naSetPreferencesEnum(cpPrefs[CPHSVHSLSelect], HSV);
    newColorType = CML_COLOR_HSV;
  }else if(reaction.uiElement == con->radioHSL){
    naSetPreferencesEnum(cpPrefs[CPHSVHSLSelect], HSL);
    newColorType = CML_COLOR_HSL;
  }

  CMLColorMachine* cm = cpGetCurrentColorMachine();
  CMLColorConverter converter = cmlGetColorConverter(newColorType, oldColorType);
  converter(cm, con->color, con->color, 1);

  cpSetColorControllerColorType(&(con->baseController), newColorType);
  cpSetCurrentColorController(&(con->baseController));
  cpUpdateColor();
  
  return NA_TRUE;
}



NABool cp_HSVHSLValueEdited(NAReaction reaction){
  CPHSVHSLColorController* con = (CPHSVHSLColorController*)reaction.controller;
  
  if(reaction.uiElement == con->textField0){
    con->color[0] = (float)naGetTextFieldDouble(con->textField0);
  }else if(reaction.uiElement == con->textField1){
    con->color[1] = (float)naGetTextFieldDouble(con->textField1);
  }else if(reaction.uiElement == con->textField2){
    con->color[2] = (float)naGetTextFieldDouble(con->textField2);
  }
  
  cpSetCurrentColorController(&(con->baseController));
  cpUpdateColor();
  
  return NA_TRUE;
}



CPHSVHSLColorController* cpAllocHSVHSLColorController(void){
  HSVHSLSelect hsvhslSelect = (HSVHSLSelect)naInitPreferencesEnum(cpPrefs[CPHSVHSLSelect], HSV, HSVHSLSelectCount);
  CMLColorType colorType = (hsvhslSelect == HSV) ? CML_COLOR_HSV : CML_COLOR_HSL;

  CPHSVHSLColorController* con = naAlloc(CPHSVHSLColorController);
  
  cpInitColorController(&(con->baseController), colorType);
  
  con->colorWell2D = cpAllocColorWell2D(&(con->baseController), 2);

  con->channelSpace = naNewSpace(naMakeSize(1, 1));
  con->radioHSV = naNewRadio(cpTranslate(CPColorSpaceHSV), radioSelectWidth);
  con->radioHSL = naNewRadio(cpTranslate(CPColorSpaceHSL), radioSelectWidth);
  naAddUIReaction(con->radioHSV, NA_UI_COMMAND_PRESSED, cp_HSVHSLSelectionChanged, con);
  naAddUIReaction(con->radioHSL, NA_UI_COMMAND_PRESSED, cp_HSVHSLSelectionChanged, con);
  
  con->label0 = cpNewColorComponentLabel("");
  con->label1 = cpNewColorComponentLabel("");
  con->label2 = cpNewColorComponentLabel("");
  con->textField0 = cpNewValueTextField(cp_HSVHSLValueEdited, con);
  con->textField1 = cpNewValueTextField(cp_HSVHSLValueEdited, con);
  con->textField2 = cpNewValueTextField(cp_HSVHSLValueEdited, con);
  con->colorWell1D0 = cpAllocColorWell1D(&(con->baseController), con->color, 0);
  con->colorWell1D1 = cpAllocColorWell1D(&(con->baseController), con->color, 1);
  con->colorWell1D2 = cpAllocColorWell1D(&(con->baseController), con->color, 2);

  naSetUIElementNextTabElement(con->textField0, con->textField1);
  naSetUIElementNextTabElement(con->textField1, con->textField2);
  naSetUIElementNextTabElement(con->textField2, con->textField0);

  cpBeginUILayout(con->channelSpace, naMakeBezel4Zero());
  cpAddUIPos(0, (int)((colorWell2DSize - (4 * 25. + radioChannelCenteringOffset)) / 2.)); // center the channels
  cpAddUIRowH(con->radioHSV, colorValueCondensedRowHeight, colorComponentWidth + colorComponentMarginH);
  cpAddUICol(con->radioHSL, 10);
  cpAddUIPos(0, radioChannelOffset);
  
  cpAddUIRow(con->label0, colorValueCondensedRowHeight);
  cpAddUICol(con->textField0, colorComponentMarginH);
  cpAddUIColV(cpGetColorWell1DUIElement(con->colorWell1D0), 10, colorWell1DOffset);
  cpAddUIRow(con->label1, colorValueCondensedRowHeight);
  cpAddUICol(con->textField1, colorComponentMarginH);
  cpAddUIColV(cpGetColorWell1DUIElement(con->colorWell1D1), 10, colorWell1DOffset);
  cpAddUIRow(con->label2, colorValueCondensedRowHeight);
  cpAddUICol(con->textField2, colorComponentMarginH);
  cpAddUIColV(cpGetColorWell1DUIElement(con->colorWell1D2), 10, colorWell1DOffset);
  cpEndUILayout();
  
  cpBeginUILayout(con->baseController.space, colorWellBezel);
  cpAddUIRow(cpGetColorWell2DUIElement(con->colorWell2D), 0);
  cpAddUICol(con->channelSpace, colorWell2DRightMargin);
  cpEndUILayout();

  return con;
}



void cpDeallocHSVHSLColorController(CPHSVHSLColorController* con){
  cpDeallocColorWell2D(con->colorWell2D);
  cpDeallocColorWell1D(con->colorWell1D0);
  cpDeallocColorWell1D(con->colorWell1D1);
  cpDeallocColorWell1D(con->colorWell1D2);
  cpClearColorController(&(con->baseController));
  naFree(con);
}



const void* cpGetHSVHSLColorControllerColorData(const CPHSVHSLColorController* con){
  return &(con->color);
}



void cpSetHSVHSLColorControllerColorData(CPHSVHSLColorController* con, const void* data){
  cmlCpy3(con->color, data);
}



void cpUpdateHSVHSLColorController(CPHSVHSLColorController* con){
  cpUpdateColorController(&(con->baseController));

  HSVHSLSelect hsvhslSelect = (HSVHSLSelect)naGetPreferencesEnum(cpPrefs[CPHSVHSLSelect]);
  CMLColorType colorType = (hsvhslSelect == HSV) ? CML_COLOR_HSV : CML_COLOR_HSL;
  
  naSetRadioState(con->radioHSV, hsvhslSelect == HSV);
  naSetRadioState(con->radioHSL, hsvhslSelect == HSL);
  
  if(hsvhslSelect == HSV){
    naSetLabelText(con->label0, cpTranslate(CPHSVColorChannelH));
    naSetLabelText(con->label1, cpTranslate(CPHSVColorChannelS));
    naSetLabelText(con->label2, cpTranslate(CPHSVColorChannelV));
  }else{
    naSetLabelText(con->label0, cpTranslate(CPHSLColorChannelH));
    naSetLabelText(con->label1, cpTranslate(CPHSLColorChannelS));
    naSetLabelText(con->label2, cpTranslate(CPHSLColorChannelL));
  }
  
  CMLColorMachine* cm = cpGetCurrentColorMachine();
  CMLColorType currentColorType = cpGetCurrentColorType();
  const float* currentColorData = cpGetCurrentColorData();
  CMLColorConverter converter = cmlGetColorConverter(colorType, currentColorType);
  converter(cm, con->color, currentColorData, 1);
  
  cpUpdateColorWell2D(con->colorWell2D);

  naSetTextFieldText(
    con->textField0,
    naAllocSprintf(NA_TRUE, "%3.03f", con->color[0]));
  naSetTextFieldText(
    con->textField1,
    naAllocSprintf(NA_TRUE, "%1.05f", con->color[1]));
  naSetTextFieldText(
    con->textField2,
    naAllocSprintf(NA_TRUE, "%1.05f", con->color[2]));

  cpUpdateColorWell1D(con->colorWell1D0);
  cpUpdateColorWell1D(con->colorWell1D1);
  cpUpdateColorWell1D(con->colorWell1D2);
}
