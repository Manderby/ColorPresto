
#import "XYZColorController.h"
#import "ColorMachineApplication.h"



@implementation XYZColorController

- (void)awakeFromNib{
  [self color] = new XYZColor;
  [sliderX initWithController:self
                    colorType:CML_COLOR_XYZ
         normedinputconverter:cmlGetNormedInputConverter(CML_COLOR_XYZ)
        normedoutputconverter:cmlGetNormedOutputConverter(CML_COLOR_XYZ)
                     channelx:0
                     channely:(size_t)-1
                 drawspectrum:NO];
  [sliderY initWithController:self
                    colorType:CML_COLOR_XYZ
         normedinputconverter:cmlGetNormedInputConverter(CML_COLOR_XYZ)
        normedoutputconverter:cmlGetNormedOutputConverter(CML_COLOR_XYZ)
                     channelx:1
                     channely:(size_t)-1
                 drawspectrum:NO];
  [sliderZ initWithController:self
                    colorType:CML_COLOR_XYZ
         normedinputconverter:cmlGetNormedInputConverter(CML_COLOR_XYZ)
        normedoutputconverter:cmlGetNormedOutputConverter(CML_COLOR_XYZ)
                     channelx:2
                     channely:(size_t)-1
                 drawspectrum:NO];
  [(ColorWell*)colordisplay initWithController:self
                    colorType:CML_COLOR_XYZ
         normedinputconverter:cmlGetNormedCartesianInputConverter(CML_COLOR_XYZ)
        normedoutputconverter:cmlGetNormedCartesianOutputConverter(CML_COLOR_XYZ)
                     channelx:0
                     channely:2
                 drawspectrum:NO];
}

- (IBAction)valueChangeXYZ:(NSControl*)sender {
  XYZColor& xyz = *(XYZColor*)[self color];
  float value = [sender floatValue];
  if      (sender == textFieldX){xyz[0] = value;
  }else if(sender == textFieldY){xyz[1] = value;
  }else if(sender == textFieldZ){xyz[2] = value;}
  [(ColorMachineApplication*)NSApp colorHasChanged];
}

- (void) update{
  XYZColor& xyz = *(XYZColor*)[self color];
  xyz = [(ColorMachineApplication*)NSApp getCurrentColor]->toXYZ();
  [textFieldX setStringValue:[NSString stringWithFormat:@"%1.05f", xyz[0]]];
  [textFieldY setStringValue:[NSString stringWithFormat:@"%1.05f", xyz[1]]];
  [textFieldZ setStringValue:[NSString stringWithFormat:@"%1.05f", xyz[2]]];
//  [self setNeedsDisplay:YES];
  [colordisplay setNeedsDisplay:YES];
  [sliderX setNeedsDisplay:YES];
  [sliderY setNeedsDisplay:YES];
  [sliderZ setNeedsDisplay:YES];
}

- (void)setActive:(BOOL)newactive{
  if(newactive){
    [labelX setTextColor:[NSColor whiteColor]];
    [labelY setTextColor:[NSColor whiteColor]];
    [labelZ setTextColor:[NSColor whiteColor]];
  }else{
    [labelX setTextColor:[NSColor blackColor]];
    [labelY setTextColor:[NSColor blackColor]];
    [labelZ setTextColor:[NSColor blackColor]];
  }
  [super setActive:newactive];
}

@end
