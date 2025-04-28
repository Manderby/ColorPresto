
#include "CPColorPrestoApplication.h"



#if NA_OS == NA_OS_WINDOWS



int WINAPI WinMain(
  _In_ HINSTANCE hInstance,
  _In_opt_ HINSTANCE hPrevInstance,
  _In_ LPSTR lpCmdLine,
  _In_ int nShowCmd)
{
  NA_UNUSED(hInstance);
  NA_UNUSED(hPrevInstance);
  NA_UNUSED(lpCmdLine);
  NA_UNUSED(nShowCmd);
  
  //naOpenConsoleWindow();

  naStartApplication(
    cpPreStartupApplication,
    cpPostStartupApplication,
    cpShutdownApplication,
    NA_NULL);

  return 0;
}



#elif NA_OS == NA_OS_MAC_OS_X



int main(int argc, char *argv[]){
  NA_UNUSED(argc);
  NA_UNUSED(argv);

  naInstanciateNSApplication(CPColorPrestoNSApplication);

  naStartApplication(
    cpPreStartupApplication,
    cpPostStartupApplication,
    cpShutdownApplication,
    NA_NULL);

  return 0;
}



#endif // NA_OS



