
#import "main.h"
#import "ColorController.h"

@class MachineController;


@interface LuvColorController : ColorController {
  IBOutlet ColorWell *sliderL;
  IBOutlet ColorWell *slideru;
  IBOutlet ColorWell *sliderv;
  IBOutlet NSTextField *labelL;
  IBOutlet NSTextField *labelu;
  IBOutlet NSTextField *labelv;
  IBOutlet InputTextField *textFieldL;
  IBOutlet InputTextField *textFieldu;
  IBOutlet InputTextField *textFieldv;
}
- (void)awakeFromNib;
- (IBAction)valueChangeLuv:(NSControl*)sender;
- (void)update;
- (void)setActive:(BOOL)newactive;
@end


