
#include "../mainC.h"
#include "CML.h"

CP_PROTOTYPE(NAOpenGLSpace);


typedef struct CPThreeDeeView CPThreeDeeView;



void cmInitThreeDeeDisplay(NAOpenGLSpace* openGLSpace);

void cmBeginThreeDeeDrawing(const CMLVec3 axisRGB);
void cmEndThreeDeeDrawing(NAOpenGLSpace* openGLSpace);

void cmSetupThreeDeeProjection(
  NAOpenGLSpace* openGLSpace,
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

void cmDrawThreeDeeSurfaces(
  const CMLColorMachine* cm,
  const CMLColorMachine* sm,
  const CMLVec3 backgroundRGB,
  const CMLVec3 axisRGB,
  NABool bodySolid,
  double bodyAlpha,
  double gridAlpha,
  double gridTint,
  CMLColorType space3D,
  NAInt steps3D,
  CMLNormedConverter normedInputConverter,
  CMLColorConverter coordConverter,
  CMLNormedConverter normedCoordConverter,
  NAInt hueIndex);

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

