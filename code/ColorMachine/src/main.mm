
#include "ColorMachineTranslations.h"
#include "ThreeDeeController.h"

#import "main.h"
#import "mainC.h"
#import "ColorMachineApplication.h"

#include "ManderAppAbout.h"
#include "ManderAppTranslations.h"
#include "NAApp.h"



CMLColorMachine* cmGetCurrentColorMachine(){
  return [(ColorMachineApplication*)NSApp getCurrentMachine];
}
CMLColorMachine* cmGetCurrentScreenMachine(){
  return [(ColorMachineApplication*)NSApp getCurrentScreenMachine];
}


double cmGetUIScaleFactorForWindow(void* nativeWindowPtr){
  return [ColorMachineApplication getUIScaleFactorForWindow: (NSWindow*)nativeWindowPtr];
}



void preStartup(void* arg){
  // here come translations.
  mandInitManderAppTranslations();
  initTranslations();
}



void postStartup(void* arg){
  naLoadNib("ColorMachine", NA_NULL);
  
  // ManderApp
  mandCreateAboutController();
  mandSetAboutDescriptionAndHelpURL(
    cmTranslate(ColorMachineApplicationDescription),
    cmTranslate(ColorMachineApplicationHelpURL));

  // Color Machine
}



int main(int argc, char *argv[]){
  naStartRuntime();
  [ColorMachineApplication sharedApplication];
  naStartApplication(preStartup, postStartup, NA_NULL);
  naStopRuntime();
  return 0;
}



