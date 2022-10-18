
#include "CML.h"

typedef struct CMWhitePoints CMWhitePoints;
struct CMWhitePoints{
  CMLVec3 illXYZ10;
  CMLVec3 illXYZ2;
  CMLVec3 illXYZunnorm10;
  CMLVec3 illXYZunnorm2;
  CMLVec3 illYxy10;
  CMLVec3 illYxy2;
};

CMWhitePoints CMGetWhitePoints();
