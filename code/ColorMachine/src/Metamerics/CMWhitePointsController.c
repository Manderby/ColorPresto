
#include "CMWhitePointsController.h"

#include "CMDesign.h"
#include "CMMetamericsController.h"
#include "CMTranslations.h"
#include "CMWhitePoints.h"

#include "CML.h"

#include "NAUtility/NABinaryData.h"
#include "NAUtility/NAMemory.h"



struct CMWhitePointsController{
  NASpace* space;

  NALabel* ill10DegLabel;
  NALabel* ill2DegLabel;
  
  NALabel* illTitle;

  NALabel* illXYZTitle;
  NALabel* illYxyTitle;
  NALabel* illYupvpTitle;
  NALabel* illYuvTitle;

  NALabel* illXYZ10Label;
  NALabel* illYxy10Label;
  NALabel* illYupvp10Label;
  NALabel* illYuv10Label;

  NALabel* illXYZ2Label;
  NALabel* illYxy2Label;
  NALabel* illYupvp2Label;
  NALabel* illYuv2Label;
  
  NALabel* ref10DegLabel;
  NALabel* ref2DegLabel;

  NALabel* refTitle;
  NAPopupButton* refPopupButton;
  NAMenuItem* refD50MenuItem;
  NAMenuItem* refD55MenuItem;
  NAMenuItem* refD65MenuItem;
  NAMenuItem* refD75MenuItem;

  NALabel* refXYZ10Label;
  NALabel* refYxy10Label;
  NALabel* refYupvp10Label;
  NALabel* refYuv10Label;

  NALabel* refXYZ2Label;
  NALabel* refYxy2Label;
  NALabel* refYupvp2Label;
  NALabel* refYuv2Label;

  CMReferenceIlluminationType referenceIlluminationType;
};

static const double fourValuesWidth = 4 * valueWidth + 3 * marginH;



NABool cmSelectRefSpectrum(NAReaction reaction){
  CMWhitePointsController* con = (CMWhitePointsController*)reaction.controller;
  if(reaction.uiElement == con->refD50MenuItem){
    con->referenceIlluminationType = REFERENCE_ILLUMINATION_D50;
  }else if(reaction.uiElement == con->refD55MenuItem){
    con->referenceIlluminationType = REFERENCE_ILLUMINATION_D55;
  }else if(reaction.uiElement == con->refD65MenuItem){
    con->referenceIlluminationType = REFERENCE_ILLUMINATION_D65;
  }else if(reaction.uiElement == con->refD75MenuItem){
    con->referenceIlluminationType = REFERENCE_ILLUMINATION_D75;
  }

  cmUpdateMetamerics();

  return NA_TRUE;
}



CMWhitePointsController* cmAllocWhitePointsController(void){
  CMWhitePointsController* con = naAlloc(CMWhitePointsController);
  naZeron(con, sizeof(CMWhitePointsController));

  double spaceWidth = spaceMarginLeft + degreeWidth + 4 * valueWidth + 3 * marginH + spaceMarginRight;
  double spaceHeight = 4 * uiElemHeight + 4 * threeValueMargin + spaceMarginV;

  con->space = naNewSpace(naMakeSize(spaceWidth, spaceHeight));
//  naSetSpaceAlternateBackground(con->space, NA_TRUE);

  // Illumination whitepoint
  
  con->ill10DegLabel = cmNewTitleLabel(cmTranslate(CMObserverDegree10), degreeWidth);
  con->ill2DegLabel = cmNewTitleLabel(cmTranslate(CMObserverDegree2), degreeWidth);

  con->illTitle = cmNewTitleLabel("", fourValuesWidth);
  naSetLabelTextAlignment(con->illTitle, NA_TEXT_ALIGNMENT_CENTER);

  con->illXYZTitle = cmNewTitleLabel(cmTranslate(CMColorSpaceXYZ), valueWidth);
  naSetLabelTextAlignment(con->illXYZTitle, NA_TEXT_ALIGNMENT_CENTER);
  con->illYxyTitle = cmNewTitleLabel(cmTranslate(CMColorSpaceYxy), valueWidth);
  naSetLabelTextAlignment(con->illYxyTitle, NA_TEXT_ALIGNMENT_CENTER);
  con->illYupvpTitle = cmNewTitleLabel(cmTranslate(CMColorSpaceYupvp), valueWidth);
  naSetLabelTextAlignment(con->illYupvpTitle, NA_TEXT_ALIGNMENT_CENTER);
  con->illYuvTitle = cmNewTitleLabel(cmTranslate(CMColorSpaceYuv), valueWidth);
  naSetLabelTextAlignment(con->illYuvTitle, NA_TEXT_ALIGNMENT_CENTER);

  con->illXYZ10Label = cmNewThreeValueLabel();
  con->illYxy10Label = cmNewThreeValueLabel();
  con->illYupvp10Label = cmNewThreeValueLabel();
  con->illYuv10Label = cmNewThreeValueLabel();
  
  con->illXYZ2Label = cmNewThreeValueLabel();
  con->illYxy2Label = cmNewThreeValueLabel();
  con->illYupvp2Label = cmNewThreeValueLabel();
  con->illYuv2Label = cmNewThreeValueLabel();

  // Reference whitepoint

  con->ref10DegLabel = cmNewTitleLabel(cmTranslate(CMObserverDegree10), degreeWidth);
  con->ref2DegLabel = cmNewTitleLabel(cmTranslate(CMObserverDegree2), degreeWidth);

  con->refTitle = cmNewTitleLabel(cmTranslate(CMReferenceIllumination), 80);

  con->refPopupButton = naNewPopupButton(70);
  con->refD50MenuItem = naNewMenuItem("D50");
  con->refD55MenuItem = naNewMenuItem("D55");
  con->refD65MenuItem = naNewMenuItem("D65");
  con->refD75MenuItem = naNewMenuItem("D75");
  naAddPopupButtonMenuItem(con->refPopupButton, con->refD50MenuItem, NA_NULL);
  naAddPopupButtonMenuItem(con->refPopupButton, con->refD55MenuItem, NA_NULL);
  naAddPopupButtonMenuItem(con->refPopupButton, con->refD65MenuItem, NA_NULL);
  naAddPopupButtonMenuItem(con->refPopupButton, con->refD75MenuItem, NA_NULL);
  naAddUIReaction(con->refD50MenuItem, NA_UI_COMMAND_PRESSED, cmSelectRefSpectrum, con);
  naAddUIReaction(con->refD55MenuItem, NA_UI_COMMAND_PRESSED, cmSelectRefSpectrum, con);
  naAddUIReaction(con->refD65MenuItem, NA_UI_COMMAND_PRESSED, cmSelectRefSpectrum, con);
  naAddUIReaction(con->refD75MenuItem, NA_UI_COMMAND_PRESSED, cmSelectRefSpectrum, con);

  con->refXYZ10Label = cmNewThreeValueLabel();
  con->refYxy10Label = cmNewThreeValueLabel();
  con->refYupvp10Label = cmNewThreeValueLabel();
  con->refYuv10Label = cmNewThreeValueLabel();
  
  con->refXYZ2Label = cmNewThreeValueLabel();
  con->refYxy2Label = cmNewThreeValueLabel();
  con->refYupvp2Label = cmNewThreeValueLabel();
  con->refYuv2Label = cmNewThreeValueLabel();



  // Adding elements to the space

  double spaceY = spaceHeight - spaceMarginTop;
  spaceY -= uiElemHeight;
  naAddSpaceChild(con->space, con->illTitle, naMakePos(spaceMarginDegreeLeft, spaceY));
  spaceY -= uiElemHeight;
  naAddSpaceChild(con->space, con->illXYZTitle, naMakePos(spaceMarginDegreeLeft + 0 * (valueWidth + marginH), spaceY));
  naAddSpaceChild(con->space, con->illYxyTitle, naMakePos(spaceMarginDegreeLeft + 1 * (valueWidth + marginH), spaceY));
  naAddSpaceChild(con->space, con->illYupvpTitle, naMakePos(spaceMarginDegreeLeft + 2 * (valueWidth + marginH), spaceY));
  naAddSpaceChild(con->space, con->illYuvTitle, naMakePos(spaceMarginDegreeLeft + 3 * (valueWidth + marginH), spaceY));
  spaceY -= threeValueMargin;
  naAddSpaceChild(con->space, con->illXYZ10Label, naMakePos(spaceMarginDegreeLeft + 0 * (valueWidth + marginH), spaceY));
  naAddSpaceChild(con->space, con->illYxy10Label, naMakePos(spaceMarginDegreeLeft + 1 * (valueWidth + marginH), spaceY));
  naAddSpaceChild(con->space, con->illYupvp10Label, naMakePos(spaceMarginDegreeLeft + 2 * (valueWidth + marginH), spaceY));
  naAddSpaceChild(con->space, con->illYuv10Label, naMakePos(spaceMarginDegreeLeft + 3 * (valueWidth + marginH), spaceY));

  spaceY -= threeValueMargin;
  naAddSpaceChild(con->space, con->illXYZ2Label, naMakePos(spaceMarginDegreeLeft + 0 * (valueWidth + marginH), spaceY));
  naAddSpaceChild(con->space, con->illYxy2Label, naMakePos(spaceMarginDegreeLeft + 1 * (valueWidth + marginH), spaceY));
  naAddSpaceChild(con->space, con->illYupvp2Label, naMakePos(spaceMarginDegreeLeft + 2 * (valueWidth + marginH), spaceY));
  naAddSpaceChild(con->space, con->illYuv2Label, naMakePos(spaceMarginDegreeLeft + 3 * (valueWidth + marginH), spaceY));

  naAddSpaceChild(con->space, con->ill10DegLabel, naMakePos(spaceMarginLeft, 283));
  naAddSpaceChild(con->space, con->ill2DegLabel, naMakePos(spaceMarginLeft, 218));



  spaceY -= 2 * uiElemHeight;
  naAddSpaceChild(con->space, con->refTitle, naMakePos(120, spaceY));
  naAddSpaceChild(con->space, con->refPopupButton, naMakePos(200, spaceY));
  spaceY -= threeValueMargin;
  naAddSpaceChild(con->space, con->refXYZ10Label, naMakePos(spaceMarginDegreeLeft + 0 * (valueWidth + marginH), spaceY));
  naAddSpaceChild(con->space, con->refYxy10Label, naMakePos(spaceMarginDegreeLeft + 1 * (valueWidth + marginH), spaceY));
  naAddSpaceChild(con->space, con->refYupvp10Label, naMakePos(spaceMarginDegreeLeft + 2 * (valueWidth + marginH), spaceY));
  naAddSpaceChild(con->space, con->refYuv10Label, naMakePos(spaceMarginDegreeLeft + 3 * (valueWidth + marginH), spaceY));

  spaceY -= threeValueMargin;
  naAddSpaceChild(con->space, con->refXYZ2Label, naMakePos(spaceMarginDegreeLeft + 0 * (valueWidth + marginH), spaceY));
  naAddSpaceChild(con->space, con->refYxy2Label, naMakePos(spaceMarginDegreeLeft + 1 * (valueWidth + marginH), spaceY));
  naAddSpaceChild(con->space, con->refYupvp2Label, naMakePos(spaceMarginDegreeLeft + 2 * (valueWidth + marginH), spaceY));
  naAddSpaceChild(con->space, con->refYuv2Label, naMakePos(spaceMarginDegreeLeft + 3 * (valueWidth + marginH), spaceY));

  naAddSpaceChild(con->space, con->ref10DegLabel, naMakePos(spaceMarginLeft, 103));
  naAddSpaceChild(con->space, con->ref2DegLabel, naMakePos(spaceMarginLeft, 38));



  con->referenceIlluminationType = REFERENCE_ILLUMINATION_D50;

  return con;
}



void cmDeallocWhitePointsController(CMWhitePointsController* con){
  naFree(con);
}



NASpace* cmGetWhitePointsUIElement(CMWhitePointsController* con){
  return con->space;
}

CMReferenceIlluminationType cmGetReferenceIlluminationType(CMWhitePointsController* con){
  return con->referenceIlluminationType;
}



void cmUpdateWhitePointsController(
  CMWhitePointsController* con,
  const NAUTF8Char* illuminationName,
  const CMWhitePoints* illWhitePoint10,
  const CMWhitePoints* illWhitePoint2,
  const CMWhitePoints* refWhitePoint10,
  const CMWhitePoints* refWhitePoint2)
{
  // current whitepoint
  naSetLabelText(
    con->illTitle,
    naAllocSprintf(NA_TRUE, cmTranslate(CMCurrentIllumination), illuminationName));

  naSetLabelText(
    con->illXYZ10Label,
    naAllocSprintf(NA_TRUE, "%1.05f\n%1.05f\n%1.05f", illWhitePoint10->XYZ[0], illWhitePoint10->XYZ[1], illWhitePoint10->XYZ[2]));
  naSetLabelText(
    con->illYxy10Label,
    naAllocSprintf(NA_TRUE, "%1.05f\n%1.05f\n%1.05f", illWhitePoint10->Yxy[0], illWhitePoint10->Yxy[1], illWhitePoint10->Yxy[2]));
  naSetLabelText(
    con->illYupvp10Label,
    naAllocSprintf(NA_TRUE, "%1.05f\n%1.05f\n%1.05f", illWhitePoint10->Yupvp[0], illWhitePoint10->Yupvp[1], illWhitePoint10->Yupvp[2]));
  naSetLabelText(
    con->illYuv10Label,
    naAllocSprintf(NA_TRUE, "%1.05f\n%1.05f\n%1.05f", illWhitePoint10->Yuv[0], illWhitePoint10->Yuv[1], illWhitePoint10->Yuv[2]));

  naSetLabelText(
    con->illXYZ2Label,
    naAllocSprintf(NA_TRUE, "%1.05f\n%1.05f\n%1.05f", illWhitePoint2->XYZ[0], illWhitePoint2->XYZ[1], illWhitePoint2->XYZ[2]));
  naSetLabelText(
    con->illYxy2Label,
    naAllocSprintf(NA_TRUE, "%1.05f\n%1.05f\n%1.05f", illWhitePoint2->Yxy[0], illWhitePoint2->Yxy[1], illWhitePoint2->Yxy[2]));
  naSetLabelText(
    con->illYupvp2Label,
    naAllocSprintf(NA_TRUE, "%1.05f\n%1.05f\n%1.05f", illWhitePoint2->Yupvp[0], illWhitePoint2->Yupvp[1], illWhitePoint2->Yupvp[2]));
  naSetLabelText(
    con->illYuv2Label,
    naAllocSprintf(NA_TRUE, "%1.05f\n%1.05f\n%1.05f", illWhitePoint2->Yuv[0], illWhitePoint2->Yuv[1], illWhitePoint2->Yuv[2]));



  // Reference whitepoint
  
  naSetLabelText(
    con->refXYZ10Label,
    naAllocSprintf(NA_TRUE, "%1.05f\n%1.05f\n%1.05f", refWhitePoint10->XYZ[0], refWhitePoint10->XYZ[1], refWhitePoint10->XYZ[2]));
  naSetLabelText(
    con->refYxy10Label,
    naAllocSprintf(NA_TRUE, "%1.05f\n%1.05f\n%1.05f", refWhitePoint10->Yxy[0], refWhitePoint10->Yxy[1], refWhitePoint10->Yxy[2]));
  naSetLabelText(
    con->refYupvp10Label,
    naAllocSprintf(NA_TRUE, "%1.05f\n%1.05f\n%1.05f", refWhitePoint10->Yupvp[0], refWhitePoint10->Yupvp[1], refWhitePoint10->Yupvp[2]));
  naSetLabelText(
    con->refYuv10Label,
    naAllocSprintf(NA_TRUE, "%1.05f\n%1.05f\n%1.05f", refWhitePoint10->Yuv[0], refWhitePoint10->Yuv[1], refWhitePoint10->Yuv[2]));

  naSetLabelText(
    con->refXYZ2Label,
    naAllocSprintf(NA_TRUE, "%1.05f\n%1.05f\n%1.05f", refWhitePoint2->XYZ[0], refWhitePoint2->XYZ[1], refWhitePoint2->XYZ[2]));
  naSetLabelText(
    con->refYxy2Label,
    naAllocSprintf(NA_TRUE, "%1.05f\n%1.05f\n%1.05f", refWhitePoint2->Yxy[0], refWhitePoint2->Yxy[1], refWhitePoint2->Yxy[2]));
  naSetLabelText(
    con->refYupvp2Label,
    naAllocSprintf(NA_TRUE, "%1.05f\n%1.05f\n%1.05f", refWhitePoint2->Yupvp[0], refWhitePoint2->Yupvp[1], refWhitePoint2->Yupvp[2]));
  naSetLabelText(
    con->refYuv2Label,
    naAllocSprintf(NA_TRUE, "%1.05f\n%1.05f\n%1.05f", refWhitePoint2->Yuv[0], refWhitePoint2->Yuv[1], refWhitePoint2->Yuv[2]));
}
