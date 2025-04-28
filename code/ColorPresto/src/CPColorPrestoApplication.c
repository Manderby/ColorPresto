
#include "CPColorPrestoApplication.h"

#include "CPColorsManager.h"
#include "CPDesign.h"
#include "CPTranslations.h"
#include "About/CPAboutController.h"
#include "Machine/CPMachineWindowController.h"
#include "Metamerics/CPMetamericsController.h"
#include "Preferences/CPPreferences.h"
#include "Preferences/CPPreferencesController.h"
#include "ThreeDee/CPThreeDeeController.h"

#include "NAUtility/NAString.h"
#include "NAUtility/NAMemory.h"



typedef struct CPColorPrestoApplication CPColorPrestoApplication;
struct CPColorPrestoApplication{
  CMLColorMachine* cm; // current ColorMachine
  CMLColorMachine* sm; // current ScreenMachine
  CPColorsManager* colorsManager;

  CPMachineWindowController* machineWindowController;
  CPMetamericsController* metamericsController;
  CPThreeDeeController* threeDeeController;
  CPAboutController* aboutController;
  CPPreferencesController* preferencesController;
};

CPColorPrestoApplication* app = NA_NULL;



void cpPreStartupApplication(void* arg){
  NA_UNUSED(arg);

  //NAString* appPath = naNewExecutablePath();
  //naPresentAlertBox(NA_ALERT_BOX_INFO, "Working directory", naGetStringUTF8Pointer(appPath));
  //naDelete(appPath);

  app = naAlloc(CPColorPrestoApplication);

  naSetApplicationName("Color Presto");
  naSetApplicationVersionString(CP_VERSION_STRING);
  naSetApplicationBuildString(CP_BUILD_NUMBER_STRING);

  NAString* appPath = naNewExecutablePath();
  naSetApplicationResourceBasePath(naGetStringUTF8Pointer(appPath));
  //naPresentAlertBox(NA_ALERT_BOX_INFO, "Resource directory", naGetStringUTF8Pointer(appPath));
  naDelete(appPath);

  #if NA_OS == NA_OS_WINDOWS
    naSetApplicationIconPath("icon.png");
  #endif
    
  initTranslations();
  initPreferences();

  app->cm = cmlCreateColorMachine();
  app->sm = cmlCreateColorMachine();
  app->colorsManager = cpAllocColorsController();
}



void cpPostStartupApplication(void* arg){
  NA_UNUSED(arg);

  #if NA_OS == NA_OS_MAC_OS_X
    naLoadNib("MainMenu", NA_NULL);
  #endif

  NALanguageCode3 languageCode = cpGetPrefsPreferredLanguage();
  if(languageCode != 0){
    naSetTranslatorLanguagePreference(languageCode);
  }

  cpStartupDesign();

  app->aboutController         = NA_NULL;
  app->machineWindowController = cpAllocMachineWindowController();
  app->metamericsController    = NA_NULL;
  app->preferencesController   = NA_NULL;
  app->threeDeeController      = NA_NULL;

  cpSetCurrentColorController(cpGetInitialColorController(app->machineWindowController));
  cpShowMachineWindowController(app->machineWindowController);
}



void cpShutdownApplication(void* arg){
  NA_UNUSED(arg);
  
  if(app->threeDeeController) {
    cpDeallocThreeDeeController(app->threeDeeController);
  }
  if(app->preferencesController) {
    cpDeallocPreferencesController(app->preferencesController);
  }
  if(app->metamericsController) {
    cpDeallocMetamericsController(app->metamericsController);
  }
  cpDeallocMachineWindowController(app->machineWindowController);
  if(app->aboutController) {
    cpDeallocAboutController(app->aboutController);
  }

  cpShutdownDesign();

  cpDeallocColorsController(app->colorsManager);
  cmlReleaseColorMachine(app->sm);
  cmlReleaseColorMachine(app->cm);

  naFree(app);
}



CMLColorMachine* cpGetCurrentColorMachine(){
  return app->cm;
}

void cpResetColorMachine(){
  cmlReleaseColorMachine(app->cm);
  app->cm = cmlCreateColorMachine();
}

CMLColorMachine* cpGetCurrentScreenMachine(){
  return app->sm;
}

CPColorsManager* cpGetColorsManager(){
  return app->colorsManager;
}



void cpShowMetamerics(){
  NABool newlyCreated = NA_FALSE;
  if(!app->metamericsController) {
    app->metamericsController = cpAllocMetamericsController();
    newlyCreated = NA_TRUE;
  }
  cpShowMetamericsController(app->metamericsController);
  if(newlyCreated) {
    cpUpdateMetamericsController(app->metamericsController);
  }
}
void cpUpdateMetamerics(){
  if(app->metamericsController) {
    cpUpdateMetamericsController(app->metamericsController);
  }
}



void cpShowThreeDee(){
  NABool newlyCreated = NA_FALSE;
  if(!app->threeDeeController) {
    app->threeDeeController = cpAllocThreeDeeController();
    newlyCreated = NA_TRUE;
  }
  cpShowThreeDeeController(app->threeDeeController);
  if(newlyCreated) {
    cpUpdateThreeDeeController(app->threeDeeController);
  }
}
void cpUpdateThreeDee(){
  if(app->threeDeeController) {
    cpUpdateThreeDeeController(app->threeDeeController);
  }
}



void cpShowAbout(){
  if(!app->aboutController) {
    app->aboutController = cpAllocAboutController();
  }
  cpShowAboutController(app->aboutController);
}



void cpShowPreferences(){
  NABool newlyCreated = NA_FALSE;
  if(!app->preferencesController) {
    app->preferencesController = cpAllocPreferencesController();
    newlyCreated = NA_TRUE;
  }
  cpShowPreferencesController(app->preferencesController);
  if(newlyCreated) {
    cpUpdatePreferencesController(app->preferencesController);
  }
}



void cpUpdateColor(){
  cpUpdateColorWells(app->machineWindowController);
  cpUpdateMetamerics();
  cpUpdateThreeDee();
}
void cpUpdateMachine(){
  cpUpdateMachineWindowController(app->machineWindowController);
  cpUpdateColor();
}



void cpSetCurrentColorController(const CPColorController* con){
  if(cpSetColorsManagerCurrentColorController(cpGetColorsManager(), con)) {
    cpUpdateMachine();
  }
}

const CPColorController* cpGetCurrentColorController(){
  return cpGetColorsManagerCurrentColorController(cpGetColorsManager());
}

const float* cpGetCurrentColorData(){
  return cpGetColorsManagerCurrentColorData(cpGetColorsManager());
}

CMLColorType cpGetCurrentColorType(){
  return cpGetColorsManagerCurrentColorType(cpGetColorsManager());
}



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
