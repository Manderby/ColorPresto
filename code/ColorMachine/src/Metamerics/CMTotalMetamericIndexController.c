
#include "CMTotalMetamericIndexController.h"

#include "CMColorConversionsYcdUVW.h"
#include "../CMDesign.h"
#include "../CMTranslations.h"

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

  con->space = naNewSpace(naMakeSize(1, 1));
//  naSetSpaceAlternateBackground(con->space, NA_TRUE);

  con->title = cmNewTitleLabel(cmTranslate(CMTotalMetamericIndex), 250);
  con->metamericsAverageLabel = naNewLabel(cmTranslate(CMAverage), indexWidth);
  con->metamericsLabel = cmNewValueLabel();
  con->metamericsGradeLabel = naNewLabel("", 120);



  // Placing elements in the space

  cmBeginUILayout(con->space, spaceBezel);
  cmAddUIRow(con->title, uiElemHeight);

  cmAddUIRow(con->metamericsAverageLabel, uiElemHeight);
  cmAddUICol(con->metamericsLabel, indexMargin);
  cmAddUICol(con->metamericsGradeLabel, valueMargin);

  cmEndUILayout();

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
