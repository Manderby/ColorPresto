
#ifndef CP_DESIGN_INCLUDED
#define CP_DESIGN_INCLUDED


#include "NAApp/NAApp.h"
#include "NAMath/NACoord.h"

#define uiElemHeight 25.

#define spaceMarginLeft 16.
#define spaceMarginRight 16.
#define spaceMarginBottom 16.
#define spaceMarginTop 16.
#define spaceInterMargin 8.

static const NABorder2D spaceBorder = {
  spaceMarginLeft,
  spaceMarginRight,
  spaceMarginBottom,
  spaceMarginTop};
#define spaceMarginV (spaceMarginTop + spaceMarginBottom)

#define marginH 15.
#define marginHSmall 5.

#define initial3DDisplayWidth 500.

#define radioSelectWidth 55.
#define labelValueWidth 60.
#define textFieldValueWidth 65.
#define threeValueHeight 55.
#define threeValueHeightMargin 10.
#define spaceMarginLeft3D 10.
static const NABorder2D threeDeeBorder = {
  spaceMarginLeft3D,
  spaceMarginRight,
  spaceMarginBottom,
  spaceMarginTop};

#define threeDeeLabelWidth 130.
#define threeDeeControlWidth 140.

#define degreeWidth 35
#define spaceMarginDegreeLeft (spaceMarginLeft + degreeWidth)

#define indexWidth 25.
#define twoColorWidth 150.
#define twoColorHeight 21.

#define indexMargin 0.
#define valueMargin 10.

static const float greyColor[3] = {.5f, .5f, .5f};

#define machineLabelWidth 160.

#define setButtonWidth 60.
#define setBigButtonWidth 110.
#define colorValueCondensedRowHeight 25.
#define gammaDisplaySize 50
#define colorWell2DRightMargin 2.
#define colorWell2DSize 125
#define colorWell1DSize 125
#define spectralWellSize 355
#define colorWell1DMarginLeft 210
#define colorWell1DHeight 15.
#define colorWell1DOffset 5.
#define colorComponentWidth 28.
#define colorComponentMarginH 3.
#define radioChannelOffset 2.
#define radioChannelCenteringOffset 15.
static const NABorder2D colorWellBorder = {10, 10, 10, 10};

void cpStartupDesign(void);
void cpShutdownDesign(void);

NALabel* cpNewTitleLabel(
  const NAUTF8Char* text,
  double width);
NALabel* cpNewValueLabel(void);
NALabel* cpNewColorComponentLabel(const NAUTF8Char* string);
NALabel* cpNewThreeValueLabel(void);
NATextField* cpNewValueTextField(NAReactionCallback reactionCallback, void* con);
NATextField* cpNewBigValueTextField(NAReactionCallback reactionCallback, void* con);

#endif // CP_DESIGN_INCLUDED
