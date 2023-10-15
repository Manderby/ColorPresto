
#include "CPDesign.h"



NAFont* boldFont;
NAFont* monoFont;



void cmStartupDesign(){
  boldFont = naCreateFontWithPreset(NA_FONT_KIND_TITLE, NA_FONT_SIZE_DEFAULT);
//  monoFont = naCreateFontWithPreset(NA_FONT_KIND_MONOSPACE, NA_FONT_SIZE_DEFAULT);
//  monoFont = naCreateFont("Helvetica", 0, 13);
  monoFont = naCreateFontWithPreset(NA_FONT_KIND_SYSTEM, NA_FONT_SIZE_DEFAULT);
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
  NALabel* label = naNewLabel("", labelValueWidth);
  naSetLabelTextAlignment(label, NA_TEXT_ALIGNMENT_RIGHT);
  naSetLabelFont(label, monoFont);
  return label;
}



NALabel* cmNewColorComponentLabel(const NAUTF8Char* string){
  NALabel* label = naNewLabel(string, colorComponentWidth);
  naSetLabelTextAlignment(label, NA_TEXT_ALIGNMENT_RIGHT);
  return label;
}



NALabel* cmNewThreeValueLabel(){
  NALabel* label = naNewLabel("", labelValueWidth);
  naSetLabelHeight(label, threeValueHeight);
  naSetLabelFont(label, monoFont);
  naSetLabelTextAlignment(label, NA_TEXT_ALIGNMENT_RIGHT);
  return label;
}



NATextField* cmNewValueTextField(NAReactionHandler reactionHandler, void* con){
  NATextField* textField = naNewTextField(textFieldValueWidth);
  naSetTextFieldFont(textField, monoFont);
  naSetTextFieldTextAlignment(textField, NA_TEXT_ALIGNMENT_RIGHT);
  naAddUIReaction(textField, NA_UI_COMMAND_EDIT_FINISHED, reactionHandler, con);
  return textField;
}

NATextField* cmNewBigValueTextField(NAReactionHandler reactionHandler, void* con){
  NATextField* textField = naNewTextField(colorWell1DSize);
  naSetTextFieldFont(textField, monoFont);
  naSetTextFieldTextAlignment(textField, NA_TEXT_ALIGNMENT_RIGHT);
  naAddUIReaction(textField, NA_UI_COMMAND_EDIT_FINISHED, reactionHandler, con);
  return textField;
}



NASpace* curDesignSpace = NA_NULL;
NABezel4 curDesignMargin;
NAPos curDesignPos = {0., 0.};
double maxDesignWidth = 0.;
double curDesignRowHeight = 0.;
NABool curDesignRowHeightFixed = NA_FALSE;

void cmBeginUILayout(NASpace* space, NABezel4 margin){
  NASize size = naGetUIElementRect(space).size;
  curDesignSpace = space;
  curDesignMargin = margin;
  curDesignPos = naMakePos(margin.left, size.height - margin.top);
  maxDesignWidth = margin.left;
  curDesignRowHeight = 0.;
  curDesignRowHeightFixed = NA_FALSE;
}

void cmAddUIPos(double x, double y){
  #if NA_DEBUG
    if(!curDesignSpace)
      naError("No space defined for design. Use cmBeginUILayout");
  #endif
  curDesignPos.x += x;
  curDesignPos.y -= y;
}

void cm_AddLayoutRowPlain(void* child, NASize size, double vOffset){
  if(curDesignRowHeightFixed){
    naAddSpaceChild(curDesignSpace, child, naMakePos(curDesignPos.x, curDesignPos.y - curDesignRowHeight + vOffset));
  }else{
    naAddSpaceChild(curDesignSpace, child, naMakePos(curDesignPos.x, curDesignPos.y - size.height));
    curDesignRowHeight = naMax(curDesignRowHeight, size.height);
  }
  curDesignPos.x += size.width;
  maxDesignWidth = naMax(maxDesignWidth, curDesignPos.x);
}

void cmAddUIRow(void* child, double rowHeight){
  #if NA_DEBUG
    if(!curDesignSpace)
      naError("No space defined for design. Use cmBeginUILayout");
  #endif
  NASize size = naGetUIElementRect(child).size;
  curDesignPos.x = curDesignMargin.left;
  curDesignPos.y -= curDesignRowHeight;
  if(rowHeight){
    curDesignRowHeightFixed = NA_TRUE;
    curDesignRowHeight = rowHeight;
  }else{
    curDesignRowHeightFixed = NA_FALSE;
    curDesignRowHeight = size.height;
  }
  cm_AddLayoutRowPlain(child, size, 0.);
}

void cmAddUIRowH(void* child, double rowHeight, double hOffset){
  #if NA_DEBUG
    if(!curDesignSpace)
      naError("No space defined for design. Use cmBeginUILayout");
  #endif
  curDesignPos.x += hOffset;
  NASize size = naGetUIElementRect(child).size;
  curDesignPos.x = hOffset + curDesignMargin.left;
  curDesignPos.y -= curDesignRowHeight;
  if(rowHeight){
    curDesignRowHeightFixed = NA_TRUE;
    curDesignRowHeight = rowHeight;
  }else{
    curDesignRowHeightFixed = NA_FALSE;
    curDesignRowHeight = size.height;
  }
  cm_AddLayoutRowPlain(child, size, 0.);
}

void cmAddUICol(void* child, double marginLeft){
  #if NA_DEBUG
    if(!curDesignSpace)
      naError("No space defined for design. Use cmBeginUILayout");
  #endif
  NASize size = naGetUIElementRect(child).size;
  curDesignPos.x += marginLeft;
  cm_AddLayoutRowPlain(child, size, 0.);
}

void cmAddUIColV(void* child, double marginLeft, double vOffset){
  #if NA_DEBUG
    if(!curDesignSpace)
      naError("No space defined for design. Use cmBeginUILayout");
  #endif
  NASize size = naGetUIElementRect(child).size;
  curDesignPos.x += marginLeft;
  cm_AddLayoutRowPlain(child, size, vOffset);
}

void cmEndUILayout(){
  NARect spaceRect = naGetUIElementRect(curDesignSpace);
  double prevHeight = spaceRect.size.height;
  spaceRect.size.width = maxDesignWidth + curDesignMargin.right;
  double newHeight = spaceRect.size.height - (curDesignPos.y - curDesignRowHeight) + curDesignMargin.bottom;
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
