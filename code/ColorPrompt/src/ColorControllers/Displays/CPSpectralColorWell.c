
#include "CPSpectralColorWell.h"

#include "../../CPColorPromptApplication.h"
#include "../../CPDesign.h"
#include "../CPColorController.h"

#include "NAApp.h"



struct CPSpectralColorWell{
  NAOpenGLSpace* openGLSpace;
  NAInt fontId;

  GLuint wellTex;

  CPColorController* colorController;
};



NABool cmDragSpectralColorWell(NAReaction reaction){
  const NAMouseStatus* mouseStatus = naGetMouseStatus();
  if(mouseStatus->leftPressed){
    CPSpectralColorWell* well = (CPSpectralColorWell*)reaction.controller;
    CMLColorMachine* cm = cpGetCurrentColorMachine();

    NARect spaceRect = naGetUIElementRectAbsolute(well->openGLSpace);
    double mouseX = (mouseStatus->pos.x - spaceRect.pos.x) / spaceRect.size.width;
    if(mouseX < 0.f){mouseX = 0.f;}
    if(mouseX > 1.f){mouseX = 1.f;}

    float lambda = CML_DEFAULT_INTEGRATION_MIN + (CML_DEFAULT_INTEGRATION_MAX - CML_DEFAULT_INTEGRATION_MIN) * (float)mouseX;

    CMLFunction* dirac = cmlCreateDiracFilter(lambda);
    CMLFunction* illumDirac = cmlCreateFunctionMulScalar(dirac, cmlInverse(cmlGetRadiometricScale(cm)));

    cmSetColorControllerColorData(well->colorController, illumDirac);
    cpSetCurrentColorController(well->colorController);
    cpUpdateColor();

    cmlReleaseFunction(dirac);
    cmlReleaseFunction(illumDirac);

    return NA_TRUE;
  }

  return NA_FALSE;
}



void cmInitSpectralColorWell(void* data){
  CPSpectralColorWell* well = (CPSpectralColorWell*)data;
  glEnable(GL_LINE_SMOOTH);
  glEnable(GL_BLEND);
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

  glGenTextures(1, &(well->wellTex));
  glBindTexture(GL_TEXTURE_1D, well->wellTex);
  glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);
  glTexParameteri(GL_TEXTURE_1D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
  glTexParameteri(GL_TEXTURE_1D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

  // Draw the background;
  CMLColorMachine* cm = cpGetCurrentColorMachine();
  CMLColorMachine* sm = cpGetCurrentScreenMachine();

  float rgbInputValues[spectralWellSize * 3] = {0};
  for(size_t x = 0; x < spectralWellSize; ++x){
    float lambda = CML_DEFAULT_INTEGRATION_MIN + ((float)x / spectralWellSize) * (CML_DEFAULT_INTEGRATION_MAX - CML_DEFAULT_INTEGRATION_MIN);
    CMLVec3 xyz;
    cmlGetSpectralXYZColor(sm, xyz, lambda);
    float* rgbPtr = &rgbInputValues[x * 3];
    cmlXYZToRGB(sm, rgbPtr, xyz, 1);
    cmlClampRGB(rgbPtr, 1);
    cmlMul3(rgbPtr, .4f);
  }
  cmlRGBToNormedOutput(rgbInputValues, rgbInputValues, spectralWellSize);

  // Convert the given values to screen RGBs.
  float rgbValues[spectralWellSize * 3];
  fillRGBFloatArrayWithArray(
    cm,
    sm,
    rgbValues,
    rgbInputValues,
    CML_COLOR_RGB,
    cmlGetNormedInputConverter(CML_COLOR_RGB),
    spectralWellSize);

  glTexImage1D(GL_TEXTURE_1D, 0, GL_RGBA, spectralWellSize, 0, GL_RGB, GL_FLOAT, rgbValues);
}



NABool cmDrawSpectralColorWell(NAReaction reaction){
  CPSpectralColorWell* well = (CPSpectralColorWell*)reaction.controller;
  CMLColorMachine* cm = cpGetCurrentColorMachine();
//  CMLColorMachine* sm = cpGetCurrentScreenMachine();

  double uiScale = naGetUIElementResolutionFactor(well->openGLSpace);
  NASize viewSize = naGetUIElementRect(reaction.uiElement).size;
  glViewport(
    0,
    0,
    (GLsizei)(viewSize.width * uiScale),
    (GLsizei)(viewSize.height * uiScale));

  glClear(GL_DEPTH_BUFFER_BIT);

  // Draw the background
  glEnable(GL_TEXTURE_1D);
  glBegin(GL_TRIANGLE_STRIP);
    glTexCoord2f(0., 0.);
    glVertex2f(-1., -1.);
    glTexCoord2f(0., 1.);
    glVertex2f(-1., +1.);
    glTexCoord2f(1., 0.);
    glVertex2f(+1., -1.);
    glTexCoord2f(1., 1.);
    glVertex2f(+1., +1.);
  glEnd();

  // Draw the Grid
  glMatrixMode(GL_PROJECTION);
  glPushMatrix();
  glLoadIdentity();
  glOrtho(CML_DEFAULT_INTEGRATION_MIN, CML_DEFAULT_INTEGRATION_MAX, 0, 1., -1., 1.);

  int lineOffset = (int)roundf((CML_DEFAULT_INTEGRATION_MIN) / 10.f);
  float lineCount = (CML_DEFAULT_INTEGRATION_MAX - CML_DEFAULT_INTEGRATION_MIN) / 10.f;

  glDisable(GL_TEXTURE_1D);
  glBegin(GL_LINES);
    for(int i = 0; i <= (int)lineCount; ++i){
      if(!((lineOffset + i) % 10)){
        glColor4f(1.f, 1.f, 1.f, .45f);
      }else if(!((lineOffset+i) % 5)){
        glColor4f(1.f, 1.f, 1.f, .175f);
      }else{
        glColor4f(1.f, 1.f, 1.f, .075f);
      }
      float lambda = CML_DEFAULT_INTEGRATION_MIN + ((float)i / lineCount) * (CML_DEFAULT_INTEGRATION_MAX - CML_DEFAULT_INTEGRATION_MIN);
      glVertex2f(lambda, 0);
      glVertex2f(lambda, 1.);
    }

    // Draw the bottom and top line
    const float viewRange = .8f;
    const float viewOffset = .05f;
    glColor4f(1.f, 1.f, 1.f, .5f);
    glVertex2f(CML_DEFAULT_INTEGRATION_MIN, viewOffset);
    glVertex2f(CML_DEFAULT_INTEGRATION_MAX, viewOffset);
    glVertex2f(CML_DEFAULT_INTEGRATION_MIN, viewOffset + viewRange);
    glVertex2f(CML_DEFAULT_INTEGRATION_MAX, viewOffset + viewRange);
  glEnd();

  // Draw the spectral distribution functions
  int32 intervals = (int32)((CML_DEFAULT_INTEGRATION_MAX - CML_DEFAULT_INTEGRATION_MIN) / CML_DEFAULT_INTEGRATION_STEPSIZE) + 1;
  const CMLFunction* specDistFuncs[3] = {
    cmlGetSpecDistFunction(cm, 0),
    cmlGetSpecDistFunction(cm, 1),
    cmlGetSpecDistFunction(cm, 2),
  };

  glColor4f(1.f, .5f, .5f, 1.f);
  glBegin(GL_LINE_STRIP);
    for(int32 iStep = 0; iStep <= intervals; iStep++){
      float lambda = CML_DEFAULT_INTEGRATION_MIN + (((CML_DEFAULT_INTEGRATION_MAX - CML_DEFAULT_INTEGRATION_MIN) * iStep) / intervals);
      float y = cmlEval(specDistFuncs[0], lambda);
      glVertex2f(lambda, viewOffset + y * viewRange);
    }
  glEnd();

  glColor4f(.5f, 1.f, .5f, 1.f);
  glBegin(GL_LINE_STRIP);
    for(int32 iStep = 0; iStep <= intervals; iStep++){
      float lambda = CML_DEFAULT_INTEGRATION_MIN + (((CML_DEFAULT_INTEGRATION_MAX - CML_DEFAULT_INTEGRATION_MIN) * iStep) / intervals);
      float y = cmlEval(specDistFuncs[1], lambda);
      glVertex2f(lambda, viewOffset + y * viewRange);
    }
  glEnd();

  glColor4f(.5f, .5f, 1.f, 1.f);
  glBegin(GL_LINE_STRIP);
    for(int32 iStep = 0; iStep <= intervals; iStep++){
      float lambda = CML_DEFAULT_INTEGRATION_MIN + (((CML_DEFAULT_INTEGRATION_MAX - CML_DEFAULT_INTEGRATION_MIN) * iStep) / intervals);
      float y = cmlEval(specDistFuncs[2], lambda);
      glVertex2f(lambda, viewOffset + y * viewRange);
    }
  glEnd();

  // Draw the illumination
  CMLIntegration integration = cmlMakeDefaultIntegration();
  const CMLFunction* illuminationSpectrum = cmlGetIlluminationSpectrum(cm);
  if(illuminationSpectrum){
    float illuminationMax = cmlGetFunctionMaxValue(illuminationSpectrum, &integration);
    glColor4f(1.f, 1.f, 1.f, 1.f);
    glBegin(GL_LINE_STRIP);
      for(int32 iStep = 0; iStep <= intervals; iStep++){
        float lambda = CML_DEFAULT_INTEGRATION_MIN + (((CML_DEFAULT_INTEGRATION_MAX - CML_DEFAULT_INTEGRATION_MIN) * iStep) / intervals);
        float y = cmlEval(illuminationSpectrum, lambda);
        glVertex2f(lambda, viewOffset + y / illuminationMax * viewRange);
      }
    glEnd();
  }

  // Draw the color
  if(cpGetColorControllerColorType(well->colorController) == CML_COLOR_SPECTRUM_ILLUMINATION){
    const CMLFunction* colorSpectrum = (const CMLFunction*)cpGetColorControllerColorData(well->colorController);
    if(colorSpectrum){
      float colorMax = cmlGetFunctionMaxValue(colorSpectrum, &integration);
      glColor4f(1.f, 1.f, .5f, 1.f);
      CMLDefinitionRange colorDefRange;
      cmlGetFunctionDefinitionRange(colorSpectrum, &colorDefRange);
      // In case this is a continuous function, set the stepSize to the default.
      if(colorDefRange.stepSize == 0.f){colorDefRange.stepSize = CML_DEFAULT_INTEGRATION_STEPSIZE;}
      size_t sampleCount = cmlGetSampleCount(colorDefRange.minSampleCoord, colorDefRange.maxSampleCoord, colorDefRange.stepSize);
      if(sampleCount == 1){
        glBegin(GL_LINES);
          float lambda = colorDefRange.minSampleCoord;
          float y = cmlEval(colorSpectrum, lambda);
          glVertex2f(lambda, viewOffset);
          glVertex2f(lambda, viewOffset + (y / colorMax) * viewRange);
        glEnd();
      }else{
        glBegin(GL_LINE_STRIP);
          for(int32 iStep = 0; iStep <= intervals; iStep++){
            float lambda = CML_DEFAULT_INTEGRATION_MIN + (((CML_DEFAULT_INTEGRATION_MAX - CML_DEFAULT_INTEGRATION_MIN) * iStep) / intervals);
            float y = cmlEval(colorSpectrum, lambda);
            glVertex2f(lambda, viewOffset + y / colorMax * viewRange);
          }
        glEnd();
      }
    }
  }

  glMatrixMode(GL_PROJECTION);
  glPopMatrix();

  naSwapOpenGLSpaceBuffer(well->openGLSpace);

  return NA_TRUE;
}



CPSpectralColorWell* cmAllocSpectralColorWell(CPColorController* colorController){
  CPSpectralColorWell* well = naAlloc(CPSpectralColorWell);
  
  well->openGLSpace = naNewOpenGLSpace(naMakeSize(spectralWellSize, colorWell2DSize), cmInitSpectralColorWell, well);
  naAddUIReaction(well->openGLSpace, NA_UI_COMMAND_REDRAW, cmDrawSpectralColorWell, well);
  naAddUIReaction(well->openGLSpace, NA_UI_COMMAND_MOUSE_DOWN, cmDragSpectralColorWell, well);
  naAddUIReaction(well->openGLSpace, NA_UI_COMMAND_MOUSE_MOVED, cmDragSpectralColorWell, well);
  
  well->colorController = colorController;
  
  return well;
}



void cmDeallocSpectralColorWell(CPSpectralColorWell* well){
  glDeleteTextures(1, &(well->wellTex));
}



NAOpenGLSpace* cmGetSpectralColorWellUIElement(CPSpectralColorWell* well){
  return well->openGLSpace;
}



void cmUpdateSpectralColorWell(CPSpectralColorWell* well){
  naRefreshUIElement(well->openGLSpace, 0.);
}
