
#include "CPDesign.h"
#include "NAUtility/NAMemory.h"



NAFont* boldFont;
NAFont* monoFont;



void cpStartupDesign(){
  boldFont = naCreateFontWithPreset(NA_FONT_KIND_TITLE, NA_FONT_SIZE_DEFAULT);
//  monoFont = naCreateFontWithPreset(NA_FONT_KIND_MONOSPACE, NA_FONT_SIZE_DEFAULT);
//  monoFont = naCreateFont("Helvetica", 0, 13);
  monoFont = naCreateFontWithPreset(NA_FONT_KIND_SYSTEM, NA_FONT_SIZE_DEFAULT);
}



void cpShutdownDesign(){
  naRelease(boldFont);
  naRelease(monoFont);
}



NALabel* cpNewTitleLabel(const NAUTF8Char* text, double width){
  NALabel* label = naNewLabel(text, width);
  naSetLabelFont(label, boldFont);
  return label;
}



NALabel* cpNewValueLabel(){
  NALabel* label = naNewLabel("", labelValueWidth);
  naSetLabelTextAlignment(label, NA_TEXT_ALIGNMENT_RIGHT);
  naSetLabelFont(label, monoFont);
  return label;
}



NALabel* cpNewColorComponentLabel(const NAUTF8Char* string){
  NALabel* label = naNewLabel(string, colorComponentWidth);
  naSetLabelTextAlignment(label, NA_TEXT_ALIGNMENT_RIGHT);
  return label;
}



NALabel* cpNewThreeValueLabel(){
  NALabel* label = naNewLabel("", labelValueWidth);
  naSetLabelHeight(label, threeValueHeight);
  naSetLabelFont(label, monoFont);
  naSetLabelTextAlignment(label, NA_TEXT_ALIGNMENT_RIGHT);
  return label;
}



NATextField* cpNewValueTextField(NAReactionCallback reactionCallback, void* con){
  NATextField* textField = naNewTextField(textFieldValueWidth);
  naSetTextFieldFont(textField, monoFont);
  naSetTextFieldTextAlignment(textField, NA_TEXT_ALIGNMENT_RIGHT);
  naAddUIReaction(textField, NA_UI_COMMAND_EDIT_FINISHED, reactionCallback, con);
  return textField;
}

NATextField* cpNewBigValueTextField(NAReactionCallback reactionCallback, void* con){
  NATextField* textField = naNewTextField(colorWell1DSize);
  naSetTextFieldFont(textField, monoFont);
  naSetTextFieldTextAlignment(textField, NA_TEXT_ALIGNMENT_RIGHT);
  naAddUIReaction(textField, NA_UI_COMMAND_EDIT_FINISHED, reactionCallback, con);
  return textField;
}



NASpace* curDesignSpace = NA_NULL;
NABorder2D curDesignBorder;
NAPos curDesignPos = {0., 0.};
double maxDesignWidth = 0.;
double curDesignRowHeight = 0.;
NABool curDesignRowHeightFixed = NA_FALSE;

void cpBeginUILayout(NASpace* space, NABorder2D border){
  NASize size = naGetUIElementRect(space).size;
  curDesignSpace = space;
  curDesignBorder = border;
  curDesignPos = naMakePos(border.left, size.height - border.top);
  maxDesignWidth = border.left;
  curDesignRowHeight = 0.;
  curDesignRowHeightFixed = NA_FALSE;
}

void cpAddUIPos(double x, double y){
  #if NA_DEBUG
    if(!curDesignSpace)
      naError("No space defined for design. Use cpBeginUILayout");
  #endif
  curDesignPos.x += x;
  curDesignPos.y -= y;
}

void cp_AddLayoutRowPlain(void* child, NASize size, double vOffset){
  if(curDesignRowHeightFixed){
    naAddSpaceChild(curDesignSpace, child, naMakePos(curDesignPos.x, curDesignPos.y - curDesignRowHeight + vOffset));
  }else{
    naAddSpaceChild(curDesignSpace, child, naMakePos(curDesignPos.x, curDesignPos.y - size.height));
    curDesignRowHeight = naMax(curDesignRowHeight, size.height);
  }
  curDesignPos.x += size.width;
  maxDesignWidth = naMax(maxDesignWidth, curDesignPos.x);
}

void cpAddUIRow(void* child, double rowHeight){
  #if NA_DEBUG
    if(!curDesignSpace)
      naError("No space defined for design. Use cpBeginUILayout");
  #endif
  NASize size = naGetUIElementRect(child).size;
  curDesignPos.x = curDesignBorder.left;
  curDesignPos.y -= curDesignRowHeight;
  if(rowHeight){
    curDesignRowHeightFixed = NA_TRUE;
    curDesignRowHeight = rowHeight;
  }else{
    curDesignRowHeightFixed = NA_FALSE;
    curDesignRowHeight = size.height;
  }
  cp_AddLayoutRowPlain(child, size, 0.);
}

void cpAddUIRowH(void* child, double rowHeight, double hOffset){
  #if NA_DEBUG
    if(!curDesignSpace)
      naError("No space defined for design. Use cpBeginUILayout");
  #endif
  curDesignPos.x += hOffset;
  NASize size = naGetUIElementRect(child).size;
  curDesignPos.x = hOffset + curDesignBorder.left;
  curDesignPos.y -= curDesignRowHeight;
  if(rowHeight){
    curDesignRowHeightFixed = NA_TRUE;
    curDesignRowHeight = rowHeight;
  }else{
    curDesignRowHeightFixed = NA_FALSE;
    curDesignRowHeight = size.height;
  }
  cp_AddLayoutRowPlain(child, size, 0.);
}

void cpAddUICol(void* child, double marginLeft){
  #if NA_DEBUG
    if(!curDesignSpace)
      naError("No space defined for design. Use cpBeginUILayout");
  #endif
  NASize size = naGetUIElementRect(child).size;
  curDesignPos.x += marginLeft;
  cp_AddLayoutRowPlain(child, size, 0.);
}

void cpAddUIColV(void* child, double marginLeft, double vOffset){
  #if NA_DEBUG
    if(!curDesignSpace)
      naError("No space defined for design. Use cpBeginUILayout");
  #endif
  NASize size = naGetUIElementRect(child).size;
  curDesignPos.x += marginLeft;
  cp_AddLayoutRowPlain(child, size, vOffset);
}

void cpEndUILayout(){
  NARect spaceRect = naGetUIElementRect(curDesignSpace);
  double prevHeight = spaceRect.size.height;
  spaceRect.size.width = maxDesignWidth + curDesignBorder.right;
  double newHeight = spaceRect.size.height - (curDesignPos.y - curDesignRowHeight) + curDesignBorder.bottom;
  spaceRect.size.height = newHeight;
  naSetUIElementRect(curDesignSpace, spaceRect);

  naShiftSpaceChilds(curDesignSpace, naMakePos(0, spaceRect.size.height - prevHeight));

  NAWindow* window = naGetUIElementWindow(curDesignSpace);
  if(window){
    NASpace* contentSpace = naGetWindowContentSpace(window);
    if(contentSpace == curDesignSpace){
      NARect windowRect = naGetUIElementRect(window);
      windowRect.size = spaceRect.size;
      naSetUIElementRect(window, windowRect);
    }
  }

  curDesignSpace = NA_NULL;
}
