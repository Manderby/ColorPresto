
#include "CPColorController.h"

#include "../CPColorPrestoApplication.h"
#include "../CPDesign.h"
#include "../CPTranslations.h"
#include "CPGrayColorController.h"
#include "Displays/CPColorWell1D.h"
#include "Displays/CPGrayColorWell.h"

#include "NAApp/NAApp.h"
#include "NAUtility/NAString.h"

struct CPGrayColorController{
  CPColorController baseController;
  
  CPGrayColorWell* display;
  
  NASpace* channelSpace;
  NALabel* labelGray;
  NATextField* textFieldGray;
  CPColorWell1D* colorWell1DGray;

  float grayColor;
};



void cp_GrayValueEdited(NAReaction reaction) {
  CPGrayColorController* con = (CPGrayColorController*)reaction.controller;
  
  if(reaction.uiElement == con->textFieldGray) {
    con->grayColor = (float)naGetTextFieldDouble(con->textFieldGray);
  }
  
  cpSetCurrentColorController(&(con->baseController));
  cpUpdateColor();
}



CPGrayColorController* cpAllocGrayColorController(void) {
  CPGrayColorController* con = naAlloc(CPGrayColorController);
  
  cpInitColorController(&(con->baseController), CML_COLOR_Gray);
  
  con->display = cpAllocGrayColorWell(&(con->baseController));
  
  con->channelSpace = naNewSpace();
  con->labelGray = cpNewColorComponentLabel(cpTranslate(CPGrayColorChannelGr));
  con->textFieldGray = cpNewValueTextField(cp_GrayValueEdited, con);
  con->colorWell1DGray = cpAllocColorWell1D(&(con->baseController), &(con->grayColor), 0);

  NABorder2D zeroPadding = naMakeBorder2D(0., 0., 0., 0.);

  naBeginLayout(con->baseController.space, colorWellBorder);
    
    naAddLayoutSection(NA_LAYOUT_MIN, zeroPadding);
      naAddLayoutElement(cpGetGrayColorWellUIElement(con->display), 0, NA_LAYOUT_MIN);
    
      naBeginSubLayout(con->channelSpace, zeroPadding, 0, NA_LAYOUT_MIN);
        naAddLayoutSection(colorValueCondensedRowHeight, zeroPadding);
          naAddLayoutElement(con->labelGray, 0, colorComponentWidth);
          naAddLayoutElement(con->textFieldGray, colorComponentMarginH, textFieldValueWidth);
          naAddLayoutElement(cpGetColorWell1DUIElement(con->colorWell1DGray), 10, NA_LAYOUT_MIN);
      naEndLayout();

  naEndLayout();

  con->grayColor = .5;

  return con;
}



void cpDeallocGrayColorController(CPGrayColorController* con) {
  cpDeallocGrayColorWell(con->display);
  cpDeallocColorWell1D(con->colorWell1DGray);
  cpClearColorController(&(con->baseController));
  naFree(con);
}



const void* cpGetGrayColorControllerColorData(const CPGrayColorController* con) {
  return &(con->grayColor);
}



void cpSetGrayColorControllerColorData(CPGrayColorController* con, const void* data) {
  con->grayColor = *(const float*)data;
}



void cpComputeGrayColorController(CPGrayColorController* con) {
  CMLColorMachine* cm = cpGetCurrentColorMachine();

  CMLColorType currentColorType = cpGetCurrentColorType();
  const float* currentColorData = cpGetCurrentColorData();
  CMLColorConverter converter = cmlGetColorConverter(CML_COLOR_Gray, currentColorType);
  converter(cm, &(con->grayColor), currentColorData, 1);

  cpComputeColorWell1D(con->colorWell1DGray);
}



void cpUpdateGrayColorController(CPGrayColorController* con) {
  naSetTextFieldText(
    con->textFieldGray,
    naAllocSprintf(NA_TRUE, "%1.05f", con->grayColor));

  cpUpdateGrayColorWell(con->display);
  cpUpdateColorWell1D(con->colorWell1DGray);
}
