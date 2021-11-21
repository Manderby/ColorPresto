
#import "YuvColorController.h"
#import "ColorMachineApplication.h"



@implementation YuvColorController

- (void)awakeFromNib{
  [self color] = new YupvpColor;
  [sliderY initWithController:self
                    colortype:CML_COLOR_Yupvp
         normedinputconverter:CMLgetNormedInputConverter(CML_COLOR_Yupvp)
        normedoutputconverter:CMLgetNormedOutputConverter(CML_COLOR_Yupvp)
                     channelx:0
                     channely:(CMLuint32)-1
                 drawspectrum:NO];
  [sliderup initWithController:self
                    colortype:CML_COLOR_Yupvp
         normedinputconverter:CMLgetNormedInputConverter(CML_COLOR_Yupvp)
        normedoutputconverter:CMLgetNormedOutputConverter(CML_COLOR_Yupvp)
                     channelx:1
                     channely:(CMLuint32)-1
                 drawspectrum:NO];
  [slidervp initWithController:self
                    colortype:CML_COLOR_Yupvp
         normedinputconverter:CMLgetNormedInputConverter(CML_COLOR_Yupvp)
        normedoutputconverter:CMLgetNormedOutputConverter(CML_COLOR_Yupvp)
                     channelx:2
                     channely:(CMLuint32)-1
                 drawspectrum:NO];
  [slideru initWithController:self
                    colortype:CML_COLOR_Yuv
         normedinputconverter:CMLgetNormedInputConverter(CML_COLOR_Yuv)
        normedoutputconverter:CMLgetNormedOutputConverter(CML_COLOR_Yuv)
                     channelx:1
                     channely:(CMLuint32)-1
                 drawspectrum:NO];
  [sliderv initWithController:self
                    colortype:CML_COLOR_Yuv
         normedinputconverter:CMLgetNormedInputConverter(CML_COLOR_Yuv)
        normedoutputconverter:CMLgetNormedOutputConverter(CML_COLOR_Yuv)
                     channelx:2
                     channely:(CMLuint32)-1
                 drawspectrum:NO];
  [(ColorWell*)colordisplay initWithController:self
                    colortype:CML_COLOR_Yupvp
         normedinputconverter:CMLgetNormedCartesianInputConverter(CML_COLOR_Yupvp)
        normedoutputconverter:CMLgetNormedCartesianOutputConverter(CML_COLOR_Yupvp)
                     channelx:1
                     channely:2
                 drawspectrum:YES];
}

- (IBAction)valueChangeYupvp:(NSControl*)sender {
  YupvpColor& Yupvp = *(YupvpColor*)[self color];
  float value = [sender floatValue];
  if      (sender == textfieldY){Yupvp[0] = value;
  }else if(sender == textfieldu){Yupvp[1] = value;
  }else if(sender == textfieldv){Yupvp[2] = value;}
  [(ColorMachineApplication*)NSApp colorHasChanged];
}

- (IBAction)valueChangeYuv:(NSControl*)sender {
  YupvpColor& Yupvp = *(YupvpColor*)[self color];
  YuvColor Yuv(Yupvp);
  float value = [sender floatValue];
  if(sender == textfieldu){Yuv[1] = value;
  }else if(sender == textfieldv){Yuv[2] = value;}
  Yupvp = Yuv.toYupvp();
  [(ColorMachineApplication*)NSApp colorHasChanged];
}

- (void) update{
  YupvpColor& Yupvp = *(YupvpColor*)[self color];
  Yupvp = [(ColorMachineApplication*)NSApp getCurrentColor]->toYupvp();
  YuvColor Yuv(Yupvp);
  [textfieldY setStringValue:[NSString stringWithFormat:@"%1.05f", Yupvp[0]]];
  [textfieldup setStringValue:[NSString stringWithFormat:@"%1.05f", Yupvp[1]]];
  [textfieldvp setStringValue:[NSString stringWithFormat:@"%1.05f", Yupvp[2]]];
  [textfieldu setStringValue:[NSString stringWithFormat:@"%1.05f", Yuv[1]]];
  [textfieldv setStringValue:[NSString stringWithFormat:@"%1.05f", Yuv[2]]];
//  [self setNeedsDisplay:YES];
  [colordisplay setNeedsDisplay:YES];
  [sliderY setNeedsDisplay:YES];
  [sliderup setNeedsDisplay:YES];
  [slidervp setNeedsDisplay:YES];
  [slideru setNeedsDisplay:YES];
  [sliderv setNeedsDisplay:YES];
}

- (void)setActive:(BOOL)newactive{
  if(newactive){
    [labelY setTextColor:[NSColor whiteColor]];
    [labelup setTextColor:[NSColor whiteColor]];
    [labelvp setTextColor:[NSColor whiteColor]];
    [labelu setTextColor:[NSColor whiteColor]];
    [labelv setTextColor:[NSColor whiteColor]];
  }else{
    [labelY setTextColor:[NSColor blackColor]];
    [labelup setTextColor:[NSColor blackColor]];
    [labelvp setTextColor:[NSColor blackColor]];
    [labelu setTextColor:[NSColor blackColor]];
    [labelv setTextColor:[NSColor blackColor]];
  }
  [super setActive:newactive];
}

@end
