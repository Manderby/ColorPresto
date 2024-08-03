
#include "CPTranslations.h"

uint32 translatorGroup;



const NAUTF8Char* cpTranslate(uint32 id){
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

