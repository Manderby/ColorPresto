
#include "mainC.h"

#include "NAUtility/NAMemory.h"
#include "NAUtility/NAString.h"
#include "CPColorPrestoApplication.h"
#include "CPTranslations.h"
#include "About/CPAboutController.h"
#include "Preferences/CPPreferences.h"
#include "NAApp/NAApp.h"


CPColorPrestoApplication* app;



void fillRGBFloatArrayWithArray(const CMLColorMachine* cm, const CMLColorMachine* sm, float* outData, const float* inputData, CMLColorType inputColorType, CMLNormedConverter normedConverter, size_t count){
  
  size_t numColorChannels = cmlGetNumChannels(inputColorType);
  CMLVec3 cmWhitePointYxy;
  CMLVec3 smWhitePointYxy;
  CMLColorConverter colorToXYZ = cmlGetColorConverter(CML_COLOR_XYZ, inputColorType);
  float* colorBuffer = naMalloc(numColorChannels * count * sizeof(float));
  float* XYZbuffer = naMalloc(3 * count * sizeof(float));
  
  cmlCpy3(cmWhitePointYxy, cmlGetWhitePointYxy(cm));
  cmWhitePointYxy[0] = 1.f;
  cmlCpy3(smWhitePointYxy, cmlGetWhitePointYxy(sm));
  smWhitePointYxy[0] = 1.f;
  
  normedConverter(colorBuffer, inputData, count);
  colorToXYZ(cm, XYZbuffer, colorBuffer, count);
  float* aXYZbuffer = naMalloc(3 * count * sizeof(float));
  CMLMat33 amatrix;
  cmlFillChromaticAdaptationMatrix(amatrix, CML_CHROMATIC_ADAPTATION_NONE, smWhitePointYxy, cmWhitePointYxy);
  for(size_t i=0; i<count; ++i){
    cmlConvertXYZToChromaticAdaptedXYZ(&(aXYZbuffer[i*3]), &(XYZbuffer[i*3]), amatrix);
  }
  cmlXYZToRGB(sm, outData, aXYZbuffer, count);
  naFree(aXYZbuffer);

  cmlClampRGB(outData, count);
  
  naFree(XYZbuffer);
  naFree(colorBuffer);
}



void preStartup(void* arg){
  initTranslations();
  initPreferences();

  NAString* appPath = naNewExecutablePath();
  naSetApplicationResourceBasePath(naGetStringUTF8Pointer(appPath));
  //naPresentAlertBox(NA_ALERT_BOX_INFO, "Resource directory", naGetStringUTF8Pointer(appPath));
  naDelete(appPath);

  naSetApplicationName("Color Presto");
  naSetApplicationVersionString("2.1");
  naSetApplicationBuildString("2.1.1");
  #if NA_OS == NA_OS_WINDOWS
    naSetApplicationIconPath("icon.png");
  #endif

  cpStartupColorPrestoApplication();
}



void postStartup(void* arg){
  #if NA_OS == NA_OS_MAC_OS_X
    naLoadNib("MainMenu", NA_NULL);
  #endif

  NALanguageCode3 languageCode = cpGetPrefsPreferredLanguage();
  if(languageCode != 0){
    naSetTranslatorLanguagePreference(languageCode);
  }

  // Color Presto
  cpStartupColorPrestoApplicationUI();
}




#if NA_OS == NA_OS_WINDOWS

int WINAPI WinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPSTR lpCmdLine, _In_ int nShowCmd){
  NA_UNUSED(hInstance);
  NA_UNUSED(hPrevInstance);
  NA_UNUSED(lpCmdLine);
  NA_UNUSED(nShowCmd);
  
  naOpenConsoleWindow();

  naStartRuntime();
  naStartApplication(preStartup, postStartup, NA_NULL, NA_NULL);
  return 0;
}

#endif // NA_OS == NA_OS_WINDOWS
