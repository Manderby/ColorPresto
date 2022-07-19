
#import "ColorController.h"
#import "ColorsController.h"
#import "ColorMachineApplication.h"
#import "MachineWindowController.h"
#import "GrayColorController.h"
#import "XYZColorController.h"
#import "YxyColorController.h"
#import "YuvColorController.h"
#import "LabColorController.h"
#import "LuvColorController.h"
#import "RGBColorController.h"
#import "HSVColorController.h"
#import "HSLColorController.h"
#import "YCbCrColorController.h"
#import "SpectralColorController.h"
#include "NAUICocoaLegacy.h"



@implementation OutlineViewItem

- (NSString*)getTitle{
  return title;
}

- (void)setTitle:(NSString*)string{
  title = string;
}

- (id)getObjectValue{
  return self;
}

- (id)copyWithZone:(NSZone *)zone{
  return NA_COCOA_RETAIN(self);
}

- (BOOL)isExpandable{return NO;}

@end




@implementation ColorItem

//- (id)init{
//  CMLCIEDIlluminant spectralfunction(4000.f + 10000.f * (rand()/(float)RAND_MAX));
//  CMLFunctionMulScalar remfunc(&spectralfunction, cmlInverse(spectralfunction.getMaxValue()));
//  color = new SpectralColor(&remfunc, true);
////  color = new SpectralColor(&spectralfunction, false);
////  color = new RGBColor(rand()/(float)RAND_MAX, rand()/(float)RAND_MAX, rand()/(float)RAND_MAX);
////  rowheight = 16.f + 20.f * (rand()/(float)RAND_MAX);
//  rowheight = 12.f;
//  return [super init];
//}

- (id)initWithCMLColor:(Color*) newcolor title:(NSString*) string{
  color = newcolor;
  if(string){
    [self setTitle:string];
  }else{
    if(color){
      CMLColorType colorType = color->getColorType();
      const char* colorname = cmlGetColorTypeString(colorType);
      switch(colorType){
      case CML_COLOR_GRAY:
        title = [NSString stringWithFormat:@"%s %1.04f", colorname, (*color)[0]];
        break;
      case CML_COLOR_XYZ:
        title = [NSString stringWithFormat:@"%s %1.02f, %1.02f, %1.02f", colorname, (*color)[0], (*color)[1], (*color)[2]];
        break;
      case CML_COLOR_Yxy:
        title = [NSString stringWithFormat:@"%s %1.02f, %1.02f, %1.02f", colorname, (*color)[0], (*color)[1], (*color)[2]];
        break;
      case CML_COLOR_Yuv:
        title = [NSString stringWithFormat:@"%s %1.02f, %1.02f, %1.02f", colorname, (*color)[0], (*color)[1], (*color)[2]];
        break;
      case CML_COLOR_Yupvp:
        title = [NSString stringWithFormat:@"%s %1.02f, %1.02f, %1.02f", colorname, (*color)[0], (*color)[1], (*color)[2]];
        break;
      case CML_COLOR_YCbCr:
        title = [NSString stringWithFormat:@"%s %1.02f, %1.02f, %1.02f", colorname, (*color)[0], (*color)[1], (*color)[2]];
        break;
      case CML_COLOR_Lab:
        title = [NSString stringWithFormat:@"%s %3.00f, %3.00f, %3.00f", colorname, (*color)[0], (*color)[1], (*color)[2]];
        break;
      case CML_COLOR_Lch:
        title = [NSString stringWithFormat:@"%s %3.00f, %3.00f, %3.00f", colorname, (*color)[0], (*color)[1], (*color)[2]];
        break;
      case CML_COLOR_Luv:
        title = [NSString stringWithFormat:@"%s %3.00f, %3.00f, %3.00f", colorname, (*color)[0], (*color)[1], (*color)[2]];
        break;
      case CML_COLOR_RGB:
        title = [NSString stringWithFormat:@"%s %1.02f, %1.02f, %1.02f", colorname, (*color)[0], (*color)[1], (*color)[2]];
        break;
      case CML_COLOR_HSV:
        title = [NSString stringWithFormat:@"%s %3.00f, %1.02f, %1.02f", colorname, (*color)[0], (*color)[1], (*color)[2]];
        break;
      case CML_COLOR_HSL:
        title = [NSString stringWithFormat:@"%s %3.00f, %1.02f, %1.02f", colorname, (*color)[0], (*color)[1], (*color)[2]];
        break;
      case CML_COLOR_CMYK:
        title = [NSString stringWithFormat:@"%s %1.02f, %1.02f, %1.02f, %1.02f", colorname, (*color)[0], (*color)[1], (*color)[2], (*color)[3]];
        break;
      case CML_COLOR_SPECTRUM_ILLUMINATION:
        title = [NSString stringWithFormat:@"%s", colorname];
        break;
      case CML_COLOR_SPECTRUM_REMISSION:
        title = [NSString stringWithFormat:@"%s", colorname];
        break;
      default:
        title = [NSString stringWithFormat:@"Unknown"];
        break;
      }
    }else{
      title = @"Empty";
    }
  }
  rowheight = SMALL_LINE_HEIGHT;
  return [super init];
}

- (void)dealloc{
  delete color;
  NA_COCOA_SUPER_DEALLOC();
}

- (BOOL)isExpandable{
  return NO;
}

- (CGFloat)getRowHeight{
  return rowheight;
}

- (void)drawWithFrame:(NSRect)cellFrame inContext:(CGContextRef) context{
  RGBColor rgbcolor;
  [(ColorMachineApplication*)NSApp fillRGBfloatarray:rgbcolor fromColor:color];

//  const float viewrange = .8f;
//  const float viewoffset = .05f;

//  float width = (float)cellFrame.size.width;
//  float height = (float)cellFrame.size.height;

  CGRect colorrect = CGRectMake(cellFrame.origin.x + START_X_OFFSET, cellFrame.origin.y + cellFrame.size.height, COLOR_VIEW_WIDTH - START_X_OFFSET, -cellFrame.size.height);
  [(ColorMachineApplication*)NSApp drawColor:color fillBack:YES linecolor:NULL context:context inRect:colorrect];


//  CGColorRef cgcolor = CGColorCreateGenericRGB(rgbcolor[0], rgbcolor[1], rgbcolor[2], 1.f);
//
//  CGContextSetFillColorWithColor(context, cgcolor);
//  CGRect colorrect = {{cellFrame.origin.x + START_X_OFFSET, cellFrame.origin.y}, {COLOR_VIEW_WIDTH - START_X_OFFSET, height}};
//  CGContextFillRect(context, colorrect);
//  CGColorRelease(cgcolor);
//  
//  
//  if((color->getColorType() == CML_COLOR_SPECTRUM_REMISSION) || color->getColorType() == CML_COLOR_SPECTRUM_ILLUMINATION){
//
//    const CMLFunction* colorspec = ((SpectralColor*)color)->getSpectrum();
//    if(colorspec){
//      float divisor = 1.f;
//      if(color->getColorType() == CML_COLOR_SPECTRUM_ILLUMINATION){
//        divisor = cmlInverse(colorspec->getMaxValue());
//      }
//  //    float divisor = cmlInverse((*colorspec)(CML_NORMALIZATION_WAVELENGTH_5NM));
//
//      LabColor labcolor = rgbcolor;
//      labcolor[0] -= 50.f;
//      if(labcolor[0] < 0.f){labcolor[0] += 100.f;}
//      RGBColor linecolor = labcolor;
//      cgcolor = CGColorCreateGenericRGB(linecolor[0], linecolor[1], linecolor[2], 1.f);
//      CGContextSetStrokeColorWithColor(context, cgcolor);
//
//      CMLDefinitionRange defRange = colorspec->getDefinitionRange();
//      CGContextBeginPath(context);
//      if(defRange.stepSize == 0.f){defRange.stepSize = CML_DEFAULT_INTEGRATION_STEPSIZE;}
//      size_t sampleCount = cmlGetIntervalCount(defRange.minSampleCoord, defRange.maxSampleCoord, defRange.stepSize);
//      if(sampleCount == 1){
//        float curcoord = defRange.minSampleCoord;
//        CGFloat x = cellFrame.origin.x + ((curcoord - defRange.minSampleCoord) / (defRange.maxSampleCoord - defRange.minSampleCoord)) * COLOR_VIEW_WIDTH + .5f;
//        CGFloat y1 = cellFrame.origin.y + height * (1.f - 0.f * viewrange + viewoffset);
//        CGFloat y2 = cellFrame.origin.y + height * (1.f - (*colorspec)(curcoord) * divisor * viewrange + viewoffset);
//        CGContextMoveToPoint(context, x, y1);
//        CGContextAddLineToPoint(context, x, y2);
//      }else{
//        for(size_t i=0; i<sampleCount; i++){
//          float curcoord = defRange.minSampleCoord + i * defRange.stepSize;
//          CGFloat x = cellFrame.origin.x + ((curcoord - defRange.minSampleCoord) / (defRange.maxSampleCoord - defRange.minSampleCoord)) * COLOR_VIEW_WIDTH + .5f;
//          CGFloat y = cellFrame.origin.y + height * (1.f - (*colorspec)(curcoord) * divisor * viewrange + viewoffset);
//          if(i == 0){CGContextMoveToPoint(context, x, y);}
//          CGContextAddLineToPoint(context, x, y);
//        }
//      }
//      CGContextStrokePath(context);
//      CGColorRelease(cgcolor);
//
//    }
//    
//  }else{
//  }
  NSDictionary *attributes = [NSDictionary dictionaryWithObjectsAndKeys:
    [NSFont fontWithName:@"Lucida Grande" size:10], NSFontAttributeName,
    [NSColor blackColor], NSForegroundColorAttributeName, nil];
  NSAttributedString * currentText1 = [[NSAttributedString alloc] initWithString:title attributes: attributes];
  [currentText1 drawAtPoint:NSMakePoint(cellFrame.origin.x + COLOR_VIEW_WIDTH + START_X_OFFSET, cellFrame.origin.y)];
  NA_COCOA_RELEASE(currentText1);
}

- (BOOL)collapseAtClick{return NO;}

- (void)performClick:(NSEvent*)theEvent{
  printf("click!\n");
}

- (const Color*) getColor{
  return color;
}

@end





@implementation ColorGroup

- (void)dealloc{
  NA_COCOA_RELEASE(colors);
  NA_COCOA_SUPER_DEALLOC();
}

- (NSInteger)getNumChildren{
  return [colors count];
}

- (void)addItem:(ColorItem*)item{
  [colors addObject:item];
//  NA_COCOA_RELEASE(item release);
}

- (ColorItem*)getChildAtIndex:(NSInteger)index{
  return [colors objectAtIndex:index];
}

- (BOOL)isExpandable{
  return YES;
}

- (CGFloat)getRowHeight{
  return BIG_LINE_HEIGHT;
}

- (void)drawWithFrame:(NSRect)cellFrame inContext:(CGContextRef) context{
  CGColorRef fillColor = CGColorCreateGenericRGB(.75f, .75f, .75f, 1.f);
  CGContextSetFillColorWithColor(context, fillColor);
  CGContextFillRect(context, NSRectToCGRect(cellFrame));
  CGColorRelease(fillColor);
  
  NSDictionary *attributes = [NSDictionary dictionaryWithObjectsAndKeys:
    [NSFont fontWithName:@"Lucida Grande" size:12], NSFontAttributeName,
    [NSColor blackColor], NSForegroundColorAttributeName, nil];
  NSAttributedString * currentText1 = [[NSAttributedString alloc] initWithString:title attributes: attributes];
  [currentText1 drawAtPoint:NSMakePoint(cellFrame.origin.x + START_X_OFFSET, cellFrame.origin.y)];
  NA_COCOA_RELEASE(currentText1);

}

- (BOOL)collapseAtClick{return YES;}

@end





@implementation ColorItemColorGroup

- (void)setItem:(ColorItem*)newitem{item = NA_COCOA_RETAIN(newitem);}
- (void)setGroup:(ColorGroup*)newgroup{group = NA_COCOA_RETAIN(newgroup);}
- (ColorItem*)getItem{return item;}
- (ColorGroup*)getGroup{return group;}
- (void)dealloc{
  NA_COCOA_RELEASE(item);
  NA_COCOA_RELEASE(group);
  NA_COCOA_SUPER_DEALLOC();
}

@end





@implementation ColorCell

- (void)drawWithFrame:(NSRect)cellFrame inView:(NSView *)controlView{
  CGContextRef context = (CGContextRef)[[NSGraphicsContext currentContext] graphicsPort];
  [[self objectValue] drawWithFrame:cellFrame inContext:context];
}

@end




@implementation ColorMachineOutlineView

- (NSRect)frameOfOutlineCellAtRow:(NSInteger)row{
  return NSZeroRect;
//  NSRect superrect = [super frameOfOutlineCellAtRow:row];
//  superrect.size.width = 10.;
//  return superrect;
}

//- (NSRect)frameOfCellAtColumn:(NSInteger)columnIndex row:(NSInteger)rowIndex{
//  NSRect superrect = [super frameOfCellAtColumn:columnIndex row:rowIndex];
//  superrect.size.width = [self bounds].size.width - 20;
//  return superrect;
//}

- (void)drawRect:(NSRect)rect{
  [super drawRect:rect];
  if([self numberOfRows] == 0){
    NSMutableParagraphStyle* parastyle = [[NSMutableParagraphStyle alloc] init];
    [parastyle setAlignment:NATextAlignmentCenter];
    NSDictionary *attributes = [NSDictionary dictionaryWithObjectsAndKeys:
      [NSFont fontWithName:@"Lucida Grande" size:10], NSFontAttributeName,
      parastyle, NSParagraphStyleAttributeName,
      [NSColor blackColor], NSForegroundColorAttributeName, nil];
    NSAttributedString * currentText = [[NSAttributedString alloc] initWithString:@"No measurements or devices available." attributes: attributes];
    NSRect drawrect = [self bounds];
    drawrect.size.height /= 2.f;
    drawrect.origin.y += drawrect.size.height;
    [currentText drawInRect:drawrect];
//    [currentText drawinRect:NSMakePoint(cellFrame.origin.x + COLOR_VIEW_WIDTH + START_X_OFFSET, cellFrame.origin.y)];
    NA_COCOA_RELEASE(currentText);
    NA_COCOA_RELEASE(parastyle);
  }
}

- (void)mouseDown:(NSEvent *)theEvent{
  NSPoint eventLocation = [theEvent locationInWindow];
  NSPoint pos = [self convertPoint:eventLocation fromView:nil];
  
  NSInteger index = [self rowAtPoint:pos];
  if(index != -1){
    id item = [self itemAtRow:index];
    if([item collapseAtClick]){
      if([self isItemExpanded:item]){
        [self collapseItem:item];
//        printf("Collapsing\n");
      }else{
        [self expandItem:item];
//        printf("Expanding\n");
      }
//      [self noteNumberOfRowsChanged];
//      [self setNeedsDisplay: YES];
    }else{
      [super mouseDown:theEvent];
//      [(ColorItem*)item performClick:theEvent];
    }
//    [super mouseDown:theEvent];
  }
}



@end



@implementation ColorsController

- (void)awakeFromNib{
  [colorsoutlineview setIndentationPerLevel:0];
  [colorsoutlineview setIntercellSpacing:NSMakeSize(0.f, 1.f)];
  [colorsoutlineview setDelegate:self];
  [colorsoutlineview setDataSource:self];
}

- (id)init{
  self = [super init];
  workcolorcontroller = nil;
  colorgroups = [[NSMutableArray alloc] init];
//  [colorgroups addObject:NA_COCOA_AUTORELEASE([[ColorGroup alloc] init] autorelease)];
  
  return self;
}

- (void)dealloc{
  NA_COCOA_RELEASE(colorgroups);
  NA_COCOA_SUPER_DEALLOC();
}

- (const Color*)currentColor{
  return curcolor;
}

- (void)colorHasChanged{
  [(ColorMachineApplication*)NSApp updateColor];
}

- (void)colorItemHasChanged:(ColorGroup*)colorgroup{
  [colorsoutlineview reloadItem:colorgroup reloadChildren:[colorsoutlineview isItemExpanded:colorgroup]];
}

//- (void)colorItemHeightHasChanged:(NSNotification*)notification{
//  [colorsoutlineview setNeedsDisplay:YES];
//}

- (void)addColorGroup:(ColorGroup*)colorgroup{
  [colorgroups addObject:colorgroup];
  [colorsoutlineview reloadItem:nil reloadChildren:YES];
//  [colorsoutlineview expandItem:[notification object]];

  dispatch_time_t nexttime = dispatch_time(DISPATCH_TIME_NOW, 0);
  dispatch_queue_t queue = dispatch_get_main_queue();
  dispatch_after(nexttime, queue, ^{
    [[(ColorMachineApplication*)NSApp getMachineWindowController] expandColorSelection];
    });

//  NSNotificationCenter* notcenter = [NSNotificationCenter defaultCenter];
//  [notcenter postNotification:[NSNotification notificationWithName:COLOR_MACHINE_EXPAND_COLOR_SELECTION object:nil]];
}

- (void)assimilateColor:(ColorItemColorGroup*)coloritemcolorgroup{
  ColorItemColorGroup* cicg = (ColorItemColorGroup*)coloritemcolorgroup;
  [[cicg getGroup] addItem:[cicg getItem]];
  if([colorsoutlineview isItemExpanded:[cicg getGroup]]){
    [colorsoutlineview reloadItem:[cicg getGroup] reloadChildren:YES];
  }else{
    [colorsoutlineview expandItem:[cicg getGroup]];
  }
  NSIndexSet* indexset = [NSIndexSet indexSetWithIndex:[colorsoutlineview rowForItem:[cicg getItem]]];
  [colorsoutlineview selectRowIndexes:indexset byExtendingSelection:NO];
  [self outlineViewSelectionDidChange:nil];
}

- (const ColorController*)getWorkingColorController{
  return workcolorcontroller;
}

- (void)setWorkingColorController:(ColorController*) newworkingcolorcontroller{
  if(newworkingcolorcontroller != workcolorcontroller){
    [workcolorcontroller setActive:NO];
    workcolorcontroller = newworkingcolorcontroller;
    curcolor = [workcolorcontroller color];
    [workcolorcontroller setActive:YES];
  }
}



- (NSInteger)outlineView:(NSOutlineView *)outlineView numberOfChildrenOfItem:(id)item{
  if(item == nil){
    // root items
    return [colorgroups count];
  }else{
    return [item getNumChildren];
  }
}

- (id)outlineView:(NSOutlineView *)outlineView child:(NSInteger)index ofItem:(id)item{
  if(item == nil){
    return [colorgroups objectAtIndex:index];
  }else{
    return [item getChildAtIndex:index];
  }
}

- (BOOL)outlineView:(NSOutlineView *)outlineView isItemExpandable:(id)item{
  return [item isExpandable];
}

- (id)outlineView:(NSOutlineView *)outlineView objectValueForTableColumn:(NSTableColumn *)tableColumn byItem:(id)item{
  return [item getObjectValue];
}

- (CGFloat)outlineView:(NSOutlineView *)outlineView heightOfRowByItem:(id)item{
  return [item getRowHeight];
}

//- (BOOL)outlineView:(NSOutlineView *)outlineView shouldShowOutlineCellForItem:(id)item{
//  return NO;
//}

- (void)outlineViewSelectionDidChange:(NSNotification *)notification{
  NSIndexSet* indexes = [colorsoutlineview selectedRowIndexes];

  if([indexes count] > 0){
//    printf("Selected %d\n", (int)[indexes firstIndex]);
    NSUInteger curindex = [indexes firstIndex];
    id curitem = [colorsoutlineview itemAtRow:curindex];
    if([curitem class] == [ColorItem class]){
      ColorItem* curcoloritem = (ColorItem*)curitem;
//      printf("Is a color item\n");
      [(ColorMachineApplication*)NSApp setCurrentColor:[curcoloritem getColor]];
    }else{
//      printf("Is no color item\n");
    }
  }else{
//    printf("Nothing selected\n");
  }

//  [colorsoutlineview selectRowIndexes:indexes byExtendingSelection:NO];
}

- (void)setCurrentColor:(const Color*)color{

  if(color->getColorType() == CML_COLOR_SPECTRUM_ILLUMINATION){
    cmlSetIlluminationSpectrum([(ColorMachineApplication*)NSApp getCurrentMachine], ((const SpectralColor*)color)->getSpectrum());
    [(ColorMachineApplication*)NSApp updateMachine];
    return;
  }

  ColorController* workingcolorcontroller;
  switch(color->getColorType()){
  case CML_COLOR_GRAY:  workingcolorcontroller = (ColorController*)graycolorcontroller; break;
  case CML_COLOR_XYZ:   workingcolorcontroller = (ColorController*)xyzcolorcontroller; break;
  case CML_COLOR_Yxy:   workingcolorcontroller = (ColorController*)yxycolorcontroller; break;
  case CML_COLOR_Yuv:   workingcolorcontroller = (ColorController*)yuvcolorcontroller; break;
  case CML_COLOR_Yupvp: workingcolorcontroller = (ColorController*)yuvcolorcontroller; break;
  case CML_COLOR_YCbCr: workingcolorcontroller = (ColorController*)ycbcrcolorcontroller; break;
  case CML_COLOR_Lab:   workingcolorcontroller = (ColorController*)labcolorcontroller; break;
  case CML_COLOR_Lch:   workingcolorcontroller = (ColorController*)labcolorcontroller; break;
  case CML_COLOR_Luv:   workingcolorcontroller = (ColorController*)luvcolorcontroller; break;
  case CML_COLOR_RGB:   workingcolorcontroller = (ColorController*)rgbcolorcontroller; break;
  case CML_COLOR_HSV:   workingcolorcontroller = (ColorController*)hsvcolorcontroller; break;
  case CML_COLOR_HSL:   workingcolorcontroller = (ColorController*)hslcolorcontroller; break;
  case CML_COLOR_SPECTRUM_REMISSION:    workingcolorcontroller = (ColorController*)spectralcolorcontroller; break;
  default:
    workingcolorcontroller = (ColorController*)xyzcolorcontroller; break;
    break;
  }

  // Set the working color controller.
  [self setWorkingColorController:workingcolorcontroller];
  // Now, curcolor is set to the color stored in the workingcolorcontroller
  *curcolor = *color;
  [self updateColor];
}

- (void)updateColor{

//  NSIndexSet* indexes = [colorsoutlineview selectedRowIndexes];
//  if([indexes count] > 0){
//    NSUInteger curindex = [indexes firstIndex];
//    id curitem = [colorsoutlineview itemAtRow:curindex];
//    if([curitem class] == [ColorItem class]){
//      ColorItem* curcoloritem = (ColorItem*)curitem;
//      if(curcolor != [curcoloritem getColor]){
//        [colorsoutlineview deselectAll:self];
//      }
//    }else{
//      [colorsoutlineview deselectAll:self];
//    }
//  }

//  [NSThread]

  [graycolorcontroller      update];
  [xyzcolorcontroller       update];
  [yxycolorcontroller       update];
  [yuvcolorcontroller       update];
  [labcolorcontroller       update];
  [luvcolorcontroller       update];
  [rgbcolorcontroller       update];
//  [cmykcolorcontroller      update];
  [hsvcolorcontroller       update];
  [hslcolorcontroller       update];
  [ycbcrcolorcontroller     update];
  [spectralcolorcontroller  update];
  
  [colorsoutlineview setNeedsDisplay:YES];
//  [[self window] display];
}

@end
