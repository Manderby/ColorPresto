
#include "CPColorController.h"

#include "../CPColorPromptApplication.h"
#include "../CPDesign.h"
#include "Displays/CPColorWell1D.h"
#include "Displays/CPSpectralColorWell.h"
#include "CPSpectralColorController.h"

#include "NAApp.h"

struct CPSpectralColorController{
  CPColorController baseController;
  
  CPSpectralColorWell* display;
  
  CMLFunction* spectralColor;
};



NABool cmSpectralValueEdited(NAReaction reaction){
  CPSpectralColorController* con = (CPSpectralColorController*)reaction.controller;
  
  cpSetCurrentColorController(&(con->baseController));
  cpUpdateColor();
  
  return NA_TRUE;
}



CPSpectralColorController* cmAllocSpectralColorController(void){
  CPSpectralColorController* con = naAlloc(CPSpectralColorController);
  
  cmInitColorController(&(con->baseController), CML_COLOR_SPECTRUM_ILLUMINATION);
  
  con->spectralColor = cmlCreateConstFilter(0.f);
  
  con->display = cmAllocSpectralColorWell(&(con->baseController));
  
  cpBeginUILayout(con->baseController.space, colorWellBezel);
  cpAddUIRow(cmGetSpectralColorWellUIElement(con->display), 0);
  cpEndUILayout();

  return con;
}



void cmDeallocSpectralColorController(CPSpectralColorController* con){
  cmDeallocSpectralColorWell(con->display);
  cmClearColorController(&(con->baseController));
  naFree(con);
}



const void* cmGetSpectralColorControllerColorData(const CPSpectralColorController* con){
  return con->spectralColor;
}



void cmSetSpectralColorControllerColorData(CPSpectralColorController* con, const void* data){
  cmlReleaseFunction(con->spectralColor);
  con->spectralColor = cmlDuplicateFunction((CMLFunction*)data);
}



void cmUpdateSpectralColorController(CPSpectralColorController* con){
  cpUpdateColorController(&(con->baseController));

  CMLColorType currentColorType = cpGetCurrentColorType();
  if(currentColorType != CML_COLOR_SPECTRUM_ILLUMINATION){
    cmlReleaseFunction(con->spectralColor);
    con->spectralColor = cmlCreateConstFilter(0.f);
  }
  
  cmUpdateSpectralColorWell(con->display);
}
