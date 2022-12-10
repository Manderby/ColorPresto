
#include "../mainC.h"
#include "NAApp.h"
#include "CMThreeDeeController.h"

CM_PROTOTYPE(CMWhitePoints);
CM_PROTOTYPE(NASpace);



typedef struct CMThreeDeeOptionsController CMThreeDeeOptionsController;

CMThreeDeeOptionsController* cmAllocThreeDeeOptionsController(CMThreeDeeController* parent);
void cmDeallocThreeDeeOptionsController(CMThreeDeeOptionsController* con);

NASpace* cmGetThreeDeeOptionsControllerUIElement(CMThreeDeeOptionsController* con);

double cmGetThreeDeeOptionsControllerAxisGray(CMThreeDeeOptionsController* con);
double cmGetThreeDeeOptionsControllerBackgroundGray(CMThreeDeeOptionsController* con);
double cmGetThreeDeeOptionsControllerFovy(CMThreeDeeOptionsController* con);
NABool cmGetThreeDeeOptionsControllerShowAxis(CMThreeDeeOptionsController* con);
NABool cmGetThreeDeeOptionsControllerShowSpectrum(CMThreeDeeOptionsController* con);

void cmUpdateThreeDeeOptionsController(CMThreeDeeOptionsController* con);
