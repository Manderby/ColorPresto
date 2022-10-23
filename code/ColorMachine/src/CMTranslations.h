
#include "NATranslator.h"

#ifdef __cplusplus
  extern "C"{
#endif



enum{
  CMApplicationDescription,
  CMApplicationHelpURL,

  // Strings for Whitepoint and Metamerics window
  CMWhitepointsAndMetamerics,
  CMChromaticityErrorTitle,

  // Strings for 3D window
  CM3DView,
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
