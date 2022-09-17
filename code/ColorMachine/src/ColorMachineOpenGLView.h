
#import "main.h"
#include <OpenGL/gl.h>
#include "NAString.h"

@class MachineController;
@class ColorController;

@interface ColorMachineOpenGLView : NSOpenGLView{
  float mousex;
  float mousey;
  uint32 width;
  uint32 height;
}
- (void)awakeFromNib;
- (id)initWithFrame:(NSRect)frameRect;
- (void)prepareOpenGL;
- (void)reshape;
- (void)mouseDown:(NSEvent*)event;
- (void)mouseDragged:(NSEvent*)event;
- (BOOL)isOpaque;

@end



//@interface PixelDisplay : ColorMachineOpenGLView{
//  IBOutlet ColorController* colorcontroller;
//  CMLColorType texturecolortype;
//  uint32 texturewidth;
//  uint32 textureheight;
//  float* colordata;
//  Byte* texdata;
//  GLuint texture;
//  bool singlelinetexture;
//}
//- (void)awakeFromNib;
//- (void)prepareOpenGL;
//- (void)dealloc;
//- (void)reshape;
//- (void)drawRect:(NSRect)rect;
//- (ColorController*) colorcontroller;
//
//@end





@interface ColorWell : NSView{
  ColorController* colorcontroller;
  CMLColorType colorType;
  float* colordata;
//  Byte* rgb8Bitdata;
  size_t width;
  size_t height;
  float* colorBuffer;
  float* normedbuffer;
  CMLNormedConverter normedinputconverter;
  CMLNormedConverter normedoutputconverter;
  size_t channelx;
  size_t channely;
  BOOL drawspectrum;
}
- (id)init;
- (void)dealloc;
- (void)initWithController:(ColorController*)controller
                 colorType:(CMLColorType)colorType
      normedinputconverter:(CMLNormedConverter)normedinputconverter
     normedoutputconverter:(CMLNormedConverter)normedoutputconverter
                  channelx:(size_t)channelx
                  channely:(size_t)channely
              drawspectrum:(BOOL)drawspectrum;
- (void)drawRect:(NSRect)rect;
- (void)mouseDown:(NSEvent*)event;
- (void)mouseDragged:(NSEvent*)event;
- (BOOL)isOpaque;
@end

