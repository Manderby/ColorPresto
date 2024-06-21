
#include "CPChromaticityErrorController.h"

#include "../CPDesign.h"
#include "../CPTranslations.h"
#include "CPWhitePoints.h"

#include "NAApp/NAApp.h"
#include "NAUtility/NABinaryData.h"
#include "NAUtility/NAMemory.h"
#include "NAUtility/NAString.h"


struct CPChromaticityErrorController{
  NASpace* space;

  NALabel* title;
  NALabel* chromaticityErrorLabel;
};



CPChromaticityErrorController* cpAllocChromaticityErrorController(void){
  CPChromaticityErrorController* con = naAlloc(CPChromaticityErrorController);

  con->space = naNewSpace(naMakeSize(1, 1));

  con->title = cpNewTitleLabel(cpTranslate(CPChromaticityErrorTitle), 160.);
  con->chromaticityErrorLabel = cpNewValueLabel();

  cpBeginUILayout(
    con->space,
    naMakeBorder2D(spaceMarginDegreeLeft, spaceMarginRight, spaceMarginBottom, spaceMarginTop));
  cpAddUIRow(con->title, uiElemHeight);
  cpAddUICol(con->chromaticityErrorLabel, marginH);
  
  cpEndUILayout();

  return con;
}



void cpDeallocChromaticityErrorController(CPChromaticityErrorController* con){
  naFree(con);
}



NASpace* cpGetChromaticityErrorUIElement(CPChromaticityErrorController* con){
  return con->space;
}



void cpUpdateChromaticityErrorController(
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
