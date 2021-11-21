
#import "LabColorController.h"
#import "ColorMachineApplication.h"



@implementation LabColorController

- (void)awakeFromNib{
  [self color] = new LabColor;
  [sliderL initWithController:self
                    colortype:CML_COLOR_Lab
         normedinputconverter:CMLgetNormedInputConverter(CML_COLOR_Lab)
        normedoutputconverter:CMLgetNormedOutputConverter(CML_COLOR_Lab)
                     channelx:0
                     channely:(CMLuint32)-1
                 drawspectrum:NO];
  [slidera initWithController:self
                    colortype:CML_COLOR_Lab
         normedinputconverter:CMLgetNormedInputConverter(CML_COLOR_Lab)
        normedoutputconverter:CMLgetNormedOutputConverter(CML_COLOR_Lab)
                     channelx:1
                     channely:(CMLuint32)-1
                 drawspectrum:NO];
  [sliderb initWithController:self
                    colortype:CML_COLOR_Lab
         normedinputconverter:CMLgetNormedInputConverter(CML_COLOR_Lab)
        normedoutputconverter:CMLgetNormedOutputConverter(CML_COLOR_Lab)
                     channelx:2
                     channely:(CMLuint32)-1
                 drawspectrum:NO];
  [sliderc initWithController:self
                    colortype:CML_COLOR_Lch
         normedinputconverter:CMLgetNormedInputConverter(CML_COLOR_Lch)
        normedoutputconverter:CMLgetNormedOutputConverter(CML_COLOR_Lch)
                     channelx:1
                     channely:(CMLuint32)-1
                 drawspectrum:NO];
  [sliderh initWithController:self
                    colortype:CML_COLOR_Lch
         normedinputconverter:CMLgetNormedInputConverter(CML_COLOR_Lch)
        normedoutputconverter:CMLgetNormedOutputConverter(CML_COLOR_Lch)
                     channelx:2
                     channely:(CMLuint32)-1
                 drawspectrum:NO];
  [(ColorWell*)colordisplay initWithController:self
                    colortype:CML_COLOR_Lab
         normedinputconverter:CMLgetNormedCartesianInputConverter(CML_COLOR_Lab)
        normedoutputconverter:CMLgetNormedCartesianOutputConverter(CML_COLOR_Lab)
                     channelx:1
                     channely:2
                 drawspectrum:NO];
}

- (IBAction)valueChangeLab:(NSControl*)sender {
  LabColor& Lab = *(LabColor*)[self color];
  float value = [sender floatValue];
  if      (sender == textfieldL){Lab[0] = value;
  }else if(sender == textfielda){Lab[1] = value;
  }else if(sender == textfieldb){Lab[2] = value;}
  [(ColorMachineApplication*)NSApp colorHasChanged];
}

- (IBAction)valueChangeLch:(NSControl*)sender {
  LabColor& Lab = *(LabColor*)[self color];
  LchColor Lch(Lab);
  float value = [sender floatValue];
  if      (sender == textfieldc){Lch[1] = value;
  }else if(sender == textfieldh){Lch[2] = value;}
  Lab = Lch.toLab();
  [(ColorMachineApplication*)NSApp colorHasChanged];
}

- (void) update{
  LabColor& Lab = *(LabColor*)[self color];
  Lab = [(ColorMachineApplication*)NSApp getCurrentColor]->toLab();
  LchColor Lch(Lab);
  [textfieldL setStringValue:[NSString stringWithFormat:@"%3.02f", Lab[0]]];
  [textfielda setStringValue:[NSString stringWithFormat:@"%3.02f", Lab[1]]];
  [textfieldb setStringValue:[NSString stringWithFormat:@"%3.02f", Lab[2]]];
  [textfieldc setStringValue:[NSString stringWithFormat:@"%3.02f", Lch[1]]];
  [textfieldh setStringValue:[NSString stringWithFormat:@"%3.02f", Lch[2]]];
//  [self setNeedsDisplay:YES];
  [colordisplay setNeedsDisplay:YES];
  [sliderL setNeedsDisplay:YES];
  [slidera setNeedsDisplay:YES];
  [sliderb setNeedsDisplay:YES];
  [sliderc setNeedsDisplay:YES];
  [sliderh setNeedsDisplay:YES];
}

- (void)setActive:(BOOL)newactive{
  if(newactive){
    [labelL setTextColor:[NSColor whiteColor]];
    [labela setTextColor:[NSColor whiteColor]];
    [labelb setTextColor:[NSColor whiteColor]];
    [labelc setTextColor:[NSColor whiteColor]];
    [labelh setTextColor:[NSColor whiteColor]];
  }else{
    [labelL setTextColor:[NSColor blackColor]];
    [labela setTextColor:[NSColor blackColor]];
    [labelb setTextColor:[NSColor blackColor]];
    [labelc setTextColor:[NSColor blackColor]];
    [labelh setTextColor:[NSColor blackColor]];
  }
  [super setActive:newactive];
}

@end
