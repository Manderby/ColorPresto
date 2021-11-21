
#import "ColorMachineApplication.h"

#import "MachineWindowController.h"
#import "GrayColorController.h"
#import "XYZColorController.h"
#import "YxyColorController.h"
#import "LabColorController.h"
#import "LuvColorController.h"
#import "RGBColorController.h"
#import "HSVColorController.h"
#import "HSLColorController.h"
#import "YCbCrColorController.h"
#import "SpectralColorController.h"

#import "ThreeDeeWindowController.h"






@implementation MachineWindowController

- (void)awakeFromNib{

//  [[self window] setColorSpace:[NSColorSpace deviceRGBColorSpace]];
//  [[self window] setColorSpace:[NSColorSpace sRGBColorSpace]];
  
  colorselectionisExpanded = YES;
  [self collapseColorSelection];

  [[self window] setDelegate:self];
  
  
//  NSScreen* screen = [[self window] screen];
//  NSNumber* screenID = (NSNumber*)[screendict objectForKey:@"NSScreenNumber"];
//  CGDirectDisplayID cgid = [screenID unsignedIntValue];
//
//  CGDisplayConfigRef configref;
//  CGBeginDisplayConfiguration(&configref);
//  CGSetDisplayTransferByFormula(cgid, 0.f, 1.f, 1.f, 0.f, 1.f, 1.f, 0.f, 1.f, 1.f);
//  CGCompleteDisplayConfiguration(configref, kCGConfigureForAppOnly);

//  NSData* iccnsdata = [[[[self window] screen] colorSpace] ICCProfileData];
//  const Byte* iccdata = (const Byte*)[iccnsdata bytes];

  
  
  maskcolor = CML_COLOR_RGB;
  showgrid = false;
  borderthickness = .01f;
  bordercount = 4;

  // //////////////////////////
  // Init the select menus
  // //////////////////////////

  [maskselect removeAllItems];
  for(uint32 i=0; i<CML_NUMBER_OF_COLORTYPES; ++i){
    if((CMLColorType)i >= CML_COLOR_CMYK){continue;}
    [maskselect insertItemWithTitle:[NSString stringWithUTF8String:CMLgetColorTypeString((CMLColorType)i)] atIndex:i];
  }
  [maskselect selectItemAtIndex:(int)CML_COLOR_RGB];




  [observerselect removeAllItems];
  for(uint32 i=0; i<CML_NUMBER_OF_OBSERVERS - 1; ++i){
    [observerselect insertItemWithTitle:[NSString stringWithUTF8String:CMLgetObserverTypeString((CMLObserverType)i)] atIndex:i];
  }

  [illuminationselect setAutoenablesItems:NO];
  [illuminationselect removeAllItems];
  for(uint32 i=0; i<CML_NUMBER_OF_ILLUMINATIONS; ++i){
    [illuminationselect insertItemWithTitle:[NSString stringWithUTF8String:CMLgetIlluminationTypeString((CMLIlluminationType)i)] atIndex:i];
  }
  [[illuminationselect itemAtIndex:CML_ILLUMINATION_CUSTOM_SPECTRUM] setEnabled:FALSE];

  [rgbcolorspaceselect removeAllItems];
  for(uint32 i=0; i<CML_NUMBER_OF_RGB_SPACES; ++i){
    [rgbcolorspaceselect insertItemWithTitle:[NSString stringWithUTF8String:CMLgetRGBColorspaceString((CMLRGBColorSpace)i)] atIndex:i];
  }

  [responseRGBselect removeAllItems];
  [responseRGBselect insertItemWithTitle:@"Custom" atIndex:0];
  for(uint32 i=0; i<CML_NUMBER_OF_RESPONSE_CURVE_PRESETS; ++i){
    [responseRGBselect insertItemWithTitle:[NSString stringWithUTF8String:CMLgetRGBResponsePresetString((CMLResponseCurvePreset)i)] atIndex:i+1];
  }

  [labspaceselect removeAllItems];
  uint32 curindex = 0;
  for(uint32 i=0; i<CML_NUMBER_OF_LAB_SPACES; ++i){
    if(i == CML_LAB_CUSTOM_L){continue;}
    [labspaceselect insertItemWithTitle:[NSString stringWithUTF8String:CMLgetLabSpaceTypeString((CMLLabColorSpaceType)i)] atIndex:curindex];
    curindex++;
  }
  [responseLselect removeAllItems];
  for(uint32 i=0; i<CML_NUMBER_OF_FUNCTION_TYPES; ++i){
    [responseLselect insertItemWithTitle:[NSString stringWithUTF8String:CMLgetFunctionTypeString((CMLFunctionType)i)] atIndex:i];
  }

  [graycomputationselect removeAllItems];
  for(uint32 i=0; i<CML_NUMBER_OF_GRAY_COMPUTATIONS; ++i){
    [graycomputationselect insertItemWithTitle:[NSString stringWithUTF8String:CMLgetGrayComputationTypeString((CMLGrayComputationType)i)] atIndex:i];
  }

  [chromaticadaptationselect removeAllItems];
  for(uint32 i=0; i<CML_NUMBER_OF_CHROMATIC_ADAPTATIONS; ++i){
    [chromaticadaptationselect insertItemWithTitle:[NSString stringWithUTF8String:CMLgetChromaticAdaptationTypeString((CMLChromaticAdaptationType)i)] atIndex:i];
  }

}



- (IBAction)maskstateChange:(NSButton*)sender {
  showmask = ([sender state] == NSOnState);
  [(ColorMachineApplication*)NSApp updateMachine];
}

- (IBAction)maskChange:(NSPopUpButton*)sender {
  maskcolor = (CMLColorType)([sender indexOfSelectedItem]);
  [(ColorMachineApplication*)NSApp updateMachine];
}

- (IBAction)gridlinesChange:(NSButton*)sender {
  showgrid = ([sender state] == NSOnState);
  [(ColorMachineApplication*)NSApp updateMachine];
}

- (IBAction)observerChange:(NSPopUpButton*)sender {
  CMLColorMachine* cm = [(ColorMachineApplication*)NSApp getCurrentMachine];
  CMLsetObserverType(cm, (CMLObserverType)[sender indexOfSelectedItem]);
  [(ColorMachineApplication*)NSApp updateMachine];
}

- (IBAction)illuminationChange:(NSPopUpButton*)sender {
  CMLColorMachine* cm = [(ColorMachineApplication*)NSApp getCurrentMachine];
  CMLIlluminationType newillum = (CMLIlluminationType)[sender indexOfSelectedItem];
  if(newillum == CML_ILLUMINATION_CUSTOM_WHITEPOINT){
    CMLVec3 wpyxy;
    CMLgetWhitePointYxy(cm, wpyxy);
    wpyxy[0] = 1.f;
    CMLsetWhitePointYxy(cm, wpyxy);
  }else{
    CMLsetIlluminationType(cm, newillum);
  }
  [(ColorMachineApplication*)NSApp updateMachine];
}

//- (IBAction)chromaticadaptationChange:(NSPopUpButton*)sender {
//  CMLColorMachine* cm = [(ColorMachineApplication*)NSApp getCurrentMachine];
//  CMLChromaticAdaptationType newadaptation = (CMLChromaticAdaptationType)[sender indexOfSelectedItem];
//  CMLsetChromaticAdaptation(cm, newadaptation);
//  [(ColorMachineApplication*)NSApp updateMachine];
//}

- (IBAction)whitepointChange:(NSControl*)sender{
  CMLColorMachine* cm = [(ColorMachineApplication*)NSApp getCurrentMachine];
  CMLVec3 curwhite;
  CMLgetWhitePointYxy(cm, curwhite);
  curwhite[0] = 1.f;
  if(sender == whitepointx){
    curwhite[1] = [sender floatValue];
  }else if(sender == whitepointy){
    curwhite[2] = [sender floatValue];
  }else{
//    curwhite[0] = [sender floatValue];
  }
  CMLsetWhitePointYxy(cm, curwhite);
  [(ColorMachineApplication*)NSApp updateMachine];
}

- (IBAction)rgbprimariesChange:(NSControl*)sender{
  CMLColorMachine* cm = [(ColorMachineApplication*)NSApp getCurrentMachine];
  CMLVec3 primaries[3];
  CMLgetRGBPrimariesYxy(cm, primaries);
  if(sender == redprimaryx){
    primaries[0][1] = [sender floatValue];
  }else if(sender == redprimaryy){
    primaries[0][2] = [sender floatValue];
  }else if(sender == greenprimaryx){
    primaries[1][1] = [sender floatValue];
  }else if(sender == greenprimaryy){
    primaries[1][2] = [sender floatValue];
  }else if(sender == blueprimaryx){
    primaries[2][1] = [sender floatValue];
  }else if(sender == blueprimaryy){
    primaries[2][2] = [sender floatValue];
  }
  CMLsetRGBPrimariesYxy(cm, primaries);
  [(ColorMachineApplication*)NSApp updateMachine];
}

- (IBAction)rgbresponseChange:(NSPopUpButton*)sender{
  CMLColorMachine* cm = [(ColorMachineApplication*)NSApp getCurrentMachine];
//  const CMLResponseCurve* responseR = CMLgetResponseR(cm);
  if      (sender == responseRGBselect){
    NSInteger selecteditem = [responseRGBselect indexOfSelectedItem] - 1;
    if(selecteditem < 0){return;}
    CMLResponseCurve* newresponse = cmlCreateResponseCurveWithPreset(NULL, (CMLResponseCurvePreset)selecteditem);
//    CMLResponseCurve* newresponse = CMLcreateResponseCurveWith4ParamsFunction(NULL, [textfieldgammaRGB floatValue], [textfieldoffsetRGB floatValue], [textfieldlinscaleRGB floatValue], [textfieldsplitRGB floatValue]);
    CMLsetResponseRGB(cm, newresponse);
    CMLdestroyResponseCurve(newresponse);
//    CMLsetResponseRGB(cm, (CMLFunctionType)[sender indexOfSelectedItem], CMLgetResponseCurveParam0(responseR), CMLgetResponseCurveParam1(responseR), CMLgetResponseCurveParam2(responseR), CMLgetResponseCurveParam3(responseR));
  }
  [(ColorMachineApplication*)NSApp updateMachine];
}

- (IBAction)rgbgammaChange:(NSControl*)sender{
  CMLColorMachine* cm = [(ColorMachineApplication*)NSApp getCurrentMachine];
//  const CMLResponseCurve* responseR = CMLgetResponseR(cm);
//  CMLFunctionType curvetype = CMLgetResponseCurveFunctionType(responseR);
  if      ((sender == slidergammaRGB) || (sender == textfieldgammaRGB)){
    CMLResponseCurve* newresponse = cmlCreateResponseCurveWith4ParamsFunction(NULL, [sender floatValue], [textfieldoffsetRGB floatValue], [textfieldlinscaleRGB floatValue], [textfieldsplitRGB floatValue]);
    CMLsetResponseRGB(cm, newresponse);
    CMLdestroyResponseCurve(newresponse);
//    CMLsetResponseRGB(cm, curvetype, [sender floatValue], CMLgetResponseCurveParam1(responseR), CMLgetResponseCurveParam2(responseR), CMLgetResponseCurveParam3(responseR));
  }
  [(ColorMachineApplication*)NSApp updateMachine];
}

- (IBAction)rgboffsetChange:(NSControl*)sender{
  CMLColorMachine* cm = [(ColorMachineApplication*)NSApp getCurrentMachine];
//  const CMLResponseCurve* responseR = CMLgetResponseR(cm);
//  CMLFunctionType curvetype = CMLgetResponseCurveFunctionType(responseR);
  if      ((sender == slideroffsetRGB) || (sender == textfieldoffsetRGB)){
    CMLResponseCurve* newresponse = cmlCreateResponseCurveWith4ParamsFunction(NULL, [textfieldgammaRGB floatValue], [sender floatValue], [textfieldlinscaleRGB floatValue], [textfieldsplitRGB floatValue]);
    CMLsetResponseRGB(cm, newresponse);
    CMLdestroyResponseCurve(newresponse);
//    CMLsetResponseRGB(cm, curvetype, CMLgetResponseCurveParam0(responseR), [sender floatValue], CMLgetResponseCurveParam2(responseR), CMLgetResponseCurveParam3(responseR));
  }
  [(ColorMachineApplication*)NSApp updateMachine];
}

- (IBAction)rgblinscaleChange:(NSControl*)sender{
  CMLColorMachine* cm = [(ColorMachineApplication*)NSApp getCurrentMachine];
//  const CMLResponseCurve* responseR = CMLgetResponseR(cm);
//  CMLFunctionType curvetype = CMLgetResponseCurveFunctionType(responseR);
  if      ((sender == sliderlinscaleRGB) || (sender == textfieldlinscaleRGB)){
    CMLResponseCurve* newresponse = cmlCreateResponseCurveWith4ParamsFunction(NULL, [textfieldgammaRGB floatValue], [textfieldoffsetRGB floatValue], [sender floatValue], [textfieldsplitRGB floatValue]);
    CMLsetResponseRGB(cm, newresponse);
    CMLdestroyResponseCurve(newresponse);
//    CMLsetResponseRGB(cm, curvetype, CMLgetResponseCurveParam0(responseR), CMLgetResponseCurveParam1(responseR), [sender floatValue], CMLgetResponseCurveParam3(responseR));
  }
  [(ColorMachineApplication*)NSApp updateMachine];
}

- (IBAction)rgbsplitChange:(NSControl*)sender{
  CMLColorMachine* cm = [(ColorMachineApplication*)NSApp getCurrentMachine];
//  const CMLResponseCurve* responseR = CMLgetResponseR(cm);
//  CMLFunctionType curvetype = CMLgetResponseCurveFunctionType(responseR);
  if      ((sender == slidersplitRGB) || (sender == textfieldsplitRGB)){
    CMLResponseCurve* newresponse = cmlCreateResponseCurveWith4ParamsFunction(NULL, [textfieldgammaRGB floatValue], [textfieldoffsetRGB floatValue], [textfieldlinscaleRGB floatValue], [sender floatValue]);
    CMLsetResponseRGB(cm, newresponse);
    CMLdestroyResponseCurve(newresponse);
//    CMLsetResponseRGB(cm, curvetype, CMLgetResponseCurveParam0(responseR), CMLgetResponseCurveParam1(responseR), CMLgetResponseCurveParam2(responseR), [sender floatValue]);
  }
  [(ColorMachineApplication*)NSApp updateMachine];
}

- (IBAction)graycomputationChange:(NSPopUpButton*)sender {
  CMLColorMachine* cm = [(ColorMachineApplication*)NSApp getCurrentMachine];
  CMLsetGrayComputationType(cm, (CMLGrayComputationType)[sender indexOfSelectedItem]);
  [(ColorMachineApplication*)NSApp updateMachine];
}

- (IBAction)labspaceChange:(NSPopUpButton*)sender {
  CMLColorMachine* cm = [(ColorMachineApplication*)NSApp getCurrentMachine];
  uint64 selectedindex = [sender indexOfSelectedItem];
  if(selectedindex >= CML_LAB_CUSTOM_L){selectedindex++;}
  CMLsetLabColorSpace(cm, (CMLLabColorSpaceType)selectedindex);
  [(ColorMachineApplication*)NSApp updateMachine];
}

- (IBAction)labresponseChange:(NSPopUpButton*)sender{
//  CMLColorMachine* cm = [(ColorMachineApplication*)NSApp getCurrentMachine];
//  CMLsetLabResponse(cm, (CMLFunctionType)[sender indexOfSelectedItem], 1.f, 0.f, 0.f, 0.f);
//  [(ColorMachineApplication*)NSApp updateMachine];
}

- (IBAction)labgammaChange:(NSControl*)sender{
//  CMLColorMachine* cm = [(ColorMachineApplication*)NSApp getCurrentMachine];
//  CMLsetLabResponse(cm, CML_FUNCTION_GAMMA, [sender floatValue], 0.f, 0.f, 0.f);
//  [(ColorMachineApplication*)NSApp updateMachine];
}

- (IBAction)rgbspaceChange:(NSPopUpButton*)sender {
  CMLColorMachine* cm = [(ColorMachineApplication*)NSApp getCurrentMachine];
  CMLsetRGBColorSpace(cm, (CMLRGBColorSpace)[sender indexOfSelectedItem]);
  [(ColorMachineApplication*)NSApp updateMachine];
}

- (IBAction)valueChangeT:(NSControl*)sender {
  CMLColorMachine* cm = [(ColorMachineApplication*)NSApp getCurrentMachine];
  float selectedtemp = [sender floatValue];
  if(sender == sliderT){
    float realtemp;
  //  if(selectedtemp == 1.f){realtemp = CML_INFINITY;}else{realtemp = 4000.f / (1.f - selectedtemp);}
    if(selectedtemp == 1.f){realtemp = CML_INFINITY;}else{realtemp = (2000.f + 6000.f * (-logf(1.f - selectedtemp)));}
    CMLsetIlluminationTemperature(cm, realtemp);
  }else{
    CMLsetIlluminationTemperature(cm, selectedtemp);
  }
  [(ColorMachineApplication*)NSApp updateMachine];
}

- (IBAction)valueChangeK:(NSControl*)sender {
  CMLColorMachine* cm = [(ColorMachineApplication*)NSApp getCurrentMachine];
  float K;
  float ke;
  CMLgetAdamsChromaticityValenceParameters(cm, &K, &ke);
  CMLsetAdamsChromaticityValenceParameters(cm, [sender floatValue], ke);
  [(ColorMachineApplication*)NSApp updateMachine];
}

- (IBAction)valueChangeke:(NSControl*)sender {
  CMLColorMachine* cm = [(ColorMachineApplication*)NSApp getCurrentMachine];
  float K;
  float ke;
  CMLgetAdamsChromaticityValenceParameters(cm, &K, &ke);
  CMLsetAdamsChromaticityValenceParameters(cm, K, [sender floatValue]);
  [(ColorMachineApplication*)NSApp updateMachine];
}



- (void )windowDidChangeScreenProfile:(NSNotification *)notification{
  [(ColorMachineApplication*)NSApp applicationDidChangeScreenParameters:notification];
}

//- (void)windowDidChangeBackingProperties:(NSNotification *)notification{
//  [(ColorMachineApplication*)NSApp applicationDidChangeScreenParameters:notification];
//}



- (void)updateMachine{

  CMLColorMachine* cm = [(ColorMachineApplication*)NSApp getCurrentMachine];

//  [textfieldminintegration setStringValue:[NSString stringWithFormat:@"%d", (int)(cm->getMinIntegration())]];
//  [textfieldmaxintegration setStringValue:[NSString stringWithFormat:@"%d", (int)(cm->getMaxIntegration())]];

  uint32 selecteditem;

  [observerselect             selectItemAtIndex:(int)CMLgetObserverType(cm)];
  [illuminationselect         selectItemAtIndex:(int)CMLgetIlluminationType(cm)];
//  [chromaticadaptationselect  selectItemAtIndex:(int)CMLgetChromaticAdaptation(cm)];
  [graycomputationselect      selectItemAtIndex:(int)CMLgetGrayComputationType(cm)];
  selecteditem = (int)CMLgetLabColorSpace(cm);
  if(selecteditem >= CML_LAB_CUSTOM_L){selecteditem--;}
  [labspaceselect             selectItemAtIndex:selecteditem];
  [rgbcolorspaceselect        selectItemAtIndex:(int)CMLgetRGBColorSpace(cm)];
  
  [maskselect setEnabled:(showmask | showgrid)];

  CMLIlluminationType illumination = CMLgetIlluminationType(cm);
  if((illumination == CML_ILLUMINATION_BLACKBODY) || (illumination == CML_ILLUMINATION_D_ILLUMINANT)){
    [sliderT setEnabled:true];
    [textfieldT setEnabled:true];
  }else{
    [sliderT setEnabled:false];
    [textfieldT setEnabled:false];
  }
  if(illumination == CML_ILLUMINATION_CUSTOM_SPECTRUM){
    [[illuminationselect itemAtIndex:CML_ILLUMINATION_CUSTOM_SPECTRUM] setEnabled:YES];
  }else{
    [[illuminationselect itemAtIndex:CML_ILLUMINATION_CUSTOM_SPECTRUM] setEnabled:NO];
  }

  if(illumination == CML_ILLUMINATION_CUSTOM_WHITEPOINT){
//    [whitepointY setEnabled:true];
    [whitepointx setEnabled:true];
    [whitepointy setEnabled:true];
  }else{
//    [whitepointY setEnabled:false];
    [whitepointx setEnabled:false];
    [whitepointy setEnabled:false];
  }

  switch(CMLgetLabColorSpace(cm)){
  case CML_LAB_CIELAB:
    [textL setStringValue:@"L*"];
    [texta setStringValue:@"a*"];
    [textb setStringValue:@"b*"];
    break;
  default:
    [textL setStringValue:@"L"];
    [texta setStringValue:@"a"];
    [textb setStringValue:@"b"];
  }

  if(CMLgetLabColorSpace(cm) == CML_LAB_ADAMS_CROMATIC_VALENCE){
    [sliderK setEnabled:true];
    [sliderke setEnabled:true];
    [textfieldK setEnabled:true];
    [textfieldke setEnabled:true];
  }else{
    [sliderK setEnabled:false];
    [sliderke setEnabled:false];
    [textfieldK setEnabled:false];
    [textfieldke setEnabled:false];
  }

  float temp = CMLgetIlluminationTemperature(cm);
  float slidervalue;
//  if(temp == CML_INFINITY){slidervalue = 1.f;}else{slidervalue = -((4000.f / temp) - 1.f);}
  if(temp == CML_INFINITY){slidervalue = 1.f;}else{slidervalue = 1.f - expf(-((temp - 2000.f) / 6000.f));}
  [sliderT setFloatValue:slidervalue];
  [textfieldT setStringValue:[NSString stringWithFormat:@"%5.01f", temp]];

  CMLVec3 whitePointYxy;
  CMLgetWhitePointYxy(cm, whitePointYxy);
  [whitepointY setStringValue:[NSString stringWithFormat:@"%1.01f", whitePointYxy[0]]];
  [whitepointx setStringValue:[NSString stringWithFormat:@"%1.05f", whitePointYxy[1]]];
  [whitepointy setStringValue:[NSString stringWithFormat:@"%1.05f", whitePointYxy[2]]];

  float K;
  float ke;
  CMLgetAdamsChromaticityValenceParameters(cm, &K, &ke);
  [sliderK setFloatValue:K];
  [sliderke setFloatValue:ke];
  [textfieldK setStringValue:[NSString stringWithFormat:@"%2.03f", K]];
  [textfieldke setStringValue:[NSString stringWithFormat:@"%2.03f", ke]];

  CMLVec3 primaries[3];
  CMLgetRGBPrimariesYxy(cm, primaries);
  [redprimaryY setStringValue:[NSString stringWithFormat:@"%1.05f", primaries[0][0]]];
  [redprimaryx setStringValue:[NSString stringWithFormat:@"%1.05f", primaries[0][1]]];
  [redprimaryy setStringValue:[NSString stringWithFormat:@"%1.05f", primaries[0][2]]];
  [greenprimaryY setStringValue:[NSString stringWithFormat:@"%1.05f", primaries[1][0]]];
  [greenprimaryx setStringValue:[NSString stringWithFormat:@"%1.05f", primaries[1][1]]];
  [greenprimaryy setStringValue:[NSString stringWithFormat:@"%1.05f", primaries[1][2]]];
  [blueprimaryY setStringValue:[NSString stringWithFormat:@"%1.05f", primaries[2][0]]];
  [blueprimaryx setStringValue:[NSString stringWithFormat:@"%1.05f", primaries[2][1]]];
  [blueprimaryy setStringValue:[NSString stringWithFormat:@"%1.05f", primaries[2][2]]];

  const CMLResponseCurve* responseR = CMLgetResponseR(cm);
//  [responseRGBselect selectItemAtIndex:(int)CMLgetResponseCurveFunctionType(responseR)];
  [textfieldgammaRGB setStringValue:[NSString stringWithFormat:@"%1.05f", CMLgetResponseCurveParam0(responseR)]];
  [slidergammaRGB setFloatValue:CMLgetResponseCurveParam0(responseR)];
  [textfieldoffsetRGB setStringValue:[NSString stringWithFormat:@"%1.05f", CMLgetResponseCurveParam1(responseR)]];
  [slideroffsetRGB setFloatValue:CMLgetResponseCurveParam1(responseR)];
  [textfieldlinscaleRGB setStringValue:[NSString stringWithFormat:@"%2.04f", CMLgetResponseCurveParam2(responseR)]];
  [sliderlinscaleRGB setFloatValue:CMLgetResponseCurveParam2(responseR)];
  [textfieldsplitRGB setStringValue:[NSString stringWithFormat:@"%1.05f", CMLgetResponseCurveParam3(responseR)]];
  [slidersplitRGB setFloatValue:CMLgetResponseCurveParam3(responseR)];

  [gammadisplay setNeedsDisplay:YES];
  
//  const CMLResponseCurve* responseL = CMLgetResponseL(cm);
//  float Lfunctiontype = CMLgetResponseCurveFunctionType(responseL);
//  float Lgamma = CMLgetResponseCurveParam0(responseL);
  //responsefun = cm->getResponseL();
//  [responseLselect selectItemAtIndex:(int)Lfunctiontype];
//  if(Lfunctiontype == CML_FUNCTION_GAMMA){
//    [textfieldgammaL setStringValue:[NSString stringWithFormat:@"%1.03f", Lgamma]];
//    [slidergammaL setFloatValue:Lgamma];
//  }else{
//    [textfieldgammaL setStringValue:[NSString stringWithFormat:@""]];
//  }


  CMLRGBColorSpace rgbcolorspace = CMLgetRGBColorSpace(cm);
  if(rgbcolorspace == CML_RGB_CUSTOM){
    [redprimaryx setEnabled:true];
    [redprimaryy setEnabled:true];
    [greenprimaryx setEnabled:true];
    [greenprimaryy setEnabled:true];
    [blueprimaryx setEnabled:true];
    [blueprimaryy setEnabled:true];
    [responseRGBselect setEnabled:true];
    [responseRGBselect selectItemAtIndex:0];
  }else{
    [redprimaryx setEnabled:false];
    [redprimaryy setEnabled:false];
    [greenprimaryx setEnabled:false];
    [greenprimaryy setEnabled:false];
    [blueprimaryx setEnabled:false];
    [blueprimaryy setEnabled:false];
    [responseRGBselect setEnabled:false];
    [responseRGBselect selectItemAtIndex:CMLgetRGBColorSpaceResponseCurvePreset(rgbcolorspace) + 1];
  }
//  CMLFunctionType functiontype = CMLgetResponseCurveFunctionType(responseR);
  if(rgbcolorspace == CML_RGB_CUSTOM){
    [textfieldgammaRGB setEnabled:true];
    [slidergammaRGB setEnabled:true];
    [textfieldoffsetRGB setEnabled:true];
    [slideroffsetRGB setEnabled:true];
    [textfieldlinscaleRGB setEnabled:true];
    [sliderlinscaleRGB setEnabled:true];
    [textfieldsplitRGB setEnabled:true];
    [slidersplitRGB setEnabled:true];
  }else{
    [textfieldgammaRGB setEnabled:false];
    [slidergammaRGB setEnabled:false];
    [textfieldoffsetRGB setEnabled:false];
    [slideroffsetRGB setEnabled:false];
    [textfieldlinscaleRGB setEnabled:false];
    [sliderlinscaleRGB setEnabled:false];
    [textfieldsplitRGB setEnabled:false];
    [slidersplitRGB setEnabled:false];
  }

  CMLLabColorSpaceType labcolorspace = CMLgetLabColorSpace(cm);
  if(labcolorspace == CML_LAB_CUSTOM_L){
    [responseLselect setEnabled:true];
  }else{
    [responseLselect setEnabled:false];
  }
//  if((labcolorspace == CML_LAB_CUSTOM_L) && (Lfunctiontype == CML_FUNCTION_GAMMA)){
//    [textfieldgammaL setEnabled:true];
//    [slidergammaL setEnabled:true];
//  }else{
    [textfieldgammaL setEnabled:false];
    [slidergammaL setEnabled:false];
//  }

}



- (IBAction)toggleColorSelection:(id)sender{
  if(colorselectionisExpanded){
    [self collapseColorSelection];
  }else{
    [self expandColorSelection];
  }
}

- (void)collapseColorSelection{
  if(!colorselectionisExpanded){return;}
//  [collapseexpandColorSelectionButton setTarget:self];
//  [collapseexpandColorSelectionButton setAction:@selector(expandColorSelection:)];
  [collapseexpandColorSelectionButton setImage:[NSImage imageNamed:NSImageNameRightFacingTriangleTemplate]];
  NSRect winframe = [[self window] frame];
//  float scalefactor = (float)[ColorMachineApplication getUIScaleFactorForWindow:[self window]];
  winframe.size.width -= 257.f;
  [[self window] setFrame:winframe display:YES animate:YES];
  colorselectionisExpanded = NO;
}
- (void)expandColorSelection{
  if(colorselectionisExpanded){return;}
//  [collapseexpandColorSelectionButton setTarget:self];
//  [collapseexpandColorSelectionButton setAction:@selector(collapseColorSelection:)];
  [collapseexpandColorSelectionButton setImage:[NSImage imageNamed:NSImageNameLeftFacingTriangleTemplate]];
  NSRect winframe = [[self window] frame];
//  float scalefactor = (float)[ColorMachineApplication getUIScaleFactorForWindow:[self window]];
  winframe.size.width += 257.f;
  [[self window] setFrame:winframe display:YES animate:YES];
  colorselectionisExpanded = YES;
}


@end





