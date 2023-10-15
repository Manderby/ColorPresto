
#include "../mainC.h"
#include "NAApp.h"
#include "CMThreeDeeController.h"

CM_PROTOTYPE(CMWhitePoints);
CM_PROTOTYPE(NASpace);



typedef struct CMThreeDeeOptionsController CMThreeDeeOptionsController;

CMThreeDeeOptionsController* cmAllocThreeDeeOptionsController(CMThreeDeeController* parent);
void cmDeallocThreeDeeOptionsController(CMThreeDeeOptionsController* con);

NASpace* cmGetThreeDeeOptionsControllerUIElement(CMThreeDeeOptionsController* con);

float cmGetThreeDeeOptionsControllerAxisGray(CMThreeDeeOptionsController* con);
float cmGetThreeDeeOptionsControllerBackgroundGray(CMThreeDeeOptionsController* con);
float cmGetThreeDeeOptionsControllerFovy(CMThreeDeeOptionsController* con);
NABool cmGetThreeDeeOptionsControllerShowAxis(CMThreeDeeOptionsController* con);
NABool cmGetThreeDeeOptionsControllerShowSpectrum(CMThreeDeeOptionsController* con);

void cmUpdateThreeDeeOptionsController(CMThreeDeeOptionsController* con);
