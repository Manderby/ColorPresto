
#include "CPColorController.h"

#include "../CPColorPrestoApplication.h"
#include "../CPDesign.h"
#include "../Preferences/CPPreferences.h"
#include "../CPTranslations.h"
#include "Displays/CPColorWell1D.h"
#include "Displays/CPColorWell2D.h"
#include "CPLabLchColorController.h"

#include "NAApp/NAApp.h"

struct CPLabLchColorController{
  CPColorController baseController;
  
  CPColorWell2D* colorWell2D;

  NASpace* channelSpace;
  NARadio* radioLab;
  NARadio* radioLch;
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



NABool cp_LabLchSelectionChanged(NAReaction reaction){
  CPLabLchColorController* con = (CPLabLchColorController*)reaction.controller;
  
  LabLchSelect lablchSelect = cpGetPrefsLabLchSelect();
  CMLColorType oldColorType = (lablchSelect == Lab) ? CML_COLOR_Lab : CML_COLOR_Lch;
  CMLColorType newColorType = oldColorType;

  if(reaction.uiElement == con->radioLab){
    cpSetPrefsLabLchSelect(Lab);
    newColorType = CML_COLOR_Lab;
  }else if(reaction.uiElement == con->radioLch){
    cpSetPrefsLabLchSelect(Lch);
    newColorType = CML_COLOR_Lch;
  }

  CMLColorMachine* cm = cpGetCurrentColorMachine();
  CMLColorConverter converter = cmlGetColorConverter(newColorType, oldColorType);
  converter(cm, con->color, con->color, 1);

  cpSetColorControllerColorType(&(con->baseController), newColorType);
  cpSetCurrentColorController(&(con->baseController));
  cpUpdateColor();
  
  return NA_TRUE;
}



NABool cp_LabValueEdited(NAReaction reaction){
  CPLabLchColorController* con = (CPLabLchColorController*)reaction.controller;
  
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



CPLabLchColorController* cpAllocLabLchColorController(void){
  LabLchSelect lablchSelect = cpGetPrefsLabLchSelect();
  CMLColorType colorType = (lablchSelect == Lab) ? CML_COLOR_Lab : CML_COLOR_Lch;

  CPLabLchColorController* con = naAlloc(CPLabLchColorController);
  
  cpInitColorController(&(con->baseController), colorType);
  
  con->colorWell2D = cpAllocColorWell2D(&(con->baseController), 0);

  con->channelSpace = naNewSpace(naMakeSize(1, 1));
  con->radioLab = naNewRadio(cpTranslate(CPColorSpaceLab), radioSelectWidth);
  con->radioLch = naNewRadio(cpTranslate(CPColorSpaceLch), radioSelectWidth);
  naAddUIReaction(con->radioLab, NA_UI_COMMAND_PRESSED, cp_LabLchSelectionChanged, con);
  naAddUIReaction(con->radioLch, NA_UI_COMMAND_PRESSED, cp_LabLchSelectionChanged, con);

  con->label0 = cpNewColorComponentLabel("");
  con->label1 = cpNewColorComponentLabel("");
  con->label2 = cpNewColorComponentLabel("");
  con->textField0 = cpNewValueTextField(cp_LabValueEdited, con);
  con->textField1 = cpNewValueTextField(cp_LabValueEdited, con);
  con->textField2 = cpNewValueTextField(cp_LabValueEdited, con);
  con->colorWell1D0 = cpAllocColorWell1D(&(con->baseController), con->color, 0);
  con->colorWell1D1 = cpAllocColorWell1D(&(con->baseController), con->color, 1);
  con->colorWell1D2 = cpAllocColorWell1D(&(con->baseController), con->color, 2);

  naSetUIElementNextTabElement(con->textField0, con->textField1);
  naSetUIElementNextTabElement(con->textField1, con->textField2);
  naSetUIElementNextTabElement(con->textField2, con->textField0);

  cpBeginUILayout(con->channelSpace, naMakeBezel4Zero());
  cpAddUIPos(0, (int)((colorWell2DSize - (4 * 25. + radioChannelCenteringOffset)) / 2.)); // center the channels
  cpAddUIRowH(con->radioLab, colorValueCondensedRowHeight, colorComponentWidth + colorComponentMarginH);
  cpAddUICol(con->radioLch, 10);
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



void cpDeallocLabLchColorController(CPLabLchColorController* con){
  cpDeallocColorWell2D(con->colorWell2D);
  cpDeallocColorWell1D(con->colorWell1D0);
  cpDeallocColorWell1D(con->colorWell1D1);
  cpDeallocColorWell1D(con->colorWell1D2);
  cpClearColorController(&(con->baseController));
  naFree(con);
}



const void* cpGetLabLchColorControllerColorData(const CPLabLchColorController* con){
  return &(con->color);
}



void cpSetLabLchColorControllerColorData(CPLabLchColorController* con, const void* data){
  cmlCpy3(con->color, data);
}



void cpUpdateLabLchColorController(CPLabLchColorController* con){
  CMLColorMachine* cm = cpGetCurrentColorMachine();
  cpUpdateColorController(&(con->baseController));

  LabLchSelect lablchSelect = cpGetPrefsLabLchSelect();
  CMLColorType colorType = (lablchSelect == Lab) ? CML_COLOR_Lab : CML_COLOR_Lch;
  
  naSetRadioState(con->radioLab, lablchSelect == Lab);
  naSetRadioState(con->radioLch, lablchSelect == Lch);
  
  switch(cmlGetLabColorSpace(cm)){
  case CML_LAB_CIELAB:
    naSetLabelText(con->label0, cpTranslate(CPLabColorChannelLStar));
    break;
  default:
    naSetLabelText(con->label0, cpTranslate(CPLabColorChannelL));
  }

  if(lablchSelect == Lab){
    switch(cmlGetLabColorSpace(cm)){
    case CML_LAB_CIELAB:
      naSetLabelText(con->label1, cpTranslate(CPLabColorChannelaStar));
      naSetLabelText(con->label2, cpTranslate(CPLabColorChannelbStar));
      break;
    default:
      naSetLabelText(con->label1, cpTranslate(CPLabColorChannela));
      naSetLabelText(con->label2, cpTranslate(CPLabColorChannelb));
    }
  }else{
    naSetLabelText(con->label1, cpTranslate(CPLchColorChannelc));
    naSetLabelText(con->label2, cpTranslate(CPLchColorChannelh));
  }

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
    naAllocSprintf(NA_TRUE, "%3.02f", con->color[1]));
  naSetTextFieldText(
    con->textField2,
    naAllocSprintf(NA_TRUE, "%3.02f", con->color[2]));

  cpUpdateColorWell1D(con->colorWell1D0);
  cpUpdateColorWell1D(con->colorWell1D1);
  cpUpdateColorWell1D(con->colorWell1D2);
}
