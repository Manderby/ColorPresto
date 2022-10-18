
#include <CML.h>
#import "main.h"
#include "CMMetamericsController.h"


@class MachineController;



extern const char* referenceIlluminationstrings[NUMBER_OF_REFERENCE_ILLUMINATIONS];


@interface TwoColorView : NSView {
  CMLVec3 leftcolor;
  CMLVec3 rightcolor;
}
- (void)setColors:(CMLVec3)left :(CMLVec3)right;
- (void)drawRect:(NSRect)rect;
@end



@interface MetamericsWindowController : NSWindowController {
  IBOutlet NSTextField *illnamelabel;
  IBOutlet NSTextField *illXYZ10_X;
  IBOutlet NSTextField *illXYZ10_Z;
  IBOutlet NSTextField *illYxy10_x;
  IBOutlet NSTextField *illYxy10_y;
  IBOutlet NSTextField *illYupvp10_up;
  IBOutlet NSTextField *illYupvp10_vp;
  IBOutlet NSTextField *illYuv10_u;
  IBOutlet NSTextField *illYuv10_v;
  IBOutlet NSTextField *refXYZ10_X;
  IBOutlet NSTextField *refXYZ10_Z;
  IBOutlet NSTextField *refYxy10_x;
  IBOutlet NSTextField *refYxy10_y;
  IBOutlet NSTextField *refYupvp10_up;
  IBOutlet NSTextField *refYupvp10_vp;
  IBOutlet NSTextField *refYuv10_u;
  IBOutlet NSTextField *refYuv10_v;
  IBOutlet NSTextField *illXYZ2_X;
  IBOutlet NSTextField *illXYZ2_Z;
  IBOutlet NSTextField *illYxy2_x;
  IBOutlet NSTextField *illYxy2_y;
  IBOutlet NSTextField *illYupvp2_up;
  IBOutlet NSTextField *illYupvp2_vp;
  IBOutlet NSTextField *illYuv2_u;
  IBOutlet NSTextField *illYuv2_v;
  IBOutlet NSTextField *refXYZ2_X;
  IBOutlet NSTextField *refXYZ2_Z;
  IBOutlet NSTextField *refYxy2_x;
  IBOutlet NSTextField *refYxy2_y;
  IBOutlet NSTextField *refYupvp2_up;
  IBOutlet NSTextField *refYupvp2_vp;
  IBOutlet NSTextField *refYuv2_u;
  IBOutlet NSTextField *refYuv2_v;
  IBOutlet NSTextField *chrErrortextField;
  
  IBOutlet NSTextField *deltaEavg8;
  IBOutlet NSTextField *deltaEmetamer1;
  IBOutlet NSTextField *deltaEmetamer2;
  IBOutlet NSTextField *deltaEmetamer3;
  IBOutlet NSTextField *deltaEmetamer4;
  IBOutlet NSTextField *deltaEmetamer5;
  IBOutlet NSTextField *deltaEmetamer6;
  IBOutlet NSTextField *deltaEmetamer7;
  IBOutlet NSTextField *deltaEmetamer8;
  IBOutlet NSTextField *deltaEmetamer9;
  IBOutlet NSTextField *deltaEmetamer10;
  IBOutlet NSTextField *deltaEmetamer11;
  IBOutlet NSTextField *deltaEmetamer12;
  IBOutlet NSTextField *deltaEmetamer13;
  IBOutlet NSTextField *deltaEmetamer14;
  IBOutlet TwoColorView *deltaEcolorview1;
  IBOutlet TwoColorView *deltaEcolorview2;
  IBOutlet TwoColorView *deltaEcolorview3;
  IBOutlet TwoColorView *deltaEcolorview4;
  IBOutlet TwoColorView *deltaEcolorview5;
  IBOutlet TwoColorView *deltaEcolorview6;
  IBOutlet TwoColorView *deltaEcolorview7;
  IBOutlet TwoColorView *deltaEcolorview8;
  IBOutlet TwoColorView *deltaEcolorview9;
  IBOutlet TwoColorView *deltaEcolorview10;
  IBOutlet TwoColorView *deltaEcolorview11;
  IBOutlet TwoColorView *deltaEcolorview12;
  IBOutlet TwoColorView *deltaEcolorview13;
  IBOutlet TwoColorView *deltaEcolorview14;

  IBOutlet NSTextField *MIvisavg5;
  IBOutlet NSTextField *MIvis1;
  IBOutlet NSTextField *MIvis2;
  IBOutlet NSTextField *MIvis3;
  IBOutlet NSTextField *MIvis4;
  IBOutlet NSTextField *MIvis5;
  IBOutlet NSTextField *MIvisgradelabel;
  IBOutlet TwoColorView *MIviscolorview1;
  IBOutlet TwoColorView *MIviscolorview2;
  IBOutlet TwoColorView *MIviscolorview3;
  IBOutlet TwoColorView *MIviscolorview4;
  IBOutlet TwoColorView *MIviscolorview5;

  IBOutlet NSTextField *MIUVavg3;
  IBOutlet NSTextField *MIUV1;
  IBOutlet NSTextField *MIUV2;
  IBOutlet NSTextField *MIUV3;
  IBOutlet NSTextField *MIUVgradelabel;
  IBOutlet TwoColorView *MIUVcolorview1;
  IBOutlet TwoColorView *MIUVcolorview2;
  IBOutlet TwoColorView *MIUVcolorview3;

  IBOutlet NSTextField *MIavg8;
  IBOutlet NSTextField *MIgradelabel;

  IBOutlet NSTextField *testfield1;
  IBOutlet NSTextField *testfield2;
  IBOutlet NSTextField *testfield3;

  IBOutlet NSPopUpButton *referenceIlluminationselect;
  CMReferenceIlluminationType referenceIlluminationType;
}
- (void)awakeFromNib;
- (void)update;
- (void)showDialog;
- (IBAction)referenceIlluminationchange:(NSPopUpButton*)sender;
@end
