
#include "mainC.h"

#include "NAUtility/NAMemory.h"
#include "CMColorMachineApplication.h"
#include "CMTranslations.h"
#include "NAApp.h"
//#include "ManderAppTranslations.h"


CMColorMachineApplication* app;



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
  //mandInitManderAppTranslations();
  initTranslations();

  cmStartupColorMachineApplication();
}



void postStartup(void* arg){
  //naLoadNib("ColorMachine", NA_NULL);

  // ManderApp
  //mandCreateAboutController();
  //mandSetAboutDescriptionAndHelpURL(
  //  cmTranslate(CMApplicationDescription),
  //  cmTranslate(CMApplicationHelpURL));

  // Color Machine
  cmStartupColorMachineApplicationUI();
}




#if NA_OS == NA_OS_WINDOWS

double cmGetUIScaleFactorForWindow(void* nativeWindowPtr){
  return 1.;
}

int main()
{
  naStartRuntime();
  naStartApplication(preStartup, postStartup, NA_NULL);
  return 0;
}

#endif // NA_OS == NA_OS_WINDOWS
