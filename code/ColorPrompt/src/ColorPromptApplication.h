
#include "mainC.h"
#import <Cocoa/Cocoa.h>

CM_PROTOTYPE(CPColorPromptApplication);
CM_PROTOTYPE(CPColorsManager);
CM_PROTOTYPE(CMHSLColorController);
CM_PROTOTYPE(CPMachineWindowController);
CM_PROTOTYPE(CPMetamericsController);
CM_PROTOTYPE(CPThreeDeeController);




@interface ColorPromptApplication : NSApplication <NSApplicationDelegate>{
  CPColorsManager* colorsManager;
}

- (id)init;

- (void)applicationDidFinishLaunching:(NSNotification *)aNotification;

- (void)applicationDidChangeScreenParameters:(NSNotification *)aNotification;

- (IBAction)showAbout:(id)sender;
- (IBAction)showHelp:(NSMenuItem*)sender;

+ (CGFloat) getUIScaleFactorForWindow:(NSWindow*)window;

@end
