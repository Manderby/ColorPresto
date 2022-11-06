
#import "main.h"

CM_PROTOTYPE(CMHSLColorController);
CM_PROTOTYPE(CMHSVColorController);
CM_PROTOTYPE(CMLabColorController);
CM_PROTOTYPE(CMLuvColorController);
CM_PROTOTYPE(CMRGBColorController);
CM_PROTOTYPE(CMXYZColorController);
CM_PROTOTYPE(CMYCbCrColorController);
CM_PROTOTYPE(CMYcdColorController);
CM_PROTOTYPE(CMYuvColorController);
CM_PROTOTYPE(CMYxyColorController);

@class GammaDisplay;

@class ThreeDeeWindowController;

@interface MachineWindowController : NSWindowController <NSWindowDelegate> {

  IBOutlet NSButton *maskState;
  IBOutlet NSButton *gridLinesState;

  IBOutlet NSPopUpButton* observerSelect;
  IBOutlet NSPopUpButton* illuminationSelect;
  IBOutlet NSPopUpButton* chromaticAdaptationSelect;
  IBOutlet NSPopUpButton* grayComputationSelect;
  IBOutlet NSPopUpButton* labSpaceSelect;
  IBOutlet NSPopUpButton* rgbColorSpaceSelect;
  IBOutlet NSPopUpButton* responseChannelSelect;
  IBOutlet NSPopUpButton* responseRGBSelect;
  IBOutlet NSPopUpButton* responseLSelect;
//  IBOutlet NSPopUpButton* cmyktransformselect;
  IBOutlet NSPopUpButton* maskselect;

  IBOutlet NSSlider *sliderT;
  IBOutlet NSSlider *sliderK;
  IBOutlet NSSlider *sliderke;
  IBOutlet NSSlider *sliderGammaRGB;
  IBOutlet NSSlider *sliderOffsetRGB;
  IBOutlet NSSlider *sliderLinScaleRGB;
  IBOutlet NSSlider *sliderSplitRGB;
  IBOutlet NSSlider *sliderGammaL;
  IBOutlet GammaDisplay *gammaDisplay;

  IBOutlet NSTextField *textFieldT;
  IBOutlet NSTextField *textL;
  IBOutlet NSTextField *texta;
  IBOutlet NSTextField *textb;
  IBOutlet NSTextField *whitePointY;
  IBOutlet NSTextField *whitePointx;
  IBOutlet NSTextField *whitePointy;
  IBOutlet NSTextField *textFieldK;
  IBOutlet NSTextField *textFieldke;
  IBOutlet NSTextField *redPrimaryY;
  IBOutlet NSTextField *redPrimaryx;
  IBOutlet NSTextField *redPrimaryy;
  IBOutlet NSTextField *greenPrimaryY;
  IBOutlet NSTextField *greenPrimaryx;
  IBOutlet NSTextField *greenPrimaryy;
  IBOutlet NSTextField *bluePrimaryY;
  IBOutlet NSTextField *bluePrimaryx;
  IBOutlet NSTextField *bluePrimaryy;
  IBOutlet NSTextField *textFieldGammaRGB;
  IBOutlet NSTextField *textFieldOffsetRGB;
  IBOutlet NSTextField *textFieldLinScaleRGB;
  IBOutlet NSTextField *textFieldSplitRGB;
  IBOutlet NSTextField *textFieldGammaL;

  BOOL colorSelectionIsExpanded;
  size_t lastSelectedChannel;

  CMHSLColorController* hslColorController;
  CMHSVColorController* hsvColorController;
  CMLabColorController* labColorController;
  CMLuvColorController* luvColorController;
  CMRGBColorController* rgbColorController;
  CMXYZColorController* xyzColorController;
  CMYCbCrColorController* ycbcrColorController;
  CMYcdColorController* ycdColorController;
  CMYuvColorController* yuvColorController;
  CMYxyColorController* yxyColorController;
}
- (void)awakeFromNib;

- (IBAction)maskStateChange:(NSButton*)sender;
- (IBAction)maskChange:(NSPopUpButton*)sender;
- (IBAction)gridlinesChange:(NSButton*)sender;

- (IBAction)observerChange:(NSPopUpButton*)sender;
- (IBAction)illuminationChange:(NSPopUpButton*)sender;
//- (IBAction)chromaticAdaptationChange:(NSPopUpButton*)sender;
- (IBAction)whitePointChange:(NSControl*)sender;
- (IBAction)rgbprimariesChange:(NSControl*)sender;
- (IBAction)rgbResponseChange:(NSPopUpButton*)sender;
- (IBAction)rgbGammaChange:(NSControl*)sender;
- (IBAction)rgbOffsetChange:(NSControl*)sender;
- (IBAction)rgbLinScaleChange:(NSControl*)sender;
- (IBAction)rgbSplitChange:(NSControl*)sender;
- (IBAction)graycomputationChange:(NSPopUpButton*)sender;
- (IBAction)labSpaceChange:(NSPopUpButton*)sender;
- (IBAction)labresponseChange:(NSPopUpButton*)sender;
- (IBAction)labgammaChange:(NSControl*)sender;
- (IBAction)rgbSpaceChange:(NSPopUpButton*)sender;

- (IBAction)valueChangeT:(NSControl*)sender;
- (IBAction)valueChangeK:(NSControl*)sender;
- (IBAction)valueChangeke:(NSControl*)sender;

- (void)collapseColorSelection;
- (void)expandColorSelection;

- (void)windowDidChangeScreenProfile:(NSNotification *)notification;
//- (void)windowDidChangeBackingProperties:(NSNotification *)notification;

- (CMHSLColorController*)getHSLColorController;

- (void)updateMachine;

@end



