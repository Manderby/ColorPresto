
#include "CPTranslations.h"

NAInt translatorGroup;



const NAUTF8Char* cpTranslate(NAInt id){
  return naTranslate(translatorGroup, id);
}



void initTranslations(){
  translatorGroup = naRegisterTranslatorGroup();
  #include "../res/ColorPromptStrings_eng.h"
  #include "../res/ColorPromptStrings_deu.h"
//  #include "../res/ColorPromptStrings_jpn.h"
}

