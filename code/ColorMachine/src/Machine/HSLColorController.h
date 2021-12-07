
#import "main.h"
#import "ColorController.h"

@class MachineController;



@interface HSLColorController : ColorController {
  IBOutlet ColorWell *sliderH;
  IBOutlet ColorWell *sliderS;
  IBOutlet ColorWell *sliderL;
  IBOutlet NSTextField *labelH;
  IBOutlet NSTextField *labelS;
  IBOutlet NSTextField *labelL;
  IBOutlet InputTextField *textFieldH;
  IBOutlet InputTextField *textFieldS;
  IBOutlet InputTextField *textFieldL;
}
- (void)awakeFromNib;
- (IBAction)valueChangeHSL:(NSControl*)sender;
- (void)update;
- (void)setActive:(BOOL)newactive;
@end


