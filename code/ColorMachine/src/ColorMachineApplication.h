
#import "main.h"

CM_PROTOTYPE(CMThreeDeeController);

@class MachineWindowController;
@class AboutWindowController;
@class ScreenResolutionWindowController;
@class ThreeDeeWindowController;
@class MetamericsWindowController;

@class MachinesController;
@class ColorController;
@class ColorsController;
@class GrayColorController;
@class ColorMachineOutlineView;

@class OutlineViewItem;

extern CMLColorType maskcolor;
extern bool showmask;
extern bool showgrid;
extern float borderthickness;
extern size_t bordercount;


//#define COLOR_MACHINE_ITEM_HEIGHT_CHANGED @"ColorMachineItemHeightChanged"

//#define COLOR_MACHINE_EXPAND_COLOR_SELECTION @"ColorMachineExpandColorSelection"
//#define COLOR_MACHINE_COLLAPSE_COLOR_SELECTION @"ColorMachineCollapseColorSelection"

//#define COLOR_MACHINE_ITEM_CHANGED @"ColorMachineItemChanged"
//#define COLOR_MACHINE_ADD_COLORGROUP @"ColorMachineAddColorGroup"
//#define COLOR_MACHINE_ASSIMILATE_COLOR @"ColorMachineAssimilateColor"


@interface ColorMachineApplication : NSApplication <NSApplicationDelegate>{
  CMThreeDeeController* threeDeeController;

  IBOutlet AboutWindowController* aboutwindowcontroller;
  IBOutlet ThreeDeeWindowController* threedeewindowcontroller;
  IBOutlet MetamericsWindowController* metamericswindowcontroller;
  IBOutlet MachineWindowController* machinewindowcontroller;
  IBOutlet ScreenResolutionWindowController* screenresolutionwindowcontroller;
  
  MachinesController* machinescontroller;
  IBOutlet ColorsController* colorscontroller;
  
  NSTimeInterval sleepinterval;
}

- (void)applicationDidChangeScreenParameters:(NSNotification *)aNotification;
- (BOOL)applicationShouldTerminateAfterLastWindowClosed:(NSApplication *)theApplication;
- (void)applicationDidFinishLaunching:(NSNotification *)aNotification;
- (NSApplicationTerminateReply)applicationShouldTerminate:(NSApplication *)sender;

//- (void)awakeFromNib;
- (id)init;

- (IBAction)showAbout:(id)sender;
- (IBAction)showHelp:(NSMenuItem*)sender;
//- (IBAction)showScreensTool:(id)sender;
- (IBAction)showScreenResolution:(id)sender;
- (IBAction)showThreeDee:(id)sender;
- (IBAction)showMetamerics:(id)sender;

- (void)setCurrentColor:(const Color*)color;
- (const Color*)getCurrentColor;
- (void)colorHasChanged;
- (void)setWorkingColorController:(ColorController*) workingcolorcontroller;
- (CMLColorMachine*)getCurrentMachine;
- (CMLColorMachine*)getCurrentScreenMachine;
- (MachineWindowController*)getMachineWindowController;
- (ColorsController*)getColorsController;
- (void)updateMachine;
- (void)updateColor;

- (IBAction)resetMachine:(id)sender;
- (IBAction)setCurrentColorAsWhitepoint:(id)sender;
- (IBAction)setCurrentColorAsRedPrimary:(id)sender;
- (IBAction)setCurrentColorAsGreenPrimary:(id)sender;
- (IBAction)setCurrentColorAsBluePrimary:(id)sender;

- (void)fillRGBfloatarray :(float*)texdata
              fromArray:(float*)inputarray
          withColorType:(CMLColorType)inputColorType
   normedInputConverter:(CMLNormedConverter)normedconverter
                  count:(size_t)count
               drawgrid:(BOOL)drawgridlines
               drawmask:(BOOL)drawmask;

//- (void)fillRGBuint8array :(Byte*)texdata
//              fromArray:(float*)inputarray
//          withColorType:(CMLColorType)inputColorType
//   normedInputConverter:(CMLNormedConverter)normedconverter
//                  count:(size_t)count
//               drawgrid:(BOOL)drawgridlines
//               drawmask:(BOOL)drawmask;

- (void)fillRGBfloatarray:(float*)outdata fromColor:(const Color*)inputcolor;

- (void)drawColor:(const Color*)color fillBack:(BOOL)fill linecolor:(CGColorRef)linecolor context:(CGContextRef)context inRect:(CGRect)rect;


+ (CGFloat) getUIScaleFactorForWindow:(NSWindow*)window;

@end
