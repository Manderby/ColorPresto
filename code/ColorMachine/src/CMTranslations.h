
#include "NATranslator.h"

#ifdef __cplusplus
  extern "C"{
#endif



enum{
  CMApplicationDescription,
  CMApplicationHelpURL,

  // General things
  CMAverage,

  // Observer strings
  CMObserverDegree2,
  CMObserverDegree10,

  // Colorspaces
  CMColorSpaceXYZ,
  CMColorSpaceYxy,
  CMColorSpaceYupvp,
  CMColorSpaceYuv,
  CMColorSpaceLab,
  CMColorSpaceLch,
  CMColorSpaceLuv,
  CMColorSpaceRGB,
  CMColorSpaceYCbCr,
  CMColorSpaceHSV,
  CMColorSpaceHSL,

  // Strings for Whitepoint and Metamerics window
  CMWhitepointsAndMetamerics,
  CMCurrentIllumination,
  CMReferenceIllumination,
  CMChromaticityErrorTitle,
  CMColorRenderingIndex,
  CMVisMetamericIndex,
  CMUVMetamericIndex,
  CMTotalMetamericIndex,
  CMGrade,

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

#ifdef __cplusplus
  }
#endif
