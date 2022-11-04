
#include "CML.h"
#include "NAApp.h"
#include "NAMath.h"
#include "NAVisual.h"
#include "CMThreeDeeView.h"
#include "CMDesign.h"



typedef size_t CMLVec4UInt[CML_MAX_NUMBER_OF_CHANNELS];

inline static void cmlSet4UInt(CMLVec4UInt d, size_t a0, size_t a1, size_t a2, size_t a3){
  d[0] = a0;
  d[1] = a1;
  d[2] = a2;
  d[3] = a3;
}



void cmInitThreeDeeDisplay(NAOpenGLSpace* openGLSpace){
  NA_UNUSED(openGLSpace);
  glEnable(GL_POINT_SMOOTH);
  glEnable(GL_LINE_SMOOTH);
  glEnable(GL_BLEND);
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}



void cmBeginThreeDeeDrawing(const CMLVec3 backgroundRGB){
  glClearColor(backgroundRGB[0], backgroundRGB[1], backgroundRGB[2], 1.);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}



void cmEndThreeDeeDrawing(NAOpenGLSpace* openGLSpace){
  naSwapOpenGLSpaceBuffer(openGLSpace);
}



void cmSetupThreeDeeProjection(NASize viewSize, double fovy, double zoom){
  glViewport(0, 0, (GLsizei)viewSize.width, (GLsizei)viewSize.height);
  
//  float curZoom;

  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();

  NAMat44d projectionMatrix;
  if(fovy == 0){
    naFillMatrixOrtho(
      projectionMatrix,
      -zoom * 3. * .5,
      zoom * 3. * .5,
      -zoom * 3. * .5,
      zoom * 3. * .5,
      .1,
      50);
  }else{
    naFillMatrixPerspective(
      projectionMatrix,
      fovy,
      viewSize.width / viewSize.height,
      .1,
      50.);
  }
  glLoadMatrixd(projectionMatrix);
}



void cmSetupThreeDeeModelView(int primeAxis, const double* scale, double curZoom, double viewPol, double viewEqu){
  float vShift = .2f;
  NAMat44d matrix;

  glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

  switch(primeAxis){
  case 0:
    naFillMatrixLookAt(matrix,
      vShift * scale[0] + curZoom * 3 * naCosf(viewPol),
      .5f * scale[1] + curZoom * 3 * naCosf(viewEqu) * naSinf(viewPol),
      .5f * scale[2] + curZoom * 3 * naSinf(viewEqu) * naSinf(viewPol),
      vShift * scale[0], .5f * scale[1], .5f * scale[2],
      1, 0, 0);
    break;
  case 1:
    naFillMatrixLookAt(matrix,
      .5f * scale[0] + curZoom * 3 * naSinf(viewEqu) * naSinf(viewPol),
      vShift * scale[1] + curZoom * 3 * naCosf(viewPol),
      .5f * scale[2] + curZoom * 3 * naCosf(viewEqu) * naSinf(viewPol),
      .5f * scale[0], vShift * scale[1], .5f * scale[2],
      0, 1, 0);
    break;
  case 2:
    naFillMatrixLookAt(matrix,
      .5f * scale[0] + curZoom * 3 * naCosf(viewEqu) * naSinf(viewPol),
      .5f * scale[1] + curZoom * 3 * naSinf(viewEqu) * naSinf(viewPol),
      vShift * scale[2] + curZoom * 3 * naCosf(viewPol),
      .5f * scale[0], .5f * scale[1], vShift * scale[2],
      0, 0, 1);
    break;
  }
  
  glLoadMatrixd(matrix);
  glScaled(scale[0], scale[1], scale[2]);
}



void cmDrawThreeDeePointCloud(const CMLColorMachine* cm, const CMLColorMachine* sm, double pointsAlpha, CMLColorType space3D, NAInt steps3D, CMLNormedConverter normedInputConverter, CMLColorConverter coordConverter, CMLNormedConverter normedCoordConverter, double zoom){
  size_t numChannels = cmlGetNumChannels(space3D);

  CMLVec4UInt steps;
  switch(space3D){
  case CML_COLOR_GRAY:  cmlSet4UInt(steps, 2 * steps3D, 1, 1, 1); break;
  case CML_COLOR_XYZ:   cmlSet4UInt(steps, steps3D, steps3D, steps3D, 1); break;
  case CML_COLOR_Yxy:   cmlSet4UInt(steps, steps3D, steps3D, steps3D, 1); break;
  case CML_COLOR_Yuv:   cmlSet4UInt(steps, steps3D, steps3D, steps3D, 1); break;
  case CML_COLOR_Yupvp: cmlSet4UInt(steps, steps3D, steps3D, steps3D, 1); break;
  case CML_COLOR_YCbCr: cmlSet4UInt(steps, steps3D, steps3D, steps3D, 1); break;
  case CML_COLOR_Lab:   cmlSet4UInt(steps, steps3D, steps3D, steps3D, 1); break;
  case CML_COLOR_Lch:   cmlSet4UInt(steps, steps3D, steps3D, 3 * steps3D + 1, 1); break;
  case CML_COLOR_Luv:   cmlSet4UInt(steps, steps3D, steps3D, steps3D, 1); break;
  case CML_COLOR_RGB:   cmlSet4UInt(steps, steps3D, steps3D, steps3D, 1); break;
  case CML_COLOR_HSV:   cmlSet4UInt(steps, 3 * steps3D + 1, steps3D, steps3D, 1); break;
  case CML_COLOR_HSL:   cmlSet4UInt(steps, 3 * steps3D + 1, steps3D, steps3D, 1); break;
  default: cmlSet4UInt(steps, 1, 1, 1, 1); break;
  }
  
  size_t totalCloudCount = steps[0] * steps[1] * steps[2] * steps[3];
  float* cloudNormedColorCoords = (float*)cmlCreateNormedGamutSlice(space3D, steps, NA_NULL, NA_NULL, NA_NULL, NA_NULL, NA_NULL);
  float* cloudRGBFloatValues      = naMalloc(totalCloudCount * 3 * sizeof(float));
  float* cloudColorCoords         = naMalloc(totalCloudCount * numChannels * sizeof(float));
  float* cloudSystemCoords        = naMalloc(totalCloudCount * 3 * sizeof(float));
  float* cloudNormedSystemCoords  = naMalloc(totalCloudCount * 3 * sizeof(float));

  normedInputConverter(cloudColorCoords, cloudNormedColorCoords, totalCloudCount);
  coordConverter(cm, cloudSystemCoords, cloudColorCoords, totalCloudCount);
  normedCoordConverter(cloudNormedSystemCoords, cloudSystemCoords, totalCloudCount);
  
  // Convert the given values to screen RGBs.
  fillRGBFloatArrayWithArray(
    cm,
    sm,
    cloudRGBFloatValues,
    cloudNormedColorCoords,
    space3D,
    normedInputConverter,
    totalCloudCount,
    NA_FALSE,
    NA_FALSE);

  glDisable(GL_DEPTH_TEST);
  
  glPointSize((2.f / numChannels) / zoom);
  glBegin(GL_POINTS);
  for(size_t i = 0; i < totalCloudCount; ++i){
    glColor4f(cloudRGBFloatValues[i * 3 + 0], cloudRGBFloatValues[i * 3 + 1], cloudRGBFloatValues[i * 3 + 2], pointsAlpha);
    glVertex3fv(&(cloudNormedSystemCoords[i * 3]));
  }
  glEnd();
  
//    glEnableClientState(GL_COLOR_ARRAY);
//    glColorPointer(3, GL_UNSIGNED_BYTE, 0, cloudrgb8Bitvalues);
//    glEnableClientState(GL_VERTEX_ARRAY);
//    glVertexPointer(3, GL_FLOAT, 0, cloudNormedSystemCoords);
//    glDrawArrays(GL_POINTS, 0, totalCloudCount);
//    glDisableClientState(GL_COLOR_ARRAY);
//    glDisableClientState(GL_VERTEX_ARRAY);

  naFree(cloudNormedSystemCoords);
  naFree(cloudSystemCoords);
  naFree(cloudColorCoords);
  naFree(cloudRGBFloatValues);
  naFree(cloudNormedColorCoords);
}



void cmDrawThreeDeeSurfaces(const CMLColorMachine* cm, const CMLColorMachine* sm, const CMLVec3 backgroundRGB, const CMLVec3 axisRGB, NABool bodySolid, double bodyAlpha, double gridAlpha, double gridTint, CMLColorType space3D, NAInt steps3D, CMLNormedConverter normedInputConverter, CMLColorConverter coordConverter, CMLNormedConverter normedCoordConverter, NAInt hueIndex){
  if(!bodySolid){
//    glClear(GL_DEPTH_BUFFER_BIT);
  }
  glEnable(GL_DEPTH_TEST);
  
  size_t numChannels = cmlGetNumChannels(space3D);
  size_t surfaceCount = 0;
  CMLVec4UInt* surfaceSteps = NULL;
  CMLVec4* origins = NULL;
  CMLVec4* axis1s = NULL;
  CMLVec4* axis2s = NULL;
  switch(space3D){
  case CML_COLOR_GRAY:  surfaceCount = 0; break;
  case CML_COLOR_XYZ:   surfaceCount = 6; break;
  case CML_COLOR_Yxy:   surfaceCount = 4; break;
  case CML_COLOR_Yuv:   surfaceCount = 4; break;
  case CML_COLOR_Yupvp: surfaceCount = 4; break;
  case CML_COLOR_YCbCr: surfaceCount = 6; break;
  case CML_COLOR_Lab:   surfaceCount = 6; break;
  case CML_COLOR_Lch:   surfaceCount = 3; break;
  case CML_COLOR_Luv:   surfaceCount = 5; break;
  case CML_COLOR_RGB:   surfaceCount = 6; break;
  case CML_COLOR_HSV:   surfaceCount = 2; break;
  case CML_COLOR_HSL:   surfaceCount = 3; break;
  default: break;
  }

  if(surfaceCount){
    surfaceSteps = naMalloc(surfaceCount * sizeof(CMLVec4UInt));
    origins = naMalloc(surfaceCount * sizeof(CMLVec4));
    axis1s = naMalloc(surfaceCount * sizeof(CMLVec4));
    axis2s = naMalloc(surfaceCount * sizeof(CMLVec4));
    float** normedColorCoords = naMalloc(surfaceCount * sizeof(float*));
    float** rgbFloatValues = naMalloc(surfaceCount * sizeof(float*));
    float** colorCoords = naMalloc(surfaceCount * sizeof(float*));
    float** systemCoords = naMalloc(surfaceCount * sizeof(float*));
    float** normedSystemCoords = naMalloc(surfaceCount * sizeof(float*));
    
    switch(space3D){
    case CML_COLOR_GRAY: break;
    case CML_COLOR_XYZ:
      cmlSet4UInt(surfaceSteps[0], steps3D, steps3D, 1, 1);
      cmlSet4(origins[0], 0.f, 0.f, 0.f, 0.f);
      cmlSet4(axis1s[0], 1.f, 0.f, 0.f, 0.f);
      cmlSet4(axis2s[0], 0.f, 1.f, 0.f, 0.f);
      cmlSet4UInt(surfaceSteps[1], steps3D, steps3D, 1, 1);
      cmlSet4(origins[1], 0.f, 0.f, 0.f, 0.f);
      cmlSet4(axis1s[1], 0.f, 1.f, 0.f, 0.f);
      cmlSet4(axis2s[1], 0.f, 0.f, 1.f, 0.f);
      cmlSet4UInt(surfaceSteps[2], steps3D, steps3D, 1, 1);
      cmlSet4(origins[2], 0.f, 0.f, 0.f, 0.f);
      cmlSet4(axis1s[2], 0.f, 0.f, 1.f, 0.f);
      cmlSet4(axis2s[2], 1.f, 0.f, 0.f, 0.f);
      cmlSet4UInt(surfaceSteps[3], steps3D, steps3D, 1, 1);
      cmlSet4(origins[3], 1.f, 1.f, 1.f, 1.f);
      cmlSet4(axis1s[3], -1.f, 0.f, 0.f, 0.f);
      cmlSet4(axis2s[3], 0.f, -1.f, 0.f, 0.f);
      cmlSet4UInt(surfaceSteps[4], steps3D, steps3D, 1, 1);
      cmlSet4(origins[4], 1.f, 1.f, 1.f, 1.f);
      cmlSet4(axis1s[4], 0.f, -1.f, 0.f, 0.f);
      cmlSet4(axis2s[4], 0.f, 0.f, -1.f, 0.f);
      cmlSet4UInt(surfaceSteps[5], steps3D, steps3D, 1, 1);
      cmlSet4(origins[5], 1.f, 1.f, 1.f, 1.f);
      cmlSet4(axis1s[5], 0.f, 0.f, -1.f, 0.f);
      cmlSet4(axis2s[5], -1.f, 0.f, 0.f, 0.f);
      break;
    case CML_COLOR_Yxy:
      cmlSet4UInt(surfaceSteps[0], steps3D, steps3D, 1, 1);
      cmlSet4(origins[0], 0.f, 0.f, 0.f, 0.f);
      cmlSet4(axis1s[0], 0.f, 0.f, 1.f, 0.f);
      cmlSet4(axis2s[0], 1.f, 0.f, 0.f, 0.f);
      cmlSet4UInt(surfaceSteps[1], steps3D, steps3D, 1, 1);
      cmlSet4(origins[1], 1.f, 1.f, 1.f, 1.f);
      cmlSet4(axis1s[1], -1.f, 0.f, 0.f, 0.f);
      cmlSet4(axis2s[1], 0.f, -1.f, 0.f, 0.f);
      cmlSet4UInt(surfaceSteps[2], steps3D, steps3D, 1, 1);
      cmlSet4(origins[2], 1.f, 1.f, 1.f, 1.f);
      cmlSet4(axis1s[2], 0.f, -1.f, 0.f, 0.f);
      cmlSet4(axis2s[2], 0.f, 0.f, -1.f, 0.f);
      cmlSet4UInt(surfaceSteps[3], steps3D, steps3D, 1, 1);
      cmlSet4(origins[3], 1.f, 1.f, 1.f, 1.f);
      cmlSet4(axis1s[3], 0.f, 0.f, -1.f, 0.f);
      cmlSet4(axis2s[3], -1.f, 0.f, 0.f, 0.f);
      break;
    case CML_COLOR_Yuv:
      cmlSet4UInt(surfaceSteps[0], steps3D, steps3D, 1, 1);
      cmlSet4(origins[0], 0.f, 0.f, 0.f, 0.f);
      cmlSet4(axis1s[0], 0.f, 0.f, 1.f, 0.f);
      cmlSet4(axis2s[0], 1.f, 0.f, 0.f, 0.f);
      cmlSet4UInt(surfaceSteps[1], steps3D, steps3D, 1, 1);
      cmlSet4(origins[1], 1.f, 1.f, 1.f, 1.f);
      cmlSet4(axis1s[1], -1.f, 0.f, 0.f, 0.f);
      cmlSet4(axis2s[1], 0.f, -1.f, 0.f, 0.f);
      cmlSet4UInt(surfaceSteps[2], steps3D, steps3D, 1, 1);
      cmlSet4(origins[2], 1.f, 1.f, 1.f, 1.f);
      cmlSet4(axis1s[2], 0.f, -1.f, 0.f, 0.f);
      cmlSet4(axis2s[2], 0.f, 0.f, -1.f, 0.f);
      cmlSet4UInt(surfaceSteps[3], steps3D, steps3D, 1, 1);
      cmlSet4(origins[3], 1.f, 1.f, 1.f, 1.f);
      cmlSet4(axis1s[3], 0.f, 0.f, -1.f, 0.f);
      cmlSet4(axis2s[3], -1.f, 0.f, 0.f, 0.f);
      break;
    case CML_COLOR_Yupvp:
      cmlSet4UInt(surfaceSteps[0], steps3D, steps3D, 1, 1);
      cmlSet4(origins[0], 0.f, 0.f, 0.f, 0.f);
      cmlSet4(axis1s[0], 0.f, 0.f, 1.f, 0.f);
      cmlSet4(axis2s[0], 1.f, 0.f, 0.f, 0.f);
      cmlSet4UInt(surfaceSteps[1], steps3D, steps3D, 1, 1);
      cmlSet4(origins[1], 1.f, 1.f, 1.f, 1.f);
      cmlSet4(axis1s[1], -1.f, 0.f, 0.f, 0.f);
      cmlSet4(axis2s[1], 0.f, -1.f, 0.f, 0.f);
      cmlSet4UInt(surfaceSteps[2], steps3D, steps3D, 1, 1);
      cmlSet4(origins[2], 1.f, 1.f, 1.f, 1.f);
      cmlSet4(axis1s[2], 0.f, -1.f, 0.f, 0.f);
      cmlSet4(axis2s[2], 0.f, 0.f, -1.f, 0.f);
      cmlSet4UInt(surfaceSteps[3], steps3D, steps3D, 1, 1);
      cmlSet4(origins[3], 1.f, 1.f, 1.f, 1.f);
      cmlSet4(axis1s[3], 0.f, 0.f, -1.f, 0.f);
      cmlSet4(axis2s[3], -1.f, 0.f, 0.f, 0.f);
      break;
    case CML_COLOR_YCbCr:
      cmlSet4UInt(surfaceSteps[0], steps3D, steps3D, 1, 1);
      cmlSet4(origins[0], 0.f, 0.f, 0.f, 0.f);
      cmlSet4(axis1s[0], 1.f, 0.f, 0.f, 0.f);
      cmlSet4(axis2s[0], 0.f, 1.f, 0.f, 0.f);
      cmlSet4UInt(surfaceSteps[1], steps3D, steps3D, 1, 1);
      cmlSet4(origins[1], 0.f, 0.f, 0.f, 0.f);
      cmlSet4(axis1s[1], 0.f, 1.f, 0.f, 0.f);
      cmlSet4(axis2s[1], 0.f, 0.f, 1.f, 0.f);
      cmlSet4UInt(surfaceSteps[2], steps3D, steps3D, 1, 1);
      cmlSet4(origins[2], 0.f, 0.f, 0.f, 0.f);
      cmlSet4(axis1s[2], 0.f, 0.f, 1.f, 0.f);
      cmlSet4(axis2s[2], 1.f, 0.f, 0.f, 0.f);
      cmlSet4UInt(surfaceSteps[3], steps3D, steps3D, 1, 1);
      cmlSet4(origins[3], 1.f, 1.f, 1.f, 1.f);
      cmlSet4(axis1s[3], -1.f, 0.f, 0.f, 0.f);
      cmlSet4(axis2s[3], 0.f, -1.f, 0.f, 0.f);
      cmlSet4UInt(surfaceSteps[4], steps3D, steps3D, 1, 1);
      cmlSet4(origins[4], 1.f, 1.f, 1.f, 1.f);
      cmlSet4(axis1s[4], 0.f, -1.f, 0.f, 0.f);
      cmlSet4(axis2s[4], 0.f, 0.f, -1.f, 0.f);
      cmlSet4UInt(surfaceSteps[5], steps3D, steps3D, 1, 1);
      cmlSet4(origins[5], 1.f, 1.f, 1.f, 1.f);
      cmlSet4(axis1s[5], 0.f, 0.f, -1.f, 0.f);
      cmlSet4(axis2s[5], -1.f, 0.f, 0.f, 0.f);
      break;
    case CML_COLOR_Lab:
      cmlSet4UInt(surfaceSteps[0], steps3D, steps3D, 1, 1);
      cmlSet4(origins[0], 0.f, 0.f, 0.f, 0.f);
      cmlSet4(axis1s[0], 1.f, 0.f, 0.f, 0.f);
      cmlSet4(axis2s[0], 0.f, 1.f, 0.f, 0.f);
      cmlSet4UInt(surfaceSteps[1], steps3D, steps3D, 1, 1);
      cmlSet4(origins[1], 0.f, 0.f, 0.f, 0.f);
      cmlSet4(axis1s[1], 0.f, 1.f, 0.f, 0.f);
      cmlSet4(axis2s[1], 0.f, 0.f, 1.f, 0.f);
      cmlSet4UInt(surfaceSteps[2], steps3D, steps3D, 1, 1);
      cmlSet4(origins[2], 0.f, 0.f, 0.f, 0.f);
      cmlSet4(axis1s[2], 0.f, 0.f, 1.f, 0.f);
      cmlSet4(axis2s[2], 1.f, 0.f, 0.f, 0.f);
      cmlSet4UInt(surfaceSteps[3], steps3D, steps3D, 1, 1);
      cmlSet4(origins[3], 1.f, 1.f, 1.f, 1.f);
      cmlSet4(axis1s[3], -1.f, 0.f, 0.f, 0.f);
      cmlSet4(axis2s[3], 0.f, -1.f, 0.f, 0.f);
      cmlSet4UInt(surfaceSteps[4], steps3D, steps3D, 1, 1);
      cmlSet4(origins[4], 1.f, 1.f, 1.f, 1.f);
      cmlSet4(axis1s[4], 0.f, -1.f, 0.f, 0.f);
      cmlSet4(axis2s[4], 0.f, 0.f, -1.f, 0.f);
      cmlSet4UInt(surfaceSteps[5], steps3D, steps3D, 1, 1);
      cmlSet4(origins[5], 1.f, 1.f, 1.f, 1.f);
      cmlSet4(axis1s[5], 0.f, 0.f, -1.f, 0.f);
      cmlSet4(axis2s[5], -1.f, 0.f, 0.f, 0.f);
      break;
    case CML_COLOR_Lch:
      cmlSet4UInt(surfaceSteps[0], steps3D, steps3D * 3 + 1, 1, 1);
      cmlSet4(origins[0], 0.f, 0.f, 0.f, 0.f);
      cmlSet4(axis1s[0], 0.f, 1.f, 0.f, 0.f);
      cmlSet4(axis2s[0], 0.f, 0.f, 1.f, 0.f);
      cmlSet4UInt(surfaceSteps[1], steps3D, steps3D * 3 + 1, 1, 1);
      cmlSet4(origins[1], 1.f, 1.f, 1.f, 1.f);
      cmlSet4(axis1s[1], 0.f, -1.f, 0.f, 0.f);
      cmlSet4(axis2s[1], 0.f, 0.f, -1.f, 0.f);
      cmlSet4UInt(surfaceSteps[2], steps3D * 3 + 1, steps3D, 1, 1);
      cmlSet4(origins[2], 1.f, 1.f, 1.f, 1.f);
      cmlSet4(axis1s[2], 0.f, 0.f, -1.f, 0.f);
      cmlSet4(axis2s[2], -1.f, 0.f, 0.f, 0.f);
      break;
    case CML_COLOR_Luv:
      cmlSet4UInt(surfaceSteps[0], steps3D, steps3D, 1, 1);
      cmlSet4(origins[0], 0.f, 0.f, 0.f, 0.f);
      cmlSet4(axis1s[0], 1.f, 0.f, 0.f, 0.f);
      cmlSet4(axis2s[0], 0.f, 1.f, 0.f, 0.f);
      cmlSet4UInt(surfaceSteps[1], steps3D, steps3D, 1, 1);
      cmlSet4(origins[1], 0.f, 0.f, 0.f, 0.f);
      cmlSet4(axis1s[1], 0.f, 0.f, 1.f, 0.f);
      cmlSet4(axis2s[1], 1.f, 0.f, 0.f, 0.f);
      cmlSet4UInt(surfaceSteps[2], steps3D, steps3D, 1, 1);
      cmlSet4(origins[2], 1.f, 1.f, 1.f, 1.f);
      cmlSet4(axis1s[2], -1.f, 0.f, 0.f, 0.f);
      cmlSet4(axis2s[2], 0.f, -1.f, 0.f, 0.f);
      cmlSet4UInt(surfaceSteps[3], steps3D, steps3D, 1, 1);
      cmlSet4(origins[3], 1.f, 1.f, 1.f, 1.f);
      cmlSet4(axis1s[3], 0.f, -1.f, 0.f, 0.f);
      cmlSet4(axis2s[3], 0.f, 0.f, -1.f, 0.f);
      cmlSet4UInt(surfaceSteps[4], steps3D, steps3D, 1, 1);
      cmlSet4(origins[4], 1.f, 1.f, 1.f, 1.f);
      cmlSet4(axis1s[4], 0.f, 0.f, -1.f, 0.f);
      cmlSet4(axis2s[4], -1.f, 0.f, 0.f, 0.f);
      break;
    case CML_COLOR_RGB:
      cmlSet4UInt(surfaceSteps[0], steps3D, steps3D, 1, 1);
      cmlSet4(origins[0], 0.f, 0.f, 0.f, 0.f);
      cmlSet4(axis1s[0], 1.f, 0.f, 0.f, 0.f);
      cmlSet4(axis2s[0], 0.f, 1.f, 0.f, 0.f);
      cmlSet4UInt(surfaceSteps[1], steps3D, steps3D, 1, 1);
      cmlSet4(origins[1], 0.f, 0.f, 0.f, 0.f);
      cmlSet4(axis1s[1], 0.f, 1.f, 0.f, 0.f);
      cmlSet4(axis2s[1], 0.f, 0.f, 1.f, 0.f);
      cmlSet4UInt(surfaceSteps[2], steps3D, steps3D, 1, 1);
      cmlSet4(origins[2], 0.f, 0.f, 0.f, 0.f);
      cmlSet4(axis1s[2], 0.f, 0.f, 1.f, 0.f);
      cmlSet4(axis2s[2], 1.f, 0.f, 0.f, 0.f);
      cmlSet4UInt(surfaceSteps[3], steps3D, steps3D, 1, 1);
      cmlSet4(origins[3], 1.f, 1.f, 1.f, 1.f);
      cmlSet4(axis1s[3], -1.f, 0.f, 0.f, 0.f);
      cmlSet4(axis2s[3], 0.f, -1.f, 0.f, 0.f);
      cmlSet4UInt(surfaceSteps[4], steps3D, steps3D, 1, 1);
      cmlSet4(origins[4], 1.f, 1.f, 1.f, 1.f);
      cmlSet4(axis1s[4], 0.f, -1.f, 0.f, 0.f);
      cmlSet4(axis2s[4], 0.f, 0.f, -1.f, 0.f);
      cmlSet4UInt(surfaceSteps[5], steps3D, steps3D, 1, 1);
      cmlSet4(origins[5], 1.f, 1.f, 1.f, 1.f);
      cmlSet4(axis1s[5], 0.f, 0.f, -1.f, 0.f);
      cmlSet4(axis2s[5], -1.f, 0.f, 0.f, 0.f);
      break;
    case CML_COLOR_HSV:
      cmlSet4UInt(surfaceSteps[0], steps3D * 3 + 1, steps3D, 1, 1);
      cmlSet4(origins[0], 1.f, 1.f, 1.f, 1.f);
      cmlSet4(axis1s[0], -1.f, 0.f, 0.f, 0.f);
      cmlSet4(axis2s[0], 0.f, -1.f, 0.f, 0.f);
      cmlSet4UInt(surfaceSteps[1], steps3D, steps3D * 3 + 1, 1, 1);
      cmlSet4(origins[1], 1.f, 1.f, 1.f, 1.f);
      cmlSet4(axis1s[1], 0.f, 0.f, -1.f, 0.f);
      cmlSet4(axis2s[1], -1.f, 0.f, 0.f, 0.f);
      break;
    case CML_COLOR_HSL:
      cmlSet4UInt(surfaceSteps[0], steps3D * 3 + 1, steps3D, 1, 1);
      cmlSet4(origins[0], 0.f, 0.f, 0.f, 0.f);
      cmlSet4(axis1s[0], 1.f, 0.f, 0.f, 0.f);
      cmlSet4(axis2s[0], 0.f, 1.f, 0.f, 0.f);
      cmlSet4UInt(surfaceSteps[1], steps3D * 3 + 1, steps3D, 1, 1);
      cmlSet4(origins[1], 1.f, 1.f, 1.f, 1.f);
      cmlSet4(axis1s[1], -1.f, 0.f, 0.f, 0.f);
      cmlSet4(axis2s[1], 0.f, -1.f, 0.f, 0.f);
      cmlSet4UInt(surfaceSteps[2], steps3D, steps3D * 3 + 1, 1, 1);
      cmlSet4(origins[2], 1.f, 1.f, 1.f, 1.f);
      cmlSet4(axis1s[2], 0.f, 0.f, -1.f, 0.f);
      cmlSet4(axis2s[2], -1.f, 0.f, 0.f, 0.f);
      break;
    default: break;
    }

    for(size_t s = 0; s < surfaceCount; ++s){
      size_t totalCount = surfaceSteps[s][0] * surfaceSteps[s][1] * surfaceSteps[s][2] * surfaceSteps[s][3];
      normedColorCoords[s] = (float*)cmlCreateNormedGamutSlice(space3D, surfaceSteps[s], origins[s], axis1s[s], axis2s[s], NULL, NULL);
      rgbFloatValues[s] = naMalloc(totalCount * 3 * sizeof(float));
      colorCoords[s] = naMalloc(totalCount * numChannels * sizeof(float));
      systemCoords[s] = naMalloc(totalCount * 3 * sizeof(float));
      normedSystemCoords[s] = naMalloc(totalCount * 3 * sizeof(float));

      normedInputConverter(colorCoords[s], normedColorCoords[s], totalCount);
      coordConverter(cm, systemCoords[s], colorCoords[s], totalCount);
      normedCoordConverter(normedSystemCoords[s], systemCoords[s], totalCount);
      
      // Convert the given values to screen RGBs.
      fillRGBFloatArrayWithArray(
        cm,
        sm,
        rgbFloatValues[s],
        normedColorCoords[s],
        space3D,
        normedInputConverter,
        totalCount,
        NA_FALSE,
        NA_FALSE);
    }

    // ////////////////////
    // Draw the quads
    // ////////////////////

    for(size_t s = 0; s < surfaceCount; ++s){
      glEnable(GL_POLYGON_OFFSET_FILL);
      glPolygonOffset(1.f, 1.f);
      glShadeModel(GL_FLAT);
      glBegin(GL_QUADS);
      for(size_t ax1 = 0; ax1 < surfaceSteps[s][1] - 1; ax1++){
        for(size_t ax2 = 0; ax2 < surfaceSteps[s][0] - 1; ax2++){
          size_t index0 = (ax1 + 0) * surfaceSteps[s][0] * 3 + (ax2 + 0) * 3;
          size_t index1 = (ax1 + 0) * surfaceSteps[s][0] * 3 + (ax2 + 1) * 3;
          size_t index2 = (ax1 + 1) * surfaceSteps[s][0] * 3 + (ax2 + 1) * 3;
          size_t index3 = (ax1 + 1) * surfaceSteps[s][0] * 3 + (ax2 + 0) * 3;

          glColor4f(rgbFloatValues[s][index3 + 0] * bodyAlpha + backgroundRGB[0] * (1.f - bodyAlpha),
                    rgbFloatValues[s][index3 + 1] * bodyAlpha + backgroundRGB[1] * (1.f - bodyAlpha),
                    rgbFloatValues[s][index3 + 2] * bodyAlpha + backgroundRGB[2] * (1.f - bodyAlpha),
                    1.f);

          if(hueIndex >= 0){
            if(    (fabsf(normedSystemCoords[s][index0 + hueIndex] - normedSystemCoords[s][index1 + hueIndex]) > .5f)
                || (fabsf(normedSystemCoords[s][index0 + hueIndex] - normedSystemCoords[s][index2 + hueIndex]) > .5f)
                || (fabsf(normedSystemCoords[s][index0 + hueIndex] - normedSystemCoords[s][index3 + hueIndex]) > .5f)){
              continue;
            }
          }
          
          glVertex3fv(&(normedSystemCoords[s][index0]));
          glVertex3fv(&(normedSystemCoords[s][index1]));
          glVertex3fv(&(normedSystemCoords[s][index2]));
          glVertex3fv(&(normedSystemCoords[s][index3]));
        }
      }
      glEnd();
      glPolygonOffset(0.f, 0.f);
      glDisable(GL_POLYGON_OFFSET_FILL);
    }

    if(!bodySolid){
      glClear(GL_DEPTH_BUFFER_BIT);
    }

    // ////////////////////
    // Draw the lines
    // ////////////////////

    for(size_t s = 0; s < surfaceCount; ++s){
      if(gridAlpha > 0.f){
        glShadeModel(GL_SMOOTH);
        glDepthFunc(GL_LEQUAL);
        for(size_t ax1 = 0; ax1 < surfaceSteps[s][1] - 1; ax1++){
          for(size_t ax2 = 0; ax2 < surfaceSteps[s][0] - 1; ax2++){
            size_t index0 = (ax1 + 0) * surfaceSteps[s][0] * 3 + (ax2 + 0) * 3;
            size_t index1 = (ax1 + 0) * surfaceSteps[s][0] * 3 + (ax2 + 1) * 3;
            size_t index2 = (ax1 + 1) * surfaceSteps[s][0] * 3 + (ax2 + 1) * 3;
            size_t index3 = (ax1 + 1) * surfaceSteps[s][0] * 3 + (ax2 + 0) * 3;
            if(hueIndex >= 0){
              if(    (fabsf(normedSystemCoords[s][index0 + hueIndex] - normedSystemCoords[s][index1 + hueIndex]) > .5f)
                  || (fabsf(normedSystemCoords[s][index0 + hueIndex] - normedSystemCoords[s][index2 + hueIndex]) > .5f)
                  || (fabsf(normedSystemCoords[s][index0 + hueIndex] - normedSystemCoords[s][index3 + hueIndex]) > .5f)){
                continue;
              }
            }
            glBegin(GL_LINE_STRIP);
            glColor4f( rgbFloatValues[s][index0 + 0] * gridTint + axisRGB[0] * (1.f - gridTint),
                        rgbFloatValues[s][index0 + 1] * gridTint + axisRGB[1] * (1.f - gridTint),
                        rgbFloatValues[s][index0 + 2] * gridTint + axisRGB[2] * (1.f - gridTint), gridAlpha);
            glVertex3fv(&(normedSystemCoords[s][index0]));
            glColor4f( rgbFloatValues[s][index1 + 0] * gridTint + axisRGB[0] * (1.f - gridTint),
                        rgbFloatValues[s][index1 + 1] * gridTint + axisRGB[1] * (1.f - gridTint),
                        rgbFloatValues[s][index1 + 2] * gridTint + axisRGB[2] * (1.f - gridTint), gridAlpha);
            glVertex3fv(&(normedSystemCoords[s][index1]));
            glColor4f( rgbFloatValues[s][index2 + 0] * gridTint + axisRGB[0] * (1.f - gridTint),
                        rgbFloatValues[s][index2 + 1] * gridTint + axisRGB[1] * (1.f - gridTint),
                        rgbFloatValues[s][index2 + 2] * gridTint + axisRGB[2] * (1.f - gridTint), gridAlpha);
            glVertex3fv(&(normedSystemCoords[s][index2]));
            glColor4f( rgbFloatValues[s][index3 + 0] * gridTint + axisRGB[0] * (1.f - gridTint),
                        rgbFloatValues[s][index3 + 1] * gridTint + axisRGB[1] * (1.f - gridTint),
                        rgbFloatValues[s][index3 + 2] * gridTint + axisRGB[2] * (1.f - gridTint), gridAlpha);
            glVertex3fv(&(normedSystemCoords[s][index3]));
            glColor4f( rgbFloatValues[s][index0 + 0] * gridTint + axisRGB[0] * (1.f - gridTint),
                        rgbFloatValues[s][index0 + 1] * gridTint + axisRGB[1] * (1.f - gridTint),
                        rgbFloatValues[s][index0 + 2] * gridTint + axisRGB[2] * (1.f - gridTint), gridAlpha);
            glVertex3fv(&(normedSystemCoords[s][index0]));

            glEnd();
          }
        }
        glDepthFunc(GL_LESS);
      }

    }

    for(size_t s = 0; s < surfaceCount; ++s){
      naFree(normedSystemCoords[s]);
      naFree(systemCoords[s]);
      naFree(colorCoords[s]);
      naFree(rgbFloatValues[s]);
      naFree(normedColorCoords[s]);
    }

    naFree(normedColorCoords);
    naFree(rgbFloatValues);
    naFree(colorCoords);
    naFree(systemCoords);
    naFree(normedSystemCoords);
    naFree(axis2s);
    naFree(axis1s);
    naFree(origins);
    naFree(surfaceSteps);
  }
}



void cmDrawThreeDeeSpectrum(const CMLColorMachine* cm, CMLNormedConverter normedCoordConverter, CMLColorType coordSpace, NAInt hueIndex){
  float iMin = CML_DEFAULT_INTEGRATION_MIN;
  float iMax = CML_DEFAULT_INTEGRATION_MAX;
  NAInt intervals = (int32)((iMax - iMin) / CML_DEFAULT_INTEGRATION_STEPSIZE) + 1;
  
  CMLColorConverter xyzConverter = cmlGetColorConverter(coordSpace, CML_COLOR_XYZ);

  glBegin(GL_LINE_STRIP);
    float prevNormedHue = -CML_INFINITY;
    for(NAInt iStep = 0; iStep <= intervals; ++iStep){
      float l = iMin + (((iMax - iMin) * iStep) / intervals);
      CMLVec3 curXYZ;
      cmlGetSpectralXYZColor(cm, curXYZ, l);
      
      if(curXYZ[1] > 0.f){
        CMLVec3 curRGB;
        CMLVec3 curCoords;
        CMLVec3 curNormedCoords;
        xyzConverter(cm, curCoords, curXYZ, 1);
        normedCoordConverter(curNormedCoords, curCoords, 1);
        
        if(hueIndex >= 0){
          if((prevNormedHue != -CML_INFINITY) && (fabsf(prevNormedHue - curNormedCoords[hueIndex]) > .5f)){
            glEnd();
            glBegin(GL_LINE_STRIP);      
            prevNormedHue = -CML_INFINITY;
            continue;
          }else{
            prevNormedHue = curNormedCoords[hueIndex];
          }
        }
        
        cmlXYZToRGB(cm, curRGB, curXYZ, 1);
        cmlMul3(curRGB, .7f);
        cmlClampRGB(curRGB, 1);
        cmlMul3(curRGB, .7f);
        glColor4f(curRGB[0], curRGB[1], curRGB[2], 1.f);
        glVertex3fv(curNormedCoords);
      }
    }
  glEnd();
}



void cmDrawThreeDeeAxis(CMLNormedConverter normedCoordConverter, const float* min, const float* max, const char** labels, const CMLVec3 axisRGB, NAInt fontId){
  glClear(GL_DEPTH_BUFFER_BIT);
  glColor3fv(axisRGB);

  float pos[3] = {0.f, 0.f, 0.f};
  float normedPos[3];
  
  glBegin(GL_LINES);
    // draw a line from -x to +x
    pos[0] = min[0];
    normedCoordConverter(normedPos, pos, 1);
    glVertex3fv(normedPos);
    pos[0] = max[0];
    normedCoordConverter(normedPos, pos, 1);
    glVertex3fv(normedPos);
    pos[0] = 0.f;
    
    // draw a line from -y to +y
    pos[1] = min[1];
    normedCoordConverter(normedPos, pos, 1);
    glVertex3fv(normedPos);
    pos[1] = max[1];
    normedCoordConverter(normedPos, pos, 1);
    glVertex3fv(normedPos);
    pos[1] = 0.f;
    
    // draw a line from -z to +z
    pos[2] = min[2];
    normedCoordConverter(normedPos, pos, 1);
    glVertex3fv(normedPos);
    pos[2] = max[2];
    normedCoordConverter(normedPos, pos, 1);
    glVertex3fv(normedPos);
    pos[2] = 0.f;
  glEnd();

  // Draw label X
  pos[0] = max[0] * 1.03f;
  normedCoordConverter(normedPos, pos, 1);
  naDrawASCIICharacters(fontId, labels[0], normedPos[0], normedPos[1], normedPos[2]);
  pos[0] = 0.f;
  
  // Draw label Y
  pos[1] = max[1] * 1.03f;
  normedCoordConverter(normedPos, pos, 1);
  naDrawASCIICharacters(fontId, labels[1], normedPos[0], normedPos[1], normedPos[2]);
  pos[1] = 0.f;
  
  // Draw label Z
  pos[2] = max[2] * 1.03f;
  normedCoordConverter(normedPos, pos, 1);
  naDrawASCIICharacters(fontId, labels[2], normedPos[0], normedPos[1], normedPos[2]);
  pos[2] = 0.f;
}
