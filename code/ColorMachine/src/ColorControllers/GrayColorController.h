
#import "main.h"
#import "ColorController.h"

@class MachineController;


@interface GrayDisplay : NSView {
  IBOutlet ColorController* colorcontroller;
}
- (void)drawRect:(NSRect)rect;
@end


@interface GrayColorController : ColorController {
  IBOutlet ColorWell *sliderGray;
  IBOutlet NSTextField *labelGray;
  IBOutlet InputTextField *textFieldGray;
}
- (void)awakeFromNib;
- (IBAction)valueChangeGray:(NSControl*)sender;
- (void)update;
- (void)setActive:(BOOL)newactive;

@end
