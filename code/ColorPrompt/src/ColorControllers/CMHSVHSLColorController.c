
#include "CMColorController.h"

#include "../CPColorPromptApplication.h"
#include "../CPDesign.h"
#include "../CPPreferences.h"
#include "../CPTranslations.h"
#include "Displays/CMColorWell1D.h"
#include "Displays/CMColorWell2D.h"
#include "CMHSVHSLColorController.h"

#include "NAApp.h"



struct CMHSVHSLColorController{
  CMColorController baseController;
  
  CMColorWell2D* colorWell2D;

  NASpace* channelSpace;
  NARadio* radioHSV;
  NARadio* radioHSL;
  NALabel* label0;
  NALabel* label1;
  NALabel* label2;
  NATextField* textField0;
  NATextField* textField1;
  NATextField* textField2;
  CMColorWell1D* colorWell1D0;
  CMColorWell1D* colorWell1D1;
  CMColorWell1D* colorWell1D2;

  CMLVec3 color;
};



typedef enum {
  HSV,
  HSL
} HSVHSLSelect;



NABool cmHSVHSLSelectionChanged(NAReaction reaction){
  CMHSVHSLColorController* con = (CMHSVHSLColorController*)reaction.controller;
  
  HSVHSLSelect hsvhslSelect = (HSVHSLSelect)naGetPreferencesEnum(cmPrefs[CMHSVHSLSelect]);
  CMLColorType oldColorType = (hsvhslSelect == HSV) ? CML_COLOR_HSV : CML_COLOR_HSL;
  CMLColorType newColorType = oldColorType;

  if(reaction.uiElement == con->radioHSV){
    naSetPreferencesEnum(cmPrefs[CMHSVHSLSelect], HSV);
    newColorType = CML_COLOR_HSV;
  }else if(reaction.uiElement == con->radioHSL){
    naSetPreferencesEnum(cmPrefs[CMHSVHSLSelect], HSL);
    newColorType = CML_COLOR_HSL;
  }

  CMLColorMachine* cm = cmGetCurrentColorMachine();
  CMLColorConverter converter = cmlGetColorConverter(newColorType, oldColorType);
  converter(cm, con->color, con->color, 1);

  cmSetColorControllerColorType(&(con->baseController), newColorType);
  cmSetCurrentColorController(&(con->baseController));
  cmUpdateColor();
  
  return NA_TRUE;
}



NABool cmChannelValueEdited(NAReaction reaction){
  CMHSVHSLColorController* con = (CMHSVHSLColorController*)reaction.controller;
  
  if(reaction.uiElement == con->textField0){
    con->color[0] = (float)naGetTextFieldDouble(con->textField0);
  }else if(reaction.uiElement == con->textField1){
    con->color[1] = (float)naGetTextFieldDouble(con->textField1);
  }else if(reaction.uiElement == con->textField2){
    con->color[2] = (float)naGetTextFieldDouble(con->textField2);
  }
  
  cmSetCurrentColorController(&(con->baseController));
  cmUpdateColor();
  
  return NA_TRUE;
}



CMHSVHSLColorController* cmAllocHSVHSLColorController(void){
  HSVHSLSelect hsvhslSelect = (HSVHSLSelect)naInitPreferencesEnum(cmPrefs[CMHSVHSLSelect], HSV);
  CMLColorType colorType = (hsvhslSelect == HSV) ? CML_COLOR_HSV : CML_COLOR_HSL;

  CMHSVHSLColorController* con = naAlloc(CMHSVHSLColorController);
  
  cmInitColorController(&(con->baseController), colorType);
  
  con->colorWell2D = cmAllocColorWell2D(&(con->baseController), 2);

  con->channelSpace = naNewSpace(naMakeSize(1, 1));
  con->radioHSV = naNewRadio(cmTranslate(CMColorSpaceHSV), radioSelectWidth);
  con->radioHSL = naNewRadio(cmTranslate(CMColorSpaceHSL), radioSelectWidth);
  naAddUIReaction(con->radioHSV, NA_UI_COMMAND_PRESSED, cmHSVHSLSelectionChanged, con);
  naAddUIReaction(con->radioHSL, NA_UI_COMMAND_PRESSED, cmHSVHSLSelectionChanged, con);
  
  con->label0 = cmNewColorComponentLabel("");
  con->label1 = cmNewColorComponentLabel("");
  con->label2 = cmNewColorComponentLabel("");
  con->textField0 = cmNewValueTextField(cmChannelValueEdited, con);
  con->textField1 = cmNewValueTextField(cmChannelValueEdited, con);
  con->textField2 = cmNewValueTextField(cmChannelValueEdited, con);
  con->colorWell1D0 = cmAllocColorWell1D(&(con->baseController), con->color, 0);
  con->colorWell1D1 = cmAllocColorWell1D(&(con->baseController), con->color, 1);
  con->colorWell1D2 = cmAllocColorWell1D(&(con->baseController), con->color, 2);

  naSetUIElementNextTabElement(con->textField0, con->textField1);
  naSetUIElementNextTabElement(con->textField1, con->textField2);
  naSetUIElementNextTabElement(con->textField2, con->textField0);

  cmBeginUILayout(con->channelSpace, naMakeBezel4Zero());
  cmAddUIPos(0, (int)((colorWell2DSize - (4 * 25. + radioChannelCenteringOffset)) / 2.)); // center the channels
  cmAddUIRowH(con->radioHSV, colorValueCondensedRowHeight, colorComponentWidth + colorComponentMarginH);
  cmAddUICol(con->radioHSL, 10);
  cmAddUIPos(0, radioChannelOffset);
  
  cmAddUIRow(con->label0, colorValueCondensedRowHeight);
  cmAddUICol(con->textField0, colorComponentMarginH);
  cmAddUIColV(cmGetColorWell1DUIElement(con->colorWell1D0), 10, colorWell1DOffset);
  cmAddUIRow(con->label1, colorValueCondensedRowHeight);
  cmAddUICol(con->textField1, colorComponentMarginH);
  cmAddUIColV(cmGetColorWell1DUIElement(con->colorWell1D1), 10, colorWell1DOffset);
  cmAddUIRow(con->label2, colorValueCondensedRowHeight);
  cmAddUICol(con->textField2, colorComponentMarginH);
  cmAddUIColV(cmGetColorWell1DUIElement(con->colorWell1D2), 10, colorWell1DOffset);
  cmEndUILayout();
  
  cmBeginUILayout(con->baseController.space, colorWellBezel);
  cmAddUIRow(cmGetColorWell2DUIElement(con->colorWell2D), 0);
  cmAddUICol(con->channelSpace, colorWell2DRightMargin);
  cmEndUILayout();

  return con;
}



void cmDeallocHSVHSLColorController(CMHSVHSLColorController* con){
  cmDeallocColorWell2D(con->colorWell2D);
  cmDeallocColorWell1D(con->colorWell1D0);
  cmDeallocColorWell1D(con->colorWell1D1);
  cmDeallocColorWell1D(con->colorWell1D2);
  cmClearColorController(&(con->baseController));
  naFree(con);
}



const void* cmGetHSVHSLColorControllerColorData(const CMHSVHSLColorController* con){
  return &(con->color);
}



void cmSetHSVHSLColorControllerColorData(CMHSVHSLColorController* con, const void* data){
  cmlCpy3(con->color, data);
}



void cmUpdateHSVHSLColorController(CMHSVHSLColorController* con){
  cmUpdateColorController(&(con->baseController));

  HSVHSLSelect hsvhslSelect = (HSVHSLSelect)naGetPreferencesEnum(cmPrefs[CMHSVHSLSelect]);
  CMLColorType colorType = (hsvhslSelect == HSV) ? CML_COLOR_HSV : CML_COLOR_HSL;
  
  naSetRadioState(con->radioHSV, hsvhslSelect == HSV);
  naSetRadioState(con->radioHSL, hsvhslSelect == HSL);
  
  if(hsvhslSelect == HSV){
    naSetLabelText(con->label0, cmTranslate(CMHSVColorChannelH));
    naSetLabelText(con->label1, cmTranslate(CMHSVColorChannelS));
    naSetLabelText(con->label2, cmTranslate(CMHSVColorChannelV));
  }else{
    naSetLabelText(con->label0, cmTranslate(CMHSLColorChannelH));
    naSetLabelText(con->label1, cmTranslate(CMHSLColorChannelS));
    naSetLabelText(con->label2, cmTranslate(CMHSLColorChannelL));
  }
  
  CMLColorMachine* cm = cmGetCurrentColorMachine();
  CMLColorType currentColorType = cmGetCurrentColorType();
  const float* currentColorData = cmGetCurrentColorData();
  CMLColorConverter converter = cmlGetColorConverter(colorType, currentColorType);
  converter(cm, con->color, currentColorData, 1);
  
  cmUpdateColorWell2D(con->colorWell2D);

  naSetTextFieldText(
    con->textField0,
    naAllocSprintf(NA_TRUE, "%3.03f", con->color[0]));
  naSetTextFieldText(
    con->textField1,
    naAllocSprintf(NA_TRUE, "%1.05f", con->color[1]));
  naSetTextFieldText(
    con->textField2,
    naAllocSprintf(NA_TRUE, "%1.05f", con->color[2]));

  cmUpdateColorWell1D(con->colorWell1D0);
  cmUpdateColorWell1D(con->colorWell1D1);
  cmUpdateColorWell1D(con->colorWell1D2);
}
