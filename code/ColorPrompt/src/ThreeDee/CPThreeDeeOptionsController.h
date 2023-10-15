
#include "../mainC.h"
#include "NAApp.h"
#include "CPThreeDeeController.h"

CP_PROTOTYPE(CPWhitePoints);
CP_PROTOTYPE(NASpace);



typedef struct CPThreeDeeOptionsController CPThreeDeeOptionsController;

CPThreeDeeOptionsController* cmAllocThreeDeeOptionsController(CPThreeDeeController* parent);
void cmDeallocThreeDeeOptionsController(CPThreeDeeOptionsController* con);

NASpace* cmGetThreeDeeOptionsControllerUIElement(CPThreeDeeOptionsController* con);

float cmGetThreeDeeOptionsControllerAxisGray(CPThreeDeeOptionsController* con);
float cmGetThreeDeeOptionsControllerBackgroundGray(CPThreeDeeOptionsController* con);
float cmGetThreeDeeOptionsControllerFovy(CPThreeDeeOptionsController* con);
NABool cmGetThreeDeeOptionsControllerShowAxis(CPThreeDeeOptionsController* con);
NABool cmGetThreeDeeOptionsControllerShowSpectrum(CPThreeDeeOptionsController* con);

void cmUpdateThreeDeeOptionsController(CPThreeDeeOptionsController* con);
