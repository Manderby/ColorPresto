
#include "CPPreferencesController.h"

#include "../CPTranslations.h"
#include "CPPreferences.h"
#include "../mainC.h"

#include "NAApp/NAApp.h"



struct CPPreferencesController {
  NAWindow* window;
  
  NALabel* languageLabel;
  NASelect* languageSelect;
  NAMenuItem* languageSystem;
  NAMenuItem* languageDeutsch;
  NAMenuItem* languageEnglish;
  NAMenuItem* languageEspanol;
  NAMenuItem* languageFrancais;
  NAMenuItem* languageKlingon;
  NAMenuItem* languageJapanese;
  NAMenuItem* languageChinese;
  NAMenuItem* languageReport;
};



void cp_ChangePreferencesLanguage(NAReaction reaction){
  CPPreferencesController* con = reaction.controller;

  if(reaction.uiElement == con->languageSystem){
    cpSetPrefsPreferredLanguage((NALanguageCode3)0);
  }else if(reaction.uiElement == con->languageDeutsch){
    cpSetPrefsPreferredLanguage(NA_LANG_DEU);
  }else if(reaction.uiElement == con->languageEnglish){
    cpSetPrefsPreferredLanguage(NA_LANG_ENG);
  }else if(reaction.uiElement == con->languageEspanol){
    cpSetPrefsPreferredLanguage(NA_LANG_SPA);
  }else if(reaction.uiElement == con->languageFrancais){
    cpSetPrefsPreferredLanguage(NA_LANG_FRA);
  }else if(reaction.uiElement == con->languageKlingon){
    cpSetPrefsPreferredLanguage(NA_LANG_TLH);
  }else if(reaction.uiElement == con->languageJapanese){
    cpSetPrefsPreferredLanguage(NA_LANG_JPN);
  }else if(reaction.uiElement == con->languageChinese){
    cpSetPrefsPreferredLanguage(NA_LANG_ZHO);
  }

  naPresentAlertBox(
    NA_ALERT_BOX_INFO,
    cpTranslate(CPPreferencesLanguageChangeAlertTitle),
    cpTranslate(CPPreferencesLanguageChangeAlertText));
}



void cp_ReportBadTranslation(NAReaction reaction){
  NA_UNUSED(reaction);

  naPresentAlertBox(
    NA_ALERT_BOX_INFO,
    cpTranslate(CPPreferencesLanguageBadTranslationTitle),
    cpTranslate(CPPreferencesLanguageBadTranslationText));
}



CPPreferencesController* cpAllocPreferencesController(void) {
  CPPreferencesController* con = naAlloc(CPPreferencesController);

  NARect windowrect = naMakeRectS(20, 300, 440, 65);
  con->window = naNewWindow(cpTranslate(CPPreferences), windowrect, NA_FALSE, CP_PREFERENCES_WINDOW_STORAGE_TAG);

  NASpace* contentSpace = naGetWindowContentSpace(con->window);

  con->languageLabel = naNewLabel(cpTranslate(CPPreferencesLanguage), 250);
  con->languageSelect = naNewSelect(150);
  con->languageSystem = naNewMenuItem(cpTranslate(CPPreferencesLanguageSameAsSystem));
  con->languageDeutsch = naNewMenuItem(cpTranslate(CPPreferencesLanguageDeutsch));
  con->languageEnglish = naNewMenuItem(cpTranslate(CPPreferencesLanguageEnglish));
  con->languageEspanol = naNewMenuItem(cpTranslate(CPPreferencesLanguageEspanol));
  con->languageFrancais = naNewMenuItem(cpTranslate(CPPreferencesLanguageFrancais));
  con->languageKlingon = naNewMenuItem(cpTranslate(CPPreferencesLanguageKlingon));
  con->languageJapanese = naNewMenuItem(cpTranslate(CPPreferencesLanguageJapanese));
  con->languageChinese = naNewMenuItem(cpTranslate(CPPreferencesLanguageChinese));
  con->languageReport = naNewMenuItem(cpTranslate(CPPreferencesLanguageReport));
  naAddSelectMenuItem(con->languageSelect, con->languageSystem, NA_NULL);
  naAddSelectMenuItem(con->languageSelect, naNewMenuSeparator(), NA_NULL);
  naAddSelectMenuItem(con->languageSelect, con->languageDeutsch, NA_NULL);
  naAddSelectMenuItem(con->languageSelect, con->languageEnglish, NA_NULL);
  naAddSelectMenuItem(con->languageSelect, con->languageEspanol, NA_NULL);
  naAddSelectMenuItem(con->languageSelect, con->languageFrancais, NA_NULL);
  naAddSelectMenuItem(con->languageSelect, con->languageKlingon, NA_NULL);
  naAddSelectMenuItem(con->languageSelect, con->languageJapanese, NA_NULL);
  naAddSelectMenuItem(con->languageSelect, con->languageChinese, NA_NULL);
  naAddSelectMenuItem(con->languageSelect, naNewMenuSeparator(), NA_NULL);
  naAddSelectMenuItem(con->languageSelect, con->languageReport, NA_NULL);

  naAddSpaceChild(contentSpace, con->languageLabel, naMakePos(20, 20));
  naAddSpaceChild(contentSpace, con->languageSelect, naMakePos(270, 20));

  naAddUIReaction(con->languageSystem, NA_UI_COMMAND_PRESSED, cp_ChangePreferencesLanguage, con);
  naAddUIReaction(con->languageDeutsch, NA_UI_COMMAND_PRESSED, cp_ChangePreferencesLanguage, con);
  naAddUIReaction(con->languageEnglish, NA_UI_COMMAND_PRESSED, cp_ChangePreferencesLanguage, con);
  naAddUIReaction(con->languageEspanol, NA_UI_COMMAND_PRESSED, cp_ChangePreferencesLanguage, con);
  naAddUIReaction(con->languageFrancais, NA_UI_COMMAND_PRESSED, cp_ChangePreferencesLanguage, con);
  naAddUIReaction(con->languageKlingon, NA_UI_COMMAND_PRESSED, cp_ChangePreferencesLanguage, con);
  naAddUIReaction(con->languageJapanese, NA_UI_COMMAND_PRESSED, cp_ChangePreferencesLanguage, con);
  naAddUIReaction(con->languageChinese, NA_UI_COMMAND_PRESSED, cp_ChangePreferencesLanguage, con);

  naAddUIReaction(con->languageReport, NA_UI_COMMAND_PRESSED, cp_ReportBadTranslation, con);

  return con;
}



void cpDeallocPreferencesController(CPPreferencesController* con) {
  naFree(con);
}



void cpShowPreferencesController(CPPreferencesController* con) {
  naShowWindow(con->window);
}



void cpUpdatePreferencesController(CPPreferencesController* con) {
  NALanguageCode3 languageCode = cpGetPrefsPreferredLanguage();

  switch(languageCode){
  case NA_LANG_DEU: naSetSelectItemSelected(con->languageSelect, con->languageDeutsch); break;
  case NA_LANG_ENG: naSetSelectItemSelected(con->languageSelect, con->languageEnglish); break;
  case NA_LANG_SPA: naSetSelectItemSelected(con->languageSelect, con->languageEspanol); break;
  case NA_LANG_FRA: naSetSelectItemSelected(con->languageSelect, con->languageFrancais); break;
  case NA_LANG_TLH: naSetSelectItemSelected(con->languageSelect, con->languageKlingon); break;
  case NA_LANG_JPN: naSetSelectItemSelected(con->languageSelect, con->languageJapanese); break;
  case NA_LANG_ZHO: naSetSelectItemSelected(con->languageSelect, con->languageChinese); break;
  default: naSetSelectItemSelected(con->languageSelect, con->languageSystem); break;
  }
}
