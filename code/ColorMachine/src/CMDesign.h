
#ifndef CM_DESIGN_INCLUDED
#define CM_DESIGN_INCLUDED

#ifdef __cplusplus
  extern "C"{
#endif



#include "NAApp.h"

static const double uiElemHeight = 25.;

static const double spaceMarginLeft = 15.;
static const double spaceMarginRight = 15.;
static const double spaceMarginBottom = 15.;
static const double spaceMarginTop = spaceMarginBottom - 3.;
static const double spaceMarginV = spaceMarginTop + spaceMarginBottom;

static const double marginH = 15.;

static const double valueWidth = 60.;
static const double threeValueHeight = 55.;
static const double threeValueMargin = threeValueHeight + 10.;

static const double degreeWidth = 35;
static const double spaceMarginDegreeLeft = spaceMarginLeft + degreeWidth;

static const double indexWidth = 30.;
static const double twoColorWidth = 150.;



void cmStartupDesign(void);
void cmShutdownDesign(void);

NALabel* cmNewTitleLabel(
  const NAUTF8Char* text,
  double width);
NALabel* cmNewValueLabel(void);
NALabel* cmNewThreeValueLabel(void);



#ifdef __cplusplus
  }
#endif

#endif // CM_DESIGN_INCLUDED
