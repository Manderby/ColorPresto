
#include "CMColorController.h"

#include "../CMColorMachineApplication.h"
#include "../CMDesign.h"
#include "../CMPreferences.h"
#include "../CMTranslations.h"
#include "Displays/CMColorWell1D.h"
#include "Displays/CMColorWell2D.h"
#include "CMLabLchColorController.h"

#include "NAApp.h"

struct CMLabLchColorController{
  CMColorController baseController;
  
  CMColorWell2D* colorWell2D;

  NASpace* channelSpace;
  NARadio* radioLab;
  NARadio* radioLch;
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
  Lab,
  Lch
} LabLchSelect;



NABool cmLabLchSelectionChanged(NAReaction reaction){
  CMLabLchColorController* con = (CMLabLchColorController*)reaction.controller;
  
  LabLchSelect lablchSelect = (LabLchSelect)naGetPreferencesEnum(cmPrefs[CMLabLchSelect]);
  CMLColorType oldColorType = (lablchSelect == Lab) ? CML_COLOR_Lab : CML_COLOR_Lch;
  CMLColorType newColorType = oldColorType;

  if(reaction.uiElement == con->radioLab){
    naSetPreferencesEnum(cmPrefs[CMLabLchSelect], Lab);
    newColorType = CML_COLOR_Lab;
  }else if(reaction.uiElement == con->radioLch){
    naSetPreferencesEnum(cmPrefs[CMLabLchSelect], Lch);
    newColorType = CML_COLOR_Lch;
  }

  CMLColorMachine* cm = cmGetCurrentColorMachine();
  CMLColorConverter converter = cmlGetColorConverter(newColorType, oldColorType);
  converter(cm, con->color, con->color, 1);

  cmSetColorControllerColorType(&(con->baseController), newColorType);
  cmSetCurrentColorController(&(con->baseController));
  cmUpdateColor();
  
  return NA_TRUE;
}



NABool cmLabValueEdited(NAReaction reaction){
  CMLabLchColorController* con = (CMLabLchColorController*)reaction.controller;
  
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



CMLabLchColorController* cmAllocLabLchColorController(void){
  LabLchSelect lablchSelect = (LabLchSelect)naInitPreferencesEnum(cmPrefs[CMLabLchSelect], Lab);
  CMLColorType colorType = (lablchSelect == Lab) ? CML_COLOR_Lab : CML_COLOR_Lch;

  CMLabLchColorController* con = naAlloc(CMLabLchColorController);
  
  cmInitColorController(&(con->baseController), colorType);
  
  con->colorWell2D = cmAllocColorWell2D(&(con->baseController), 0);

  con->channelSpace = naNewSpace(naMakeSize(1, 1));
  con->radioLab = naNewRadio(cmTranslate(CMColorSpaceLab), radioSelectWidth);
  con->radioLch = naNewRadio(cmTranslate(CMColorSpaceLch), radioSelectWidth);
  naAddUIReaction(con->radioLab, NA_UI_COMMAND_PRESSED, cmLabLchSelectionChanged, con);
  naAddUIReaction(con->radioLch, NA_UI_COMMAND_PRESSED, cmLabLchSelectionChanged, con);

  con->label0 = cmNewColorComponentLabel("");
  con->label1 = cmNewColorComponentLabel("");
  con->label2 = cmNewColorComponentLabel("");
  con->textField0 = cmNewValueTextField(cmLabValueEdited, con);
  con->textField1 = cmNewValueTextField(cmLabValueEdited, con);
  con->textField2 = cmNewValueTextField(cmLabValueEdited, con);
  con->colorWell1D0 = cmAllocColorWell1D(&(con->baseController), con->color, 0);
  con->colorWell1D1 = cmAllocColorWell1D(&(con->baseController), con->color, 1);
  con->colorWell1D2 = cmAllocColorWell1D(&(con->baseController), con->color, 2);

  naSetUIElementNextTabElement(con->textField0, con->textField1);
  naSetUIElementNextTabElement(con->textField1, con->textField2);
  naSetUIElementNextTabElement(con->textField2, con->textField0);

  cmBeginUILayout(con->channelSpace, naMakeBezel4Zero());
  cmAddUIPos(0, (int)((colorWell2DSize - (4 * 25. + 10.)) / 2.)); // center the channels
  cmAddUIRowH(con->radioLab, colorValueCondensedRowHeight, colorComponentWidth + colorComponentMarginH);
  cmAddUICol(con->radioLch, 10);
  cmAddUIPos(0, 5);
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
  cmAddUICol(con->channelSpace, 10);
  cmEndUILayout();

  return con;
}



void cmDeallocLabLchColorController(CMLabLchColorController* con){
  cmDeallocColorWell2D(con->colorWell2D);
  cmDeallocColorWell1D(con->colorWell1D0);
  cmDeallocColorWell1D(con->colorWell1D1);
  cmDeallocColorWell1D(con->colorWell1D2);
  cmClearColorController(&(con->baseController));
  naFree(con);
}



const void* cmGetLabLchColorControllerColorData(const CMLabLchColorController* con){
  return &(con->color);
}



void cmSetLabLchColorControllerColorData(CMLabLchColorController* con, const void* data){
  cmlCpy3(con->color, data);
}



void cmUpdateLabLchColorController(CMLabLchColorController* con){
  CMLColorMachine* cm = cmGetCurrentColorMachine();
  cmUpdateColorController(&(con->baseController));

  LabLchSelect lablchSelect = (LabLchSelect)naGetPreferencesEnum(cmPrefs[CMLabLchSelect]);
  CMLColorType colorType = (lablchSelect == Lab) ? CML_COLOR_Lab : CML_COLOR_Lch;
  
  naSetRadioState(con->radioLab, lablchSelect == Lab);
  naSetRadioState(con->radioLch, lablchSelect == Lch);
  
  switch(cmlGetLabColorSpace(cm)){
  case CML_LAB_CIELAB:
    naSetLabelText(con->label0, cmTranslate(CMLabColorChannelLStar));
    break;
  default:
    naSetLabelText(con->label0, cmTranslate(CMLabColorChannelL));
  }

  if(lablchSelect == Lab){
    switch(cmlGetLabColorSpace(cm)){
    case CML_LAB_CIELAB:
      naSetLabelText(con->label1, cmTranslate(CMLabColorChannelaStar));
      naSetLabelText(con->label2, cmTranslate(CMLabColorChannelbStar));
      break;
    default:
      naSetLabelText(con->label1, cmTranslate(CMLabColorChannela));
      naSetLabelText(con->label2, cmTranslate(CMLabColorChannelb));
    }
  }else{
    naSetLabelText(con->label1, cmTranslate(CMLchColorChannelc));
    naSetLabelText(con->label2, cmTranslate(CMLchColorChannelh));
  }

  CMLColorType currentColorType = cmGetCurrentColorType();
  const float* currentColorData = cmGetCurrentColorData();
  CMLColorConverter labConverter = cmlGetColorConverter(colorType, currentColorType);
  labConverter(cm, con->color, currentColorData, 1);
  
  cmUpdateColorWell2D(con->colorWell2D);

  naSetTextFieldText(
    con->textField0,
    naAllocSprintf(NA_TRUE, "%3.03f", con->color[0]));
  naSetTextFieldText(
    con->textField1,
    naAllocSprintf(NA_TRUE, "%3.02f", con->color[1]));
  naSetTextFieldText(
    con->textField2,
    naAllocSprintf(NA_TRUE, "%3.02f", con->color[2]));

  cmUpdateColorWell1D(con->colorWell1D0);
  cmUpdateColorWell1D(con->colorWell1D1);
  cmUpdateColorWell1D(con->colorWell1D2);
}
