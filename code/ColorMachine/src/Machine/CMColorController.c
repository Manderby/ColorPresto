
#include "CMColorController.h"
#include "CMHSLColorController.h"
#include "CMHSVColorController.h"
#include "NAApp.h"



NABool cmColorControllerMouseDown(NAReaction reaction){
  CMColorController* con = reaction.controller;
  
  cmSetCurrentColorController(con);
  
  return NA_TRUE;
}



void cmInitColorController(CMColorController* con, CMLColorType colorType){
  con->space = naNewSpace(naMakeSize(300, 100));
  naAddUIReaction(con->space, NA_UI_COMMAND_MOUSE_DOWN, cmColorControllerMouseDown, con);
  
  con->active = NA_FALSE;
  con->colorType = colorType;
}



void cmClearColorController(CMColorController* con){
}



void cmSetColorControllerActive(CMColorController* con, NABool active){
  con->active = active;
}



CMLColorType cmGetColorControllerColorType(const CMColorController* con){
  return con->colorType;
}



const void* cmGetColorControllerColorData(const CMColorController* con){
  switch(con->colorType){
  case CML_COLOR_HSL: return cmGetHSLColorControllerColorData((const CMHSLColorController*)con); 
  case CML_COLOR_HSV: return cmGetHSVColorControllerColorData((const CMHSVColorController*)con);
  default: return NA_NULL;
  }
}




NASpace* cmGetColorControllerUIElement(CMColorController* con){
  return con->space;
}



void cmUpdateColorController(CMColorController* con){
  naSetSpaceAlternateBackground(con->space, con->active);
}
