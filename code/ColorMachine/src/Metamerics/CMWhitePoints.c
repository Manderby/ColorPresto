
#include "CMWhitePoints.h"
#include "mainC.h"



void CMFillChromaticAdaptationMatrix(CMLMat33 adaptationMatrix, const CMLVec3 whitePointYxy10)
{
  CMLColorMachine* sm = cmGetCurrentScreenMachine();

  // Note that the use of a chromatic adaptation is purely for displaying
  // reasons and is not in the ISO-standard at all. The differences between
  // the colors can be seen better when using the 10 deg observer. That's all.
  CMLVec3 screenWhitePoint;
  cmlCpy3(screenWhitePoint, cmlGetReferenceWhitePointYxy(sm));
  screenWhitePoint[0] = 1.f;
  cmlFillChromaticAdaptationMatrix(adaptationMatrix, CML_CHROMATIC_ADAPTATION_BRADFORD, screenWhitePoint, whitePointYxy10);
}



CMWhitePoints CMGetWhitePoints()
{
  CMLColorMachine* cm = cmGetCurrentColorMachine();
  CMLIntegration integration = cmlMakeDefaultIntegration();
  const CMLFunction* illuminationSpec = cmlGetReferenceIlluminationSpectrum(cm);
  NABool ill2available = NA_TRUE;
  NABool ill10available = NA_TRUE;
  CMLFunction* observer10Funcs[3];
  cmlCreateSpecDistFunctions(observer10Funcs, CML_DEFAULT_10DEG_OBSERVER);
  CMLFunction* observer2Funcs[3];
  cmlCreateSpecDistFunctions(observer2Funcs, CML_DEFAULT_2DEG_OBSERVER);
  
  CMWhitePoints wp;
  
  if(illuminationSpec){
    cmlSet3(
      wp.illXYZunnorm10,
      cmlFilterFunction(illuminationSpec, observer10Funcs[0], &integration),
      cmlFilterFunction(illuminationSpec, observer10Funcs[1], &integration),
      cmlFilterFunction(illuminationSpec, observer10Funcs[2], &integration));
    cmlCpy3(wp.illXYZ10, wp.illXYZunnorm10);
    cmlDiv3(wp.illXYZ10, wp.illXYZunnorm10[1]);

    cmlSet3(
      wp.illXYZunnorm2,
      cmlFilterFunction(illuminationSpec, observer2Funcs[0], &integration),
      cmlFilterFunction(illuminationSpec, observer2Funcs[1], &integration),
      cmlFilterFunction(illuminationSpec, observer2Funcs[2], &integration));
    cmlCpy3(wp.illXYZ2, wp.illXYZunnorm2);
    cmlDiv3(wp.illXYZ2, wp.illXYZunnorm2[1]);
  }else{
    CMLObserverType illObserverType = cmlGetObserverType(cm);
    if(illObserverType == CML_OBSERVER_10DEG_CIE_1964){
      cmlCpy3(wp.illYxy10, cmlGetReferenceWhitePointYxy(cm));
      wp.illYxy10[0] = 1.f;
      cmlConvertYxyToXYZ(wp.illXYZ10, wp.illYxy10, CML_NULL);
      cmlSet3(wp.illXYZ2, 0.f, 1.f, 0.f);
      ill2available = NA_FALSE;
    }else{
      cmlCpy3(wp.illYxy2, cmlGetReferenceWhitePointYxy(cm));
      wp.illYxy2[0] = 1.f;
      cmlConvertYxyToXYZ(wp.illXYZ2, wp.illYxy2, CML_NULL);
      cmlSet3(wp.illXYZ10, 0.f, 1.f, 0.f);
      ill10available = NA_FALSE;
    }
  }

  cmlConvertXYZToYxy(wp.illYxy10, wp.illXYZ10, CML_NULL);
//  cmlConvertYxyToYupvp(wp.illYupvp10, wp.illYxy10, CML_NULL);
//  cmlConvertYupvpToYuv(wp.illYuv10, wp.illYupvp10);
  
//  cmlConvertXYZToYxy(wp.refYxy10, wp.refXYZ10, CML_NULL);
//  cmlConvertYxyToYupvp(wp.refYupvp10, wp.refYxy10, CML_NULL);
//  cmlConvertYupvpToYuv(wp.refYuv10, wp.refYupvp10);
  
  cmlConvertXYZToYxy(wp.illYxy2, wp.illXYZ2, CML_NULL);
//  cmlConvertYxyToYupvp(wp.illYupvp2, wp.illYxy2, CML_NULL);
//  cmlConvertYupvpToYuv(wp.illYuv2, wp.illYupvp2);
//  convertYuvtoYcd(wp.illYcd2, wp.illYuv2);
  
//  cmlConvertXYZToYxy(wp.refYxy2, wp.refXYZ2, CML_NULL);
//  cmlConvertYxyToYupvp(wp.refYupvp2, wp.refYxy2, CML_NULL);
//  cmlConvertYupvpToYuv(wp.refYuv2, wp.refYupvp2);
//  convertYuvtoYcd(wp.refYcd2, wp.refYuv2);

  cmlReleaseFunction(observer10Funcs[0]);
  cmlReleaseFunction(observer10Funcs[1]);
  cmlReleaseFunction(observer10Funcs[2]);
  cmlReleaseFunction(observer2Funcs[0]);
  cmlReleaseFunction(observer2Funcs[1]);
  cmlReleaseFunction(observer2Funcs[2]);

  return wp;
}

