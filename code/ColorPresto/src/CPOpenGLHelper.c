
#include "CPOpenGLHelper.h"

#include "NAApp/NAApp.h"
#include "NAVisual/NAColor.h"

void cpDrawBorder(double uiScale){
  NAColor borderColor;
  naFillColorWithSkinTextColor(&borderColor, naGetCurrentSkin());
  borderColor.alpha = .1f;
  float glColor[4];
  naFillSRGBAWithColor(glColor, &borderColor);

  glLineWidth(2 * uiScale);
  glBegin(GL_LINE_STRIP);
  glColor4fv(glColor);
  glVertex2d(-1., -1.);
  glVertex2d(-1., +1.);
  glVertex2d(+1., +1.);
  glVertex2d(+1., -1.);
  glVertex2d(-1., -1.);
  glEnd();
}
