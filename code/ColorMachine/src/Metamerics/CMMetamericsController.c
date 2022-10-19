
#include "CMMetamericsController.h"
#include "CMTranslations.h"
#include "CMTwoColorController.h"
#include "CMUVMetamericColors.h"
#include "CMVisMetamericColors.h"
#include "CMWhitePoints.h"
#include "NAApp.h"
#include "CML.h"
#include "mainC.h"



struct CMMetamericsController{
  NAWindow* window;
  
  NALabel* VisMetamericsTitle;
  NALabel* VisMetamerics1IndexLabel;
  NALabel* VisMetamerics1Label;
  CMTwoColorController* VisMetamerics1Display;
  NALabel* VisMetamerics2IndexLabel;
  NALabel* VisMetamerics2Label;
  CMTwoColorController* VisMetamerics2Display;
  NALabel* VisMetamerics3IndexLabel;
  NALabel* VisMetamerics3Label;
  CMTwoColorController* VisMetamerics3Display;
  NALabel* VisMetamerics4IndexLabel;
  NALabel* VisMetamerics4Label;
  CMTwoColorController* VisMetamerics4Display;
  NALabel* VisMetamerics5IndexLabel;
  NALabel* VisMetamerics5Label;
  CMTwoColorController* VisMetamerics5Display;
  NALabel* VisMetamericsAverageLabel;
  NALabel* VisMetamericsLabel;
  NALabel* VisMetamericsGradeLabel;

  NALabel* UVMetamericsTitle;
  NALabel* UVMetamerics6IndexLabel;
  NALabel* UVMetamerics6Label;
  CMTwoColorController* UVMetamerics6Display;
  NALabel* UVMetamerics7IndexLabel;
  NALabel* UVMetamerics7Label;
  CMTwoColorController* UVMetamerics7Display;
  NALabel* UVMetamerics8IndexLabel;
  NALabel* UVMetamerics8Label;
  CMTwoColorController* UVMetamerics8Display;
  NALabel* UVMetamericsAverageLabel;
  NALabel* UVMetamericsLabel;
  NALabel* UVMetamericsGradeLabel;

  NALabel* totalMetamericsTitle;
  NALabel* totalMetamericsAverageLabel;
  NALabel* totalMetamericsLabel;
  NALabel* totalMetamericsGradeLabel;

  CMReferenceIlluminationType referenceIlluminationType;
};



const NAUTF8Char* getGrade(float value){
  if(value <= .25f){return "Grade A";}
  else if(value <= .5f){return "Grade B";}
  else if(value <= 1.f){return "Grade C";}
  else if(value <= 2.f){return "Grade D";}
  return "Grade E";
}



CMMetamericsController* cmAllocMetamericsController(void){
  CMMetamericsController* con = naAlloc(CMMetamericsController);
  naZeron(con, sizeof(CMMetamericsController));

  NAFont* boldFont = naCreateFontWithPreset(NA_FONT_KIND_TITLE, NA_FONT_SIZE_DEFAULT);

  con->window = naNewWindow(cmTranslate(CMWhitepointsAndMetamerics), naMakeRectS(20, 500, 500, 500), 0, 0);
  NASpace* contentSpace = naGetWindowContentSpace(con->window);


  // visible range metamerics
  con->VisMetamericsTitle = naNewLabel("Visible Range Metameric Index:", 250);
  naSetLabelFont(con->VisMetamericsTitle, boldFont);
  con->VisMetamerics1IndexLabel = naNewLabel("1:", 20);
  con->VisMetamerics1Label = naNewLabel("", 70);
  con->VisMetamerics1Display = cmAllocTwoColorController(naMakeSize(150, 21));

  con->VisMetamerics2IndexLabel = naNewLabel("2:", 20);
  con->VisMetamerics2Label = naNewLabel("", 70);
  con->VisMetamerics2Display = cmAllocTwoColorController(naMakeSize(150, 21));

  con->VisMetamerics3IndexLabel = naNewLabel("3:", 20);
  con->VisMetamerics3Label = naNewLabel("", 70);
  con->VisMetamerics3Display = cmAllocTwoColorController(naMakeSize(150, 21));

  con->VisMetamerics4IndexLabel = naNewLabel("4:", 20);
  con->VisMetamerics4Label = naNewLabel("", 70);
  con->VisMetamerics4Display = cmAllocTwoColorController(naMakeSize(150, 21));

  con->VisMetamerics5IndexLabel = naNewLabel("5:", 20);
  con->VisMetamerics5Label = naNewLabel("", 70);
  con->VisMetamerics5Display = cmAllocTwoColorController(naMakeSize(150, 21));

  con->VisMetamericsAverageLabel = naNewLabel("Average 1-5:", 120);
  con->VisMetamericsLabel = naNewLabel("", 70);
  naSetLabelTextAlignment(con->VisMetamericsLabel, NA_TEXT_ALIGNMENT_RIGHT);
  con->VisMetamericsGradeLabel = naNewLabel("Grade A", 120);


  // UV metamerics
  con->UVMetamericsTitle = naNewLabel("Ultraviolet Range Metameric Index:", 250);
  naSetLabelFont(con->UVMetamericsTitle, boldFont);

  con->UVMetamerics6IndexLabel = naNewLabel("6:", 20);
  con->UVMetamerics6Label = naNewLabel("", 70);
  con->UVMetamerics6Display = cmAllocTwoColorController(naMakeSize(150, 21));

  con->UVMetamerics7IndexLabel = naNewLabel("7:", 20);
  con->UVMetamerics7Label = naNewLabel("", 70);
  con->UVMetamerics7Display = cmAllocTwoColorController(naMakeSize(150, 21));

  con->UVMetamerics8IndexLabel = naNewLabel("8:", 20);
  con->UVMetamerics8Label = naNewLabel("", 70);
  con->UVMetamerics8Display = cmAllocTwoColorController(naMakeSize(150, 21));

  con->UVMetamericsAverageLabel = naNewLabel("Average 6-8:", 120);
  con->UVMetamericsLabel = naNewLabel("", 70);
  naSetLabelTextAlignment(con->UVMetamericsLabel, NA_TEXT_ALIGNMENT_RIGHT);
  con->UVMetamericsGradeLabel = naNewLabel("Grade A", 120);


  // Total metamerics
  con->totalMetamericsTitle = naNewLabel("Total Metameric Index:", 250);
  naSetLabelFont(con->totalMetamericsTitle, boldFont);
  con->totalMetamericsAverageLabel = naNewLabel("Average 1-8:", 120);
  con->totalMetamericsLabel = naNewLabel("", 70);
  naSetLabelTextAlignment(con->totalMetamericsLabel, NA_TEXT_ALIGNMENT_RIGHT);
  con->totalMetamericsGradeLabel = naNewLabel("Grade A", 120);

  naAddSpaceChild(contentSpace, con->VisMetamericsTitle, naMakePos(10, 400));
  naAddSpaceChild(contentSpace, con->VisMetamerics1IndexLabel, naMakePos(10, 375));
  naAddSpaceChild(contentSpace, con->VisMetamerics1Label, naMakePos(30, 375));
  naAddSpaceChild(contentSpace, cmGetTwoColorControllerUIElement(con->VisMetamerics1Display), naMakePos(110, 375));
  naAddSpaceChild(contentSpace, con->VisMetamerics2IndexLabel, naMakePos(10, 350));
  naAddSpaceChild(contentSpace, con->VisMetamerics2Label, naMakePos(30, 350));
  naAddSpaceChild(contentSpace, cmGetTwoColorControllerUIElement(con->VisMetamerics2Display), naMakePos(110, 350));
  naAddSpaceChild(contentSpace, con->VisMetamerics3IndexLabel, naMakePos(10, 325));
  naAddSpaceChild(contentSpace, con->VisMetamerics3Label, naMakePos(30, 325));
  naAddSpaceChild(contentSpace, cmGetTwoColorControllerUIElement(con->VisMetamerics3Display), naMakePos(110, 325));
  naAddSpaceChild(contentSpace, con->VisMetamerics4IndexLabel, naMakePos(10, 300));
  naAddSpaceChild(contentSpace, con->VisMetamerics4Label, naMakePos(30, 300));
  naAddSpaceChild(contentSpace, cmGetTwoColorControllerUIElement(con->VisMetamerics4Display), naMakePos(110, 300));
  naAddSpaceChild(contentSpace, con->VisMetamerics5IndexLabel, naMakePos(10, 275));
  naAddSpaceChild(contentSpace, con->VisMetamerics5Label, naMakePos(30, 275));
  naAddSpaceChild(contentSpace, cmGetTwoColorControllerUIElement(con->VisMetamerics5Display), naMakePos(110, 275));
  naAddSpaceChild(contentSpace, con->VisMetamericsAverageLabel, naMakePos(10, 250));
  naAddSpaceChild(contentSpace, con->VisMetamericsLabel, naMakePos(110, 250));
  naAddSpaceChild(contentSpace, con->VisMetamericsGradeLabel, naMakePos(190, 250));

  naAddSpaceChild(contentSpace, con->UVMetamericsTitle, naMakePos(10, 200));
  naAddSpaceChild(contentSpace, con->UVMetamerics6IndexLabel, naMakePos(10, 175));
  naAddSpaceChild(contentSpace, con->UVMetamerics6Label, naMakePos(30, 175));
  naAddSpaceChild(contentSpace, cmGetTwoColorControllerUIElement(con->UVMetamerics6Display), naMakePos(110, 175));
  naAddSpaceChild(contentSpace, con->UVMetamerics7IndexLabel, naMakePos(10, 150));
  naAddSpaceChild(contentSpace, con->UVMetamerics7Label, naMakePos(30, 150));
  naAddSpaceChild(contentSpace, cmGetTwoColorControllerUIElement(con->UVMetamerics7Display), naMakePos(110, 150));
  naAddSpaceChild(contentSpace, con->UVMetamerics8IndexLabel, naMakePos(10, 125));
  naAddSpaceChild(contentSpace, con->UVMetamerics8Label, naMakePos(30, 125));
  naAddSpaceChild(contentSpace, cmGetTwoColorControllerUIElement(con->UVMetamerics8Display), naMakePos(110, 125));
  naAddSpaceChild(contentSpace, con->UVMetamericsAverageLabel, naMakePos(10, 100));
  naAddSpaceChild(contentSpace, con->UVMetamericsLabel, naMakePos(110, 100));
  naAddSpaceChild(contentSpace, con->UVMetamericsGradeLabel, naMakePos(190, 100));

  naAddSpaceChild(contentSpace, con->totalMetamericsTitle, naMakePos(10, 50));
  naAddSpaceChild(contentSpace, con->totalMetamericsAverageLabel, naMakePos(10, 25));
  naAddSpaceChild(contentSpace, con->totalMetamericsLabel, naMakePos(110, 25));
  naAddSpaceChild(contentSpace, con->totalMetamericsGradeLabel, naMakePos(190, 25));

  naRelease(boldFont);

  con->referenceIlluminationType = REFERENCE_ILLUMINATION_D50;
  
  return con;
}



void cmDeallocMetamericsController(CMMetamericsController* con){
  naFree(con);
}



void cmShowMetamericsController(CMMetamericsController* con){
  naShowWindow(con->window);
}



void cmUpdateMetamericsController(CMMetamericsController* con){
  CMLColorMachine* cm = cmGetCurrentColorMachine();
//  CMLColorMachine* sm = cmGetCurrentScreenMachine();

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

  CMLFunction* observer10Funcs[3];
  cmlCreateSpecDistFunctions(observer10Funcs, CML_DEFAULT_10DEG_OBSERVER);

  CMWhitePoints wp = CMGetWhitePoints();

  CMLMat33 adaptationMatrix;
  CMFillChromaticAdaptationMatrix(adaptationMatrix, wp.illYxy10);



  // Visible Range Metamerics

  VisMetamericColors visMetamericColors = cmComputeVisMetamericColors(
    observer10Funcs,
    &wp,
    adaptationMatrix,
    con->referenceIlluminationType);

  naSetLabelText(
    con->VisMetamerics1Label,
    naAllocSprintf(NA_TRUE, "%1.04f", visMetamericColors.metamericIndex[0]));
  cmSetTwoColorControllerColors(
    con->VisMetamerics1Display,
    visMetamericColors.visStandardRGBFloatData[0],
    visMetamericColors.visMetamerRGBFloatData[0]);
  cmUpdateTwoColorController(con->VisMetamerics1Display);

  naSetLabelText(
    con->VisMetamerics2Label,
    naAllocSprintf(NA_TRUE, "%1.04f", visMetamericColors.metamericIndex[1]));
  cmSetTwoColorControllerColors(
    con->VisMetamerics2Display,
    visMetamericColors.visStandardRGBFloatData[1],
    visMetamericColors.visMetamerRGBFloatData[1]);
  cmUpdateTwoColorController(con->VisMetamerics2Display);

  naSetLabelText(
    con->VisMetamerics3Label,
    naAllocSprintf(NA_TRUE, "%1.04f", visMetamericColors.metamericIndex[2]));
  cmSetTwoColorControllerColors(
    con->VisMetamerics3Display,
    visMetamericColors.visStandardRGBFloatData[2],
    visMetamericColors.visMetamerRGBFloatData[2]);
  cmUpdateTwoColorController(con->VisMetamerics3Display);

  naSetLabelText(
    con->VisMetamerics4Label,
    naAllocSprintf(NA_TRUE, "%1.04f", visMetamericColors.metamericIndex[3]));
  cmSetTwoColorControllerColors(
    con->VisMetamerics4Display,
    visMetamericColors.visStandardRGBFloatData[3],
    visMetamericColors.visMetamerRGBFloatData[3]);
  cmUpdateTwoColorController(con->VisMetamerics4Display);

  naSetLabelText(
    con->VisMetamerics5Label,
    naAllocSprintf(NA_TRUE, "%1.04f", visMetamericColors.metamericIndex[4]));
  cmSetTwoColorControllerColors(
    con->VisMetamerics5Display,
    visMetamericColors.visStandardRGBFloatData[4],
    visMetamericColors.visMetamerRGBFloatData[4]);
  cmUpdateTwoColorController(con->VisMetamerics5Display);

  float avg5 = visMetamericColors.metamericIndex[0]
    + visMetamericColors.metamericIndex[1]
    + visMetamericColors.metamericIndex[2]
    + visMetamericColors.metamericIndex[3]
    + visMetamericColors.metamericIndex[4];
  avg5 /= 5.f;

  naSetLabelText(con->VisMetamericsLabel, naAllocSprintf(NA_TRUE, "%1.04f", avg5));
  naSetLabelText(con->VisMetamericsGradeLabel, getGrade(avg5));



  // UV Metamerics
  
  UVMetamericColors uvMetamericColors = cmComputeUVMetamericColors(
    observer10Funcs,
    &wp,
    con->referenceIlluminationType);

  naSetLabelText(
    con->UVMetamerics6Label,
    naAllocSprintf(NA_TRUE, "%1.04f", uvMetamericColors.metamericIndex[0]));
  cmSetTwoColorControllerColors(
    con->UVMetamerics6Display,
    uvMetamericColors.uvStandardRGBFloatData[0],
    uvMetamericColors.uvMetamerRGBFloatData[0]);
  cmUpdateTwoColorController(con->UVMetamerics6Display);

  naSetLabelText(
    con->UVMetamerics7Label,
    naAllocSprintf(NA_TRUE, "%1.04f", uvMetamericColors.metamericIndex[1]));
  cmSetTwoColorControllerColors(
    con->UVMetamerics7Display,
    uvMetamericColors.uvStandardRGBFloatData[1],
    uvMetamericColors.uvMetamerRGBFloatData[1]);
  cmUpdateTwoColorController(con->UVMetamerics7Display);
  
  naSetLabelText(
    con->UVMetamerics8Label,
    naAllocSprintf(NA_TRUE, "%1.04f", uvMetamericColors.metamericIndex[2]));
  cmSetTwoColorControllerColors(
    con->UVMetamerics8Display,
    uvMetamericColors.uvStandardRGBFloatData[2],
    uvMetamericColors.uvMetamerRGBFloatData[2]);
  cmUpdateTwoColorController(con->UVMetamerics8Display);

  float avg3 = uvMetamericColors.metamericIndex[0]
    + uvMetamericColors.metamericIndex[1]
    + uvMetamericColors.metamericIndex[2];
  avg3 /= 3.f;

  naSetLabelText(con->UVMetamericsLabel, naAllocSprintf(NA_TRUE, "%1.04f", avg3));
  naSetLabelText(con->UVMetamericsGradeLabel, getGrade(avg3));



  // Total Metamerics
  
  const CMLFunction* illuminationSpec = cmlGetReferenceIlluminationSpectrum(cm);

  float avg53 = (avg5 * 5.f + avg3 * 3.f) / 8.f;
  if(illuminationSpec){
    naSetLabelText(con->totalMetamericsLabel, naAllocSprintf(NA_TRUE, "%1.04f", avg53));
  }else{
    naSetLabelText(con->totalMetamericsLabel, "");
  }

  naSetLabelText(con->totalMetamericsGradeLabel, getGrade(avg53));
}
