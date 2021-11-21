
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
  IBOutlet InputTextField *textfieldX;
  IBOutlet InputTextField *textfieldY;
  IBOutlet InputTextField *textfieldZ;
}
- (void)awakeFromNib;
- (IBAction)valueChangeXYZ:(NSControl*)sender;
- (void)update;
- (void)setActive:(BOOL)newactive;
@end
