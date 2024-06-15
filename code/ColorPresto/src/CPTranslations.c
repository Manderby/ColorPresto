
#include "CPTranslations.h"

NAInt translatorGroup;



const NAUTF8Char* cpTranslate(NAInt id){
  return naTranslate(translatorGroup, id);
}



void initTranslations(){
  translatorGroup = naRegisterTranslatorGroup();
  #include "../res/ColorPrestoStrings_deu.h"
  #include "../res/ColorPrestoStrings_eng.h"
  #include "../res/ColorPrestoStrings_fra.h"
  #include "../res/ColorPrestoStrings_jpn.h"
  #include "../res/ColorPrestoStrings_spa.h"
  #include "../res/ColorPrestoStrings_tlh.h"
  #include "../res/ColorPrestoStrings_zho.h"
}

