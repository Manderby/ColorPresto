
#include "NAUtility/NATranslator.h"



enum{
  CPAbout,
  CPDone,
  CPVersionBuild,
  CPOnlineHelp,
  CPApplicationHelpURL,

  // General things
  CPApplicationName,
  CPAverage,
  CPColorIndex1,
  CPColorIndex2,
  CPColorIndex3,
  CPColorIndex4,
  CPColorIndex5,
  CPColorIndex6,
  CPColorIndex7,
  CPColorIndex8,
  CPColorIndex9,
  CPColorIndex10,
  CPColorIndex11,
  CPColorIndex12,
  CPColorIndex13,
  CPColorIndex14,
  CPGradeA,
  CPGradeB,
  CPGradeC,
  CPGradeD,
  CPGradeE,

  // Channel Strings
  CPGrayColorChannelGr,
  CPHSLColorChannelH,
  CPHSLColorChannelS,
  CPHSLColorChannelL,
  CPHSVColorChannelH,
  CPHSVColorChannelS,
  CPHSVColorChannelV,
  CPLabColorChannelL,
  CPLabColorChannela,
  CPLabColorChannelb,
  CPLchColorChannelc,
  CPLchColorChannelh,
  CPLabColorChannelLStar,
  CPLabColorChannelaStar,
  CPLabColorChannelbStar,
  CPLuvColorChannelL,
  CPLuvColorChannelu,
  CPLuvColorChannelv,
  CPRGBColorChannelR,
  CPRGBColorChannelG,
  CPRGBColorChannelB,
  CPRGBColorChannelNum,
  CPUVWColorChannelU,
  CPUVWColorChannelV,
  CPUVWColorChannelW,
  CPXYZColorChannelX,
  CPXYZColorChannelY,
  CPXYZColorChannelZ,
  CPYCbCrColorChannelY,
  CPYCbCrColorChannelCb,
  CPYCbCrColorChannelCr,
  CPYcdColorChannelY,
  CPYcdColorChannelc,
  CPYcdColorChanneld,
  CPYuvColorChannelY,
  CPYuvColorChannelup,
  CPYuvColorChannelvp,
  CPYuvColorChannelu,
  CPYuvColorChannelv,
  CPYxyColorChannelY,
  CPYxyColorChannelx,
  CPYxyColorChannely,

  // Observer strings
  CPObserverTitle,
  CPObserverSteps,
  CPObserverNanoMeterSteps,
  CPObserverDegree2,
  CPObserverDegree10,

  // Illumination strings
  CPIlluminationTitle,
  CPIlluminationTemperature,
  CPIlluminationKelvin,
  CPIlluminationWhitePoint,

  // RGB colorspace
  CPRGBColorSpaceTitle,
  CPRGBColorSpaceRed,
  CPRGBColorSpaceGreen,
  CPRGBColorSpaceBlue,
  CPRGBColorResponse,
  CPRGBColorChannelRGB,
  CPRGBColorChannelLinear,
  CPRGBColorChannelSplit,
  CPRGBColorChannelGamma,
  CPRGBColorChannelOffset,

  // Lab Colorspace
  CPLabColorSpaceTitle,
  CPLabColorSpaceK,
  CPLabColorSpaceke,

  // Gray Colorspace
  CPGrayColorSpace,
  CPGrayDisplayColor,
  CPGrayDisplayGray,

  // Buttons
  CPThreeDeeButton,
  CPMetamericsButton,
  CPResetButton,
  CPAboutButton,
  CPPreferencesButton,
  CPSetButton,

  // Colorspaces
  CPColorSpaceHSL,
  CPColorSpaceHSV,
  CPColorSpaceLab,
  CPColorSpaceLch,
  CPColorSpaceLuv,
  CPColorSpaceRGB,
  CPColorSpaceUVW,
  CPColorSpaceXYZ,
  CPColorSpaceYCbCr,
  CPColorSpaceYcd,
  CPColorSpaceYupvp,
  CPColorSpaceYuv,
  CPColorSpaceYxy,

  // Strings for Whitepoint and Metamerics window
  CPWhitePointsAndMetamerics,
  CPCurrentIllumination,
  CPReferenceIllumination,
  CPChromaticityErrorTitle,
  CPColorRenderingIndex,
  CPVisMetamericIndex,
  CPUVMetamericIndex,
  CPTotalMetamericIndex,
  CPGrade,
  CPD50,
  CPD55,
  CPD65,
  CPD75,

  // Strings for 3D window
  CP3DView,
  CPColorSpace,
  CPCoordinates,
  CPSteps,
  CPRotation,
  CPStop,
  CPCartesian,
  CPPointsOpacity,
  CPGridOpacity,
  CPGridTint,
  CPBodyTint,
  CPSolid,
  
  CPAxis,
  CPSpectrum,
  CPBackground,
  CPFovy
};

const NAUTF8Char* cpTranslate(NAInt id);
void initTranslations(void);

