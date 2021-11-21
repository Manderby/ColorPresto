
#import "YxyColorController.h"
#import "ColorMachineApplication.h"



@implementation YxyColorController

- (void)awakeFromNib{
  [self color] = new YxyColor;
  [sliderY initWithController:self
                    colortype:CML_COLOR_Yxy
         normedinputconverter:CMLgetNormedInputConverter(CML_COLOR_Yxy)
        normedoutputconverter:CMLgetNormedOutputConverter(CML_COLOR_Yxy)
                     channelx:0
                     channely:(CMLuint32)-1
                 drawspectrum:NO];
  [sliderx initWithController:self
                    colortype:CML_COLOR_Yxy
         normedinputconverter:CMLgetNormedInputConverter(CML_COLOR_Yxy)
        normedoutputconverter:CMLgetNormedOutputConverter(CML_COLOR_Yxy)
                     channelx:1
                     channely:(CMLuint32)-1
                 drawspectrum:NO];
  [slidery initWithController:self
                    colortype:CML_COLOR_Yxy
         normedinputconverter:CMLgetNormedInputConverter(CML_COLOR_Yxy)
        normedoutputconverter:CMLgetNormedOutputConverter(CML_COLOR_Yxy)
                     channelx:2
                     channely:(CMLuint32)-1
                 drawspectrum:NO];
  [(ColorWell*)colordisplay initWithController:self
                    colortype:CML_COLOR_Yxy
         normedinputconverter:CMLgetNormedCartesianInputConverter(CML_COLOR_Yxy)
        normedoutputconverter:CMLgetNormedCartesianOutputConverter(CML_COLOR_Yxy)
                     channelx:1
                     channely:2
                 drawspectrum:YES];
}

- (IBAction)valueChangeYxy:(NSControl*)sender {
  YxyColor& Yxy = *(YxyColor*)[self color];
  float value = [sender floatValue];
  if      (sender == textfieldY){Yxy[0] = value;
  }else if(sender == textfieldx){Yxy[1] = value;
  }else if(sender == textfieldy){Yxy[2] = value;}
  [(ColorMachineApplication*)NSApp colorHasChanged];
}

- (void) update{
  YxyColor& Yxy = *(YxyColor*)[self color];
  Yxy = [(ColorMachineApplication*)NSApp getCurrentColor]->toYxy();
  [textfieldY setStringValue:[NSString stringWithFormat:@"%1.05f", Yxy[0]]];
  [textfieldx setStringValue:[NSString stringWithFormat:@"%1.05f", Yxy[1]]];
  [textfieldy setStringValue:[NSString stringWithFormat:@"%1.05f", Yxy[2]]];
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
