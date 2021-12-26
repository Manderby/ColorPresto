
#import "HSLColorController.h"
#import "ColorMachineApplication.h"


@implementation HSLColorController

- (void)awakeFromNib{
  [self color] = new HSLColor;
  [sliderH initWithController:self
                    colorType:CML_COLOR_HSL
         normedinputconverter:cmlGetNormedInputConverter(CML_COLOR_HSL)
        normedoutputconverter:cmlGetNormedOutputConverter(CML_COLOR_HSL)
                     channelx:0
                     channely:(size_t)-1
                 drawspectrum:NO];
  [sliderS initWithController:self
                    colorType:CML_COLOR_HSL
         normedinputconverter:cmlGetNormedInputConverter(CML_COLOR_HSL)
        normedoutputconverter:cmlGetNormedOutputConverter(CML_COLOR_HSL)
                     channelx:1
                     channely:(size_t)-1
                 drawspectrum:NO];
  [sliderL initWithController:self
                    colorType:CML_COLOR_HSL
         normedinputconverter:cmlGetNormedInputConverter(CML_COLOR_HSL)
        normedoutputconverter:cmlGetNormedOutputConverter(CML_COLOR_HSL)
                     channelx:2
                     channely:(size_t)-1
                 drawspectrum:NO];
  [(ColorWell*)colordisplay initWithController:self
                    colorType:CML_COLOR_HSL
         normedinputconverter:cmlGetNormedCartesianInputConverter(CML_COLOR_HSL)
        normedoutputconverter:cmlGetNormedCartesianOutputConverter(CML_COLOR_HSL)
                     channelx:0
                     channely:1
                 drawspectrum:NO];
}

- (IBAction)valueChangeHSL:(NSControl*)sender {
  HSLColor& hsl = *(HSLColor*)[self color];
  float value = [sender floatValue];
  if      (sender == textFieldH){hsl[0] = value;
  }else if(sender == textFieldS){hsl[1] = value;
  }else if(sender == textFieldL){hsl[2] = value;}
  [(ColorMachineApplication*)NSApp colorHasChanged];
}

- (void) update{
  HSLColor& hsl = *(HSLColor*)[self color];
  hsl = [(ColorMachineApplication*)NSApp getCurrentColor]->toHSL();
  [textFieldH setStringValue:[NSString stringWithFormat:@"%3.03f", hsl[0]]];
  [textFieldS setStringValue:[NSString stringWithFormat:@"%1.05f", hsl[1]]];
  [textFieldL setStringValue:[NSString stringWithFormat:@"%1.05f", hsl[2]]];
//  [self setNeedsDisplay:YES];
  [colordisplay setNeedsDisplay:YES];
  [sliderH setNeedsDisplay:YES];
  [sliderS setNeedsDisplay:YES];
  [sliderL setNeedsDisplay:YES];
}

- (void)setActive:(BOOL)newactive{
  if(newactive){
    [labelH setTextColor:[NSColor whiteColor]];
    [labelS setTextColor:[NSColor whiteColor]];
    [labelL setTextColor:[NSColor whiteColor]];
  }else{
    [labelH setTextColor:[NSColor blackColor]];
    [labelS setTextColor:[NSColor blackColor]];
    [labelL setTextColor:[NSColor blackColor]];
  }
  [super setActive:newactive];
}

@end
