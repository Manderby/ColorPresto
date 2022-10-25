
#include "CMMetamericsController.h"

#include "CMChromaticityErrorController.h"
#include "CMWhitePointsController.h"

#include "CMColorConversionsYcdUVW.h"
#include "CMColorRenderingIndexController.h"
#include "CMTranslations.h"
#include "CMTwoColorController.h"
#include "CMTotalMetamericIndexController.h"
#include "CMUVMetamericIndexController.h"
#include "CMVisMetamericIndexController.h"
#include "CMWhitePoints.h"
#include "NAApp.h"
#include "CML.h"
#include "mainC.h"
#include "CMDesign.h"



struct CMMetamericsController{
  NAWindow* window;
  
  NASpace* column1Space;
  NASpace* column2Space;
  NASpace* column3Space;
  
  CMWhitePointsController* whitePointsController;
  CMChromaticityErrorController* chromaticityErrorController;
  CMColorRenderingIndexController* colorRenderingIndexController;
  CMVisMetamericIndexController* visMetamericIndexController;
  CMUVMetamericIndexController* uvMetamericIndexController;
  CMTotalMetamericIndexController* totalMetamericIndexController;
};



CMMetamericsController* cmAllocMetamericsController(void){
  CMMetamericsController* con = naAlloc(CMMetamericsController);
  naZeron(con, sizeof(CMMetamericsController));

  con->chromaticityErrorController = cmAllocChromaticityErrorController();
  con->whitePointsController = cmAllocWhitePointsController();
  con->colorRenderingIndexController = cmAllocColorRenderingIndexController();
  con->visMetamericIndexController = cmAllocVisMetamericIndexController();
  con->uvMetamericIndexController = cmAllocUVMetamericIndexController();
  con->totalMetamericIndexController = cmAllocTotalMetamericIndexController();

  NASpace* whitePointsSpace = cmGetWhitePointsUIElement(con->whitePointsController);
  NASpace* chromaticityErrorSpace = cmGetChromaticityErrorUIElement(con->chromaticityErrorController);
  NASpace* rolorRenderingIndexSpace = cmGetColorRenderingIndexUIElement(con->colorRenderingIndexController);
  NASpace* visMetamericIndexSpace = cmGetVisMetamericIndexUIElement(con->visMetamericIndexController);
  NASpace* uvMetamericIndexSpace = cmGetUVMetamericIndexUIElement(con->uvMetamericIndexController);
  NASpace* totalMetamericIndexSpace = cmGetTotalMetamericIndexUIElement(con->totalMetamericIndexController);

  NASize whitePointsSize = naGetUIElementRect(whitePointsSpace, NA_NULL, NA_FALSE).size;
  NASize chromaticityErrorSize = naGetUIElementRect(chromaticityErrorSpace, NA_NULL, NA_FALSE).size;
  NASize colorRenderingIndexSize = naGetUIElementRect(rolorRenderingIndexSpace, NA_NULL, NA_FALSE).size;
  NASize visMetamericIndexSize = naGetUIElementRect(visMetamericIndexSpace, NA_NULL, NA_FALSE).size;
  NASize uvMetamericIndexSize = naGetUIElementRect(uvMetamericIndexSpace, NA_NULL, NA_FALSE).size;
  NASize totalMetamericIndexSize = naGetUIElementRect(totalMetamericIndexSpace, NA_NULL, NA_FALSE).size;

  double column1Height = whitePointsSize.height + chromaticityErrorSize.height;
  double column1Width = naMax(whitePointsSize.width, chromaticityErrorSize.width);
  double column2Height = colorRenderingIndexSize.height;
  double column2Width = colorRenderingIndexSize.width;
  double column3Height = visMetamericIndexSize.height + uvMetamericIndexSize.height + totalMetamericIndexSize.height;
  double column3Width = naMax(naMax(visMetamericIndexSize.width, uvMetamericIndexSize.width), totalMetamericIndexSize.width);

//  double windowWidth = column1Width + column2Width + column3Width;
//  double windowHeight = naMax(naMax(column1Height, column2Height), column3Height);

  con->window = naNewWindow(
    cmTranslate(CMWhitepointsAndMetamerics),
    naMakeRectS(400, 500, 1, 1),
    0,
    0);
  NASpace* contentSpace = naGetWindowContentSpace(con->window);
//  NABabyColor babyBackground = {
//    naLinearizeColorValue(.25),
//    naLinearizeColorValue(.25),
//    naLinearizeColorValue(.25),
//    1.};
//  naSetSpaceBackgroundColor(contentSpace, &babyBackground);

  con->column1Space = naNewSpace(naMakeSize(column1Width, column1Height));
  con->column2Space = naNewSpace(naMakeSize(column2Width, column2Height));
  naSetSpaceAlternateBackground(con->column2Space, NA_TRUE);
  con->column3Space = naNewSpace(naMakeSize(column3Width, column3Height));



  // Placing elements in the window

  cmBeginUILayout(con->column1Space, naMakeBezel4Zero());
  cmAddUIRow(whitePointsSpace, 0);
  cmAddUIRow(chromaticityErrorSpace, 0);
  cmEndUILayout();

  cmBeginUILayout(con->column2Space, naMakeBezel4Zero());
  cmAddUIRow(rolorRenderingIndexSpace, 0);
  cmEndUILayout();

  cmBeginUILayout(con->column3Space, naMakeBezel4Zero());
  cmAddUIRow(visMetamericIndexSpace, 0);
  cmAddUIRow(uvMetamericIndexSpace, 0);
  cmAddUIRow(totalMetamericIndexSpace, 0);
  cmEndUILayout();

  cmBeginUILayout(contentSpace, naMakeBezel4Zero());
  cmAddUICol(con->column1Space, 0);
  cmAddUICol(con->column2Space, 0);
  cmAddUICol(con->column3Space, 0);
  cmEndUILayout();

  return con;
}



void cmDeallocMetamericsController(CMMetamericsController* con){
  cmDeallocChromaticityErrorController(con->chromaticityErrorController);
  cmDeallocWhitePointsController(con->whitePointsController);
  cmDeallocColorRenderingIndexController(con->colorRenderingIndexController);
  cmDeallocVisMetamericIndexController(con->visMetamericIndexController);
  cmDeallocUVMetamericIndexController(con->uvMetamericIndexController);
  cmDeallocTotalMetamericIndexController(con->totalMetamericIndexController);

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
    &illWhitePoint10);
    
  cmUpdateColorRenderingIndexController(
    con->colorRenderingIndexController,
    observer2Funcs,
    &illWhitePoint2,
    &refWhitePoint2,
    ref,
    illuminationSpec != NA_NULL);

  cmUpdateVisMetamericIndexController(
    con->visMetamericIndexController,
    observer10Funcs,
    &illWhitePoint10,
    adaptationMatrix,
    referenceIlluminationType,
    illuminationSpec != NA_NULL);

  cmUpdateUVMetamericIndexController(
    con->uvMetamericIndexController,
    observer10Funcs,
    &illWhitePoint10,
    referenceIlluminationType,
    illuminationSpec != NA_NULL);

  cmUpdateTotalMetamericIndexController(
    con->totalMetamericIndexController,
    cmGetVisMetamericIndexAverage(con->visMetamericIndexController),
    cmGetUVMetamericIndexAverage(con->uvMetamericIndexController),
    illuminationSpec != NA_NULL);



  cmlReleaseFunction(observer10Funcs[0]);
  cmlReleaseFunction(observer10Funcs[1]);
  cmlReleaseFunction(observer10Funcs[2]);
}
