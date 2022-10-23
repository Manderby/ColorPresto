
#include "CMDesign.h"



NAFont* boldFont;
NAFont* monoFont;



void cmStartupDesign(){
  boldFont = naCreateFontWithPreset(NA_FONT_KIND_TITLE, NA_FONT_SIZE_DEFAULT);
  monoFont = naCreateFontWithPreset(NA_FONT_KIND_MONOSPACE, NA_FONT_SIZE_DEFAULT);
}



void cmShutdownDesign(){
  naRelease(boldFont);
  naRelease(monoFont);
}



NALabel* cmNewTitleLabel(const NAUTF8Char* text, double width){
  NALabel* label = naNewLabel(text, width);
  naSetLabelFont(label, boldFont);
  return label;
}



NALabel* cmNewValueLabel(){
  NALabel* label = naNewLabel("", valueWidth);
  naSetLabelFont(label, monoFont);
  return label;
}



NALabel* cmNewThreeValueLabel(){
  NALabel* label = naNewLabel("", valueWidth);
  naSetLabelHeight(label, threeValueHeight);
  naSetLabelFont(label, monoFont);
  return label;
}
