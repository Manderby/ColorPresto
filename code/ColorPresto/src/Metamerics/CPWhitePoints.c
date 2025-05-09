
#include "CPWhitePoints.h"

#include "CPColorConversionsYcdUVW.h"
#include "../CPColorPrestoApplication.h"
#include "../main.h"



void cp_FillChromaticAdaptationMatrix(CMLMat33 adaptationMatrix, const CMLVec3 whitePointYxy10)
{
  CMLColorMachine* sm = cpGetCurrentScreenMachine();

  // Note that the use of a chromatic adaptation is purely for displaying
  // reasons and is not in the ISO-standard at all. The differences between
  // the colors can be seen better when using the 10 deg observer. That's all.
  CMLVec3 screenWhitePoint;
  cmlCpy3(screenWhitePoint, cmlGetWhitePointYxy(sm));
  screenWhitePoint[0] = 1.f;
  cmlFillChromaticAdaptationMatrix(adaptationMatrix, CML_CHROMATIC_ADAPTATION_BRADFORD, screenWhitePoint, whitePointYxy10);
}



CPWhitePoints cpGetWhitePoints(const CMLFunction* spec, const float* wpYxy, CMLFunction** observerFuncs)
{
  CMLIntegration integration = cmlMakeDefaultIntegration();
  CPWhitePoints wp = {0};
  
  if(spec){
    cmlSet3(
      wp.XYZunnorm,
      cmlFilterFunction(spec, observerFuncs[0], &integration),
      cmlFilterFunction(spec, observerFuncs[1], &integration),
      cmlFilterFunction(spec, observerFuncs[2], &integration));
    cmlCpy3(wp.XYZ, wp.XYZunnorm);
    cmlDiv3(wp.XYZ, wp.XYZunnorm[1]);
    cmlConvertXYZToYxy(wp.Yxy, wp.XYZ, CML_NULL);
  }else if(wpYxy){
    cmlCpy3(wp.Yxy, wpYxy);
    wp.Yxy[0] = 1.f;
    cmlConvertYxyToXYZ(wp.XYZ, wp.Yxy, CML_NULL);
    cmlCpy3(wp.XYZunnorm, wp.XYZ);
  }else{
    #if NA_DEBUG
      cpError("Neither spectrum nor whitepoint given.");
    #endif
  }

  cmlConvertYxyToYupvp(wp.Yupvp, wp.Yxy, CML_NULL);
  cmlConvertYupvpToYuv(wp.Yuv, wp.Yupvp);
  cmlConvertYuvToYcd(wp.Ycd, wp.Yuv);
  cmlConvertYuvToUVW(wp.UVW, wp.Yuv, wp.Yuv);

  return wp;
}

