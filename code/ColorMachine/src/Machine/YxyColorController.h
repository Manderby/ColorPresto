
#import "main.h"
#import "ColorController.h"

@class MachineController;


@interface YxyColorController : ColorController {
  IBOutlet ColorWell *sliderY;
  IBOutlet ColorWell *sliderx;
  IBOutlet ColorWell *slidery;
  IBOutlet NSTextField *labelY;
  IBOutlet NSTextField *labelx;
  IBOutlet NSTextField *labely;
  IBOutlet InputTextField *textFieldY;
  IBOutlet InputTextField *textFieldx;
  IBOutlet InputTextField *textFieldy;
}
- (void)awakeFromNib;
- (IBAction)valueChangeYxy:(NSControl*)sender;
- (void)update;
- (void)setActive:(BOOL)newactive;
@end
