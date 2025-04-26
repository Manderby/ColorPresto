
#include "ColorControllers/CPColorController.h"
#include "CPColorsManager.h"
#include "main.h"
#include "NAUtility/NAMemory.h"

struct CPColorsManager{
  float fallbackColor;
  const void* currentColor;
  CMLColorType currentType;
  const CPColorController* currentController;
};

CPColorsManager* cpAllocColorsController(){
  CPColorsManager* colorsManager = naAlloc(CPColorsManager);
  
  colorsManager->fallbackColor = .5f;
  colorsManager->currentColor = &(colorsManager->fallbackColor);
  colorsManager->currentType = CML_COLOR_Gray;
  colorsManager->currentController = NA_NULL;
  
  return colorsManager;
}

void cpDeallocColorsController(CPColorsManager* colorsManager){
  free(colorsManager);
}

const float* cpGetColorsManagerCurrentColorData(const CPColorsManager* colorsManager){
  return colorsManager->currentColor;
}

CMLColorType cpGetColorsManagerCurrentColorType(const CPColorsManager* colorsManager){
  return colorsManager->currentType;
}

NABool cpSetColorsManagerCurrentColorController(CPColorsManager* colorsManager, const CPColorController* con){
  NABool controllerSwitched = (colorsManager->currentController != con);
  colorsManager->currentController = con;
  colorsManager->currentColor = cpGetColorControllerColorData(con);
  if(colorsManager->currentController == NA_NULL || colorsManager->currentColor == NA_NULL){
    colorsManager->currentColor = &(colorsManager->fallbackColor);
    colorsManager->currentType = CML_COLOR_Gray;
  }else{
    colorsManager->currentType = cpGetColorControllerColorType(con);
  }
  return controllerSwitched;
}

const CPColorController* cpGetColorsManagerCurrentColorController(CPColorsManager* colorsManager){
  return colorsManager->currentController;
}
