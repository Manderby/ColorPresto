#import "main.h"
@class ScreenResolutionWindowController;

@interface RulerView : NSView{
  ScreenResolutionWindowController* controller;
  bool showcm;
  double prevmousedist;
}
- (void)mouseDragged:(NSEvent*)event;
- (void)mouseDown:(NSEvent*)event;
- (void)setController:(ScreenResolutionWindowController*)controller;
@end

@interface ScreenResolutionWindowController : NSWindowController {
  IBOutlet NSButton* radiocm;
  IBOutlet NSButton* radioinch;
  IBOutlet NSTextField* textH;
  IBOutlet NSTextField* textV;
  IBOutlet NSButton* fullscreenbutton;
  IBOutlet NSButton* closebutton;
//  IBOutlet RulerView* rulerview;
  IBOutlet NSTextField* textpixels;
  IBOutlet NSTextField* textratio;
  IBOutlet NSTextField* texthsize;
  IBOutlet NSTextField* textvsize;
  IBOutlet NSTextField* textdsize;
  bool fullscreen;

  @public

  bool showcm;
  double hppi;
  double vppi;
}
- (void)awakeFromNib;
- (IBAction)cminchchange:(NSButton*)sender;
- (IBAction)ppichange:(NSTextField*)sender;
- (void)update;
- (void)showDialog;
- (IBAction)switchFullscreen:(NSButton*)sender;
@end


