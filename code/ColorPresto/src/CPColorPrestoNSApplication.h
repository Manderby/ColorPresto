
#include "main.h"

#if NA_OS == NA_OS_MAC_OS_X

#import <Cocoa/Cocoa.h>

CP_PROTOTYPE(CPColorPrestoApplication);
CP_PROTOTYPE(CPColorsManager);
CP_PROTOTYPE(CPHSLColorController);
CP_PROTOTYPE(CPMachineWindowController);
CP_PROTOTYPE(CPMetamericsController);
CP_PROTOTYPE(CPThreeDeeController);




@interface CPColorPrestoNSApplication : NSApplication <NSApplicationDelegate>{
  CPColorsManager* colorsManager;
}

- (id)init;

- (void)applicationDidChangeScreenParameters:(NSNotification *)aNotification;

- (IBAction)showAbout:(id)sender;
- (IBAction)showHelp:(NSMenuItem*)sender;

- (void)terminate:(id)sender;

@end

#endif // NA_OS == NA_OS_MAC_OS_X
