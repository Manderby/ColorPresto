
#import "main.h"
#import "ColorController.h"

@class MachineController;


@interface XYZColorController : ColorController {
  IBOutlet ColorWell *sliderX;
  IBOutlet ColorWell *sliderY;
  IBOutlet ColorWell *sliderZ;
  IBOutlet NSTextField *labelX;
  IBOutlet NSTextField *labelY;
  IBOutlet NSTextField *labelZ;
  IBOutlet InputTextField *textFieldX;
  IBOutlet InputTextField *textFieldY;
  IBOutlet InputTextField *textFieldZ;
}
- (void)awakeFromNib;
- (IBAction)valueChangeXYZ:(NSControl*)sender;
- (void)update;
- (void)setActive:(BOOL)newactive;
@end
