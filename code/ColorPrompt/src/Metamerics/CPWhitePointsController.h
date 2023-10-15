
#include "../mainC.h"
#include "CPColorConversionsYcdUVW.h"

CP_PROTOTYPE(CPWhitePoints);
CP_PROTOTYPE(NASpace);



typedef struct CPWhitePointsController CPWhitePointsController;

CPWhitePointsController* cmAllocWhitePointsController(void);
void cmDeallocWhitePointsController(CPWhitePointsController* con);

NASpace* cmGetWhitePointsUIElement(CPWhitePointsController* con);
CPReferenceIlluminationType cmGetReferenceIlluminationType(CPWhitePointsController* con);

void cmUpdateWhitePointsController(
  CPWhitePointsController* con,
  const NAUTF8Char* illuminationName,
  const CPWhitePoints* illWhitePoint10,
  const CPWhitePoints* illWhitePoint2,
  const CPWhitePoints* refWhitePoint10,
  const CPWhitePoints* refWhitePoint2);
