
#import "YxyColorController.h"
#import "ColorMachineApplication.h"



@implementation YxyColorController

- (void)awakeFromNib{
  [self color] = new YxyColor;
  [sliderY initWithController:self
                    colorType:CML_COLOR_Yxy
         normedinputconverter:cmlGetNormedInputConverter(CML_COLOR_Yxy)
        normedoutputconverter:cmlGetNormedOutputConverter(CML_COLOR_Yxy)
                     channelx:0
                     channely:(CMLuint32)-1
                 drawspectrum:NO];
  [sliderx initWithController:self
                    colorType:CML_COLOR_Yxy
         normedinputconverter:cmlGetNormedInputConverter(CML_COLOR_Yxy)
        normedoutputconverter:cmlGetNormedOutputConverter(CML_COLOR_Yxy)
                     channelx:1
                     channely:(CMLuint32)-1
                 drawspectrum:NO];
  [slidery initWithController:self
                    colorType:CML_COLOR_Yxy
         normedinputconverter:cmlGetNormedInputConverter(CML_COLOR_Yxy)
        normedoutputconverter:cmlGetNormedOutputConverter(CML_COLOR_Yxy)
                     channelx:2
                     channely:(CMLuint32)-1
                 drawspectrum:NO];
  [(ColorWell*)colordisplay initWithController:self
                    colorType:CML_COLOR_Yxy
         normedinputconverter:cmlGetNormedCartesianInputConverter(CML_COLOR_Yxy)
        normedoutputconverter:cmlGetNormedCartesianOutputConverter(CML_COLOR_Yxy)
                     channelx:1
                     channely:2
                 drawspectrum:YES];
}

- (IBAction)valueChangeYxy:(NSControl*)sender {
  YxyColor& yxy = *(YxyColor*)[self color];
  float value = [sender floatValue];
  if      (sender == textfieldY){yxy[0] = value;
  }else if(sender == textfieldx){yxy[1] = value;
  }else if(sender == textfieldy){yxy[2] = value;}
  [(ColorMachineApplication*)NSApp colorHasChanged];
}

- (void) update{
  YxyColor& yxy = *(YxyColor*)[self color];
  yxy = [(ColorMachineApplication*)NSApp getCurrentColor]->toYxy();
  [textfieldY setStringValue:[NSString stringWithFormat:@"%1.05f", yxy[0]]];
  [textfieldx setStringValue:[NSString stringWithFormat:@"%1.05f", yxy[1]]];
  [textfieldy setStringValue:[NSString stringWithFormat:@"%1.05f", yxy[2]]];
//  [self setNeedsDisplay:YES];
  [colordisplay setNeedsDisplay:YES];
  [sliderY setNeedsDisplay:YES];
  [sliderx setNeedsDisplay:YES];
  [slidery setNeedsDisplay:YES];
}

- (void)setActive:(BOOL)newactive{
  if(newactive){
    [labelY setTextColor:[NSColor whiteColor]];
    [labelx setTextColor:[NSColor whiteColor]];
    [labely setTextColor:[NSColor whiteColor]];
  }else{
    [labelY setTextColor:[NSColor blackColor]];
    [labelx setTextColor:[NSColor blackColor]];
    [labely setTextColor:[NSColor blackColor]];
  }
  [super setActive:newactive];
}

@end
