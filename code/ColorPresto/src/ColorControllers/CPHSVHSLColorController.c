
#include "CPColorController.h"

#include "../CPColorPrestoApplication.h"
#include "../CPDesign.h"
#include "../Preferences/CPPreferences.h"
#include "../CPTranslations.h"
#include "Displays/CPColorWell1D.h"
#include "Displays/CPColorWell2D.h"
#include "CPHSVHSLColorController.h"

#include "NAApp/NAApp.h"
#include "NAUtility/NAString.h"



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



void cp_HSVHSLSelectionChanged(NAReaction reaction) {
  CPHSVHSLColorController* con = (CPHSVHSLColorController*)reaction.controller;
  
  HSVHSLSelect hsvhslSelect = cpGetPrefsHSVHSLSelect();
  CMLColorType oldColorType = (hsvhslSelect == HSV) ? CML_COLOR_HSV : CML_COLOR_HSL;
  CMLColorType newColorType = oldColorType;

  if(reaction.uiElement == con->radioHSV) {
    cpSetPrefsHSVHSLSelect(HSV);
    newColorType = CML_COLOR_HSV;
  }else if(reaction.uiElement == con->radioHSL) {
    cpSetPrefsHSVHSLSelect(HSL);
    newColorType = CML_COLOR_HSL;
  }

  CMLColorMachine* cm = cpGetCurrentColorMachine();
  CMLColorConverter converter = cmlGetColorConverter(newColorType, oldColorType);
  converter(cm, con->color, con->color, 1);

  cpSetColorControllerColorType(&(con->baseController), newColorType);
  cpSetCurrentColorController(&(con->baseController));
  cpUpdateColor();
}



void cp_HSVHSLValueEdited(NAReaction reaction) {
  CPHSVHSLColorController* con = (CPHSVHSLColorController*)reaction.controller;
  
  if(reaction.uiElement == con->textField0) {
    con->color[0] = (float)naGetTextFieldDouble(con->textField0);
  }else if(reaction.uiElement == con->textField1) {
    con->color[1] = (float)naGetTextFieldDouble(con->textField1);
  }else if(reaction.uiElement == con->textField2) {
    con->color[2] = (float)naGetTextFieldDouble(con->textField2);
  }
  
  cpSetCurrentColorController(&(con->baseController));
  cpUpdateColor();
}



CPHSVHSLColorController* cpAllocHSVHSLColorController(void) {
  HSVHSLSelect hsvhslSelect = cpGetPrefsHSVHSLSelect();
  CMLColorType colorType = (hsvhslSelect == HSV) ? CML_COLOR_HSV : CML_COLOR_HSL;

  CPHSVHSLColorController* con = naAlloc(CPHSVHSLColorController);
  
  cpInitColorController(&(con->baseController), colorType);
  
  con->colorWell2D = cpAllocColorWell2D(&(con->baseController), 2);

  con->channelSpace = naNewSpace();
  con->radioHSV = naNewRadio(cpTranslate(CPColorSpaceHSV));
  con->radioHSL = naNewRadio(cpTranslate(CPColorSpaceHSL));
  naAddUIReaction(con->radioHSV, NA_UI_COMMAND_PRESSED, cp_HSVHSLSelectionChanged, con);
  naAddUIReaction(con->radioHSL, NA_UI_COMMAND_PRESSED, cp_HSVHSLSelectionChanged, con);
  
  con->label0 = cpNewColorComponentLabel(NA_NULL);
  con->label1 = cpNewColorComponentLabel(NA_NULL);
  con->label2 = cpNewColorComponentLabel(NA_NULL);
  con->textField0 = cpNewValueTextField(cp_HSVHSLValueEdited, con);
  con->textField1 = cpNewValueTextField(cp_HSVHSLValueEdited, con);
  con->textField2 = cpNewValueTextField(cp_HSVHSLValueEdited, con);
  con->colorWell1D0 = cpAllocColorWell1D(&(con->baseController), con->color, 0);
  con->colorWell1D1 = cpAllocColorWell1D(&(con->baseController), con->color, 1);
  con->colorWell1D2 = cpAllocColorWell1D(&(con->baseController), con->color, 2);

  naSetUIElementNextTabElement(con->textField0, con->textField1);
  naSetUIElementNextTabElement(con->textField1, con->textField2);
  naSetUIElementNextTabElement(con->textField2, con->textField0);

  NABorder2D zeroPadding = naMakeBorder2D(0., 0., 0., 0.);

  naBeginLayout(con->baseController.space, colorWellBorder);
    
    naAddLayoutSection(NA_LAYOUT_MIN, zeroPadding);
      naAddLayoutElement(cpGetColorWell2DUIElement(con->colorWell2D), 0, NA_LAYOUT_MIN);
    
      naBeginSubLayout(con->channelSpace, zeroPadding, 0, NA_LAYOUT_MIN);
        naAddLayoutSection(colorValueCondensedRowHeight, zeroPadding);
          naAddLayoutElement(con->radioHSV, colorComponentWidth + colorComponentMarginH, radioSelectWidth);
          naAddLayoutElement(con->radioHSL, 10, radioSelectWidth);
        naAddLayoutSection(colorValueCondensedRowHeight, zeroPadding);
          naAddLayoutElement(con->label0, 0, colorComponentWidth);
          naAddLayoutElement(con->textField0, colorComponentMarginH, textFieldValueWidth);
          naAddLayoutElement(cpGetColorWell1DUIElement(con->colorWell1D0), 10, NA_LAYOUT_MIN);
        naAddLayoutSection(colorValueCondensedRowHeight, zeroPadding);
          naAddLayoutElement(con->label1, 0, colorComponentWidth);
          naAddLayoutElement(con->textField1, colorComponentMarginH, textFieldValueWidth);
          naAddLayoutElement(cpGetColorWell1DUIElement(con->colorWell1D1), 10, NA_LAYOUT_MIN);
        naAddLayoutSection(colorValueCondensedRowHeight, zeroPadding);
          naAddLayoutElement(con->label2, 0, colorComponentWidth);
          naAddLayoutElement(con->textField2, colorComponentMarginH, textFieldValueWidth);
          naAddLayoutElement(cpGetColorWell1DUIElement(con->colorWell1D2), 10, NA_LAYOUT_MIN);
      naEndLayout();

  naEndLayout();
  
  return con;
}



void cpDeallocHSVHSLColorController(CPHSVHSLColorController* con) {
  cpDeallocColorWell2D(con->colorWell2D);
  cpDeallocColorWell1D(con->colorWell1D0);
  cpDeallocColorWell1D(con->colorWell1D1);
  cpDeallocColorWell1D(con->colorWell1D2);
  cpClearColorController(&(con->baseController));
  naFree(con);
}



const void* cpGetHSVHSLColorControllerColorData(const CPHSVHSLColorController* con) {
  return &(con->color);
}



void cpSetHSVHSLColorControllerColorData(CPHSVHSLColorController* con, const void* data) {
  cmlCpy3(con->color, data);
}



void cpComputeHSVHSLColorController(CPHSVHSLColorController* con) {
  HSVHSLSelect hsvhslSelect = cpGetPrefsHSVHSLSelect();
  CMLColorType colorType = (hsvhslSelect == HSV) ? CML_COLOR_HSV : CML_COLOR_HSL;
  CMLColorMachine* cm = cpGetCurrentColorMachine();

  CMLColorType currentColorType = cpGetCurrentColorType();
  const float* currentColorData = cpGetCurrentColorData();
  CMLColorConverter converter = cmlGetColorConverter(colorType, currentColorType);
  converter(cm, con->color, currentColorData, 1);

  cpComputeColorWell2D(con->colorWell2D);
  cpComputeColorWell1D(con->colorWell1D0);
  cpComputeColorWell1D(con->colorWell1D1);
  cpComputeColorWell1D(con->colorWell1D2);
}



void cpUpdateHSVHSLColorController(CPHSVHSLColorController* con) {
  HSVHSLSelect hsvhslSelect = cpGetPrefsHSVHSLSelect();
  
  naSetRadioState(con->radioHSV, hsvhslSelect == HSV);
  naSetRadioState(con->radioHSL, hsvhslSelect == HSL);
  
  if(hsvhslSelect == HSV) {
    naSetLabelText(con->label0, cpTranslate(CPHSVColorChannelH));
    naSetLabelText(con->label1, cpTranslate(CPHSVColorChannelS));
    naSetLabelText(con->label2, cpTranslate(CPHSVColorChannelV));
  }else{
    naSetLabelText(con->label0, cpTranslate(CPHSLColorChannelH));
    naSetLabelText(con->label1, cpTranslate(CPHSLColorChannelS));
    naSetLabelText(con->label2, cpTranslate(CPHSLColorChannelL));
  }
  
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
