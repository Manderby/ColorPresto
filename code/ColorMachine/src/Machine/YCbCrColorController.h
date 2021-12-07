
#import "main.h"
#import "ColorController.h"

@class MachineController;


@interface YCbCrColorController : ColorController {
  IBOutlet ColorWell *sliderY;
  IBOutlet ColorWell *sliderCb;
  IBOutlet ColorWell *sliderCr;
  IBOutlet NSTextField *labelY;
  IBOutlet NSTextField *labelCb;
  IBOutlet NSTextField *labelCr;
  IBOutlet InputTextField *textFieldY;
  IBOutlet InputTextField *textFieldCb;
  IBOutlet InputTextField *textFieldCr;
}
- (void)awakeFromNib;
- (IBAction)valueChangeYCbCr:(NSControl*)sender;
- (void)update;
@end


