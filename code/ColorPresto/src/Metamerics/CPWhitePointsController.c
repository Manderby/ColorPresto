
#include "CPWhitePointsController.h"

#include "../CPColorPrestoApplication.h"
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
  NASelect* refSelect;
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



void cp_SelectRefSpectrum(NAReaction reaction) {
  CPWhitePointsController* con = (CPWhitePointsController*)reaction.controller;
  if(reaction.uiElement == con->refD50MenuItem) {
    con->referenceIlluminationType = REFERENCE_ILLUMINATION_D50;
  }else if(reaction.uiElement == con->refD55MenuItem) {
    con->referenceIlluminationType = REFERENCE_ILLUMINATION_D55;
  }else if(reaction.uiElement == con->refD65MenuItem) {
    con->referenceIlluminationType = REFERENCE_ILLUMINATION_D65;
  }else if(reaction.uiElement == con->refD75MenuItem) {
    con->referenceIlluminationType = REFERENCE_ILLUMINATION_D75;
  }

  cpUpdateMetamerics();
}



CPWhitePointsController* cpAllocWhitePointsController(void) {
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
  naSetLabelTextAlignment(con->illXYZTitle, NA_ALIGNMENT_CENTER);
  naSetLabelTextAlignment(con->illYxyTitle, NA_ALIGNMENT_CENTER);
  naSetLabelTextAlignment(con->illYupvpTitle, NA_ALIGNMENT_CENTER);
  naSetLabelTextAlignment(con->illYuvTitle, NA_ALIGNMENT_CENTER);

  con->illXYZ10Label = cpNewThreeValueLabel();
  con->illYxy10Label = cpNewThreeValueLabel();
  con->illYupvp10Label = cpNewThreeValueLabel();
  con->illYuv10Label = cpNewThreeValueLabel();
  
  con->illXYZ2Label = cpNewThreeValueLabel();
  con->illYxy2Label = cpNewThreeValueLabel();
  con->illYupvp2Label = cpNewThreeValueLabel();
  con->illYuv2Label = cpNewThreeValueLabel();

  // Reference whitepoint

  con->ref10DegLabel = cpNewTitleLabel(cpTranslate(CPObserverDegree10), degreeWidth);
  con->ref2DegLabel = cpNewTitleLabel(cpTranslate(CPObserverDegree2), degreeWidth);

  con->refTitle = cpNewTitleLabel(cpTranslate(CPReferenceIllumination), 80);

  con->refSelect = naNewSelect(70);
  con->refD50MenuItem = naNewMenuItem(cpTranslate(CPD50), NA_NULL);
  con->refD55MenuItem = naNewMenuItem(cpTranslate(CPD55), NA_NULL);
  con->refD65MenuItem = naNewMenuItem(cpTranslate(CPD65), NA_NULL);
  con->refD75MenuItem = naNewMenuItem(cpTranslate(CPD75), NA_NULL);
  naAddSelectMenuItem(con->refSelect, con->refD50MenuItem, NA_NULL);
  naAddSelectMenuItem(con->refSelect, con->refD55MenuItem, NA_NULL);
  naAddSelectMenuItem(con->refSelect, con->refD65MenuItem, NA_NULL);
  naAddSelectMenuItem(con->refSelect, con->refD75MenuItem, NA_NULL);
  naAddUIReaction(con->refD50MenuItem, NA_UI_COMMAND_PRESSED, cp_SelectRefSpectrum, con);
  naAddUIReaction(con->refD55MenuItem, NA_UI_COMMAND_PRESSED, cp_SelectRefSpectrum, con);
  naAddUIReaction(con->refD65MenuItem, NA_UI_COMMAND_PRESSED, cp_SelectRefSpectrum, con);
  naAddUIReaction(con->refD75MenuItem, NA_UI_COMMAND_PRESSED, cp_SelectRefSpectrum, con);

  con->refXYZ10Label = cpNewThreeValueLabel();
  con->refYxy10Label = cpNewThreeValueLabel();
  con->refYupvp10Label = cpNewThreeValueLabel();
  con->refYuv10Label = cpNewThreeValueLabel();
  
  con->refXYZ2Label = cpNewThreeValueLabel();
  con->refYxy2Label = cpNewThreeValueLabel();
  con->refYupvp2Label = cpNewThreeValueLabel();
  con->refYuv2Label = cpNewThreeValueLabel();



  // Adding elements to the space

  NABorder2D zeroPadding = naMakeBorder2D(0., 0., 0., 0.);
  NABorder2D spacePadding = naMakeBorder2D(0., 0., 0., spaceInterMargin);

//  naDebugUIElementLayout(con->space);

  naBeginLayout(con->space, naMakeBorder2D(spaceMarginLeft, spaceMarginRight, spaceMarginTop, spaceInterMargin));
  
    naAddLayoutSection(uiElemHeight, spacePadding);
      naAddLayoutElement(con->illTitle, degreeWidth, fourValuesWidth);

    naAddLayoutSection(uiElemHeight, spacePadding);
      naAddLayoutElement(con->illXYZTitle, degreeWidth, labelValueWidth);
      naAddLayoutElement(con->illYxyTitle, marginH, labelValueWidth);
      naAddLayoutElement(con->illYupvpTitle, marginH, labelValueWidth);
      naAddLayoutElement(con->illYuvTitle, marginH, labelValueWidth);

    naAddLayoutSection(threeValueHeight, spacePadding);
      naAddLayoutElement(con->ill10DegLabel, 0, degreeWidth);
      naAddLayoutElement(con->illXYZ10Label, 0, labelValueWidth);
      naSetLayoutElementAlignBaseline(NA_FALSE);
      naAddLayoutElement(con->illYxy10Label, marginH, labelValueWidth);
      naSetLayoutElementAlignBaseline(NA_FALSE);
      naAddLayoutElement(con->illYupvp10Label, marginH, labelValueWidth);
      naSetLayoutElementAlignBaseline(NA_FALSE);
      naAddLayoutElement(con->illYuv10Label, marginH, labelValueWidth);
      naSetLayoutElementAlignBaseline(NA_FALSE);

    naAddLayoutSection(threeValueHeight, spacePadding);
      naAddLayoutElement(con->ill2DegLabel, 0, degreeWidth);
      naAddLayoutElement(con->illXYZ2Label, 0, labelValueWidth);
      naSetLayoutElementAlignBaseline(NA_FALSE);
      naAddLayoutElement(con->illYxy2Label, marginH, labelValueWidth);
      naSetLayoutElementAlignBaseline(NA_FALSE);
      naAddLayoutElement(con->illYupvp2Label, marginH, labelValueWidth);
      naSetLayoutElementAlignBaseline(NA_FALSE);
      naAddLayoutElement(con->illYuv2Label, marginH, labelValueWidth);
      naSetLayoutElementAlignBaseline(NA_FALSE);
    
    naAddLayoutSection(uiElemHeight, naMakeBorder2D(0., 0., spaceMarginTop, spaceInterMargin));
      naAddLayoutElement(con->refTitle, degreeWidth, 80);
      naAddLayoutElement(con->refSelect, 8., 70);

    naAddLayoutSection(threeValueHeight, spacePadding);
      naAddLayoutElement(con->ref10DegLabel, 0, degreeWidth);
      naAddLayoutElement(con->refXYZ10Label, 0, labelValueWidth);
      naSetLayoutElementAlignBaseline(NA_FALSE);
      naAddLayoutElement(con->refYxy10Label, marginH, labelValueWidth);
      naSetLayoutElementAlignBaseline(NA_FALSE);
      naAddLayoutElement(con->refYupvp10Label, marginH, labelValueWidth);
      naSetLayoutElementAlignBaseline(NA_FALSE);
      naAddLayoutElement(con->refYuv10Label, marginH, labelValueWidth);
      naSetLayoutElementAlignBaseline(NA_FALSE);

    naAddLayoutSection(threeValueHeight, spacePadding);
      naAddLayoutElement(con->ref2DegLabel, 0, degreeWidth);
      naAddLayoutElement(con->refXYZ2Label, 0, labelValueWidth);
      naSetLayoutElementAlignBaseline(NA_FALSE);
      naAddLayoutElement(con->refYxy2Label, marginH, labelValueWidth);
      naSetLayoutElementAlignBaseline(NA_FALSE);
      naAddLayoutElement(con->refYupvp2Label, marginH, labelValueWidth);
      naSetLayoutElementAlignBaseline(NA_FALSE);
      naAddLayoutElement(con->refYuv2Label, marginH, labelValueWidth);
      naSetLayoutElementAlignBaseline(NA_FALSE);

  naEndLayout();

  con->referenceIlluminationType = REFERENCE_ILLUMINATION_D50;

  return con;
}



void cpDeallocWhitePointsController(CPWhitePointsController* con) {
  naFree(con);
}



NASpace* cpGetWhitePointsUIElement(CPWhitePointsController* con) {
  return con->space;
}

CPReferenceIlluminationType cpGetReferenceIlluminationType(CPWhitePointsController* con) {
  return con->referenceIlluminationType;
}



void cpUpdateWhitePointsController(
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
