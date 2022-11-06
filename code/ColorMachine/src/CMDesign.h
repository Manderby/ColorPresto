
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
static const NABezel4 spaceBezel = {
  spaceMarginRight,
  spaceMarginTop,
  spaceMarginLeft,
  spaceMarginBottom};
static const double spaceMarginV = spaceMarginTop + spaceMarginBottom;

static const double marginH = 15.;

static const double initial3DDisplayWidth = 500.;

static const double labelValueWidth = 55.;
static const double textFieldValueWidth = 65.;
static const double threeValueHeight = 55.;
static const double threeValueHeightMargin = 10.;
static const double spaceMarginLeft3D = 10.;
static const NABezel4 threeDeeBezel = {
  spaceMarginRight,
  spaceMarginTop,
  spaceMarginLeft3D,
  spaceMarginBottom};

static const double degreeWidth = 35;
static const double spaceMarginDegreeLeft = spaceMarginLeft + degreeWidth;

static const double indexWidth = 25.;
static const double twoColorWidth = 150.;
static const double twoColorHeight = 21.;

static const double indexMargin = 0.;
static const double valueMargin = 10.;

static const float greyColor[3] = {.5f, .5f, .5f};

static const float colorValueCondensedRowHeight = 20.;
static const int colorWell2DSize = 100;
static const int colorWell1DSize = 100;
static const float colorWell1DMarginLeft = 210;
static const double colorWell1DHeight = 13.;
static const float colorComponentWidth = 25.;
static const float colorComponentMarginH = -5.;

void cmStartupDesign(void);
void cmShutdownDesign(void);

NALabel* cmNewTitleLabel(
  const NAUTF8Char* text,
  double width);
NALabel* cmNewValueLabel(void);
NALabel* cmNewColorComponentLabel(const NAUTF8Char* string);
NALabel* cmNewThreeValueLabel(void);
NATextField* cmNewValueTextBox(NAReactionHandler reactionHandler, void* con);
NATextField* cmNewBigValueTextBox(NAReactionHandler reactionHandler, void* con);

// Before constructing a UI layout, you need to define within which NASpace you
// want the layout to be in. Use cmBeginUILayout for that.
//
// You construct a UI by creating rows containing childs. You start a new row
// with cmAddUIRow which adds a child to the left. After having started a row,
// you can add more childs to that row with cmAddUICol, each with a margin to
// the previous child on the left.
//
// If you need a special shift to the right or to the bottom, use naAddUIPos.
//
// The rowHeight parameter of cmAddUIRow can be either zero or non-zero:
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

void cmBeginUILayout(NASpace* space, NABezel4 margin);
void cmAddUIPos(double x, double y);
void cmAddUIRow(void* child, double rowHeight);
void cmAddUICol(void* child, double marginLeft);
void cmEndUILayout(void);

#ifdef __cplusplus
  }
#endif

#endif // CM_DESIGN_INCLUDED
