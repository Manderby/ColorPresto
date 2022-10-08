
#include "CMMetamericsController.h"
#include "CMTranslations.h"
#include "CMThreeDeeController.h"

#import "MetamericsWindowController.h"
#import "ColorMachineApplication.h"
#import "AboutWindowController.h"
#import "MachinesController.h"
#import "ColorsController.h"
#import "GrayColorController.h"
#import "MachineWindowController.h"
#import "ScreenResolutionWindowController.h"

#include <NADateTime.h>
#include "NAApp.h"
#include "NAUICocoaLegacy.h"
#include "ManderAppAbout.h"

CMLColorType maskcolor;
bool showmask;
bool showgrid;
float borderthickness;
size_t bordercount;






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
//  Color* newcolor = new SpectralColor(cmlCreateCIEDIlluminant(5678.f), false);
//  Color* newcolor2 = new SpectralColor(cmlCreateFunctionMulScalar(cmlCreateCIEDIlluminant(7777.f), .01f), true);
//  
//  ColorItemColorGroup* cicg = NA_COCOA_AUTORELEASE([[ColorItemColorGroup alloc] init]);
//  [cicg setGroup:colorgroup];
//  ColorItem* newitem = NA_COCOA_AUTORELEASE([[ColorItem alloc] initWithCMLColor:newcolor title:nil]);
//  [newitem setTitle:@"TestSpectrum"];
//  [cicg setItem:newitem];
//
//  ColorItemColorGroup* cicg2 = NA_COCOA_AUTORELEASE([[ColorItemColorGroup alloc] init]);
//  [cicg2 setGroup:colorgroup];
//  ColorItem* newitem2 = NA_COCOA_AUTORELEASE([[ColorItem alloc] initWithCMLColor:newcolor2 title:nil]);
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
  threeDeeController = cmAllocThreeDeeController();
  metamericsController = cmAllocMetamericsController();
  cmUpdateMetamericsController(metamericsController);
  cmUpdateThreeDeeController(threeDeeController);
}

- (id)init{
  self = [super init];
  [self setDelegate:self];
  machinescontroller = [[MachinesController alloc] init];
  return self;
}

- (void)dealloc{
  cmDeallocThreeDeeController(threeDeeController);
  [super dealloc];
}

- (IBAction)showAbout:(id)sender{
  mandShowAboutController();
  
//  if(!aboutwindowcontroller){
//    naLoadNib("AboutWindow", NSApp);
//  }
//  [aboutwindowcontroller showDialog];
}

- (IBAction)showHelp:(NSMenuItem*)sender{
  NA_UNUSED(sender);
  [[NSWorkspace sharedWorkspace] openURL:[NSURL URLWithString:[NSString stringWithUTF8String:cmTranslate(CMApplicationHelpURL)]]];
}

- (IBAction)showScreenResolution:(id)sender{
  if(!screenresolutionwindowcontroller){
    naLoadNib("ScreenResolution", NSApp);
  }
  [screenresolutionwindowcontroller showDialog];
}

- (IBAction)showThreeDee:(id)sender{
  cmShowThreeDeeController(threeDeeController);
}

- (IBAction)showMetamerics:(id)sender{
  if(!metamericswindowcontroller){
    naLoadNib("Metamerics", NSApp);
  }
  [metamericswindowcontroller showDialog];
  cmShowMetamericsController(metamericsController);
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
  cmUpdateMetamericsController(metamericsController);
  cmUpdateThreeDeeController(threeDeeController);
  [colorscontroller updateColor];
  [metamericswindowcontroller update];
}

- (void)updateColor{
  [colorscontroller updateColor];
  cmUpdateMetamericsController(metamericsController);
  cmUpdateThreeDeeController(threeDeeController);
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
  cmlSetReferenceWhitePointYxy([machinescontroller currentMachine], yxybuf);
  [self updateMachine];
}

- (IBAction)setCurrentColorAsRedPrimary:(id)sender{
  CMLColorMachine* cm = [machinescontroller currentMachine];
  CMLVec3 primaries[3];
  cmlGetRGBPrimariesYxy(cm, primaries);
  [colorscontroller currentColor]->toYxyBuffer(primaries[0]);
  cmlSetRGBPrimariesYxy(cm, primaries);
  [self updateMachine];
}
- (IBAction)setCurrentColorAsGreenPrimary:(id)sender{
  CMLColorMachine* cm = [machinescontroller currentMachine];
  CMLVec3 primaries[3];
  cmlGetRGBPrimariesYxy(cm, primaries);
  [colorscontroller currentColor]->toYxyBuffer(primaries[1]);
  cmlSetRGBPrimariesYxy(cm, primaries);
  [self updateMachine];
}
- (IBAction)setCurrentColorAsBluePrimary:(id)sender{
  CMLColorMachine* cm = [machinescontroller currentMachine];
  CMLVec3 primaries[3];
  cmlGetRGBPrimariesYxy(cm, primaries);
  [colorscontroller currentColor]->toYxyBuffer(primaries[2]);
  cmlSetRGBPrimariesYxy(cm, primaries);
  [self updateMachine];
}



- (void)fillRGBfloatarray:(float*)outdata fromColor:(const Color*)inputcolor{
  
  CMLColorMachine* cm = [(ColorMachineApplication*)NSApp getCurrentMachine];
  CMLColorMachine* sm = [(ColorMachineApplication*)NSApp getCurrentScreenMachine];
  CMLVec3 cmWhitePointYxy;
  CMLVec3 smWhitePointYxy;
  cmlCpy3(cmWhitePointYxy, cmlGetReferenceWhitePointYxy(cm));
  cmWhitePointYxy[0] = 1.f;
  cmlCpy3(smWhitePointYxy, cmlGetReferenceWhitePointYxy(sm));
  smWhitePointYxy[0] = 1.f;

  CMLVec3 XYZbuffer;
  inputcolor->toXYZBuffer(XYZbuffer);
  
  CMLVec3 aXYZbuffer;
  CMLMat33 amatrix;
  cmlComputeChromaticAdaptationMatrix(amatrix, CML_CHROMATIC_ADAPTATION_NONE, smWhitePointYxy, cmWhitePointYxy);
  cmlConvertXYZToChromaticAdaptedXYZ(aXYZbuffer, XYZbuffer, amatrix);
  cmlXYZToRGB(sm, outdata, aXYZbuffer, 1);

  cmlClampRGB(outdata, 1);
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
  CMLColorType colorType = color->getColorType();
  if((colorType == CML_COLOR_SPECTRUM_ILLUMINATION) || (colorType == CML_COLOR_SPECTRUM_REMISSION)){
    const CMLFunction* spectrum = ((SpectralColor*)color)->getSpectrum();
    float divisor = 1.f;
    if(colorType == CML_COLOR_SPECTRUM_ILLUMINATION){
      CMLIntegration integration = cmlMakeDefaultIntegration();
      float maxvalue = cmlGetFunctionMaxValue(spectrum, &integration);
      if(maxvalue == 0){
        divisor = 1.f;
      }else{
        divisor = cmlInverse(cmlGetFunctionMaxValue(spectrum, &integration));
      }
    }
    CGContextSetStrokeColorWithColor(context, linecolor);
    CGContextBeginPath(context);
    CMLDefinitionRange defRange;
    cmlGetFunctionDefinitionRange(spectrum, &defRange);
    // In case this is a continuous function, set the stepSize to the default.
    if(defRange.stepSize == 0.f){defRange.stepSize = CML_DEFAULT_INTEGRATION_STEPSIZE;}
    size_t sampleCount = cmlGetSampleCount(defRange.minSampleCoord, defRange.maxSampleCoord, defRange.stepSize);
    if(sampleCount == 1){
      float curcoord = defRange.minSampleCoord;
        CGFloat x = rect.origin.x + ((curcoord - CML_DEFAULT_INTEGRATION_MIN) / (CML_DEFAULT_INTEGRATION_MAX - CML_DEFAULT_INTEGRATION_MIN)) * rect.size.width + .5f;
      CGFloat y1 = rect.origin.y + rect.size.height * (0 + VIEWOFFSET);
      CGFloat y2 = rect.origin.y + rect.size.height * (cmlEval(spectrum, curcoord) * divisor * VIEWRANGE + VIEWOFFSET);
      CGContextMoveToPoint(context, x, y1);
      CGContextAddLineToPoint(context, x, y2);
    }else{
      for(size_t i=0; i<sampleCount; i++){
        float curcoord = defRange.minSampleCoord + i * defRange.stepSize;
        CGFloat x = rect.origin.x + ((curcoord - CML_DEFAULT_INTEGRATION_MIN) / (CML_DEFAULT_INTEGRATION_MAX - CML_DEFAULT_INTEGRATION_MIN)) * rect.size.width + .5f;
        CGFloat y = rect.origin.y + rect.size.height * (cmlEval(spectrum, curcoord) * divisor * VIEWRANGE + VIEWOFFSET);
        if(i == 0){CGContextMoveToPoint(context, x, y);}
        CGContextAddLineToPoint(context, x, y);
      }
    }
    CGContextStrokePath(context);
  }
  
  if(releaselinecolor){CGColorRelease(linecolor);}
}



+ (CGFloat) getUIScaleFactorForWindow:(NSWindow*)window{
  return naGetWindowBackingScaleFactor(window);
}

@end

