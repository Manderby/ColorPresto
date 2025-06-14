
#include "../main.h"
#include "CML.h"

CP_PROTOTYPE(NAOpenGLSpace);


typedef struct CPThreeDeeView CPThreeDeeView;



void cpInitThreeDeeDisplay(NAOpenGLSpace* openGLSpace);

void cpBeginThreeDeeDrawing(const CMLVec3 axisRGB);
void cpEndThreeDeeDrawing(NAOpenGLSpace* openGLSpace);

void cpSetupThreeDeeProjection(
  NAOpenGLSpace* openGLSpace,
  NASize viewSize,
  double fovy,
  double zoom);

void cpSetupThreeDeeModelView(
  int primeAxis,
  const double* scale,
  double curZoom,
  double viewPol,
  double viewEqu);

void cpDrawThreeDeePointCloud(
  const CMLColorMachine* cm,
  const CMLColorMachine* sm,
  double pointsAlpha,
  CMLColorType space3D,
  int64 steps3D,
  CMLNormedConverter normedInputConverter,
  CMLColorConverter coordConverter,
  CMLNormedConverter normedCoordConverter,
  double zoom,
  double uiScale);

void cpDrawThreeDeeSurfaces(
  const CMLColorMachine* cm,
  const CMLColorMachine* sm,
  const CMLVec3 backgroundRGB,
  const CMLVec3 axisRGB,
  NABool bodySolid,
  double bodyAlpha,
  double gridAlpha,
  double gridTint,
  CMLColorType space3D,
  int64 steps3D,
  CMLNormedConverter normedInputConverter,
  CMLColorConverter coordConverter,
  CMLNormedConverter normedCoordConverter,
  int64 hueIndex);

void cpDrawThreeDeeSpectrum(
  const CMLColorMachine* cm, 
  CMLNormedConverter normedCoordConverter,
  CMLColorType coordSpace,
  int64 hueIndex,
  double uiScale);

void cpDrawThreeDeeAxis(
  CMLNormedConverter normedCoordConverter,
  const float* min,
  const float* max,
  const char** labels,
  const CMLVec3 axisRGB,
  int64 fontId,
  double uiScale);

