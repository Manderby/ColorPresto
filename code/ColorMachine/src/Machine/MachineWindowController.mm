
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






@implementation MachineWindowController

- (void)awakeFromNib{

//  [[self window] setColorSpace:[NSColorSpace deviceRGBColorSpace]];
//  [[self window] setColorSpace:[NSColorSpace sRGBColorSpace]];
  
  colorSelectionIsExpanded = YES;
  [self collapseColorSelection];
  
  lastSelectedChannel = 0;

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
  for(uint32 i=0; i<CML_COLOR_COUNT; ++i){
    if((CMLColorType)i >= CML_COLOR_CMYK){continue;}
    [maskselect insertItemWithTitle:[NSString stringWithUTF8String:cmlGetColorTypeString((CMLColorType)i)] atIndex:i];
  }
  [maskselect selectItemAtIndex:(int)CML_COLOR_RGB];




  [observerSelect removeAllItems];
  for(uint32 i=0; i<CML_OBSERVER_COUNT - 1; ++i){
    [observerSelect insertItemWithTitle:[NSString stringWithUTF8String:cmlGetObserverTypeString((CMLObserverType)i)] atIndex:i];
  }

  [illuminationSelect setAutoenablesItems:NO];
  [illuminationSelect removeAllItems];
  for(uint32 i=0; i<CML_ILLUMINATION_COUNT; ++i){
    [illuminationSelect insertItemWithTitle:[NSString stringWithUTF8String:cmlGetIlluminationTypeString((CMLIlluminationType)i)] atIndex:i];
  }
  [[illuminationSelect itemAtIndex:CML_ILLUMINATION_CUSTOM_SPECTRUM] setEnabled:FALSE];

  [rgbColorSpaceSelect removeAllItems];
  for(uint32 i=0; i<CML_RGB_COUNT; ++i){
    [rgbColorSpaceSelect insertItemWithTitle:[NSString stringWithUTF8String:cmlGetRGBColorSpaceTypeString((CMLRGBColorSpaceType)i)] atIndex:i];
  }

  [responseRGBSelect removeAllItems];
  for(uint32 i = 1; i < CML_RESPONSE_COUNT; ++i){ // Index 0 would be the undefined response.
    [responseRGBSelect insertItemWithTitle:[NSString stringWithUTF8String:cmlGetRGBResponseTypeString((CMLResponseCurveType)i)] atIndex:i - 1];
  }

  [labSpaceSelect removeAllItems];
  uint32 curindex = 0;
  for(uint32 i=0; i<CML_LAB_COUNT; ++i){
    if(i == CML_LAB_CUSTOM_L){continue;}
    [labSpaceSelect insertItemWithTitle:[NSString stringWithUTF8String:cmlGetLabSpaceTypeString((CMLLabColorSpaceType)i)] atIndex:curindex];
    curindex++;
  }
  [responseLSelect removeAllItems];
  for(uint32 i = 1; i < CML_FUNCTION_COUNT; ++i){ // Index 0 would be the undefined function.
    [responseLSelect insertItemWithTitle:[NSString stringWithUTF8String:cmlGetFunctionTypeString((CMLFunctionType)i)] atIndex:i - 1];
  }

  [grayComputationSelect removeAllItems];
  for(uint32 i=0; i<CML_GRAY_COUNT; ++i){
    [grayComputationSelect insertItemWithTitle:[NSString stringWithUTF8String:cmlGetGrayComputationTypeString((CMLGrayComputationType)i)] atIndex:i];
  }

  [chromaticAdaptationSelect removeAllItems];
  for(uint32 i=0; i<CML_CHROMATIC_ADAPTATION_COUNT; ++i){
    [chromaticAdaptationSelect insertItemWithTitle:[NSString stringWithUTF8String:cmlGetChromaticAdaptationTypeString((CMLChromaticAdaptationType)i)] atIndex:i];
  }

}



- (IBAction)maskStateChange:(NSButton*)sender {
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
  CMLIlluminationType newIllum = (CMLIlluminationType)[sender indexOfSelectedItem];
  if(newIllum == CML_ILLUMINATION_CUSTOM_WHITEPOINT){
    CMLVec3 wpyxy;
    cmlCpy3(wpyxy, cmlGetReferenceWhitePointYxy(cm));
    wpyxy[0] = 1.f;
    cmlSetReferenceWhitePointYxy(cm, wpyxy);
  }else{
    cmlSetIlluminationType(cm, newIllum);
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
  cmlCpy3(curwhite, cmlGetReferenceWhitePointYxy(cm));
  curwhite[0] = 1.f;
  if(sender == whitePointx){
    curwhite[1] = [sender floatValue];
  }else if(sender == whitePointy){
    curwhite[2] = [sender floatValue];
  }else{
//    curwhite[0] = [sender floatValue];
  }
  cmlSetReferenceWhitePointYxy(cm, curwhite);
  [(ColorMachineApplication*)NSApp updateMachine];
}

- (IBAction)rgbprimariesChange:(NSControl*)sender{
  CMLColorMachine* cm = [(ColorMachineApplication*)NSApp getCurrentMachine];
  CMLVec3 primaries[3];
  cmlGetRGBPrimariesYxy(cm, primaries);
  if(sender == redPrimaryx){
    primaries[0][1] = [sender floatValue];
  }else if(sender == redPrimaryy){
    primaries[0][2] = [sender floatValue];
  }else if(sender == greenPrimaryx){
    primaries[1][1] = [sender floatValue];
  }else if(sender == greenPrimaryy){
    primaries[1][2] = [sender floatValue];
  }else if(sender == bluePrimaryx){
    primaries[2][1] = [sender floatValue];
  }else if(sender == bluePrimaryy){
    primaries[2][2] = [sender floatValue];
  }
  cmlSetRGBPrimariesYxy(cm, primaries);
  [(ColorMachineApplication*)NSApp updateMachine];
}

- (IBAction)rgbResponseChannelChange:(NSPopUpButton*)sender{
  CMLColorMachine* cm = [(ColorMachineApplication*)NSApp getCurrentMachine];
  size_t newSelectedChannel = [responseChannelSelect indexOfSelectedItem];
  if(lastSelectedChannel > 0 && newSelectedChannel == 0){
    CMLResponseCurve* newResponse = cmlAllocResponseCurve();
    switch(lastSelectedChannel){
    case 0: break;
    case 1: cmlInitResponseCurveWithCopy(newResponse, cmlGetResponseR(cm)); break;
    case 2: cmlInitResponseCurveWithCopy(newResponse, cmlGetResponseG(cm)); break;
    case 3: cmlInitResponseCurveWithCopy(newResponse, cmlGetResponseB(cm)); break;
    }
    cmlSetResponseRGB(cm, newResponse);
  }
  lastSelectedChannel = newSelectedChannel;
  [(ColorMachineApplication*)NSApp updateMachine];
}

- (IBAction)rgbResponseChange:(NSPopUpButton*)sender{
  CMLColorMachine* cm = [(ColorMachineApplication*)NSApp getCurrentMachine];

  if(sender == responseRGBSelect){
    CMLResponseCurveType selectedItem = (CMLResponseCurveType)([responseRGBSelect indexOfSelectedItem] + 1);  // zero would be the undefined type.
    CMLResponseCurve* newResponse = cmlAllocResponseCurve();
    if(selectedItem == CML_RESPONSE_CUSTOM_GAMMA){
      const GammaLinearInputParameters* inputParams = cmlGetCustomGammaLinearParametersR(cm);
      cmlInitResponseCurveWithCustomGamma(newResponse, inputParams->gamma);
    }else if(selectedItem == CML_RESPONSE_CUSTOM_GAMMA_LINEAR){
      const GammaLinearInputParameters* inputParams = cmlGetCustomGammaLinearParametersR(cm);
      cmlInitResponseCurveWithCustomGammaLinear(newResponse, inputParams->gamma, inputParams->offset, inputParams->linScale, inputParams->split);
    }else{
      cmlInitResponseCurveWithType(newResponse, selectedItem);
    }

    switch(lastSelectedChannel){
    case 0: cmlSetResponseRGB(cm, newResponse); break;
    case 1: cmlSetResponseR(cm, newResponse); break;
    case 2: cmlSetResponseG(cm, newResponse); break;
    case 3: cmlSetResponseB(cm, newResponse); break;
    }

    cmlClearResponseCurve(newResponse);
    free(newResponse);
  }
  [(ColorMachineApplication*)NSApp updateMachine];
}

- (IBAction)rgbGammaChange:(NSControl*)sender{
  CMLColorMachine* cm = [(ColorMachineApplication*)NSApp getCurrentMachine];
  if((sender == sliderGammaRGB) || (sender == textFieldGammaRGB)){
    CMLResponseCurveType selectedItem = (CMLResponseCurveType)([responseRGBSelect indexOfSelectedItem] + 1);  // zero would be the undefined type.
    float gamma = [sender floatValue];
    
    GammaLinearInputParameters inputParams = {gamma, [textFieldOffsetRGB floatValue], [textFieldLinScaleRGB floatValue], [textFieldSplitRGB floatValue]};
    cmlSetCustomGammaLinearParametersRGB(cm, &inputParams);

    CMLResponseCurve* newResponse = cmlAllocResponseCurve();
    if(selectedItem == CML_RESPONSE_CUSTOM_GAMMA){
      cmlInitResponseCurveWithCustomGamma(newResponse, gamma);
    }else if(selectedItem == CML_RESPONSE_CUSTOM_GAMMA_LINEAR){
      cmlInitResponseCurveWithCustomGammaLinear(newResponse, gamma, [textFieldOffsetRGB floatValue], [textFieldLinScaleRGB floatValue], [textFieldSplitRGB floatValue]);
    }

    switch(lastSelectedChannel){
    case 0: cmlSetResponseRGB(cm, newResponse); break;
    case 1: cmlSetResponseR(cm, newResponse); break;
    case 2: cmlSetResponseG(cm, newResponse); break;
    case 3: cmlSetResponseB(cm, newResponse); break;
    }

    cmlClearResponseCurve(newResponse);
    free(newResponse);
  }
  [(ColorMachineApplication*)NSApp updateMachine];
}

- (IBAction)rgbOffsetChange:(NSControl*)sender{
  CMLColorMachine* cm = [(ColorMachineApplication*)NSApp getCurrentMachine];
  if((sender == sliderOffsetRGB) || (sender == textFieldOffsetRGB)){
    CMLResponseCurveType selectedItem = (CMLResponseCurveType)([responseRGBSelect indexOfSelectedItem] + 1);  // zero would be the undefined type.
    float offset = [sender floatValue];
    
    GammaLinearInputParameters inputParams = {[textFieldGammaRGB floatValue], offset, [textFieldLinScaleRGB floatValue], [textFieldSplitRGB floatValue]};
    cmlSetCustomGammaLinearParametersRGB(cm, &inputParams);

    CMLResponseCurve* newResponse = cmlAllocResponseCurve();
    if(selectedItem == CML_RESPONSE_CUSTOM_GAMMA_LINEAR){
      cmlInitResponseCurveWithCustomGammaLinear(newResponse, [textFieldGammaRGB floatValue], offset, [textFieldLinScaleRGB floatValue], [textFieldSplitRGB floatValue]);
    }

    switch(lastSelectedChannel){
    case 0: cmlSetResponseRGB(cm, newResponse); break;
    case 1: cmlSetResponseR(cm, newResponse); break;
    case 2: cmlSetResponseG(cm, newResponse); break;
    case 3: cmlSetResponseB(cm, newResponse); break;
    }

    cmlClearResponseCurve(newResponse);
    free(newResponse);
  }
  [(ColorMachineApplication*)NSApp updateMachine];
}

- (IBAction)rgbLinScaleChange:(NSControl*)sender{
  CMLColorMachine* cm = [(ColorMachineApplication*)NSApp getCurrentMachine];
  if((sender == sliderLinScaleRGB) || (sender == textFieldLinScaleRGB)){
    CMLResponseCurveType selectedItem = (CMLResponseCurveType)([responseRGBSelect indexOfSelectedItem] + 1);  // zero would be the undefined type.
    float scale = [sender floatValue];
    
    GammaLinearInputParameters inputParams = {[textFieldGammaRGB floatValue], [textFieldOffsetRGB floatValue], scale, [textFieldSplitRGB floatValue]};
    cmlSetCustomGammaLinearParametersRGB(cm, &inputParams);

    CMLResponseCurve* newResponse = cmlAllocResponseCurve();
    if(selectedItem == CML_RESPONSE_CUSTOM_GAMMA_LINEAR){
      cmlInitResponseCurveWithCustomGammaLinear(newResponse, [textFieldGammaRGB floatValue], [textFieldOffsetRGB floatValue], scale, [textFieldSplitRGB floatValue]);
    }

    switch(lastSelectedChannel){
    case 0: cmlSetResponseRGB(cm, newResponse); break;
    case 1: cmlSetResponseR(cm, newResponse); break;
    case 2: cmlSetResponseG(cm, newResponse); break;
    case 3: cmlSetResponseB(cm, newResponse); break;
    }

    cmlClearResponseCurve(newResponse);
    free(newResponse);
  }
  [(ColorMachineApplication*)NSApp updateMachine];
}

- (IBAction)rgbSplitChange:(NSControl*)sender{
  CMLColorMachine* cm = [(ColorMachineApplication*)NSApp getCurrentMachine];
  if((sender == sliderSplitRGB) || (sender == textFieldSplitRGB)){
    CMLResponseCurveType selectedItem = (CMLResponseCurveType)([responseRGBSelect indexOfSelectedItem] + 1);  // zero would be the undefined type.
    float split = [sender floatValue];
    
    GammaLinearInputParameters inputParams = {[textFieldGammaRGB floatValue], [textFieldOffsetRGB floatValue], [textFieldLinScaleRGB floatValue], split};
    cmlSetCustomGammaLinearParametersRGB(cm, &inputParams);

    CMLResponseCurve* newResponse = cmlAllocResponseCurve();
    if(selectedItem == CML_RESPONSE_CUSTOM_GAMMA_LINEAR){
      cmlInitResponseCurveWithCustomGammaLinear(newResponse, [textFieldGammaRGB floatValue], [textFieldOffsetRGB floatValue], [textFieldLinScaleRGB floatValue], split);
    }

    switch(lastSelectedChannel){
    case 0: cmlSetResponseRGB(cm, newResponse); break;
    case 1: cmlSetResponseR(cm, newResponse); break;
    case 2: cmlSetResponseG(cm, newResponse); break;
    case 3: cmlSetResponseB(cm, newResponse); break;
    }

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
  cmlSetRGBColorSpaceType(cm, (CMLRGBColorSpaceType)[sender indexOfSelectedItem]);
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

//  [textFieldminintegration setStringValue:[NSString stringWithFormat:@"%d", (int)(cm->getMinIntegration())]];
//  [textFieldmaxintegration setStringValue:[NSString stringWithFormat:@"%d", (int)(cm->getMaxIntegration())]];

  uint32 selectedItem;

  CMLIlluminationType illuminationType = cmlGetReferenceIlluminationType(cm);

  [observerSelect             selectItemAtIndex:(int)cmlGetObserverType(cm)];
  [illuminationSelect         selectItemAtIndex:(int)illuminationType];
//  [chromaticAdaptationSelect  selectItemAtIndex:(int)cmlGetChromaticAdaptation(cm)];
  [grayComputationSelect      selectItemAtIndex:(int)cmlGetGrayComputationType(cm)];
  selectedItem = (int)cmlGetLabColorSpace(cm);
  if(selectedItem >= CML_LAB_CUSTOM_L){selectedItem--;}
  [labSpaceSelect             selectItemAtIndex:selectedItem];
  [rgbColorSpaceSelect        selectItemAtIndex:(int)cmlGetRGBColorSpaceType(cm)];
  
  [maskselect setEnabled:(showmask | showgrid)];

  if((illuminationType == CML_ILLUMINATION_BLACKBODY) || (illuminationType == CML_ILLUMINATION_D_ILLUMINANT)){
    [sliderT setEnabled:true];
    [textFieldT setEnabled:true];
  }else{
    [sliderT setEnabled:false];
    [textFieldT setEnabled:false];
  }
  if(illuminationType == CML_ILLUMINATION_CUSTOM_SPECTRUM){
    [[illuminationSelect itemAtIndex:CML_ILLUMINATION_CUSTOM_SPECTRUM] setEnabled:YES];
  }else{
    [[illuminationSelect itemAtIndex:CML_ILLUMINATION_CUSTOM_SPECTRUM] setEnabled:NO];
  }

  if(illuminationType == CML_ILLUMINATION_CUSTOM_WHITEPOINT){
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
    [textFieldK setEnabled:true];
    [textFieldke setEnabled:true];
  }else{
    [sliderK setEnabled:false];
    [sliderke setEnabled:false];
    [textFieldK setEnabled:false];
    [textFieldke setEnabled:false];
  }

  float temp = cmlGetIlluminationTemperature(cm);
  if(temp == 0.f){
    CMLVec3 whitePointYuv;
    cmlYupvpToYuv(cm, whitePointYuv, cmlGetReferenceWhitePointYupvp(cm), 1);
    temp = cmlGetCorrelatedColorTemperature(whitePointYuv);
  }
  
  float slidervalue;
//  if(temp == CML_INFINITY){slidervalue = 1.f;}else{slidervalue = -((4000.f / temp) - 1.f);}
  if(temp == CML_INFINITY){slidervalue = 1.f;}else{slidervalue = 1.f - expf(-((temp - 2000.f) / 6000.f));}
  [sliderT setFloatValue:slidervalue];
  [textFieldT setStringValue:[NSString stringWithFormat:@"%5.01f", temp]];

  const float* whitePointYxy = cmlGetReferenceWhitePointYxy(cm);
  [whitePointY setStringValue:[NSString stringWithFormat:@"%1.01f", whitePointYxy[0]]];
  [whitePointx setStringValue:[NSString stringWithFormat:@"%1.05f", whitePointYxy[1]]];
  [whitePointy setStringValue:[NSString stringWithFormat:@"%1.05f", whitePointYxy[2]]];

  float K;
  float ke;
  cmlGetAdamsChromaticityValenceParameters(cm, &K, &ke);
  [sliderK setFloatValue:K];
  [sliderke setFloatValue:ke];
  [textFieldK setStringValue:[NSString stringWithFormat:@"%2.03f", K]];
  [textFieldke setStringValue:[NSString stringWithFormat:@"%2.03f", ke]];

  CMLVec3 primaries[3];
  cmlGetRGBPrimariesYxy(cm, primaries);
  [redPrimaryY setStringValue:[NSString stringWithFormat:@"%1.05f", primaries[0][0]]];
  [redPrimaryx setStringValue:[NSString stringWithFormat:@"%1.05f", primaries[0][1]]];
  [redPrimaryy setStringValue:[NSString stringWithFormat:@"%1.05f", primaries[0][2]]];
  [greenPrimaryY setStringValue:[NSString stringWithFormat:@"%1.05f", primaries[1][0]]];
  [greenPrimaryx setStringValue:[NSString stringWithFormat:@"%1.05f", primaries[1][1]]];
  [greenPrimaryy setStringValue:[NSString stringWithFormat:@"%1.05f", primaries[1][2]]];
  [bluePrimaryY setStringValue:[NSString stringWithFormat:@"%1.05f", primaries[2][0]]];
  [bluePrimaryx setStringValue:[NSString stringWithFormat:@"%1.05f", primaries[2][1]]];
  [bluePrimaryy setStringValue:[NSString stringWithFormat:@"%1.05f", primaries[2][2]]];

  [gammaDisplay setNeedsDisplay:YES];
  
  CMLRGBColorSpaceType type = cmlGetRGBColorSpaceType(cm);
  CMLResponseCurveType responseTypes[3];
  cmlGetRGBResponseTypes(cm, responseTypes);
  size_t colorIndex = lastSelectedChannel;
  if(colorIndex > 0){ colorIndex--; }
  
  [responseRGBSelect selectItemAtIndex:responseTypes[colorIndex] - 1]; // zero would be the undefined response.
  CMLBool customRGB = type == CML_RGB_CUSTOM;

  [responseChannelSelect setEnabled:customRGB];
  [responseRGBSelect setEnabled:customRGB];
  [redPrimaryx   setEnabled:customRGB];
  [redPrimaryy   setEnabled:customRGB];
  [greenPrimaryx setEnabled:customRGB];
  [greenPrimaryy setEnabled:customRGB];
  [bluePrimaryx  setEnabled:customRGB];
  [bluePrimaryy  setEnabled:customRGB];
  
  float gamma = -1.;
  float offset = -1.;
  float linScale = -1.;
  float split = -1.;

  switch(responseTypes[colorIndex]){
  case CML_RESPONSE_LINEAR:
    gamma = 1.0;
    break;
  case CML_RESPONSE_GAMMA_1_8:
    gamma = 1.8;
    break;
  case CML_RESPONSE_GAMMA_1_9:
    gamma = 1.9;
    break;
  case CML_RESPONSE_GAMMA_2_0:
    gamma = 2.0;
    break;
  case CML_RESPONSE_GAMMA_ADOBE_98:
    gamma = 2.f + 51.f / 256.f;
    break;
  case CML_RESPONSE_GAMMA_2_2:
    gamma = 2.2;
    break;
  case CML_RESPONSE_GAMMA_LINEAR_REC_BT_10BIT:
    gamma = 1.f / 0.45f;
    offset = 0.099f;
    linScale = 4.5f;
    split = 0.018f;
    break;
  case CML_RESPONSE_GAMMA_LINEAR_REC_BT_12BIT:
    gamma = 1.f / 0.45f;
    offset = 0.0993f;
    linScale = 4.5f;
    split = 0.0181f;
    break;
  case CML_RESPONSE_SRGB:
    break;
  case CML_RESPONSE_LSTAR:
    break;
  case CML_RESPONSE_LSTAR_STANDARD:
    break;
  case CML_RESPONSE_CUSTOM_GAMMA: {
    const GammaLinearInputParameters* inputParams = cmlGetCustomGammaLinearParametersR(cm);
    gamma = inputParams->gamma;
    break; }
  case CML_RESPONSE_CUSTOM_GAMMA_LINEAR: {
    const GammaLinearInputParameters* inputParams = cmlGetCustomGammaLinearParametersR(cm);
    gamma = inputParams->gamma;
    offset = inputParams->offset;
    linScale = inputParams->linScale;
    split = inputParams->split;
    break; }
  default:
    break;
  }

  [textFieldGammaRGB    setStringValue:gamma > -1.f ?    [NSString stringWithFormat:@"%1.05f", (double)gamma] :    @""];
  [textFieldOffsetRGB   setStringValue:offset > -1.f ?   [NSString stringWithFormat:@"%1.05f", (double)offset] :   @""];
  [textFieldLinScaleRGB setStringValue:linScale > -1.f ? [NSString stringWithFormat:@"%1.05f", (double)linScale] : @""];
  [textFieldSplitRGB    setStringValue:split > -1.f ?    [NSString stringWithFormat:@"%1.05f", (double)split] :    @""];
  [sliderGammaRGB       setFloatValue:gamma > -1.f ?    gamma :    0.f];
  [sliderOffsetRGB      setFloatValue:offset > -1.f ?   offset :   0.f];
  [sliderLinScaleRGB    setFloatValue:linScale > -1.f ? linScale : 0.f];
  [sliderSplitRGB       setFloatValue:split > -1.f ?    split :    0.f];
  
  [textFieldGammaRGB    setEnabled:CML_FALSE];
  [textFieldOffsetRGB   setEnabled:CML_FALSE];
  [textFieldLinScaleRGB setEnabled:CML_FALSE];
  [textFieldSplitRGB    setEnabled:CML_FALSE];
  [sliderGammaRGB       setEnabled:CML_FALSE];
  [sliderOffsetRGB      setEnabled:CML_FALSE];
  [sliderLinScaleRGB    setEnabled:CML_FALSE];
  [sliderSplitRGB       setEnabled:CML_FALSE];

  if(responseTypes[colorIndex] == CML_RESPONSE_CUSTOM_GAMMA){
    [textFieldGammaRGB    setEnabled:CML_TRUE];
    [sliderGammaRGB       setEnabled:CML_TRUE];
  }
  if(responseTypes[colorIndex] == CML_RESPONSE_CUSTOM_GAMMA_LINEAR){
  [textFieldGammaRGB    setEnabled:CML_TRUE];
  [textFieldOffsetRGB   setEnabled:CML_TRUE];
  [textFieldLinScaleRGB setEnabled:CML_TRUE];
  [textFieldSplitRGB    setEnabled:CML_TRUE];
  [sliderGammaRGB       setEnabled:CML_TRUE];
  [sliderOffsetRGB      setEnabled:CML_TRUE];
  [sliderLinScaleRGB    setEnabled:CML_TRUE];
  [sliderSplitRGB       setEnabled:CML_TRUE];
  }

  CMLLabColorSpaceType labcolorspace = cmlGetLabColorSpace(cm);
  if(labcolorspace == CML_LAB_CUSTOM_L){
    [responseLSelect setEnabled:true];
  }else{
    [responseLSelect setEnabled:false];
  }
//  if((labcolorspace == CML_LAB_CUSTOM_L) && (LfunctionType == CML_FUNCTION_GAMMA)){
//    [textFieldGammaL setEnabled:true];
//    [sliderGammaL setEnabled:true];
//  }else{
    [textFieldGammaL setEnabled:false];
    [sliderGammaL setEnabled:false];
//  }

}



- (void)collapseColorSelection{
  if(!colorSelectionIsExpanded){return;}
  NSRect winframe = [[self window] frame];
//  float scalefactor = (float)[ColorMachineApplication getUIScaleFactorForWindow:[self window]];
  winframe.size.width -= 257.f;
  [[self window] setFrame:winframe display:YES animate:YES];
  colorSelectionIsExpanded = NO;
}
- (void)expandColorSelection{
  if(colorSelectionIsExpanded){return;}
  NSRect winframe = [[self window] frame];
//  float scalefactor = (float)[ColorMachineApplication getUIScaleFactorForWindow:[self window]];
  winframe.size.width += 257.f;
  [[self window] setFrame:winframe display:YES animate:YES];
  colorSelectionIsExpanded = YES;
}


@end





