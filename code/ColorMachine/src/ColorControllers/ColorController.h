
#import "main.h"
#import "ColorMachineOpenGLView.h"

@class ColorController;



@interface InputTextField : NSTextField {
  IBOutlet ColorController* colorcontroller;
}
- (BOOL)becomeFirstResponder;
@end





@interface ColorController : NSView {
  BOOL active;
  Color* color;
  IBOutlet NSView *colordisplay;
  IBOutlet InputTextField* firsttextField;
}
- (id)init;
- (void)dealloc;
- (NSView*) colordisplay;
- (Color*&) color;
- (Color*) getColor;
- (BOOL)isActive;
- (BOOL)isOpaque;
- (void)drawRect:(NSRect)dirtyRect;
- (void)setActive:(BOOL)active;
- (void)mouseDown:(NSEvent *)theEvent;
@end




