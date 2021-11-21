
#import "main.h"
#import "ColorController.h"

@class MachineController;



@interface YuvColorController : ColorController {
  IBOutlet ColorWell *sliderY;
  IBOutlet ColorWell *sliderup;
  IBOutlet ColorWell *slidervp;
  IBOutlet ColorWell *slideru;
  IBOutlet ColorWell *sliderv;
  IBOutlet NSTextField *labelY;
  IBOutlet NSTextField *labelup;
  IBOutlet NSTextField *labelvp;
  IBOutlet NSTextField *labelu;
  IBOutlet NSTextField *labelv;
  IBOutlet InputTextField *textfieldY;
  IBOutlet InputTextField *textfieldup;
  IBOutlet InputTextField *textfieldvp;
  IBOutlet InputTextField *textfieldu;
  IBOutlet InputTextField *textfieldv;
}
- (void)awakeFromNib;
- (IBAction)valueChangeYupvp:(NSControl*)sender;
- (IBAction)valueChangeYuv:(NSControl*)sender;
- (void)update;
- (void)setActive:(BOOL)newactive;
@end


