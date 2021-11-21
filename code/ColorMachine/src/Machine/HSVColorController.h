
#import "main.h"
#import "ColorController.h"

@class MachineController;



@interface HSVColorController : ColorController {
  IBOutlet ColorWell *sliderH;
  IBOutlet ColorWell *sliderS;
  IBOutlet ColorWell *sliderV;
  IBOutlet NSTextField *labelH;
  IBOutlet NSTextField *labelS;
  IBOutlet NSTextField *labelV;
  IBOutlet InputTextField *textfieldH;
  IBOutlet InputTextField *textfieldS;
  IBOutlet InputTextField *textfieldV;
}
- (void)awakeFromNib;
- (IBAction)valueChangeHSV:(NSControl*)sender;
- (void)update;
- (void)setActive:(BOOL)newactive;
@end


