
#import "HSLColorController.h"
#import "ColorMachineApplication.h"


@implementation HSLColorController

- (void)awakeFromNib{
  [self color] = new HSLColor;
  [sliderH initWithController:self
                    colortype:CML_COLOR_HSL
         normedinputconverter:CMLgetNormedInputConverter(CML_COLOR_HSL)
        normedoutputconverter:CMLgetNormedOutputConverter(CML_COLOR_HSL)
                     channelx:0
                     channely:(CMLuint32)-1
                 drawspectrum:NO];
  [sliderS initWithController:self
                    colortype:CML_COLOR_HSL
         normedinputconverter:CMLgetNormedInputConverter(CML_COLOR_HSL)
        normedoutputconverter:CMLgetNormedOutputConverter(CML_COLOR_HSL)
                     channelx:1
                     channely:(CMLuint32)-1
                 drawspectrum:NO];
  [sliderL initWithController:self
                    colortype:CML_COLOR_HSL
         normedinputconverter:CMLgetNormedInputConverter(CML_COLOR_HSL)
        normedoutputconverter:CMLgetNormedOutputConverter(CML_COLOR_HSL)
                     channelx:2
                     channely:(CMLuint32)-1
                 drawspectrum:NO];
  [(ColorWell*)colordisplay initWithController:self
                    colortype:CML_COLOR_HSL
         normedinputconverter:CMLgetNormedCartesianInputConverter(CML_COLOR_HSL)
        normedoutputconverter:CMLgetNormedCartesianOutputConverter(CML_COLOR_HSL)
                     channelx:0
                     channely:1
                 drawspectrum:NO];
}

- (IBAction)valueChangeHSL:(NSControl*)sender {
  HSLColor& hsl = *(HSLColor*)[self color];
  float value = [sender floatValue];
  if      (sender == textfieldH){hsl[0] = value;
  }else if(sender == textfieldS){hsl[1] = value;
  }else if(sender == textfieldL){hsl[2] = value;}
  [(ColorMachineApplication*)NSApp colorHasChanged];
}

- (void) update{
  HSLColor& hsl = *(HSLColor*)[self color];
  hsl = [(ColorMachineApplication*)NSApp getCurrentColor]->toHSL();
  [textfieldH setStringValue:[NSString stringWithFormat:@"%3.03f", hsl[0]]];
  [textfieldS setStringValue:[NSString stringWithFormat:@"%1.05f", hsl[1]]];
  [textfieldL setStringValue:[NSString stringWithFormat:@"%1.05f", hsl[2]]];
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
