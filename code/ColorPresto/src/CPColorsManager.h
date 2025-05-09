
#include "CML.h"
#include "main.h"


CP_PROTOTYPE(CPColorController);
CP_PROTOTYPE(CPColorsManager);

typedef struct CPColorsManager CPColorsManager;

CPColorsManager* cpAllocColorsController(void);
void cpDeallocColorsController(CPColorsManager* colorsManager);

const float* cpGetColorsManagerCurrentColorData(
  const CPColorsManager* colorsManager);

CMLColorType cpGetColorsManagerCurrentColorType(
  const CPColorsManager* colorsManager);

NABool cpSetColorsManagerCurrentColorController(
  CPColorsManager* colorsManager,
  const CPColorController* con);

const CPColorController* cpGetColorsManagerCurrentColorController(
  CPColorsManager* colorsManager);

