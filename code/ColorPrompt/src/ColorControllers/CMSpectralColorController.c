
#include "CMColorController.h"

#include "../CPColorPromptApplication.h"
#include "../CPDesign.h"
#include "Displays/CMColorWell1D.h"
#include "Displays/CMSpectralColorWell.h"
#include "CMSpectralColorController.h"

#include "NAApp.h"

struct CMSpectralColorController{
  CMColorController baseController;
  
  CMSpectralColorWell* display;
  
  CMLFunction* spectralColor;
};



NABool cmSpectralValueEdited(NAReaction reaction){
  CMSpectralColorController* con = (CMSpectralColorController*)reaction.controller;
  
  cmSetCurrentColorController(&(con->baseController));
  cmUpdateColor();
  
  return NA_TRUE;
}



CMSpectralColorController* cmAllocSpectralColorController(void){
  CMSpectralColorController* con = naAlloc(CMSpectralColorController);
  
  cmInitColorController(&(con->baseController), CML_COLOR_SPECTRUM_ILLUMINATION);
  
  con->spectralColor = cmlCreateConstFilter(0.f);
  
  con->display = cmAllocSpectralColorWell(&(con->baseController));
  
  cmBeginUILayout(con->baseController.space, colorWellBezel);
  cmAddUIRow(cmGetSpectralColorWellUIElement(con->display), 0);
  cmEndUILayout();

  return con;
}



void cmDeallocSpectralColorController(CMSpectralColorController* con){
  cmDeallocSpectralColorWell(con->display);
  cmClearColorController(&(con->baseController));
  naFree(con);
}



const void* cmGetSpectralColorControllerColorData(const CMSpectralColorController* con){
  return con->spectralColor;
}



void cmSetSpectralColorControllerColorData(CMSpectralColorController* con, const void* data){
  cmlReleaseFunction(con->spectralColor);
  con->spectralColor = cmlDuplicateFunction((CMLFunction*)data);
}



void cmUpdateSpectralColorController(CMSpectralColorController* con){
  cmUpdateColorController(&(con->baseController));

  CMLColorType currentColorType = cmGetCurrentColorType();
  if(currentColorType != CML_COLOR_SPECTRUM_ILLUMINATION){
    cmlReleaseFunction(con->spectralColor);
    con->spectralColor = cmlCreateConstFilter(0.f);
  }
  
  cmUpdateSpectralColorWell(con->display);
}
