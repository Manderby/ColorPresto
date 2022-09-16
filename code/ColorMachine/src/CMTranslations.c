
#include "CMTranslations.h"

NAInt translatorGroup;



const NAUTF8Char* cmTranslate(NAInt id){
  return naTranslate(translatorGroup, id);
}



void initTranslations(){
  translatorGroup = naRegisterTranslatorGroup();
  #include "../res/ColorMachineStrings_eng.h"
  #include "../res/ColorMachineStrings_deu.h"
//  #include "../res/ColorMachineStrings_jpn.h"
}

