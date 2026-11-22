
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



CPTotalMetamericIndexController* cpAllocTotalMetamericIndexController(void) {
  CPTotalMetamericIndexController* con = naAlloc(CPTotalMetamericIndexController);

  con->space = naNewSpace();
//  naSetSpaceAlternateBackground(con->space, NA_TRUE);

  con->title = cpNewTitleLabel(cpTranslate(CPTotalMetamericIndex));
  con->metamericsAverageLabel = naNewLabel(cpTranslate(CPAverage));
  con->metamericsLabel = cpNewValueLabel();
  con->metamericsGradeLabel = naNewLabel(NA_NULL);



  // Placing elements in the space

  NABorder2D zeroPadding = naMakeBorder2D(0., 0., 0., 0.);

  naBeginLayout(con->space, spaceBorder);
  
    naAddLayoutSection(uiElemHeight, zeroPadding);
      naAddLayoutElement(con->title, 0, 250.);

    naAddLayoutSection(uiElemHeight, zeroPadding);
      naAddLayoutElement(con->metamericsAverageLabel, 0, indexWidth);
      naAddLayoutElement(con->metamericsLabel, indexMargin, labelValueWidth);
      naAddLayoutElement(con->metamericsGradeLabel, valueMargin, 120);
      
  naEndLayout();

  return con;
}



void cpDeallocTotalMetamericIndexController(CPTotalMetamericIndexController* con) {
  naFree(con);
}



NASpace* cpGetTotalMetamericIndexUIElement(CPTotalMetamericIndexController* con) {
  return con->space;
}



void cpUpdateTotalMetamericIndexController(
  CPTotalMetamericIndexController* con,
  float avg5,
  float avg3,
  NABool valid)
{
  if(valid) {
    float avg53 = (avg5 * 5.f + avg3 * 3.f) / 8.f;
    naSetLabelText(con->metamericsLabel, naAllocSprintf(NA_TRUE, "%1.04f", avg53));
    naSetLabelText(con->metamericsGradeLabel, naAllocSprintf(NA_TRUE, cpTranslate(CPGrade), getGrade(avg53)));
  }else{
    naSetLabelText(con->metamericsLabel, "");
    naSetLabelText(con->metamericsGradeLabel, "");
  }
}
