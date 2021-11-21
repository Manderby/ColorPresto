
#import "main.h"
#import "ColorController.h"

@class MachineController;


@interface LabColorController : ColorController {
  IBOutlet ColorWell *sliderL;
  IBOutlet ColorWell *slidera;
  IBOutlet ColorWell *sliderb;
  IBOutlet ColorWell *sliderc;
  IBOutlet ColorWell *sliderh;
  IBOutlet NSTextField *labelL;
  IBOutlet NSTextField *labela;
  IBOutlet NSTextField *labelb;
  IBOutlet NSTextField *labelc;
  IBOutlet NSTextField *labelh;
  IBOutlet InputTextField *textfieldL;
  IBOutlet InputTextField *textfielda;
  IBOutlet InputTextField *textfieldb;
  IBOutlet InputTextField *textfieldc;
  IBOutlet InputTextField *textfieldh;
}
- (void)awakeFromNib;
- (IBAction)valueChangeLab:(NSControl*)sender;
- (IBAction)valueChangeLch:(NSControl*)sender;
- (void)update;
- (void)setActive:(BOOL)newactive;
@end


