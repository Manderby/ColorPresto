
#include "CPColorPrestoNSApplication.h"

#if NA_OS == NA_OS_MAC_OS_X

#include "About/CPAboutController.h"
#include "CPColorPrestoApplication.h"
#include "CPTranslations.h"

#include "NAApp/NAApp.h"
#include "NAUtility/NAMemory.h"



@implementation CPColorPrestoNSApplication

- (id)init{
  self = [super init];
  [self setDelegate:self];
  return self;
}

- (void)applicationDidChangeScreenParameters:(NSNotification *)aNotification{
  // theoretically, needs recomputation of the screen machine. todo.
  cpUpdateMachine();
}

- (IBAction)openAbout:(id)sender{
  NA_UNUSED(sender);
  cpShowAbout();
}

- (IBAction)openHelp:(NSMenuItem*)sender{
  NA_UNUSED(sender);
  [[NSWorkspace sharedWorkspace] openURL:[NSURL URLWithString:[NSString stringWithUTF8String:cpTranslate(CPApplicationHelpURL)]]];
}

- (IBAction)openPreferences:(id)sender{
  NA_UNUSED(sender);
  cpShowPreferences();
}

- (void)terminate:(id)sender{
  NA_UNUSED(sender);
  //naStopApplication();
  [super terminate:sender];
}



@end

#endif // NA_OS == NA_OS_MAC_OS_X
