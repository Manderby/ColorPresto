
#include "CML.h"
#include "mainC.h"


CM_PROTOTYPE(CMColorController);
CM_PROTOTYPE(CMColorsManager);

typedef struct CMColorsManager CMColorsManager;

CMColorsManager* cmAllocColorsController();
void cmDeallocColorsController(CMColorsManager* colorsManager);

const float* cmGetColorsManagerCurrentColorData(
  const CMColorsManager* colorsManager);

CMLColorType cmGetColorsManagerCurrentColorType(
  const CMColorsManager* colorsManager);

void cmSetColorsManagerCurrentColorController(
  CMColorsManager* colorsManager,
  const CMColorController* con);

const CMColorController* cmGetColorsManagerCurrentColorController(
  CMColorsManager* colorsManager);

