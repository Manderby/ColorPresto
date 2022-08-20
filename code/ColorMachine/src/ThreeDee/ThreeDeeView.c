
#include "NAApp.h"
#include "NAMath.h"
#include "NAVisual.h"
#include "ThreeDeeView.h"



void cmBeginThreeDeeDrawing(const CMLVec3 axisRGB){
  glClearColor(axisRGB[0], axisRGB[1], axisRGB[2], 1.);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  glEnable(GL_BLEND);
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}



void cmEndThreeDeeDrawing(NAOpenGLSpace* openGlSpace){
  naSwapOpenGLSpaceBuffer(openGlSpace);
}



void cmSetupThreeDeeProjection(NASize viewSize, double fovy, double zoom){
  glViewport(0, 0, (GLsizei)viewSize.width, (GLsizei)viewSize.height);
  
//  float curZoom;

  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();

  if(fovy == 0){
    glOrtho(
      -(viewSize.width  / 200.) * zoom,
       (viewSize.width  / 200.) * zoom,
      -(viewSize.height / 200.) * zoom,
       (viewSize.height / 200.) * zoom,
      -50.,
      50.);
  }else{
    NAMat44d projectionMatrix;
    naFillMatrixPerspective(
      projectionMatrix,
      fovy,
      viewSize.width / viewSize.height,
      .1,
      50.);
    glLoadMatrixd(projectionMatrix);
  }
}



void cmSetupThreeDeeModelView(int primeAxis, const double* scale, double curZoom, double viewPol, double viewEqu){
  float vshift = .2f;
  NAMat44d matrix;

  glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

  switch(primeAxis){
  case 0:
    naFillMatrixLookAt(matrix,
      vshift * scale[0] + curZoom * 3 * naCosf(viewPol),
      .5f * scale[1] + curZoom * 3 * naCosf(viewEqu) * naSinf(viewPol),
      .5f * scale[2] + curZoom * 3 * naSinf(viewEqu) * naSinf(viewPol),
      vshift * scale[0], .5f * scale[1], .5f * scale[2],
      1, 0, 0);
    break;
  case 1:
    naFillMatrixLookAt(matrix,
      .5f * scale[0] + curZoom * 3 * naSinf(viewEqu) * naSinf(viewPol),
      vshift * scale[1] + curZoom * 3 * naCosf(viewPol),
      .5f * scale[2] + curZoom * 3 * naCosf(viewEqu) * naSinf(viewPol),
      .5f * scale[0], vshift * scale[1], .5f * scale[2],
      0, 1, 0);
    break;
  case 2:
    naFillMatrixLookAt(matrix,
      .5f * scale[0] + curZoom * 3 * naCosf(viewEqu) * naSinf(viewPol),
      .5f * scale[1] + curZoom * 3 * naSinf(viewEqu) * naSinf(viewPol),
      vshift * scale[2] + curZoom * 3 * naCosf(viewPol),
      .5f * scale[0], .5f * scale[1], vshift * scale[2],
      0, 0, 1);
    break;
  }
  
  glLoadMatrixd(matrix);
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

  float center[3] = {0.f, 0.f, 0.f};
  float normedCenter[3];
  glBegin(GL_LINES);
    // draw a line from -x to +x
    center[0] = min[0];
    normedCoordConverter(normedCenter, center, 1);
    glVertex3fv(normedCenter);
    center[0] = max[0];
    normedCoordConverter(normedCenter, center, 1);
    glVertex3fv(normedCenter);
    center[0] = 0.f;
    
    // draw a line from -y to +y
    center[1] = min[1];
    normedCoordConverter(normedCenter, center, 1);
    glVertex3fv(normedCenter);
    center[1] = max[1];
    normedCoordConverter(normedCenter, center, 1);
    glVertex3fv(normedCenter);
    center[1] = 0.f;
    
    // draw a line from -z to +z
    center[2] = min[2];
    normedCoordConverter(normedCenter, center, 1);
    glVertex3fv(normedCenter);
    center[2] = max[2];
    normedCoordConverter(normedCenter, center, 1);
    glVertex3fv(normedCenter);
    center[2] = 0.f;
  glEnd();

  // Draw label X
  center[0] = max[0] * 1.03f;
  normedCoordConverter(normedCenter, center, 1);
  naDrawASCIICharacters(fontId, labels[0], normedCenter[0], normedCenter[1], normedCenter[2]);
  center[0] = 0.f;
  
  // Draw label Y
  center[1] = max[1] * 1.03f;
  normedCoordConverter(normedCenter, center, 1);
  naDrawASCIICharacters(fontId, labels[1], normedCenter[0], normedCenter[1], normedCenter[2]);
  center[1] = 0.f;
  
  // Draw label Z
  center[2] = max[2] * 1.03f;
  normedCoordConverter(normedCenter, center, 1);
  naDrawASCIICharacters(fontId, labels[2], normedCenter[0], normedCenter[1], normedCenter[2]);
  center[2] = 0.f;
}
