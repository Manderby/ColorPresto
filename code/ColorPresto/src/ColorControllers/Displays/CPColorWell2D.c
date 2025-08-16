
#include "CPColorWell2D.h"

#include "../../CPColorPrestoApplication.h"
#include "../../CPDesign.h"
#include "../../CPOpenGLHelper.h"
#include "../CPColorController.h"

#include "NAApp/NAApp.h"
#include "NAMath/NAVectorAlgebra.h"



struct CPColorWell2D{
  NAOpenGLSpace* display;
  
  GLuint wellTex;
  
  CPColorController* colorController;
  size_t fixedIndex;

  float* inputValues;
  float* rgbValues;
};



void cmInitColorWell2D(void* data){
  CPColorWell2D* well = (CPColorWell2D*)data;
  glEnable(GL_LINE_SMOOTH);
  glEnable(GL_BLEND);
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

  glGenTextures(1, &(well->wellTex));
  glBindTexture(GL_TEXTURE_2D, well->wellTex);
  glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
}



void cmDragColorWell2D(NAReaction reaction){
  CPColorWell2D* well = (CPColorWell2D*)reaction.controller;
 
  const NAMouseStatus* mouseStatus = naGetCurrentMouseStatus();
  if(naGetMouseButtonPressed(mouseStatus, NA_MOUSE_BUTTON_LEFT)){
    CMLColorType colorType = cpGetColorControllerColorType(well->colorController);
    CMLNormedConverter outputConverter = cmlGetNormedCartesianOutputConverter(colorType);
    CMLNormedConverter inputConverter = cmlGetNormedCartesianInputConverter(colorType);
    CMLColorMutator clamper = cmlGetClamper(colorType);

    CMLVec3 normedColorValues = {0.f, 0.f, 0.f};
    outputConverter(normedColorValues, cpGetColorControllerColorData(well->colorController), 1);

    NARect displayRect = naGetUIElementRectAbsolute(well->display);
    NAPos mousePos = naGetMousePos(mouseStatus);
    switch(well->fixedIndex){
    case 0:
      normedColorValues[1] = (float)((mousePos.x - displayRect.pos.x) / displayRect.size.width);
      normedColorValues[2] = (float)((mousePos.y - displayRect.pos.y) / displayRect.size.height);
      break;
    case 1:
      normedColorValues[0] = (float)((mousePos.x - displayRect.pos.x) / displayRect.size.width);
      normedColorValues[2] = (float)((mousePos.y - displayRect.pos.y) / displayRect.size.height);
      break;
    case 2:
      normedColorValues[0] = (float)((mousePos.x - displayRect.pos.x) / displayRect.size.width);
      normedColorValues[1] = (float)((mousePos.y - displayRect.pos.y) / displayRect.size.height);
      break;
    }

    CMLVec3 newColorValues = {0.f, 0.f, 0.f};
    inputConverter(newColorValues, normedColorValues, 1);
    clamper(newColorValues, 1);
    
    cpSetColorControllerColorData(well->colorController, newColorValues);
    cpSetCurrentColorController(well->colorController);
    cpUpdateColor();
  }
}



void cmDrawColorWell2D(NAReaction reaction){
  CPColorWell2D* well = (CPColorWell2D*)reaction.controller;
  CMLColorMachine* cm = cpGetCurrentColorMachine();

  double uiScale = naGetUIElementUIScale(well->display);
  NASize viewSize = naGetUIElementRect(reaction.uiElement).size;
  glViewport(
    0,
    0,
    (GLsizei)(viewSize.width * uiScale),
    (GLsizei)(viewSize.height * uiScale));

  glClear(GL_DEPTH_BUFFER_BIT);

  CMLColorType colorType = cpGetColorControllerColorType(well->colorController);
  CMLNormedConverter outputConverter = cmlGetNormedCartesianOutputConverter(colorType);

  float fixedValueA = 0.f;
  float fixedValueB = 0.f;
  CMLVec3 normedColorValues = { 0.f, 0.f, 0.f };
  outputConverter(normedColorValues, cpGetColorControllerColorData(well->colorController), 1);

  switch (well->fixedIndex) {
  case 0:
    fixedValueA = normedColorValues[1];
    fixedValueB = normedColorValues[2];
    break;
  case 1:
    fixedValueA = normedColorValues[0];
    fixedValueB = normedColorValues[2];
    break;
  case 2:
    fixedValueA = normedColorValues[0];
    fixedValueB = normedColorValues[1];
    break;
  }

  glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, colorWell2DSize, colorWell2DSize, 0, GL_RGB, GL_FLOAT, well->rgbValues);

  glEnable(GL_TEXTURE_2D);
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

  const float whiteR = 2.f * 4.f / (float)colorWell2DSize;
  const float blackR = 2.f * 5.f / (float)colorWell2DSize;
  const int subdivisions = 16;

  glDisable(GL_TEXTURE_2D);
  glDisable(GL_DEPTH);

  // Draw the spectrum
  if((colorType == CML_COLOR_Yupvp) || (colorType == CML_COLOR_Yxy)){
    glLineWidth(1);
    float imin = CML_DEFAULT_INTEGRATION_MIN;
    float imax = CML_DEFAULT_INTEGRATION_MAX;
    int32 intervals = (int32)((imax - imin) / CML_DEFAULT_INTEGRATION_STEPSIZE) + 1;
    
    CMLColorConverter coordConverter = cmlGetColorConverter(colorType, CML_COLOR_XYZ);
    CMLNormedConverter normedConverter = cmlGetNormedOutputConverter(colorType);

    glLineWidth(uiScale);
    glBegin(GL_LINE_STRIP);
    for(int32 iStep = 0; iStep <= intervals; iStep++){
      float l = imin + (((imax - imin) * iStep) / intervals);
      CMLVec3 curXYZ;
      cmlGetSpectralXYZColor(cm, curXYZ, l);
      if(curXYZ[1] > 0.f){

        CMLVec3 curRGB = {0.f, 0.f, 0.f};
        CMLVec3 curcoords = {0.f, 0.f, 0.f};
        CMLVec3 curNormedCoords = {0.f, 0.f, 0.f};
        coordConverter(cm, curcoords, curXYZ, 1);
        normedConverter(curNormedCoords, curcoords, 1);
        cmlXYZToRGB(cm, curRGB, curXYZ, 1);
        cmlMul3(curRGB, .7f);
        cmlClampRGB(curRGB, 1);
        cmlMul3(curRGB, .75f);
        glColor3fv(curRGB);

        switch(well->fixedIndex){
        case 0:
          glVertex2d(curNormedCoords[1] * 2. - 1., curNormedCoords[2] * 2. - 1.);
          break;
        case 1:
          glVertex2d(curNormedCoords[0] * 2. - 1., curNormedCoords[2] * 2. - 1.);
          break;
        case 2:
          glVertex2d(curNormedCoords[0] * 2. - 1., curNormedCoords[1] * 2. - 1.);
          break;
        }
      }
    }
    glEnd();
  }

  glLineWidth(uiScale);
  glBegin(GL_LINE_LOOP);
    glColor4f(1., 1., 1., 1.);
    for(int i = 0; i < subdivisions; ++i){
      float ang = NA_PI2f * (float)i / (float)subdivisions;
      glVertex2d(fixedValueA * 2. - 1. + whiteR * naCos(ang), fixedValueB * 2. - 1. + whiteR * naSin(ang));
    }
  glEnd();
  glLineWidth(uiScale);
  glBegin(GL_LINE_LOOP);
    glColor4f(0., 0., 0., 1.);
    for(int i = 0; i < subdivisions; ++i){
      float ang = NA_PI2f * (float)i / (float)subdivisions;
      glVertex2d(fixedValueA * 2. - 1. + blackR * naCos(ang), fixedValueB * 2. - 1. + blackR * naSin(ang));
    }
  glEnd();

  cpDrawBorder(uiScale);

  naSwapOpenGLSpaceBuffer(well->display);
}



CPColorWell2D* cpAllocColorWell2D(CPColorController* colorController, size_t fixedIndex){
  CPColorWell2D* well = naAlloc(CPColorWell2D);
  
  well->display = naNewOpenGLSpace(naMakeSize(colorWell2DSize, colorWell2DSize), cmInitColorWell2D, well);
  naAddUIReaction(well->display, NA_UI_COMMAND_REDRAW, cmDrawColorWell2D, well);
  naAddUIReaction(well->display, NA_UI_COMMAND_MOUSE_DOWN, cmDragColorWell2D, well);
  naAddUIReaction(well->display, NA_UI_COMMAND_MOUSE_MOVED, cmDragColorWell2D, well);
  
  well->colorController = colorController;
  well->fixedIndex = fixedIndex;

  well->inputValues = naMalloc(colorWell2DSize * colorWell2DSize * 3 * sizeof(float));
  well->rgbValues = naMalloc(colorWell2DSize * colorWell2DSize * 3 * sizeof(float));

  return well;
}



void cpDeallocColorWell2D(CPColorWell2D* well){
  naFree(well->inputValues);
  naFree(well->rgbValues);
  glDeleteTextures(1, &(well->wellTex));
}



void cpSetColorWell2DFixedIndex(CPColorWell2D* well, size_t fixedIndex){
  well->fixedIndex = fixedIndex;
}



NAOpenGLSpace* cpGetColorWell2DUIElement(CPColorWell2D* well){
  return well->display;
}



void cpComputeColorWell2D(CPColorWell2D* well) {
  CMLColorMachine* cm = cpGetCurrentColorMachine();
  CMLColorMachine* sm = cpGetCurrentScreenMachine();
  CMLColorType colorType = cpGetColorControllerColorType(well->colorController);
  CMLNormedConverter outputConverter = cmlGetNormedCartesianOutputConverter(colorType);
  CMLNormedConverter inputConverter = cmlGetNormedCartesianInputConverter(colorType);

  float* inputPtr = well->inputValues;
  CMLVec3 normedColorValues = { 0.f, 0.f, 0.f };
  outputConverter(normedColorValues, cpGetColorControllerColorData(well->colorController), 1);

  switch (well->fixedIndex) {
  case 0:
    for (int y = 0; y < colorWell2DSize; ++y) {
      float yValue = (float)y / (float)colorWell2DSize;
      for (int x = 0; x < colorWell2DSize; ++x) {
        float xValue = (float)x / (float)colorWell2DSize;
        *inputPtr++ = normedColorValues[0];
        *inputPtr++ = xValue;
        *inputPtr++ = yValue;
      }
    }
    break;
  case 1:
    for (int y = 0; y < colorWell2DSize; ++y) {
      float yValue = (float)y / (float)colorWell2DSize;
      for (int x = 0; x < colorWell2DSize; ++x) {
        float xValue = (float)x / (float)colorWell2DSize;
        *inputPtr++ = xValue;
        *inputPtr++ = normedColorValues[1];
        *inputPtr++ = yValue;
      }
    }
    break;
  case 2:
    for (int y = 0; y < colorWell2DSize; ++y) {
      float yValue = (float)y / (float)colorWell2DSize;
      for (int x = 0; x < colorWell2DSize; ++x) {
        float xValue = (float)x / (float)colorWell2DSize;
        *inputPtr++ = xValue;
        *inputPtr++ = yValue;
        *inputPtr++ = normedColorValues[2];
      }
    }
    break;
  }

  // Convert the given values to screen RGBs.
  fillRGBFloatArrayWithArray(
    cm,
    sm,
    well->rgbValues,
    well->inputValues,
    colorType,
    inputConverter,
    colorWell2DSize * colorWell2DSize);
}



void cpUpdateColorWell2D(CPColorWell2D* well){
  naRefreshUIElement(well->display, 0.);
}
