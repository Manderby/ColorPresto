
#include "CMColorController.h"

#include "../CPColorPromptApplication.h"
#include "../CPDesign.h"
#include "../CPPreferences.h"
#include "../CPTranslations.h"
#include "Displays/CMColorWell1D.h"
#include "Displays/CMColorWell2D.h"
#include "CMYuvYupvpColorController.h"

#include "NAApp.h"

struct CMYuvYupvpColorController{
  CMColorController baseController;
  
  CMColorWell2D* colorWell2D;

  NASpace* channelSpace;
  NARadio* radioYuv;
  NARadio* radioYupvp;
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
  Yuv,
  Yupvp
} YuvYupvpSelect;



NABool cmYuvYupvpSelectionChanged(NAReaction reaction){
  CMYuvYupvpColorController* con = (CMYuvYupvpColorController*)reaction.controller;
  
  YuvYupvpSelect yuvyupvpSelect = (YuvYupvpSelect)naGetPreferencesEnum(cmPrefs[CMYuvYupvpSelect]);
  CMLColorType oldColorType = (yuvyupvpSelect == Yuv) ? CML_COLOR_Yuv : CML_COLOR_Yupvp;
  CMLColorType newColorType = oldColorType;

  if(reaction.uiElement == con->radioYuv){
    naSetPreferencesEnum(cmPrefs[CMYuvYupvpSelect], Yuv);
    newColorType = CML_COLOR_Yuv;
  }else if(reaction.uiElement == con->radioYupvp){
    naSetPreferencesEnum(cmPrefs[CMYuvYupvpSelect], Yupvp);
    newColorType = CML_COLOR_Yupvp;
  }

  CMLColorMachine* cm = cmGetCurrentColorMachine();
  CMLColorConverter converter = cmlGetColorConverter(newColorType, oldColorType);
  converter(cm, con->color, con->color, 1);

  cmSetColorControllerColorType(&(con->baseController), newColorType);
  cmSetCurrentColorController(&(con->baseController));
  cmUpdateColor();
  
  return NA_TRUE;
}



NABool cmYuvValueEdited(NAReaction reaction){
  CMYuvYupvpColorController* con = (CMYuvYupvpColorController*)reaction.controller;
  
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



CMYuvYupvpColorController* cmAllocYuvColorController(void){
  YuvYupvpSelect yuvyupvpSelect = (YuvYupvpSelect)naInitPreferencesEnum(cmPrefs[CMYuvYupvpSelect], Yupvp);
  CMLColorType colorType = (yuvyupvpSelect == Yuv) ? CML_COLOR_Yuv : CML_COLOR_Yupvp;

  CMYuvYupvpColorController* con = naAlloc(CMYuvYupvpColorController);
  
  cmInitColorController(&(con->baseController), colorType);
  
  con->colorWell2D = cmAllocColorWell2D(&(con->baseController), 0);

  con->channelSpace = naNewSpace(naMakeSize(1, 1));
  con->radioYuv = naNewRadio(cmTranslate(CMColorSpaceYuv), radioSelectWidth);
  con->radioYupvp = naNewRadio(cmTranslate(CMColorSpaceYupvp), radioSelectWidth);
  naAddUIReaction(con->radioYuv, NA_UI_COMMAND_PRESSED, cmYuvYupvpSelectionChanged, con);
  naAddUIReaction(con->radioYupvp, NA_UI_COMMAND_PRESSED, cmYuvYupvpSelectionChanged, con);

  con->label0 = cmNewColorComponentLabel(cmTranslate(CMYuvColorChannelY));
  con->label1 = cmNewColorComponentLabel(cmTranslate(CMYuvColorChannelup));
  con->label2 = cmNewColorComponentLabel(cmTranslate(CMYuvColorChannelvp));
  con->textField0 = cmNewValueTextField(cmYuvValueEdited, con);
  con->textField1 = cmNewValueTextField(cmYuvValueEdited, con);
  con->textField2 = cmNewValueTextField(cmYuvValueEdited, con);
  con->colorWell1D0 = cmAllocColorWell1D(&(con->baseController), con->color, 0);
  con->colorWell1D1 = cmAllocColorWell1D(&(con->baseController), con->color, 1);
  con->colorWell1D2 = cmAllocColorWell1D(&(con->baseController), con->color, 2);

  naSetUIElementNextTabElement(con->textField0, con->textField1);
  naSetUIElementNextTabElement(con->textField1, con->textField2);
  naSetUIElementNextTabElement(con->textField2, con->textField0);

  cmBeginUILayout(con->channelSpace, naMakeBezel4Zero());
  cmAddUIPos(0, (int)((colorWell2DSize - (4 * 25. + radioChannelCenteringOffset)) / 2.)); // center the channels
  cmAddUIRowH(con->radioYuv, colorValueCondensedRowHeight, colorComponentWidth + colorComponentMarginH);
  cmAddUICol(con->radioYupvp, 10);
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



void cmDeallocYuvColorController(CMYuvYupvpColorController* con){
  cmDeallocColorWell2D(con->colorWell2D);
  cmDeallocColorWell1D(con->colorWell1D0);
  cmDeallocColorWell1D(con->colorWell1D1);
  cmDeallocColorWell1D(con->colorWell1D2);
  cmClearColorController(&(con->baseController));
  naFree(con);
}



const void* cmGetYuvColorControllerColorData(const CMYuvYupvpColorController* con){
  return &(con->color);
}



void cmSetYuvColorControllerColorData(CMYuvYupvpColorController* con, const void* data){
  cmlCpy3(con->color, data);
}



void cmUpdateYuvColorController(CMYuvYupvpColorController* con){
  cmUpdateColorController(&(con->baseController));

  YuvYupvpSelect yuvyupvpSelect = (YuvYupvpSelect)naGetPreferencesEnum(cmPrefs[CMYuvYupvpSelect]);
  CMLColorType colorType = (yuvyupvpSelect == Yuv) ? CML_COLOR_Yuv : CML_COLOR_Yupvp;
  
  naSetRadioState(con->radioYuv, yuvyupvpSelect == Yuv);
  naSetRadioState(con->radioYupvp, yuvyupvpSelect == Yupvp);
  
  if(yuvyupvpSelect == Yuv){
    naSetLabelText(con->label0, cmTranslate(CMYuvColorChannelY));
    naSetLabelText(con->label1, cmTranslate(CMYuvColorChannelu));
    naSetLabelText(con->label2, cmTranslate(CMYuvColorChannelv));
  }else{
    naSetLabelText(con->label0, cmTranslate(CMYuvColorChannelY));
    naSetLabelText(con->label1, cmTranslate(CMYuvColorChannelup));
    naSetLabelText(con->label2, cmTranslate(CMYuvColorChannelvp));
  }

  CMLColorMachine* cm = cmGetCurrentColorMachine();
  CMLColorType currentColorType = cmGetCurrentColorType();
  const float* currentColorData = cmGetCurrentColorData();
  CMLColorConverter converter = cmlGetColorConverter(colorType, currentColorType);
  converter(cm, con->color, currentColorData, 1);

  cmUpdateColorWell2D(con->colorWell2D);

  naSetTextFieldText(
    con->textField0,
    naAllocSprintf(NA_TRUE, "%1.05f", con->color[0]));
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
