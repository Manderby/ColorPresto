
#include "CML.h"
#include "mainC.h"


CM_PROTOTYPE(CPColorController);
CM_PROTOTYPE(CPColorsManager);

typedef struct CPColorsManager CPColorsManager;

CPColorsManager* cmAllocColorsController(void);
void cmDeallocColorsController(CPColorsManager* colorsManager);

const float* cmGetColorsManagerCurrentColorData(
  const CPColorsManager* colorsManager);

CMLColorType cmGetColorsManagerCurrentColorType(
  const CPColorsManager* colorsManager);

void cmSetColorsManagerCurrentColorController(
  CPColorsManager* colorsManager,
  const CPColorController* con);

const CPColorController* cmGetColorsManagerCurrentColorController(
  CPColorsManager* colorsManager);

