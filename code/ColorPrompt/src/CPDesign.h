
#ifndef CP_DESIGN_INCLUDED
#define CP_DESIGN_INCLUDED


#include "NAApp/NAApp.h"
#include "NAMath/NACoord.h"

#define uiElemHeight 25.

#define spaceMarginLeft 15.
#define spaceMarginRight 15.
#define spaceMarginBottom 15.
#define spaceMarginTop 15.
static const NABezel4 spaceBezel = {
  spaceMarginRight,
  spaceMarginTop,
  spaceMarginLeft,
  spaceMarginBottom};
#define spaceMarginV (spaceMarginTop + spaceMarginBottom)

#define marginH 15.

#define initial3DDisplayWidth 500.

#define radioSelectWidth 55.
#define labelValueWidth 60.
#define textFieldValueWidth 65.
#define threeValueHeight 55.
#define threeValueHeightMargin 10.
#define spaceMarginLeft3D 10.
static const NABezel4 threeDeeBezel = {
  spaceMarginRight,
  spaceMarginTop,
  spaceMarginLeft3D,
  spaceMarginBottom};

#define threeDeeRotationLabelWidth 55.
#define threeDeeLabelWidth 110.
#define threeDeeControlWidth 140.

#define degreeWidth 35
#define spaceMarginDegreeLeft (spaceMarginLeft + degreeWidth)

#define indexWidth 25.
#define twoColorWidth 150.
#define twoColorHeight 21.

#define indexMargin 0.
#define valueMargin 10.

static const float greyColor[3] = {.5f, .5f, .5f};

#define machineLabelWidth 120.

#define setButtonWidth 40.
#define colorValueCondensedRowHeight 25.
#define gammaDisplaySize 50
#define colorWell2DRightMargin 2.
#define colorWell2DSize 125
#define colorWell1DSize 125
#define spectralWellSize 355
#define colorWell1DMarginLeft 210
#define colorWell1DHeight 15.
#define colorWell1DOffset 5.
#define colorComponentWidth 25.
#define colorComponentMarginH 3.
#define radioChannelOffset 2.
#define radioChannelCenteringOffset 15.
static const NABezel4 colorWellBezel = {10, 10, 10, 10};

void cpStartupDesign(void);
void cpShutdownDesign(void);

NALabel* cpNewTitleLabel(
  const NAUTF8Char* text,
  double width);
NALabel* cpNewValueLabel(void);
NALabel* cpNewColorComponentLabel(const NAUTF8Char* string);
NALabel* cpNewThreeValueLabel(void);
NATextField* cpNewValueTextField(NAReactionHandler reactionHandler, void* con);
NATextField* cpNewBigValueTextField(NAReactionHandler reactionHandler, void* con);

// Before constructing a UI layout, you need to define within which NASpace you
// want the layout to be in. Use cpBeginUILayout for that.
//
// You construct a UI by creating rows containing childs. You start a new row
// with cpAddUIRow which adds a child to the left. After having started a row,
// you can add more childs to that row with cpAddUICol, each with a margin to
// the previous child on the left.
//
// If you need a special shift to the right or to the bottom, use naAddUIPos.
//
// The rowHeight parameter of cpAddUIRow can be either zero or non-zero:
// 
// If it is a zero value, the height of the whole row will be determined by
// the maximum height of all childs and all childs are added to the upper
// boundary. This is very useful when having sub-spaces which should all
// align on the top.
//
// If the valid is non-zero, the row is defined to have that fixed height and
// all childs are added to the lower boundary, no matter if they overlap the
// upper boundary. This is useful for basic UI elements which should all be
// aligned properly within one row. The default row height for all standard
// UI elements is 25.
//
// Height 0:
// O--+-----+---+-----+---+-----+--  \
//    |     |   |     |   |     |     \
//    |     |   |     |   +-----+      \
//    |     |   |     |                 } max height
//    +-----+   |     |                /
//              |     |               /
// -------------+-----+------------  /
//
// Height non-0:
//              +-----+        
//              |     |        
// O--+-----+---|- - -|------------  \
//    |     |   |     |               \
//    |     |   |     |   +-----+      } heigth
//    |     |   |     |   |     |     /
// ---+-----+---+-----+---+-----+--  /
//
// These few functions allow for the most basic cases of a UI design. If you
// need to place UIElements on more specialized places, you can always use
// naAddSpaceChild and set the coordinates manually.

void cpBeginUILayout(NASpace* space, NABezel4 margin);
void cpAddUIPos(double x, double y);
void cpAddUIRow(void* child, double rowHeight);
void cpAddUIRowH(void* child, double rowHeight, double hOffset);
void cpAddUICol(void* child, double marginLeft);
void cpAddUIColV(void* child, double marginLeft, double vOffset);
void cpEndUILayout(void);

#endif // CP_DESIGN_INCLUDED
