
#include "CPThreeDeeCoordinateController.h"

#include "../CPDesign.h"
#include "../CPTranslations.h"

#include "CML.h"

#include "NAApp/NAApp.h"
#include "NAUtility/NABinaryData.h"
#include "NAUtility/NAMemory.h"
#include "NAUtility/NAString.h"

struct CPThreeDeeCoordinateController{
  NASpace* space;
  CPThreeDeeController* threeDeeController;

  NALabel* colorSpaceLabel;
  NASelect* colorSpaceSelect;
  NALabel* coordSysLabel;
  NASelect* coordSysSelect;

  NALabel* stepsLabel;
  NASlider* stepsSlider;

  ColorSpaceType colorSpaceType;
  CoordSysType coordSysType;
  NAInt steps3D;
};



CMLColorType cpGetCMLColorTypeFromColorSpaceType(ColorSpaceType colorSpaceType){
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
      cpError("Unknown colorspace.");
    #endif
    break;
  }
  return retValue;
}



const NAUTF8Char* cpGetCoordSysName(CoordSysType coordSysType){
  const NAUTF8Char* retValue = "";
  switch(coordSysType){
  case COORD_SYS_HSL: retValue = cpTranslate(CPColorSpaceHSL); break;
  case COORD_SYS_HSL_CARTESIAN: retValue = cpTranslate(CPColorSpaceHSL); break;
  case COORD_SYS_HSV: retValue = cpTranslate(CPColorSpaceHSV); break;
  case COORD_SYS_HSV_CARTESIAN: retValue = cpTranslate(CPColorSpaceHSV); break;
  case COORD_SYS_Lab: retValue = cpTranslate(CPColorSpaceLab); break;
  case COORD_SYS_Lch_CARTESIAN: retValue = cpTranslate(CPColorSpaceLch); break;
  case COORD_SYS_Luv: retValue = cpTranslate(CPColorSpaceLuv); break;
  case COORD_SYS_RGB: retValue = cpTranslate(CPColorSpaceRGB); break;
  case COORD_SYS_UVW: retValue = cpTranslate(CPColorSpaceUVW); break;
  case COORD_SYS_XYZ: retValue = cpTranslate(CPColorSpaceXYZ); break;
  case COORD_SYS_Ycbcr: retValue = cpTranslate(CPColorSpaceYCbCr); break;
  case COORD_SYS_Ycd: retValue = cpTranslate(CPColorSpaceYcd); break;
  case COORD_SYS_Yupvp: retValue = cpTranslate(CPColorSpaceYupvp); break;
  case COORD_SYS_Yuv: retValue = cpTranslate(CPColorSpaceYuv); break;
  case COORD_SYS_Yxy: retValue = cpTranslate(CPColorSpaceYxy); break;
  default: break;
  }
  if(coordSysType == COORD_SYS_Lch_CARTESIAN
  || coordSysType == COORD_SYS_HSV_CARTESIAN
  || coordSysType == COORD_SYS_HSL_CARTESIAN)
  {
    retValue = naAllocSprintf(NA_TRUE, cpTranslate(CPCartesian), retValue);
  }
  return retValue;
}



void cp_SelectColorSpace(NAReaction reaction){
  CPThreeDeeCoordinateController* con = (CPThreeDeeCoordinateController*)reaction.controller;

  size_t index = naGetSelectItemIndex(con->colorSpaceSelect, reaction.uiElement);
  con->colorSpaceType = (ColorSpaceType)index;

  cpUpdateThreeDeeController(con->threeDeeController);
}



void cp_SelectCoordSys(NAReaction reaction){
  CPThreeDeeCoordinateController* con = (CPThreeDeeCoordinateController*)reaction.controller;

  size_t index = naGetSelectItemIndex(con->coordSysSelect, reaction.uiElement);
  con->coordSysType = (CoordSysType)index;
  
  cpUpdateThreeDeeController(con->threeDeeController);
}



void cp_ChangeCoordinateSlider(NAReaction reaction){
  CPThreeDeeCoordinateController* con = (CPThreeDeeCoordinateController*)reaction.controller;

  if(reaction.uiElement == con->stepsSlider){
    con->steps3D = (NAInt)naGetSliderValue(con->stepsSlider);
  }
  
  cpUpdateThreeDeeController(con->threeDeeController);
}



CPThreeDeeCoordinateController* cpAllocThreeDeeCoordinateController(CPThreeDeeController* threeDeeController){
  CPThreeDeeCoordinateController* con = naAlloc(CPThreeDeeCoordinateController);

  con->threeDeeController = threeDeeController;

  con->space = naNewSpace(naMakeSize(1, 1));
  naSetSpaceAlternateBackground(con->space, NA_TRUE);

  con->colorSpaceLabel = naNewLabel(cpTranslate(CPColorSpace), threeDeeLabelWidth);
  con->colorSpaceSelect = naNewSelect(threeDeeControlWidth);
  for(size_t i = 0; i < COLOR_SPACE_COUNT; ++i){
    ColorSpaceType colorSpaceType = (ColorSpaceType)i;
    NAMenuItem* item = naNewMenuItem(cmlGetColorTypeString(cpGetCMLColorTypeFromColorSpaceType(colorSpaceType)));
    naAddSelectMenuItem(con->colorSpaceSelect, item, NA_NULL);
    naAddUIReaction(item, NA_UI_COMMAND_PRESSED, cp_SelectColorSpace, con);
  }

  con->coordSysLabel = naNewLabel(cpTranslate(CPCoordinates), threeDeeLabelWidth);
  con->coordSysSelect = naNewSelect(threeDeeControlWidth);
  for(size_t i = 0; i < COORD_SYS_COUNT; ++i){
    NAMenuItem* item = naNewMenuItem(cpGetCoordSysName((CoordSysType)i));
    naAddSelectMenuItem(con->coordSysSelect, item, NA_NULL);
    naAddUIReaction(item, NA_UI_COMMAND_PRESSED, cp_SelectCoordSys, con);
  }

  con->stepsLabel = naNewLabel(cpTranslate(CPSteps), threeDeeLabelWidth);
  con->stepsSlider = naNewSlider(threeDeeControlWidth);
  naSetSliderRange(con->stepsSlider, 2., 40., 0);
  naAddUIReaction(con->stepsSlider, NA_UI_COMMAND_EDITED, cp_ChangeCoordinateSlider, con);

  // layout
  cpBeginUILayout(con->space, threeDeeBorder);
  
  cpAddUIRow(con->colorSpaceLabel, uiElemHeight);
  cpAddUICol(con->colorSpaceSelect, marginH);

  cpAddUIRow(con->coordSysLabel, uiElemHeight);
  cpAddUICol(con->coordSysSelect, marginH);

  cpAddUIRow(con->stepsLabel, uiElemHeight);
  cpAddUICol(con->stepsSlider, marginH);

  cpEndUILayout();

  // initial values
  con->colorSpaceType = COLOR_SPACE_RGB;
  con->coordSysType = COORD_SYS_Lab;
  con->steps3D = 25;

  return con;
}



void cpDeallocThreeDeeCoordinateController(CPThreeDeeCoordinateController* con){
  naFree(con);
}



NASpace* cpGetThreeDeeCoordinateControllerUIElement(CPThreeDeeCoordinateController* con){
  return con->space;
}


CoordSysType cpGetThreeDeeCoordinateControllerCoordSysType(CPThreeDeeCoordinateController* con){
  return con->coordSysType;
}
CMLColorType cpGetThreeDeeCoordinateControllerColorSpaceType(CPThreeDeeCoordinateController* con){
  return cpGetCMLColorTypeFromColorSpaceType(con->colorSpaceType);
}
NAInt cpGetThreeDeeCoordinateControllerSteps3D(CPThreeDeeCoordinateController* con){
  return con->steps3D;
}


void cpUpdateThreeDeeCoordinateController(CPThreeDeeCoordinateController* con){
  naSetSelectIndexSelected(con->colorSpaceSelect, con->colorSpaceType);
  naSetSelectIndexSelected(con->coordSysSelect, con->coordSysType);
  naSetSliderValue(con->stepsSlider, (double)con->steps3D);
}
