
#include "ColorPrestoApplication.h"

#if NA_OS == NA_OS_MAC_OS_X

#include "CPAboutController.h"
#include "CPColorPrestoApplication.h"
#include "CPTranslations.h"

#include "NAApp/NAApp.h"
#include "NAUICocoaLegacy.h"



@implementation ColorPrestoApplication

- (id)init{
  self = [super init];
  [self setDelegate:self];
  return self;
}

- (void)applicationDidChangeScreenParameters:(NSNotification *)aNotification{
  // theoretically, needs recomputation of the screen machine. todo.
  cpUpdateMachine();
}

- (void)applicationDidFinishLaunching:(NSNotification *)aNotification{  
}

- (void)applicationWillTerminate:(NSApplication *)sender{
  cpShutdownColorPrestoApplication();
  naDelete(naGetApplication());
  naStopApplication();
  naStopRuntime();
}



- (IBAction)showAbout:(id)sender{
  cpShowAbout();
}

- (IBAction)showHelp:(NSMenuItem*)sender{
  NA_UNUSED(sender);
  [[NSWorkspace sharedWorkspace] openURL:[NSURL URLWithString:[NSString stringWithUTF8String:cpTranslate(CPApplicationHelpURL)]]];
}



@end

#endif // NA_OS == NA_OS_MAC_OS_X
