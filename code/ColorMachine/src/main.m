
#include "CMColorsManager.h"
#include "CMTranslations.h"
#include "CMThreeDeeController.h"

#include "CMHSLColorController.h"

#include "mainC.h"
#import <Cocoa/Cocoa.h>

#import "ColorMachineApplication.h"
#include "CMColorMachineApplication.h"

#include "ManderAppAbout.h"
#include "ManderAppTranslations.h"
#include "NAApp.h"



CMColorMachineApplication* app;



void cmSetCurrentColorController(const CMColorController* con){
  cmSetColorsManagerCurrentColorController(cmGetColorsManager(), con);
  cmUpdateMachine();
}

const CMColorController* cmGetCurrentColorController(){
  return cmGetColorsManagerCurrentColorController(cmGetColorsManager());
}

const float* cmGetCurrentColorData(){
  return cmGetColorsManagerCurrentColorData(cmGetColorsManager());
}

CMLColorType cmGetCurrentColorType(){
  return cmGetColorsManagerCurrentColorType(cmGetColorsManager());
}


double cmGetUIScaleFactorForWindow(void* nativeWindowPtr){
  return [ColorMachineApplication getUIScaleFactorForWindow: (NSWindow*)nativeWindowPtr];
}



void preStartup(void* arg){
  mandInitManderAppTranslations();
  initTranslations();
}



void postStartup(void* arg){
  naLoadNib("ColorMachine", NA_NULL);
  
  // ManderApp
  mandCreateAboutController();
  mandSetAboutDescriptionAndHelpURL(
    cmTranslate(CMApplicationDescription),
    cmTranslate(CMApplicationHelpURL));

  // Color Machine
}



int main(int argc, char *argv[]){
  naStartRuntime();
  [ColorMachineApplication sharedApplication];
  naStartApplication(preStartup, postStartup, NA_NULL);
  naStopRuntime();
  return 0;
}



