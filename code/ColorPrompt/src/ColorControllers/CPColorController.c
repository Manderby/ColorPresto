
#include "CPColorController.h"
#include "CPGrayColorController.h"
#include "CPHSVHSLColorController.h"
#include "CPLabLchColorController.h"
#include "CPLuvUVWColorController.h"
#include "CPRGBColorController.h"
#include "CPSpectralColorController.h"
#include "CPXYZColorController.h"
#include "CPYCbCrColorController.h"
#include "CPYuvYupvpColorController.h"
#include "CPYxyColorController.h"
#include "NAApp.h"



NABool CPColorControllerMouseDown(NAReaction reaction){
  CPColorController* con = reaction.controller;
  
  cpSetCurrentColorController(con);
  
  return NA_TRUE;
}



void cpInitColorController(CPColorController* con, CMLColorType colorType){
  con->space = naNewSpace(naMakeSize(300, 100));
  naAddUIReaction(con->space, NA_UI_COMMAND_MOUSE_DOWN, CPColorControllerMouseDown, con);
  
  con->active = NA_FALSE;
  con->colorType = colorType;
}



void cpClearColorController(CPColorController* con){
}



void cpSetColorControllerColorType(CPColorController* con, CMLColorType colorType){
  con->colorType = colorType;
}



void cpSetColorControllerActive(CPColorController* con, NABool active){
  con->active = active;
}



CMLColorType cpGetColorControllerColorType(const CPColorController* con){
  return con->colorType;
}



const void* cpGetColorControllerColorData(const CPColorController* con){
  switch(con->colorType){
  case CML_COLOR_Gray: return cpGetGrayColorControllerColorData((const CPGrayColorController*)con); 
  case CML_COLOR_HSL: return cpGetHSVHSLColorControllerColorData((const CPHSVHSLColorController*)con); 
  case CML_COLOR_HSV: return cpGetHSVHSLColorControllerColorData((const CPHSVHSLColorController*)con);
  case CML_COLOR_Lab: return cpGetLabLchColorControllerColorData((const CPLabLchColorController*)con);
  case CML_COLOR_Lch: return cpGetLabLchColorControllerColorData((const CPLabLchColorController*)con);
  case CML_COLOR_Luv: return cpGetLuvUVWColorControllerColorData((const CPLuvUVWColorController*)con);
  case CML_COLOR_RGB: return cpGetRGBColorControllerColorData((const CPRGBColorController*)con);
  case CML_COLOR_SPECTRUM_ILLUMINATION: return cpGetSpectralColorControllerColorData((const CPSpectralColorController*)con);
  case CML_COLOR_UVW: return cpGetLuvUVWColorControllerColorData((const CPLuvUVWColorController*)con);
  case CML_COLOR_XYZ: return cpGetXYZColorControllerColorData((const CPXYZColorController*)con);
  case CML_COLOR_YCbCr: return cpGetYCbCrColorControllerColorData((const CPYCbCrColorController*)con);
  case CML_COLOR_Yupvp: return cpGetYuvColorControllerColorData((const CPYuvYupvpColorController*)con);
  case CML_COLOR_Yuv: return cpGetYuvColorControllerColorData((const CPYuvYupvpColorController*)con);
  case CML_COLOR_Yxy: return cpGetYxyColorControllerColorData((const CPYxyColorController*)con);
  default: return NA_NULL;
  }
}



void cpSetColorControllerColorData(CPColorController* con, const void* data){
  switch(con->colorType){
  case CML_COLOR_Gray: cpSetGrayColorControllerColorData((CPGrayColorController*)con, data); break; 
  case CML_COLOR_HSL: cpSetHSVHSLColorControllerColorData((CPHSVHSLColorController*)con, data); break; 
  case CML_COLOR_HSV: cpSetHSVHSLColorControllerColorData((CPHSVHSLColorController*)con, data); break;
  case CML_COLOR_Lab: cpSetLabLchColorControllerColorData((CPLabLchColorController*)con, data); break;
  case CML_COLOR_Lch: cpSetLabLchColorControllerColorData((CPLabLchColorController*)con, data); break;
  case CML_COLOR_Luv: cpSetLuvUVWColorControllerColorData((CPLuvUVWColorController*)con, data); break;
  case CML_COLOR_RGB: cpSetRGBColorControllerColorData((CPRGBColorController*)con, data); break;
  case CML_COLOR_SPECTRUM_ILLUMINATION: cpSetSpectralColorControllerColorData((CPSpectralColorController*)con, data); break;
  case CML_COLOR_UVW: cpSetLuvUVWColorControllerColorData((CPLuvUVWColorController*)con, data); break;
  case CML_COLOR_XYZ: cpSetXYZColorControllerColorData((CPXYZColorController*)con, data); break;
  case CML_COLOR_YCbCr: cpSetYCbCrColorControllerColorData((CPYCbCrColorController*)con, data); break;
  case CML_COLOR_Yupvp: cpSetYuvColorControllerColorData((CPYuvYupvpColorController*)con, data); break;
  case CML_COLOR_Yuv: cpSetYuvColorControllerColorData((CPYuvYupvpColorController*)con, data); break;
  case CML_COLOR_Yxy: cpSetYxyColorControllerColorData((CPYxyColorController*)con, data); break;
  default: break;
  }
}



NASpace* cpGetColorControllerUIElement(CPColorController* con){
  return con->space;
}



void cpUpdateColorController(CPColorController* con){
  if(con->active){
    NABabyColor highlightColor;
    naFillDefaultTextColorWithSkin(highlightColor, naGetSkinForCurrentAppearance());
    highlightColor[3] = .2;
    naSetSpaceBackgroundColor(con->space, highlightColor);
  }else{
    naSetSpaceBackgroundColor(con->space, NA_NULL);
  }
}
