
#include "../mainC.h"
#include "CPColorConversionsYcdUVW.h"

CP_PROTOTYPE(CPWhitePoints);
CP_PROTOTYPE(NASpace);



typedef struct CPWhitePointsController CPWhitePointsController;

CPWhitePointsController* cpAllocWhitePointsController(void);
void cpDeallocWhitePointsController(CPWhitePointsController* con);

NASpace* cpGetWhitePointsUIElement(CPWhitePointsController* con);
CPReferenceIlluminationType cpGetReferenceIlluminationType(CPWhitePointsController* con);

void cpUpdateWhitePointsController(
  CPWhitePointsController* con,
  const NAUTF8Char* illuminationName,
  const CPWhitePoints* illWhitePoint10,
  const CPWhitePoints* illWhitePoint2,
  const CPWhitePoints* refWhitePoint10,
  const CPWhitePoints* refWhitePoint2);
