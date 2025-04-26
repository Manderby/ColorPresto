
#include "../main.h"
#include "NAApp/NAPreferences.h"
#include "NAUtility/NATranslator.h"


void initPreferences(void);

HSVHSLSelect cpGetPrefsHSVHSLSelect(void);
void cpSetPrefsHSVHSLSelect(HSVHSLSelect selection);

LuvUVWSelect cpGetPrefsLuvUVWSelect(void);
void cpSetPrefsLuvUVWSelect(LuvUVWSelect selection);

LabLchSelect cpGetPrefsLabLchSelect(void);
void cpSetPrefsLabLchSelect(LabLchSelect selection);

YuvYupvpSelect cpGetPrefsYuvYupvpSelect(void);
void cpSetPrefsYuvYupvpSelect(YuvYupvpSelect selection);

NALanguageCode3 cpGetPrefsPreferredLanguage(void);
void cpSetPrefsPreferredLanguage(NALanguageCode3 languageCode);


