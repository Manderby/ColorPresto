
#import "main.h"
#import "ColorController.h"

@class MachineController;

@interface GammaDisplay : ColorMachineOpenGLView {}
- (void)drawRect:(NSRect)rect;
@end


@interface RGBColorController : ColorController {
  IBOutlet ColorWell *sliderR;
  IBOutlet ColorWell *sliderG;
  IBOutlet ColorWell *sliderB;
  IBOutlet NSTextField *labelR;
  IBOutlet NSTextField *labelG;
  IBOutlet NSTextField *labelB;
  IBOutlet NSTextField *labelHash;
  IBOutlet InputTextField *textFieldR;
  IBOutlet InputTextField *textFieldG;
  IBOutlet InputTextField *textFieldB;
  IBOutlet InputTextField *textFieldweb;
  IBOutlet InputTextField *textFieldwebrgb;
}
- (void)awakeFromNib;
- (IBAction)valueChangeRGB:(NSControl*)sender;
- (IBAction)valueChangeweb:(NSControl*)sender;
- (IBAction)valueChangewebrgb:(NSControl*)sender;
- (void)update;
- (void)setActive:(BOOL)newactive;
@end


