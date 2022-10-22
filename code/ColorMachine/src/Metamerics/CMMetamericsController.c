
#include "CMMetamericsController.h"
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
static const double colorWidth = 160.;
static const double columnWidth = marginHLeft + indexWidth + valueWidth + colorWidth + 2 * marginH + marginHRight;

static const double valueLeft = marginHLeft + indexWidth + marginH;
static const double colorLeft = valueLeft + valueWidth + marginH;



NAFont* monoFont;

struct CMMetamericsController{
  NAWindow* window;
  
  NASpace* illSpace;
  NALabel* illXYZXLabel;
  NALabel* illYxyYLabel;
  NALabel* illYupvpYLabel;
  NALabel* illYuvYLabel;
  
  NASpace* refSpace;

  NAPopupButton* refPopupButton;

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



CMMetamericsController* cmAllocMetamericsController(void){
  monoFont = naCreateFontWithPreset(NA_FONT_KIND_MONOSPACE, NA_FONT_SIZE_DEFAULT);
//  monoFont = naCreateFont("Andale Mono", NA_FONT_FLAG_REGULAR, 12.5);

  CMMetamericsController* con = naAlloc(CMMetamericsController);
  naZeron(con, sizeof(CMMetamericsController));

  NAFont* boldFont = naCreateFontWithPreset(NA_FONT_KIND_TITLE, NA_FONT_SIZE_DEFAULT);

  const double illSpaceHeight = 3 * 25 + 2 * threeValueHeight + marginYTop + marginYBottom;
  const double refSpaceHeight = 3 * 25 + 2 * threeValueHeight + marginYTop + marginYBottom;
  const double chromaticitySpaceHeight = 1 * 25 + marginYTop + marginYBottom;
  const double visMetamericsSpaceHeight = 7 * 25 + marginYTop + marginYBottom;
  const double uvMetamericsSpaceHeight = 5 * 25 + marginYTop + marginYBottom;
  const double totalMetamericsSpaceHeight = 2 * 25 + marginYTop + marginYBottom;

  con->window = naNewWindow(
    cmTranslate(CMWhitepointsAndMetamerics),
    naMakeRectS(
      600,
      500,
      2 * columnWidth,
      refSpaceHeight + chromaticitySpaceHeight + visMetamericsSpaceHeight + uvMetamericsSpaceHeight + totalMetamericsSpaceHeight),
    0,
    0);
  NASpace* contentSpace = naGetWindowContentSpace(con->window);




  // Illumination whitepoint
  con->illSpace = naNewSpace(naMakeSize(columnWidth, illSpaceHeight));
  naSetSpaceAlternateBackground(con->illSpace, NA_FALSE);

  con->illXYZXLabel = cmNewValueLabel();
  con->illYxyYLabel = cmNewValueLabel();
  con->illYupvpYLabel = cmNewValueLabel();
  con->illYuvYLabel = cmNewValueLabel();



  // Reference whitepoint
  con->refSpace = naNewSpace(naMakeSize(columnWidth, refSpaceHeight));
  naSetSpaceAlternateBackground(con->refSpace, NA_TRUE);

  con->refPopupButton = naNewPopupButton(60);

  con->refXYZTitle = naNewLabel("XYZ", valueWidth);
  naSetLabelTextAlignment(con->refXYZTitle, NA_TEXT_ALIGNMENT_CENTER);
  con->refYxyTitle = naNewLabel("Yxy", valueWidth);
  naSetLabelTextAlignment(con->refYxyTitle, NA_TEXT_ALIGNMENT_CENTER);
  con->refYupvpTitle = naNewLabel("Yu'v'", valueWidth);
  naSetLabelTextAlignment(con->refYupvpTitle, NA_TEXT_ALIGNMENT_CENTER);
  con->refYuvTitle = naNewLabel("Yuv", valueWidth);
  naSetLabelTextAlignment(con->refYuvTitle, NA_TEXT_ALIGNMENT_CENTER);

  con->refXYZ10Label = cmNewThreeValueLabel();
  con->refYxy10Label = cmNewThreeValueLabel();
  con->refYupvp10Label = cmNewThreeValueLabel();
  con->refYuv10Label = cmNewThreeValueLabel();
  
  con->refXYZ2Label = cmNewThreeValueLabel();
  con->refYxy2Label = cmNewThreeValueLabel();
  con->refYupvp2Label = cmNewThreeValueLabel();
  con->refYuv2Label = cmNewThreeValueLabel();
  


  // Chromaticity error
  con->chromaticitySpace = naNewSpace(naMakeSize(columnWidth, chromaticitySpaceHeight));
  naSetSpaceAlternateBackground(con->chromaticitySpace, NA_FALSE);

  con->chromaticityTitle = naNewLabel("Chromaticity error:", 250);
  naSetLabelFont(con->chromaticityTitle, boldFont);



  // visible range metamerics
  con->visMetamericsSpace = naNewSpace(naMakeSize(columnWidth, visMetamericsSpaceHeight));
  naSetSpaceAlternateBackground(con->visMetamericsSpace, NA_TRUE);
  
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
//  naSetLabelTextAlignment(con->visMetamericsLabel, NA_TEXT_ALIGNMENT_RIGHT);
  con->visMetamericsGradeLabel = naNewLabel("Grade A", 120);


  // UV metamerics
  con->uvMetamericsSpace = naNewSpace(naMakeSize(columnWidth, uvMetamericsSpaceHeight));
  naSetSpaceAlternateBackground(con->uvMetamericsSpace, NA_TRUE);

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
//  naSetLabelTextAlignment(con->uvMetamericsLabel, NA_TEXT_ALIGNMENT_RIGHT);
  con->uvMetamericsGradeLabel = naNewLabel("Grade A", 120);


  // Total metamerics
  con->totalMetamericsSpace = naNewSpace(naMakeSize(columnWidth, totalMetamericsSpaceHeight));
  naSetSpaceAlternateBackground(con->totalMetamericsSpace, NA_TRUE);

  con->totalMetamericsTitle = naNewLabel("Total Metameric Index (Average 1-8):", 250);
  naSetLabelFont(con->totalMetamericsTitle, boldFont);
  con->totalMetamericsAverageLabel = naNewLabel("Avg:", 120);
  con->totalMetamericsLabel = cmNewValueLabel();
//  naSetLabelTextAlignment(con->totalMetamericsLabel, NA_TEXT_ALIGNMENT_RIGHT);
  con->totalMetamericsGradeLabel = naNewLabel("Grade A", 120);



  // Placing elements in the window
  
  NASize contentSpaceSize = naGetUIElementRect(contentSpace, NA_NULL, NA_FALSE).size;
  double y = contentSpaceSize.height;
  


  double illY = illSpaceHeight - marginYTop;
  illY -= 25;
  // add dropdown
  illY -= 25;
  // add title
  illY -= 25;
  naAddSpaceChild(con->illSpace, con->illXYZXLabel, naMakePos(marginHLeft + 0 * (valueWidth + margin2H), illY));
  naAddSpaceChild(con->illSpace, con->illYxyYLabel, naMakePos(marginHLeft + 1 * (valueWidth + margin2H), illY));
  naAddSpaceChild(con->illSpace, con->illYupvpYLabel, naMakePos(marginHLeft + 2 * (valueWidth + margin2H), illY));
  naAddSpaceChild(con->illSpace, con->illYuvYLabel, naMakePos(marginHLeft + 3 * (valueWidth + margin2H), illY));
  illY -= 15;
  // add [1] of 2deg
  illY -= 15;
  // add [2] of 2deg
  illY -= 50;
  // add [0] of 10deg
  illY -= 15;
  // add [1] of 10deg
  illY -= 15;
  // add [2] of 10deg

  y -= illSpaceHeight;
  naAddSpaceChild(contentSpace, con->illSpace, naMakePos(0, y));



  double refY = refSpaceHeight - marginYTop;
  refY -= 25;
  // add dropdown
  refY -= 25;
  naAddSpaceChild(con->refSpace, con->refXYZTitle, naMakePos(marginHLeft + 0 * (valueWidth + margin2H) - 3, refY));
  naAddSpaceChild(con->refSpace, con->refYxyTitle, naMakePos(marginHLeft + 1 * (valueWidth + margin2H) - 3, refY));
  naAddSpaceChild(con->refSpace, con->refYupvpTitle, naMakePos(marginHLeft + 2 * (valueWidth + margin2H) - 3, refY));
  naAddSpaceChild(con->refSpace, con->refYuvTitle, naMakePos(marginHLeft + 3 * (valueWidth + margin2H) - 3, refY));
  refY -= 25;
  naAddSpaceChild(con->refSpace, con->refXYZ10Label, naMakePos(marginHLeft + 0 * (valueWidth + margin2H), refY - 35));
  naAddSpaceChild(con->refSpace, con->refYxy10Label, naMakePos(marginHLeft + 1 * (valueWidth + margin2H), refY - 35));
  naAddSpaceChild(con->refSpace, con->refYupvp10Label, naMakePos(marginHLeft + 2 * (valueWidth + margin2H), refY - 35));
  naAddSpaceChild(con->refSpace, con->refYuv10Label, naMakePos(marginHLeft + 3 * (valueWidth + margin2H), refY - 35));

  refY -= (threeValueHeight + 25);
  naAddSpaceChild(con->refSpace, con->refXYZ2Label, naMakePos(marginHLeft + 0 * (valueWidth + margin2H), refY - 35));
  naAddSpaceChild(con->refSpace, con->refYxy2Label, naMakePos(marginHLeft + 1 * (valueWidth + margin2H), refY - 35));
  naAddSpaceChild(con->refSpace, con->refYupvp2Label, naMakePos(marginHLeft + 2 * (valueWidth + margin2H), refY - 35));
  naAddSpaceChild(con->refSpace, con->refYuv2Label, naMakePos(marginHLeft + 3 * (valueWidth + margin2H), refY - 35));

  naAddSpaceChild(contentSpace, con->refSpace, naMakePos(columnWidth, y));

  

  double chromaticityY = chromaticitySpaceHeight - marginYTop;
  chromaticityY -= 25;
  naAddSpaceChild(con->chromaticitySpace, con->chromaticityTitle, naMakePos(marginHLeft, chromaticityY));

  y -= chromaticitySpaceHeight;
  naAddSpaceChild(contentSpace, con->chromaticitySpace, naMakePos(0, y));



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

  y -= visMetamericsSpaceHeight;
  naAddSpaceChild(contentSpace, con->visMetamericsSpace, naMakePos(columnWidth, y));



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

  y -= uvMetamericsSpaceHeight;
  naAddSpaceChild(contentSpace, con->uvMetamericsSpace, naMakePos(columnWidth, y));



  double totalMetamericsY = totalMetamericsSpaceHeight - marginYTop;
  totalMetamericsY -= 25;

  naAddSpaceChild(con->totalMetamericsSpace, con->totalMetamericsTitle, naMakePos(marginHLeft, totalMetamericsY));
 
  totalMetamericsY -= 25;
  naAddSpaceChild(con->totalMetamericsSpace, con->totalMetamericsAverageLabel, naMakePos(marginHLeft, totalMetamericsY));
  naAddSpaceChild(con->totalMetamericsSpace, con->totalMetamericsLabel, naMakePos(valueLeft, totalMetamericsY));
  naAddSpaceChild(con->totalMetamericsSpace, con->totalMetamericsGradeLabel, naMakePos(colorLeft, totalMetamericsY));

  y -= totalMetamericsSpaceHeight;
  naAddSpaceChild(contentSpace, con->totalMetamericsSpace, naMakePos(columnWidth, y));



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
//  CMLColorMachine* sm = cmGetCurrentScreenMachine();

  CMLFunction* observer10Funcs[3];
  cmlCreateSpecDistFunctions(observer10Funcs, CML_DEFAULT_10DEG_OBSERVER);
  CMLFunction* observer2Funcs[3];
  cmlCreateSpecDistFunctions(observer2Funcs, CML_DEFAULT_2DEG_OBSERVER);
  const CMLFunction* illuminationSpec = cmlGetReferenceIlluminationSpectrum(cm);

  const CMLFunction* ref;
  switch(con->referenceIlluminationType){
  default:  // Default should not happen.
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
  }

  CMWhitePoints illWhitePoint10 = CMGetWhitePoints(
    illuminationSpec,
    cmlGetReferenceWhitePointYxy(cm),
    observer10Funcs);
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



  // Visible Range Metamerics

  VisMetamericColors visMetamericColors = cmComputeVisMetamericColors(
    observer10Funcs,
    &illWhitePoint10,
    adaptationMatrix,
    con->referenceIlluminationType);

  naSetLabelText(
    con->visMetamerics1Label,
    naAllocSprintf(NA_TRUE, "%1.04f", visMetamericColors.metamericIndex[0]));
  cmSetTwoColorControllerColors(
    con->visMetamerics1Display,
    visMetamericColors.visStandardRGBFloatData[0],
    visMetamericColors.visMetamerRGBFloatData[0]);
  cmUpdateTwoColorController(con->visMetamerics1Display);

  naSetLabelText(
    con->visMetamerics2Label,
    naAllocSprintf(NA_TRUE, "%1.04f", visMetamericColors.metamericIndex[1]));
  cmSetTwoColorControllerColors(
    con->visMetamerics2Display,
    visMetamericColors.visStandardRGBFloatData[1],
    visMetamericColors.visMetamerRGBFloatData[1]);
  cmUpdateTwoColorController(con->visMetamerics2Display);

  naSetLabelText(
    con->visMetamerics3Label,
    naAllocSprintf(NA_TRUE, "%1.04f", visMetamericColors.metamericIndex[2]));
  cmSetTwoColorControllerColors(
    con->visMetamerics3Display,
    visMetamericColors.visStandardRGBFloatData[2],
    visMetamericColors.visMetamerRGBFloatData[2]);
  cmUpdateTwoColorController(con->visMetamerics3Display);

  naSetLabelText(
    con->visMetamerics4Label,
    naAllocSprintf(NA_TRUE, "%1.04f", visMetamericColors.metamericIndex[3]));
  cmSetTwoColorControllerColors(
    con->visMetamerics4Display,
    visMetamericColors.visStandardRGBFloatData[3],
    visMetamericColors.visMetamerRGBFloatData[3]);
  cmUpdateTwoColorController(con->visMetamerics4Display);

  naSetLabelText(
    con->visMetamerics5Label,
    naAllocSprintf(NA_TRUE, "%1.04f", visMetamericColors.metamericIndex[4]));
  cmSetTwoColorControllerColors(
    con->visMetamerics5Display,
    visMetamericColors.visStandardRGBFloatData[4],
    visMetamericColors.visMetamerRGBFloatData[4]);
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
  
  UVMetamericColors uvMetamericColors = cmComputeUVMetamericColors(
    observer10Funcs,
    &illWhitePoint10,
    con->referenceIlluminationType);

  naSetLabelText(
    con->uvMetamerics6Label,
    naAllocSprintf(NA_TRUE, "%1.04f", uvMetamericColors.metamericIndex[0]));
  cmSetTwoColorControllerColors(
    con->uvMetamerics6Display,
    uvMetamericColors.uvStandardRGBFloatData[0],
    uvMetamericColors.uvMetamerRGBFloatData[0]);
  cmUpdateTwoColorController(con->uvMetamerics6Display);

  naSetLabelText(
    con->uvMetamerics7Label,
    naAllocSprintf(NA_TRUE, "%1.04f", uvMetamericColors.metamericIndex[1]));
  cmSetTwoColorControllerColors(
    con->uvMetamerics7Display,
    uvMetamericColors.uvStandardRGBFloatData[1],
    uvMetamericColors.uvMetamerRGBFloatData[1]);
  cmUpdateTwoColorController(con->uvMetamerics7Display);
  
  naSetLabelText(
    con->uvMetamerics8Label,
    naAllocSprintf(NA_TRUE, "%1.04f", uvMetamericColors.metamericIndex[2]));
  cmSetTwoColorControllerColors(
    con->uvMetamerics8Display,
    uvMetamericColors.uvStandardRGBFloatData[2],
    uvMetamericColors.uvMetamerRGBFloatData[2]);
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
