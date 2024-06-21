
#include "CPColorController.h"

#include "../CPColorPrestoApplication.h"
#include "../CPDesign.h"
#include "Displays/CPColorWell1D.h"
#include "Displays/CPSpectralColorWell.h"
#include "CPSpectralColorController.h"

#include "NAApp/NAApp.h"

struct CPSpectralColorController{
  CPColorController baseController;
  
  CPSpectralColorWell* display;
  
  CMLFunction* spectralColor;
};



NABool cp_SpectralValueEdited(NAReaction reaction){
  CPSpectralColorController* con = (CPSpectralColorController*)reaction.controller;
  
  cpSetCurrentColorController(&(con->baseController));
  cpUpdateColor();
  
  return NA_TRUE;
}



CPSpectralColorController* cpAllocSpectralColorController(void){
  CPSpectralColorController* con = naAlloc(CPSpectralColorController);
  
  cpInitColorController(&(con->baseController), CML_COLOR_SPECTRUM_ILLUMINATION);
  
  con->spectralColor = cmlCreateConstFilter(0.f);
  
  con->display = cpAllocSpectralColorWell(&(con->baseController));
  
  cpBeginUILayout(con->baseController.space, colorWellBorder);
  cpAddUIRow(cpGetSpectralColorWellUIElement(con->display), 0);
  cpEndUILayout();

  return con;
}



void cpDeallocSpectralColorController(CPSpectralColorController* con){
  cpDeallocSpectralColorWell(con->display);
  cpClearColorController(&(con->baseController));
  naFree(con);
}



const void* cpGetSpectralColorControllerColorData(const CPSpectralColorController* con){
  return con->spectralColor;
}



void cpSetSpectralColorControllerColorData(CPSpectralColorController* con, const void* data){
  cmlReleaseFunction(con->spectralColor);
  con->spectralColor = cmlDuplicateFunction((CMLFunction*)data);
}



void cpUpdateSpectralColorController(CPSpectralColorController* con){
  cpUpdateColorController(&(con->baseController));

  CMLColorType currentColorType = cpGetCurrentColorType();
  if(currentColorType != CML_COLOR_SPECTRUM_ILLUMINATION){
    cmlReleaseFunction(con->spectralColor);
    con->spectralColor = cmlCreateConstFilter(0.f);
  }
  
  cpUpdateSpectralColorWell(con->display);
}
