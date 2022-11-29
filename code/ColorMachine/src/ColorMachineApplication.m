
#import "ColorMachineApplication.h"
#include "CMColorMachineApplication.h"

#include "CMDesign.h"

#include "CMColorsManager.h"
#include "CMMachineWindowController.h"
#include "CMMetamericsController.h"
#include "CMTranslations.h"
#include "CMThreeDeeController.h"

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
  cmStartupColorMachineApplication();
}

- (void)applicationWillTerminate:(NSApplication *)sender{
  cmShutdownColorMachineApplication(app);

  naDelete(naGetApplication());

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



+ (CGFloat) getUIScaleFactorForWindow:(NSWindow*)window{
  return naGetWindowBackingScaleFactor(window);
}

@end

