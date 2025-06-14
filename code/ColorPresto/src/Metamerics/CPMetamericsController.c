
#include "CPMetamericsController.h"

#include "../CPColorPrestoApplication.h"
#include "../CPTranslations.h"
#include "../main.h"
#include "../CPDesign.h"

#include "CPChromaticityErrorController.h"
#include "CPWhitePointsController.h"
#include "CPColorConversionsYcdUVW.h"
#include "CPColorRenderingIndexController.h"
#include "CPTwoColorController.h"
#include "CPTotalMetamericIndexController.h"
#include "CPUVMetamericIndexController.h"
#include "CPVisMetamericIndexController.h"
#include "CPWhitePoints.h"
#include "CML.h"

#include "NAApp/NAApp.h"



struct CPMetamericsController{
  NAWindow* window;
  
  NASpace* column1Space;
  NASpace* column2Space;
  NASpace* column3Space;
  
  CPWhitePointsController* whitePointsController;
  CPChromaticityErrorController* chromaticityErrorController;
  CPColorRenderingIndexController* colorRenderingIndexController;
  CPVisMetamericIndexController* visMetamericIndexController;
  CPUVMetamericIndexController* uvMetamericIndexController;
  CPTotalMetamericIndexController* totalMetamericIndexController;
};



CPMetamericsController* cpAllocMetamericsController(void){
  CPMetamericsController* con = naAlloc(CPMetamericsController);

  con->chromaticityErrorController = cpAllocChromaticityErrorController();
  con->whitePointsController = cpAllocWhitePointsController();
  con->colorRenderingIndexController = cpAllocColorRenderingIndexController();
  con->visMetamericIndexController = cpAllocVisMetamericIndexController();
  con->uvMetamericIndexController = cpAllocUVMetamericIndexController();
  con->totalMetamericIndexController = cpAllocTotalMetamericIndexController();

  NASpace* whitePointsSpace = cpGetWhitePointsUIElement(con->whitePointsController);
  NASpace* chromaticityErrorSpace = cpGetChromaticityErrorUIElement(con->chromaticityErrorController);
  NASpace* colorRenderingIndexSpace = cpGetColorRenderingIndexUIElement(con->colorRenderingIndexController);
  NASpace* visMetamericIndexSpace = cpGetVisMetamericIndexUIElement(con->visMetamericIndexController);
  NASpace* uvMetamericIndexSpace = cpGetUVMetamericIndexUIElement(con->uvMetamericIndexController);
  NASpace* totalMetamericIndexSpace = cpGetTotalMetamericIndexUIElement(con->totalMetamericIndexController);

  con->window = naNewWindow(
    cpTranslate(CPWhitePointsAndMetamerics),
    naMakeRectS(400, 500, 1, 1),
    0);
  naSetWindowStorageTag(con->window, CP_METAMERICS_WINDOW_STORAGE_TAG);
  NASpace* contentSpace = naGetWindowContentSpace(con->window);
//  NABabyColor babyBackground = {
//    naLinearizeColorValue(.25),
//    naLinearizeColorValue(.25),
//    naLinearizeColorValue(.25),
//    1.};
//  naSetSpaceBackgroundColor(contentSpace, babyBackground);

//  con->column1Space = naNewSpace(naMakeSize(column1Width, column1Height));
//  con->column2Space = naNewSpace(naMakeSize(column2Width, column2Height));
//  naSetSpaceAlternateBackground(con->column2Space, NA_TRUE);
//  con->column3Space = naNewSpace(naMakeSize(column3Width, column3Height));
  con->column1Space = naNewSpace(naMakeSize(1, 1));
  con->column2Space = naNewSpace(naMakeSize(1, 1));
  naSetSpaceAlternateBackground(con->column2Space, NA_TRUE);
  con->column3Space = naNewSpace(naMakeSize(1, 1));



  // Placing elements in the window

  cpBeginUILayout(con->column1Space, naMakeBorder2D(0., 0., 0., 0.));
  cpAddUIRow(whitePointsSpace, 0);
  cpAddUIRow(chromaticityErrorSpace, 0);
  cpEndUILayout();

  cpBeginUILayout(con->column2Space, naMakeBorder2D(0., 0., 0., 0.));
  cpAddUIRow(colorRenderingIndexSpace, 0);
  cpEndUILayout();

  cpBeginUILayout(con->column3Space, naMakeBorder2D(0., 0., 0., 0.));
  cpAddUIRow(visMetamericIndexSpace, 0);
  cpAddUIRow(uvMetamericIndexSpace, 0);
  cpAddUIRow(totalMetamericIndexSpace, 0);
  cpEndUILayout();

  cpBeginUILayout(contentSpace, naMakeBorder2D(0., 0., 0., 0.));
  cpAddUICol(con->column1Space, 0);
  cpAddUICol(con->column2Space, 0);
  cpAddUICol(con->column3Space, 0);
  cpEndUILayout();

  return con;
}



void cpDeallocMetamericsController(CPMetamericsController* con){
  cpDeallocChromaticityErrorController(con->chromaticityErrorController);
  cpDeallocWhitePointsController(con->whitePointsController);
  cpDeallocColorRenderingIndexController(con->colorRenderingIndexController);
  cpDeallocVisMetamericIndexController(con->visMetamericIndexController);
  cpDeallocUVMetamericIndexController(con->uvMetamericIndexController);
  cpDeallocTotalMetamericIndexController(con->totalMetamericIndexController);

  naFree(con);
}



void cpShowMetamericsController(CPMetamericsController* con){
  naShowWindow(con->window);
}



void cpUpdateMetamericsController(CPMetamericsController* con){
  CMLColorMachine* cm = cpGetCurrentColorMachine();

  CMLFunction* observer10Funcs[3];
  cmlCreateSpecDistFunctions(observer10Funcs, CML_DEFAULT_10DEG_OBSERVER);
  CMLFunction* observer2Funcs[3];
  cmlCreateSpecDistFunctions(observer2Funcs, CML_DEFAULT_2DEG_OBSERVER);
  const CMLFunction* illuminationSpec = cmlGetIlluminationSpectrum(cm);
  CPReferenceIlluminationType referenceIlluminationType = cpGetReferenceIlluminationType(con->whitePointsController);

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
      cpError("This shoud not happen.");
    #endif
    ref = cmlCreateIlluminationSpectrum(CML_ILLUMINATION_D50, 0.f);
  }

  CPWhitePoints illWhitePoint10 = cpGetWhitePoints(
    illuminationSpec,
    cmlGetWhitePointYxy(cm),
    observer10Funcs);
  CPWhitePoints illWhitePoint2 = cpGetWhitePoints(
    illuminationSpec,
    cmlGetWhitePointYxy(cm),
    observer2Funcs);
  CPWhitePoints refWhitePoint10 = cpGetWhitePoints(
    ref,
    NA_NULL,
    observer10Funcs);
  CPWhitePoints refWhitePoint2 = cpGetWhitePoints(
    ref,
    NA_NULL,
    observer2Funcs);

  CMLMat33 adaptationMatrix;
  cp_FillChromaticAdaptationMatrix(adaptationMatrix, illWhitePoint10.Yxy);



  cpUpdateWhitePointsController(
    con->whitePointsController,
    cmlGetIlluminationTypeString(cmlGetIlluminationType(cm)),
    &illWhitePoint10,
    &illWhitePoint2,
    &refWhitePoint10,
    &refWhitePoint2);

  cpUpdateChromaticityErrorController(
    con->chromaticityErrorController,
    &refWhitePoint10,
    &illWhitePoint10);
    
  cpUpdateColorRenderingIndexController(
    con->colorRenderingIndexController,
    observer2Funcs,
    &illWhitePoint2,
    &refWhitePoint2,
    ref,
    illuminationSpec != NA_NULL);

  cpUpdateVisMetamericIndexController(
    con->visMetamericIndexController,
    observer10Funcs,
    &illWhitePoint10,
    adaptationMatrix,
    referenceIlluminationType,
    illuminationSpec != NA_NULL);

  cpUpdateUVMetamericIndexController(
    con->uvMetamericIndexController,
    observer10Funcs,
    &illWhitePoint10,
    referenceIlluminationType,
    illuminationSpec != NA_NULL);

  cpUpdateTotalMetamericIndexController(
    con->totalMetamericIndexController,
    cpGetVisMetamericIndexAverage(con->visMetamericIndexController),
    cpGetUVMetamericIndexAverage(con->uvMetamericIndexController),
    illuminationSpec != NA_NULL);



  cmlReleaseFunction(observer10Funcs[0]);
  cmlReleaseFunction(observer10Funcs[1]);
  cmlReleaseFunction(observer10Funcs[2]);
}
