
#import "XYZColorController.h"
#import "ColorMachineApplication.h"



@implementation XYZColorController

- (void)awakeFromNib{
  [self color] = new XYZColor;
  [sliderX initWithController:self
                    colortype:CML_COLOR_XYZ
         normedinputconverter:CMLgetNormedInputConverter(CML_COLOR_XYZ)
        normedoutputconverter:CMLgetNormedOutputConverter(CML_COLOR_XYZ)
                     channelx:0
                     channely:(CMLuint32)-1
                 drawspectrum:NO];
  [sliderY initWithController:self
                    colortype:CML_COLOR_XYZ
         normedinputconverter:CMLgetNormedInputConverter(CML_COLOR_XYZ)
        normedoutputconverter:CMLgetNormedOutputConverter(CML_COLOR_XYZ)
                     channelx:1
                     channely:(CMLuint32)-1
                 drawspectrum:NO];
  [sliderZ initWithController:self
                    colortype:CML_COLOR_XYZ
         normedinputconverter:CMLgetNormedInputConverter(CML_COLOR_XYZ)
        normedoutputconverter:CMLgetNormedOutputConverter(CML_COLOR_XYZ)
                     channelx:2
                     channely:(CMLuint32)-1
                 drawspectrum:NO];
  [(ColorWell*)colordisplay initWithController:self
                    colortype:CML_COLOR_XYZ
         normedinputconverter:CMLgetNormedCartesianInputConverter(CML_COLOR_XYZ)
        normedoutputconverter:CMLgetNormedCartesianOutputConverter(CML_COLOR_XYZ)
                     channelx:0
                     channely:2
                 drawspectrum:NO];
}

- (IBAction)valueChangeXYZ:(NSControl*)sender {
  XYZColor& xyz = *(XYZColor*)[self color];
  float value = [sender floatValue];
  if      (sender == textfieldX){xyz[0] = value;
  }else if(sender == textfieldY){xyz[1] = value;
  }else if(sender == textfieldZ){xyz[2] = value;}
  [(ColorMachineApplication*)NSApp colorHasChanged];
}

- (void) update{
  XYZColor& xyz = *(XYZColor*)[self color];
  xyz = [(ColorMachineApplication*)NSApp getCurrentColor]->toXYZ();
  [textfieldX setStringValue:[NSString stringWithFormat:@"%1.05f", xyz[0]]];
  [textfieldY setStringValue:[NSString stringWithFormat:@"%1.05f", xyz[1]]];
  [textfieldZ setStringValue:[NSString stringWithFormat:@"%1.05f", xyz[2]]];
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
