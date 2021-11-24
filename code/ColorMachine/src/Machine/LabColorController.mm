
#import "LabColorController.h"
#import "ColorMachineApplication.h"



@implementation LabColorController

- (void)awakeFromNib{
  [self color] = new LabColor;
  [sliderL initWithController:self
                    colorType:CML_COLOR_Lab
         normedinputconverter:cmlGetNormedInputConverter(CML_COLOR_Lab)
        normedoutputconverter:cmlGetNormedOutputConverter(CML_COLOR_Lab)
                     channelx:0
                     channely:(CMLuint32)-1
                 drawspectrum:NO];
  [slidera initWithController:self
                    colorType:CML_COLOR_Lab
         normedinputconverter:cmlGetNormedInputConverter(CML_COLOR_Lab)
        normedoutputconverter:cmlGetNormedOutputConverter(CML_COLOR_Lab)
                     channelx:1
                     channely:(CMLuint32)-1
                 drawspectrum:NO];
  [sliderb initWithController:self
                    colorType:CML_COLOR_Lab
         normedinputconverter:cmlGetNormedInputConverter(CML_COLOR_Lab)
        normedoutputconverter:cmlGetNormedOutputConverter(CML_COLOR_Lab)
                     channelx:2
                     channely:(CMLuint32)-1
                 drawspectrum:NO];
  [sliderc initWithController:self
                    colorType:CML_COLOR_Lch
         normedinputconverter:cmlGetNormedInputConverter(CML_COLOR_Lch)
        normedoutputconverter:cmlGetNormedOutputConverter(CML_COLOR_Lch)
                     channelx:1
                     channely:(CMLuint32)-1
                 drawspectrum:NO];
  [sliderh initWithController:self
                    colorType:CML_COLOR_Lch
         normedinputconverter:cmlGetNormedInputConverter(CML_COLOR_Lch)
        normedoutputconverter:cmlGetNormedOutputConverter(CML_COLOR_Lch)
                     channelx:2
                     channely:(CMLuint32)-1
                 drawspectrum:NO];
  [(ColorWell*)colordisplay initWithController:self
                    colorType:CML_COLOR_Lab
         normedinputconverter:cmlGetNormedCartesianInputConverter(CML_COLOR_Lab)
        normedoutputconverter:cmlGetNormedCartesianOutputConverter(CML_COLOR_Lab)
                     channelx:1
                     channely:2
                 drawspectrum:NO];
}

- (IBAction)valueChangeLab:(NSControl*)sender {
  LabColor& lab = *(LabColor*)[self color];
  float value = [sender floatValue];
  if      (sender == textfieldL){lab[0] = value;
  }else if(sender == textfielda){lab[1] = value;
  }else if(sender == textfieldb){lab[2] = value;}
  [(ColorMachineApplication*)NSApp colorHasChanged];
}

- (IBAction)valueChangeLch:(NSControl*)sender {
  LabColor& lab = *(LabColor*)[self color];
  LchColor lch(lab);
  float value = [sender floatValue];
  if      (sender == textfieldc){lch[1] = value;
  }else if(sender == textfieldh){lch[2] = value;}
  lab = lch.toLab();
  [(ColorMachineApplication*)NSApp colorHasChanged];
}

- (void) update{
  LabColor& lab = *(LabColor*)[self color];
  lab = [(ColorMachineApplication*)NSApp getCurrentColor]->toLab();
  LchColor lch(lab);
  [textfieldL setStringValue:[NSString stringWithFormat:@"%3.02f", lab[0]]];
  [textfielda setStringValue:[NSString stringWithFormat:@"%3.02f", lab[1]]];
  [textfieldb setStringValue:[NSString stringWithFormat:@"%3.02f", lab[2]]];
  [textfieldc setStringValue:[NSString stringWithFormat:@"%3.02f", lch[1]]];
  [textfieldh setStringValue:[NSString stringWithFormat:@"%3.02f", lch[2]]];
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
