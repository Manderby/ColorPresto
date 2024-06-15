
#include "CPPreferences.h"

enum{
  CPPreferredLanguage,

  CPHSVHSLSelection,
  CPLuvUVWSelection,
  CPLabLchSelection,
  CPYuvYupvpSelection,
 
  CPPrefCount
};

const char* cpPrefs[CPPrefCount] = {
  [CPPreferredLanguage]  = "preferredLanguage",

  [CPHSVHSLSelection]    = "HSVHSLSelection",
  [CPLuvUVWSelection]    = "LuvUVWSelection",
  [CPLabLchSelection]    = "LabLchSelection",
  [CPYuvYupvpSelection]  = "YuvYupvpSelection",
};



void initPreferences(){
  naInitPreferencesInt(
    cpPrefs[CPPreferredLanguage],
    0,
    0,
    NA_MAX_i32);

  naInitPreferencesEnum(
    cpPrefs[CPHSVHSLSelection],
    HSV,
    HSVHSLSelectCount);
  naInitPreferencesEnum(
    cpPrefs[CPLuvUVWSelection],
    Luv,
    LuvUVWSelectCount);
  naInitPreferencesEnum(
    cpPrefs[CPLabLchSelection],
    Lab,
    LabLchSelectCount);
  naInitPreferencesEnum(
    cpPrefs[CPYuvYupvpSelection],
    Yupvp,
    YuvYupvpSelectCount);
}



NALanguageCode3 cpGetPrefsPreferredLanguage(){
  return (NALanguageCode3)naGetPreferencesInt(cpPrefs[CPPreferredLanguage]);
}
void cpSetPrefsPreferredLanguage(NALanguageCode3 languageCode){
  naSetPreferencesInt(cpPrefs[CPPreferredLanguage], (NAInt)languageCode);
  naSetTranslatorLanguagePreference(languageCode);
}



HSVHSLSelect cpGetPrefsHSVHSLSelect(){
  return (HSVHSLSelect)naGetPreferencesEnum(cpPrefs[CPHSVHSLSelection]);
}
void cpSetPrefsHSVHSLSelect(HSVHSLSelect selection){
  naSetPreferencesEnum(cpPrefs[CPHSVHSLSelection], selection);
}



LuvUVWSelect cpGetPrefsLuvUVWSelect(){
  return (LuvUVWSelect)naGetPreferencesEnum(cpPrefs[CPLuvUVWSelection]);
}
void cpSetPrefsLuvUVWSelect(LuvUVWSelect selection){
  naSetPreferencesEnum(cpPrefs[CPLuvUVWSelection], selection);
}



LabLchSelect cpGetPrefsLabLchSelect(){
  return (LabLchSelect)naGetPreferencesEnum(cpPrefs[CPLabLchSelection]);
}
void cpSetPrefsLabLchSelect(LabLchSelect selection){
  naSetPreferencesEnum(cpPrefs[CPLabLchSelection], selection);
}



YuvYupvpSelect cpGetPrefsYuvYupvpSelect(){
  return (YuvYupvpSelect)naGetPreferencesEnum(cpPrefs[CPYuvYupvpSelection]);
}
void cpSetPrefsYuvYupvpSelect(YuvYupvpSelect selection){
  naSetPreferencesEnum(cpPrefs[CPYuvYupvpSelection], selection);
}


