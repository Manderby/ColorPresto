
#include "CMColorController.h"
#include "CMColorsManager.h"
#include "mainC.h"
#include "NAUtility/NAMemory.h"

struct CMColorsManager{
  float fallbackColor;
  const void* currentColor;
  CMLColorType currentType;
  const CMColorController* currentController;
};

CMColorsManager* cmAllocColorsController(){
  CMColorsManager* colorsManager = naAlloc(CMColorsManager);
  
  colorsManager->fallbackColor = .5f;
  colorsManager->currentColor = &(colorsManager->fallbackColor);
  colorsManager->currentType = CML_COLOR_Gray;
  colorsManager->currentController = NA_NULL;
  
  return colorsManager;
}

void cmDeallocColorsController(CMColorsManager* colorsManager){
  free(colorsManager);
}

const float* cmGetColorsManagerCurrentColorData(const CMColorsManager* colorsManager){
  return colorsManager->currentColor;
}

CMLColorType cmGetColorsManagerCurrentColorType(const CMColorsManager* colorsManager){
  return colorsManager->currentType;
}

void cmSetColorsManagerCurrentColorController(CMColorsManager* colorsManager, const CMColorController* con){
  colorsManager->currentController = con;
  colorsManager->currentColor = cmGetColorControllerColorData(con);
  if(colorsManager->currentController == NA_NULL || colorsManager->currentColor == NA_NULL){
    colorsManager->currentColor = &(colorsManager->fallbackColor);
    colorsManager->currentType = CML_COLOR_Gray;
  }else{
    colorsManager->currentType = cmGetColorControllerColorType(con);
  }
}

const CMColorController* cmGetColorsManagerCurrentColorController(CMColorsManager* colorsManager){
  return colorsManager->currentController;
}
