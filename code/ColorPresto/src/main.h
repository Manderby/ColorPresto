
#ifndef CP_MAIN_INCLUDED
#define CP_MAIN_INCLUDED

#define CP_PROTOTYPE(type) typedef struct type type

#define cpError naError

CP_PROTOTYPE(CMLColorMachine);

CP_PROTOTYPE(CPColorController);
CP_PROTOTYPE(CPHSLColorController);


#include "CML.h"
#include "NABase/NABase.h"
#include "NAApp/NAApp.h"


#define CP_COLOR_PRESTO_STORAGE_TAG       1
#define CP_METAMERICS_WINDOW_STORAGE_TAG  2
#define CP_THREEDEE_WINDOW_STORAGE_TAG    3
#define CP_ABOUT_WINDOW_STORAGE_TAG       4
#define CP_PREFERENCES_WINDOW_STORAGE_TAG 5

typedef enum {
  HSV,
  HSL,
  HSVHSLSelectCount
} HSVHSLSelect;

typedef enum {
  Luv,
  UVW,
  LuvUVWSelectCount
} LuvUVWSelect;

typedef enum {
  Lab,
  Lch,
  LabLchSelectCount
} LabLchSelect;

typedef enum {
  Yuv,
  Yupvp,
  YuvYupvpSelectCount
} YuvYupvpSelect;




void cpSetCurrentColorController(const CPColorController* con);
const CPColorController* cpGetCurrentColorController(void);

const float* cpGetCurrentColorData(void);
CMLColorType cpGetCurrentColorType(void);


void fillRGBFloatArrayWithArray(const CMLColorMachine* cm, const CMLColorMachine* sm, float* texdata, const float* inputarray, CMLColorType inputColorType, CMLNormedConverter normedConverter, size_t count);


#endif // CP_MAIN_INCLUDED
