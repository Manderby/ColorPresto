
#include "mainC.h"
#import <Cocoa/Cocoa.h>

CP_PROTOTYPE(CPColorPromptApplication);
CP_PROTOTYPE(CPColorsManager);
CP_PROTOTYPE(CPHSLColorController);
CP_PROTOTYPE(CPMachineWindowController);
CP_PROTOTYPE(CPMetamericsController);
CP_PROTOTYPE(CPThreeDeeController);




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
