
#include "CPWhitePointsController.h"

#include "../CPColorPromptApplication.h"
#include "../CPDesign.h"
#include "CPMetamericsController.h"
#include "../CPTranslations.h"
#include "CPWhitePoints.h"

#include "CML.h"

#include "NAUtility/NABinaryData.h"
#include "NAUtility/NAMemory.h"



struct CPWhitePointsController{
  NASpace* space;

  NALabel* ill10DegLabel;
  NALabel* ill2DegLabel;
  
  NALabel* illTitle;

  NALabel* illXYZTitle;
  NALabel* illYxyTitle;
  NALabel* illYupvpTitle;
  NALabel* illYuvTitle;
  NALabel* illYcdTitle;
  NALabel* illUVWTitle;

  NALabel* illXYZ10Label;
  NALabel* illYxy10Label;
  NALabel* illYupvp10Label;
  NALabel* illYuv10Label;
  NALabel* illYcd10Label;
  NALabel* illUVW10Label;

  NALabel* illXYZ2Label;
  NALabel* illYxy2Label;
  NALabel* illYupvp2Label;
  NALabel* illYuv2Label;
  NALabel* illYcd2Label;
  NALabel* illUVW2Label;
  
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

  CPReferenceIlluminationType referenceIlluminationType;
};

static const double fourValuesWidth = 4 * labelValueWidth + 3 * marginH;



NABool cmSelectRefSpectrum(NAReaction reaction){
  CPWhitePointsController* con = (CPWhitePointsController*)reaction.controller;
  if(reaction.uiElement == con->refD50MenuItem){
    con->referenceIlluminationType = REFERENCE_ILLUMINATION_D50;
  }else if(reaction.uiElement == con->refD55MenuItem){
    con->referenceIlluminationType = REFERENCE_ILLUMINATION_D55;
  }else if(reaction.uiElement == con->refD65MenuItem){
    con->referenceIlluminationType = REFERENCE_ILLUMINATION_D65;
  }else if(reaction.uiElement == con->refD75MenuItem){
    con->referenceIlluminationType = REFERENCE_ILLUMINATION_D75;
  }

  cpUpdateMetamerics();

  return NA_TRUE;
}



CPWhitePointsController* cmAllocWhitePointsController(void){
  CPWhitePointsController* con = naAlloc(CPWhitePointsController);

  con->space = naNewSpace(naMakeSize(1, 1));

  // Illumination whitepoint
  
  con->ill10DegLabel = cpNewTitleLabel(cpTranslate(CPObserverDegree10), degreeWidth);
  con->ill2DegLabel = cpNewTitleLabel(cpTranslate(CPObserverDegree2), degreeWidth);

  con->illTitle = cpNewTitleLabel("", fourValuesWidth);
//  naSetLabelTextAlignment(con->illTitle, NA_TEXT_ALIGNMENT_CENTER);

  con->illXYZTitle = cpNewTitleLabel(cpTranslate(CPColorSpaceXYZ), labelValueWidth);
  con->illYxyTitle = cpNewTitleLabel(cpTranslate(CPColorSpaceYxy), labelValueWidth);
  con->illYupvpTitle = cpNewTitleLabel(cpTranslate(CPColorSpaceYupvp), labelValueWidth);
  con->illYuvTitle = cpNewTitleLabel(cpTranslate(CPColorSpaceYuv), labelValueWidth);
//  con->illYcdTitle = cpNewTitleLabel(cpTranslate(CPColorSpaceYcd), labelValueWidth);
//  con->illUVWTitle = cpNewTitleLabel(cpTranslate(CPColorSpaceUVW), labelValueWidth);
  naSetLabelTextAlignment(con->illXYZTitle, NA_TEXT_ALIGNMENT_CENTER);
  naSetLabelTextAlignment(con->illYxyTitle, NA_TEXT_ALIGNMENT_CENTER);
  naSetLabelTextAlignment(con->illYupvpTitle, NA_TEXT_ALIGNMENT_CENTER);
  naSetLabelTextAlignment(con->illYuvTitle, NA_TEXT_ALIGNMENT_CENTER);
//  naSetLabelTextAlignment(con->illYcdTitle, NA_TEXT_ALIGNMENT_CENTER);
//  naSetLabelTextAlignment(con->illUVWTitle, NA_TEXT_ALIGNMENT_CENTER);

  con->illXYZ10Label = cpNewThreeValueLabel();
  con->illYxy10Label = cpNewThreeValueLabel();
  con->illYupvp10Label = cpNewThreeValueLabel();
  con->illYuv10Label = cpNewThreeValueLabel();
//  con->illYcd10Label = cpNewThreeValueLabel();
//  con->illUVW10Label = cpNewThreeValueLabel();
  
  con->illXYZ2Label = cpNewThreeValueLabel();
  con->illYxy2Label = cpNewThreeValueLabel();
  con->illYupvp2Label = cpNewThreeValueLabel();
  con->illYuv2Label = cpNewThreeValueLabel();
//  con->illYcd2Label = cpNewThreeValueLabel();
//  con->illUVW2Label = cpNewThreeValueLabel();

  // Reference whitepoint

  con->ref10DegLabel = cpNewTitleLabel(cpTranslate(CPObserverDegree10), degreeWidth);
  con->ref2DegLabel = cpNewTitleLabel(cpTranslate(CPObserverDegree2), degreeWidth);

  con->refTitle = cpNewTitleLabel(cpTranslate(CPReferenceIllumination), 80);

  con->refPopupButton = naNewPopupButton(70);
  con->refD50MenuItem = naNewMenuItem(cpTranslate(CPD50));
  con->refD55MenuItem = naNewMenuItem(cpTranslate(CPD55));
  con->refD65MenuItem = naNewMenuItem(cpTranslate(CPD65));
  con->refD75MenuItem = naNewMenuItem(cpTranslate(CPD75));
  naAddPopupButtonMenuItem(con->refPopupButton, con->refD50MenuItem, NA_NULL);
  naAddPopupButtonMenuItem(con->refPopupButton, con->refD55MenuItem, NA_NULL);
  naAddPopupButtonMenuItem(con->refPopupButton, con->refD65MenuItem, NA_NULL);
  naAddPopupButtonMenuItem(con->refPopupButton, con->refD75MenuItem, NA_NULL);
  naAddUIReaction(con->refD50MenuItem, NA_UI_COMMAND_PRESSED, cmSelectRefSpectrum, con);
  naAddUIReaction(con->refD55MenuItem, NA_UI_COMMAND_PRESSED, cmSelectRefSpectrum, con);
  naAddUIReaction(con->refD65MenuItem, NA_UI_COMMAND_PRESSED, cmSelectRefSpectrum, con);
  naAddUIReaction(con->refD75MenuItem, NA_UI_COMMAND_PRESSED, cmSelectRefSpectrum, con);

  con->refXYZ10Label = cpNewThreeValueLabel();
  con->refYxy10Label = cpNewThreeValueLabel();
  con->refYupvp10Label = cpNewThreeValueLabel();
  con->refYuv10Label = cpNewThreeValueLabel();
  
  con->refXYZ2Label = cpNewThreeValueLabel();
  con->refYxy2Label = cpNewThreeValueLabel();
  con->refYupvp2Label = cpNewThreeValueLabel();
  con->refYuv2Label = cpNewThreeValueLabel();



  // Adding elements to the space

  cpBeginUILayout(con->space, naMakeBezel4(spaceMarginRight, spaceMarginTop, spaceMarginDegreeLeft, spaceMarginBottom));
  cpAddUIRow(con->illTitle, uiElemHeight);
  
  cpAddUIRow(con->illXYZTitle, uiElemHeight);
  cpAddUICol(con->illYxyTitle, marginH);
  cpAddUICol(con->illYupvpTitle, marginH);
  cpAddUICol(con->illYuvTitle, marginH);
//  cpAddUICol(con->illYcdTitle, marginH);
//  cpAddUICol(con->illUVWTitle, marginH);

  cpAddUIPos(0, threeValueHeightMargin);
  cpAddUIRow(con->illXYZ10Label, threeValueHeight);
  cpAddUICol(con->illYxy10Label, marginH);
  cpAddUICol(con->illYupvp10Label, marginH);
  cpAddUICol(con->illYuv10Label, marginH);
//  cpAddUICol(con->illYcd10Label, marginH);
//  cpAddUICol(con->illUVW10Label, marginH);

  cpAddUIPos(0, threeValueHeightMargin);
  cpAddUIRow(con->illXYZ2Label, 0);
  cpAddUICol(con->illYxy2Label, marginH);
  cpAddUICol(con->illYupvp2Label, marginH);
  cpAddUICol(con->illYuv2Label, marginH);
//  cpAddUICol(con->illYcd2Label, marginH);
//  cpAddUICol(con->illUVW2Label, marginH);

  cpAddUIPos(0, spaceMarginV);
  
  cpAddUIRow(con->refTitle, uiElemHeight);
  cpAddUICol(con->refPopupButton, 5.);

  cpAddUIPos(0, threeValueHeightMargin);
  cpAddUIRow(con->refXYZ10Label, threeValueHeight);
  cpAddUICol(con->refYxy10Label, marginH);
  cpAddUICol(con->refYupvp10Label, marginH);
  cpAddUICol(con->refYuv10Label, marginH);

  cpAddUIPos(0, threeValueHeightMargin);
  cpAddUIRow(con->refXYZ2Label, 0);
  cpAddUICol(con->refYxy2Label, marginH);
  cpAddUICol(con->refYupvp2Label, marginH);
  cpAddUICol(con->refYuv2Label, marginH);

  cpEndUILayout();

  naAddSpaceChild(con->space, con->ill10DegLabel, naMakePos(spaceMarginLeft, 286));
  naAddSpaceChild(con->space, con->ill2DegLabel, naMakePos(spaceMarginLeft, 221));

  naAddSpaceChild(con->space, con->ref10DegLabel, naMakePos(spaceMarginLeft, 103));
  naAddSpaceChild(con->space, con->ref2DegLabel, naMakePos(spaceMarginLeft, 38));

  con->referenceIlluminationType = REFERENCE_ILLUMINATION_D50;

  return con;
}



void cmDeallocWhitePointsController(CPWhitePointsController* con){
  naFree(con);
}



NASpace* cmGetWhitePointsUIElement(CPWhitePointsController* con){
  return con->space;
}

CPReferenceIlluminationType cmGetReferenceIlluminationType(CPWhitePointsController* con){
  return con->referenceIlluminationType;
}



void cmUpdateWhitePointsController(
  CPWhitePointsController* con,
  const NAUTF8Char* illuminationName,
  const CPWhitePoints* illWhitePoint10,
  const CPWhitePoints* illWhitePoint2,
  const CPWhitePoints* refWhitePoint10,
  const CPWhitePoints* refWhitePoint2)
{
  // current whitepoint
  naSetLabelText(
    con->illTitle,
    naAllocSprintf(NA_TRUE, cpTranslate(CPCurrentIllumination), illuminationName));

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
//  naSetLabelText(
//    con->illYcd10Label,
//    naAllocSprintf(NA_TRUE, "%1.05f\n%1.05f\n%1.05f", illWhitePoint10->Ycd[0], illWhitePoint10->Ycd[1], illWhitePoint10->Ycd[2]));
//  naSetLabelText(
//    con->illUVW10Label,
//    naAllocSprintf(NA_TRUE, "%1.05f\n%1.05f\n%3.03f", illWhitePoint10->UVW[0], illWhitePoint10->UVW[1], illWhitePoint10->UVW[2]));

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
//  naSetLabelText(
//    con->illYcd2Label,
//    naAllocSprintf(NA_TRUE, "%1.05f\n%1.05f\n%1.05f", illWhitePoint2->Ycd[0], illWhitePoint2->Ycd[1], illWhitePoint2->Ycd[2]));
//  naSetLabelText(
//    con->illUVW2Label,
//    naAllocSprintf(NA_TRUE, "%1.05f\n%1.05f\n%3.03f", illWhitePoint2->UVW[0], illWhitePoint2->UVW[1], illWhitePoint2->UVW[2]));



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
