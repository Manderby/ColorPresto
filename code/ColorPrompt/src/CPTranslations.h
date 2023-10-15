
#include "NAUtility/NATranslator.h"



enum{
  CMApplicationDescription,
  CMApplicationHelpURL,

  // General things
  CMApplicationName,
  CMAverage,
  CMColorIndex1,
  CMColorIndex2,
  CMColorIndex3,
  CMColorIndex4,
  CMColorIndex5,
  CMColorIndex6,
  CMColorIndex7,
  CMColorIndex8,
  CMColorIndex9,
  CMColorIndex10,
  CMColorIndex11,
  CMColorIndex12,
  CMColorIndex13,
  CMColorIndex14,
  CMGradeA,
  CMGradeB,
  CMGradeC,
  CMGradeD,
  CMGradeE,

  // Channel Strings
  CMGrayColorChannelGr,
  CMHSLColorChannelH,
  CMHSLColorChannelS,
  CMHSLColorChannelL,
  CMHSVColorChannelH,
  CMHSVColorChannelS,
  CMHSVColorChannelV,
  CMLabColorChannelL,
  CMLabColorChannela,
  CMLabColorChannelb,
  CMLchColorChannelc,
  CMLchColorChannelh,
  CMLabColorChannelLStar,
  CMLabColorChannelaStar,
  CMLabColorChannelbStar,
  CMLuvColorChannelL,
  CMLuvColorChannelu,
  CMLuvColorChannelv,
  CMRGBColorChannelR,
  CMRGBColorChannelG,
  CMRGBColorChannelB,
  CMRGBColorChannelNum,
  CMUVWColorChannelU,
  CMUVWColorChannelV,
  CMUVWColorChannelW,
  CMXYZColorChannelX,
  CMXYZColorChannelY,
  CMXYZColorChannelZ,
  CMYCbCrColorChannelY,
  CMYCbCrColorChannelCb,
  CMYCbCrColorChannelCr,
  CMYcdColorChannelY,
  CMYcdColorChannelc,
  CMYcdColorChanneld,
  CMYuvColorChannelY,
  CMYuvColorChannelup,
  CMYuvColorChannelvp,
  CMYuvColorChannelu,
  CMYuvColorChannelv,
  CMYxyColorChannelY,
  CMYxyColorChannelx,
  CMYxyColorChannely,

  // Observer strings
  CMObserverTitle,
  CMObserverSteps,
  CMObserverNanoMeterSteps,
  CMObserverDegree2,
  CMObserverDegree10,

  // Illumination strings
  CMIlluminationTitle,
  CMIlluminationTemperature,
  CMIlluminationKelvin,
  CMIlluminationWhitePoint,

  // RGB colorspace
  CMRGBColorSpaceTitle,
  CMRGBColorSpaceRed,
  CMRGBColorSpaceGreen,
  CMRGBColorSpaceBlue,
  CMRGBColorResponse,
  CMRGBColorChannelRGB,
  CMRGBColorChannelLinear,
  CMRGBColorChannelSplit,
  CMRGBColorChannelGamma,
  CMRGBColorChannelOffset,

  // Lab Colorspace
  CMLabColorSpaceTitle,
  CMLabColorSpaceK,
  CMLabColorSpaceke,

  // Gray Colorspace
  CMGrayColorSpace,
  CMGrayDisplayColor,
  CMGrayDisplayGray,

  // Buttons
  CMThreeDeeButton,
  CMMetamericsButton,
  CMResetButton,
  CMSetButton,

  // Colorspaces
  CMColorSpaceHSL,
  CMColorSpaceHSV,
  CMColorSpaceLab,
  CMColorSpaceLch,
  CMColorSpaceLuv,
  CMColorSpaceRGB,
  CMColorSpaceUVW,
  CMColorSpaceXYZ,
  CMColorSpaceYCbCr,
  CMColorSpaceYcd,
  CMColorSpaceYupvp,
  CMColorSpaceYuv,
  CMColorSpaceYxy,

  // Strings for Whitepoint and Metamerics window
  CPWhitePointsAndMetamerics,
  CMCurrentIllumination,
  CMReferenceIllumination,
  CMChromaticityErrorTitle,
  CMColorRenderingIndex,
  CMVisMetamericIndex,
  CMUVMetamericIndex,
  CMTotalMetamericIndex,
  CMGrade,
  CMD50,
  CMD55,
  CMD65,
  CMD75,

  // Strings for 3D window
  CM3DView,
  CMColorSpace,
  CMCoordinates,
  CMSteps,
  CMRotation,
  CMStop,
  CMCartesian,
  CMPointsOpacity,
  CMGridOpacity,
  CMGridTint,
  CMBodyTint,
  CMSolid,
  
  CMAxis,
  CMSpectrum,
  CMBackground,
  CMFovy
};

const NAUTF8Char* cmTranslate(NAInt id);
void initTranslations(void);

