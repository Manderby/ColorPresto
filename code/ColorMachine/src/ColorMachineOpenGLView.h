
#import "main.h"
#include <OpenGL/gl.h>
#include <NAString.h>

@class MachineController;
@class ColorController;

void OpenGLtextoutput(float x, float y, float z, NAString* str);

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
  CMLColorType colortype;
  float* colordata;
//  Byte* rgb8Bitdata;
  CMLuint32 width;
  CMLuint32 height;
  float* colorbuffer;
  float* normedbuffer;
  CMLNormedConverter normedinputconverter;
  CMLNormedConverter normedoutputconverter;
  CMLuint32 channelx;
  CMLuint32 channely;
  BOOL drawspectrum;
}
- (id)init;
- (void)dealloc;
- (void)initWithController:(ColorController*)controller
                 colortype:(CMLColorType)colortype
      normedinputconverter:(CMLNormedConverter)normedinputconverter
     normedoutputconverter:(CMLNormedConverter)normedoutputconverter
                  channelx:(CMLuint32)channelx
                  channely:(CMLuint32)channely
              drawspectrum:(BOOL)drawspectrum;
- (void)drawRect:(NSRect)rect;
- (void)mouseDown:(NSEvent*)event;
- (void)mouseDragged:(NSEvent*)event;
- (BOOL)isOpaque;
@end

