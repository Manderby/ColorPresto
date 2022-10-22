
#include "CMMetamericsController.h"

#include "CMColorRenderingIndex.h"
#include "CMTranslations.h"
#include "CMTwoColorController.h"
#include "CMUVMetamericColors.h"
#include "CMVisMetamericColors.h"
#include "CMWhitePoints.h"
#include "NAApp.h"
#include "CML.h"
#include "mainC.h"


static const double marginHLeft = 15.;
static const double marginH = 5.;
static const double margin2H = 10.;
static const double marginHRight = 15.;
static const double marginYBottom = 15.;
static const double marginYTop = marginYBottom - 3.;

static const double indexWidth = 35.;
static const double valueWidth = 60.;
static const double threeValueHeight = 55.;
static const double threeValueMargin = threeValueHeight + 10.;
static const double colorWidth = 160.;
static const double columnWidth = marginHLeft + indexWidth + valueWidth + colorWidth + 2 * marginH + marginHRight;
static const double degreeWidth = 30;
static const double firstColumnWidth = columnWidth + degreeWidth + 5;
static const double firstColumLeft = marginHLeft + degreeWidth + 5;

static const double valueLeft = marginHLeft + indexWidth + marginH;
static const double colorLeft = valueLeft + valueWidth + marginH;



NAFont* monoFont;

struct CMMetamericsController{
  NAWindow* window;
  
  NASpace* whitePointBigSpace;
  NASpace* colorRenderingBigSpace;
  NASpace* metamericsBigSpace;
  
  NASpace* illSpace;
  NALabel* ill10DegLabel;
  NALabel* ill2DegLabel;
  
  NALabel* illTitle;

  NALabel* illXYZTitle;
  NALabel* illYxyTitle;
  NALabel* illYupvpTitle;
  NALabel* illYuvTitle;

  NALabel* illXYZ10Label;
  NALabel* illYxy10Label;
  NALabel* illYupvp10Label;
  NALabel* illYuv10Label;

  NALabel* illXYZ2Label;
  NALabel* illYxy2Label;
  NALabel* illYupvp2Label;
  NALabel* illYuv2Label;
  
  NASpace* refSpace;
  NALabel* ref10DegLabel;
  NALabel* ref2DegLabel;

  NALabel* refTitle;
  NAPopupButton* refPopupButton;
  NAMenuItem* refD50MenuItem;
  NAMenuItem* refD55MenuItem;
  NAMenuItem* refD65MenuItem;
  NAMenuItem* refD75MenuItem;

  NALabel* refXYZTitle;
  NALabel* refYxyTitle;
  NALabel* refYupvpTitle;
  NALabel* refYuvTitle;

  NALabel* refXYZ10Label;
  NALabel* refYxy10Label;
  NALabel* refYupvp10Label;
  NALabel* refYuv10Label;

  NALabel* refXYZ2Label;
  NALabel* refYxy2Label;
  NALabel* refYupvp2Label;
  NALabel* refYuv2Label;
  
  NASpace* chromaticitySpace;
  NALabel* chromaticityTitle;
  NALabel* chromaticityLabel;

  NASpace* colorRenderingSpace;
  NALabel* colorRenderingTitle;
  NALabel* colorRendering1IndexLabel;
  NALabel* colorRendering1Label;
  CMTwoColorController* colorRendering1Display;
  NALabel* colorRendering2IndexLabel;
  NALabel* colorRendering2Label;
  CMTwoColorController* colorRendering2Display;
  NALabel* colorRendering3IndexLabel;
  NALabel* colorRendering3Label;
  CMTwoColorController* colorRendering3Display;
  NALabel* colorRendering4IndexLabel;
  NALabel* colorRendering4Label;
  CMTwoColorController* colorRendering4Display;
  NALabel* colorRendering5IndexLabel;
  NALabel* colorRendering5Label;
  CMTwoColorController* colorRendering5Display;
  NALabel* colorRendering6IndexLabel;
  NALabel* colorRendering6Label;
  CMTwoColorController* colorRendering6Display;
  NALabel* colorRendering7IndexLabel;
  NALabel* colorRendering7Label;
  CMTwoColorController* colorRendering7Display;
  NALabel* colorRendering8IndexLabel;
  NALabel* colorRendering8Label;
  CMTwoColorController* colorRendering8Display;

  NALabel* colorRenderingAverageLabel;
  NALabel* colorRenderingLabel;

  NALabel* colorRendering9IndexLabel;
  NALabel* colorRendering9Label;
  CMTwoColorController* colorRendering9Display;
  NALabel* colorRendering10IndexLabel;
  NALabel* colorRendering10Label;
  CMTwoColorController* colorRendering10Display;
  NALabel* colorRendering11IndexLabel;
  NALabel* colorRendering11Label;
  CMTwoColorController* colorRendering11Display;
  NALabel* colorRendering12IndexLabel;
  NALabel* colorRendering12Label;
  CMTwoColorController* colorRendering12Display;
  NALabel* colorRendering13IndexLabel;
  NALabel* colorRendering13Label;
  CMTwoColorController* colorRendering13Display;
  NALabel* colorRendering14IndexLabel;
  NALabel* colorRendering14Label;
  CMTwoColorController* colorRendering14Display;

  NASpace* visMetamericsSpace;
  NALabel* visMetamericsTitle;
  NALabel* visMetamerics1IndexLabel;
  NALabel* visMetamerics1Label;
  CMTwoColorController* visMetamerics1Display;
  NALabel* visMetamerics2IndexLabel;
  NALabel* visMetamerics2Label;
  CMTwoColorController* visMetamerics2Display;
  NALabel* visMetamerics3IndexLabel;
  NALabel* visMetamerics3Label;
  CMTwoColorController* visMetamerics3Display;
  NALabel* visMetamerics4IndexLabel;
  NALabel* visMetamerics4Label;
  CMTwoColorController* visMetamerics4Display;
  NALabel* visMetamerics5IndexLabel;
  NALabel* visMetamerics5Label;
  CMTwoColorController* visMetamerics5Display;
  NALabel* visMetamericsAverageLabel;
  NALabel* visMetamericsLabel;
  NALabel* visMetamericsGradeLabel;

  NASpace* uvMetamericsSpace;
  NALabel* uvMetamericsTitle;
  NALabel* uvMetamerics6IndexLabel;
  NALabel* uvMetamerics6Label;
  CMTwoColorController* uvMetamerics6Display;
  NALabel* uvMetamerics7IndexLabel;
  NALabel* uvMetamerics7Label;
  CMTwoColorController* uvMetamerics7Display;
  NALabel* uvMetamerics8IndexLabel;
  NALabel* uvMetamerics8Label;
  CMTwoColorController* uvMetamerics8Display;
  NALabel* uvMetamericsAverageLabel;
  NALabel* uvMetamericsLabel;
  NALabel* uvMetamericsGradeLabel;

  NASpace* totalMetamericsSpace;
  NALabel* totalMetamericsTitle;
  NALabel* totalMetamericsAverageLabel;
  NALabel* totalMetamericsLabel;
  NALabel* totalMetamericsGradeLabel;

  CMReferenceIlluminationType referenceIlluminationType;
};



NALabel* cmNewValueLabel(){
  NALabel* label = naNewLabel("", valueWidth);
  naSetLabelFont(label, monoFont);
  return label;
}

NALabel* cmNewThreeValueLabel(){
  NALabel* label = naNewLabel("", valueWidth);
  naSetLabelHeight(label, threeValueHeight);
  naSetLabelFont(label, monoFont);
  return label;
}

const NAUTF8Char* getGrade(float value){
  if(value <= .25f){return "Grade A";}
  else if(value <= .5f){return "Grade B";}
  else if(value <= 1.f){return "Grade C";}
  else if(value <= 2.f){return "Grade D";}
  return "Grade E";
}



NABool cmSelectRefSpectrum(NAReaction reaction){
  CMMetamericsController* con = (CMMetamericsController*)reaction.controller;
  if(reaction.uiElement == con->refD50MenuItem){
    con->referenceIlluminationType = REFERENCE_ILLUMINATION_D50;
  }else if(reaction.uiElement == con->refD55MenuItem){
    con->referenceIlluminationType = REFERENCE_ILLUMINATION_D55;
  }else if(reaction.uiElement == con->refD65MenuItem){
    con->referenceIlluminationType = REFERENCE_ILLUMINATION_D65;
  }else if(reaction.uiElement == con->refD75MenuItem){
    con->referenceIlluminationType = REFERENCE_ILLUMINATION_D75;
  }

  cmUpdateMetamericsController(con);

  return NA_TRUE;
}



CMMetamericsController* cmAllocMetamericsController(void){
  monoFont = naCreateFontWithPreset(NA_FONT_KIND_MONOSPACE, NA_FONT_SIZE_DEFAULT);

  CMMetamericsController* con = naAlloc(CMMetamericsController);
  naZeron(con, sizeof(CMMetamericsController));

  NAFont* boldFont = naCreateFontWithPreset(NA_FONT_KIND_TITLE, NA_FONT_SIZE_DEFAULT);

  const double illSpaceHeight = 2 * 25 + 2 * threeValueMargin + marginYTop + marginYBottom;
  const double refSpaceHeight = 1 * 25 + 2 * threeValueMargin + marginYTop + marginYBottom;
  const double chromaticitySpaceHeight = 1 * 25 + marginYTop + marginYBottom;
  const double colorRenderingSpaceHeight = 17 * 25 + marginYTop + marginYBottom;
  const double visMetamericsSpaceHeight = 7 * 25 + marginYTop + marginYBottom;
  const double uvMetamericsSpaceHeight = 5 * 25 + marginYTop + marginYBottom;
  const double totalMetamericsSpaceHeight = 2 * 25 + marginYTop + marginYBottom;

  const double totalHeight = colorRenderingSpaceHeight;

  con->window = naNewWindow(
    cmTranslate(CMWhitepointsAndMetamerics),
    naMakeRectS(
      600,
      500,
      firstColumnWidth + 2 * columnWidth,
      totalHeight),
    0,
    0);
  NASpace* contentSpace = naGetWindowContentSpace(con->window);

  con->whitePointBigSpace = naNewSpace(naMakeSize(firstColumnWidth, totalHeight));
  con->colorRenderingBigSpace = naNewSpace(naMakeSize(columnWidth, totalHeight));
  naSetSpaceAlternateBackground(con->colorRenderingBigSpace, NA_TRUE);
  con->metamericsBigSpace = naNewSpace(naMakeSize(columnWidth, totalHeight));


  // Illumination whitepoint
  con->illSpace = naNewSpace(naMakeSize(firstColumnWidth, illSpaceHeight));

  con->ill10DegLabel = naNewLabel("10°", degreeWidth);
  naSetLabelFont(con->ill10DegLabel, boldFont);
  con->ill2DegLabel = naNewLabel("2°", degreeWidth);
  naSetLabelFont(con->ill2DegLabel, boldFont);

  con->illTitle = naNewLabel("Current:", columnWidth - marginHLeft - marginHRight);
  naSetLabelTextAlignment(con->illTitle, NA_TEXT_ALIGNMENT_CENTER);

  con->illXYZTitle = naNewLabel("XYZ", valueWidth);
  naSetLabelTextAlignment(con->illXYZTitle, NA_TEXT_ALIGNMENT_CENTER);
  naSetLabelFont(con->illXYZTitle, boldFont);
  con->illYxyTitle = naNewLabel("Yxy", valueWidth);
  naSetLabelTextAlignment(con->illYxyTitle, NA_TEXT_ALIGNMENT_CENTER);
  naSetLabelFont(con->illYxyTitle, boldFont);
  con->illYupvpTitle = naNewLabel("Yu'v'", valueWidth);
  naSetLabelTextAlignment(con->illYupvpTitle, NA_TEXT_ALIGNMENT_CENTER);
  naSetLabelFont(con->illYupvpTitle, boldFont);
  con->illYuvTitle = naNewLabel("Yuv", valueWidth);
  naSetLabelTextAlignment(con->illYuvTitle, NA_TEXT_ALIGNMENT_CENTER);
  naSetLabelFont(con->illYuvTitle, boldFont);

  con->illXYZ10Label = cmNewThreeValueLabel();
  con->illYxy10Label = cmNewThreeValueLabel();
  con->illYupvp10Label = cmNewThreeValueLabel();
  con->illYuv10Label = cmNewThreeValueLabel();
  
  con->illXYZ2Label = cmNewThreeValueLabel();
  con->illYxy2Label = cmNewThreeValueLabel();
  con->illYupvp2Label = cmNewThreeValueLabel();
  con->illYuv2Label = cmNewThreeValueLabel();



  // Reference whitepoint
  con->refSpace = naNewSpace(naMakeSize(firstColumnWidth, refSpaceHeight));

  con->ref10DegLabel = naNewLabel("10°", degreeWidth);
  naSetLabelFont(con->ref10DegLabel, boldFont);
  con->ref2DegLabel = naNewLabel("2°", degreeWidth);
  naSetLabelFont(con->ref2DegLabel, boldFont);

  con->refTitle = naNewLabel("Reference:", 70);

  con->refPopupButton = naNewPopupButton(70);
  con->refD50MenuItem = naNewMenuItem("D50");
  con->refD55MenuItem = naNewMenuItem("D55");
  con->refD65MenuItem = naNewMenuItem("D65");
  con->refD75MenuItem = naNewMenuItem("D75");
  naAddPopupButtonMenuItem(con->refPopupButton, con->refD50MenuItem, NA_NULL);
  naAddPopupButtonMenuItem(con->refPopupButton, con->refD55MenuItem, NA_NULL);
  naAddPopupButtonMenuItem(con->refPopupButton, con->refD65MenuItem, NA_NULL);
  naAddPopupButtonMenuItem(con->refPopupButton, con->refD75MenuItem, NA_NULL);
  naAddUIReaction(con->refD50MenuItem, NA_UI_COMMAND_PRESSED, cmSelectRefSpectrum, con);
  naAddUIReaction(con->refD55MenuItem, NA_UI_COMMAND_PRESSED, cmSelectRefSpectrum, con);
  naAddUIReaction(con->refD65MenuItem, NA_UI_COMMAND_PRESSED, cmSelectRefSpectrum, con);
  naAddUIReaction(con->refD75MenuItem, NA_UI_COMMAND_PRESSED, cmSelectRefSpectrum, con);

  con->refXYZTitle = naNewLabel("XYZ", valueWidth);
  naSetLabelTextAlignment(con->refXYZTitle, NA_TEXT_ALIGNMENT_CENTER);
  naSetLabelFont(con->refXYZTitle, boldFont);
  con->refYxyTitle = naNewLabel("Yxy", valueWidth);
  naSetLabelTextAlignment(con->refYxyTitle, NA_TEXT_ALIGNMENT_CENTER);
  naSetLabelFont(con->refYxyTitle, boldFont);
  con->refYupvpTitle = naNewLabel("Yu'v'", valueWidth);
  naSetLabelTextAlignment(con->refYupvpTitle, NA_TEXT_ALIGNMENT_CENTER);
  naSetLabelFont(con->refYupvpTitle, boldFont);
  con->refYuvTitle = naNewLabel("Yuv", valueWidth);
  naSetLabelTextAlignment(con->refYuvTitle, NA_TEXT_ALIGNMENT_CENTER);
  naSetLabelFont(con->refYuvTitle, boldFont);

  con->refXYZ10Label = cmNewThreeValueLabel();
  con->refYxy10Label = cmNewThreeValueLabel();
  con->refYupvp10Label = cmNewThreeValueLabel();
  con->refYuv10Label = cmNewThreeValueLabel();
  
  con->refXYZ2Label = cmNewThreeValueLabel();
  con->refYxy2Label = cmNewThreeValueLabel();
  con->refYupvp2Label = cmNewThreeValueLabel();
  con->refYuv2Label = cmNewThreeValueLabel();
  


  // Chromaticity error
  con->chromaticitySpace = naNewSpace(naMakeSize(firstColumnWidth, chromaticitySpaceHeight));

  con->chromaticityTitle = naNewLabel("Chromaticity Error:", 250);
  naSetLabelFont(con->chromaticityTitle, boldFont);

  con->chromaticityLabel = cmNewValueLabel();



  // Color Rendering index
  con->colorRenderingSpace = naNewSpace(naMakeSize(columnWidth, colorRenderingSpaceHeight));

  con->colorRenderingTitle = naNewLabel("Color Rendering Index:", 250);
  naSetLabelFont(con->colorRenderingTitle, boldFont);

  con->colorRendering1IndexLabel = naNewLabel("1:", indexWidth);
  con->colorRendering1Label = cmNewValueLabel();
  con->colorRendering1Display = cmAllocTwoColorController(naMakeSize(colorWidth, 21));
  con->colorRendering2IndexLabel = naNewLabel("2:", indexWidth);
  con->colorRendering2Label = cmNewValueLabel();
  con->colorRendering2Display = cmAllocTwoColorController(naMakeSize(colorWidth, 21));
  con->colorRendering3IndexLabel = naNewLabel("3:", indexWidth);
  con->colorRendering3Label = cmNewValueLabel();
  con->colorRendering3Display = cmAllocTwoColorController(naMakeSize(colorWidth, 21));
  con->colorRendering4IndexLabel = naNewLabel("4:", indexWidth);
  con->colorRendering4Label = cmNewValueLabel();
  con->colorRendering4Display = cmAllocTwoColorController(naMakeSize(colorWidth, 21));
  con->colorRendering5IndexLabel = naNewLabel("5:", indexWidth);
  con->colorRendering5Label = cmNewValueLabel();
  con->colorRendering5Display = cmAllocTwoColorController(naMakeSize(colorWidth, 21));
  con->colorRendering6IndexLabel = naNewLabel("6:", indexWidth);
  con->colorRendering6Label = cmNewValueLabel();
  con->colorRendering6Display = cmAllocTwoColorController(naMakeSize(colorWidth, 21));
  con->colorRendering7IndexLabel = naNewLabel("7:", indexWidth);
  con->colorRendering7Label = cmNewValueLabel();
  con->colorRendering7Display = cmAllocTwoColorController(naMakeSize(colorWidth, 21));
  con->colorRendering8IndexLabel = naNewLabel("8:", indexWidth);
  con->colorRendering8Label = cmNewValueLabel();
  con->colorRendering8Display = cmAllocTwoColorController(naMakeSize(colorWidth, 21));

  con->colorRenderingAverageLabel = naNewLabel("Avg:", 120);
  con->colorRenderingLabel = cmNewValueLabel();

  con->colorRendering9IndexLabel = naNewLabel("9:", indexWidth);
  con->colorRendering9Label = cmNewValueLabel();
  con->colorRendering9Display = cmAllocTwoColorController(naMakeSize(colorWidth, 21));
  con->colorRendering10IndexLabel = naNewLabel("10:", indexWidth);
  con->colorRendering10Label = cmNewValueLabel();
  con->colorRendering10Display = cmAllocTwoColorController(naMakeSize(colorWidth, 21));
  con->colorRendering11IndexLabel = naNewLabel("11:", indexWidth);
  con->colorRendering11Label = cmNewValueLabel();
  con->colorRendering11Display = cmAllocTwoColorController(naMakeSize(colorWidth, 21));
  con->colorRendering12IndexLabel = naNewLabel("12:", indexWidth);
  con->colorRendering12Label = cmNewValueLabel();
  con->colorRendering12Display = cmAllocTwoColorController(naMakeSize(colorWidth, 21));
  con->colorRendering13IndexLabel = naNewLabel("13:", indexWidth);
  con->colorRendering13Label = cmNewValueLabel();
  con->colorRendering13Display = cmAllocTwoColorController(naMakeSize(colorWidth, 21));
  con->colorRendering14IndexLabel = naNewLabel("14:", indexWidth);
  con->colorRendering14Label = cmNewValueLabel();
  con->colorRendering14Display = cmAllocTwoColorController(naMakeSize(colorWidth, 21));

  // visible range metamerics
  con->visMetamericsSpace = naNewSpace(naMakeSize(columnWidth, visMetamericsSpaceHeight));
  
  con->visMetamericsTitle = naNewLabel("Visible Range Metameric Index:", 250);
  naSetLabelFont(con->visMetamericsTitle, boldFont);
  
  con->visMetamerics1IndexLabel = naNewLabel("1:", indexWidth);
  con->visMetamerics1Label = cmNewValueLabel();
  con->visMetamerics1Display = cmAllocTwoColorController(naMakeSize(colorWidth, 21));

  con->visMetamerics2IndexLabel = naNewLabel("2:", indexWidth);
  con->visMetamerics2Label = cmNewValueLabel();
  con->visMetamerics2Display = cmAllocTwoColorController(naMakeSize(colorWidth, 21));

  con->visMetamerics3IndexLabel = naNewLabel("3:", indexWidth);
  con->visMetamerics3Label = cmNewValueLabel();
  con->visMetamerics3Display = cmAllocTwoColorController(naMakeSize(colorWidth, 21));

  con->visMetamerics4IndexLabel = naNewLabel("4:", indexWidth);
  con->visMetamerics4Label = cmNewValueLabel();
  con->visMetamerics4Display = cmAllocTwoColorController(naMakeSize(colorWidth, 21));

  con->visMetamerics5IndexLabel = naNewLabel("5:", indexWidth);
  con->visMetamerics5Label = cmNewValueLabel();
  con->visMetamerics5Display = cmAllocTwoColorController(naMakeSize(colorWidth, 21));

  con->visMetamericsAverageLabel = naNewLabel("Avg:", indexWidth);
  con->visMetamericsLabel = cmNewValueLabel();
  con->visMetamericsGradeLabel = naNewLabel("Grade A", 120);


  // UV metamerics
  con->uvMetamericsSpace = naNewSpace(naMakeSize(columnWidth, uvMetamericsSpaceHeight));

  con->uvMetamericsTitle = naNewLabel("Ultraviolet Range Metameric Index:", 250);
  naSetLabelFont(con->uvMetamericsTitle, boldFont);

  con->uvMetamerics6IndexLabel = naNewLabel("6:", indexWidth);
  con->uvMetamerics6Label = cmNewValueLabel();
  con->uvMetamerics6Display = cmAllocTwoColorController(naMakeSize(colorWidth, 21));

  con->uvMetamerics7IndexLabel = naNewLabel("7:", indexWidth);
  con->uvMetamerics7Label = cmNewValueLabel();
  con->uvMetamerics7Display = cmAllocTwoColorController(naMakeSize(colorWidth, 21));

  con->uvMetamerics8IndexLabel = naNewLabel("8:", indexWidth);
  con->uvMetamerics8Label = cmNewValueLabel();
  con->uvMetamerics8Display = cmAllocTwoColorController(naMakeSize(colorWidth, 21));

  con->uvMetamericsAverageLabel = naNewLabel("Avg:", 120);
  con->uvMetamericsLabel = cmNewValueLabel();
  con->uvMetamericsGradeLabel = naNewLabel("Grade A", 120);


  // Total metamerics
  con->totalMetamericsSpace = naNewSpace(naMakeSize(columnWidth, totalMetamericsSpaceHeight));

  con->totalMetamericsTitle = naNewLabel("Total Metameric Index (Average 1-8):", 250);
  naSetLabelFont(con->totalMetamericsTitle, boldFont);
  con->totalMetamericsAverageLabel = naNewLabel("Avg:", 120);
  con->totalMetamericsLabel = cmNewValueLabel();
  con->totalMetamericsGradeLabel = naNewLabel("Grade A", 120);



  // Placing elements in the window

  // Left BigSpace: White Points and Chromaticity Error

  double columnY = totalHeight;

  double illY = illSpaceHeight - marginYTop;
  illY -= 25;
  naAddSpaceChild(con->illSpace, con->illTitle, naMakePos(firstColumLeft, illY));
  illY -= 25;
  naAddSpaceChild(con->illSpace, con->illXYZTitle, naMakePos(firstColumLeft + 0 * (valueWidth + margin2H) - 3, illY));
  naAddSpaceChild(con->illSpace, con->illYxyTitle, naMakePos(firstColumLeft + 1 * (valueWidth + margin2H) - 3, illY));
  naAddSpaceChild(con->illSpace, con->illYupvpTitle, naMakePos(firstColumLeft + 2 * (valueWidth + margin2H) - 3, illY));
  naAddSpaceChild(con->illSpace, con->illYuvTitle, naMakePos(firstColumLeft + 3 * (valueWidth + margin2H) - 3, illY));
  illY -= threeValueMargin;
  naAddSpaceChild(con->illSpace, con->illXYZ10Label, naMakePos(firstColumLeft + 0 * (valueWidth + margin2H), illY));
  naAddSpaceChild(con->illSpace, con->illYxy10Label, naMakePos(firstColumLeft + 1 * (valueWidth + margin2H), illY));
  naAddSpaceChild(con->illSpace, con->illYupvp10Label, naMakePos(firstColumLeft + 2 * (valueWidth + margin2H), illY));
  naAddSpaceChild(con->illSpace, con->illYuv10Label, naMakePos(firstColumLeft + 3 * (valueWidth + margin2H), illY));

  illY -= threeValueMargin;
  naAddSpaceChild(con->illSpace, con->illXYZ2Label, naMakePos(firstColumLeft + 0 * (valueWidth + margin2H), illY));
  naAddSpaceChild(con->illSpace, con->illYxy2Label, naMakePos(firstColumLeft + 1 * (valueWidth + margin2H), illY));
  naAddSpaceChild(con->illSpace, con->illYupvp2Label, naMakePos(firstColumLeft + 2 * (valueWidth + margin2H), illY));
  naAddSpaceChild(con->illSpace, con->illYuv2Label, naMakePos(firstColumLeft + 3 * (valueWidth + margin2H), illY));

  naAddSpaceChild(con->illSpace, con->ill10DegLabel, naMakePos(marginHLeft, 103));
  naAddSpaceChild(con->illSpace, con->ill2DegLabel, naMakePos(marginHLeft, 33));

  columnY -= illSpaceHeight;
  naAddSpaceChild(con->whitePointBigSpace, con->illSpace, naMakePos(0, columnY));



  double refY = refSpaceHeight - marginYTop;
  refY -= 25;
  naAddSpaceChild(con->refSpace, con->refTitle, naMakePos(110, refY));
  naAddSpaceChild(con->refSpace, con->refPopupButton, naMakePos(190, refY));
//  refY -= 25;
//  naAddSpaceChild(con->refSpace, con->refXYZTitle, naMakePos(firstColumLeft + 0 * (valueWidth + margin2H) - 3, refY));
//  naAddSpaceChild(con->refSpace, con->refYxyTitle, naMakePos(firstColumLeft + 1 * (valueWidth + margin2H) - 3, refY));
//  naAddSpaceChild(con->refSpace, con->refYupvpTitle, naMakePos(firstColumLeft + 2 * (valueWidth + margin2H) - 3, refY));
//  naAddSpaceChild(con->refSpace, con->refYuvTitle, naMakePos(firstColumLeft + 3 * (valueWidth + margin2H) - 3, refY));
  refY -= threeValueMargin;
  naAddSpaceChild(con->refSpace, con->refXYZ10Label, naMakePos(firstColumLeft + 0 * (valueWidth + margin2H), refY));
  naAddSpaceChild(con->refSpace, con->refYxy10Label, naMakePos(firstColumLeft + 1 * (valueWidth + margin2H), refY));
  naAddSpaceChild(con->refSpace, con->refYupvp10Label, naMakePos(firstColumLeft + 2 * (valueWidth + margin2H), refY));
  naAddSpaceChild(con->refSpace, con->refYuv10Label, naMakePos(firstColumLeft + 3 * (valueWidth + margin2H), refY));

  refY -= threeValueMargin;
  naAddSpaceChild(con->refSpace, con->refXYZ2Label, naMakePos(firstColumLeft + 0 * (valueWidth + margin2H), refY));
  naAddSpaceChild(con->refSpace, con->refYxy2Label, naMakePos(firstColumLeft + 1 * (valueWidth + margin2H), refY));
  naAddSpaceChild(con->refSpace, con->refYupvp2Label, naMakePos(firstColumLeft + 2 * (valueWidth + margin2H), refY));
  naAddSpaceChild(con->refSpace, con->refYuv2Label, naMakePos(firstColumLeft + 3 * (valueWidth + margin2H), refY));

  naAddSpaceChild(con->refSpace, con->ref10DegLabel, naMakePos(marginHLeft, 103));
  naAddSpaceChild(con->refSpace, con->ref2DegLabel, naMakePos(marginHLeft, 33));

  columnY -= refSpaceHeight;
  naAddSpaceChild(con->whitePointBigSpace, con->refSpace, naMakePos(0, columnY));



  double chromaticityY = chromaticitySpaceHeight - marginYTop;
  chromaticityY -= 25;
  naAddSpaceChild(con->chromaticitySpace, con->chromaticityTitle, naMakePos(firstColumLeft, chromaticityY));
  naAddSpaceChild(con->chromaticitySpace, con->chromaticityLabel, naMakePos(firstColumLeft + 180, chromaticityY));

  columnY -= chromaticitySpaceHeight;
  naAddSpaceChild(con->whitePointBigSpace, con->chromaticitySpace, naMakePos(0, columnY));

  naAddSpaceChild(contentSpace, con->whitePointBigSpace, naMakePos(0, 0));



  // Middle BigSpace: Color Rendering Index

  columnY = totalHeight;

  double colorRenderingY = colorRenderingSpaceHeight - marginYTop;
  colorRenderingY -= 25;
  naAddSpaceChild(con->colorRenderingSpace, con->colorRenderingTitle, naMakePos(marginHLeft, colorRenderingY));

  colorRenderingY -= 25;
  naAddSpaceChild(con->colorRenderingSpace, con->colorRendering1IndexLabel, naMakePos(marginHLeft, colorRenderingY));
  naAddSpaceChild(con->colorRenderingSpace, con->colorRendering1Label, naMakePos(valueLeft, colorRenderingY));
  naAddSpaceChild(con->colorRenderingSpace, cmGetTwoColorControllerUIElement(con->colorRendering1Display), naMakePos(colorLeft, colorRenderingY));
  colorRenderingY -= 25;
  naAddSpaceChild(con->colorRenderingSpace, con->colorRendering2IndexLabel, naMakePos(marginHLeft, colorRenderingY));
  naAddSpaceChild(con->colorRenderingSpace, con->colorRendering2Label, naMakePos(valueLeft, colorRenderingY));
  naAddSpaceChild(con->colorRenderingSpace, cmGetTwoColorControllerUIElement(con->colorRendering2Display), naMakePos(colorLeft, colorRenderingY));
  colorRenderingY -= 25;
  naAddSpaceChild(con->colorRenderingSpace, con->colorRendering3IndexLabel, naMakePos(marginHLeft, colorRenderingY));
  naAddSpaceChild(con->colorRenderingSpace, con->colorRendering3Label, naMakePos(valueLeft, colorRenderingY));
  naAddSpaceChild(con->colorRenderingSpace, cmGetTwoColorControllerUIElement(con->colorRendering3Display), naMakePos(colorLeft, colorRenderingY));
  colorRenderingY -= 25;
  naAddSpaceChild(con->colorRenderingSpace, con->colorRendering4IndexLabel, naMakePos(marginHLeft, colorRenderingY));
  naAddSpaceChild(con->colorRenderingSpace, con->colorRendering4Label, naMakePos(valueLeft, colorRenderingY));
  naAddSpaceChild(con->colorRenderingSpace, cmGetTwoColorControllerUIElement(con->colorRendering4Display), naMakePos(colorLeft, colorRenderingY));
  colorRenderingY -= 25;
  naAddSpaceChild(con->colorRenderingSpace, con->colorRendering5IndexLabel, naMakePos(marginHLeft, colorRenderingY));
  naAddSpaceChild(con->colorRenderingSpace, con->colorRendering5Label, naMakePos(valueLeft, colorRenderingY));
  naAddSpaceChild(con->colorRenderingSpace, cmGetTwoColorControllerUIElement(con->colorRendering5Display), naMakePos(colorLeft, colorRenderingY));
  colorRenderingY -= 25;
  naAddSpaceChild(con->colorRenderingSpace, con->colorRendering6IndexLabel, naMakePos(marginHLeft, colorRenderingY));
  naAddSpaceChild(con->colorRenderingSpace, con->colorRendering6Label, naMakePos(valueLeft, colorRenderingY));
  naAddSpaceChild(con->colorRenderingSpace, cmGetTwoColorControllerUIElement(con->colorRendering6Display), naMakePos(colorLeft, colorRenderingY));
  colorRenderingY -= 25;
  naAddSpaceChild(con->colorRenderingSpace, con->colorRendering7IndexLabel, naMakePos(marginHLeft, colorRenderingY));
  naAddSpaceChild(con->colorRenderingSpace, con->colorRendering7Label, naMakePos(valueLeft, colorRenderingY));
  naAddSpaceChild(con->colorRenderingSpace, cmGetTwoColorControllerUIElement(con->colorRendering7Display), naMakePos(colorLeft, colorRenderingY));
  colorRenderingY -= 25;
  naAddSpaceChild(con->colorRenderingSpace, con->colorRendering8IndexLabel, naMakePos(marginHLeft, colorRenderingY));
  naAddSpaceChild(con->colorRenderingSpace, con->colorRendering8Label, naMakePos(valueLeft, colorRenderingY));
  naAddSpaceChild(con->colorRenderingSpace, cmGetTwoColorControllerUIElement(con->colorRendering8Display), naMakePos(colorLeft, colorRenderingY));

  colorRenderingY -= 25;
  naAddSpaceChild(con->colorRenderingSpace, con->colorRenderingAverageLabel, naMakePos(marginHLeft, colorRenderingY));
  naAddSpaceChild(con->colorRenderingSpace, con->colorRenderingLabel, naMakePos(valueLeft, colorRenderingY));

  colorRenderingY -= 50;
  naAddSpaceChild(con->colorRenderingSpace, con->colorRendering9IndexLabel, naMakePos(marginHLeft, colorRenderingY));
  naAddSpaceChild(con->colorRenderingSpace, con->colorRendering9Label, naMakePos(valueLeft, colorRenderingY));
  naAddSpaceChild(con->colorRenderingSpace, cmGetTwoColorControllerUIElement(con->colorRendering9Display), naMakePos(colorLeft, colorRenderingY));
  colorRenderingY -= 25;
  naAddSpaceChild(con->colorRenderingSpace, con->colorRendering10IndexLabel, naMakePos(marginHLeft, colorRenderingY));
  naAddSpaceChild(con->colorRenderingSpace, con->colorRendering10Label, naMakePos(valueLeft, colorRenderingY));
  naAddSpaceChild(con->colorRenderingSpace, cmGetTwoColorControllerUIElement(con->colorRendering10Display), naMakePos(colorLeft, colorRenderingY));
  colorRenderingY -= 25;
  naAddSpaceChild(con->colorRenderingSpace, con->colorRendering11IndexLabel, naMakePos(marginHLeft, colorRenderingY));
  naAddSpaceChild(con->colorRenderingSpace, con->colorRendering11Label, naMakePos(valueLeft, colorRenderingY));
  naAddSpaceChild(con->colorRenderingSpace, cmGetTwoColorControllerUIElement(con->colorRendering11Display), naMakePos(colorLeft, colorRenderingY));
  colorRenderingY -= 25;
  naAddSpaceChild(con->colorRenderingSpace, con->colorRendering12IndexLabel, naMakePos(marginHLeft, colorRenderingY));
  naAddSpaceChild(con->colorRenderingSpace, con->colorRendering12Label, naMakePos(valueLeft, colorRenderingY));
  naAddSpaceChild(con->colorRenderingSpace, cmGetTwoColorControllerUIElement(con->colorRendering12Display), naMakePos(colorLeft, colorRenderingY));
  colorRenderingY -= 25;
  naAddSpaceChild(con->colorRenderingSpace, con->colorRendering13IndexLabel, naMakePos(marginHLeft, colorRenderingY));
  naAddSpaceChild(con->colorRenderingSpace, con->colorRendering13Label, naMakePos(valueLeft, colorRenderingY));
  naAddSpaceChild(con->colorRenderingSpace, cmGetTwoColorControllerUIElement(con->colorRendering13Display), naMakePos(colorLeft, colorRenderingY));
  colorRenderingY -= 25;
  naAddSpaceChild(con->colorRenderingSpace, con->colorRendering14IndexLabel, naMakePos(marginHLeft, colorRenderingY));
  naAddSpaceChild(con->colorRenderingSpace, con->colorRendering14Label, naMakePos(valueLeft, colorRenderingY));
  naAddSpaceChild(con->colorRenderingSpace, cmGetTwoColorControllerUIElement(con->colorRendering14Display), naMakePos(colorLeft, colorRenderingY));

  columnY -= colorRenderingSpaceHeight;
  naAddSpaceChild(con->colorRenderingBigSpace, con->colorRenderingSpace, naMakePos(0, columnY));

  naAddSpaceChild(contentSpace, con->colorRenderingBigSpace, naMakePos(firstColumnWidth, 0));



  // Right BigSpace: Metameric Index

  columnY = totalHeight;

  double visMetamericsY = visMetamericsSpaceHeight - marginYTop;
  visMetamericsY -= 25;
  naAddSpaceChild(con->visMetamericsSpace, con->visMetamericsTitle, naMakePos(marginHLeft, visMetamericsY));
  
  visMetamericsY -= 25;
  naAddSpaceChild(con->visMetamericsSpace, con->visMetamerics1IndexLabel, naMakePos(marginHLeft, visMetamericsY));
  naAddSpaceChild(con->visMetamericsSpace, con->visMetamerics1Label, naMakePos(valueLeft, visMetamericsY));
  naAddSpaceChild(con->visMetamericsSpace, cmGetTwoColorControllerUIElement(con->visMetamerics1Display), naMakePos(colorLeft, visMetamericsY));
  
  visMetamericsY -= 25;
  naAddSpaceChild(con->visMetamericsSpace, con->visMetamerics2IndexLabel, naMakePos(marginHLeft, visMetamericsY));
  naAddSpaceChild(con->visMetamericsSpace, con->visMetamerics2Label, naMakePos(valueLeft, visMetamericsY));
  naAddSpaceChild(con->visMetamericsSpace, cmGetTwoColorControllerUIElement(con->visMetamerics2Display), naMakePos(colorLeft, visMetamericsY));
  
  visMetamericsY -= 25;
  naAddSpaceChild(con->visMetamericsSpace, con->visMetamerics3IndexLabel, naMakePos(marginHLeft, visMetamericsY));
  naAddSpaceChild(con->visMetamericsSpace, con->visMetamerics3Label, naMakePos(valueLeft, visMetamericsY));
  naAddSpaceChild(con->visMetamericsSpace, cmGetTwoColorControllerUIElement(con->visMetamerics3Display), naMakePos(colorLeft, visMetamericsY));

  visMetamericsY -= 25;
  naAddSpaceChild(con->visMetamericsSpace, con->visMetamerics4IndexLabel, naMakePos(marginHLeft, visMetamericsY));
  naAddSpaceChild(con->visMetamericsSpace, con->visMetamerics4Label, naMakePos(valueLeft, visMetamericsY));
  naAddSpaceChild(con->visMetamericsSpace, cmGetTwoColorControllerUIElement(con->visMetamerics4Display), naMakePos(colorLeft, visMetamericsY));
  
  visMetamericsY -= 25;
  naAddSpaceChild(con->visMetamericsSpace, con->visMetamerics5IndexLabel, naMakePos(marginHLeft, visMetamericsY));
  naAddSpaceChild(con->visMetamericsSpace, con->visMetamerics5Label, naMakePos(valueLeft, visMetamericsY));
  naAddSpaceChild(con->visMetamericsSpace, cmGetTwoColorControllerUIElement(con->visMetamerics5Display), naMakePos(colorLeft, visMetamericsY));
  
  visMetamericsY -= 25;
  naAddSpaceChild(con->visMetamericsSpace, con->visMetamericsAverageLabel, naMakePos(marginHLeft, visMetamericsY));
  naAddSpaceChild(con->visMetamericsSpace, con->visMetamericsLabel, naMakePos(valueLeft, visMetamericsY));
  naAddSpaceChild(con->visMetamericsSpace, con->visMetamericsGradeLabel, naMakePos(colorLeft, visMetamericsY));

  columnY -= visMetamericsSpaceHeight;
  naAddSpaceChild(con->metamericsBigSpace, con->visMetamericsSpace, naMakePos(0, columnY));



  double uvMetamericsY = uvMetamericsSpaceHeight - marginYTop;
  uvMetamericsY -= 25;

  naAddSpaceChild(con->uvMetamericsSpace, con->uvMetamericsTitle, naMakePos(marginHLeft, uvMetamericsY));

  uvMetamericsY -= 25;
  naAddSpaceChild(con->uvMetamericsSpace, con->uvMetamerics6IndexLabel, naMakePos(marginHLeft, uvMetamericsY));
  naAddSpaceChild(con->uvMetamericsSpace, con->uvMetamerics6Label, naMakePos(valueLeft, uvMetamericsY));
  naAddSpaceChild(con->uvMetamericsSpace, cmGetTwoColorControllerUIElement(con->uvMetamerics6Display), naMakePos(colorLeft, uvMetamericsY));

  uvMetamericsY -= 25;
  naAddSpaceChild(con->uvMetamericsSpace, con->uvMetamerics7IndexLabel, naMakePos(marginHLeft, uvMetamericsY));
  naAddSpaceChild(con->uvMetamericsSpace, con->uvMetamerics7Label, naMakePos(valueLeft, uvMetamericsY));
  naAddSpaceChild(con->uvMetamericsSpace, cmGetTwoColorControllerUIElement(con->uvMetamerics7Display), naMakePos(colorLeft, uvMetamericsY));

  uvMetamericsY -= 25;
  naAddSpaceChild(con->uvMetamericsSpace, con->uvMetamerics8IndexLabel, naMakePos(marginHLeft, uvMetamericsY));
  naAddSpaceChild(con->uvMetamericsSpace, con->uvMetamerics8Label, naMakePos(valueLeft, uvMetamericsY));
  naAddSpaceChild(con->uvMetamericsSpace, cmGetTwoColorControllerUIElement(con->uvMetamerics8Display), naMakePos(colorLeft, uvMetamericsY));

  uvMetamericsY -= 25;
  naAddSpaceChild(con->uvMetamericsSpace, con->uvMetamericsAverageLabel, naMakePos(marginHLeft, uvMetamericsY));
  naAddSpaceChild(con->uvMetamericsSpace, con->uvMetamericsLabel, naMakePos(valueLeft, uvMetamericsY));
  naAddSpaceChild(con->uvMetamericsSpace, con->uvMetamericsGradeLabel, naMakePos(colorLeft, uvMetamericsY));

  columnY -= uvMetamericsSpaceHeight;
  naAddSpaceChild(con->metamericsBigSpace, con->uvMetamericsSpace, naMakePos(0, columnY));



  double totalMetamericsY = totalMetamericsSpaceHeight - marginYTop;
  totalMetamericsY -= 25;

  naAddSpaceChild(con->totalMetamericsSpace, con->totalMetamericsTitle, naMakePos(marginHLeft, totalMetamericsY));
 
  totalMetamericsY -= 25;
  naAddSpaceChild(con->totalMetamericsSpace, con->totalMetamericsAverageLabel, naMakePos(marginHLeft, totalMetamericsY));
  naAddSpaceChild(con->totalMetamericsSpace, con->totalMetamericsLabel, naMakePos(valueLeft, totalMetamericsY));
  naAddSpaceChild(con->totalMetamericsSpace, con->totalMetamericsGradeLabel, naMakePos(colorLeft, totalMetamericsY));

  columnY -= totalMetamericsSpaceHeight;
  naAddSpaceChild(con->metamericsBigSpace, con->totalMetamericsSpace, naMakePos(0, columnY));

  naAddSpaceChild(contentSpace, con->metamericsBigSpace, naMakePos(firstColumnWidth + columnWidth, 0));



  naRelease(boldFont);

  con->referenceIlluminationType = REFERENCE_ILLUMINATION_D50;
  
  return con;
}



void cmDeallocMetamericsController(CMMetamericsController* con){
  naRelease(monoFont);
  naFree(con);
}



void cmShowMetamericsController(CMMetamericsController* con){
  naShowWindow(con->window);
}



void cmUpdateMetamericsController(CMMetamericsController* con){
  CMLColorMachine* cm = cmGetCurrentColorMachine();

  CMLFunction* observer10Funcs[3];
  cmlCreateSpecDistFunctions(observer10Funcs, CML_DEFAULT_10DEG_OBSERVER);
  CMLFunction* observer2Funcs[3];
  cmlCreateSpecDistFunctions(observer2Funcs, CML_DEFAULT_2DEG_OBSERVER);
  const CMLFunction* illuminationSpec = cmlGetReferenceIlluminationSpectrum(cm);

  const CMLFunction* ref;
  switch(con->referenceIlluminationType){
  case REFERENCE_ILLUMINATION_D50:
    ref = cmlCreateIlluminationSpectrum(CML_ILLUMINATION_D50, 0.f);
    break;
  case REFERENCE_ILLUMINATION_D55:
    ref = cmlCreateIlluminationSpectrum(CML_ILLUMINATION_D55, 0.f);
    break;
  case REFERENCE_ILLUMINATION_D65:
    ref = cmlCreateIlluminationSpectrum(CML_ILLUMINATION_D65, 0.f);
    break;
  case REFERENCE_ILLUMINATION_D75:
    ref = cmlCreateIlluminationSpectrum(CML_ILLUMINATION_D75, 0.f);
    break;
  default:
    #if NA_DEBUG
      naError("This shoud not happen.");
    #endif
    ref = cmlCreateIlluminationSpectrum(CML_ILLUMINATION_D50, 0.f);
  }

  CMWhitePoints illWhitePoint10 = CMGetWhitePoints(
    illuminationSpec,
    cmlGetReferenceWhitePointYxy(cm),
    observer10Funcs);
  CMWhitePoints illWhitePoint2 = CMGetWhitePoints(
    illuminationSpec,
    cmlGetReferenceWhitePointYxy(cm),
    observer2Funcs);
  CMWhitePoints refWhitePoint10 = CMGetWhitePoints(
    ref,
    NA_NULL,
    observer10Funcs);
  CMWhitePoints refWhitePoint2 = CMGetWhitePoints(
    ref,
    NA_NULL,
    observer2Funcs);

  CMLMat33 adaptationMatrix;
  CMFillChromaticAdaptationMatrix(adaptationMatrix, illWhitePoint10.Yxy);



  // current whitepoint
  const char* illuminationName = cmlGetIlluminationTypeString(cmlGetReferenceIlluminationType(cm));
  naSetLabelText(
    con->illTitle,
    naAllocSprintf(NA_TRUE, "Current: %s", illuminationName));

  naSetLabelText(
    con->illXYZ10Label,
    naAllocSprintf(NA_TRUE, "%1.05f\n%1.05f\n%1.05f", illWhitePoint10.XYZ[0], illWhitePoint10.XYZ[1], illWhitePoint10.XYZ[2]));
  naSetLabelText(
    con->illYxy10Label,
    naAllocSprintf(NA_TRUE, "%1.05f\n%1.05f\n%1.05f", illWhitePoint10.Yxy[0], illWhitePoint10.Yxy[1], illWhitePoint10.Yxy[2]));
  naSetLabelText(
    con->illYupvp10Label,
    naAllocSprintf(NA_TRUE, "%1.05f\n%1.05f\n%1.05f", illWhitePoint10.Yupvp[0], illWhitePoint10.Yupvp[1], illWhitePoint10.Yupvp[2]));
  naSetLabelText(
    con->illYuv10Label,
    naAllocSprintf(NA_TRUE, "%1.05f\n%1.05f\n%1.05f", illWhitePoint10.Yuv[0], illWhitePoint10.Yuv[1], illWhitePoint10.Yuv[2]));

  naSetLabelText(
    con->illXYZ2Label,
    naAllocSprintf(NA_TRUE, "%1.05f\n%1.05f\n%1.05f", illWhitePoint2.XYZ[0], illWhitePoint2.XYZ[1], illWhitePoint2.XYZ[2]));
  naSetLabelText(
    con->illYxy2Label,
    naAllocSprintf(NA_TRUE, "%1.05f\n%1.05f\n%1.05f", illWhitePoint2.Yxy[0], illWhitePoint2.Yxy[1], illWhitePoint2.Yxy[2]));
  naSetLabelText(
    con->illYupvp2Label,
    naAllocSprintf(NA_TRUE, "%1.05f\n%1.05f\n%1.05f", illWhitePoint2.Yupvp[0], illWhitePoint2.Yupvp[1], illWhitePoint2.Yupvp[2]));
  naSetLabelText(
    con->illYuv2Label,
    naAllocSprintf(NA_TRUE, "%1.05f\n%1.05f\n%1.05f", illWhitePoint2.Yuv[0], illWhitePoint2.Yuv[1], illWhitePoint2.Yuv[2]));



  // Reference whitepoint
  
  naSetLabelText(
    con->refXYZ10Label,
    naAllocSprintf(NA_TRUE, "%1.05f\n%1.05f\n%1.05f", refWhitePoint10.XYZ[0], refWhitePoint10.XYZ[1], refWhitePoint10.XYZ[2]));
  naSetLabelText(
    con->refYxy10Label,
    naAllocSprintf(NA_TRUE, "%1.05f\n%1.05f\n%1.05f", refWhitePoint10.Yxy[0], refWhitePoint10.Yxy[1], refWhitePoint10.Yxy[2]));
  naSetLabelText(
    con->refYupvp10Label,
    naAllocSprintf(NA_TRUE, "%1.05f\n%1.05f\n%1.05f", refWhitePoint10.Yupvp[0], refWhitePoint10.Yupvp[1], refWhitePoint10.Yupvp[2]));
  naSetLabelText(
    con->refYuv10Label,
    naAllocSprintf(NA_TRUE, "%1.05f\n%1.05f\n%1.05f", refWhitePoint10.Yuv[0], refWhitePoint10.Yuv[1], refWhitePoint10.Yuv[2]));

  naSetLabelText(
    con->refXYZ2Label,
    naAllocSprintf(NA_TRUE, "%1.05f\n%1.05f\n%1.05f", refWhitePoint2.XYZ[0], refWhitePoint2.XYZ[1], refWhitePoint2.XYZ[2]));
  naSetLabelText(
    con->refYxy2Label,
    naAllocSprintf(NA_TRUE, "%1.05f\n%1.05f\n%1.05f", refWhitePoint2.Yxy[0], refWhitePoint2.Yxy[1], refWhitePoint2.Yxy[2]));
  naSetLabelText(
    con->refYupvp2Label,
    naAllocSprintf(NA_TRUE, "%1.05f\n%1.05f\n%1.05f", refWhitePoint2.Yupvp[0], refWhitePoint2.Yupvp[1], refWhitePoint2.Yupvp[2]));
  naSetLabelText(
    con->refYuv2Label,
    naAllocSprintf(NA_TRUE, "%1.05f\n%1.05f\n%1.05f", refWhitePoint2.Yuv[0], refWhitePoint2.Yuv[1], refWhitePoint2.Yuv[2]));


  // /////////////////////
  // D.4.1 Chromaticity Error
  // /////////////////////

  if(illuminationSpec){
    CMLVec3 chromErrorDistance;
    cmlCpy3(chromErrorDistance, refWhitePoint10.Yupvp);
    cmlSub3(chromErrorDistance, illWhitePoint10.Yupvp);
    float chromError = cmlLength2(&(chromErrorDistance[1]));
    naSetLabelText(
      con->chromaticityLabel,
      naAllocSprintf(NA_TRUE, "%1.05f\n", chromError));
  }else{
    naSetLabelText(
      con->chromaticityLabel,
      "");
  }



  // Color Rendering Index
  
  CMColorRenderingColors colorRenderingColors = cmComputeColorRenderingColors(
    observer2Funcs,
    &refWhitePoint2,
    &illWhitePoint2,
    ref);

  naSetLabelText(
    con->colorRendering1Label,
    naAllocSprintf(NA_TRUE, "%3.03f", colorRenderingColors.colorRenderingIndex[0]));
  cmSetTwoColorControllerColors(
    con->colorRendering1Display,
    colorRenderingColors.crMetamerRGBFloatData[0],
    colorRenderingColors.crReferenceRGBFloatData[0]);
  cmUpdateTwoColorController(con->colorRendering1Display);
  naSetLabelText(
    con->colorRendering2Label,
    naAllocSprintf(NA_TRUE, "%3.03f", colorRenderingColors.colorRenderingIndex[1]));
  cmSetTwoColorControllerColors(
    con->colorRendering2Display,
    colorRenderingColors.crMetamerRGBFloatData[1],
    colorRenderingColors.crReferenceRGBFloatData[1]);
  cmUpdateTwoColorController(con->colorRendering2Display);
  naSetLabelText(
    con->colorRendering3Label,
    naAllocSprintf(NA_TRUE, "%3.03f", colorRenderingColors.colorRenderingIndex[2]));
  cmSetTwoColorControllerColors(
    con->colorRendering3Display,
    colorRenderingColors.crMetamerRGBFloatData[2],
    colorRenderingColors.crReferenceRGBFloatData[2]);
  cmUpdateTwoColorController(con->colorRendering3Display);
  naSetLabelText(
    con->colorRendering4Label,
    naAllocSprintf(NA_TRUE, "%3.03f", colorRenderingColors.colorRenderingIndex[3]));
  cmSetTwoColorControllerColors(
    con->colorRendering4Display,
    colorRenderingColors.crMetamerRGBFloatData[3],
    colorRenderingColors.crReferenceRGBFloatData[3]);
  cmUpdateTwoColorController(con->colorRendering4Display);
  naSetLabelText(
    con->colorRendering5Label,
    naAllocSprintf(NA_TRUE, "%3.03f", colorRenderingColors.colorRenderingIndex[4]));
  cmSetTwoColorControllerColors(
    con->colorRendering5Display,
    colorRenderingColors.crMetamerRGBFloatData[4],
    colorRenderingColors.crReferenceRGBFloatData[4]);
  cmUpdateTwoColorController(con->colorRendering5Display);
  naSetLabelText(
    con->colorRendering6Label,
    naAllocSprintf(NA_TRUE, "%3.03f", colorRenderingColors.colorRenderingIndex[5]));
  cmSetTwoColorControllerColors(
    con->colorRendering6Display,
    colorRenderingColors.crMetamerRGBFloatData[5],
    colorRenderingColors.crReferenceRGBFloatData[5]);
  cmUpdateTwoColorController(con->colorRendering6Display);
  naSetLabelText(
    con->colorRendering7Label,
    naAllocSprintf(NA_TRUE, "%3.03f", colorRenderingColors.colorRenderingIndex[6]));
  cmSetTwoColorControllerColors(
    con->colorRendering7Display,
    colorRenderingColors.crMetamerRGBFloatData[6],
    colorRenderingColors.crReferenceRGBFloatData[6]);
  cmUpdateTwoColorController(con->colorRendering7Display);
  naSetLabelText(
    con->colorRendering8Label,
    naAllocSprintf(NA_TRUE, "%3.03f", colorRenderingColors.colorRenderingIndex[7]));
  cmSetTwoColorControllerColors(
    con->colorRendering8Display,
    colorRenderingColors.crMetamerRGBFloatData[7],
    colorRenderingColors.crReferenceRGBFloatData[7]);
  cmUpdateTwoColorController(con->colorRendering8Display);

  float colorRenderingAverage = 
    colorRenderingColors.colorRenderingIndex[0]
    + colorRenderingColors.colorRenderingIndex[1]
    + colorRenderingColors.colorRenderingIndex[2]
    + colorRenderingColors.colorRenderingIndex[3]
    + colorRenderingColors.colorRenderingIndex[4]
    + colorRenderingColors.colorRenderingIndex[5]
    + colorRenderingColors.colorRenderingIndex[6]
    + colorRenderingColors.colorRenderingIndex[7];
  colorRenderingAverage /= 8.f;

  naSetLabelText(con->colorRenderingLabel, naAllocSprintf(NA_TRUE, "%3.03f", colorRenderingAverage));

  naSetLabelText(
    con->colorRendering9Label,
    naAllocSprintf(NA_TRUE, "%3.03f", colorRenderingColors.colorRenderingIndex[8]));
  cmSetTwoColorControllerColors(
    con->colorRendering9Display,
    colorRenderingColors.crMetamerRGBFloatData[8],
    colorRenderingColors.crReferenceRGBFloatData[8]);
  cmUpdateTwoColorController(con->colorRendering9Display);
  naSetLabelText(
    con->colorRendering10Label,
    naAllocSprintf(NA_TRUE, "%3.03f", colorRenderingColors.colorRenderingIndex[9]));
  cmSetTwoColorControllerColors(
    con->colorRendering10Display,
    colorRenderingColors.crMetamerRGBFloatData[9],
    colorRenderingColors.crReferenceRGBFloatData[9]);
  cmUpdateTwoColorController(con->colorRendering10Display);
  naSetLabelText(
    con->colorRendering11Label,
    naAllocSprintf(NA_TRUE, "%3.03f", colorRenderingColors.colorRenderingIndex[10]));
  cmSetTwoColorControllerColors(
    con->colorRendering11Display,
    colorRenderingColors.crMetamerRGBFloatData[10],
    colorRenderingColors.crReferenceRGBFloatData[10]);
  cmUpdateTwoColorController(con->colorRendering11Display);
  naSetLabelText(
    con->colorRendering12Label,
    naAllocSprintf(NA_TRUE, "%3.03f", colorRenderingColors.colorRenderingIndex[11]));
  cmSetTwoColorControllerColors(
    con->colorRendering12Display,
    colorRenderingColors.crMetamerRGBFloatData[11],
    colorRenderingColors.crReferenceRGBFloatData[11]);
  cmUpdateTwoColorController(con->colorRendering12Display);
  naSetLabelText(
    con->colorRendering13Label,
    naAllocSprintf(NA_TRUE, "%3.03f", colorRenderingColors.colorRenderingIndex[12]));
  cmSetTwoColorControllerColors(
    con->colorRendering13Display,
    colorRenderingColors.crMetamerRGBFloatData[12],
    colorRenderingColors.crReferenceRGBFloatData[12]);
  cmUpdateTwoColorController(con->colorRendering13Display);
  naSetLabelText(
    con->colorRendering14Label,
    naAllocSprintf(NA_TRUE, "%3.03f", colorRenderingColors.colorRenderingIndex[13]));
  cmSetTwoColorControllerColors(
    con->colorRendering14Display,
    colorRenderingColors.crMetamerRGBFloatData[13],
    colorRenderingColors.crReferenceRGBFloatData[13]);
  cmUpdateTwoColorController(con->colorRendering14Display);


  // Visible Range Metamerics

  CMVisMetamericColors visMetamericColors = cmComputeVisMetamericColors(
    observer10Funcs,
    &illWhitePoint10,
    adaptationMatrix,
    con->referenceIlluminationType);

  naSetLabelText(
    con->visMetamerics1Label,
    naAllocSprintf(NA_TRUE, "%1.04f", visMetamericColors.metamericIndex[0]));
  cmSetTwoColorControllerColors(
    con->visMetamerics1Display,
    visMetamericColors.visMetamerRGBFloatData[0],
    visMetamericColors.visStandardRGBFloatData[0]);
  cmUpdateTwoColorController(con->visMetamerics1Display);

  naSetLabelText(
    con->visMetamerics2Label,
    naAllocSprintf(NA_TRUE, "%1.04f", visMetamericColors.metamericIndex[1]));
  cmSetTwoColorControllerColors(
    con->visMetamerics2Display,
    visMetamericColors.visMetamerRGBFloatData[1],
    visMetamericColors.visStandardRGBFloatData[1]);
  cmUpdateTwoColorController(con->visMetamerics2Display);

  naSetLabelText(
    con->visMetamerics3Label,
    naAllocSprintf(NA_TRUE, "%1.04f", visMetamericColors.metamericIndex[2]));
  cmSetTwoColorControllerColors(
    con->visMetamerics3Display,
    visMetamericColors.visMetamerRGBFloatData[2],
    visMetamericColors.visStandardRGBFloatData[2]);
  cmUpdateTwoColorController(con->visMetamerics3Display);

  naSetLabelText(
    con->visMetamerics4Label,
    naAllocSprintf(NA_TRUE, "%1.04f", visMetamericColors.metamericIndex[3]));
  cmSetTwoColorControllerColors(
    con->visMetamerics4Display,
    visMetamericColors.visMetamerRGBFloatData[3],
    visMetamericColors.visStandardRGBFloatData[3]);
  cmUpdateTwoColorController(con->visMetamerics4Display);

  naSetLabelText(
    con->visMetamerics5Label,
    naAllocSprintf(NA_TRUE, "%1.04f", visMetamericColors.metamericIndex[4]));
  cmSetTwoColorControllerColors(
    con->visMetamerics5Display,
    visMetamericColors.visMetamerRGBFloatData[4],
    visMetamericColors.visStandardRGBFloatData[4]);
  cmUpdateTwoColorController(con->visMetamerics5Display);

  float avg5 = visMetamericColors.metamericIndex[0]
    + visMetamericColors.metamericIndex[1]
    + visMetamericColors.metamericIndex[2]
    + visMetamericColors.metamericIndex[3]
    + visMetamericColors.metamericIndex[4];
  avg5 /= 5.f;

  naSetLabelText(con->visMetamericsLabel, naAllocSprintf(NA_TRUE, "%1.04f", avg5));
  naSetLabelText(con->visMetamericsGradeLabel, getGrade(avg5));



  // UV Metamerics
  
  CMUVMetamericColors uvMetamericColors = cmComputeUVMetamericColors(
    observer10Funcs,
    &illWhitePoint10,
    con->referenceIlluminationType);

  naSetLabelText(
    con->uvMetamerics6Label,
    naAllocSprintf(NA_TRUE, "%1.04f", uvMetamericColors.metamericIndex[0]));
  cmSetTwoColorControllerColors(
    con->uvMetamerics6Display,
    uvMetamericColors.uvMetamerRGBFloatData[0],
    uvMetamericColors.uvStandardRGBFloatData[0]);
  cmUpdateTwoColorController(con->uvMetamerics6Display);

  naSetLabelText(
    con->uvMetamerics7Label,
    naAllocSprintf(NA_TRUE, "%1.04f", uvMetamericColors.metamericIndex[1]));
  cmSetTwoColorControllerColors(
    con->uvMetamerics7Display,
    uvMetamericColors.uvMetamerRGBFloatData[1],
    uvMetamericColors.uvStandardRGBFloatData[1]);
  cmUpdateTwoColorController(con->uvMetamerics7Display);
  
  naSetLabelText(
    con->uvMetamerics8Label,
    naAllocSprintf(NA_TRUE, "%1.04f", uvMetamericColors.metamericIndex[2]));
  cmSetTwoColorControllerColors(
    con->uvMetamerics8Display,
    uvMetamericColors.uvMetamerRGBFloatData[2],
    uvMetamericColors.uvStandardRGBFloatData[2]);
  cmUpdateTwoColorController(con->uvMetamerics8Display);

  float avg3 = uvMetamericColors.metamericIndex[0]
    + uvMetamericColors.metamericIndex[1]
    + uvMetamericColors.metamericIndex[2];
  avg3 /= 3.f;

  naSetLabelText(con->uvMetamericsLabel, naAllocSprintf(NA_TRUE, "%1.04f", avg3));
  naSetLabelText(con->uvMetamericsGradeLabel, getGrade(avg3));



  // Total Metamerics
  
  float avg53 = (avg5 * 5.f + avg3 * 3.f) / 8.f;
  if(illuminationSpec){
    naSetLabelText(con->totalMetamericsLabel, naAllocSprintf(NA_TRUE, "%1.04f", avg53));
  }else{
    naSetLabelText(con->totalMetamericsLabel, "");
  }

  naSetLabelText(con->totalMetamericsGradeLabel, getGrade(avg53));

  cmlReleaseFunction(observer10Funcs[0]);
  cmlReleaseFunction(observer10Funcs[1]);
  cmlReleaseFunction(observer10Funcs[2]);
}
