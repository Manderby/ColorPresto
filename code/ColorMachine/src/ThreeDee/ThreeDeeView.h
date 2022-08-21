
#ifdef __cplusplus
  extern "C"{
#endif

#include "mainC.h"
#include "CML.h"

CM_PROTOTYPE(NAOpenGLSpace);



void cmBeginThreeDeeDrawing(const CMLVec3 axisRGB);
void cmEndThreeDeeDrawing(NAOpenGLSpace* openGlSpace);

void cmSetupThreeDeeProjection(
  NASize viewSize,
  double fovy,
  double zoom);

void cmSetupThreeDeeModelView(
  int primeAxis,
  const double* scale,
  double curZoom,
  double viewPol,
  double viewEqu);

void cmDrawThreeDeePointCloud(
  const CMLColorMachine* cm,
  const CMLColorMachine* sm,
  double pointsAlpha,
  CMLColorType space3D,
  NAInt steps3D,
  CMLNormedConverter normedInputConverter,
  CMLColorConverter coordConverter,
  CMLNormedConverter normedCoordConverter,
  double zoom);

void cmDrawThreeDeeSpectrum(
  const CMLColorMachine* cm, 
  CMLNormedConverter normedCoordConverter,
  CMLColorType coordSpace,
  NAInt hueIndex);

void cmDrawThreeDeeAxis(
  CMLNormedConverter normedCoordConverter,
  const float* min,
  const float* max,
  const char** labels,
  const CMLVec3 axisRGB,
  NAInt fontId);



#ifdef __cplusplus
  }
#endif
