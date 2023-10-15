
#include "ColorControllers/CPColorController.h"
#include "CPColorsManager.h"
#include "mainC.h"
#include "NAUtility/NAMemory.h"

struct CPColorsManager{
  float fallbackColor;
  const void* currentColor;
  CMLColorType currentType;
  const CPColorController* currentController;
};

CPColorsManager* cmAllocColorsController(){
  CPColorsManager* colorsManager = naAlloc(CPColorsManager);
  
  colorsManager->fallbackColor = .5f;
  colorsManager->currentColor = &(colorsManager->fallbackColor);
  colorsManager->currentType = CML_COLOR_Gray;
  colorsManager->currentController = NA_NULL;
  
  return colorsManager;
}

void cmDeallocColorsController(CPColorsManager* colorsManager){
  free(colorsManager);
}

const float* cmGetColorsManagerCurrentColorData(const CPColorsManager* colorsManager){
  return colorsManager->currentColor;
}

CMLColorType cmGetColorsManagerCurrentColorType(const CPColorsManager* colorsManager){
  return colorsManager->currentType;
}

void cmSetColorsManagerCurrentColorController(CPColorsManager* colorsManager, const CPColorController* con){
  colorsManager->currentController = con;
  colorsManager->currentColor = cmGetColorControllerColorData(con);
  if(colorsManager->currentController == NA_NULL || colorsManager->currentColor == NA_NULL){
    colorsManager->currentColor = &(colorsManager->fallbackColor);
    colorsManager->currentType = CML_COLOR_Gray;
  }else{
    colorsManager->currentType = cmGetColorControllerColorType(con);
  }
}

const CPColorController* cmGetColorsManagerCurrentColorController(CPColorsManager* colorsManager){
  return colorsManager->currentController;
}
