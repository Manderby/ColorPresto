
#import "main.h"

CM_PROTOTYPE(CMColorsManager);
CM_PROTOTYPE(CMMachineWindowController);
CM_PROTOTYPE(CMMetamericsController);
CM_PROTOTYPE(CMThreeDeeController);

CM_PROTOTYPE(CMHSLColorController);

@class MachineWindowController;
@class ThreeDeeWindowController;

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
  CMLColorMachine* cm; // current ColorMachine
  CMLColorMachine* sm; // current ScreenMachine

  CMColorsManager* colorsManager;

  CMMachineWindowController* machineWindowController2;
  CMMetamericsController* metamericsController;
  CMThreeDeeController* threeDeeController;

  IBOutlet MachineWindowController* machinewindowcontroller;
  
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
- (CMColorsManager*)getColorsManager;
- (void)updateMachine;
- (void)updateColor;
- (void)updateMetamerics;

- (IBAction)resetMachine:(id)sender;
- (IBAction)setCurrentColorAsWhitepoint:(id)sender;
- (IBAction)setCurrentColorAsRedPrimary:(id)sender;
- (IBAction)setCurrentColorAsGreenPrimary:(id)sender;
- (IBAction)setCurrentColorAsBluePrimary:(id)sender;

- (void)fillRGBfloatarray:(float*)outdata fromColor:(const Color*)inputcolor;

- (void)drawColor:(const Color*)color fillBack:(BOOL)fill linecolor:(CGColorRef)linecolor context:(CGContextRef)context inRect:(CGRect)rect;


+ (CGFloat) getUIScaleFactorForWindow:(NSWindow*)window;

@end
