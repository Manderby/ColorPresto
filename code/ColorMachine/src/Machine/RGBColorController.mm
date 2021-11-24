
#import "RGBColorController.h"
#import "ColorMachineApplication.h"



@implementation GammaDisplay

-(void) drawRect: (NSRect) rect{
  
  [super drawRect:rect];

  CMLColorMachine* cm = [(ColorMachineApplication*)NSApp getCurrentMachine];
  glEnable(GL_DEPTH_TEST);
  glClearColor(0, 0, 0, 1);
  glClear(GL_COLOR_BUFFER_BIT);
  glClear(GL_DEPTH_BUFFER_BIT);

  float stripes = 10.f;

  const CMLFunction* (responses[3]);
  responses[0] = CMLgetResponseCurveInvFunc(CMLgetResponseR(cm));
  responses[1] = CMLgetResponseCurveInvFunc(CMLgetResponseG(cm));
  responses[2] = CMLgetResponseCurveInvFunc(CMLgetResponseB(cm));

  glBegin(GL_LINE_STRIP);
    glColor3d(1, .5, .5);
    for(uint32 x=0; x<width; ++x){
      float curx = (float)x / width;
      float y = height * CMLeval(responses[0], curx);
      float z = sinf(stripes*((float)x * NA_PI2f / (float)width + (0.f/3.f) * NA_PI2f));
      glVertex3d(x, y, z);
    }
  glEnd();
  glBegin(GL_LINE_STRIP);
    glColor3d(.5, 1, .5);
    for(uint32 x=0; x<width; ++x){
      float curx = (float)x / width;
      float y = height * CMLeval(responses[1], curx);
      float z = sinf(stripes*((float)x * NA_PI2f / (float)width + (1.f/3.f) * NA_PI2f));
      glVertex3d(x, y, z);
    }
  glEnd();
  glBegin(GL_LINE_STRIP);
    glColor3d(.5, .5, 1);
    for(uint32 x=0; x<width; ++x){
      float curx = (float)x / width;
      float y = height * CMLeval(responses[2], curx);
      float z = sinf(stripes*((float)x * NA_PI2f / (float)width + (2.f/3.f) * NA_PI2f));
      glVertex3d(x, y, z);
    }
  glEnd();

  [[self openGLContext] flushBuffer];

}

@end


@implementation RGBColorController

- (void)awakeFromNib{
  [self color] = new RGBColor;
  [sliderR initWithController:self
                    colorType:CML_COLOR_RGB
         normedinputconverter:cmlGetNormedInputConverter(CML_COLOR_RGB)
        normedoutputconverter:cmlGetNormedOutputConverter(CML_COLOR_RGB)
                     channelx:0
                     channely:(CMLuint32)-1
                 drawspectrum:NO];
  [sliderG initWithController:self
                    colorType:CML_COLOR_RGB
         normedinputconverter:cmlGetNormedInputConverter(CML_COLOR_RGB)
        normedoutputconverter:cmlGetNormedOutputConverter(CML_COLOR_RGB)
                     channelx:1
                     channely:(CMLuint32)-1
                 drawspectrum:NO];
  [sliderB initWithController:self
                    colorType:CML_COLOR_RGB
         normedinputconverter:cmlGetNormedInputConverter(CML_COLOR_RGB)
        normedoutputconverter:cmlGetNormedOutputConverter(CML_COLOR_RGB)
                     channelx:2
                     channely:(CMLuint32)-1
                 drawspectrum:NO];
  [(ColorWell*)colordisplay initWithController:self
                    colorType:CML_COLOR_RGB
         normedinputconverter:cmlGetNormedCartesianInputConverter(CML_COLOR_RGB)
        normedoutputconverter:cmlGetNormedCartesianOutputConverter(CML_COLOR_RGB)
                     channelx:0
                     channely:2
                 drawspectrum:NO];
}

- (IBAction)valueChangeRGB:(NSControl*)sender {
  RGBColor& rgb = *(RGBColor*)[self color];
  float value = [sender floatValue];
  if      (sender == textfieldR){rgb[0] = value;
  }else if(sender == textfieldG){rgb[1] = value;
  }else if(sender == textfieldB){rgb[2] = value;}
  [(ColorMachineApplication*)NSApp colorHasChanged];
}

- (IBAction)valueChangeweb:(NSControl*)sender {
  char string[7];
  [[sender stringValue] getCString: string maxLength: 7 encoding: [NSString defaultCStringEncoding]];
  int rgbbuf[3];
  sscanf(string, "%02x%02x%02x", &(rgbbuf[0]), &(rgbbuf[1]), &(rgbbuf[2]));
  Byte rgbbuf2[3];
  rgbbuf2[0] = rgbbuf[0];
  rgbbuf2[1] = rgbbuf[1];
  rgbbuf2[2] = rgbbuf[2];
  RGBColor& rgb = *(RGBColor*)[self color];
  rgb.from8BitBuffer(rgbbuf2);
  [(ColorMachineApplication*)NSApp colorHasChanged];
}

- (IBAction)valueChangewebrgb:(NSControl*)sender {
  char string[100];
  [[sender stringValue] getCString: string maxLength: 100 encoding: [NSString defaultCStringEncoding]];
  int rgbbuf[3];
  int assigned = sscanf(string, "%d, %d, %d", &(rgbbuf[0]), &(rgbbuf[1]), &(rgbbuf[2]));
  if(assigned < 3){
    sscanf(string, "%d %d %d", &(rgbbuf[0]), &(rgbbuf[1]), &(rgbbuf[2]));
  }
  Byte rgbbuf2[3];
  rgbbuf2[0] = rgbbuf[0];
  rgbbuf2[1] = rgbbuf[1];
  rgbbuf2[2] = rgbbuf[2];
  RGBColor& rgb = *(RGBColor*)[self color];
  rgb.from8BitBuffer(rgbbuf2);
  [(ColorMachineApplication*)NSApp colorHasChanged];
}

- (void) update{
  RGBColor& rgb = *(RGBColor*)[self color];
  rgb = [(ColorMachineApplication*)NSApp getCurrentColor]->toRGB();
  [textfieldR setStringValue:[NSString stringWithFormat:@"%1.05f", rgb[0]]];
  [textfieldG setStringValue:[NSString stringWithFormat:@"%1.05f", rgb[1]]];
  [textfieldB setStringValue:[NSString stringWithFormat:@"%1.05f", rgb[2]]];
  RGBColor clamped = rgb;
  clamped.clamp();
  Byte rgbbuf[3];
  clamped.to8BitBuffer(rgbbuf);
  [textfieldweb setStringValue:[NSString stringWithFormat:@"%02x%02x%02x", (int)rgbbuf[0], (int)rgbbuf[1], (int)rgbbuf[2]]];
  [textfieldwebrgb setStringValue:[NSString stringWithFormat:@"%d, %d, %d", (int)rgbbuf[0], (int)rgbbuf[1], (int)rgbbuf[2]]];
//  [self setNeedsDisplay:YES];
  [colordisplay setNeedsDisplay:YES];
  [sliderR setNeedsDisplay:YES];
  [sliderG setNeedsDisplay:YES];
  [sliderB setNeedsDisplay:YES];
}

- (void)setActive:(BOOL)newactive{
  if(newactive){
    [labelR setTextColor:[NSColor whiteColor]];
    [labelG setTextColor:[NSColor whiteColor]];
    [labelB setTextColor:[NSColor whiteColor]];
    [labelHash setTextColor:[NSColor whiteColor]];
  }else{
    [labelR setTextColor:[NSColor blackColor]];
    [labelG setTextColor:[NSColor blackColor]];
    [labelB setTextColor:[NSColor blackColor]];
    [labelHash setTextColor:[NSColor blackColor]];
  }
  [super setActive:newactive];
}

@end
