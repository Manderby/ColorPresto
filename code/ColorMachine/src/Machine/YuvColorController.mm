
#import "YuvColorController.h"
#import "ColorMachineApplication.h"



@implementation YuvColorController

- (void)awakeFromNib{
  [self color] = new YupvpColor;
  [sliderY initWithController:self
                    colorType:CML_COLOR_Yupvp
         normedinputconverter:cmlGetNormedInputConverter(CML_COLOR_Yupvp)
        normedoutputconverter:cmlGetNormedOutputConverter(CML_COLOR_Yupvp)
                     channelx:0
                     channely:(CMLuint32)-1
                 drawspectrum:NO];
  [sliderup initWithController:self
                    colorType:CML_COLOR_Yupvp
         normedinputconverter:cmlGetNormedInputConverter(CML_COLOR_Yupvp)
        normedoutputconverter:cmlGetNormedOutputConverter(CML_COLOR_Yupvp)
                     channelx:1
                     channely:(CMLuint32)-1
                 drawspectrum:NO];
  [slidervp initWithController:self
                    colorType:CML_COLOR_Yupvp
         normedinputconverter:cmlGetNormedInputConverter(CML_COLOR_Yupvp)
        normedoutputconverter:cmlGetNormedOutputConverter(CML_COLOR_Yupvp)
                     channelx:2
                     channely:(CMLuint32)-1
                 drawspectrum:NO];
  [slideru initWithController:self
                    colorType:CML_COLOR_Yuv
         normedinputconverter:cmlGetNormedInputConverter(CML_COLOR_Yuv)
        normedoutputconverter:cmlGetNormedOutputConverter(CML_COLOR_Yuv)
                     channelx:1
                     channely:(CMLuint32)-1
                 drawspectrum:NO];
  [sliderv initWithController:self
                    colorType:CML_COLOR_Yuv
         normedinputconverter:cmlGetNormedInputConverter(CML_COLOR_Yuv)
        normedoutputconverter:cmlGetNormedOutputConverter(CML_COLOR_Yuv)
                     channelx:2
                     channely:(CMLuint32)-1
                 drawspectrum:NO];
  [(ColorWell*)colordisplay initWithController:self
                    colorType:CML_COLOR_Yupvp
         normedinputconverter:cmlGetNormedCartesianInputConverter(CML_COLOR_Yupvp)
        normedoutputconverter:cmlGetNormedCartesianOutputConverter(CML_COLOR_Yupvp)
                     channelx:1
                     channely:2
                 drawspectrum:YES];
}

- (IBAction)valueChangeYupvp:(NSControl*)sender {
  YupvpColor& yupvp = *(YupvpColor*)[self color];
  float value = [sender floatValue];
  if      (sender == textfieldY){yupvp[0] = value;
  }else if(sender == textfieldu){yupvp[1] = value;
  }else if(sender == textfieldv){yupvp[2] = value;}
  [(ColorMachineApplication*)NSApp colorHasChanged];
}

- (IBAction)valueChangeYuv:(NSControl*)sender {
  YupvpColor& yupvp = *(YupvpColor*)[self color];
  YuvColor yuv(yupvp);
  float value = [sender floatValue];
  if(sender == textfieldu){yuv[1] = value;
  }else if(sender == textfieldv){yuv[2] = value;}
  yupvp = yuv.toYupvp();
  [(ColorMachineApplication*)NSApp colorHasChanged];
}

- (void) update{
  YupvpColor& yupvp = *(YupvpColor*)[self color];
  yupvp = [(ColorMachineApplication*)NSApp getCurrentColor]->toYupvp();
  YuvColor yuv(yupvp);
  [textfieldY setStringValue:[NSString stringWithFormat:@"%1.05f", yupvp[0]]];
  [textfieldup setStringValue:[NSString stringWithFormat:@"%1.05f", yupvp[1]]];
  [textfieldvp setStringValue:[NSString stringWithFormat:@"%1.05f", yupvp[2]]];
  [textfieldu setStringValue:[NSString stringWithFormat:@"%1.05f", yuv[1]]];
  [textfieldv setStringValue:[NSString stringWithFormat:@"%1.05f", yuv[2]]];
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
