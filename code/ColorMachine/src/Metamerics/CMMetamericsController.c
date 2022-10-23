
#include "CMMetamericsController.h"

#include "CMChromaticityErrorController.h"
#include "CMWhitePointsController.h"

#include "CMColorConversionsYcdUVW.h"
#include "CMColorRenderingIndex.h"
#include "CMTranslations.h"
#include "CMTwoColorController.h"
#include "CMUVMetamericColors.h"
#include "CMVisMetamericColors.h"
#include "CMWhitePoints.h"
#include "NAApp.h"
#include "CML.h"
#include "mainC.h"
#include "CMDesign.h"


static const double indexWidth = 30.;
static const double colorWidth = 140.;
static const double columnWidth = spaceMarginLeft + indexWidth + valueWidth + colorWidth + 1 * 5. + spaceMarginRight;
static const double degreeWidth = 30;
static const double firstColumLeft = spaceMarginLeft + degreeWidth + 5;

static const double valueLeft = spaceMarginLeft + indexWidth;
static const double colorLeft = valueLeft + valueWidth + 5.;



struct CMMetamericsController{
  NAWindow* window;
  
  NASpace* whitePointBigSpace;
  NASpace* colorRenderingBigSpace;
  NASpace* metamericsBigSpace;
  
  CMWhitePointsController* whitePointsController;
  CMChromaticityErrorController* chromaticityErrorController;

  NASpace* colorRenderingSpace;
  NALabel* colorRenderingTitle;
  NALabel* colorRendering1IndexLabel;
  NALabel* colorRendering1Label;
  CMTwoColorController* colorRendering1Display;
  NALabel* colorRendering2IndexLabel;
  NALabel* colorRendering2Label;
  CMTwoColorController* colorRendering2Display;
  NALabel* colorRendering3IndexLabel;
  NALabel* colorRendering3Label;
  CMTwoColorController* colorRendering3Display;
  NALabel* colorRendering4IndexLabel;
  NALabel* colorRendering4Label;
  CMTwoColorController* colorRendering4Display;
  NALabel* colorRendering5IndexLabel;
  NALabel* colorRendering5Label;
  CMTwoColorController* colorRendering5Display;
  NALabel* colorRendering6IndexLabel;
  NALabel* colorRendering6Label;
  CMTwoColorController* colorRendering6Display;
  NALabel* colorRendering7IndexLabel;
  NALabel* colorRendering7Label;
  CMTwoColorController* colorRendering7Display;
  NALabel* colorRendering8IndexLabel;
  NALabel* colorRendering8Label;
  CMTwoColorController* colorRendering8Display;

  NALabel* colorRenderingAverageLabel;
  NALabel* colorRenderingLabel;

  NALabel* colorRendering9IndexLabel;
  NALabel* colorRendering9Label;
  CMTwoColorController* colorRendering9Display;
  NALabel* colorRendering10IndexLabel;
  NALabel* colorRendering10Label;
  CMTwoColorController* colorRendering10Display;
  NALabel* colorRendering11IndexLabel;
  NALabel* colorRendering11Label;
  CMTwoColorController* colorRendering11Display;
  NALabel* colorRendering12IndexLabel;
  NALabel* colorRendering12Label;
  CMTwoColorController* colorRendering12Display;
  NALabel* colorRendering13IndexLabel;
  NALabel* colorRendering13Label;
  CMTwoColorController* colorRendering13Display;
  NALabel* colorRendering14IndexLabel;
  NALabel* colorRendering14Label;
  CMTwoColorController* colorRendering14Display;

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

  const double colorRenderingSpaceHeight = 17 * uiElemHeight + spaceMarginV;
  const double visMetamericsSpaceHeight = 7 * uiElemHeight + spaceMarginV;
  const double uvMetamericsSpaceHeight = 5 * uiElemHeight + spaceMarginV;
  const double totalMetamericsSpaceHeight = 2 * uiElemHeight + spaceMarginV;

  const double totalHeight = colorRenderingSpaceHeight;

  con->window = naNewWindow(
    cmTranslate(CMWhitepointsAndMetamerics),
    naMakeRectS(
      600,
      500,
      metamericsFirstColumnWidth + 2 * columnWidth,
      totalHeight),
    0,
    0);
  NASpace* contentSpace = naGetWindowContentSpace(con->window);

  con->colorRenderingBigSpace = naNewSpace(naMakeSize(columnWidth, totalHeight));
  naSetSpaceAlternateBackground(con->colorRenderingBigSpace, NA_TRUE);
  con->metamericsBigSpace = naNewSpace(naMakeSize(columnWidth, totalHeight));



  con->chromaticityErrorController = cmAllocChromaticityErrorController();
  con->whitePointsController = cmAllocWhitePointsController();



  // Color Rendering index
  con->colorRenderingSpace = naNewSpace(naMakeSize(columnWidth, colorRenderingSpaceHeight));

  con->colorRenderingTitle = cmNewTitleLabel("Color Rendering Index:", 250);

  con->colorRendering1IndexLabel = naNewLabel("1:", indexWidth);
  con->colorRendering1Label = cmNewValueLabel();
  con->colorRendering1Display = cmAllocTwoColorController(naMakeSize(colorWidth, 21));
  con->colorRendering2IndexLabel = naNewLabel("2:", indexWidth);
  con->colorRendering2Label = cmNewValueLabel();
  con->colorRendering2Display = cmAllocTwoColorController(naMakeSize(colorWidth, 21));
  con->colorRendering3IndexLabel = naNewLabel("3:", indexWidth);
  con->colorRendering3Label = cmNewValueLabel();
  con->colorRendering3Display = cmAllocTwoColorController(naMakeSize(colorWidth, 21));
  con->colorRendering4IndexLabel = naNewLabel("4:", indexWidth);
  con->colorRendering4Label = cmNewValueLabel();
  con->colorRendering4Display = cmAllocTwoColorController(naMakeSize(colorWidth, 21));
  con->colorRendering5IndexLabel = naNewLabel("5:", indexWidth);
  con->colorRendering5Label = cmNewValueLabel();
  con->colorRendering5Display = cmAllocTwoColorController(naMakeSize(colorWidth, 21));
  con->colorRendering6IndexLabel = naNewLabel("6:", indexWidth);
  con->colorRendering6Label = cmNewValueLabel();
  con->colorRendering6Display = cmAllocTwoColorController(naMakeSize(colorWidth, 21));
  con->colorRendering7IndexLabel = naNewLabel("7:", indexWidth);
  con->colorRendering7Label = cmNewValueLabel();
  con->colorRendering7Display = cmAllocTwoColorController(naMakeSize(colorWidth, 21));
  con->colorRendering8IndexLabel = naNewLabel("8:", indexWidth);
  con->colorRendering8Label = cmNewValueLabel();
  con->colorRendering8Display = cmAllocTwoColorController(naMakeSize(colorWidth, 21));

  con->colorRenderingAverageLabel = naNewLabel("Ø:", 120);
//  naSetLabelFont(con->colorRenderingAverageLabel, boldFont);
  con->colorRenderingLabel = cmNewValueLabel();

  con->colorRendering9IndexLabel = naNewLabel("9:", indexWidth);
  con->colorRendering9Label = cmNewValueLabel();
  con->colorRendering9Display = cmAllocTwoColorController(naMakeSize(colorWidth, 21));
  con->colorRendering10IndexLabel = naNewLabel("10:", indexWidth);
  con->colorRendering10Label = cmNewValueLabel();
  con->colorRendering10Display = cmAllocTwoColorController(naMakeSize(colorWidth, 21));
  con->colorRendering11IndexLabel = naNewLabel("11:", indexWidth);
  con->colorRendering11Label = cmNewValueLabel();
  con->colorRendering11Display = cmAllocTwoColorController(naMakeSize(colorWidth, 21));
  con->colorRendering12IndexLabel = naNewLabel("12:", indexWidth);
  con->colorRendering12Label = cmNewValueLabel();
  con->colorRendering12Display = cmAllocTwoColorController(naMakeSize(colorWidth, 21));
  con->colorRendering13IndexLabel = naNewLabel("13:", indexWidth);
  con->colorRendering13Label = cmNewValueLabel();
  con->colorRendering13Display = cmAllocTwoColorController(naMakeSize(colorWidth, 21));
  con->colorRendering14IndexLabel = naNewLabel("14:", indexWidth);
  con->colorRendering14Label = cmNewValueLabel();
  con->colorRendering14Display = cmAllocTwoColorController(naMakeSize(colorWidth, 21));

  // visible range metamerics
  con->visMetamericsSpace = naNewSpace(naMakeSize(columnWidth, visMetamericsSpaceHeight));
  
  con->visMetamericsTitle = cmNewTitleLabel("Visible Range Metameric Index:", 250);
  
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

  con->visMetamericsAverageLabel = naNewLabel("Ø:", indexWidth);
//  naSetLabelFont(con->visMetamericsAverageLabel, boldFont);
  con->visMetamericsLabel = cmNewValueLabel();
  con->visMetamericsGradeLabel = naNewLabel("Grade A", 120);


  // UV metamerics
  con->uvMetamericsSpace = naNewSpace(naMakeSize(columnWidth, uvMetamericsSpaceHeight));

  con->uvMetamericsTitle = cmNewTitleLabel("Ultraviolet Range Metameric Index:", 250);

  con->uvMetamerics6IndexLabel = naNewLabel("6:", indexWidth);
  con->uvMetamerics6Label = cmNewValueLabel();
  con->uvMetamerics6Display = cmAllocTwoColorController(naMakeSize(colorWidth, 21));

  con->uvMetamerics7IndexLabel = naNewLabel("7:", indexWidth);
  con->uvMetamerics7Label = cmNewValueLabel();
  con->uvMetamerics7Display = cmAllocTwoColorController(naMakeSize(colorWidth, 21));

  con->uvMetamerics8IndexLabel = naNewLabel("8:", indexWidth);
  con->uvMetamerics8Label = cmNewValueLabel();
  con->uvMetamerics8Display = cmAllocTwoColorController(naMakeSize(colorWidth, 21));

  con->uvMetamericsAverageLabel = naNewLabel("Ø:", 120);
//  naSetLabelFont(con->uvMetamericsAverageLabel, boldFont);
  con->uvMetamericsLabel = cmNewValueLabel();
  con->uvMetamericsGradeLabel = naNewLabel("Grade A", 120);


  // Total metamerics
  con->totalMetamericsSpace = naNewSpace(naMakeSize(columnWidth, totalMetamericsSpaceHeight));

  con->totalMetamericsTitle = cmNewTitleLabel("Total Metameric Index (1-8):", 250);
  con->totalMetamericsAverageLabel = naNewLabel("Ø:", 120);
//  naSetLabelFont(con->totalMetamericsAverageLabel, boldFont);
  con->totalMetamericsLabel = cmNewValueLabel();
  con->totalMetamericsGradeLabel = naNewLabel("Grade A", 120);



  // Placing elements in the window

  // Left BigSpace: White Points and Chromaticity Error

  double columnY;



  NASpace* whitePointsSpace = cmGetWhitePointsUIElement(con->whitePointsController);
  NASpace* chromaticityErrorSpace = cmGetChromaticityErrorUIElement(con->chromaticityErrorController);
  
  NASize whitePointsSize = naGetUIElementRect(whitePointsSpace, NA_NULL, NA_FALSE).size;
  NASize chromaticityErrorSize = naGetUIElementRect(chromaticityErrorSpace, NA_NULL, NA_FALSE).size;
  double firstColumnHeight = whitePointsSize.height + chromaticityErrorSize.height;
  double firstColumnWidth = naMax(whitePointsSize.width, chromaticityErrorSize.width);
  
  con->whitePointBigSpace = naNewSpace(naMakeSize(firstColumnWidth, firstColumnHeight));

  columnY = firstColumnHeight;

  columnY -= whitePointsSize.height;
  naAddSpaceChild(
    con->whitePointBigSpace,
    whitePointsSpace,
    naMakePos(0, columnY));

  columnY -= chromaticityErrorSize.height;
  naAddSpaceChild(
    con->whitePointBigSpace,
    chromaticityErrorSpace,
    naMakePos(firstColumLeft, columnY));

  naAddSpaceChild(contentSpace, con->whitePointBigSpace, naMakePos(0, totalHeight - firstColumnHeight));



  // Middle BigSpace: Color Rendering Index

  columnY = totalHeight;

  double colorRenderingY = colorRenderingSpaceHeight - spaceMarginTop;
  colorRenderingY -= uiElemHeight;
  naAddSpaceChild(con->colorRenderingSpace, con->colorRenderingTitle, naMakePos(spaceMarginLeft, colorRenderingY));

  colorRenderingY -= uiElemHeight;
  naAddSpaceChild(con->colorRenderingSpace, con->colorRendering1IndexLabel, naMakePos(spaceMarginLeft, colorRenderingY));
  naAddSpaceChild(con->colorRenderingSpace, con->colorRendering1Label, naMakePos(valueLeft, colorRenderingY));
  naAddSpaceChild(con->colorRenderingSpace, cmGetTwoColorControllerUIElement(con->colorRendering1Display), naMakePos(colorLeft, colorRenderingY));
  colorRenderingY -= uiElemHeight;
  naAddSpaceChild(con->colorRenderingSpace, con->colorRendering2IndexLabel, naMakePos(spaceMarginLeft, colorRenderingY));
  naAddSpaceChild(con->colorRenderingSpace, con->colorRendering2Label, naMakePos(valueLeft, colorRenderingY));
  naAddSpaceChild(con->colorRenderingSpace, cmGetTwoColorControllerUIElement(con->colorRendering2Display), naMakePos(colorLeft, colorRenderingY));
  colorRenderingY -= uiElemHeight;
  naAddSpaceChild(con->colorRenderingSpace, con->colorRendering3IndexLabel, naMakePos(spaceMarginLeft, colorRenderingY));
  naAddSpaceChild(con->colorRenderingSpace, con->colorRendering3Label, naMakePos(valueLeft, colorRenderingY));
  naAddSpaceChild(con->colorRenderingSpace, cmGetTwoColorControllerUIElement(con->colorRendering3Display), naMakePos(colorLeft, colorRenderingY));
  colorRenderingY -= uiElemHeight;
  naAddSpaceChild(con->colorRenderingSpace, con->colorRendering4IndexLabel, naMakePos(spaceMarginLeft, colorRenderingY));
  naAddSpaceChild(con->colorRenderingSpace, con->colorRendering4Label, naMakePos(valueLeft, colorRenderingY));
  naAddSpaceChild(con->colorRenderingSpace, cmGetTwoColorControllerUIElement(con->colorRendering4Display), naMakePos(colorLeft, colorRenderingY));
  colorRenderingY -= uiElemHeight;
  naAddSpaceChild(con->colorRenderingSpace, con->colorRendering5IndexLabel, naMakePos(spaceMarginLeft, colorRenderingY));
  naAddSpaceChild(con->colorRenderingSpace, con->colorRendering5Label, naMakePos(valueLeft, colorRenderingY));
  naAddSpaceChild(con->colorRenderingSpace, cmGetTwoColorControllerUIElement(con->colorRendering5Display), naMakePos(colorLeft, colorRenderingY));
  colorRenderingY -= uiElemHeight;
  naAddSpaceChild(con->colorRenderingSpace, con->colorRendering6IndexLabel, naMakePos(spaceMarginLeft, colorRenderingY));
  naAddSpaceChild(con->colorRenderingSpace, con->colorRendering6Label, naMakePos(valueLeft, colorRenderingY));
  naAddSpaceChild(con->colorRenderingSpace, cmGetTwoColorControllerUIElement(con->colorRendering6Display), naMakePos(colorLeft, colorRenderingY));
  colorRenderingY -= uiElemHeight;
  naAddSpaceChild(con->colorRenderingSpace, con->colorRendering7IndexLabel, naMakePos(spaceMarginLeft, colorRenderingY));
  naAddSpaceChild(con->colorRenderingSpace, con->colorRendering7Label, naMakePos(valueLeft, colorRenderingY));
  naAddSpaceChild(con->colorRenderingSpace, cmGetTwoColorControllerUIElement(con->colorRendering7Display), naMakePos(colorLeft, colorRenderingY));
  colorRenderingY -= uiElemHeight;
  naAddSpaceChild(con->colorRenderingSpace, con->colorRendering8IndexLabel, naMakePos(spaceMarginLeft, colorRenderingY));
  naAddSpaceChild(con->colorRenderingSpace, con->colorRendering8Label, naMakePos(valueLeft, colorRenderingY));
  naAddSpaceChild(con->colorRenderingSpace, cmGetTwoColorControllerUIElement(con->colorRendering8Display), naMakePos(colorLeft, colorRenderingY));

  colorRenderingY -= uiElemHeight;
  naAddSpaceChild(con->colorRenderingSpace, con->colorRenderingAverageLabel, naMakePos(spaceMarginLeft, colorRenderingY));
  naAddSpaceChild(con->colorRenderingSpace, con->colorRenderingLabel, naMakePos(valueLeft, colorRenderingY));

  colorRenderingY -= 50;
  naAddSpaceChild(con->colorRenderingSpace, con->colorRendering9IndexLabel, naMakePos(spaceMarginLeft, colorRenderingY));
  naAddSpaceChild(con->colorRenderingSpace, con->colorRendering9Label, naMakePos(valueLeft, colorRenderingY));
  naAddSpaceChild(con->colorRenderingSpace, cmGetTwoColorControllerUIElement(con->colorRendering9Display), naMakePos(colorLeft, colorRenderingY));
  colorRenderingY -= uiElemHeight;
  naAddSpaceChild(con->colorRenderingSpace, con->colorRendering10IndexLabel, naMakePos(spaceMarginLeft, colorRenderingY));
  naAddSpaceChild(con->colorRenderingSpace, con->colorRendering10Label, naMakePos(valueLeft, colorRenderingY));
  naAddSpaceChild(con->colorRenderingSpace, cmGetTwoColorControllerUIElement(con->colorRendering10Display), naMakePos(colorLeft, colorRenderingY));
  colorRenderingY -= uiElemHeight;
  naAddSpaceChild(con->colorRenderingSpace, con->colorRendering11IndexLabel, naMakePos(spaceMarginLeft, colorRenderingY));
  naAddSpaceChild(con->colorRenderingSpace, con->colorRendering11Label, naMakePos(valueLeft, colorRenderingY));
  naAddSpaceChild(con->colorRenderingSpace, cmGetTwoColorControllerUIElement(con->colorRendering11Display), naMakePos(colorLeft, colorRenderingY));
  colorRenderingY -= uiElemHeight;
  naAddSpaceChild(con->colorRenderingSpace, con->colorRendering12IndexLabel, naMakePos(spaceMarginLeft, colorRenderingY));
  naAddSpaceChild(con->colorRenderingSpace, con->colorRendering12Label, naMakePos(valueLeft, colorRenderingY));
  naAddSpaceChild(con->colorRenderingSpace, cmGetTwoColorControllerUIElement(con->colorRendering12Display), naMakePos(colorLeft, colorRenderingY));
  colorRenderingY -= uiElemHeight;
  naAddSpaceChild(con->colorRenderingSpace, con->colorRendering13IndexLabel, naMakePos(spaceMarginLeft, colorRenderingY));
  naAddSpaceChild(con->colorRenderingSpace, con->colorRendering13Label, naMakePos(valueLeft, colorRenderingY));
  naAddSpaceChild(con->colorRenderingSpace, cmGetTwoColorControllerUIElement(con->colorRendering13Display), naMakePos(colorLeft, colorRenderingY));
  colorRenderingY -= uiElemHeight;
  naAddSpaceChild(con->colorRenderingSpace, con->colorRendering14IndexLabel, naMakePos(spaceMarginLeft, colorRenderingY));
  naAddSpaceChild(con->colorRenderingSpace, con->colorRendering14Label, naMakePos(valueLeft, colorRenderingY));
  naAddSpaceChild(con->colorRenderingSpace, cmGetTwoColorControllerUIElement(con->colorRendering14Display), naMakePos(colorLeft, colorRenderingY));

  columnY -= colorRenderingSpaceHeight;
  naAddSpaceChild(con->colorRenderingBigSpace, con->colorRenderingSpace, naMakePos(0, columnY));

  naAddSpaceChild(contentSpace, con->colorRenderingBigSpace, naMakePos(metamericsFirstColumnWidth, 0));



  // Right BigSpace: Metameric Index

  columnY = totalHeight;

  double visMetamericsY = visMetamericsSpaceHeight - spaceMarginTop;
  visMetamericsY -= uiElemHeight;
  naAddSpaceChild(con->visMetamericsSpace, con->visMetamericsTitle, naMakePos(spaceMarginLeft, visMetamericsY));
  
  visMetamericsY -= uiElemHeight;
  naAddSpaceChild(con->visMetamericsSpace, con->visMetamerics1IndexLabel, naMakePos(spaceMarginLeft, visMetamericsY));
  naAddSpaceChild(con->visMetamericsSpace, con->visMetamerics1Label, naMakePos(valueLeft, visMetamericsY));
  naAddSpaceChild(con->visMetamericsSpace, cmGetTwoColorControllerUIElement(con->visMetamerics1Display), naMakePos(colorLeft, visMetamericsY));
  
  visMetamericsY -= uiElemHeight;
  naAddSpaceChild(con->visMetamericsSpace, con->visMetamerics2IndexLabel, naMakePos(spaceMarginLeft, visMetamericsY));
  naAddSpaceChild(con->visMetamericsSpace, con->visMetamerics2Label, naMakePos(valueLeft, visMetamericsY));
  naAddSpaceChild(con->visMetamericsSpace, cmGetTwoColorControllerUIElement(con->visMetamerics2Display), naMakePos(colorLeft, visMetamericsY));
  
  visMetamericsY -= uiElemHeight;
  naAddSpaceChild(con->visMetamericsSpace, con->visMetamerics3IndexLabel, naMakePos(spaceMarginLeft, visMetamericsY));
  naAddSpaceChild(con->visMetamericsSpace, con->visMetamerics3Label, naMakePos(valueLeft, visMetamericsY));
  naAddSpaceChild(con->visMetamericsSpace, cmGetTwoColorControllerUIElement(con->visMetamerics3Display), naMakePos(colorLeft, visMetamericsY));

  visMetamericsY -= uiElemHeight;
  naAddSpaceChild(con->visMetamericsSpace, con->visMetamerics4IndexLabel, naMakePos(spaceMarginLeft, visMetamericsY));
  naAddSpaceChild(con->visMetamericsSpace, con->visMetamerics4Label, naMakePos(valueLeft, visMetamericsY));
  naAddSpaceChild(con->visMetamericsSpace, cmGetTwoColorControllerUIElement(con->visMetamerics4Display), naMakePos(colorLeft, visMetamericsY));
  
  visMetamericsY -= uiElemHeight;
  naAddSpaceChild(con->visMetamericsSpace, con->visMetamerics5IndexLabel, naMakePos(spaceMarginLeft, visMetamericsY));
  naAddSpaceChild(con->visMetamericsSpace, con->visMetamerics5Label, naMakePos(valueLeft, visMetamericsY));
  naAddSpaceChild(con->visMetamericsSpace, cmGetTwoColorControllerUIElement(con->visMetamerics5Display), naMakePos(colorLeft, visMetamericsY));
  
  visMetamericsY -= uiElemHeight;
  naAddSpaceChild(con->visMetamericsSpace, con->visMetamericsAverageLabel, naMakePos(spaceMarginLeft, visMetamericsY));
  naAddSpaceChild(con->visMetamericsSpace, con->visMetamericsLabel, naMakePos(valueLeft, visMetamericsY));
  naAddSpaceChild(con->visMetamericsSpace, con->visMetamericsGradeLabel, naMakePos(colorLeft, visMetamericsY));

  columnY -= visMetamericsSpaceHeight;
  naAddSpaceChild(con->metamericsBigSpace, con->visMetamericsSpace, naMakePos(0, columnY));



  double uvMetamericsY = uvMetamericsSpaceHeight - spaceMarginTop;
  uvMetamericsY -= uiElemHeight;

  naAddSpaceChild(con->uvMetamericsSpace, con->uvMetamericsTitle, naMakePos(spaceMarginLeft, uvMetamericsY));

  uvMetamericsY -= uiElemHeight;
  naAddSpaceChild(con->uvMetamericsSpace, con->uvMetamerics6IndexLabel, naMakePos(spaceMarginLeft, uvMetamericsY));
  naAddSpaceChild(con->uvMetamericsSpace, con->uvMetamerics6Label, naMakePos(valueLeft, uvMetamericsY));
  naAddSpaceChild(con->uvMetamericsSpace, cmGetTwoColorControllerUIElement(con->uvMetamerics6Display), naMakePos(colorLeft, uvMetamericsY));

  uvMetamericsY -= uiElemHeight;
  naAddSpaceChild(con->uvMetamericsSpace, con->uvMetamerics7IndexLabel, naMakePos(spaceMarginLeft, uvMetamericsY));
  naAddSpaceChild(con->uvMetamericsSpace, con->uvMetamerics7Label, naMakePos(valueLeft, uvMetamericsY));
  naAddSpaceChild(con->uvMetamericsSpace, cmGetTwoColorControllerUIElement(con->uvMetamerics7Display), naMakePos(colorLeft, uvMetamericsY));

  uvMetamericsY -= uiElemHeight;
  naAddSpaceChild(con->uvMetamericsSpace, con->uvMetamerics8IndexLabel, naMakePos(spaceMarginLeft, uvMetamericsY));
  naAddSpaceChild(con->uvMetamericsSpace, con->uvMetamerics8Label, naMakePos(valueLeft, uvMetamericsY));
  naAddSpaceChild(con->uvMetamericsSpace, cmGetTwoColorControllerUIElement(con->uvMetamerics8Display), naMakePos(colorLeft, uvMetamericsY));

  uvMetamericsY -= uiElemHeight;
  naAddSpaceChild(con->uvMetamericsSpace, con->uvMetamericsAverageLabel, naMakePos(spaceMarginLeft, uvMetamericsY));
  naAddSpaceChild(con->uvMetamericsSpace, con->uvMetamericsLabel, naMakePos(valueLeft, uvMetamericsY));
  naAddSpaceChild(con->uvMetamericsSpace, con->uvMetamericsGradeLabel, naMakePos(colorLeft, uvMetamericsY));

  columnY -= uvMetamericsSpaceHeight;
  naAddSpaceChild(con->metamericsBigSpace, con->uvMetamericsSpace, naMakePos(0, columnY));



  double totalMetamericsY = totalMetamericsSpaceHeight - spaceMarginTop;
  totalMetamericsY -= uiElemHeight;

  naAddSpaceChild(con->totalMetamericsSpace, con->totalMetamericsTitle, naMakePos(spaceMarginLeft, totalMetamericsY));
 
  totalMetamericsY -= uiElemHeight;
  naAddSpaceChild(con->totalMetamericsSpace, con->totalMetamericsAverageLabel, naMakePos(spaceMarginLeft, totalMetamericsY));
  naAddSpaceChild(con->totalMetamericsSpace, con->totalMetamericsLabel, naMakePos(valueLeft, totalMetamericsY));
  naAddSpaceChild(con->totalMetamericsSpace, con->totalMetamericsGradeLabel, naMakePos(colorLeft, totalMetamericsY));

  columnY -= totalMetamericsSpaceHeight;
  naAddSpaceChild(con->metamericsBigSpace, con->totalMetamericsSpace, naMakePos(0, columnY));

  naAddSpaceChild(contentSpace, con->metamericsBigSpace, naMakePos(metamericsFirstColumnWidth + columnWidth, 0));



  
  return con;
}



void cmDeallocMetamericsController(CMMetamericsController* con){
  cmDeallocChromaticityErrorController(con->chromaticityErrorController);
  cmDeallocWhitePointsController(con->whitePointsController);
  naFree(con);
}



void cmShowMetamericsController(CMMetamericsController* con){
  naShowWindow(con->window);
}



void cmUpdateMetamericsController(CMMetamericsController* con){
  CMLColorMachine* cm = cmGetCurrentColorMachine();

  CMLFunction* observer10Funcs[3];
  cmlCreateSpecDistFunctions(observer10Funcs, CML_DEFAULT_10DEG_OBSERVER);
  CMLFunction* observer2Funcs[3];
  cmlCreateSpecDistFunctions(observer2Funcs, CML_DEFAULT_2DEG_OBSERVER);
  const CMLFunction* illuminationSpec = cmlGetReferenceIlluminationSpectrum(cm);
  CMReferenceIlluminationType referenceIlluminationType = cmGetReferenceIlluminationType(con->whitePointsController);


  const CMLFunction* ref;
  switch(referenceIlluminationType){
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
  default:
    #if NA_DEBUG
      naError("This shoud not happen.");
    #endif
    ref = cmlCreateIlluminationSpectrum(CML_ILLUMINATION_D50, 0.f);
  }

  CMWhitePoints illWhitePoint10 = CMGetWhitePoints(
    illuminationSpec,
    cmlGetReferenceWhitePointYxy(cm),
    observer10Funcs);
  CMWhitePoints illWhitePoint2 = CMGetWhitePoints(
    illuminationSpec,
    cmlGetReferenceWhitePointYxy(cm),
    observer2Funcs);
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




  cmUpdateWhitePointsController(
    con->whitePointsController,
    cmlGetIlluminationTypeString(cmlGetReferenceIlluminationType(cm)),
    &illWhitePoint10,
    &illWhitePoint2,
    &refWhitePoint10,
    &refWhitePoint2);

  cmUpdateChromaticityErrorController(
    con->chromaticityErrorController,
    &refWhitePoint10,
    &illWhitePoint10,
    illuminationSpec != NA_NULL);
    


  // Color Rendering Index
  
  CMColorRenderingColors colorRenderingColors = cmComputeColorRenderingColors(
    observer2Funcs,
    &refWhitePoint2,
    &illWhitePoint2,
    ref);

  naSetLabelText(
    con->colorRendering1Label,
    naAllocSprintf(NA_TRUE, "%3.03f", colorRenderingColors.colorRenderingIndex[0]));
  cmUpdateTwoColorController(
    con->colorRendering1Display,
    colorRenderingColors.crMetamerRGBFloatData[0],
    colorRenderingColors.crReferenceRGBFloatData[0]);
  naSetLabelText(
    con->colorRendering2Label,
    naAllocSprintf(NA_TRUE, "%3.03f", colorRenderingColors.colorRenderingIndex[1]));
  cmUpdateTwoColorController(
    con->colorRendering2Display,
    colorRenderingColors.crMetamerRGBFloatData[1],
    colorRenderingColors.crReferenceRGBFloatData[1]);
  naSetLabelText(
    con->colorRendering3Label,
    naAllocSprintf(NA_TRUE, "%3.03f", colorRenderingColors.colorRenderingIndex[2]));
  cmUpdateTwoColorController(
    con->colorRendering3Display,
    colorRenderingColors.crMetamerRGBFloatData[2],
    colorRenderingColors.crReferenceRGBFloatData[2]);
  naSetLabelText(
    con->colorRendering4Label,
    naAllocSprintf(NA_TRUE, "%3.03f", colorRenderingColors.colorRenderingIndex[3]));
  cmUpdateTwoColorController(
    con->colorRendering4Display,
    colorRenderingColors.crMetamerRGBFloatData[3],
    colorRenderingColors.crReferenceRGBFloatData[3]);
  naSetLabelText(
    con->colorRendering5Label,
    naAllocSprintf(NA_TRUE, "%3.03f", colorRenderingColors.colorRenderingIndex[4]));
  cmUpdateTwoColorController(
    con->colorRendering5Display,
    colorRenderingColors.crMetamerRGBFloatData[4],
    colorRenderingColors.crReferenceRGBFloatData[4]);
  naSetLabelText(
    con->colorRendering6Label,
    naAllocSprintf(NA_TRUE, "%3.03f", colorRenderingColors.colorRenderingIndex[5]));
  cmUpdateTwoColorController(
    con->colorRendering6Display,
    colorRenderingColors.crMetamerRGBFloatData[5],
    colorRenderingColors.crReferenceRGBFloatData[5]);
  naSetLabelText(
    con->colorRendering7Label,
    naAllocSprintf(NA_TRUE, "%3.03f", colorRenderingColors.colorRenderingIndex[6]));
  cmUpdateTwoColorController(
    con->colorRendering7Display,
    colorRenderingColors.crMetamerRGBFloatData[6],
    colorRenderingColors.crReferenceRGBFloatData[6]);
  naSetLabelText(
    con->colorRendering8Label,
    naAllocSprintf(NA_TRUE, "%3.03f", colorRenderingColors.colorRenderingIndex[7]));
  cmUpdateTwoColorController(
    con->colorRendering8Display,
    colorRenderingColors.crMetamerRGBFloatData[7],
    colorRenderingColors.crReferenceRGBFloatData[7]);

  float colorRenderingAverage = 
    colorRenderingColors.colorRenderingIndex[0]
    + colorRenderingColors.colorRenderingIndex[1]
    + colorRenderingColors.colorRenderingIndex[2]
    + colorRenderingColors.colorRenderingIndex[3]
    + colorRenderingColors.colorRenderingIndex[4]
    + colorRenderingColors.colorRenderingIndex[5]
    + colorRenderingColors.colorRenderingIndex[6]
    + colorRenderingColors.colorRenderingIndex[7];
  colorRenderingAverage /= 8.f;

  naSetLabelText(con->colorRenderingLabel, naAllocSprintf(NA_TRUE, "%3.03f", colorRenderingAverage));

  naSetLabelText(
    con->colorRendering9Label,
    naAllocSprintf(NA_TRUE, "%3.03f", colorRenderingColors.colorRenderingIndex[8]));
  cmUpdateTwoColorController(
    con->colorRendering9Display,
    colorRenderingColors.crMetamerRGBFloatData[8],
    colorRenderingColors.crReferenceRGBFloatData[8]);
  naSetLabelText(
    con->colorRendering10Label,
    naAllocSprintf(NA_TRUE, "%3.03f", colorRenderingColors.colorRenderingIndex[9]));
  cmUpdateTwoColorController(
    con->colorRendering10Display,
    colorRenderingColors.crMetamerRGBFloatData[9],
    colorRenderingColors.crReferenceRGBFloatData[9]);
  naSetLabelText(
    con->colorRendering11Label,
    naAllocSprintf(NA_TRUE, "%3.03f", colorRenderingColors.colorRenderingIndex[10]));
  cmUpdateTwoColorController(
    con->colorRendering11Display,
    colorRenderingColors.crMetamerRGBFloatData[10],
    colorRenderingColors.crReferenceRGBFloatData[10]);
  naSetLabelText(
    con->colorRendering12Label,
    naAllocSprintf(NA_TRUE, "%3.03f", colorRenderingColors.colorRenderingIndex[11]));
  cmUpdateTwoColorController(
    con->colorRendering12Display,
    colorRenderingColors.crMetamerRGBFloatData[11],
    colorRenderingColors.crReferenceRGBFloatData[11]);
  naSetLabelText(
    con->colorRendering13Label,
    naAllocSprintf(NA_TRUE, "%3.03f", colorRenderingColors.colorRenderingIndex[12]));
  cmUpdateTwoColorController(
    con->colorRendering13Display,
    colorRenderingColors.crMetamerRGBFloatData[12],
    colorRenderingColors.crReferenceRGBFloatData[12]);
  naSetLabelText(
    con->colorRendering14Label,
    naAllocSprintf(NA_TRUE, "%3.03f", colorRenderingColors.colorRenderingIndex[13]));
  cmUpdateTwoColorController(
    con->colorRendering14Display,
    colorRenderingColors.crMetamerRGBFloatData[13],
    colorRenderingColors.crReferenceRGBFloatData[13]);


  // Visible Metamerics

  CMVisMetamericColors visMetamericColors = cmComputeVisMetamericColors(
    observer10Funcs,
    &illWhitePoint10,
    adaptationMatrix,
    referenceIlluminationType);

  naSetLabelText(
    con->visMetamerics1Label,
    naAllocSprintf(NA_TRUE, "%1.04f", visMetamericColors.metamericIndex[0]));
  cmUpdateTwoColorController(
    con->visMetamerics1Display,
    visMetamericColors.visStandardRGBFloatData[0],
    visMetamericColors.visMetamerRGBFloatData[0]);

  naSetLabelText(
    con->visMetamerics2Label,
    naAllocSprintf(NA_TRUE, "%1.04f", visMetamericColors.metamericIndex[1]));
  cmUpdateTwoColorController(
    con->visMetamerics2Display,
    visMetamericColors.visStandardRGBFloatData[1],
    visMetamericColors.visMetamerRGBFloatData[1]);

  naSetLabelText(
    con->visMetamerics3Label,
    naAllocSprintf(NA_TRUE, "%1.04f", visMetamericColors.metamericIndex[2]));
  cmUpdateTwoColorController(
    con->visMetamerics3Display,
    visMetamericColors.visStandardRGBFloatData[2],
    visMetamericColors.visMetamerRGBFloatData[2]);

  naSetLabelText(
    con->visMetamerics4Label,
    naAllocSprintf(NA_TRUE, "%1.04f", visMetamericColors.metamericIndex[3]));
  cmUpdateTwoColorController(
    con->visMetamerics4Display,
    visMetamericColors.visStandardRGBFloatData[3],
    visMetamericColors.visMetamerRGBFloatData[3]);

  naSetLabelText(
    con->visMetamerics5Label,
    naAllocSprintf(NA_TRUE, "%1.04f", visMetamericColors.metamericIndex[4]));
  cmUpdateTwoColorController(
    con->visMetamerics5Display,
    visMetamericColors.visStandardRGBFloatData[4],
    visMetamericColors.visMetamerRGBFloatData[4]);

  float avg5 = visMetamericColors.metamericIndex[0]
    + visMetamericColors.metamericIndex[1]
    + visMetamericColors.metamericIndex[2]
    + visMetamericColors.metamericIndex[3]
    + visMetamericColors.metamericIndex[4];
  avg5 /= 5.f;

  naSetLabelText(con->visMetamericsLabel, naAllocSprintf(NA_TRUE, "%1.04f", avg5));
  naSetLabelText(con->visMetamericsGradeLabel, getGrade(avg5));



  // UV Metamerics
  
  CMUVMetamericColors uvMetamericColors = cmComputeUVMetamericColors(
    observer10Funcs,
    &illWhitePoint10,
    referenceIlluminationType);

  naSetLabelText(
    con->uvMetamerics6Label,
    naAllocSprintf(NA_TRUE, "%1.04f", uvMetamericColors.metamericIndex[0]));
  cmUpdateTwoColorController(
    con->uvMetamerics6Display,
    uvMetamericColors.uvStandardRGBFloatData[0],
    uvMetamericColors.uvMetamerRGBFloatData[0]);

  naSetLabelText(
    con->uvMetamerics7Label,
    naAllocSprintf(NA_TRUE, "%1.04f", uvMetamericColors.metamericIndex[1]));
  cmUpdateTwoColorController(
    con->uvMetamerics7Display,
    uvMetamericColors.uvStandardRGBFloatData[1],
    uvMetamericColors.uvMetamerRGBFloatData[1]);
  
  naSetLabelText(
    con->uvMetamerics8Label,
    naAllocSprintf(NA_TRUE, "%1.04f", uvMetamericColors.metamericIndex[2]));
  cmUpdateTwoColorController(
    con->uvMetamerics8Display,
    uvMetamericColors.uvStandardRGBFloatData[2],
    uvMetamericColors.uvMetamerRGBFloatData[2]);

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
