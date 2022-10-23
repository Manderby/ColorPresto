
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
  naZeron(con, sizeof(CMChromaticityErrorController));

  double chromaticityTitleWidth = 150.;
  double spaceWidth = chromaticityTitleWidth + marginH + valueWidth;
  double spaceHeight = uiElemHeight + spaceMarginV;

  con->space = naNewSpace(naMakeSize(spaceWidth, spaceHeight));
//  naSetSpaceAlternateBackground(con->space, NA_TRUE);

  con->title = cmNewTitleLabel(cmTranslate(CMChromaticityErrorTitle), chromaticityTitleWidth);
  con->chromaticityErrorLabel = cmNewValueLabel();

  double chromaticityY = spaceHeight - spaceMarginTop;
  chromaticityY -= uiElemHeight;
  naAddSpaceChild(con->space, con->title, naMakePos(0, chromaticityY));
  naAddSpaceChild(con->space, con->chromaticityErrorLabel, naMakePos(chromaticityTitleWidth + marginH, chromaticityY));

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
  const CMWhitePoints* illWhitePoint10,
  NABool valid)
{
  if(valid){
    CMLVec3 chromErrorDistance;
    cmlCpy3(chromErrorDistance, refWhitePoint10->Yupvp);
    cmlSub3(chromErrorDistance, illWhitePoint10->Yupvp);
    float chromError = cmlLength2(&(chromErrorDistance[1]));
    naSetLabelText(
      con->chromaticityErrorLabel,
      naAllocSprintf(NA_TRUE, "%1.05f\n", chromError));
  }else{
    naSetLabelText(
      con->chromaticityErrorLabel,
      "");
  }
}
