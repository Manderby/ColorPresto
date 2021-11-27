
#include <CML.h>
#import "main.h"


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


typedef CMLuint32 CMLVec4UInt[CML_MAX_NUMBER_OF_CHANNELS];
inline static void cmlCpy4UInt(CMLVec4UInt d, const CMLVec4UInt a) {d[0]=a[0];d[1]=a[1];d[2]=a[2];d[3]=a[3];}
inline static void cmlSet4UInt(CMLVec4UInt d, uint32 a0, uint32 a1, uint32 a2, uint32 a3) {d[0]=a0;d[1]=a1;d[2]=a2;d[3]=a3;}

typedef struct CMLBoundsInt{
  CMLuint32 min;
  CMLuint32 max;
} CMLBoundsInt;

typedef struct CMLBoundsFloat{
  float min;
  float max;
} CMLBoundsFloat;

typedef CMLBoundsInt CMLChannelBoundsInt[CML_MAX_NUMBER_OF_CHANNELS];
typedef CMLBoundsFloat CMLChannelBoundsFloat[CML_MAX_NUMBER_OF_CHANNELS];

// Creates a one-, two-, three- or four-dimensional array filled with normed
// color values in the given colorspace.
//
// This function is named Slice because it is used very often for getting
// two-dimensional surfaces out of a three-dimensional body. But using this
// function, you can get any part of any body in up to four dimensions.
//
// The numbers given in the dimensions parameter depict the number of steps per
// dimension. For example, the parameter dimensions={20, 40, 0, 0} will create
// a two-dimensional array with 20 steps in the primary and 40 steps
// in the secondary axis.
//
// In the dimensions-parameter, the value 0 will be interpreted as 1. This
// means that in the example above, you can write dimensions={20, 40, 1, 1}
// which does exactly the same thing. This has been introduced to simplify
// the work of any programmer who often juggles around with different
// dimension-settings. This also means that the function always returns an
// array with at least 1 color entry.
//
// The returned array is filled with a linear combination of normed color values
// in the given colorspace. The range of the values for all channels can be
// given by the remaining parameters. The origin parameter defines the origin
// of the linear combination. The next four parameters defines the
// range of the primary, secondary, ternary and quaternary dimension.
//
// All of the origin- and range-parameters can be set to NULL. In this case, a
// default origin and range will be assumed. The default origin
// is 0 and the default range is 1 for the channel depicted by the dimension and
// 0 elsewhere. Note that if the stepSize of a dimension is 0 or 1, the range of
// that dimension is unused.
//
// Only the values of the channels available in the given colorspace
// will be considered. The rest of the CMLVec4-values is ignored.
//
// Let's assume in the above example, that the colorspace is RGB and the
// following parameters are given:
// origin = {0, .5,  1, 0};
// range0 = {1,  0,  0, 0};
// range1 = {0,  0, -1, 0};
// range2 = NULL;
// range3 = NULL;
// This will result in a color plane where in primary dimension, the red
// component goes from 0 to 1 and in secondary dimension, the blue component
// goes from 1 to 0. The green component is .5 always. The parameters range2
// and range3 are ignored as the number of steps is 0 or 1 respectively. 
//
// Note that the returned arrays are always stored as one-dimensional row-first
// C-Arrays. Therefore, a two-dimensional array must be addressed with
// DesiredColor = returnedarray[y * dim[0] * numchannels + x * numchannels];
// where according to the example above, dim[0] would be 20 and numchannels
// would be 3.
//
// To convert the resulting values to non-normed color-coordinates, simply
// convert the whole array using the appropriate fromNormedInput-Converter.
// In the example above, this would be cmlNormedInputToRGB. Note that you
// need to provide the buffer for this conversion by yourself. The required
// number of bytes can be computed like this:
// numbytes = dim[0] * dim[1] * dim[2] * dim[3] * numchannels * sizeof(float);
// (Beware of 0-Entries in dim!)
//
// The returned array must be deleted manually by the user with free();
//
// This function does only work with channeled color types. Any other
// colorspace will return NULL.

CMLOutput cmlCreateNormedGamutSlice(  CMLColorType colorspace,
                                 const CMLVec4UInt dimensions,
                                     const CMLVec4 origin,
                                     const CMLVec4 range0,
                                     const CMLVec4 range1,
                                     const CMLVec4 range2,
                                     const CMLVec4 range3);




@class MachineController;
@class ThreeDeeWindowController;

@interface ThreeDeeDisplay : NSOpenGLView {
  IBOutlet ThreeDeeWindowController* controller;
  float mousex;
  float mousey;
  CMLint32 width;
  CMLint32 height;
  float viewpol;
  float viewequ;
  float zoom;
}
- (id)initWithFrame:(NSRect)frameRect;
- (void)awakeFromNib;

- (void)getWidthHeight;
- (void)fixViewParameters;

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
  dispatch_semaphore_t semaphore;
  
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
  
}
- (void)awakeFromNib;
- (void)dealloc;
- (void)update;
- (void)showDialog;
- (void)windowWillClose:(NSNotification *)notification;

- (void)autodisplay;

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
