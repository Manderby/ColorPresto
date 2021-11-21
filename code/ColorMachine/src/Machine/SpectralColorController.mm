
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

  CMLuint32 width = (CMLuint32)[self bounds].size.width;
  CMLuint32 height = (CMLuint32)[self bounds].size.height;

  CGColorRef cgcolor;
  
  const float viewrange = .8f;
  const float viewoffset = .05f;
  
  // Draw the background;
  Byte* rgb8bitdata = new Byte[width * height * 3];
  for(CMLuint32 x=0; x<width; x++){
    float lambda = imin + ((float)x / width) * (imax - imin);
    CMLVec3 xyz;
    CMLgetSpectralXYZColor(sm, xyz, lambda);
    CMLVec3 rgb;
    CMLXYZtoRGB(sm, rgb, xyz, 1);
    CMLclampRGB(rgb, 1);
    cmlMul3(rgb, .4f);
    CMLRGBto8bitOutput(sm, &(rgb8bitdata[x*3]), rgb, 1);
  }
  for(CMLuint32 y=1; y<height; y++){
    memcpy(&(rgb8bitdata[y * width * 3]), rgb8bitdata, width*3);
  }
  
  NSBitmapImageRep* imgrep = [[NSBitmapImageRep alloc]
    initWithBitmapDataPlanes:&rgb8bitdata
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
  [imgrep release];
  
  CGContextDrawImage(context, NSRectToCGRect([self bounds]), cgimage);
  delete [] rgb8bitdata;


  // Draw the Grid

  int lineoffset = (int)roundf((imin) / 10.f);
  float linecount = (imax - imin) / 10.f;

  for(int i = 0; i <= (int)linecount; i++){
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
  const CMLFunction* specdistfuncs[3];
  CMLgetSpecDistFunctions(cm, specdistfuncs);

  CGColorRef Rlinecolor = CGColorCreateGenericRGB(1.f, .5f, .5f, 1.f);
  SpectralColor Rcolor(CMLduplicateFunction(specdistfuncs[0]), true);
  [(ColorMachineApplication*)NSApp drawColor:&Rcolor fillBack:NO linecolor:Rlinecolor context:context inRect:NSRectToCGRect([self bounds])];
  CGColorRelease(Rlinecolor);

  CGColorRef Glinecolor = CGColorCreateGenericRGB(.5f, 1.f, .5f, 1.f);
  SpectralColor Gcolor(CMLduplicateFunction(specdistfuncs[1]), true);
  [(ColorMachineApplication*)NSApp drawColor:&Gcolor fillBack:NO linecolor:Glinecolor context:context inRect:NSRectToCGRect([self bounds])];
  CGColorRelease(Glinecolor);

  CGColorRef Blinecolor = CGColorCreateGenericRGB(.5f, .5f, 1.f, 1.f);
  SpectralColor Bcolor(CMLduplicateFunction(specdistfuncs[2]), true);
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
//  [currentText release];
//
//  [parastyle setAlignment:NSRightTextAlignment];
//  NSDictionary *attributes2 = [NSDictionary dictionaryWithObjectsAndKeys:
//    [NSFont fontWithName:@"Lucida Grande" size:8.], NSFontAttributeName,
//    textColor, NSForegroundColorAttributeName,
//    parastyle, NSParagraphStyleAttributeName, nil];
//  currentText = [[NSAttributedString alloc] initWithString:[NSString stringWithFormat:@"%d", (int)CML_DEFAULT_INTEGRATION_MAX] attributes: attributes2];
//  [currentText drawInRect:[self bounds]];
//  [currentText release];
//  
//  [parastyle release];


  // Draw the illumination
  CGColorRef lightlinecolor = CGColorCreateGenericRGB(1.f, 1.f, 1.f, 1.f);
  const CMLFunction* lightspectrum = CMLgetIlluminationSpectrum(cm);
  if(lightspectrum){
    SpectralColor lightcolor(CMLduplicateFunction(lightspectrum), false);
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

  CMLVec3 whitepointYxy;
  CMLgetWhitePointYxy(cm, whitepointYxy);
  CMLFunction* dirac = CMLcreateDiracFilter(lambda);
  CMLFunction* illumdirac = CMLcreateFunctionMulScalar(dirac, cmlInverse(cmlGetObserverRadiometricScale(cmlGetObserver(cm))));
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
