
#include "CMTotalMetamericIndexController.h"

#include "CMColorConversionsYcdUVW.h"
#include "CMDesign.h"
#include "CMTranslations.h"

#include "NAApp.h"


struct CMTotalMetamericIndexController{
  NASpace* space;

  NALabel* title;
  NALabel* metamericsAverageLabel;
  NALabel* metamericsLabel;
  NALabel* metamericsGradeLabel;
};



CMTotalMetamericIndexController* cmAllocTotalMetamericIndexController(void){
  CMTotalMetamericIndexController* con = naAlloc(CMTotalMetamericIndexController);
  naZeron(con, sizeof(CMTotalMetamericIndexController));

  double marginH1 = 0.;
  double marginH2 = 5.;

  double spaceWidth = spaceMarginLeft + indexWidth + marginH1 + valueWidth + marginH2 + twoColorWidth + spaceMarginRight;
  double spaceHeight = 2 * uiElemHeight + spaceMarginV;

  double valueLeft = spaceMarginLeft + indexWidth + marginH1;
  double colorLeft = valueLeft + valueWidth + marginH2;

  con->space = naNewSpace(naMakeSize(spaceWidth, spaceHeight));
//  naSetSpaceAlternateBackground(con->space, NA_TRUE);

  con->title = cmNewTitleLabel(cmTranslate(CMTotalMetamericIndex), 250);
  con->metamericsAverageLabel = naNewLabel(cmTranslate(CMAverage), 120);
  con->metamericsLabel = cmNewValueLabel();
  con->metamericsGradeLabel = naNewLabel("", 120);



  // Placing elements in the space

  double spaceY = spaceHeight - spaceMarginTop;
  spaceY -= uiElemHeight;
  naAddSpaceChild(con->space, con->title, naMakePos(spaceMarginLeft, spaceY));
 
  spaceY -= uiElemHeight;
  naAddSpaceChild(con->space, con->metamericsAverageLabel, naMakePos(spaceMarginLeft, spaceY));
  naAddSpaceChild(con->space, con->metamericsLabel, naMakePos(valueLeft, spaceY));
  naAddSpaceChild(con->space, con->metamericsGradeLabel, naMakePos(colorLeft, spaceY));

  return con;
}



void cmDeallocTotalMetamericIndexController(CMTotalMetamericIndexController* con){
  naFree(con);
}



NASpace* cmGetTotalMetamericIndexUIElement(CMTotalMetamericIndexController* con){
  return con->space;
}



void cmUpdateTotalMetamericIndexController(
  CMTotalMetamericIndexController* con,
  float avg5,
  float avg3,
  NABool valid)
{
  if(valid){
    float avg53 = (avg5 * 5.f + avg3 * 3.f) / 8.f;
    naSetLabelText(con->metamericsLabel, naAllocSprintf(NA_TRUE, "%1.04f", avg53));
    naSetLabelText(con->metamericsGradeLabel, naAllocSprintf(NA_TRUE, cmTranslate(CMGrade), getGrade(avg53)));
  }else{
    naSetLabelText(con->metamericsLabel, "");
    naSetLabelText(con->metamericsGradeLabel, "");
  }
}
