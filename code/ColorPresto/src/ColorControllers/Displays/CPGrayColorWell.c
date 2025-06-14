
#include "CPGrayColorWell.h"

#include "../../CPColorPrestoApplication.h"
#include "../../CPDesign.h"
#include "../../CPOpenGLHelper.h"
#include "../../CPTranslations.h"
#include "../CPColorController.h"

#include "NAApp/NAApp.h"
#include "NAUtility/NAMemory.h"



struct CPGrayColorWell{
  NAOpenGLSpace* display;
  int64 fontId;

  CPColorController* colorController;
};



void cmInitGrayColorWell(void* data){
  CPGrayColorWell* well = (CPGrayColorWell*)data;
  well->fontId = naStartupPixelFont();
  glEnable(GL_BLEND);
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}



void cmDrawGrayColorWell(NAReaction reaction){
  CPGrayColorWell* well = (CPGrayColorWell*)reaction.controller;
  CMLColorMachine* cm = cpGetCurrentColorMachine();
  CMLColorMachine* sm = cpGetCurrentScreenMachine();

  double uiScale = naGetUIElementResolutionScale(well->display);
  NASize viewSize = naGetUIElementRect(reaction.uiElement).size;
  glViewport(
    0,
    0,
    (GLsizei)(viewSize.width * uiScale),
    (GLsizei)(viewSize.height * uiScale));

  glClear(GL_DEPTH_BUFFER_BIT);

  CMLNormedConverter rgbInputConverter = cmlGetNormedInputConverter(CML_COLOR_RGB);
  CMLNormedConverter rgbOutputConverter = cmlGetNormedOutputConverter(CML_COLOR_RGB);

  CMLColorType colorType = cpGetCurrentColorType();
  CMLColorConverter colorConverter = cmlGetColorConverter(CML_COLOR_RGB, colorType);
  const void* color = cpGetCurrentColorData();
  float originalColorRGB[3] = {0.f, 0.f, 0.f};
  colorConverter(cm, originalColorRGB, color, 1);
  float normedColorRGB[3] = {0.f, 0.f, 0.f};
  rgbOutputConverter(normedColorRGB, originalColorRGB, 1);
  
  float colorRGB[3];
  fillRGBFloatArrayWithArray(
    cm,
    sm,
    colorRGB,
    normedColorRGB,
    CML_COLOR_RGB,
    rgbInputConverter,
    1);

  CMLColorConverter grayConverter = cmlGetColorConverter(CML_COLOR_RGB, CML_COLOR_Gray);
  const void* gray = cpGetColorControllerColorData(well->colorController);
  float originalGrayRGB[3] = {0.f, 0.f, 0.f};
  grayConverter(cm, originalGrayRGB, gray, 1);
  float normedGrayRGB[3] = {0.f, 0.f, 0.f};
  rgbOutputConverter(normedGrayRGB, originalGrayRGB, 1);
  
  float grayRGB[3];
  fillRGBFloatArrayWithArray(
    cm,
    sm,
    grayRGB,
    normedGrayRGB,
    CML_COLOR_RGB,
    rgbInputConverter,
    1);

  glBegin(GL_TRIANGLE_STRIP);
    glColor3fv(colorRGB);
    glVertex2f(-1., -1.);
    glVertex2f(-1., +1.);
    glVertex2f(+0., -1.);
    glVertex2f(+0., +1.);
    glColor3fv(grayRGB);
    glVertex2f(-0., -1.);
    glVertex2f(-0., +1.);
    glVertex2f(+1., -1.);
    glVertex2f(+1., +1.);
  glEnd();

  NARect rect = naGetUIElementRect(well->display);
  glMatrixMode(GL_PROJECTION);
  glPushMatrix();
  glLoadIdentity();
  glOrtho(0, rect.size.width, 0, rect.size.height, -1., 1.);

  int pixelwidth = 5 + 1;
  const NAUTF8Char* colorString = cpTranslate(CPGrayDisplayColor);
  const NAUTF8Char* grayString = cpTranslate(CPGrayDisplayGray);
  double leftPos = (int)(((colorWell2DSize / 2.) - strlen(colorString) * pixelwidth) / 2.);
  double rightPos = (int)((colorWell2DSize / 2.) + ((colorWell2DSize / 2.) - strlen(grayString) * pixelwidth) / 2.);
  glColor3f(0., 0., 0.);
  naDrawASCIICharacters(well->fontId, cpTranslate(CPGrayDisplayColor), leftPos, colorWell2DSize - 15, 0, uiScale);
  naDrawASCIICharacters(well->fontId, cpTranslate(CPGrayDisplayGray), rightPos, colorWell2DSize - 15, 0, uiScale);
  glColor3f(1., 1., 1.);
  naDrawASCIICharacters(well->fontId, cpTranslate(CPGrayDisplayColor), leftPos - 1, colorWell2DSize - 14, 0, uiScale);
  naDrawASCIICharacters(well->fontId, cpTranslate(CPGrayDisplayGray), rightPos - 1, colorWell2DSize - 14, 0, uiScale);

  glMatrixMode(GL_PROJECTION);
  glPopMatrix();

  cpDrawBorder();

  naSwapOpenGLSpaceBuffer(well->display);
}



CPGrayColorWell* cpAllocGrayColorWell(CPColorController* colorController){
  CPGrayColorWell* well = naAlloc(CPGrayColorWell);
  
  well->display = naNewOpenGLSpace(naMakeSize(colorWell2DSize, colorWell2DSize), cmInitGrayColorWell, well);
  naAddUIReaction(well->display, NA_UI_COMMAND_REDRAW, cmDrawGrayColorWell, well);
  
  well->colorController = colorController;
  
  return well;
}



void cpDeallocGrayColorWell(CPGrayColorWell* well){
  naShutdownPixelFont(well->fontId);
}



NAOpenGLSpace* cpGetGrayColorWellUIElement(CPGrayColorWell* well){
  return well->display;
}



void cpUpdateGrayColorWell(CPGrayColorWell* well){
  naRefreshUIElement(well->display, 0.);
}
