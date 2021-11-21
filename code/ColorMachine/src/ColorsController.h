
#import "main.h"


@class ColorController;
@class GrayColorController;
@class XYZColorController;
@class YxyColorController;
@class YuvColorController;
@class LabColorController;
@class LuvColorController;
@class RGBColorController;
@class HSVColorController;
@class HSLColorController;
@class YCbCrColorController;
@class SpectralColorController;

#define MINI_FONT_SIZE 8.f
#define BIG_FONT_SIZE 12.f
#define SMALL_FONT_SIZE 10.f
#define SMALL_LINE_HEIGHT 14.f
#define BIG_LINE_HEIGHT 18.f
#define START_X_OFFSET 8.f
#define COLOR_VIEW_WIDTH 90.f

@interface OutlineViewItem : NSObject <NSCopying>{
  NSString* title;
}
- (NSString*)getTitle;
- (void)setTitle:(NSString*)title;
- (id)getObjectValue;
- (id)copyWithZone:(NSZone *)zone;
- (BOOL)isExpandable;
@end



@interface ColorItem : OutlineViewItem{
  Color* color;
  CGFloat rowheight;
}
- (id)initWithCMLColor:(Color*) newcolor title:(NSString*) title;
- (BOOL)isExpandable;
- (CGFloat)getRowHeight;
- (void)drawWithFrame:(NSRect)cellFrame inContext:(CGContextRef) context;
- (BOOL)collapseAtClick;
- (void)performClick:(NSEvent*)theEvent;
- (const Color*) getColor;
@end



@interface ColorGroup : OutlineViewItem{
  NSMutableArray* colors;
}
- (void)dealloc;
- (NSInteger)getNumChildren;
- (void)addItem:(ColorItem*)item;
- (ColorItem*)getChildAtIndex:(NSInteger)index;
- (BOOL)isExpandable;
- (CGFloat)getRowHeight;
- (void)drawWithFrame:(NSRect)cellFrame inContext:(CGContextRef) context;
@end




@interface ColorItemColorGroup : NSObject{
  ColorItem* item;
  ColorGroup* group;
}
- (void)setItem:(ColorItem*)item;
- (void)setGroup:(ColorGroup*)group;
- (ColorItem*)getItem;
- (ColorGroup*)getGroup;
- (void)dealloc;
@end





@interface ColorCell : NSCell {
}
//- (void)setObjectValue:(id < NSCopying >)object;
- (void)drawWithFrame:(NSRect)cellFrame inView:(NSView *)controlView;


@end




@interface ColorMachineOutlineView : NSOutlineView {
}
//- (NSRect)frameOfCellAtColumn:(NSInteger)columnIndex row:(NSInteger)rowIndex;
- (void)drawRect:(NSRect)rect;
- (NSRect)frameOfOutlineCellAtRow:(NSInteger)row;
- (void)mouseDown:(NSEvent *)theEvent;
@end



@interface ColorsController : NSObject <NSOutlineViewDataSource, NSOutlineViewDelegate> {
  NSMutableArray* colorgroups;
  Color* curcolor;
  const ColorController* workcolorcontroller;

  IBOutlet ColorMachineOutlineView* colorsoutlineview;

  IBOutlet GrayColorController*     graycolorcontroller;
  IBOutlet XYZColorController*      xyzcolorcontroller;
  IBOutlet YxyColorController*      yxycolorcontroller;
  IBOutlet YuvColorController*      yuvcolorcontroller;
  IBOutlet LabColorController*      labcolorcontroller;
  IBOutlet LuvColorController*      luvcolorcontroller;
  IBOutlet RGBColorController*      rgbcolorcontroller;
  IBOutlet HSVColorController*      hsvcolorcontroller;
  IBOutlet HSLColorController*      hslcolorcontroller;
  IBOutlet YCbCrColorController*    ycbcrcolorcontroller;
  IBOutlet SpectralColorController* spectralcolorcontroller;
  
}

- (void)awakeFromNib;
- (id)init;
- (void)dealloc;
- (const Color*)currentColor;
- (void)colorHasChanged;
//- (void)setCurrentColor:(NSNotification*)notification;
- (void)colorItemHasChanged:(ColorGroup*)colorgroup;
//- (void)colorItemHeightHasChanged:(NSNotification*)notification;
- (void)addColorGroup:(ColorGroup*)colorgroup;
- (void)assimilateColor:(ColorItemColorGroup*)coloritemcolorgroup;
- (const ColorController*)getWorkingColorController;
- (void)setWorkingColorController:(ColorController*) workingcolorcontroller;


// outline view source implementations:
- (NSInteger)outlineView:(NSOutlineView *)outlineView numberOfChildrenOfItem:(id)item;
- (id)outlineView:(NSOutlineView *)outlineView child:(NSInteger)index ofItem:(id)item;
- (BOOL)outlineView:(NSOutlineView *)outlineView isItemExpandable:(id)item;
- (id)outlineView:(NSOutlineView *)outlineView objectValueForTableColumn:(NSTableColumn *)tableColumn byItem:(id)item;
- (CGFloat)outlineView:(NSOutlineView *)outlineView heightOfRowByItem:(id)item;
//- (BOOL)outlineView:(NSOutlineView *)outlineView shouldShowOutlineCellForItem:(id)item;
- (void)outlineViewSelectionDidChange:(NSNotification *)notification;

- (void)setCurrentColor:(const Color*)color;
- (void)updateColor;

@end
