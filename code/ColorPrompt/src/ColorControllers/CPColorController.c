
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



void cmInitColorController(CPColorController* con, CMLColorType colorType){
  con->space = naNewSpace(naMakeSize(300, 100));
  naAddUIReaction(con->space, NA_UI_COMMAND_MOUSE_DOWN, CPColorControllerMouseDown, con);
  
  con->active = NA_FALSE;
  con->colorType = colorType;
}



void cmClearColorController(CPColorController* con){
}



void cmSetColorControllerColorType(CPColorController* con, CMLColorType colorType){
  con->colorType = colorType;
}



void cmSetColorControllerActive(CPColorController* con, NABool active){
  con->active = active;
}



CMLColorType cpGetColorControllerColorType(const CPColorController* con){
  return con->colorType;
}



const void* cpGetColorControllerColorData(const CPColorController* con){
  switch(con->colorType){
  case CML_COLOR_Gray: return cmGetGrayColorControllerColorData((const CPGrayColorController*)con); 
  case CML_COLOR_HSL: return cmGetHSVHSLColorControllerColorData((const CPHSVHSLColorController*)con); 
  case CML_COLOR_HSV: return cmGetHSVHSLColorControllerColorData((const CPHSVHSLColorController*)con);
  case CML_COLOR_Lab: return cmGetLabLchColorControllerColorData((const CPLabLchColorController*)con);
  case CML_COLOR_Lch: return cmGetLabLchColorControllerColorData((const CPLabLchColorController*)con);
  case CML_COLOR_Luv: return cmGetLuvUVWColorControllerColorData((const CPLuvUVWColorController*)con);
  case CML_COLOR_RGB: return cmGetRGBColorControllerColorData((const CPRGBColorController*)con);
  case CML_COLOR_SPECTRUM_ILLUMINATION: return cmGetSpectralColorControllerColorData((const CPSpectralColorController*)con);
  case CML_COLOR_UVW: return cmGetLuvUVWColorControllerColorData((const CPLuvUVWColorController*)con);
  case CML_COLOR_XYZ: return cmGetXYZColorControllerColorData((const CPXYZColorController*)con);
  case CML_COLOR_YCbCr: return cmGetYCbCrColorControllerColorData((const CPYCbCrColorController*)con);
  case CML_COLOR_Yupvp: return cmGetYuvColorControllerColorData((const CPYuvYupvpColorController*)con);
  case CML_COLOR_Yuv: return cmGetYuvColorControllerColorData((const CPYuvYupvpColorController*)con);
  case CML_COLOR_Yxy: return cmGetYxyColorControllerColorData((const CPYxyColorController*)con);
  default: return NA_NULL;
  }
}



void cmSetColorControllerColorData(CPColorController* con, const void* data){
  switch(con->colorType){
  case CML_COLOR_Gray: cmSetGrayColorControllerColorData((CPGrayColorController*)con, data); break; 
  case CML_COLOR_HSL: cmSetHSVHSLColorControllerColorData((CPHSVHSLColorController*)con, data); break; 
  case CML_COLOR_HSV: cmSetHSVHSLColorControllerColorData((CPHSVHSLColorController*)con, data); break;
  case CML_COLOR_Lab: cmSetLabLchColorControllerColorData((CPLabLchColorController*)con, data); break;
  case CML_COLOR_Lch: cmSetLabLchColorControllerColorData((CPLabLchColorController*)con, data); break;
  case CML_COLOR_Luv: cmSetLuvUVWColorControllerColorData((CPLuvUVWColorController*)con, data); break;
  case CML_COLOR_RGB: cmSetRGBColorControllerColorData((CPRGBColorController*)con, data); break;
  case CML_COLOR_SPECTRUM_ILLUMINATION: cmSetSpectralColorControllerColorData((CPSpectralColorController*)con, data); break;
  case CML_COLOR_UVW: cmSetLuvUVWColorControllerColorData((CPLuvUVWColorController*)con, data); break;
  case CML_COLOR_XYZ: cmSetXYZColorControllerColorData((CPXYZColorController*)con, data); break;
  case CML_COLOR_YCbCr: cmSetYCbCrColorControllerColorData((CPYCbCrColorController*)con, data); break;
  case CML_COLOR_Yupvp: cmSetYuvColorControllerColorData((CPYuvYupvpColorController*)con, data); break;
  case CML_COLOR_Yuv: cmSetYuvColorControllerColorData((CPYuvYupvpColorController*)con, data); break;
  case CML_COLOR_Yxy: cmSetYxyColorControllerColorData((CPYxyColorController*)con, data); break;
  default: break;
  }
}



NASpace* cmGetColorControllerUIElement(CPColorController* con){
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
