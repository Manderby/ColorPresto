
#include "mainC.h"



CM_PROTOTYPE(NASpace);

typedef struct CMColorController CMColorController;
struct CMColorController{
  NASpace* space;
  NABool active;
  CMLColorType colorType;
};

void cmInitColorController(
  CMColorController* con,
  CMLColorType colorType);
void cmClearColorController(CMColorController* con);

void cmSetColorControllerActive(CMColorController* con, NABool active);

CMLColorType cmGetColorControllerColorType(const CMColorController* con);
const void* cmGetColorControllerColorData(const CMColorController* con);
void cmSetColorControllerColorData(CMColorController* con, const void* data);

NASpace* cmGetColorControllerUIElement(CMColorController* con);
void cmUpdateColorController(CMColorController* con);

