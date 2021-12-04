
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
    [maskselect insertItemWithTitle:[NSString stringWithUTF8String:cmlGetColorTypeString((CMLColorType)i)] atIndex:i];
  }
  [maskselect selectItemAtIndex:(int)CML_COLOR_RGB];




  [observerselect removeAllItems];
  for(uint32 i=0; i<CML_NUMBER_OF_OBSERVERS - 1; ++i){
    [observerselect insertItemWithTitle:[NSString stringWithUTF8String:cmlGetObserverTypeString((CMLObserverType)i)] atIndex:i];
  }

  [illuminationselect setAutoenablesItems:NO];
  [illuminationselect removeAllItems];
  for(uint32 i=0; i<CML_NUMBER_OF_ILLUMINATIONS; ++i){
    [illuminationselect insertItemWithTitle:[NSString stringWithUTF8String:cmlGetIlluminationTypeString((CMLIlluminationType)i)] atIndex:i];
  }
  [[illuminationselect itemAtIndex:CML_ILLUMINATION_CUSTOM_SPECTRUM] setEnabled:FALSE];

  [rgbcolorspaceselect removeAllItems];
  for(uint32 i=0; i<CML_NUMBER_OF_RGB_SPACES; ++i){
    [rgbcolorspaceselect insertItemWithTitle:[NSString stringWithUTF8String:cmlGetRGBColorspaceString((CMLRGBColorSpace)i)] atIndex:i];
  }

  [responseRGBselect removeAllItems];
  [responseRGBselect insertItemWithTitle:@"Custom" atIndex:0];
  for(uint32 i = 1; i < CML_NUMBER_OF_RESPONSE_CURVE_PRESETS; ++i){ // Index 0 would be the undefined response.
    [responseRGBselect insertItemWithTitle:[NSString stringWithUTF8String:cmlGetRGBResponsePresetString((CMLResponseCurvePreset)i)] atIndex:i];
  }

  [labSpaceselect removeAllItems];
  uint32 curindex = 0;
  for(uint32 i=0; i<CML_NUMBER_OF_LAB_SPACES; ++i){
    if(i == CML_LAB_CUSTOM_L){continue;}
    [labSpaceselect insertItemWithTitle:[NSString stringWithUTF8String:cmlGetLabSpaceTypeString((CMLLabColorSpaceType)i)] atIndex:curindex];
    curindex++;
  }
  [responseLselect removeAllItems];
  for(uint32 i = 1; i < CML_NUMBER_OF_FUNCTION_TYPES; ++i){ // Index 0 would be the undefined function.
    [responseLselect insertItemWithTitle:[NSString stringWithUTF8String:cmlGetFunctionTypeString((CMLFunctionType)i)] atIndex:i - 1];
  }

  [graycomputationselect removeAllItems];
  for(uint32 i=0; i<CML_NUMBER_OF_GRAY_COMPUTATIONS; ++i){
    [graycomputationselect insertItemWithTitle:[NSString stringWithUTF8String:cmlGetGrayComputationTypeString((CMLGrayComputationType)i)] atIndex:i];
  }

  [chromaticAdaptationselect removeAllItems];
  for(uint32 i=0; i<CML_NUMBER_OF_CHROMATIC_ADAPTATIONS; ++i){
    [chromaticAdaptationselect insertItemWithTitle:[NSString stringWithUTF8String:cmlGetChromaticAdaptationTypeString((CMLChromaticAdaptationType)i)] atIndex:i];
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
  cmlSetObserverType(cm, (CMLObserverType)[sender indexOfSelectedItem]);
  [(ColorMachineApplication*)NSApp updateMachine];
}

- (IBAction)illuminationChange:(NSPopUpButton*)sender {
  CMLColorMachine* cm = [(ColorMachineApplication*)NSApp getCurrentMachine];
  CMLIlluminationType newillum = (CMLIlluminationType)[sender indexOfSelectedItem];
  if(newillum == CML_ILLUMINATION_CUSTOM_WHITEPOINT){
    CMLVec3 wpyxy;
    cmlGetWhitePointYxy(cm, wpyxy);
    wpyxy[0] = 1.f;
    cmlSetWhitePointYxy(cm, wpyxy);
  }else{
    cmlSetIlluminationType(cm, newillum);
  }
  [(ColorMachineApplication*)NSApp updateMachine];
}

//- (IBAction)chromaticAdaptationChange:(NSPopUpButton*)sender {
//  CMLColorMachine* cm = [(ColorMachineApplication*)NSApp getCurrentMachine];
//  CMLChromaticAdaptationType newadaptation = (CMLChromaticAdaptationType)[sender indexOfSelectedItem];
//  cmlSetChromaticAdaptation(cm, newadaptation);
//  [(ColorMachineApplication*)NSApp updateMachine];
//}

- (IBAction)whitePointChange:(NSControl*)sender{
  CMLColorMachine* cm = [(ColorMachineApplication*)NSApp getCurrentMachine];
  CMLVec3 curwhite;
  cmlGetWhitePointYxy(cm, curwhite);
  curwhite[0] = 1.f;
  if(sender == whitePointx){
    curwhite[1] = [sender floatValue];
  }else if(sender == whitePointy){
    curwhite[2] = [sender floatValue];
  }else{
//    curwhite[0] = [sender floatValue];
  }
  cmlSetWhitePointYxy(cm, curwhite);
  [(ColorMachineApplication*)NSApp updateMachine];
}

- (IBAction)rgbprimariesChange:(NSControl*)sender{
  CMLColorMachine* cm = [(ColorMachineApplication*)NSApp getCurrentMachine];
  CMLVec3 primaries[3];
  cmlGetRGBPrimariesYxy(cm, primaries);
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
  cmlSetRGBPrimariesYxy(cm, primaries);
  [(ColorMachineApplication*)NSApp updateMachine];
}

- (IBAction)rgbResponseChange:(NSPopUpButton*)sender{
  CMLColorMachine* cm = [(ColorMachineApplication*)NSApp getCurrentMachine];
//  const CMLResponseCurve* responseR = cmlGetResponseR(cm);
  if      (sender == responseRGBselect){
    NSInteger selectedItem = [responseRGBselect indexOfSelectedItem];
    if(selectedItem == 0){return;}  // custom response
    CMLResponseCurve* newResponse = cmlAllocResponseCurve();
    cmlInitResponseCurveWithPreset(newResponse, (CMLResponseCurvePreset)selectedItem);
//    CMLResponseCurve* newResponse = cmlInitResponseCurveWith4ParamsFunction(NULL, [textfieldgammaRGB floatValue], [textfieldoffsetRGB floatValue], [textfieldlinScaleRGB floatValue], [textfieldsplitRGB floatValue]);
    cmlSetResponseRGB(cm, newResponse);
    cmlClearResponseCurve(newResponse);
    free(newResponse);
//    cmlSetResponseRGB(cm, (CMLFunctionType)[sender indexOfSelectedItem] + 1, cmlGetResponseCurveParam0(responseR), cmlGetResponseCurveParam1(responseR), cmlGetResponseCurveParam2(responseR), cmlGetResponseCurveParam3(responseR));
  }
  [(ColorMachineApplication*)NSApp updateMachine];
}

- (IBAction)rgbGammaChange:(NSControl*)sender{
  CMLColorMachine* cm = [(ColorMachineApplication*)NSApp getCurrentMachine];
  if      ((sender == slidergammaRGB) || (sender == textfieldgammaRGB)){
    CMLResponseCurve* newResponse = cmlAllocResponseCurve();
    cmlInitResponseCurveWith4ParamsFunction(newResponse, [sender floatValue], [textfieldoffsetRGB floatValue], [textfieldlinScaleRGB floatValue], [textfieldsplitRGB floatValue]);
    cmlSetResponseRGB(cm, newResponse);
    cmlClearResponseCurve(newResponse);
    free(newResponse);
  }
  [(ColorMachineApplication*)NSApp updateMachine];
}

- (IBAction)rgbOffsetChange:(NSControl*)sender{
  CMLColorMachine* cm = [(ColorMachineApplication*)NSApp getCurrentMachine];
  if      ((sender == slideroffsetRGB) || (sender == textfieldoffsetRGB)){
    CMLResponseCurve* newResponse = cmlAllocResponseCurve();
    cmlInitResponseCurveWith4ParamsFunction(newResponse, [textfieldgammaRGB floatValue], [sender floatValue], [textfieldlinScaleRGB floatValue], [textfieldsplitRGB floatValue]);
    cmlSetResponseRGB(cm, newResponse);
    cmlClearResponseCurve(newResponse);
    free(newResponse);
  }
  [(ColorMachineApplication*)NSApp updateMachine];
}

- (IBAction)rgbLinScaleChange:(NSControl*)sender{
  CMLColorMachine* cm = [(ColorMachineApplication*)NSApp getCurrentMachine];
  if      ((sender == sliderlinScaleRGB) || (sender == textfieldlinScaleRGB)){
    CMLResponseCurve* newResponse = cmlAllocResponseCurve();
    cmlInitResponseCurveWith4ParamsFunction(newResponse, [textfieldgammaRGB floatValue], [textfieldoffsetRGB floatValue], [sender floatValue], [textfieldsplitRGB floatValue]);
    cmlSetResponseRGB(cm, newResponse);
    cmlClearResponseCurve(newResponse);
    free(newResponse);
  }
  [(ColorMachineApplication*)NSApp updateMachine];
}

- (IBAction)rgbSplitChange:(NSControl*)sender{
  CMLColorMachine* cm = [(ColorMachineApplication*)NSApp getCurrentMachine];
  if      ((sender == slidersplitRGB) || (sender == textfieldsplitRGB)){
    CMLResponseCurve* newResponse = cmlAllocResponseCurve();
    cmlInitResponseCurveWith4ParamsFunction(newResponse, [textfieldgammaRGB floatValue], [textfieldoffsetRGB floatValue], [textfieldlinScaleRGB floatValue], [sender floatValue]);
    cmlSetResponseRGB(cm, newResponse);
    cmlClearResponseCurve(newResponse);
    free(newResponse);
  }
  [(ColorMachineApplication*)NSApp updateMachine];
}

- (IBAction)graycomputationChange:(NSPopUpButton*)sender {
  CMLColorMachine* cm = [(ColorMachineApplication*)NSApp getCurrentMachine];
  cmlSetGrayComputationType(cm, (CMLGrayComputationType)[sender indexOfSelectedItem]);
  [(ColorMachineApplication*)NSApp updateMachine];
}

- (IBAction)labSpaceChange:(NSPopUpButton*)sender {
  CMLColorMachine* cm = [(ColorMachineApplication*)NSApp getCurrentMachine];
  uint64 selectedindex = [sender indexOfSelectedItem];
  if(selectedindex >= CML_LAB_CUSTOM_L){selectedindex++;}
  cmlSetLabColorSpace(cm, (CMLLabColorSpaceType)selectedindex);
  [(ColorMachineApplication*)NSApp updateMachine];
}

- (IBAction)labresponseChange:(NSPopUpButton*)sender{
//  CMLColorMachine* cm = [(ColorMachineApplication*)NSApp getCurrentMachine];
//  cmlSetLabResponse(cm, (CMLFunctionType)[sender indexOfSelectedItem] + 1, 1.f, 0.f, 0.f, 0.f);
//  [(ColorMachineApplication*)NSApp updateMachine];
}

- (IBAction)labgammaChange:(NSControl*)sender{
//  CMLColorMachine* cm = [(ColorMachineApplication*)NSApp getCurrentMachine];
//  cmlSetLabResponse(cm, CML_FUNCTION_GAMMA, [sender floatValue], 0.f, 0.f, 0.f);
//  [(ColorMachineApplication*)NSApp updateMachine];
}

- (IBAction)rgbSpaceChange:(NSPopUpButton*)sender {
  CMLColorMachine* cm = [(ColorMachineApplication*)NSApp getCurrentMachine];
  cmlSetRGBColorSpace(cm, (CMLRGBColorSpace)[sender indexOfSelectedItem]);
  [(ColorMachineApplication*)NSApp updateMachine];
}

- (IBAction)valueChangeT:(NSControl*)sender {
  CMLColorMachine* cm = [(ColorMachineApplication*)NSApp getCurrentMachine];
  float selectedtemp = [sender floatValue];
  if(sender == sliderT){
    float realtemp;
  //  if(selectedtemp == 1.f){realtemp = CML_INFINITY;}else{realtemp = 4000.f / (1.f - selectedtemp);}
    if(selectedtemp == 1.f){realtemp = CML_INFINITY;}else{realtemp = (2000.f + 6000.f * (-logf(1.f - selectedtemp)));}
    cmlSetIlluminationTemperature(cm, realtemp);
  }else{
    cmlSetIlluminationTemperature(cm, selectedtemp);
  }
  [(ColorMachineApplication*)NSApp updateMachine];
}

- (IBAction)valueChangeK:(NSControl*)sender {
  CMLColorMachine* cm = [(ColorMachineApplication*)NSApp getCurrentMachine];
  float K;
  float ke;
  cmlGetAdamsChromaticityValenceParameters(cm, &K, &ke);
  cmlSetAdamsChromaticityValenceParameters(cm, [sender floatValue], ke);
  [(ColorMachineApplication*)NSApp updateMachine];
}

- (IBAction)valueChangeke:(NSControl*)sender {
  CMLColorMachine* cm = [(ColorMachineApplication*)NSApp getCurrentMachine];
  float K;
  float ke;
  cmlGetAdamsChromaticityValenceParameters(cm, &K, &ke);
  cmlSetAdamsChromaticityValenceParameters(cm, K, [sender floatValue]);
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

  uint32 selectedItem;

  [observerselect             selectItemAtIndex:(int)cmlGetObserverType(cm)];
  [illuminationselect         selectItemAtIndex:(int)cmlGetIlluminationType(cm)];
//  [chromaticAdaptationselect  selectItemAtIndex:(int)cmlGetChromaticAdaptation(cm)];
  [graycomputationselect      selectItemAtIndex:(int)cmlGetGrayComputationType(cm)];
  selectedItem = (int)cmlGetLabColorSpace(cm);
  if(selectedItem >= CML_LAB_CUSTOM_L){selectedItem--;}
  [labSpaceselect             selectItemAtIndex:selectedItem];
  [rgbcolorspaceselect        selectItemAtIndex:(int)cmlGetRGBColorSpace(cm)];
  
  [maskselect setEnabled:(showmask | showgrid)];

  CMLIlluminationType illumination = cmlGetIlluminationType(cm);
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
//    [whitePointY setEnabled:true];
    [whitePointx setEnabled:true];
    [whitePointy setEnabled:true];
  }else{
//    [whitePointY setEnabled:false];
    [whitePointx setEnabled:false];
    [whitePointy setEnabled:false];
  }

  switch(cmlGetLabColorSpace(cm)){
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

  if(cmlGetLabColorSpace(cm) == CML_LAB_ADAMS_CROMATIC_VALENCE){
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

  float temp = cmlGetIlluminationTemperature(cm);
  float slidervalue;
//  if(temp == CML_INFINITY){slidervalue = 1.f;}else{slidervalue = -((4000.f / temp) - 1.f);}
  if(temp == CML_INFINITY){slidervalue = 1.f;}else{slidervalue = 1.f - expf(-((temp - 2000.f) / 6000.f));}
  [sliderT setFloatValue:slidervalue];
  [textfieldT setStringValue:[NSString stringWithFormat:@"%5.01f", temp]];

  CMLVec3 whitePointYxy;
  cmlGetWhitePointYxy(cm, whitePointYxy);
  [whitePointY setStringValue:[NSString stringWithFormat:@"%1.01f", whitePointYxy[0]]];
  [whitePointx setStringValue:[NSString stringWithFormat:@"%1.05f", whitePointYxy[1]]];
  [whitePointy setStringValue:[NSString stringWithFormat:@"%1.05f", whitePointYxy[2]]];

  float K;
  float ke;
  cmlGetAdamsChromaticityValenceParameters(cm, &K, &ke);
  [sliderK setFloatValue:K];
  [sliderke setFloatValue:ke];
  [textfieldK setStringValue:[NSString stringWithFormat:@"%2.03f", K]];
  [textfieldke setStringValue:[NSString stringWithFormat:@"%2.03f", ke]];

  CMLVec3 primaries[3];
  cmlGetRGBPrimariesYxy(cm, primaries);
  [redprimaryY setStringValue:[NSString stringWithFormat:@"%1.05f", primaries[0][0]]];
  [redprimaryx setStringValue:[NSString stringWithFormat:@"%1.05f", primaries[0][1]]];
  [redprimaryy setStringValue:[NSString stringWithFormat:@"%1.05f", primaries[0][2]]];
  [greenprimaryY setStringValue:[NSString stringWithFormat:@"%1.05f", primaries[1][0]]];
  [greenprimaryx setStringValue:[NSString stringWithFormat:@"%1.05f", primaries[1][1]]];
  [greenprimaryy setStringValue:[NSString stringWithFormat:@"%1.05f", primaries[1][2]]];
  [blueprimaryY setStringValue:[NSString stringWithFormat:@"%1.05f", primaries[2][0]]];
  [blueprimaryx setStringValue:[NSString stringWithFormat:@"%1.05f", primaries[2][1]]];
  [blueprimaryy setStringValue:[NSString stringWithFormat:@"%1.05f", primaries[2][2]]];

  const CMLResponseCurve* responseR = cmlGetResponseR(cm);
  [textfieldgammaRGB setStringValue:[NSString stringWithFormat:@"%1.05f", cmlGetResponseCurveParam0(responseR)]];
  [slidergammaRGB setFloatValue:cmlGetResponseCurveParam0(responseR)];
  [textfieldoffsetRGB setStringValue:[NSString stringWithFormat:@"%1.05f", cmlGetResponseCurveParam1(responseR)]];
  [slideroffsetRGB setFloatValue:cmlGetResponseCurveParam1(responseR)];
  [textfieldlinScaleRGB setStringValue:[NSString stringWithFormat:@"%2.04f", cmlGetResponseCurveParam2(responseR)]];
  [sliderlinScaleRGB setFloatValue:cmlGetResponseCurveParam2(responseR)];
  [textfieldsplitRGB setStringValue:[NSString stringWithFormat:@"%1.05f", cmlGetResponseCurveParam3(responseR)]];
  [slidersplitRGB setFloatValue:cmlGetResponseCurveParam3(responseR)];

  [gammadisplay setNeedsDisplay:YES];
  
//  const CMLResponseCurve* responseL = cmlGetResponseL(cm);
//  float LfunctionType = cmlGetResponseCurveFunctionType(responseL);
//  float Lgamma = cmlGetResponseCurveParam0(responseL);
  //responsefun = cm->getResponseL();
//  [responseLselect selectItemAtIndex:(int)LfunctionType];
//  if(LfunctionType == CML_FUNCTION_GAMMA){
//    [textfieldgammaL setStringValue:[NSString stringWithFormat:@"%1.03f", Lgamma]];
//    [slidergammaL setFloatValue:Lgamma];
//  }else{
//    [textfieldgammaL setStringValue:[NSString stringWithFormat:@""]];
//  }


  CMLRGBColorSpace rgbcolorspace = cmlGetRGBColorSpace(cm);
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
    [responseRGBselect selectItemAtIndex:cmlGetRGBColorSpaceResponseCurvePreset(rgbcolorspace) + 1];
  }
  if(rgbcolorspace == CML_RGB_CUSTOM){
    [textfieldgammaRGB setEnabled:true];
    [slidergammaRGB setEnabled:true];
    [textfieldoffsetRGB setEnabled:true];
    [slideroffsetRGB setEnabled:true];
    [textfieldlinScaleRGB setEnabled:true];
    [sliderlinScaleRGB setEnabled:true];
    [textfieldsplitRGB setEnabled:true];
    [slidersplitRGB setEnabled:true];
  }else{
    [textfieldgammaRGB setEnabled:false];
    [slidergammaRGB setEnabled:false];
    [textfieldoffsetRGB setEnabled:false];
    [slideroffsetRGB setEnabled:false];
    [textfieldlinScaleRGB setEnabled:false];
    [sliderlinScaleRGB setEnabled:false];
    [textfieldsplitRGB setEnabled:false];
    [slidersplitRGB setEnabled:false];
  }

  CMLLabColorSpaceType labcolorspace = cmlGetLabColorSpace(cm);
  if(labcolorspace == CML_LAB_CUSTOM_L){
    [responseLselect setEnabled:true];
  }else{
    [responseLselect setEnabled:false];
  }
//  if((labcolorspace == CML_LAB_CUSTOM_L) && (LfunctionType == CML_FUNCTION_GAMMA)){
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





