
#include "CMCoordinateController.h"

#include "CMDesign.h"
#include "CMTranslations.h"
#include "CMWhitePoints.h"

#include "CML.h"

#include "NAApp.h"
#include "NAUtility/NABinaryData.h"
#include "NAUtility/NAMemory.h"
#include "NAUtility/NAString.h"

struct CMCoordinateController{
  NASpace* space;

  NALabel* colorSpaceLabel;
  NAPopupButton* colorSpacePopupButton;
  NALabel* coordSysLabel;
  NAPopupButton* coordSysPopupButton;

  NALabel* stepsLabel;
  NASlider* stepsSlider;

  CMThreeDeeController* parentController;

  ColorSpaceType colorSpaceType;
  CoordSysType coordSysType;
  NAInt steps3D;
};



CMLColorType cmGetCMLColorTypeFromColorSpaceType(ColorSpaceType colorSpaceType){
  CMLColorType retValue = CML_COLOR_COUNT;
  switch(colorSpaceType){
  case COLOR_SPACE_GRAY:  retValue = CML_COLOR_Gray; break;
  case COLOR_SPACE_HSL:   retValue = CML_COLOR_HSL; break;
  case COLOR_SPACE_HSV:   retValue = CML_COLOR_HSV; break;
  case COLOR_SPACE_Lab:   retValue = CML_COLOR_Lab; break;
  case COLOR_SPACE_Lch:   retValue = CML_COLOR_Lch; break;
  case COLOR_SPACE_Luv:   retValue = CML_COLOR_Luv; break;
  case COLOR_SPACE_RGB:   retValue = CML_COLOR_RGB; break;
  case COLOR_SPACE_UVW:   retValue = CML_COLOR_UVW; break;
  case COLOR_SPACE_XYZ:   retValue = CML_COLOR_XYZ; break;
  case COLOR_SPACE_YCbCr: retValue = CML_COLOR_YCbCr; break;
  case COLOR_SPACE_Ycd:   retValue = CML_COLOR_Ycd; break;
  case COLOR_SPACE_Yuv:   retValue = CML_COLOR_Yuv; break;
  case COLOR_SPACE_Yxy:   retValue = CML_COLOR_Yxy; break;
  default:
    #if NA_DEBUG
      naError("Unknown colorspace.");
    #endif
    break;
  }
  return retValue;
}



const NAUTF8Char* cmGetCoordSysName(CoordSysType coordSysType){
  const NAUTF8Char* retValue = "";
  switch(coordSysType){
  case COORD_SYS_HSL: retValue = cmTranslate(CMColorSpaceHSL); break;
  case COORD_SYS_HSL_CARTESIAN: retValue = cmTranslate(CMColorSpaceHSL); break;
  case COORD_SYS_HSV: retValue = cmTranslate(CMColorSpaceHSV); break;
  case COORD_SYS_HSV_CARTESIAN: retValue = cmTranslate(CMColorSpaceHSV); break;
  case COORD_SYS_Lab: retValue = cmTranslate(CMColorSpaceLab); break;
  case COORD_SYS_Lch_CARTESIAN: retValue = cmTranslate(CMColorSpaceLch); break;
  case COORD_SYS_Luv: retValue = cmTranslate(CMColorSpaceLuv); break;
  case COORD_SYS_RGB: retValue = cmTranslate(CMColorSpaceRGB); break;
  case COORD_SYS_UVW: retValue = cmTranslate(CMColorSpaceUVW); break;
  case COORD_SYS_XYZ: retValue = cmTranslate(CMColorSpaceXYZ); break;
  case COORD_SYS_Ycbcr: retValue = cmTranslate(CMColorSpaceYCbCr); break;
  case COORD_SYS_Ycd: retValue = cmTranslate(CMColorSpaceYcd); break;
  case COORD_SYS_Yupvp: retValue = cmTranslate(CMColorSpaceYupvp); break;
  case COORD_SYS_Yuv: retValue = cmTranslate(CMColorSpaceYuv); break;
  case COORD_SYS_Yxy: retValue = cmTranslate(CMColorSpaceYxy); break;
  default: break;
  }
  if(coordSysType == COORD_SYS_Lch_CARTESIAN || coordSysType == COORD_SYS_HSV_CARTESIAN || coordSysType == COORD_SYS_HSL_CARTESIAN){
    retValue = naAllocSprintf(NA_TRUE, cmTranslate(CMCartesian), retValue);
  }
  return retValue;
}



NABool cmSelectColorSpace(NAReaction reaction){
  CMCoordinateController* con = (CMCoordinateController*)reaction.controller;

  size_t index = naGetPopupButtonItemIndex(con->colorSpacePopupButton, reaction.uiElement);
  con->colorSpaceType = (ColorSpaceType)index;

  cmUpdateThreeDeeController(con->parentController);

  return TRUE;
}



NABool cmSelectCoordSys(NAReaction reaction){
  CMCoordinateController* con = (CMCoordinateController*)reaction.controller;

  size_t index = naGetPopupButtonItemIndex(con->coordSysPopupButton, reaction.uiElement);
  con->coordSysType = (CoordSysType)index;
  
  cmUpdateThreeDeeController(con->parentController);

  return TRUE;
}



NABool cmChangeCoordinateSlider(NAReaction reaction){
  CMCoordinateController* con = (CMCoordinateController*)reaction.controller;

  if(reaction.uiElement == con->stepsSlider){
    con->steps3D = (NAInt)naGetSliderValue(con->stepsSlider);
  }
  
  cmUpdateThreeDeeController(con->parentController);

  return TRUE;
}



CMCoordinateController* cmAllocCoordinateController(CMThreeDeeController* parentController){
  CMCoordinateController* con = naAlloc(CMCoordinateController);
  naZeron(con, sizeof(CMCoordinateController));

  con->parentController = parentController;

  con->space = naNewSpace(naMakeSize(1, 1));
  naSetSpaceAlternateBackground(con->space, NA_TRUE);

  con->colorSpaceLabel = naNewLabel(cmTranslate(CMColorSpace), threeDeeLabelWidth);
  con->colorSpacePopupButton = naNewPopupButton(threeDeeControlWidth);
  for(size_t i = 0; i < COLOR_SPACE_COUNT; ++i){
    ColorSpaceType colorSpaceType = (ColorSpaceType)i;
    NAMenuItem* item = naNewMenuItem(cmlGetColorTypeString(cmGetCMLColorTypeFromColorSpaceType(colorSpaceType)));
    naAddPopupButtonMenuItem(con->colorSpacePopupButton, item, NA_NULL);
    naAddUIReaction(item, NA_UI_COMMAND_PRESSED, cmSelectColorSpace, con);
  }

  con->coordSysLabel = naNewLabel(cmTranslate(CMCoordinates), threeDeeLabelWidth);
  con->coordSysPopupButton = naNewPopupButton(threeDeeControlWidth);
  for(size_t i = 0; i < COORD_SYS_COUNT; ++i){
    NAMenuItem* item = naNewMenuItem(cmGetCoordSysName((CoordSysType)i));
    naAddPopupButtonMenuItem(con->coordSysPopupButton, item, NA_NULL);
    naAddUIReaction(item, NA_UI_COMMAND_PRESSED, cmSelectCoordSys, con);
  }

  con->stepsLabel = naNewLabel(cmTranslate(CMSteps), threeDeeLabelWidth);
  con->stepsSlider = naNewSlider(threeDeeControlWidth);
  naSetSliderRange(con->stepsSlider, 2., 40., 0);
  naAddUIReaction(con->stepsSlider, NA_UI_COMMAND_EDITED, cmChangeCoordinateSlider, con);

  // layout

  cmBeginUILayout(con->space, threeDeeBezel);
  
  cmAddUIRow(con->colorSpaceLabel, uiElemHeight);
  cmAddUICol(con->colorSpacePopupButton, marginH);

  cmAddUIRow(con->coordSysLabel, uiElemHeight);
  cmAddUICol(con->coordSysPopupButton, marginH);

  cmAddUIRow(con->stepsLabel, uiElemHeight);
  cmAddUICol(con->stepsSlider, marginH);

  cmEndUILayout();

  // initial values

  con->colorSpaceType = COLOR_SPACE_RGB;
  con->coordSysType = COORD_SYS_Lab;
  con->steps3D = 25;

  return con;
}



void cmDeallocCoordinateController(CMCoordinateController* con){
  naFree(con);
}



NASpace* cmGetCoordinateUIElement(CMCoordinateController* con){
  return con->space;
}


CoordSysType cmGetCoordinateCoordSysType(CMCoordinateController* con){
  return con->coordSysType;
}
CMLColorType cmGetCoordinateColorSpaceType(CMCoordinateController* con){
  return cmGetCMLColorTypeFromColorSpaceType(con->colorSpaceType);
}
NAInt cmGetCoordinateSteps3D(CMCoordinateController* con){
  return con->steps3D;
}


void cmUpdateCoordinateController(CMCoordinateController* con){
  naSetPopupButtonIndexSelected(con->colorSpacePopupButton, con->colorSpaceType);
  naSetPopupButtonIndexSelected(con->coordSysPopupButton, con->coordSysType);
  naSetSliderValue(con->stepsSlider, con->steps3D);
}
