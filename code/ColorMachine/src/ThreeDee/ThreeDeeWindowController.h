
#include <CML.h>
#import "main.h"
#include "NABase.h"

typedef enum{
  COORDSYSTEM_XYZ,
  COORDSYSTEM_YXY,
  COORDSYSTEM_Yuv,
  COORDSYSTEM_YCBCR,
  COORDSYSTEM_LAB,
  COORDSYSTEM_LCH_CARTESIAN,
  COORDSYSTEM_LUV,
  COORDSYSTEM_RGB,
  COORDSYSTEM_HSV,
  COORDSYSTEM_HSV_CARTESIAN,
  COORDSYSTEM_HSL,
  COORDSYSTEM_HSL_CARTESIAN,
  NUMBER_OF_COORDINATE_SYSTEMS
} CoordSystemType;


typedef size_t CMLVec4UInt[CML_MAX_NUMBER_OF_CHANNELS];
inline static void cmlSet4UInt(CMLVec4UInt d, uint32 a0, uint32 a1, uint32 a2, uint32 a3) {d[0]=a0;d[1]=a1;d[2]=a2;d[3]=a3;}

typedef struct CMLBoundsInt{
  size_t min;
  size_t max;
} CMLBoundsInt;

typedef struct CMLBoundsFloat{
  float min;
  float max;
} CMLBoundsFloat;

typedef CMLBoundsInt CMLChannelBoundsInt[CML_MAX_NUMBER_OF_CHANNELS];
typedef CMLBoundsFloat CMLChannelBoundsFloat[CML_MAX_NUMBER_OF_CHANNELS];





@class MachineController;
@class ThreeDeeWindowController;

@interface ThreeDeeDisplay : NSOpenGLView {
  IBOutlet ThreeDeeWindowController* controller;
  float mousex;
  float mousey;
  int width;
  int height;
  float viewpol;
  float viewequ;
  float zoom;
  NAInt fontId;
}
- (id)initWithFrame:(NSRect)frameRect;
- (void)awakeFromNib;

- (void)getWidthHeight;
- (void)fixViewParameters;

- (void)rotateBy:(float)ang;

- (void)drawRect:(NSRect)rect;
- (void)mouseDown:(NSEvent*)event;
- (void)mouseDragged:(NSEvent*)event;
- (void)scrollWheel:(NSEvent*)event;
@end





@interface ThreeDeeWindowController : NSWindowController <NSWindowDelegate> {
  IBOutlet NSPopUpButton *space3dselect;
  IBOutlet NSPopUpButton *coord3dselect;
  IBOutlet NSSlider *steps3dslider;
  IBOutlet NSSlider *pointsalphaslider;
  IBOutlet NSSlider *gridalphaslider;
  IBOutlet NSSlider *gridtintsslider;
  IBOutlet NSSlider *bodyalphaslider;
  IBOutlet NSSlider *backgroundcolorslider;
  IBOutlet NSSlider *fovyslider;
  IBOutlet NSSlider *rotationslider;
  IBOutlet NSButton *solidcheckbox;
  IBOutlet NSButton *axischeckbox;
  IBOutlet NSButton *spectrumcheckbox;
  IBOutlet ThreeDeeDisplay *colordisplay;
//  bool fullscreen;

  float backgroundgray;
  float fovy;
  bool showaxis;
  float rotation;
  bool dispatchinprogress;
//  dispatch_semaphore_t semaphore;
  
  CMLColorType space3d;
  uint8 steps3d;
  CoordSystemType coord3d;
  bool outline3d;
  float pointsalpha;
  uint8 bodyalpha;
  uint8 gridalpha;
  float gridwhiteness;
  bool bodysolid;
  bool showspectrum;
//  NAMutex mutex;
}
- (void)awakeFromNib;
- (void)dealloc;
- (void)update;
- (void)showDialog;
- (void)windowWillClose:(NSNotification *)notification;

//- (void)autodisplay;

- (void)getBackgroundRGB:(CMLVec3) returncolor;
- (void)getAxisRGB:(CMLVec3) returncolor;
- (float)getFovy;
- (bool)getShowAxis;
- (bool)getShowSpectrum;
- (CMLColorType)getColorSpace;
- (CoordSystemType)getCoordinateSpace;
- (uint8)getSteps;
- (bool)getBodySolid;
- (float)getPointsAlpha;
- (uint8)getBodyAlpha;
- (uint8)getGridAlpha;
- (float)getGridWhiteness;
- (float)getRotation;
- (ThreeDeeDisplay*)getColorDisplay;

//- (IBAction)switchFullscreen:(NSButton*)sender;
- (IBAction)space3dChange:(NSPopUpButton*)sender;
- (IBAction)coord3dChange:(NSPopUpButton*)sender;
- (IBAction)steps3dChange:(NSSlider*)sender;
- (IBAction)bodyalphaChange:(NSSlider*)sender;
- (IBAction)gridwhitenessChange:(NSSlider*)sender;
- (IBAction)pointsalphaChange:(NSSlider*)sender;
- (IBAction)gridalphaChange:(NSSlider*)sender;
- (IBAction)perspectivityChange:(NSSlider*)sender;
- (IBAction)backgroundChange:(NSSlider*)sender;
- (IBAction)spectralChange:(NSButton*)sender;
- (IBAction)solidChange:(NSButton*)sender;
- (IBAction)axisChange:(NSButton*)sender;
- (IBAction)rotationChange:(NSSlider*)sender;
- (IBAction)stopRotation:(NSButton*)sender;
@end
