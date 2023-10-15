
#include "../mainC.h"



CP_PROTOTYPE(NASpace);

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

CMLColorType cpGetColorControllerColorType(const CPColorController* con);
const void* cpGetColorControllerColorData(const CPColorController* con);
void cmSetColorControllerColorData(CPColorController* con, const void* data);

NASpace* cmGetColorControllerUIElement(CPColorController* con);
void cpUpdateColorController(CPColorController* con);

