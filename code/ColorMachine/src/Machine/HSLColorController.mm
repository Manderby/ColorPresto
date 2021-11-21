
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
  HSLColor& HSL = *(HSLColor*)[self color];
  float value = [sender floatValue];
  if      (sender == textfieldH){HSL[0] = value;
  }else if(sender == textfieldS){HSL[1] = value;
  }else if(sender == textfieldL){HSL[2] = value;}
  [(ColorMachineApplication*)NSApp colorHasChanged];
}

- (void) update{
  HSLColor& HSL = *(HSLColor*)[self color];
  HSL = [(ColorMachineApplication*)NSApp getCurrentColor]->toHSL();
  [textfieldH setStringValue:[NSString stringWithFormat:@"%3.03f", HSL[0]]];
  [textfieldS setStringValue:[NSString stringWithFormat:@"%1.05f", HSL[1]]];
  [textfieldL setStringValue:[NSString stringWithFormat:@"%1.05f", HSL[2]]];
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
