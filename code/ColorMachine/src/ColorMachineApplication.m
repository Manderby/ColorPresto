
#import "ColorMachineApplication.h"
#include "CMColorMachineApplication.h"
#include "CMTranslations.h"

#include "NAApp.h"
#include "NAUICocoaLegacy.h"
#include "ManderAppAbout.h"



@implementation ColorMachineApplication

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
  cmShutdownColorMachineApplication();
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



- (IBAction)resetMachine:(id)sender{
//  cmlReleaseColorMachine(cm);
//  cm = cmlCreateColorMachine();
//  [self updateMachine];
}

- (IBAction)setCurrentColorAsWhitepoint:(id)sender{
//  float yxybuf[3];
//  [colorscontroller currentColor]->toYxyBuffer(yxybuf);
//  cmlSetReferenceWhitePointYxy(cm, yxybuf);
//  [self updateMachine];
}

- (IBAction)setCurrentColorAsRedPrimary:(id)sender{
//  CMLVec3 primaries[3];
//  cmlGetRGBPrimariesYxy(cm, primaries);
//  [colorscontroller currentColor]->toYxyBuffer(primaries[0]);
//  cmlSetRGBPrimariesYxy(cm, primaries);
//  [self updateMachine];
}
- (IBAction)setCurrentColorAsGreenPrimary:(id)sender{
//  CMLVec3 primaries[3];
//  cmlGetRGBPrimariesYxy(cm, primaries);
//  [colorscontroller currentColor]->toYxyBuffer(primaries[1]);
//  cmlSetRGBPrimariesYxy(cm, primaries);
//  [self updateMachine];
}
- (IBAction)setCurrentColorAsBluePrimary:(id)sender{
//  CMLVec3 primaries[3];
//  cmlGetRGBPrimariesYxy(cm, primaries);
//  [colorscontroller currentColor]->toYxyBuffer(primaries[2]);
//  cmlSetRGBPrimariesYxy(cm, primaries);
//  [self updateMachine];
}


double cmGetUIScaleFactorForWindow(void* nativeWindowPtr){
  return [ColorMachineApplication getUIScaleFactorForWindow: (NSWindow*)nativeWindowPtr];
}

+ (CGFloat) getUIScaleFactorForWindow:(NSWindow*)window{
  return naGetWindowBackingScaleFactor(window);
}

@end

