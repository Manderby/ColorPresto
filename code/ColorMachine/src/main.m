
#import "ColorMachineApplication.h"

#include "CMColorMachineApplication.h"
#include "CMTranslations.h"

#include "ManderAppAbout.h"
#include "NAApp.h"

void preStartup(void* arg);
void postStartup(void* arg);



void preStartup(void* arg){
  mandInitManderAppTranslations();
  initTranslations();
  
  cmStartupColorMachineApplication();
}



void postStartup(void* arg){
  naLoadNib("ColorMachine", NA_NULL);
  
  // ManderApp
  mandCreateAboutController();
  mandSetAboutDescriptionAndHelpURL(
    cmTranslate(CMApplicationDescription),
    cmTranslate(CMApplicationHelpURL));

  // Color Machine
  cmStartupColorMachineApplicationUI();
}



int main(int argc, char *argv[]){
  naStartRuntime();
  [ColorMachineApplication sharedApplication];
  naStartApplication(preStartup, postStartup, NA_NULL);
  return 0;
}



