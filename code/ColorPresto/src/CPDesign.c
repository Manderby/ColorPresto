
#include "CPDesign.h"
#include "NAUtility/NAMemory.h"



NAFont* boldFont;
NAFont* monoFont;



void cpStartupDesign() {
  boldFont = naCreateFontWithPreset(NA_FONT_KIND_TITLE, NA_FONT_SIZE_DEFAULT);
  monoFont = naCreateFontWithPreset(NA_FONT_KIND_SYSTEM, NA_FONT_SIZE_DEFAULT);
}



void cpShutdownDesign() {
  naRelease(boldFont);
  naRelease(monoFont);
}



NALabel* cpNewTitleLabel(const NAUTF8Char* text, double width) {
  NALabel* label = naNewLabel(text, width);
  naSetLabelFont(label, boldFont);
  return label;
}



NALabel* cpNewValueLabel() {
  NALabel* label = naNewLabel("", labelValueWidth);
  naSetLabelTextAlignment(label, NA_ALIGNMENT_END);
  naSetLabelFont(label, monoFont);
  return label;
}



NALabel* cpNewColorComponentLabel(const NAUTF8Char* string) {
  NALabel* label = naNewLabel(string, colorComponentWidth);
  naSetLabelTextAlignment(label, NA_ALIGNMENT_END);
  return label;
}



NALabel* cpNewThreeValueLabel() {
  NALabel* label = naNewLabel("", labelValueWidth);
  naSetLabelHeight(label, threeValueHeight);
  naSetLabelFont(label, monoFont);
  naSetLabelTextAlignment(label, NA_ALIGNMENT_END);
  return label;
}



NATextField* cpNewValueTextField(NAReactionCallback reactionCallback, void* con) {
  NATextField* textField = naNewTextField(textFieldValueWidth);
  naSetTextFieldFont(textField, monoFont);
  naSetTextFieldTextAlignment(textField, NA_ALIGNMENT_END);
  naAddUIReaction(textField, NA_UI_COMMAND_EDIT_FINISHED, reactionCallback, con);
  return textField;
}

NATextField* cpNewBigValueTextField(NAReactionCallback reactionCallback, void* con) {
  NATextField* textField = naNewTextField(colorWell1DSize);
  naSetTextFieldFont(textField, monoFont);
  naSetTextFieldTextAlignment(textField, NA_ALIGNMENT_END);
  naAddUIReaction(textField, NA_UI_COMMAND_EDIT_FINISHED, reactionCallback, con);
  return textField;
}



