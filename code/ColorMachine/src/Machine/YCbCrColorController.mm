
#import "YCbCrColorController.h"
#import "ColorMachineApplication.h"



@implementation YCbCrColorController

- (void)awakeFromNib{
  [self color] = new YCbCrColor;
  [sliderY initWithController:self
                    colorType:CML_COLOR_YCbCr
         normedinputconverter:cmlGetNormedInputConverter(CML_COLOR_YCbCr)
        normedoutputconverter:cmlGetNormedOutputConverter(CML_COLOR_YCbCr)
                     channelx:0
                     channely:(CMLuint32)-1
                 drawspectrum:NO];
  [sliderCb initWithController:self
                    colorType:CML_COLOR_YCbCr
         normedinputconverter:cmlGetNormedInputConverter(CML_COLOR_YCbCr)
        normedoutputconverter:cmlGetNormedOutputConverter(CML_COLOR_YCbCr)
                     channelx:1
                     channely:(CMLuint32)-1
                 drawspectrum:NO];
  [sliderCr initWithController:self
                    colorType:CML_COLOR_YCbCr
         normedinputconverter:cmlGetNormedInputConverter(CML_COLOR_YCbCr)
        normedoutputconverter:cmlGetNormedOutputConverter(CML_COLOR_YCbCr)
                     channelx:2
                     channely:(CMLuint32)-1
                 drawspectrum:NO];
  [(ColorWell*)colordisplay initWithController:self
                    colorType:CML_COLOR_YCbCr
         normedinputconverter:cmlGetNormedCartesianInputConverter(CML_COLOR_YCbCr)
        normedoutputconverter:cmlGetNormedCartesianOutputConverter(CML_COLOR_YCbCr)
                     channelx:1
                     channely:2
                 drawspectrum:NO];
}

- (IBAction)valueChangeYCbCr:(NSControl*)sender {
  YCbCrColor& ycbcr = *(YCbCrColor*)[self color];
  float value = [sender floatValue];
  if      (sender == textFieldY){ycbcr[0] = value;
  }else if(sender == textFieldCb){ycbcr[1] = value;
  }else if(sender == textFieldCr){ycbcr[2] = value;}
  [(ColorMachineApplication*)NSApp colorHasChanged];
}

- (void) update{
  YCbCrColor& ycbcr = *(YCbCrColor*)[self color];
  ycbcr = [(ColorMachineApplication*)NSApp getCurrentColor]->toYCbCr();
  [textFieldY setStringValue:[NSString stringWithFormat:@"%1.05f", ycbcr[0]]];
  [textFieldCb setStringValue:[NSString stringWithFormat:@"%1.04f", ycbcr[1]]];
  [textFieldCr setStringValue:[NSString stringWithFormat:@"%1.04f", ycbcr[2]]];
//  [self setNeedsDisplay:YES];
  [colordisplay setNeedsDisplay:YES];
  [sliderY setNeedsDisplay:YES];
  [sliderCb setNeedsDisplay:YES];
  [sliderCr setNeedsDisplay:YES];
}

- (void)setActive:(BOOL)newactive{
  if(newactive){
    [labelY setTextColor:[NSColor whiteColor]];
    [labelCb setTextColor:[NSColor whiteColor]];
    [labelCr setTextColor:[NSColor whiteColor]];
  }else{
    [labelY setTextColor:[NSColor blackColor]];
    [labelCb setTextColor:[NSColor blackColor]];
    [labelCr setTextColor:[NSColor blackColor]];
  }
  [super setActive:newactive];
}

@end
