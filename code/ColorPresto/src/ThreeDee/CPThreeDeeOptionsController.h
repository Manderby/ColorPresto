
#include "../main.h"
#include "NAApp/NAApp.h"
#include "CPThreeDeeController.h"

CP_PROTOTYPE(CPWhitePoints);
CP_PROTOTYPE(NASpace);



typedef struct CPThreeDeeOptionsController CPThreeDeeOptionsController;

CPThreeDeeOptionsController* cpAllocThreeDeeOptionsController(CPThreeDeeController* parent);
void cpDeallocThreeDeeOptionsController(CPThreeDeeOptionsController* con);

NASpace* cpGetThreeDeeOptionsControllerUIElement(CPThreeDeeOptionsController* con);

float cpGetThreeDeeOptionsControllerAxisGray(CPThreeDeeOptionsController* con);
float cpGetThreeDeeOptionsControllerBackgroundGray(CPThreeDeeOptionsController* con);
float cpGetThreeDeeOptionsControllerFovy(CPThreeDeeOptionsController* con);
NABool cpGetThreeDeeOptionsControllerShowAxis(CPThreeDeeOptionsController* con);
NABool cpGetThreeDeeOptionsControllerShowSpectrum(CPThreeDeeOptionsController* con);

void cpUpdateThreeDeeOptionsController(CPThreeDeeOptionsController* con);
