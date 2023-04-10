
#include "CMColorWell1D.h"
#include "CMOpenGLHelper.h"

#include "../../CMColorMachineApplication.h"
#include "../../CMDesign.h"
#include "../CMColorController.h"

#include "NAApp.h"
#include "NAMath/NAVectorAlgebra.h"



struct CMColorWell1D{
  NAOpenGLSpace* display;
  
  GLuint wellTex;
  
  CMColorController* colorController;
  const void* colorData;
  size_t variableIndex;
};



void cmInitColorWell1D(void* data){
  CMColorWell1D* well = (CMColorWell1D*)data;
  glEnable(GL_LINE_SMOOTH);
  glEnable(GL_BLEND);
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

  glGenTextures(1, &(well->wellTex));
  glBindTexture(GL_TEXTURE_1D, well->wellTex);
  glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);
  glTexParameteri(GL_TEXTURE_1D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
  glTexParameteri(GL_TEXTURE_1D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
}



NABool cmDragColorWell1D(NAReaction reaction){
  CMColorWell1D* well = (CMColorWell1D*)reaction.controller;
 
  const NAMouseStatus* mouseStatus = naGetMouseStatus();
  if(mouseStatus->leftPressed){
    CMLColorMachine* cm = cmGetCurrentColorMachine();

    CMLColorType colorType = cmGetColorControllerColorType(well->colorController);
    CMLNormedConverter outputConverter = cmlGetNormedOutputConverter(colorType);
    CMLNormedConverter inputConverter = cmlGetNormedInputConverter(colorType);
    CMLColorMutator clamper = cmlGetClamper(colorType);

    CMLVec3 normedColorValues = {0.f, 0.f, 0.f};
    outputConverter(normedColorValues, well->colorData, 1);

    NARect displayRect = naGetUIElementRectAbsolute(well->display);
    float mouseX = (float)((mouseStatus->pos.x - displayRect.pos.x) / displayRect.size.width);
    if(mouseX < 0.f){mouseX = 0.f;}
    if(mouseX > 1.f){mouseX = 1.f;}

    switch(well->variableIndex){
    case 0:
      normedColorValues[0] = mouseX;
      break;
    case 1:
      normedColorValues[1] = mouseX;
      break;
    case 2:
      normedColorValues[2] = mouseX;
      break;
    }
    
    CMLVec3 newColorValues = {0.f, 0.f, 0.f};
    inputConverter(newColorValues, normedColorValues, 1);
    clamper(newColorValues, 1);
    
    CMLColorConverter converter = cmlGetColorConverter(
      cmGetColorControllerColorType(well->colorController),
      colorType);
    CMLVec3 convertedColorValues = {0.f, 0.f, 0.f};
    converter(cm, convertedColorValues, newColorValues, 1);

    cmSetColorControllerColorData(well->colorController, convertedColorValues);
    cmSetCurrentColorController(well->colorController);
    cmUpdateColor();
    return NA_TRUE;
  }

  return NA_FALSE;
}



NABool cmDrawColorWell1D(NAReaction reaction){
  CMColorWell1D* well = (CMColorWell1D*)reaction.controller;
  CMLColorMachine* cm = cmGetCurrentColorMachine();
  CMLColorMachine* sm = cmGetCurrentScreenMachine();

  double uiScale = naGetUIElementResolutionFactor(NA_NULL);
  NASize viewSize = naGetUIElementRect(reaction.uiElement).size;
  glViewport(
    0,
    0,
    (GLsizei)(viewSize.width * uiScale),
    (GLsizei)(viewSize.height * uiScale));

  glClear(GL_DEPTH_BUFFER_BIT);

  CMLColorType colorType = cmGetColorControllerColorType(well->colorController);
  CMLNormedConverter outputConverter = cmlGetNormedOutputConverter(colorType);
  CMLNormedConverter inputConverter = cmlGetNormedInputConverter(colorType);

  float inputValues[colorWell1DSize * 3] = {0};
  float* inputPtr = inputValues;
  CMLVec3 normedColorValues = {0.f, 0.f, 0.f};
  outputConverter(normedColorValues, well->colorData, 1);
  
  float variableValue;
  
  switch(cmlGetNumChannels(colorType)){
  case 1:
      for(int x = 0; x < colorWell1DSize; ++x){
        variableValue = normedColorValues[0];
        float xValue = (float)x / (float)colorWell1DSize;
        *inputPtr++ = xValue;
      }
    break;

  case 3:
    switch(well->variableIndex){
    case 0:
      for(int x = 0; x < colorWell1DSize; ++x){
        variableValue = normedColorValues[0];
        float xValue = (float)x / (float)colorWell1DSize;
        *inputPtr++ = xValue;
        *inputPtr++ = normedColorValues[1];
        *inputPtr++ = normedColorValues[2];
      }
      break;
    case 1:
      for(int x = 0; x < colorWell1DSize; ++x){
        variableValue = normedColorValues[1];
        float xValue = (float)x / (float)colorWell1DSize;
        *inputPtr++ = normedColorValues[0];
        *inputPtr++ = xValue;
        *inputPtr++ = normedColorValues[2];
      }
      break;
    case 2:
      for(int x = 0; x < colorWell1DSize; ++x){
        variableValue = normedColorValues[2];
        float xValue = (float)x / (float)colorWell1DSize;
        *inputPtr++ = normedColorValues[0];
        *inputPtr++ = normedColorValues[1];
        *inputPtr++ = xValue;
      }
      break;
    }
    break;
  }

  // Convert the given values to screen RGBs.
  float rgbValues[colorWell1DSize * 3];
  fillRGBFloatArrayWithArray(
    cm,
    sm,
    rgbValues,
    inputValues,
    colorType,
    inputConverter,
    colorWell1DSize);

  glTexImage1D(GL_TEXTURE_1D, 0, GL_RGBA, colorWell1DSize, 0, GL_RGB, GL_FLOAT, rgbValues);

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

  const float whiteR = 2.f * 4.f / (float)colorWell1DSize;
  const float blackR = 2.f * 5.f / (float)colorWell1DSize;
  const int subdivisions = 16;
  const float yDivisor = colorWell1DSize / (float)colorWell1DHeight;

  glDisable(GL_TEXTURE_1D);
  glDisable(GL_DEPTH);

  glLineWidth(1);
  glColor4f(1., 1., 1., 1.);
  glBegin(GL_LINE_LOOP);
    for(int i = 0; i < subdivisions; ++i){
      float ang = NA_PI2f * (float)i / (float)subdivisions;
      glVertex2d(variableValue * 2. - 1. + whiteR * naCos(ang), whiteR * naSin(ang) * yDivisor);
    }
  glEnd();

  glColor4f(0., 0., 0., 1.);
  glBegin(GL_LINE_LOOP);
    for(int i = 0; i < subdivisions; ++i){
      float ang = NA_PI2f * (float)i / (float)subdivisions;
      glVertex2d(variableValue * 2. - 1. + blackR * naCos(ang), blackR * naSin(ang) * yDivisor);
    }
  glEnd();

  cmDrawBorder();

  naSwapOpenGLSpaceBuffer(well->display);

  return NA_TRUE;
}



CMColorWell1D* cmAllocColorWell1D(CMColorController* colorController, const float* colorData, size_t variableIndex){
  CMColorWell1D* well = naAlloc(CMColorWell1D);
  
  well->display = naNewOpenGLSpace(naMakeSize(colorWell1DSize, colorWell1DHeight), cmInitColorWell1D, well);
  naAddUIReaction(well->display, NA_UI_COMMAND_REDRAW, cmDrawColorWell1D, well);
  naAddUIReaction(well->display, NA_UI_COMMAND_MOUSE_DOWN, cmDragColorWell1D, well);
  naAddUIReaction(well->display, NA_UI_COMMAND_MOUSE_MOVED, cmDragColorWell1D, well);
  
  well->colorController = colorController;
  well->colorData = colorData;
  well->variableIndex = variableIndex;
  
  return well;
}



void cmDeallocColorWell1D(CMColorWell1D* well){
  glDeleteTextures(1, &(well->wellTex));
}



NAOpenGLSpace* cmGetColorWell1DUIElement(CMColorWell1D* well){
  return well->display;
}



void cmUpdateColorWell1D(CMColorWell1D* well){
  naRefreshUIElement(well->display, 0.);
}
