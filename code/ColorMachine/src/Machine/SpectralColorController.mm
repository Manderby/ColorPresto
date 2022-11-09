
#import "SpectralColorController.h"
#import "MachineWindowController.h"
#import "ColorMachineApplication.h"

@implementation SpectralDisplay

- (void)awakeFromNib{
//  texturecolortype = CML_COLOR_XYZ;
//  singlelinetexture = true;
  [super awakeFromNib];
}

- (void)initWithController:(ColorController*)newcontroller{
  colorcontroller = newcontroller;
}

-(void) drawRect: (NSRect) rect{
  CMLColorMachine* cm = [(ColorMachineApplication*)NSApp getCurrentMachine];
  CMLColorMachine* sm = [(ColorMachineApplication*)NSApp getCurrentScreenMachine];
  CGContextRef context = (CGContextRef)[[NSGraphicsContext currentContext] graphicsPort];

  float imin = CML_DEFAULT_INTEGRATION_MIN;
  float imax = CML_DEFAULT_INTEGRATION_MAX;

  size_t width = (size_t)[self bounds].size.width;
  size_t height = (size_t)[self bounds].size.height;

  CGColorRef cgcolor;
  
  const float viewrange = .8f;
  const float viewoffset = .05f;
  
  // Draw the background;
  Byte* rgb8Bitdata = new Byte[width * height * 3];
  for(size_t x=0; x<width; x++){
    float lambda = imin + ((float)x / width) * (imax - imin);
    CMLVec3 xyz;
    cmlGetSpectralXYZColor(sm, xyz, lambda);
    CMLVec3 rgb;
    cmlXYZToRGB(sm, rgb, xyz, 1);
    cmlClampRGB(rgb, 1);
    cmlMul3(rgb, .4f);
    cmlRGBToData8(sm, &(rgb8Bitdata[x*3]), rgb, 1);
  }
  for(size_t y=1; y<height; y++){
    memcpy(&(rgb8Bitdata[y * width * 3]), rgb8Bitdata, width*3);
  }
  
  NSBitmapImageRep* imgrep = [[NSBitmapImageRep alloc]
    initWithBitmapDataPlanes:&rgb8Bitdata
    pixelsWide:width
    pixelsHigh:height
    bitsPerSample:8
    samplesPerPixel:3
    hasAlpha:NO
    isPlanar:NO
    colorSpaceName:NSDeviceRGBColorSpace
    bitmapFormat:0
    bytesPerRow:width*3
    bitsPerPixel:24];
  CGImage* cgimage = [imgrep CGImage];
  NA_COCOA_RELEASE(imgrep);
  
  CGContextDrawImage(context, NSRectToCGRect([self bounds]), cgimage);
  delete [] rgb8Bitdata;


  // Draw the Grid

  int lineoffset = (int)roundf((imin) / 10.f);
  float linecount = (imax - imin) / 10.f;

  for(int i = 0; i <= (int)linecount; ++i){
    if(!((lineoffset+i)%10)){
      cgcolor = CGColorCreateGenericRGB(1.f, 1.f, 1.f, .45f);
    }else if(!((lineoffset+i)%5)){
      cgcolor = CGColorCreateGenericRGB(1.f, 1.f, 1.f, .175f);
    }else{
      cgcolor = CGColorCreateGenericRGB(1.f, 1.f, 1.f, .075f);
    }
    CGContextSetStrokeColorWithColor(context, cgcolor);
    float l = (i/linecount)*width;
    CGContextBeginPath(context);
    CGContextMoveToPoint(context, l, 0);
    CGContextAddLineToPoint(context, l, height);
    CGContextStrokePath(context);
    CGColorRelease(cgcolor);
  }

  // Draw the bottom and top line
  cgcolor = CGColorCreateGenericRGB(1.f, 1.f, 1.f, .5f);
  CGContextSetStrokeColorWithColor(context, cgcolor);
  CGContextBeginPath(context);
  CGContextMoveToPoint(context, 0, viewoffset * height);
  CGContextAddLineToPoint(context, width, viewoffset * height);
  CGContextStrokePath(context);
  CGContextBeginPath(context);
  CGContextMoveToPoint(context, 0, (viewoffset + viewrange) * height);
  CGContextAddLineToPoint(context, width, (viewoffset + viewrange) * height);
  CGContextStrokePath(context);
  CGColorRelease(cgcolor);
  
  
  // Draw the spectral distribution functions
  const CMLFunction* specdistfuncs[3] = {
    cmlGetSpecDistFunction(cm, 0),
    cmlGetSpecDistFunction(cm, 1),
    cmlGetSpecDistFunction(cm, 2),
  };

  CGColorRef Rlinecolor = CGColorCreateGenericRGB(1.f, .5f, .5f, 1.f);
  SpectralColor Rcolor(cmlDuplicateFunction(specdistfuncs[0]), true);
  [(ColorMachineApplication*)NSApp drawColor:&Rcolor fillBack:NO linecolor:Rlinecolor context:context inRect:NSRectToCGRect([self bounds])];
  CGColorRelease(Rlinecolor);

  CGColorRef Glinecolor = CGColorCreateGenericRGB(.5f, 1.f, .5f, 1.f);
  SpectralColor Gcolor(cmlDuplicateFunction(specdistfuncs[1]), true);
  [(ColorMachineApplication*)NSApp drawColor:&Gcolor fillBack:NO linecolor:Glinecolor context:context inRect:NSRectToCGRect([self bounds])];
  CGColorRelease(Glinecolor);

  CGColorRef Blinecolor = CGColorCreateGenericRGB(.5f, .5f, 1.f, 1.f);
  SpectralColor Bcolor(cmlDuplicateFunction(specdistfuncs[2]), true);
  [(ColorMachineApplication*)NSApp drawColor:&Bcolor fillBack:NO linecolor:Blinecolor context:context inRect:NSRectToCGRect([self bounds])];
  CGColorRelease(Blinecolor);


//  // Draw the min and max labels
//  NSAttributedString * currentText;
//  NSColor* textColor = [NSColor colorWithDeviceRed:1.f green:1.f blue:1.f alpha:.75f];
//  
//  NSMutableParagraphStyle* parastyle = [[NSMutableParagraphStyle alloc] init];
//  [parastyle setAlignment:NSLeftTextAlignment];
//  NSDictionary *attributes1 = [NSDictionary dictionaryWithObjectsAndKeys:
//    [NSFont fontWithName:@"Lucida Grande" size:8], NSFontAttributeName,
//    textColor, NSForegroundColorAttributeName,
//    parastyle, NSParagraphStyleAttributeName, nil];
//  currentText = [[NSAttributedString alloc] initWithString:[NSString stringWithFormat:@"%d", (int)CML_DEFAULT_INTEGRATION_MIN] attributes: attributes1];
//  [currentText drawInRect:[self bounds]];
//  NA_COCOA_RELEASE(currentText);
//
//  [parastyle setAlignment:NSRightTextAlignment];
//  NSDictionary *attributes2 = [NSDictionary dictionaryWithObjectsAndKeys:
//    [NSFont fontWithName:@"Lucida Grande" size:8.], NSFontAttributeName,
//    textColor, NSForegroundColorAttributeName,
//    parastyle, NSParagraphStyleAttributeName, nil];
//  currentText = [[NSAttributedString alloc] initWithString:[NSString stringWithFormat:@"%d", (int)CML_DEFAULT_INTEGRATION_MAX] attributes: attributes2];
//  [currentText drawInRect:[self bounds]];
//  NA_COCOA_RELEASE(currentText);
//  
//  NA_COCOA_RELEASE(parastyle);


  // Draw the illumination
  CGColorRef lightlinecolor = CGColorCreateGenericRGB(1.f, 1.f, 1.f, 1.f);
  const CMLFunction* lightspectrum = cmlGetReferenceIlluminationSpectrum(cm);
  if(lightspectrum){
    SpectralColor lightcolor(cmlDuplicateFunction(lightspectrum), false);
    [(ColorMachineApplication*)NSApp drawColor:&lightcolor fillBack:NO linecolor:lightlinecolor context:context inRect:NSRectToCGRect([self bounds])];
  }
  CGColorRelease(lightlinecolor);


  // Draw the color
  CGColorRef colorlinecolor = CGColorCreateGenericRGB(1.f, 1.f, .5f, 1.f);
  const Color* curcolor = [(ColorMachineApplication*)NSApp getCurrentColor];
  [(ColorMachineApplication*)NSApp drawColor:curcolor fillBack:NO linecolor:colorlinecolor context:context inRect:NSRectToCGRect([self bounds])];
  CGColorRelease(colorlinecolor);

}

- (void)mouseDown:(NSEvent*)event{
  [(ColorMachineApplication*)NSApp setWorkingColorController:colorcontroller];
  [self mouseDragged:event];
}

- (void)mouseDragged:(NSEvent*)event{
  [super mouseDragged:event];
  CMLColorMachine* cm = [(ColorMachineApplication*)NSApp getCurrentMachine];

  NSPoint eventLocation = [event locationInWindow];
  NSPoint pos = [self convertPoint:eventLocation fromView:nil];
  float mousex = (float)pos.x / (float)[self bounds].size.width;
//  float mousey = (float)pos.y / (float)[self bounds].size.height;
  if(mousex < 0.f){mousex = 0.f;}
  if(mousex > 1.f){mousex = 1.f;}
//  if(mousey < 0.f){mousey = 0.f;}
//  if(mousey > 1.f){mousey = 1.f;}

  float minl = CML_DEFAULT_INTEGRATION_MIN;
  float maxl = CML_DEFAULT_INTEGRATION_MAX;
  float lambda = minl + (maxl-minl) * mousex;
//  XYZColor speccolor;

  Color* controllercolor = [colorcontroller getColor];
//  SpectralColor& spectral = *(SpectralColor*)[colorcontroller color];

  CMLFunction* dirac = cmlCreateDiracFilter(lambda);
  CMLFunction* illumdirac = cmlCreateFunctionMulScalar(dirac, cmlInverse(cmlGetRadiometricScale(cm)));
//  spectral.init(&dirac, false);

//  speccolor.fromFloatBuffer(cm->getSpectralXYZColor(lambda));
  ((SpectralColor*)controllercolor)->init(illumdirac, false);
  cmlReleaseFunction(dirac);
  cmlReleaseFunction(illumdirac);
  [(ColorMachineApplication*)NSApp colorHasChanged];
}

@end



@implementation SpectralColorController

- (void)awakeFromNib{
  color = new SpectralColor;
  [(SpectralDisplay*)colordisplay initWithController:self];
}

- (void) update{
  SpectralColor& spec = *(SpectralColor*)[self color];
  spec = [(ColorMachineApplication*)NSApp getCurrentColor]->toSpectral();
  [colordisplay display];
//  [self setNeedsDisplay:YES];
  [colordisplay setNeedsDisplay:YES];
}

- (void)setActive:(BOOL)newactive{
  [super setActive:newactive];
}

@end
