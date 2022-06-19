
#import "ScreenResolutionWindowController.h"



@implementation RulerView

- (void)drawRect:(NSRect)rect{

  NSDictionary* desc = [[self window] deviceDescription];
  NSSize scres = [[desc objectForKey:NSDeviceResolution] sizeValue];

  CGFloat hpixels = (CGFloat)(controller->hppi * (72.f / scres.width));
  CGFloat vpixels = (CGFloat)(controller->vppi * (72.f / scres.height));
  
  if(controller->showcm){
    hpixels /= 2.54f;
    vpixels /= 2.54f;
  }

  CGFloat width = [self frame].size.width;
  CGFloat height = [self frame].size.height;

  int hmax = (int)ceil((width / 2.) / hpixels);
  int vmax = (int)ceil((height / 2.) / vpixels);

  CGContextRef context = (CGContextRef)[[NSGraphicsContext currentContext] graphicsPort];
  CGContextSaveGState(context);
  
  CGContextSetLineWidth(context, 72.f / scres.height);
  for(int i=-hmax; i <= hmax; i++){
    if(i==0){
      CGContextSetRGBStrokeColor(context, .7f, .0f, 0.f, 1.f);
    }else if(!((int)i%10)){
      CGContextSetRGBStrokeColor(context, .2f, 0.f, 0.f, 1.f);
    }else if(!((int)i%5)){
      CGContextSetRGBStrokeColor(context, 0.f, 0.f, 0.f, .5f);
    }else{
      CGContextSetRGBStrokeColor(context, 0.f, 0.f, 0.f, .25f);
    }
    CGContextMoveToPoint(context, width / 2.f + i * hpixels, 0.f);
    CGContextAddLineToPoint(context, width / 2.f + i * hpixels, height);
    CGContextStrokePath(context);
  }
  CGContextSetLineWidth(context, 72.f / scres.width);
  for(int i=-vmax; i <= vmax; i++){
    if(i==0){
      CGContextSetRGBStrokeColor(context, .7f, .0f, 0.f, 1.f);
    }else if(!((int)i%10)){
      CGContextSetRGBStrokeColor(context, .2f, 0.f, 0.f, 1.f);
    }else if(!((int)i%5)){
      CGContextSetRGBStrokeColor(context, 0.f, 0.f, 0.f, .5f);
    }else{
      CGContextSetRGBStrokeColor(context, 0.f, 0.f, 0.f, .25f);
    }
    CGContextMoveToPoint(context, 0.f, height / 2.f + i * vpixels);
    CGContextAddLineToPoint(context, width, height / 2.f + i * vpixels);
    CGContextStrokePath(context);
  }
  int cmax = (int)sqrt(hmax * hmax + vmax * vmax);
  for(int i=0; i <= cmax; i++){
    if(i==0){
      CGContextSetRGBStrokeColor(context, .7f, .0f, 0.f, .4f);
    }else if(!((int)i%10)){
      CGContextSetRGBStrokeColor(context, .2f, 0.f, 0.f, .4f);
    }else if(!((int)i%5)){
      CGContextSetRGBStrokeColor(context, 0.f, 0.f, 0.f, .2f);
    }else{
      CGContextSetRGBStrokeColor(context, 0.f, 0.f, 0.f, .1f);
    }
    CGRect ellrect = {{width / 2.f - i * hpixels, height / 2.f - i * vpixels}, {2*i*hpixels, 2*i*vpixels}};
    CGContextAddEllipseInRect(context, ellrect);
    CGContextStrokePath(context);
  }
  
  CGContextRestoreGState(context);
}

- (void)mouseDown:(NSEvent*)event{
  NSPoint eventLocation = [event locationInWindow];
  NSPoint pos = [self convertPoint:eventLocation fromView:nil];
  CGFloat dx = pos.x - ([(NSView*)[[self window] contentView] frame].size.width / 2.f);
  CGFloat dy = pos.y - ([(NSView*)[[self window] contentView] frame].size.height / 2.f);
  prevmousedist = sqrt(dx * dx + dy * dy);
}

- (void)rightMouseDown:(NSEvent*)event{
  NSPoint eventLocation = [event locationInWindow];
  NSPoint pos = [self convertPoint:eventLocation fromView:nil];
  CGFloat dy = pos.y - ([(NSView*)[[self window] contentView] frame].size.height / 2.f);
  prevmousedist = fabs(dy);
}

- (void)mouseDragged:(NSEvent*)event{
  NSPoint eventLocation = [event locationInWindow];
  NSPoint pos = [self convertPoint:eventLocation fromView:nil];
  CGFloat dx = pos.x - ([(NSView*)[[self window] contentView] frame].size.width / 2.f);
  CGFloat dy = pos.y - ([(NSView*)[[self window] contentView] frame].size.height / 2.f);
  CGFloat curmousedist = (CGFloat)sqrt(dx * dx + dy * dy);
  controller->hppi *= (curmousedist / prevmousedist);
  controller->vppi *= (curmousedist / prevmousedist);
  if((controller->hppi >= 36) && (controller->hppi <= 300) && (controller->vppi >= 36) && (controller->vppi <= 300)){
    prevmousedist = curmousedist;
  }
  [controller update];
}

- (void)rightMouseDragged:(NSEvent*)event{
  NSPoint eventLocation = [event locationInWindow];
  NSPoint pos = [self convertPoint:eventLocation fromView:nil];
  CGFloat dy = pos.y - ([(NSView*)[[self window] contentView] frame].size.height / 2.f);
  CGFloat curmousedist = (CGFloat)fabs(dy);
  controller->vppi *= (curmousedist / prevmousedist);
  if((controller->hppi >= 36) && (controller->hppi <= 300) && (controller->vppi >= 36) && (controller->vppi <= 300)){
    prevmousedist = curmousedist;
  }
  [controller update];
}

- (void)setController:(ScreenResolutionWindowController*)newcontroller{
  controller = newcontroller;
}

@end






@implementation ScreenResolutionWindowController

-(id)init{
  showcm = true;
  fullscreen = false;
  return [super init];
}

- (void)awakeFromNib{
  NSDictionary* desc = [[[self window] screen] deviceDescription];
  CGDirectDisplayID displayid = [[desc objectForKey:@"NSScreenNumber"] unsignedIntValue];
  CGSize mmsize = CGDisplayScreenSize(displayid);
  NSRect screenrect = [[[self window] screen] frame];
  hppi = (screenrect.size.width / mmsize.width) * 25.4;
  vppi = (screenrect.size.height / mmsize.height) * 25.4;

  [[[self window] contentView] setController:self];
  [self update];
}

- (IBAction)cminchchange:(NSButton*)sender{
  if(sender == radiocm){
    if([radiocm state] == NSOnState){showcm = true;}else{showcm = false;}
  }else{
    if([radioinch state] == NSOnState){showcm = false;}else{showcm = true;}
  }
  [self update];
}

- (IBAction)ppichange:(NSTextField*)sender{
  if(sender == textH){
    hppi = [sender floatValue];
  }else{
    vppi = [sender floatValue];
  }
  [self update];
}

- (void)update{

  if(hppi > 300.){hppi = 300.;}
  if(vppi > 300.){vppi = 300.;}
  if(hppi < 36.){hppi = 36.;}
  if(vppi < 36.){vppi = 36.;}

  NSRect screenrect = [[[self window] screen] frame];
  CGFloat screenh = screenrect.size.width;
  CGFloat screenv = screenrect.size.height;
  [textpixels setStringValue:[NSString stringWithFormat:@"%d x %d", (int)screenh, (int)screenv]];
  CGFloat ratio = (screenh / screenv);
  if((ratio > (16.f / 9.f) - .01) && (ratio < (16.f / 9.f) + .01)){
    [textratio setStringValue:[NSString stringWithFormat:@"16:9"]];
  }else if((ratio > (16.f / 10.f) - .01) && (ratio < (16.f / 10.f) + .01)){
    [textratio setStringValue:[NSString stringWithFormat:@"16:10"]];
  }else if((ratio > (4.f / 3.f) - .01) && (ratio < (4.f / 3.f) + .01)){
    [textratio setStringValue:[NSString stringWithFormat:@"4:3"]];
  }else if((ratio > (3.f / 2.f) - .01) && (ratio < (3.f / 2.f) + .01)){
    [textratio setStringValue:[NSString stringWithFormat:@"3:2"]];
  }else{
    [textratio setStringValue:[NSString stringWithFormat:@"No standard ratio"]];
  }
  CGFloat screenhinch = (CGFloat)(screenh / hppi);
  [texthsize setStringValue:[NSString stringWithFormat:@"%.01f Inch / %.01f cm", screenhinch, screenhinch * 2.54]];
  CGFloat screenvinch = (CGFloat)(screenv / vppi);
  [textvsize setStringValue:[NSString stringWithFormat:@"%.01f Inch / %.01f cm", screenvinch, screenvinch * 2.54]];
  CGFloat screendinch = (CGFloat)sqrt(screenhinch * screenhinch + screenvinch * screenvinch);
  [textdsize setStringValue:[NSString stringWithFormat:@"%.01f Inch / %.01f cm", screendinch, screendinch * 2.54]];

  if(showcm){
    [radiocm setState:NSOnState];
    [radioinch setState:NSOffState];
  }else{
    [radiocm setState:NSOffState];
    [radioinch setState:NSOnState];
  }

  [textH setStringValue:[NSString stringWithFormat:@"%.01f", hppi]];
  [textV setStringValue:[NSString stringWithFormat:@"%.01f", vppi]];

  if(fullscreen){
    [fullscreenbutton setTitle:@"Exit Fullscreen"];
  }else{
    [fullscreenbutton setTitle:@"Fullscreen"];
  }

//  [[self window] display];
//  [[self window] setViewsNeedDisplay:YES];
  [[[self window] contentView] setNeedsDisplay:YES];
}

- (void)showDialog{
  [[self window] makeKeyAndOrderFront:self];
}

- (IBAction)switchFullscreen:(NSButton*)sender{
  fullscreen = !fullscreen;
  if(fullscreen){
  }
  [self update];
}

@end


