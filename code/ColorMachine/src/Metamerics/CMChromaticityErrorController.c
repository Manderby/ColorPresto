
#include "CMChromaticityErrorController.h"

#include "CMDesign.h"
#include "CMTranslations.h"
#include "CMWhitePoints.h"

#include "NAApp.h"
#include "NAUtility/NABinaryData.h"
#include "NAUtility/NAMemory.h"
#include "NAUtility/NAString.h"


struct CMChromaticityErrorController{
  NASpace* space;

  NALabel* title;
  NALabel* chromaticityErrorLabel;
};



CMChromaticityErrorController* cmAllocChromaticityErrorController(void){
  CMChromaticityErrorController* con = naAlloc(CMChromaticityErrorController);

  con->space = naNewSpace(naMakeSize(1, 1));

  con->title = cmNewTitleLabel(cmTranslate(CMChromaticityErrorTitle), 160.);
  con->chromaticityErrorLabel = cmNewValueLabel();

  cmBeginUILayout(
    con->space,
    naMakeBezel4(spaceMarginRight, spaceMarginTop, spaceMarginDegreeLeft, spaceMarginBottom));
  cmAddUIRow(con->title, uiElemHeight);
  cmAddUICol(con->chromaticityErrorLabel, marginH);
  
  cmEndUILayout();

  return con;
}



void cmDeallocChromaticityErrorController(CMChromaticityErrorController* con){
  naFree(con);
}



NASpace* cmGetChromaticityErrorUIElement(CMChromaticityErrorController* con){
  return con->space;
}



void cmUpdateChromaticityErrorController(
  CMChromaticityErrorController* con,
  const CMWhitePoints* refWhitePoint10,
  const CMWhitePoints* illWhitePoint10)
{
  CMLVec3 chromErrorDistance;
  cmlCpy3(chromErrorDistance, refWhitePoint10->Yupvp);
  cmlSub3(chromErrorDistance, illWhitePoint10->Yupvp);
  float chromError = cmlLength2(&(chromErrorDistance[1]));
  naSetLabelText(
    con->chromaticityErrorLabel,
    naAllocSprintf(NA_TRUE, "%1.05f\n", chromError));
}
