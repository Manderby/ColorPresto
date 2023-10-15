
#import "ColorPromptApplication.h"
#include "CPColorPromptApplication.h"
#include "CPTranslations.h"

#include "NAApp.h"
#include "NAUICocoaLegacy.h"
#include "ManderAppAbout.h"



@implementation ColorPromptApplication

- (id)init{
  self = [super init];
  [self setDelegate:self];
  return self;
}

- (void)applicationDidChangeScreenParameters:(NSNotification *)aNotification{
  // theoretically, needs recomputation of the screen machine. todo.
  cmUpdateMachine();
}

- (void)applicationDidFinishLaunching:(NSNotification *)aNotification{  
}

- (void)applicationWillTerminate:(NSApplication *)sender{
  cmShutdownColorPromptApplication();
  naDelete(naGetApplication());
  naStopApplication();
  naStopRuntime();
}



- (IBAction)showAbout:(id)sender{
  mandShowAboutController();
}

- (IBAction)showHelp:(NSMenuItem*)sender{
  NA_UNUSED(sender);
  [[NSWorkspace sharedWorkspace] openURL:[NSURL URLWithString:[NSString stringWithUTF8String:cmTranslate(CMApplicationHelpURL)]]];
}



double cmGetUIScaleFactorForWindow(void* nativeWindowPtr){
  return [ColorPromptApplication getUIScaleFactorForWindow: (NA_COCOA_BRIDGE NSWindow*)nativeWindowPtr];
}

+ (CGFloat) getUIScaleFactorForWindow:(NSWindow*)window{
  return naGetWindowBackingScaleFactor(window);
}

@end

