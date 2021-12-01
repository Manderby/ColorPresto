
#import "ColorController.h"
#import "ColorMachineOpenGLView.h"
#import "ColorMachineApplication.h"





@implementation ColorController

- (id)init{
//  active = NO;
  color = NULL;
  return [super init];
}

- (void)dealloc{
  delete color;
  NA_COCOA_SUPER_DEALLOC();
}

- (NSView*) colordisplay{return colordisplay;}
- (Color*&) color{return color;}
- (Color*) getColor{return color;}
- (BOOL)isActive{return active;}
- (BOOL)isOpaque{return NO;}

- (void)drawRect:(NSRect)dirtyRect{
  if(active){
    [[NSColor colorWithCalibratedWhite:.25f alpha:1.f] setFill];
    NSBezierPath *fillpath = [NSBezierPath bezierPathWithRect:[self bounds]];
    [fillpath fill];

    NSGraphicsContext *context = [NSGraphicsContext currentContext];
    [context saveGraphicsState];

    [context setCompositingOperation:NSCompositePlusDarker];

    NSBezierPath *path = [NSBezierPath bezierPathWithRect:[self bounds]];
    [path setLineWidth:1.5f];

    [[NSColor whiteColor] setStroke];

    NSShadow * shadow = NA_COCOA_AUTORELEASE([[NSShadow alloc] init]);
    [shadow setShadowColor:[NSColor colorWithCalibratedWhite:0.0f alpha:.45f]];
    [shadow setShadowBlurRadius:1.5f];
    [shadow set];

    [path stroke];

    [context restoreGraphicsState];
  }
  
  [super drawRect:dirtyRect];
  
}

- (void)setActive:(BOOL)newactive{
  BOOL needsredisplay = NO;
  if(active != newactive){needsredisplay = YES;}
  active = newactive;
  [self setNeedsDisplay:needsredisplay];
}

- (void)mouseDown:(NSEvent *)theEvent{
  [(ColorMachineApplication*)NSApp setWorkingColorController:self];
  [[self window] makeFirstResponder:firsttextfield];
}

@end




@implementation InputTextField

- (BOOL)becomeFirstResponder{
  [(ColorMachineApplication*)NSApp setWorkingColorController:colorcontroller];  
  return [super becomeFirstResponder];
}

@end


