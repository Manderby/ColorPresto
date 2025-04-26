
#include "../main.h"



CP_PROTOTYPE(NASpace);

typedef struct CPColorController CPColorController;
struct CPColorController{
  NASpace* space;
  NABool active;
  CMLColorType colorType;
};

void cpInitColorController(
  CPColorController* con,
  CMLColorType colorType);
void cpClearColorController(CPColorController* con);

void cpSetColorControllerColorType(CPColorController* con, CMLColorType colorType);

void cpSetColorControllerActive(CPColorController* con, NABool active);

CMLColorType cpGetColorControllerColorType(const CPColorController* con);
const void* cpGetColorControllerColorData(const CPColorController* con);
void cpSetColorControllerColorData(CPColorController* con, const void* data);

NASpace* cpGetColorControllerUIElement(CPColorController* con);

