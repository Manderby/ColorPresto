
#import "HSVColorController.h"
#import "ColorMachineApplication.h"


@implementation HSVColorController

- (void)awakeFromNib{
  [self color] = new HSVColor;
  [sliderH initWithController:self
                    colorType:CML_COLOR_HSV
         normedinputconverter:cmlGetNormedInputConverter(CML_COLOR_HSV)
        normedoutputconverter:cmlGetNormedOutputConverter(CML_COLOR_HSV)
                     channelx:0
                     channely:(CMLuint32)-1
                 drawspectrum:NO];
  [sliderS initWithController:self
                    colorType:CML_COLOR_HSV
         normedinputconverter:cmlGetNormedInputConverter(CML_COLOR_HSV)
        normedoutputconverter:cmlGetNormedOutputConverter(CML_COLOR_HSV)
                     channelx:1
                     channely:(CMLuint32)-1
                 drawspectrum:NO];
  [sliderV initWithController:self
                    colorType:CML_COLOR_HSV
         normedinputconverter:cmlGetNormedInputConverter(CML_COLOR_HSV)
        normedoutputconverter:cmlGetNormedOutputConverter(CML_COLOR_HSV)
                     channelx:2
                     channely:(CMLuint32)-1
                 drawspectrum:NO];
  [(ColorWell*)colordisplay initWithController:self
                    colorType:CML_COLOR_HSV
         normedinputconverter:cmlGetNormedCartesianInputConverter(CML_COLOR_HSV)
        normedoutputconverter:cmlGetNormedCartesianOutputConverter(CML_COLOR_HSV)
                     channelx:0
                     channely:1
                 drawspectrum:NO];
}

- (IBAction)valueChangeHSV:(NSControl*)sender {
  HSVColor& hsv = *(HSVColor*)[self color];
  float value = [sender floatValue];
  if      (sender == textfieldH){hsv[0] = value;
  }else if(sender == textfieldS){hsv[1] = value;
  }else if(sender == textfieldV){hsv[2] = value;}
  [(ColorMachineApplication*)NSApp colorHasChanged];
}

- (void) update{
  HSVColor& hsv = *(HSVColor*)[self color];
  hsv = [(ColorMachineApplication*)NSApp getCurrentColor]->toHSV();
  [textfieldH setStringValue:[NSString stringWithFormat:@"%3.03f", hsv[0]]];
  [textfieldS setStringValue:[NSString stringWithFormat:@"%1.05f", hsv[1]]];
  [textfieldV setStringValue:[NSString stringWithFormat:@"%1.05f", hsv[2]]];
//  [self setNeedsDisplay:YES];
  [colordisplay setNeedsDisplay:YES];
  [sliderH setNeedsDisplay:YES];
  [sliderS setNeedsDisplay:YES];
  [sliderV setNeedsDisplay:YES];
}

- (void)setActive:(BOOL)newactive{
  if(newactive){
    [labelH setTextColor:[NSColor whiteColor]];
    [labelS setTextColor:[NSColor whiteColor]];
    [labelV setTextColor:[NSColor whiteColor]];
  }else{
    [labelH setTextColor:[NSColor blackColor]];
    [labelS setTextColor:[NSColor blackColor]];
    [labelV setTextColor:[NSColor blackColor]];
  }
  [super setActive:newactive];
}


@end
