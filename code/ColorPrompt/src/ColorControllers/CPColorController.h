
#include "../mainC.h"



CM_PROTOTYPE(NASpace);

typedef struct CPColorController CPColorController;
struct CPColorController{
  NASpace* space;
  NABool active;
  CMLColorType colorType;
};

void cmInitColorController(
  CPColorController* con,
  CMLColorType colorType);
void cmClearColorController(CPColorController* con);

void cmSetColorControllerColorType(CPColorController* con, CMLColorType colorType);

void cmSetColorControllerActive(CPColorController* con, NABool active);

CMLColorType cmGetColorControllerColorType(const CPColorController* con);
const void* cmGetColorControllerColorData(const CPColorController* con);
void cmSetColorControllerColorData(CPColorController* con, const void* data);

NASpace* cmGetColorControllerUIElement(CPColorController* con);
void cmUpdateColorController(CPColorController* con);

