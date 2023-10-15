
#include "CPChromaticityErrorController.h"

#include "../CPDesign.h"
#include "../CPTranslations.h"
#include "CPWhitePoints.h"

#include "NAApp.h"
#include "NAUtility/NABinaryData.h"
#include "NAUtility/NAMemory.h"
#include "NAUtility/NAString.h"


struct CPChromaticityErrorController{
  NASpace* space;

  NALabel* title;
  NALabel* chromaticityErrorLabel;
};



CPChromaticityErrorController* cmAllocChromaticityErrorController(void){
  CPChromaticityErrorController* con = naAlloc(CPChromaticityErrorController);

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



void cmDeallocChromaticityErrorController(CPChromaticityErrorController* con){
  naFree(con);
}



NASpace* cmGetChromaticityErrorUIElement(CPChromaticityErrorController* con){
  return con->space;
}



void cmUpdateChromaticityErrorController(
  CPChromaticityErrorController* con,
  const CPWhitePoints* refWhitePoint10,
  const CPWhitePoints* illWhitePoint10)
{
  CMLVec3 chromErrorDistance;
  cmlCpy3(chromErrorDistance, refWhitePoint10->Yupvp);
  cmlSub3(chromErrorDistance, illWhitePoint10->Yupvp);
  float chromError = cmlLength2(&(chromErrorDistance[1]));
  naSetLabelText(
    con->chromaticityErrorLabel,
    naAllocSprintf(NA_TRUE, "%1.05f\n", chromError));
}
