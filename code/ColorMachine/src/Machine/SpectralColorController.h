
#import "main.h"
#import "ColorController.h"

@class MachineController;

@interface SpectralDisplay : NSView {
  ColorController* colorcontroller;
}
- (void)awakeFromNib;
- (void)initWithController:(ColorController*)newcontroller;
- (void)drawRect:(NSRect)rect;
- (void)mouseDown:(NSEvent*)event;
- (void)mouseDragged:(NSEvent*)event;
@end


@interface SpectralColorController : ColorController {
}
- (void)awakeFromNib;
- (void)update;
- (void)setActive:(BOOL)newactive;
@end
