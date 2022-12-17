
#include "CMGrayColorWell.h"

#include "../../CMColorMachineApplication.h"
#include "../../CMDesign.h"
#include "../CMColorController.h"

#include "NAApp.h"



struct CMGrayColorWell{
  NAOpenGLSpace* display;
  NAInt fontId;

  CMColorController* colorController;
};



void cmInitGrayColorWell(void* data){
  CMGrayColorWell* well = (CMGrayColorWell*)data;
  well->fontId = naStartupPixelFont();
  glEnable(GL_BLEND);
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}



NABool cmDrawGrayColorWell(NAReaction reaction){
  CMGrayColorWell* well = (CMGrayColorWell*)reaction.controller;
  CMLColorMachine* cm = cmGetCurrentColorMachine();
  CMLColorMachine* sm = cmGetCurrentScreenMachine();

  NASize viewSize = naGetUIElementRect(well->display, NA_NULL, NA_FALSE).size;
  glViewport(0, 0, (GLsizei)viewSize.width, (GLsizei)viewSize.height);

  glClear(GL_DEPTH_BUFFER_BIT);

  CMLNormedConverter rgbInputConverter = cmlGetNormedInputConverter(CML_COLOR_RGB);
  CMLNormedConverter rgbOutputConverter = cmlGetNormedOutputConverter(CML_COLOR_RGB);

  CMLColorType colorType = cmGetCurrentColorType();
  CMLColorConverter colorConverter = cmlGetColorConverter(CML_COLOR_RGB, colorType);
  const void* color = cmGetCurrentColorData();
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
  const void* gray = cmGetColorControllerColorData(well->colorController);
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

  NARect rect = naGetUIElementRect(well->display, NA_NULL, NA_FALSE);
  glMatrixMode(GL_PROJECTION);
  glPushMatrix();
  glLoadIdentity();
  glOrtho(0, rect.size.width, 0, rect.size.height, -1., 1.);

  glColor3f(0., 0., 0.);
  naDrawASCIICharacters(well->fontId, "Color", 12, 85, 0);
  naDrawASCIICharacters(well->fontId, "Gray", 65, 85, 0);
  glColor3f(1., 1., 1.);
  naDrawASCIICharacters(well->fontId, "Color", 11, 86, 0);
  naDrawASCIICharacters(well->fontId, "Gray", 64, 86, 0);

  glMatrixMode(GL_PROJECTION);
  glPopMatrix();

  naSwapOpenGLSpaceBuffer(well->display);

  return NA_TRUE;
}



CMGrayColorWell* cmAllocGrayColorWell(CMColorController* colorController){
  CMGrayColorWell* well = naAlloc(CMGrayColorWell);
  
  well->display = naNewOpenGLSpace(naMakeSize(colorWell2DSize, colorWell2DSize), cmInitGrayColorWell, well);
  naAddUIReaction(well->display, NA_UI_COMMAND_REDRAW, cmDrawGrayColorWell, well);
  
  well->colorController = colorController;
  
  return well;
}



void cmDeallocGrayColorWell(CMGrayColorWell* well){
  naShutdownPixelFont(well->fontId);
}



NAOpenGLSpace* cmGetGrayColorWellUIElement(CMGrayColorWell* well){
  return well->display;
}



void cmUpdateGrayColorWell(CMGrayColorWell* well){
  naRefreshUIElement(well->display, 0.);
}
