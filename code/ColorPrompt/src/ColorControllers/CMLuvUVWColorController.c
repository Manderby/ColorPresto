
#include "CMColorController.h"

#include "../CPColorPromptApplication.h"
#include "../CPDesign.h"
#include "../CPPreferences.h"
#include "../CPTranslations.h"
#include "Displays/CMColorWell1D.h"
#include "Displays/CMColorWell2D.h"
#include "CMLuvUVWColorController.h"

#include "NAApp.h"

struct CMLuvUVWColorController{
  CMColorController baseController;
  
  CMColorWell2D* colorWell2D;

  NASpace* channelSpace;
  NARadio* radioLuv;
  NARadio* radioUVW;
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
  Luv,
  UVW
} LuvUVWSelect;



NABool cmLuvUVWSelectionChanged(NAReaction reaction){
  CMLuvUVWColorController* con = (CMLuvUVWColorController*)reaction.controller;
  
  LuvUVWSelect luvuvwSelect = (LuvUVWSelect)naGetPreferencesEnum(cmPrefs[CMLuvUVWSelect]);
  CMLColorType oldColorType = (luvuvwSelect == Luv) ? CML_COLOR_Luv : CML_COLOR_UVW;
  CMLColorType newColorType = oldColorType;

  if(reaction.uiElement == con->radioLuv){
    naSetPreferencesEnum(cmPrefs[CMLuvUVWSelect], Luv);
    newColorType = CML_COLOR_Luv;
  }else if(reaction.uiElement == con->radioUVW){
    naSetPreferencesEnum(cmPrefs[CMLuvUVWSelect], UVW);
    newColorType = CML_COLOR_UVW;
  }

  CMLColorMachine* cm = cmGetCurrentColorMachine();
  CMLColorConverter converter = cmlGetColorConverter(newColorType, oldColorType);
  converter(cm, con->color, con->color, 1);

  cmSetColorControllerColorType(&(con->baseController), newColorType);
  cmSetCurrentColorController(&(con->baseController));
  cmUpdateColor();
  
  return NA_TRUE;
}



NABool cmLuvValueEdited(NAReaction reaction){
  CMLuvUVWColorController* con = (CMLuvUVWColorController*)reaction.controller;
  
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



CMLuvUVWColorController* cmAllocLuvUVWColorController(void){
  LuvUVWSelect luvuvwSelect = (LuvUVWSelect)naInitPreferencesEnum(cmPrefs[CMLuvUVWSelect], Luv);
  CMLColorType colorType = (luvuvwSelect == Luv) ? CML_COLOR_Luv : CML_COLOR_UVW;

  CMLuvUVWColorController* con = naAlloc(CMLuvUVWColorController);

  cmInitColorController(&(con->baseController), colorType);
  
  con->colorWell2D = cmAllocColorWell2D(&(con->baseController), 0);

  con->channelSpace = naNewSpace(naMakeSize(1, 1));
  con->radioLuv = naNewRadio(cmTranslate(CMColorSpaceLuv), radioSelectWidth);
  con->radioUVW = naNewRadio(cmTranslate(CMColorSpaceUVW), radioSelectWidth);
  naAddUIReaction(con->radioLuv, NA_UI_COMMAND_PRESSED, cmLuvUVWSelectionChanged, con);
  naAddUIReaction(con->radioUVW, NA_UI_COMMAND_PRESSED, cmLuvUVWSelectionChanged, con);

  con->label0 = cmNewColorComponentLabel("");
  con->label1 = cmNewColorComponentLabel("");
  con->label2 = cmNewColorComponentLabel("");
  con->textField0 = cmNewValueTextField(cmLuvValueEdited, con);
  con->textField1 = cmNewValueTextField(cmLuvValueEdited, con);
  con->textField2 = cmNewValueTextField(cmLuvValueEdited, con);
  con->colorWell1D0 = cmAllocColorWell1D(&(con->baseController), con->color, 0);
  con->colorWell1D1 = cmAllocColorWell1D(&(con->baseController), con->color, 1);
  con->colorWell1D2 = cmAllocColorWell1D(&(con->baseController), con->color, 2);

  naSetUIElementNextTabElement(con->textField0, con->textField1);
  naSetUIElementNextTabElement(con->textField1, con->textField2);
  naSetUIElementNextTabElement(con->textField2, con->textField0);

  cmBeginUILayout(con->channelSpace, naMakeBezel4Zero());
  cmAddUIPos(0, (int)((colorWell2DSize - (4 * 25. + radioChannelCenteringOffset)) / 2.)); // center the channels
  cmAddUIRowH(con->radioLuv, colorValueCondensedRowHeight, colorComponentWidth + colorComponentMarginH);
  cmAddUICol(con->radioUVW, 10);
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



void cmDeallocLuvUVWColorController(CMLuvUVWColorController* con){
  cmDeallocColorWell2D(con->colorWell2D);
  cmDeallocColorWell1D(con->colorWell1D0);
  cmDeallocColorWell1D(con->colorWell1D1);
  cmDeallocColorWell1D(con->colorWell1D2);
  cmClearColorController(&(con->baseController));
  naFree(con);
}



const void* cmGetLuvUVWColorControllerColorData(const CMLuvUVWColorController* con){
  return &(con->color);
}



void cmSetLuvUVWColorControllerColorData(CMLuvUVWColorController* con, const void* data){
  cmlCpy3(con->color, data);
}



void cmUpdateLuvUVWColorController(CMLuvUVWColorController* con){
  cmUpdateColorController(&(con->baseController));

  LuvUVWSelect luvuvwSelect = (LuvUVWSelect)naGetPreferencesEnum(cmPrefs[CMLuvUVWSelect]);
  CMLColorType colorType = (luvuvwSelect == Luv) ? CML_COLOR_Luv : CML_COLOR_UVW;
  
  naSetRadioState(con->radioLuv, luvuvwSelect == Luv);
  naSetRadioState(con->radioUVW, luvuvwSelect == UVW);
  
  if(luvuvwSelect == Luv){
    naSetLabelText(con->label0, cmTranslate(CMLuvColorChannelL));
    naSetLabelText(con->label1, cmTranslate(CMLuvColorChannelu));
    naSetLabelText(con->label2, cmTranslate(CMLuvColorChannelv));
    cmSetColorWell2DFixedIndex(con->colorWell2D, 0);
  }else if(luvuvwSelect == UVW){
    naSetLabelText(con->label0, cmTranslate(CMUVWColorChannelU));
    naSetLabelText(con->label1, cmTranslate(CMUVWColorChannelV));
    naSetLabelText(con->label2, cmTranslate(CMUVWColorChannelW));
    cmSetColorWell2DFixedIndex(con->colorWell2D, 2);
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
    naAllocSprintf(NA_TRUE, "%3.02f", con->color[1]));
  naSetTextFieldText(
    con->textField2,
    naAllocSprintf(NA_TRUE, "%3.02f", con->color[2]));

  cmUpdateColorWell1D(con->colorWell1D0);
  cmUpdateColorWell1D(con->colorWell1D1);
  cmUpdateColorWell1D(con->colorWell1D2);
}
