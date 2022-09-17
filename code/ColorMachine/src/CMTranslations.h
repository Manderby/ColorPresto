
#include "NATranslator.h"

#ifdef __cplusplus
  extern "C"{
#endif



enum{
  CMApplicationDescription,
  CMApplicationHelpURL,

  // Strings for 3D view
  CM3DView,

  CMColorSpace,
  CMCoordinates,
  CMSteps,
  CMRotation,
  CMStop,
  
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
