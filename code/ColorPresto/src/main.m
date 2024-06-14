
#include "ColorPrestoApplication.h"
#include "NAApp/NAApp.h"

// This file exists only to run sharedApplication in objective c.
// actual implementations are in main.c file.


#if NA_OS == NA_OS_MAC_OS_X

void preStartup(void* arg);
void postStartup(void* arg);

int main(int argc, char *argv[]){

  naStartRuntime();
  [ColorPrestoApplication sharedApplication];
  naStartApplication(preStartup, postStartup, NA_NULL, NA_NULL);
  return 0;
}

#endif // NA_OS == NA_OS_MACOSX


