
#import "ColorPromptApplication.h"
#include "NAApp.h"

// This file exists only to run sharedApplication in objective c.
// actual implementations are in main.c file.

void preStartup(void* arg);
void postStartup(void* arg);

int main(int argc, char *argv[]){
  naStartRuntime();
  [ColorPromptApplication sharedApplication];
  naStartApplication(preStartup, postStartup, NA_NULL, NA_NULL);
  return 0;
}



