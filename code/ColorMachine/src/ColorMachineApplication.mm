
#import "ThreeDeeWindowController.h"
#import "MetamericsWindowController.h"
#import "ColorMachineApplication.h"
#import "AboutWindowController.h"
#import "MachinesController.h"
#import "ColorsController.h"
#import "GrayColorController.h"
#import "MachineWindowController.h"

#include <NADateTime.h>
#include <NAApp/macOS/UI/NAUICocoaLegacy.h>

CMLColorType maskcolor;
bool showmask;
bool showgrid;
float borderthickness;
CMLSize bordercount;






@implementation ColorMachineApplication

- (void)applicationDidChangeScreenParameters:(NSNotification *)aNotification{
  [machinescontroller recomputeScreenMachines];
  [self updateMachine];
}

- (BOOL)applicationShouldTerminateAfterLastWindowClosed:(NSApplication *)theApplication{
  return YES;
}

- (void)applicationDidFinishLaunching:(NSNotification *)aNotification{  
//  NSNotificationCenter* notcenter = [NSNotificationCenter defaultCenter];

//  [notcenter addObserver:machinewindowcontroller selector:@selector(expandColorSelection:) name:COLOR_MACHINE_EXPAND_COLOR_SELECTION object:nil];
//  [notcenter addObserver:machinewindowcontroller selector:@selector(collapseColorSelection:) name:COLOR_MACHINE_COLLAPSE_COLOR_SELECTION object:nil];

//  [notcenter addObserver:colorscontroller selector:@selector(colorItemHeightHasChanged:) name:COLOR_MACHINE_ITEM_HEIGHT_CHANGED object:nil];
//  [notcenter addObserver:colorscontroller selector:@selector(colorItemHasChanged:) name:COLOR_MACHINE_ITEM_CHANGED object:nil];
//  [notcenter addObserver:colorscontroller selector:@selector(addColorGroup:) name:COLOR_MACHINE_ADD_COLORGROUP object:nil];
//  [notcenter addObserver:colorscontroller selector:@selector(assimilateColor:) name:COLOR_MACHINE_ASSIMILATE_COLOR object:nil];


  GrayColor startingcolor(.5f);
  [self setCurrentColor:&startingcolor];
  [self updateMachine];
  [machinewindowcontroller showWindow:self];
  
  
  
  
  
  
  
//  [colorgroup setTitle:@"Test"];
//  Color* newcolor = new SpectralColor(CMLcreateCIEDIlluminant(5678.f), false);
//  Color* newcolor2 = new SpectralColor(CMLcreateFunctionMulScalar(CMLcreateCIEDIlluminant(7777.f), .01f), true);
//  
//  ColorItemColorGroup* cicg = [[[ColorItemColorGroup alloc] init] autorelease];
//  [cicg setGroup:colorgroup];
//  ColorItem* newitem = [[[ColorItem alloc] initWithCMLColor:newcolor title:nil] autorelease];
//  [newitem setTitle:@"TestSpectrum"];
//  [cicg setItem:newitem];
//
//  ColorItemColorGroup* cicg2 = [[[ColorItemColorGroup alloc] init] autorelease];
//  [cicg2 setGroup:colorgroup];
//  ColorItem* newitem2 = [[[ColorItem alloc] initWithCMLColor:newcolor2 title:nil] autorelease];
//  [newitem2 setTitle:@"TestSpectrum"];
//  [cicg2 setItem:newitem2];
//
//  dispatch_time_t nexttime = dispatch_time(DISPATCH_TIME_NOW, 0);
//  dispatch_queue_t queue = dispatch_get_main_queue();
//  dispatch_after(nexttime, queue, ^{
//    [[(ColorMachineApplication*)NSApp getColorsController] addColorGroup:colorgroup];
//    });
//
//  nexttime = dispatch_time(DISPATCH_TIME_NOW, 1000000000);
//  dispatch_after(nexttime, queue, ^{
//    [[(ColorMachineApplication*)NSApp getColorsController] assimilateColor:cicg];
//    [[(ColorMachineApplication*)NSApp getColorsController] assimilateColor:cicg2];
//    });
}

- (NSApplicationTerminateReply)applicationShouldTerminate:(NSApplication *)sender{
  return NSTerminateNow;
}

- (void)awakeFromNib{
//  [self setDelegate:self];
//  machinescontroller = [[MachinesController alloc] init];
//  colorscontroller = [[ColorsController alloc] init];
}

- (id)init{
  self = [super init];
  [self setDelegate:self];
  machinescontroller = [[MachinesController alloc] init];
  return self;
}

- (IBAction)showAbout:(id)sender{
  if(!aboutwindowcontroller){
    naLoadNib("AboutWindow");
  }
  [aboutwindowcontroller showDialog];
}

- (IBAction)showScreenResolution:(id)sender{
  if(!screenresolutionwindowcontroller){
    naLoadNib("ScreenResolution");
  }
  [screenresolutionwindowcontroller showDialog];
}

- (IBAction)showThreeDee:(id)sender{
  if(!threedeewindowcontroller){
    naLoadNib("ThreeDeeWindow");
  }
  [threedeewindowcontroller showDialog];
}

- (IBAction)showMetamerics:(id)sender{
  if(!metamericswindowcontroller){
    naLoadNib("Metamerics");
  }
  [metamericswindowcontroller showDialog];
}

- (void)setCurrentColor:(const Color*)color{
  [colorscontroller setCurrentColor:color];
}

- (const Color*)getCurrentColor{
  return [colorscontroller currentColor];
}
- (void)colorHasChanged{
  [colorscontroller colorHasChanged];
}

- (void)setWorkingColorController:(ColorController*) workingcolorcontroller{
  [colorscontroller setWorkingColorController:workingcolorcontroller];
}


- (CMLColorMachine*)getCurrentMachine{
  return [machinescontroller currentMachine];
}
- (CMLColorMachine*)getCurrentScreenMachine{
  return [machinescontroller currentScreenMachine];
}
- (MachineWindowController*)getMachineWindowController{
  return machinewindowcontroller;
}
- (ColorsController*)getColorsController{
  return colorscontroller;
}


- (void)updateMachine{
  [machinewindowcontroller updateMachine];
  [threedeewindowcontroller update];
  [colorscontroller updateColor];
  [metamericswindowcontroller update];
}

- (void)updateColor{
  [colorscontroller updateColor];
  [threedeewindowcontroller update];
  [metamericswindowcontroller update];
}

//- (void)colorItemHasChanged:(NSNotification*)notification{
//  [colorscontroller colorItemHasChanged:item];
//}


- (IBAction)resetMachine:(id)sender{
  [machinescontroller resetCurrentMachine];
  [self updateMachine];
}

- (IBAction)setCurrentColorAsWhitepoint:(id)sender{
  float yxybuf[3];
  [colorscontroller currentColor]->toYxyBuffer(yxybuf);
  CMLsetWhitePointYxy([machinescontroller currentMachine], yxybuf);
  [self updateMachine];
}

- (IBAction)setCurrentColorAsRedPrimary:(id)sender{
  CMLColorMachine* cm = [machinescontroller currentMachine];
  CMLVec3 primaries[3];
  CMLgetRGBPrimariesYxy(cm, primaries);
  [colorscontroller currentColor]->toYxyBuffer(primaries[0]);
  CMLsetRGBPrimariesYxy(cm, primaries);
  [self updateMachine];
}
- (IBAction)setCurrentColorAsGreenPrimary:(id)sender{
  CMLColorMachine* cm = [machinescontroller currentMachine];
  CMLVec3 primaries[3];
  CMLgetRGBPrimariesYxy(cm, primaries);
  [colorscontroller currentColor]->toYxyBuffer(primaries[1]);
  CMLsetRGBPrimariesYxy(cm, primaries);
  [self updateMachine];
}
- (IBAction)setCurrentColorAsBluePrimary:(id)sender{
  CMLColorMachine* cm = [machinescontroller currentMachine];
  CMLVec3 primaries[3];
  CMLgetRGBPrimariesYxy(cm, primaries);
  [colorscontroller currentColor]->toYxyBuffer(primaries[2]);
  CMLsetRGBPrimariesYxy(cm, primaries);
  [self updateMachine];
}




//- (void)fillRGBuint8array :(Byte*)texdata
//              fromArray:(float*)inputarray
//          withColorType:(CMLColorType)inputcolortype
//   normedInputConverter:(CMLNormedConverter)normedconverter
//                  count:(CMLuint32)count
//               drawgrid:(BOOL)drawgridlines
//               drawmask:(BOOL)drawmask{

- (void)fillRGBfloatarray :(float*)texdata
              fromArray:(float*)inputarray
          withColorType:(CMLColorType)inputcolortype
   normedInputConverter:(CMLNormedConverter)normedconverter
                  count:(CMLuint32)count
               drawgrid:(BOOL)drawgridlines
               drawmask:(BOOL)drawmask{
  
  CMLuint32 numcolorchannels = CMLgetNumChannels(inputcolortype);
  CMLColorMachine* cm = [(ColorMachineApplication*)NSApp getCurrentMachine];
  CMLColorMachine* sm = [(ColorMachineApplication*)NSApp getCurrentScreenMachine];
  CMLVec3 cmwhitepointYxy;
  CMLVec3 smwhitepointYxy;
  CMLColorConverter colortoXYZ = CMLgetColorConverter(CML_COLOR_XYZ, inputcolortype);
  float* colorbuffer = new float[numcolorchannels * count];
//  float* RGBbuffer = new float[3 * count];
  float* XYZbuffer = new float[3 * count];
  
  CMLgetWhitePointYxy(cm, cmwhitepointYxy);
  cmwhitepointYxy[0] = 1.f;
  CMLgetWhitePointYxy(sm, smwhitepointYxy);
  smwhitepointYxy[0] = 1.f;
  
  normedconverter(colorbuffer, inputarray, count);
  colortoXYZ(cm, XYZbuffer, colorbuffer, count);
  float* aXYZbuffer = new float[3 * count];
  CMLMat33 amatrix;
  cmlComputeChromaticAdaptationMatrix(amatrix, CML_CHROMATIC_ADAPTATION_NONE, smwhitepointYxy, cmwhitepointYxy);
  for(CMLSize i=0; i<count; i++){
    CMLconvertXYZtoChromaticAdaptedXYZ(&(aXYZbuffer[i*3]), &(XYZbuffer[i*3]), amatrix);
  }
  CMLXYZtoRGB(sm, texdata, aXYZbuffer, count);
  delete [] aXYZbuffer;

//  if((showmask && drawmask) || (showgrid && drawgridlines)){
//    CMLuint32 nummaskchannels = CMLgetNumChannels(maskcolor);
//    CMLColorConverter colortomask = CMLgetColorConverter(maskcolor, inputcolortype);
//    CMLNormedConverter masktonormal = CMLgetNormedOutputConverter(maskcolor);
//    float* maskbuffer = new float[count];
//    float* maskcolorarray = new float[nummaskchannels * count];
//    float* normedcolor = new float[nummaskchannels * count];
//    for(CMLuint32 i=0; i<count; i++){maskbuffer[i] = 1.f;}
//    colortomask(cm, maskcolorarray, colorbuffer, count);
//    masktonormal(normedcolor, maskcolorarray, count);
//    if(showmask && drawmask){
//      for(CMLuint32 i=0; i<count * nummaskchannels; i++){
//        if(!CMLInRange(normedcolor[i], 0.f, 1.f)){maskbuffer[i/nummaskchannels] = .2f;}
//      }
//    }
//    if(showgrid && drawgridlines){
//      float sharpness = .01f;
//      float ledge = 1.f / ((float)(bordercount + 1)) * sharpness;
//      float* coordsbuffer = new float[((bordercount + 2) * 4)];
//      float* valsbuffer = new float[((bordercount + 2) * 4)];
//      
//      for(uint32 i=0; i<bordercount + 2; i++){
//        float pos = ((float)i)/((float)(bordercount+1));
//        coordsbuffer[i*4+0] = pos - borderthickness - ledge;
//        coordsbuffer[i*4+1] = pos - borderthickness + ledge;
//        coordsbuffer[i*4+2] = pos + borderthickness - ledge;
//        coordsbuffer[i*4+3] = pos + borderthickness + ledge;
//        valsbuffer[i*4+0] = 1.f;
//        valsbuffer[i*4+1] = .5f;
//        valsbuffer[i*4+2] = .5f;
//        valsbuffer[i*4+3] = 1.f;
//      }
////      CMLArray coords(coordsbuffer, true, (bordercount + 2) * 4);
////      CMLArray vals(valsbuffer, true, (bordercount + 2) * 4);
////      CMLSampleArrayFunction gridlines(coords, vals, CML_INTERPOLATION_LINEAR, CML_EXTRAPOLATION_CLAMP);
////      for(CMLuint32 i=0; i<count * nummaskchannels; i++){
////        maskbuffer[i/nummaskchannels] *= gridlines(normedcolor[i]);
////      }
//    }
//
//    for(CMLuint32 i=0; i<count * 3; i++){
//      RGBbuffer[i] *= maskbuffer[i/3];
//    }
//    delete [] normedcolor;
//    delete [] maskcolorarray;
//    delete [] maskbuffer;
//  }
  CMLclampRGB(texdata, count);
//  CMLclampRGB(RGBbuffer, count);
//  CMLRGBto8bitOutput(sm, texdata, RGBbuffer, count);
  
  delete [] XYZbuffer;
//  delete [] RGBbuffer;
  delete [] colorbuffer;
}


- (void)fillRGBfloatarray:(float*)outdata fromColor:(const Color*)inputcolor{
  
  CMLColorMachine* cm = [(ColorMachineApplication*)NSApp getCurrentMachine];
  CMLColorMachine* sm = [(ColorMachineApplication*)NSApp getCurrentScreenMachine];
  CMLVec3 cmwhitepointYxy;
  CMLVec3 smwhitepointYxy;
  CMLgetWhitePointYxy(cm, cmwhitepointYxy);
  cmwhitepointYxy[0] = 1.f;
  CMLgetWhitePointYxy(sm, smwhitepointYxy);
  smwhitepointYxy[0] = 1.f;

  CMLVec3 XYZbuffer;
  inputcolor->toXYZBuffer(XYZbuffer);
  
  CMLVec3 aXYZbuffer;
  CMLMat33 amatrix;
  cmlComputeChromaticAdaptationMatrix(amatrix, CML_CHROMATIC_ADAPTATION_NONE, smwhitepointYxy, cmwhitepointYxy);
  CMLconvertXYZtoChromaticAdaptedXYZ(aXYZbuffer, XYZbuffer, amatrix);
  CMLXYZtoRGB(sm, outdata, aXYZbuffer, 1);

  CMLclampRGB(outdata, 1);
}

#define VIEWRANGE .8f
#define VIEWOFFSET .05f

- (void)drawColor:(const Color*)color fillBack:(BOOL)fill linecolor:(CGColorRef)linecolor context:(CGContextRef)context inRect:(CGRect)rect{
  CMLVec3 rgb;
  if(fill || (!linecolor)){
    [self fillRGBfloatarray:rgb fromColor:color];
  }

  // Draw the background if wanted
  if(fill){
    CGColorRef backcolor = CGColorCreateGenericRGB(rgb[0], rgb[1], rgb[2], 1.f);
    CGContextSetFillColorWithColor(context, backcolor);
    CGContextFillRect(context, rect);
    CGColorRelease(backcolor);
  }

  // Create the foreground color if none is given.
  BOOL releaselinecolor = NO;
  if(!linecolor){
    HSVColor hsv;
    hsv.fromRGBBuffer(rgb);
    hsv[2] -= .5f;
    if(hsv[2] < 0.f){hsv[2] += 1.f;}
    CMLVec3 linergb;
    hsv.toRGBBuffer(linergb);
    linecolor = CGColorCreateGenericRGB(linergb[0], linergb[1], linergb[2], 1.f);
    releaselinecolor = YES;
  }

  // Draw the foreground, if any.
  CMLColorType colortype = color->getColorType();
  if((colortype == CML_COLOR_SPECTRUM_ILLUMINATION) || (colortype == CML_COLOR_SPECTRUM_REMISSION)){
    const CMLFunction* spectrum = ((SpectralColor*)color)->getSpectrum();
    float divisor = 1.f;
    if(colortype == CML_COLOR_SPECTRUM_ILLUMINATION){
      float maxvalue = CMLgetFunctionMaxValue(spectrum);
      if(maxvalue == 0){
        divisor = 1.f;
      }else{
        divisor = cmlInverse(CMLgetFunctionMaxValue(spectrum));
      }
    }
    CGContextSetStrokeColorWithColor(context, linecolor);
    CGContextBeginPath(context);
    CMLDefinitionRange defrange;
    CMLgetFunctionDefinitionRange(spectrum, &defrange);
    // In case this is a continuous function, set the stepsize to the default.
    if(defrange.stepsize == 0.f){defrange.stepsize = CML_DEFAULT_INTEGRATION_STEPSIZE;}
    CMLSize samplecount = CMLgetSampleCount(defrange.minSampleCoord, defrange.maxSampleCoord, defrange.stepsize);
    if(samplecount == 1){
      float curcoord = defrange.minSampleCoord;
        CGFloat x = rect.origin.x + ((curcoord - CML_DEFAULT_INTEGRATION_MIN) / (CML_DEFAULT_INTEGRATION_MAX - CML_DEFAULT_INTEGRATION_MIN)) * rect.size.width + .5f;
      CGFloat y1 = rect.origin.y + rect.size.height * (0 + VIEWOFFSET);
      CGFloat y2 = rect.origin.y + rect.size.height * (CMLeval(spectrum, curcoord) * divisor * VIEWRANGE + VIEWOFFSET);
      CGContextMoveToPoint(context, x, y1);
      CGContextAddLineToPoint(context, x, y2);
    }else{
      for(CMLSize i=0; i<samplecount; i++){
        float curcoord = defrange.minSampleCoord + i * defrange.stepsize;
        CGFloat x = rect.origin.x + ((curcoord - CML_DEFAULT_INTEGRATION_MIN) / (CML_DEFAULT_INTEGRATION_MAX - CML_DEFAULT_INTEGRATION_MIN)) * rect.size.width + .5f;
        CGFloat y = rect.origin.y + rect.size.height * (CMLeval(spectrum, curcoord) * divisor * VIEWRANGE + VIEWOFFSET);
        if(i == 0){CGContextMoveToPoint(context, x, y);}
        CGContextAddLineToPoint(context, x, y);
      }
    }
    CGContextStrokePath(context);
  }
  
  if(releaselinecolor){CGColorRelease(linecolor);}
}



+ (CGFloat) getUIScaleFactorForWindow:(NSWindow*)window{
//  #ifdef NSAppKitVersionNumber10_7
//    if(NSAppKitVersionNumber >= NSAppKitVersionNumber10_7){
//      #if defined __MAC_10_7
//        return [window backingScaleFactor];
//      #endif
//    }else{
//      return [window userSpaceScaleFactor];
//    }
//  #else
//    return naGetWindowBackingScaleFactor(window);
//  #endif
  return 1.;
}

@end

