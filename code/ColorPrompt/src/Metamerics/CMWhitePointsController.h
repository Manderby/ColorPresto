
#include "../mainC.h"
#include "CMColorConversionsYcdUVW.h"

CM_PROTOTYPE(CMWhitePoints);
CM_PROTOTYPE(NASpace);



typedef struct CMWhitePointsController CMWhitePointsController;

CMWhitePointsController* cmAllocWhitePointsController(void);
void cmDeallocWhitePointsController(CMWhitePointsController* con);

NASpace* cmGetWhitePointsUIElement(CMWhitePointsController* con);
CMReferenceIlluminationType cmGetReferenceIlluminationType(CMWhitePointsController* con);

void cmUpdateWhitePointsController(
  CMWhitePointsController* con,
  const NAUTF8Char* illuminationName,
  const CMWhitePoints* illWhitePoint10,
  const CMWhitePoints* illWhitePoint2,
  const CMWhitePoints* refWhitePoint10,
  const CMWhitePoints* refWhitePoint2);
