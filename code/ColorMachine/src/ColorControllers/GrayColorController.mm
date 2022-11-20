
#import "GrayColorController.h"
#import "MachineWindowController.h"
#import "ColorMachineApplication.h"
#include "NAUICocoaLegacy.h"



@implementation GrayDisplay

-(void) drawRect: (NSRect) rect{
  CGContextRef context = (CGContextRef)[[NSGraphicsContext currentContext] graphicsPort];

  CMLVec3 grayout;
  CMLVec3 rgbout;
  [(ColorMachineApplication*)NSApp fillRGBfloatarray:grayout fromColor:(GrayColor*)[colorcontroller color]];
  [(ColorMachineApplication*)NSApp fillRGBfloatarray:rgbout fromColor:[(ColorMachineApplication*)NSApp getCurrentColor]];
  CGFloat graycomponents[4];
  CGFloat rgbcomponents[4];
  graycomponents[0] = grayout[0];
  graycomponents[1] = grayout[1];
  graycomponents[2] = grayout[2];
  graycomponents[3] = 1.;
  rgbcomponents[0] = rgbout[0];
  rgbcomponents[1] = rgbout[1];
  rgbcomponents[2] = rgbout[2];
  rgbcomponents[3] = 1.;
  CGColorSpaceRef colorspace = CGColorSpaceCreateDeviceRGB();

  CGRect colorrect = NSRectToCGRect([self bounds]);
  colorrect.size.width = colorrect.size.width / 2.f;
  
  NSShadow* shadow = [[NSShadow alloc] init];
  [shadow setShadowBlurRadius:1.f];
  [shadow setShadowOffset:NSMakeSize(1.f, -1.f)];
  [shadow setShadowColor:[NSColor blackColor]];
  
  NSMutableParagraphStyle* parastyle = [[NSMutableParagraphStyle alloc] init];
  [parastyle setAlignment:NATextAlignmentCenter];
  
  NSDictionary *attributes = [NSDictionary dictionaryWithObjectsAndKeys:
    [NSFont fontWithName:@"Lucida Grande" size:8], NSFontAttributeName,
    [NSColor whiteColor], NSForegroundColorAttributeName,
    parastyle, NSParagraphStyleAttributeName,
    shadow, NSShadowAttributeName, nil];
  
  NSAttributedString * currentText;
  
  CGColorRef rgbColor = CGColorCreate(colorspace, rgbcomponents);
  CGContextSetFillColorWithColor(context, rgbColor);
  CGContextFillRect(context, colorrect);
  CGColorRelease(rgbColor);
  
  currentText = [[NSAttributedString alloc] initWithString:@"Color" attributes: attributes];
  [currentText drawInRect:NSRectFromCGRect(colorrect)];
  NA_COCOA_RELEASE(currentText);

  colorrect.origin.x += colorrect.size.width;

  CGColorRef grayColor = CGColorCreate(colorspace, graycomponents);
  CGContextSetFillColorWithColor(context, grayColor);
  CGContextFillRect(context, colorrect);
  CGColorRelease(grayColor);
  
  currentText = [[NSAttributedString alloc] initWithString:@"Gray" attributes: attributes];
  [currentText drawInRect:NSRectFromCGRect(colorrect)];
  NA_COCOA_RELEASE(currentText);

  NA_COCOA_RELEASE(shadow);
  NA_COCOA_RELEASE(parastyle);
  
  CGColorSpaceRelease(colorspace);


}

@end



@implementation GrayColorController

- (void)awakeFromNib{
  [textFieldGray setNextKeyView:textFieldGray];
  [self color] = new GrayColor(.5f);
  [sliderGray initWithController:self
                    colorType:CML_COLOR_Gray
         normedinputconverter:cmlGetNormedInputConverter(CML_COLOR_Gray)
        normedoutputconverter:cmlGetNormedOutputConverter(CML_COLOR_Gray)
                     channelx:0
                     channely:(size_t)-1
                 drawspectrum:NO];
}

- (IBAction)valueChangeGray:(NSControl*)sender {
  float value = [sender floatValue];
  (*[self color])[0] = value;
  [(ColorMachineApplication*)NSApp colorHasChanged];
}

- (void)update{
  GrayColor& gray = *(GrayColor*)[self color];
  gray = [(ColorMachineApplication*)NSApp getCurrentColor]->toGray();
  [textFieldGray setStringValue:[NSString stringWithFormat:@"%1.04f", gray[0]]];
//  [self setNeedsDisplay:YES];
  [colordisplay setNeedsDisplay:YES];
  [sliderGray setNeedsDisplay:YES];
}

- (void)setActive:(BOOL)newactive{
  if(newactive){
    [labelGray setTextColor:[NSColor whiteColor]];
  }else{
    [labelGray setTextColor:[NSColor blackColor]];
  }
  [super setActive:newactive];
}

@end
