
#import "YCbCrColorController.h"
#import "ColorMachineApplication.h"



@implementation YCbCrColorController

- (void)awakeFromNib{
  [self color] = new YCbCrColor;
  [sliderY initWithController:self
                    colortype:CML_COLOR_YCbCr
         normedinputconverter:CMLgetNormedInputConverter(CML_COLOR_YCbCr)
        normedoutputconverter:CMLgetNormedOutputConverter(CML_COLOR_YCbCr)
                     channelx:0
                     channely:(CMLuint32)-1
                 drawspectrum:NO];
  [sliderCb initWithController:self
                    colortype:CML_COLOR_YCbCr
         normedinputconverter:CMLgetNormedInputConverter(CML_COLOR_YCbCr)
        normedoutputconverter:CMLgetNormedOutputConverter(CML_COLOR_YCbCr)
                     channelx:1
                     channely:(CMLuint32)-1
                 drawspectrum:NO];
  [sliderCr initWithController:self
                    colortype:CML_COLOR_YCbCr
         normedinputconverter:CMLgetNormedInputConverter(CML_COLOR_YCbCr)
        normedoutputconverter:CMLgetNormedOutputConverter(CML_COLOR_YCbCr)
                     channelx:2
                     channely:(CMLuint32)-1
                 drawspectrum:NO];
  [(ColorWell*)colordisplay initWithController:self
                    colortype:CML_COLOR_YCbCr
         normedinputconverter:CMLgetNormedCartesianInputConverter(CML_COLOR_YCbCr)
        normedoutputconverter:CMLgetNormedCartesianOutputConverter(CML_COLOR_YCbCr)
                     channelx:1
                     channely:2
                 drawspectrum:NO];
}

- (IBAction)valueChangeYCbCr:(NSControl*)sender {
  YCbCrColor& YCbCr = *(YCbCrColor*)[self color];
  float value = [sender floatValue];
  if      (sender == textfieldY){YCbCr[0] = value;
  }else if(sender == textfieldCb){YCbCr[1] = value;
  }else if(sender == textfieldCr){YCbCr[2] = value;}
  [(ColorMachineApplication*)NSApp colorHasChanged];
}

- (void) update{
  YCbCrColor& YCbCr = *(YCbCrColor*)[self color];
  YCbCr = [(ColorMachineApplication*)NSApp getCurrentColor]->toYCbCr();
  [textfieldY setStringValue:[NSString stringWithFormat:@"%1.05f", YCbCr[0]]];
  [textfieldCb setStringValue:[NSString stringWithFormat:@"%1.04f", YCbCr[1]]];
  [textfieldCr setStringValue:[NSString stringWithFormat:@"%1.04f", YCbCr[2]]];
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
