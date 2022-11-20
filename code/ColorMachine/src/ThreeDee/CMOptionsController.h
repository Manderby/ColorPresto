
#include "mainC.h"
#include "NAApp.h"
#include "CMThreeDeeController.h"

CM_PROTOTYPE(CMWhitePoints);
CM_PROTOTYPE(NASpace);



typedef struct CMOptionsController CMOptionsController;

CMOptionsController* cmAllocOptionsController(CMThreeDeeController* parentController);
void cmDeallocOptionsController(CMOptionsController* con);

NASpace* cmGetOptionsUIElement(CMOptionsController* con);

double cmGetOptionsAxisGray(CMOptionsController* con);
double cmGetOptionsBackgroundGray(CMOptionsController* con);
double cmGetOptionsFovy(CMOptionsController* con);
NABool cmGetOptionsShowAxis(CMOptionsController* con);
NABool cmGetOptionsShowSpectrum(CMOptionsController* con);

void cmUpdateOptionsController(CMOptionsController* con);
