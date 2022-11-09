
#import "ColorMachineOpenGLView.h"
#import "MachineWindowController.h"
#import "ColorMachineApplication.h"
#import "ColorController.h"
#import "mainC.h"


//Byte pointimage[7*7*4] = { 0,0,0,0, 0,0,0,115, 0,0,0,197, 0,0,0,247, 0,0,0,197, 0,0,0,115, 0,0,0,0,
//                          0,0,0,115, 73,73,73,251, 176,176,176,255, 243,243,243,255, 176,176,176,255, 73,73,73,251, 0,0,0,115,
//                          0,0,0,197, 176,176,176,255, 255,255,255,160, 255,255,255,41, 255,255,255,160, 176,176,176,255, 0,0,0,197,
//                          0,0,0,247, 243,243,243,255, 255,255,255,41, 0,0,0,0, 255,255,255,41, 243,243,243,255, 0,0,0,247,
//                          0,0,0,197, 176,176,176,255, 255,255,255,160, 255,255,255,41, 255,255,255,160, 176,176,176,255, 0,0,0,197,
//                          0,0,0,115, 73,73,73,251, 176,176,176,255, 243,243,243,255, 176,176,176,255, 73,73,73,251, 0,0,0,115,
//                          0,0,0,0, 0,0,0,115, 0,0,0,197, 0,0,0,247, 0,0,0,197, 0,0,0,115, 0,0,0,0};





@implementation ColorMachineOpenGLView

- (void)awakeFromNib{
  width = 0;
  height = 0;
  [super awakeFromNib];
}

- (id)initWithFrame:(NSRect)frameRect {
  NSOpenGLPixelFormatAttribute attr[] = {
		NSOpenGLPFADoubleBuffer,
		NSOpenGLPFAColorSize, 32,
		NSOpenGLPFADepthSize, 16,
    NSOpenGLPFAAllowOfflineRenderers, // lets OpenGL know this context is offline renderer aware
		0 };
	NSOpenGLPixelFormat *pixelformat = NA_COCOA_AUTORELEASE([[NSOpenGLPixelFormat alloc] initWithAttributes:attr]);
  self = [super initWithFrame:frameRect pixelFormat:pixelformat];
//  if([self respondsToSelector:@selector(setWantsBestResolutionOpenGLSurface:)]){
//    #if defined __MAC_10_7 || defined __MAC_10_8
//      [self setWantsBestResolutionOpenGLSurface:YES];
//    #endif
//  }
  [[self openGLContext] makeCurrentContext];
  return self;
}

- (void)prepareOpenGL{
  [super prepareOpenGL];
  GLint swapInt = 1;
  [[self openGLContext] setValues:&swapInt forParameter:NSOpenGLCPSwapInterval];
  glEnable(GL_BLEND);
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
  glEnable(GL_LINE_SMOOTH);
  
  glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

- (void)reshape{
  [super reshape];
  [[self openGLContext] update];
  float scalefactor = (float)[ColorMachineApplication getUIScaleFactorForWindow:[self window]];
  width = (uint32)ceil([self bounds].size.width * scalefactor);
  height = (uint32)ceil([self bounds].size.height * scalefactor);
  glViewport(0, 0, width, height);
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  glOrtho(0, width, 0, height, -1, 1);
}

- (void)mouseDown:(NSEvent*)event{
  [[self superview] mouseDown:event];
  [self mouseDragged:event];
}

- (void)mouseDragged:(NSEvent*)event{
  NSPoint eventLocation = [event locationInWindow];
  NSPoint pos = [self convertPoint:eventLocation fromView:nil];
  float scalefactor = (float)[ColorMachineApplication getUIScaleFactorForWindow:[self window]];
  mousex = (float)pos.x * scalefactor / width;
  mousey = (float)pos.y * scalefactor / height;
}

- (BOOL)isOpaque{
  return YES;
}

@end














@implementation ColorWell

- (id)init{
  colordata = NULL;
//  rgb8Bitdata = NULL;
  return [super init];
  colorBuffer = NULL;
  normedbuffer = NULL;
}

- (void)dealloc{
  delete [] colordata;
//  delete [] rgb8Bitdata;
  delete [] colorBuffer;
  delete [] normedbuffer;
  NA_COCOA_SUPER_DEALLOC();
}

- (void)initWithController:(ColorController*)newcontroller
                 colorType:(CMLColorType)newcolortype
      normedinputconverter:(CMLNormedConverter)newnormedinputconverter
     normedoutputconverter:(CMLNormedConverter)newnormedoutputconverter
                  channelx:(size_t)newchannelx
                  channely:(size_t)newchannely
              drawspectrum:(BOOL)newdrawspectrum{

  colorcontroller = newcontroller;
  colorType = newcolortype;
  normedinputconverter = newnormedinputconverter;
  normedoutputconverter = newnormedoutputconverter;
  channelx = newchannelx;
  channely = newchannely;
  drawspectrum = newdrawspectrum;

  float scalefactor = (float)[ColorMachineApplication getUIScaleFactorForWindow:[self window]];
  width = (size_t)round([self bounds].size.width * scalefactor);
  height = (size_t)round([self bounds].size.height * scalefactor);
  size_t channelcount = cmlGetNumChannels(colorType);
  delete colordata;
  colordata = new float[width * height * channelcount];
//  delete rgb8Bitdata;
//  rgb8Bitdata = new Byte[width * height * 3];

  float* cptr;

  for(size_t c=0; c<channelcount; c++){
    if(channelx == c){
      cptr = &(colordata[c]);
      for(size_t y=0; y<height; y++){
        for(size_t x=0; x<width; x++){
          float curval = ((float)x)/(width-1);
          *cptr = curval;
          cptr += channelcount;
        }
      }
    }
    if(channely == c){
      cptr = &(colordata[c]);
      for(size_t y=0; y<height; y++){
        float curval = ((height-1)-(float)y)/(height-1);
        for(size_t x=0; x<width; x++){
          *cptr = curval;
          cptr += channelcount;
        }
      }
    }
  }

  delete colorBuffer;
  colorBuffer = new float[channelcount];
  delete normedbuffer;
  normedbuffer = new float[channelcount];
}

- (void)drawRect:(NSRect)rect{
  size_t channelcount = cmlGetNumChannels(colorType);
//  if(channelcount == 1){
//    int t = 1234;
//  }
  CMLColorMachine* cm = [(ColorMachineApplication*)NSApp getCurrentMachine];


  Color* controllercolor = [colorcontroller getColor];
  controllercolor->toBuffer(colorBuffer, colorType);
  normedoutputconverter(normedbuffer, colorBuffer, 1);
  
  float* cptr;

  for(size_t c=0; c<channelcount; c++){
    if((channelx != c) && (channely != c)){
      cptr = &(colordata[c]);
      for(size_t i=0; i<(width*height); ++i){
        *cptr = normedbuffer[c];
        cptr += channelcount;
      }
    }
  }
  
  bool singleline = (channely == (size_t)-1);
  
  float* normedrgbdata = new float[width * height * 3];
  fillRGBFloatArrayWithArray(
    [(ColorMachineApplication*)NSApp getCurrentMachine],
    [(ColorMachineApplication*)NSApp getCurrentScreenMachine],
    normedrgbdata,
    colordata,
    colorType,
    normedinputconverter,
    width * height,
    !singleline,
    NA_TRUE);

//  float* normedrgbdata = new float[width * height * 3];
//  [(ColorMachineApplication*)NSApp fillRGBuint8array:rgb8Bitdata
//                                         fromArray:colordata
//                                     withColorType:colorType
//                              normedInputConverter:normedinputconverter
//                                             count:width * height
//                                          drawgrid:!singleline
//                                          drawmask:YES];
//
//  cmlData8ToRGB(cm, normedrgbdata, rgb8Bitdata, width * height);

//  CGContextRef context = (CGContextRef)[[NSGraphicsContext currentContext] graphicsPort];
//  NSBitmapImageRep* imgrep = [[NSBitmapImageRep alloc]
//    initWithBitmapDataPlanes:(unsigned char**)&normedrgbdata
//    pixelsWide:width
//    pixelsHigh:height
//    bitsPerSample:32
//    samplesPerPixel:3
//    hasAlpha:NO
//    isPlanar:NO
//    colorSpaceName:NSDeviceRGBColorSpace
//    bitmapFormat:NSFloatingPointSamplesBitmapFormat
//    bytesPerRow:width*3*sizeof(float)
//    bitsPerPixel:96];
//  CGImage* cgimage = [imgrep CGImage];
//  NA_COCOA_RELEASE(imgrep);
//
//  CGContextDrawImage(context, NSRectToCGRect([self bounds]), cgimage);

  Byte* rgb8Bitdata = new Byte[width * height * 3];
  cmlSetIntegerMappingType(cm, CML_INTEGER_MAPPING_FLOOR);
  cmlRGBToData8(cm, rgb8Bitdata, normedrgbdata, width * height);
  CGContextRef context = (CGContextRef)[[NSGraphicsContext currentContext] graphicsPort];
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


  delete [] normedrgbdata;

  if(!singleline && ((colorType == CML_COLOR_Yxy) || (colorType == CML_COLOR_Yupvp))){
//  if(spectralcurve3d){
    float imin = CML_DEFAULT_INTEGRATION_MIN;
    float imax = CML_DEFAULT_INTEGRATION_MAX;
    int32 intervals = (int32)((imax - imin) / CML_DEFAULT_INTEGRATION_STEPSIZE) + 1;
    
    CMLColorConverter coordConverter = cmlGetColorConverter(colorType, CML_COLOR_XYZ);
    CMLNormedConverter normedConverter = cmlGetNormedOutputConverter(colorType);

    bool firstPointFound = false;
    CMLVec3 prevCoords;
    for(int32 iStep = 0; iStep <= intervals; iStep++){
      float l = imin + (((imax - imin) * iStep) / intervals);
      CMLVec3 curXYZ;
      cmlGetSpectralXYZColor(cm, curXYZ, l);
      if(curXYZ[1] > 0.f){

        CMLVec3 curRGB;
        CMLVec3 curcoords;
        CMLVec3 curNormedCoords;
        coordConverter(cm, curcoords, curXYZ, 1);
        normedConverter(curNormedCoords, curcoords, 1);
        cmlXYZToRGB(cm, curRGB, curXYZ, 1);
        cmlMul3(curRGB, .7f);
        cmlClampRGB(curRGB, 1);
//        curRGB *= .7f;
//        glColor3fv(curRGB);
        if(!firstPointFound){
          cmlCpy3(prevCoords, curNormedCoords);
          firstPointFound = true;
        }else{
          CGContextBeginPath(context);
          CGContextMoveToPoint(context, prevCoords[1] * width, prevCoords[2] * height);
          CGContextAddLineToPoint(context, curNormedCoords[1] * width, curNormedCoords[2] * height);
          CGColorRef cgcolor = CGColorCreateGenericRGB(curRGB[0], curRGB[1], curRGB[2], .75f);
          CGContextSetStrokeColorWithColor(context, cgcolor);
          CGContextStrokePath(context);
          CGColorRelease(cgcolor);
        }
        cmlCpy3(prevCoords, curNormedCoords);
//        glVertex3fv(curNormedCoords);
      }
    }

//  }
  }


  // /////////////////////
  // Draw the dot
  // /////////////////////
  
  CGRect dotrect;
  dotrect.size.width = 7.f;
  dotrect.size.height = 7.f;
  dotrect.origin.x = normedbuffer[channelx] * (float)width - 3.5f;
  if(singleline){
    dotrect.origin.y = .5f * (float)height - 3.5f;
  }else{
    dotrect.origin.y = normedbuffer[channely] * (float)height - 3.5f;
  }
//  dotrect.origin.x = roundf(normedbuffer[channelx] * (float)width - 3.5f);
//  if(singleline){
//    dotrect.origin.y = roundf(.5f * (float)height - 3.5f);
//  }else{
//    dotrect.origin.y = roundf(normedbuffer[channely] * (float)height - 3.5f);
//  }


//  Byte* dotpointer = pointimage;
//  NSBitmapImageRep* dotimgrep = [[NSBitmapImageRep alloc]
//    initWithBitmapDataPlanes:&dotpointer
//    pixelsWide:7
//    pixelsHigh:7
//    bitsPerSample:8
//    samplesPerPixel:4
//    hasAlpha:YES
//    isPlanar:NO
//    colorSpaceName:NSDeviceRGBColorSpace
//    bitmapFormat:0
//    bytesPerRow:7*4
//    bitsPerPixel:32];
//  CGImage* cgdotimage = [dotimgrep CGImage];
//  NA_COCOA_RELEASE(dotimgrep);
//  
//  CGContextDrawImage(context, dotrect, cgdotimage);



  NSBezierPath *path;
  
  path = [NSBezierPath bezierPathWithOvalInRect:dotrect];
  [path setLineWidth:1.f];
  [[NSColor blackColor] setStroke];
  [path stroke];
  
  dotrect.origin.x += 1.;
  dotrect.origin.y += 1.;
  dotrect.size.width -= 2.;
  dotrect.size.height -= 2.;

  path = [NSBezierPath bezierPathWithOvalInRect:dotrect];
  [path setLineWidth:1.f];
  [[NSColor whiteColor] setStroke];
  [path stroke];

}

- (void)mouseDown:(NSEvent*)event{
  [[self superview] mouseDown:event];
  [self mouseDragged:event];
}

- (void)mouseDragged:(NSEvent*)event{
  NSPoint eventLocation = [event locationInWindow];
  NSPoint pos = [self convertPoint:eventLocation fromView:nil];
  float mousex = (float)pos.x / width;
  float mousey = (float)pos.y / height;
  if(mousex < 0.f){mousex = 0.f;}
  if(mousex > 1.f){mousex = 1.f;}
  if(mousey < 0.f){mousey = 0.f;}
  if(mousey > 1.f){mousey = 1.f;}

  Color* controllercolor = [colorcontroller getColor];

  controllercolor->toBuffer(colorBuffer, colorType);
  normedoutputconverter(normedbuffer, colorBuffer, 1);
  normedbuffer[channelx] = mousex;
  if(channely != (size_t)-1){normedbuffer[channely] = mousey;}
  normedinputconverter(colorBuffer, normedbuffer, 1);
   
  controllercolor->fromBuffer(colorBuffer, colorType);
  controllercolor->clamp();

  CMLColorMachine* cm = [(ColorMachineApplication*)NSApp getCurrentMachine];
  if(colorType == CML_COLOR_XYZ){
    if(cmlGetColorimetricBase(cm) == 0.f)
      cmlDiv3(colorBuffer, cmlGetRadiometricScale(cm));
    else
      cmlMul3(colorBuffer, cmlGetColorimetricBase(cm));
  }

  [(ColorMachineApplication*)NSApp colorHasChanged];
}


- (BOOL)isOpaque{
  return YES;
}


@end

