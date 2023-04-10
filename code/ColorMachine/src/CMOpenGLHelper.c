
#include "CMOpenGLHelper.h"

#include "NAApp.h"

void cmDrawBorder(){
  NABabyColor borderColor;
  naFillDefaultTextColorWithSkin(borderColor, naGetSkinForCurrentAppearance());
  borderColor[3] = .1f;

  glLineWidth(2);
  glBegin(GL_LINE_STRIP);
  glColor4fv(borderColor);
  glVertex2d(-1., -1.);
  glVertex2d(-1., +1.);
  glVertex2d(+1., +1.);
  glVertex2d(+1., -1.);
  glVertex2d(-1., -1.);
  glEnd();
}
