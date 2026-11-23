
#include "CPColorController.h"

#include "../CPColorPrestoApplication.h"
#include "../CPDesign.h"
#include "../Preferences/CPPreferences.h"
#include "../CPTranslations.h"
#include "Displays/CPColorWell1D.h"
#include "Displays/CPColorWell2D.h"
#include "CPYuvYupvpColorController.h"

#include "NAApp/NAApp.h"
#include "NAUtility/NAString.h"

struct CPYuvYupvpColorController{
  CPColorController baseController;
  
  CPColorWell2D* colorWell2D;

  NASpace* channelSpace;
  NARadio* radioYuv;
  NARadio* radioYupvp;
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




void cp_YuvYupvpSelectionChanged(NAReaction reaction) {
  CPYuvYupvpColorController* con = (CPYuvYupvpColorController*)reaction.controller;
  
  YuvYupvpSelect yuvyupvpSelect = cpGetPrefsYuvYupvpSelect();
  CMLColorType oldColorType = (yuvyupvpSelect == Yuv) ? CML_COLOR_Yuv : CML_COLOR_Yupvp;
  CMLColorType newColorType = oldColorType;

  if(reaction.uiElement == con->radioYuv) {
    cpSetPrefsYuvYupvpSelect(Yuv);
    newColorType = CML_COLOR_Yuv;
  }else if(reaction.uiElement == con->radioYupvp) {
    cpSetPrefsYuvYupvpSelect(Yupvp);
    newColorType = CML_COLOR_Yupvp;
  }

  CMLColorMachine* cm = cpGetCurrentColorMachine();
  CMLColorConverter converter = cmlGetColorConverter(newColorType, oldColorType);
  converter(cm, con->color, con->color, 1);

  cpSetColorControllerColorType(&(con->baseController), newColorType);
  cpSetCurrentColorController(&(con->baseController));
  cpUpdateColor();
}



void cp_YuvValueEdited(NAReaction reaction) {
  CPYuvYupvpColorController* con = (CPYuvYupvpColorController*)reaction.controller;
  
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



CPYuvYupvpColorController* cpAllocYuvYupvpColorController(void) {
  YuvYupvpSelect yuvyupvpSelect = cpGetPrefsYuvYupvpSelect();
  CMLColorType colorType = (yuvyupvpSelect == Yuv) ? CML_COLOR_Yuv : CML_COLOR_Yupvp;

  CPYuvYupvpColorController* con = naAlloc(CPYuvYupvpColorController);
  
  cpInitColorController(&(con->baseController), colorType);
  
  con->colorWell2D = cpAllocColorWell2D(&(con->baseController), 0);

  con->channelSpace = naNewSpace();
  con->radioYuv = naNewRadio(cpTranslate(CPColorSpaceYuv));
  con->radioYupvp = naNewRadio(cpTranslate(CPColorSpaceYupvp));
  naAddUIReaction(con->radioYuv, NA_UI_COMMAND_PRESSED, cp_YuvYupvpSelectionChanged, con);
  naAddUIReaction(con->radioYupvp, NA_UI_COMMAND_PRESSED, cp_YuvYupvpSelectionChanged, con);

  con->label0 = cpNewColorComponentLabel(cpTranslate(CPYuvColorChannelY));
  con->label1 = cpNewColorComponentLabel(cpTranslate(CPYuvColorChannelup));
  con->label2 = cpNewColorComponentLabel(cpTranslate(CPYuvColorChannelvp));
  con->textField0 = cpNewValueTextField(cp_YuvValueEdited, con);
  con->textField1 = cpNewValueTextField(cp_YuvValueEdited, con);
  con->textField2 = cpNewValueTextField(cp_YuvValueEdited, con);
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
          naAddLayoutElement(con->radioYuv, colorComponentWidth + colorComponentMarginH, radioSelectWidth);
          naAddLayoutElement(con->radioYupvp, 10, radioSelectWidth);
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



void cpDeallocYuvYupvpColorController(CPYuvYupvpColorController* con) {
  cpDeallocColorWell2D(con->colorWell2D);
  cpDeallocColorWell1D(con->colorWell1D0);
  cpDeallocColorWell1D(con->colorWell1D1);
  cpDeallocColorWell1D(con->colorWell1D2);
  cpClearColorController(&(con->baseController));
  naFree(con);
}



const void* cpGetYuvYupvpColorControllerColorData(const CPYuvYupvpColorController* con) {
  return &(con->color);
}



void cpSetYuvYupvpColorControllerColorData(CPYuvYupvpColorController* con, const void* data) {
  cmlCpy3(con->color, data);
}



void cpComputeYuvYupvpColorController(CPYuvYupvpColorController* con) {
  YuvYupvpSelect yuvyupvpSelect = cpGetPrefsYuvYupvpSelect();
  CMLColorType colorType = (yuvyupvpSelect == Yuv) ? CML_COLOR_Yuv : CML_COLOR_Yupvp;
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
 
 

void cpUpdateYuvYupvpColorController(CPYuvYupvpColorController* con) {
  YuvYupvpSelect yuvyupvpSelect = cpGetPrefsYuvYupvpSelect();
  
  naSetRadioState(con->radioYuv, yuvyupvpSelect == Yuv);
  naSetRadioState(con->radioYupvp, yuvyupvpSelect == Yupvp);
  
  if(yuvyupvpSelect == Yuv) {
    naSetLabelText(con->label0, cpTranslate(CPYuvColorChannelY));
    naSetLabelText(con->label1, cpTranslate(CPYuvColorChannelu));
    naSetLabelText(con->label2, cpTranslate(CPYuvColorChannelv));
  }else{
    naSetLabelText(con->label0, cpTranslate(CPYuvColorChannelY));
    naSetLabelText(con->label1, cpTranslate(CPYuvColorChannelup));
    naSetLabelText(con->label2, cpTranslate(CPYuvColorChannelvp));
  }

  cpUpdateColorWell2D(con->colorWell2D);

  naSetTextFieldText(
    con->textField0,
    naAllocSprintf(NA_TRUE, "%1.05f", con->color[0]));
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
