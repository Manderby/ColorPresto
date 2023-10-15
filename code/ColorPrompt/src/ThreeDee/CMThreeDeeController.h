
#ifndef THREE_DEE_CONTROLLER_DEFINED
#define THREE_DEE_CONTROLLER_DEFINED



typedef enum{
  COLOR_SPACE_GRAY,
  COLOR_SPACE_HSL,
  COLOR_SPACE_HSV,
  COLOR_SPACE_Lab,
  COLOR_SPACE_Lch,
  COLOR_SPACE_Luv,
  COLOR_SPACE_RGB,
  COLOR_SPACE_UVW,
  COLOR_SPACE_XYZ,
  COLOR_SPACE_YCbCr,
  COLOR_SPACE_Ycd,
  COLOR_SPACE_Yuv,
  COLOR_SPACE_Yxy,
  COLOR_SPACE_COUNT
} ColorSpaceType;

typedef enum{
  COORD_SYS_HSL,
  COORD_SYS_HSL_CARTESIAN,
  COORD_SYS_HSV,
  COORD_SYS_HSV_CARTESIAN,
  COORD_SYS_Lab,
  COORD_SYS_Lch_CARTESIAN,
  COORD_SYS_Luv,
  COORD_SYS_RGB,
  COORD_SYS_UVW,
  COORD_SYS_XYZ,
  COORD_SYS_Ycbcr,
  COORD_SYS_Ycd,
  COORD_SYS_Yupvp,
  COORD_SYS_Yuv,
  COORD_SYS_Yxy,
  COORD_SYS_COUNT
} CoordSysType;



typedef struct CMThreeDeeController CMThreeDeeController;

CMThreeDeeController* cmAllocThreeDeeController(void);
void cmDeallocThreeDeeController(CMThreeDeeController* con);

void cmRefreshThreeDeeDisplay(CMThreeDeeController* con);

void cmShowThreeDeeController(CMThreeDeeController* con);
void cmUpdateThreeDeeController(CMThreeDeeController* con);



#endif // THREE_DEE_CONTROLLER_DEFINED
