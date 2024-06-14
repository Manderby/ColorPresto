
#include "CPTotalMetamericIndexController.h"

#include "CPColorConversionsYcdUVW.h"
#include "../CPDesign.h"
#include "../CPTranslations.h"

#include "NAApp/NAApp.h"


struct CPTotalMetamericIndexController{
  NASpace* space;

  NALabel* title;
  NALabel* metamericsAverageLabel;
  NALabel* metamericsLabel;
  NALabel* metamericsGradeLabel;
};



CPTotalMetamericIndexController* cpAllocTotalMetamericIndexController(void){
  CPTotalMetamericIndexController* con = naAlloc(CPTotalMetamericIndexController);

  con->space = naNewSpace(naMakeSize(1, 1));
//  naSetSpaceAlternateBackground(con->space, NA_TRUE);

  con->title = cpNewTitleLabel(cpTranslate(CPTotalMetamericIndex), 250);
  con->metamericsAverageLabel = naNewLabel(cpTranslate(CPAverage), indexWidth);
  con->metamericsLabel = cpNewValueLabel();
  con->metamericsGradeLabel = naNewLabel("", 120);



  // Placing elements in the space

  cpBeginUILayout(con->space, spaceBezel);
  cpAddUIRow(con->title, uiElemHeight);

  cpAddUIRow(con->metamericsAverageLabel, uiElemHeight);
  cpAddUICol(con->metamericsLabel, indexMargin);
  cpAddUICol(con->metamericsGradeLabel, valueMargin);

  cpEndUILayout();

  return con;
}



void cpDeallocTotalMetamericIndexController(CPTotalMetamericIndexController* con){
  naFree(con);
}



NASpace* cpGetTotalMetamericIndexUIElement(CPTotalMetamericIndexController* con){
  return con->space;
}



void cpUpdateTotalMetamericIndexController(
  CPTotalMetamericIndexController* con,
  float avg5,
  float avg3,
  NABool valid)
{
  if(valid){
    float avg53 = (avg5 * 5.f + avg3 * 3.f) / 8.f;
    naSetLabelText(con->metamericsLabel, naAllocSprintf(NA_TRUE, "%1.04f", avg53));
    naSetLabelText(con->metamericsGradeLabel, naAllocSprintf(NA_TRUE, cpTranslate(CPGrade), getGrade(avg53)));
  }else{
    naSetLabelText(con->metamericsLabel, "");
    naSetLabelText(con->metamericsGradeLabel, "");
  }
}
