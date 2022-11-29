
#include "mainC.h"
#import <Cocoa/Cocoa.h>

CM_PROTOTYPE(CMColorMachineApplication);
CM_PROTOTYPE(CMColorsManager);
CM_PROTOTYPE(CMHSLColorController);
CM_PROTOTYPE(CMMachineWindowController);
CM_PROTOTYPE(CMMetamericsController);
CM_PROTOTYPE(CMThreeDeeController);




@interface ColorMachineApplication : NSApplication <NSApplicationDelegate>{
  CMColorsManager* colorsManager;
}

- (id)init;

- (void)applicationDidFinishLaunching:(NSNotification *)aNotification;

- (void)applicationDidChangeScreenParameters:(NSNotification *)aNotification;

- (IBAction)showAbout:(id)sender;
- (IBAction)showHelp:(NSMenuItem*)sender;

- (IBAction)resetMachine:(id)sender;
- (IBAction)setCurrentColorAsWhitepoint:(id)sender;
- (IBAction)setCurrentColorAsRedPrimary:(id)sender;
- (IBAction)setCurrentColorAsGreenPrimary:(id)sender;
- (IBAction)setCurrentColorAsBluePrimary:(id)sender;

+ (CGFloat) getUIScaleFactorForWindow:(NSWindow*)window;

@end
