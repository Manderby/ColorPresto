
#import "ThreeDeeWindowController.h"
#import "ColorMachineApplication.h"
#import "ColorMachineOpenGLView.h"

#include <stdarg.h>
#include <dispatch/dispatch.h>

CMLOutput CMLcreateNormedGamutSlice(  CMLColorType colorspace,
                                 const CMLVec4UInt dimensions,
                                     const CMLVec4 origin,
                                     const CMLVec4 range0,
                                     const CMLVec4 range1,
                                     const CMLVec4 range2,
                                     const CMLVec4 range3){
  
  if(colorspace > CML_COLOR_CMYK){return NULL;}
  
  CMLuint32 numchannels = CMLgetNumChannels(colorspace);

  CMLVec4 o;
  CMLVec4 r[CML_MAX_NUMBER_OF_CHANNELS];
  if(origin){cmlCpy4(o, origin);}else{cmlSet4(o, 0.f, 0.f, 0.f, 0.f);}
  if(range0){cmlCpy4(r[0], range0);}else{cmlSet4(r[0], 1.f, 0.f, 0.f, 0.f);}
  if(range1){cmlCpy4(r[1], range1);}else{cmlSet4(r[1], 0.f, 1.f, 0.f, 0.f);}
  if(range2){cmlCpy4(r[2], range2);}else{cmlSet4(r[2], 0.f, 0.f, 1.f, 0.f);}
  if(range3){cmlCpy4(r[3], range3);}else{cmlSet4(r[3], 0.f, 0.f, 0.f, 1.f);}
  
  CMLVec4UInt dim;
  CMLVec4 invdim;
  CMLuint32 totalnumentries = 1;
  uint32 dimcount = 0;
  for(CMLuint32 d=0; d<CML_MAX_NUMBER_OF_CHANNELS; d++){
    if(dimensions[d] > 1){
      dim[dimcount] = dimensions[d];
      totalnumentries *= dimensions[d];
      invdim[dimcount] = 1.f / (dimensions[d] - 1);
      if(dimcount != d){cmlCpy4(r[dimcount], r[d]);}
      dimcount++;
    }
  }

  float* array = (float*)malloc(totalnumentries * numchannels * sizeof(float));
  float* ptr = array;
  
  CMLVec4 o1, o2, o3;

  switch(numchannels){
  case 1:
    switch(dimcount){
    case 0:
      cmlCpy1(ptr, o);
      break;
    case 1:
      for(CMLuint32 c0=0; c0<dim[0]; c0++){
        float f0 = (float)c0*invdim[0];
        *ptr++ = o[0] + f0 * r[0][0];
      }
      break;
    case 2:
      for(CMLuint32 c1=0; c1<dim[1]; c1++){
        float f1 = (float)c1*invdim[1];
        o1[0] = o[0] + f1 * r[1][0];
        for(CMLuint32 c0=0; c0<dim[0]; c0++){
          float f0 = (float)c0*invdim[0];
          *ptr++ = o1[0] + f0 * r[0][0];
        }
      }
      break;
    case 3:
      for(CMLuint32 c2=0; c2<dim[2]; c2++){
        float f2 = (float)c2*invdim[2];
        o2[0] = o[0] + f2 * r[2][0];
        for(CMLuint32 c1=0; c1<dim[1]; c1++){
          float f1 = (float)c1*invdim[1];
          o1[0] = o2[0] + f1 * r[1][0];
          for(CMLuint32 c0=0; c0<dim[0]; c0++){
            float f0 = (float)c0*invdim[0];
            *ptr++ = o1[0] + f0 * r[0][0];
          }
        }
      }
      break;
    case 4:
      for(CMLuint32 c3=0; c3<dim[3]; c3++){
        float f3 = (float)c3*invdim[3];
        o3[0] = o[0] + f3 * r[3][0];
        for(CMLuint32 c2=0; c2<dim[2]; c2++){
          float f2 = (float)c2*invdim[2];
          o2[0] = o3[0] + f2 * r[2][0];
          for(CMLuint32 c1=0; c1<dim[1]; c1++){
            float f1 = (float)c1*invdim[1];
            o1[0] = o2[0] + f1 * r[1][0];
            for(CMLuint32 c0=0; c0<dim[0]; c0++){
              float f0 = (float)c0*invdim[0];
              *ptr++ = o1[0] + f0 * r[0][0];
            }
          }
        }
      }
      break;
    }
    break;

  case 2:
    switch(dimcount){
    case 0:
      cmlCpy2(ptr, o);
      break;
    case 1:
      for(CMLuint32 c0=0; c0<dim[0]; c0++){
        float f0 = (float)c0*invdim[0];
        *ptr++ = o[0] + f0 * r[0][0];
        *ptr++ = o[1] + f0 * r[0][1];
      }
      break;
    case 2:
      for(CMLuint32 c1=0; c1<dim[1]; c1++){
        float f1 = (float)c1*invdim[1];
        o1[0] = o[0] + f1 * r[1][0];
        o1[1] = o[1] + f1 * r[1][1];
        for(CMLuint32 c0=0; c0<dim[0]; c0++){
          float f0 = (float)c0*invdim[0];
          *ptr++ = o1[0] + f0 * r[0][0];
          *ptr++ = o1[1] + f0 * r[0][1];
        }
      }
      break;
    case 3:
      for(CMLuint32 c2=0; c2<dim[2]; c2++){
        float f2 = (float)c2*invdim[2];
        o2[0] = o[0] + f2 * r[2][0];
        o2[1] = o[1] + f2 * r[2][1];
        for(CMLuint32 c1=0; c1<dim[1]; c1++){
          float f1 = (float)c1*invdim[1];
          o1[0] = o2[0] + f1 * r[1][0];
          o1[1] = o2[1] + f1 * r[1][1];
          for(CMLuint32 c0=0; c0<dim[0]; c0++){
            float f0 = (float)c0*invdim[0];
            *ptr++ = o1[0] + f0 * r[0][0];
            *ptr++ = o1[1] + f0 * r[0][1];
          }
        }
      }
      break;
    case 4:
      for(CMLuint32 c3=0; c3<dim[3]; c3++){
        float f3 = (float)c3*invdim[3];
        o3[0] = o[0] + f3 * r[3][0];
        o3[1] = o[1] + f3 * r[3][1];
        for(CMLuint32 c2=0; c2<dim[2]; c2++){
          float f2 = (float)c2*invdim[2];
          o2[0] = o3[0] + f2 * r[2][0];
          o2[1] = o3[1] + f2 * r[2][1];
          for(CMLuint32 c1=0; c1<dim[1]; c1++){
            float f1 = (float)c1*invdim[1];
            o1[0] = o2[0] + f1 * r[1][0];
            o1[1] = o2[1] + f1 * r[1][1];
            for(CMLuint32 c0=0; c0<dim[0]; c0++){
              float f0 = (float)c0*invdim[0];
              *ptr++ = o1[0] + f0 * r[0][0];
              *ptr++ = o1[1] + f0 * r[0][1];
            }
          }
        }
      }
      break;
    }
    break;

  case 3:
    switch(dimcount){
    case 0:
      cmlCpy3(ptr, o);
      break;
    case 1:
      for(CMLuint32 c0=0; c0<dim[0]; c0++){
        float f0 = (float)c0*invdim[0];
        *ptr++ = o[0] + f0 * r[0][0];
        *ptr++ = o[1] + f0 * r[0][1];
        *ptr++ = o[2] + f0 * r[0][2];
      }
      break;
    case 2:
      for(CMLuint32 c1=0; c1<dim[1]; c1++){
        float f1 = (float)c1*invdim[1];
        o1[0] = o[0] + f1 * r[1][0];
        o1[1] = o[1] + f1 * r[1][1];
        o1[2] = o[2] + f1 * r[1][2];
        for(CMLuint32 c0=0; c0<dim[0]; c0++){
          float f0 = (float)c0*invdim[0];
          *ptr++ = o1[0] + f0 * r[0][0];
          *ptr++ = o1[1] + f0 * r[0][1];
          *ptr++ = o1[2] + f0 * r[0][2];
        }
      }
      break;
    case 3:
      for(CMLuint32 c2=0; c2<dim[2]; c2++){
        float f2 = (float)c2*invdim[2];
        o2[0] = o[0] + f2 * r[2][0];
        o2[1] = o[1] + f2 * r[2][1];
        o2[2] = o[2] + f2 * r[2][2];
        for(CMLuint32 c1=0; c1<dim[1]; c1++){
          float f1 = (float)c1*invdim[1];
          o1[0] = o2[0] + f1 * r[1][0];
          o1[1] = o2[1] + f1 * r[1][1];
          o1[2] = o2[2] + f1 * r[1][2];
          for(CMLuint32 c0=0; c0<dim[0]; c0++){
            float f0 = (float)c0*invdim[0];
            *ptr++ = o1[0] + f0 * r[0][0];
            *ptr++ = o1[1] + f0 * r[0][1];
            *ptr++ = o1[2] + f0 * r[0][2];
          }
        }
      }
      break;
    case 4:
      for(CMLuint32 c3=0; c3<dim[3]; c3++){
        float f3 = (float)c3*invdim[3];
        o3[0] = o[0] + f3 * r[3][0];
        o3[1] = o[1] + f3 * r[3][1];
        o3[2] = o[2] + f3 * r[3][2];
        for(CMLuint32 c2=0; c2<dim[2]; c2++){
          float f2 = (float)c2*invdim[2];
          o2[0] = o3[0] + f2 * r[2][0];
          o2[1] = o3[1] + f2 * r[2][1];
          o2[2] = o3[2] + f2 * r[2][2];
          for(CMLuint32 c1=0; c1<dim[1]; c1++){
            float f1 = (float)c1*invdim[1];
            o1[0] = o2[0] + f1 * r[1][0];
            o1[1] = o2[1] + f1 * r[1][1];
            o1[2] = o2[2] + f1 * r[1][2];
            for(CMLuint32 c0=0; c0<dim[0]; c0++){
              float f0 = (float)c0*invdim[0];
              *ptr++ = o1[0] + f0 * r[0][0];
              *ptr++ = o1[1] + f0 * r[0][1];
              *ptr++ = o1[2] + f0 * r[0][2];
            }
          }
        }
      }
      break;
    }
    break;

  case 4:
    switch(dimcount){
    case 0:
      cmlCpy4(ptr, o);
      break;
    case 1:
      for(CMLuint32 c0=0; c0<dim[0]; c0++){
        float f0 = (float)c0*invdim[0];
        *ptr++ = o[0] + f0 * r[0][0];
        *ptr++ = o[1] + f0 * r[0][1];
        *ptr++ = o[2] + f0 * r[0][2];
        *ptr++ = o[3] + f0 * r[0][3];
      }
      break;
    case 2:
      for(CMLuint32 c1=0; c1<dim[1]; c1++){
        float f1 = (float)c1*invdim[1];
        o1[0] = o[0] + f1 * r[1][0];
        o1[1] = o[1] + f1 * r[1][1];
        o1[2] = o[2] + f1 * r[1][2];
        o1[3] = o[3] + f1 * r[1][3];
        for(CMLuint32 c0=0; c0<dim[0]; c0++){
          float f0 = (float)c0*invdim[0];
          *ptr++ = o1[0] + f0 * r[0][0];
          *ptr++ = o1[1] + f0 * r[0][1];
          *ptr++ = o1[2] + f0 * r[0][2];
          *ptr++ = o1[3] + f0 * r[0][3];
        }
      }
      break;
    case 3:
      for(CMLuint32 c2=0; c2<dim[2]; c2++){
        float f2 = (float)c2*invdim[2];
        o2[0] = o[0] + f2 * r[2][0];
        o2[1] = o[1] + f2 * r[2][1];
        o2[2] = o[2] + f2 * r[2][2];
        o2[3] = o[3] + f2 * r[2][3];
        for(CMLuint32 c1=0; c1<dim[1]; c1++){
          float f1 = (float)c1*invdim[1];
          o1[0] = o2[0] + f1 * r[1][0];
          o1[1] = o2[1] + f1 * r[1][1];
          o1[2] = o2[2] + f1 * r[1][2];
          o1[3] = o2[3] + f1 * r[1][3];
          for(CMLuint32 c0=0; c0<dim[0]; c0++){
            float f0 = (float)c0*invdim[0];
            *ptr++ = o1[0] + f0 * r[0][0];
            *ptr++ = o1[1] + f0 * r[0][1];
            *ptr++ = o1[2] + f0 * r[0][2];
            *ptr++ = o1[3] + f0 * r[0][3];
          }
        }
      }
      break;
    case 4:
      for(CMLuint32 c3=0; c3<dim[3]; c3++){
        float f3 = (float)c3*invdim[3];
        o3[0] = o[0] + f3 * r[3][0];
        o3[1] = o[1] + f3 * r[3][1];
        o3[2] = o[2] + f3 * r[3][2];
        o3[3] = o[3] + f3 * r[3][3];
        for(CMLuint32 c2=0; c2<dim[2]; c2++){
          float f2 = (float)c2*invdim[2];
          o2[0] = o3[0] + f2 * r[2][0];
          o2[1] = o3[1] + f2 * r[2][1];
          o2[2] = o3[2] + f2 * r[2][2];
          o2[3] = o3[3] + f2 * r[2][3];
          for(CMLuint32 c1=0; c1<dim[1]; c1++){
            float f1 = (float)c1*invdim[1];
            o1[0] = o2[0] + f1 * r[1][0];
            o1[1] = o2[1] + f1 * r[1][1];
            o1[2] = o2[2] + f1 * r[1][2];
            o1[3] = o2[3] + f1 * r[1][3];
            for(CMLuint32 c0=0; c0<dim[0]; c0++){
              float f0 = (float)c0*invdim[0];
              *ptr++ = o1[0] + f0 * r[0][0];
              *ptr++ = o1[1] + f0 * r[0][1];
              *ptr++ = o1[2] + f0 * r[0][2];
              *ptr++ = o1[3] + f0 * r[0][3];
            }
          }
        }
      }
      break;
    }
    break;
  }
  
  return array;
}






@implementation ThreeDeeDisplay

- (id)initWithFrame:(NSRect)frameRect {
  NSOpenGLPixelFormatAttribute attr[] = {
		NSOpenGLPFADoubleBuffer,
		NSOpenGLPFAColorSize, 32,
		NSOpenGLPFADepthSize, 16,
    NSOpenGLPFAAlphaSize, 8,
    NSOpenGLPFAAllowOfflineRenderers, // lets OpenGL know this context is offline renderer aware
		0 };
	NSOpenGLPixelFormat *pixelformat = [[NSOpenGLPixelFormat alloc] initWithAttributes:attr];
  
  if (!pixelformat) {NSLog(@"No OpenGL pixel format");}

  self = [super initWithFrame:frameRect pixelFormat: [pixelformat autorelease]];
//  if([self respondsToSelector:@selector(setWantsBestResolutionOpenGLSurface:)]){
//    #if defined __MAC_10_7 || defined __MAC_10_8
//      [self setWantsBestResolutionOpenGLSurface:YES];
//    #endif
//  }
  return self;
}


- (void)awakeFromNib{
  viewpol = 1.3f;
  viewequ = NA_PIf / 4.f;
  zoom = 1.f;
  [self getWidthHeight];
}

- (void)getWidthHeight{
  width = (CMLint32)ceil([self bounds].size.width);
  height = (CMLint32)ceil([self bounds].size.height);
}

- (void)fixViewParameters{
  if(zoom <= .025f){zoom = .025f;}
  if(zoom >= 2.f){zoom = 2.f;}
  if(viewequ < -NA_PIf){viewequ += NA_PI2f;}
  if(viewequ > NA_PIf){viewequ -= NA_PI2f;}
  if(viewpol <= NA_SINGULARITYf){viewpol = NA_SINGULARITYf;}
  if(viewpol >= NA_PIf - NA_SINGULARITYf){viewpol = NA_PIf - NA_SINGULARITYf;}
}

- (void)rotateBy:(float)rotation{
  viewequ += rotation;
  [self fixViewParameters];
}

- (void) prepareOpenGL{
  [super prepareOpenGL];
  GLint swapInt = 1;
  [[self openGLContext] setValues:&swapInt forParameter:NSOpenGLCPSwapInterval];
  glEnable(GL_POINT_SMOOTH);
  glEnable(GL_LINE_SMOOTH);
  glEnable(GL_BLEND);
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
  glEnable(GL_DEPTH_TEST);
}


- (void)reshape{
  [super reshape];
  CMLint32 oldwidth = width;
  [self getWidthHeight];
  zoom /= (float)width / (float)oldwidth;
  [self fixViewParameters];
}

-(void) drawRect: (NSRect) rect{
  [[self openGLContext] makeCurrentContext];
  
  CMLVec3 backgroundRGB;
  [controller getBackgroundRGB:backgroundRGB];
  CMLVec3 axisRGB;
  [controller getAxisRGB:axisRGB];
  bool showaxis = [controller getShowAxis];
  CMLColorType space3d = [controller getColorSpace];
  CoordSystemType coord3d = [controller getCoordinateSpace];
  uint8 steps3d = [controller getSteps];
  bool bodysolid = [controller getBodySolid];
  float pointsalpha = [controller getPointsAlpha];
  uint8 bodyalpha = [controller getBodyAlpha];
  uint8 gridalpha = [controller getGridAlpha];
  float gridwhiteness = [controller getGridWhiteness];
  bool showspectrum = [controller getShowSpectrum];

  CMLColorMachine* cm = [(ColorMachineApplication*)NSApp getCurrentMachine];

  // ////////////////
  // Setup the openGL view
  // ////////////////

  float fovy = [controller getFovy];
  glViewport(0, 0, (GLsizei)width, (GLsizei)height);
  
  float curzoom;
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  if(fovy == 0){
    glOrtho(-(width/200.) * zoom, (width/200.) * zoom, -(height/200.) * zoom, (height/200.) * zoom, -50., 50.);
    curzoom = zoom;
  }else{
//    gluPerspective(fovy, (float)width / (float)height, .1, 50.);
//    curzoom = (width / 300.f) * zoom / (2.f * ((float)width / (float)height) * tanf(.5f * DegtoRad(fovy)));
  }

  glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();


  int primeaxis;
  float scale[3];
//  NAString* labels[3];
  CMLNormedConverter normedcoordconverter;
  CMLColorType coordspace;

  switch(coord3d){
  case COORDSYSTEM_XYZ:
    coordspace = CML_COLOR_XYZ;
    primeaxis = 1;
    cmlSet3(scale, 1.f, 1.f, 1.f);
//    labels[0] = "X";
//    labels[1] = "Y";
//    labels[2] = "Z";
    normedcoordconverter = cmlGetNormedOutputConverter(CML_COLOR_XYZ);
    break;
  case COORDSYSTEM_YXY:
    coordspace = CML_COLOR_Yxy;
    primeaxis = 0;
    cmlSet3(scale, 1.f, 1.f, 1.f);
//    labels[0] = "Y";
//    labels[1] = "x";
//    labels[2] = "y";
    normedcoordconverter = cmlGetNormedOutputConverter(CML_COLOR_Yxy);
    break;
  case COORDSYSTEM_Yuv:
    coordspace = CML_COLOR_Yuv;
    primeaxis = 0;
    cmlSet3(scale, 1.f, 1.f, 1.f);
//    labels[0] = "Y";
//    labels[1] = "u";
//    labels[2] = "v";
    normedcoordconverter = cmlGetNormedOutputConverter(CML_COLOR_Yuv);
    break;
  case COORDSYSTEM_YCBCR:
    coordspace = CML_COLOR_YCbCr;
    primeaxis = 0;
    cmlSet3(scale, 1.f, 1.f, 1.f);
//    labels[0] = "Y";
//    labels[1] = "Cb";
//    labels[2] = "Cr";
    normedcoordconverter = cmlGetNormedOutputConverter(CML_COLOR_YCbCr);
    break;
  case COORDSYSTEM_LAB:
    coordspace = CML_COLOR_Lab;
    primeaxis = 0;
    cmlSet3(scale, 1.f, 2.56f, 2.56f);
//    labels[0] = "L";
//    labels[1] = "a";
//    labels[2] = "b";
    normedcoordconverter = cmlGetNormedOutputConverter(CML_COLOR_Lab);
    break;
  case COORDSYSTEM_LCH_CARTESIAN:
    coordspace = CML_COLOR_Lch;
    primeaxis = 0;
    cmlSet3(scale, 1.f, 1.f, 3.60f);
//    labels[0] = "L";
//    labels[1] = "c";
//    labels[2] = "h";
    normedcoordconverter = cmlGetNormedOutputConverter(CML_COLOR_Lch);
    break;
  case COORDSYSTEM_LUV:
    coordspace = CML_COLOR_Luv;
    primeaxis = 0;
    cmlSet3(scale, 1.f, 1.f, 1.f);
//    labels[0] = "L";
//    labels[1] = "u";
//    labels[2] = "v";
    normedcoordconverter = cmlGetNormedOutputConverter(CML_COLOR_Luv);
    break;
  case COORDSYSTEM_RGB:
    coordspace = CML_COLOR_RGB;
    primeaxis = 1;
    cmlSet3(scale, 1.f, 1.f, 1.f);
//    labels[0] = "R";
//    labels[1] = "G";
//    labels[2] = "B";
    normedcoordconverter = cmlGetNormedOutputConverter(CML_COLOR_RGB);
    break;
  case COORDSYSTEM_HSV:
    coordspace = CML_COLOR_HSV;
    primeaxis = 2;
    cmlSet3(scale, 2.f, 2.f, 1.f);
//    labels[0] = "";
//    labels[1] = "S";
//    labels[2] = "V";
    normedcoordconverter = cmlGetNormedCartesianOutputConverter(CML_COLOR_HSV);
    break;
  case COORDSYSTEM_HSV_CARTESIAN:
    coordspace = CML_COLOR_HSV;
    primeaxis = 2;
    cmlSet3(scale, 3.60f, -1.f, 1.f);
//    labels[0] = "H";
//    labels[1] = "S";
//    labels[2] = "V";
    normedcoordconverter = cmlGetNormedOutputConverter(CML_COLOR_HSV);
    break;
  case COORDSYSTEM_HSL:
    coordspace = CML_COLOR_HSL;
    primeaxis = 2;
    cmlSet3(scale, 2.f, 2.f, 1.f);
//    labels[0] = "";
//    labels[1] = "S";
//    labels[2] = "L";
    normedcoordconverter = cmlGetNormedCartesianOutputConverter(CML_COLOR_HSL);
    break;
  case COORDSYSTEM_HSL_CARTESIAN:
    coordspace = CML_COLOR_HSL;
    primeaxis = 2;
    cmlSet3(scale, 3.60f, -1.f, 1.f);
//    labels[0] = "H";
//    labels[1] = "S";
//    labels[2] = "L";
    normedcoordconverter = cmlGetNormedOutputConverter(CML_COLOR_HSL);
    break;
  default:
    return;
    break;
  }
  
//  float vshift = .2f;

  switch(primeaxis){
  case 0:
//    gluLookAt(vshift * scale[0] + curzoom * 3 * naCosf(viewpol),
//              .5f * scale[1] + curzoom * 3 * naCosf(viewequ) * naSinf(viewpol),
//              .5f * scale[2] + curzoom * 3 * naSinf(viewequ) * naSinf(viewpol),
//              vshift * scale[0], .5f * scale[1], .5f * scale[2],
//              1, 0, 0);
    break;
  case 1:
//    gluLookAt(.5f * scale[0] + curzoom * 3 * naSinf(viewequ) * naSinf(viewpol),
//              vshift * scale[1] + curzoom * 3 * naCosf(viewpol),
//              .5f * scale[2] + curzoom * 3 * naCosf(viewequ) * naSinf(viewpol),
//              .5f * scale[0], vshift * scale[1], .5f * scale[2],
//              0, 1, 0);
    break;
  case 2:
//    gluLookAt(.5f * scale[0] + curzoom * 3 * naCosf(viewequ) * naSinf(viewpol),
//              .5f * scale[1] + curzoom * 3 * naSinf(viewequ) * naSinf(viewpol),
//              vshift * scale[2] + curzoom * 3 * naCosf(viewpol),
//              .5f * scale[0], .5f * scale[1], vshift * scale[2],
//              0, 0, 1);
    break;
  }
  
  float min[3];
  float max[3];
  CMLgetMinBounds(min, coordspace);
  CMLgetMaxBounds(max, coordspace);

  CMLColorConverter coordconverter = cmlGetColorConverter(coordspace, space3d);
  CMLNormedConverter normedinputconverter = cmlGetNormedInputConverter(space3d);

  glClearColor(backgroundRGB[0], backgroundRGB[1], backgroundRGB[2], 1);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  glScaled(scale[0], scale[1], scale[2]);



  int numchannels = CMLgetNumChannels(space3d);



  // ////////////////////
  // Draw the surfaces
  // ////////////////////
  
  #define OUTLINE_MUL 1
  int32 hueindex = -1;
  if((coord3d == COORDSYSTEM_HSV_CARTESIAN) || (coord3d == COORDSYSTEM_HSL_CARTESIAN)){
    hueindex = 0;
  }else if(coord3d == COORDSYSTEM_LCH_CARTESIAN){
    hueindex = 2;
  }

  if(!bodysolid){
//    glClear(GL_DEPTH_BUFFER_BIT);
  }
  glEnable(GL_DEPTH_TEST);
  
  CMLuint32 surfacecount = 0;
  CMLVec4UInt* surfacesteps = NULL;
  CMLVec4* origins = NULL;
  CMLVec4* axis1s = NULL;
  CMLVec4* axis2s = NULL;
  switch(space3d){
  case CML_COLOR_GRAY: surfacecount = 0; break;
  case CML_COLOR_XYZ: surfacecount = 6; break;
  case CML_COLOR_Yxy: surfacecount = 4; break;
  case CML_COLOR_Yuv: surfacecount = 4; break;
  case CML_COLOR_Yupvp: surfacecount = 4; break;
  case CML_COLOR_YCbCr: surfacecount = 6; break;
  case CML_COLOR_Lab: surfacecount = 6; break;
  case CML_COLOR_Lch: surfacecount = 3; break;
  case CML_COLOR_Luv: surfacecount = 5; break;
  case CML_COLOR_RGB: surfacecount = 6; break;
  case CML_COLOR_HSV: surfacecount = 2; break;
  case CML_COLOR_HSL: surfacecount = 3; break;
  default: break;
  }

  if(surfacecount){
    surfacesteps = new CMLVec4UInt[surfacecount];
    origins = new CMLVec4[surfacecount];
    axis1s = new CMLVec4[surfacecount];
    axis2s = new CMLVec4[surfacecount];
    float** normedcolorcoords = new float*[surfacecount];
    float** rgbfloatvalues = new float*[surfacecount];
//    Byte** rgb8Bitvalues = new Byte*[surfacecount];
    float** colorcoords = new float*[surfacecount];
    float** systemcoords = new float*[surfacecount];
    float** normedsystemcoords = new float*[surfacecount];
    
    switch(space3d){
    case CML_COLOR_GRAY: break;
    case CML_COLOR_XYZ:
      cmlSet4UInt(surfacesteps[0], steps3d, steps3d, 1, 1);
      cmlSet4(origins[0], 0.f, 0.f, 0.f, 0.f);
      cmlSet4(axis1s[0], 1.f, 0.f, 0.f, 0.f);
      cmlSet4(axis2s[0], 0.f, 1.f, 0.f, 0.f);
      cmlSet4UInt(surfacesteps[1], steps3d, steps3d, 1, 1);
      cmlSet4(origins[1], 0.f, 0.f, 0.f, 0.f);
      cmlSet4(axis1s[1], 0.f, 1.f, 0.f, 0.f);
      cmlSet4(axis2s[1], 0.f, 0.f, 1.f, 0.f);
      cmlSet4UInt(surfacesteps[2], steps3d, steps3d, 1, 1);
      cmlSet4(origins[2], 0.f, 0.f, 0.f, 0.f);
      cmlSet4(axis1s[2], 0.f, 0.f, 1.f, 0.f);
      cmlSet4(axis2s[2], 1.f, 0.f, 0.f, 0.f);
      cmlSet4UInt(surfacesteps[3], steps3d, steps3d, 1, 1);
      cmlSet4(origins[3], 1.f, 1.f, 1.f, 1.f);
      cmlSet4(axis1s[3], -1.f, 0.f, 0.f, 0.f);
      cmlSet4(axis2s[3], 0.f, -1.f, 0.f, 0.f);
      cmlSet4UInt(surfacesteps[4], steps3d, steps3d, 1, 1);
      cmlSet4(origins[4], 1.f, 1.f, 1.f, 1.f);
      cmlSet4(axis1s[4], 0.f, -1.f, 0.f, 0.f);
      cmlSet4(axis2s[4], 0.f, 0.f, -1.f, 0.f);
      cmlSet4UInt(surfacesteps[5], steps3d, steps3d, 1, 1);
      cmlSet4(origins[5], 1.f, 1.f, 1.f, 1.f);
      cmlSet4(axis1s[5], 0.f, 0.f, -1.f, 0.f);
      cmlSet4(axis2s[5], -1.f, 0.f, 0.f, 0.f);
      break;
    case CML_COLOR_Yxy:
      cmlSet4UInt(surfacesteps[0], steps3d, steps3d, 1, 1);
      cmlSet4(origins[0], 0.f, 0.f, 0.f, 0.f);
      cmlSet4(axis1s[0], 0.f, 0.f, 1.f, 0.f);
      cmlSet4(axis2s[0], 1.f, 0.f, 0.f, 0.f);
      cmlSet4UInt(surfacesteps[1], steps3d, steps3d, 1, 1);
      cmlSet4(origins[1], 1.f, 1.f, 1.f, 1.f);
      cmlSet4(axis1s[1], -1.f, 0.f, 0.f, 0.f);
      cmlSet4(axis2s[1], 0.f, -1.f, 0.f, 0.f);
      cmlSet4UInt(surfacesteps[2], steps3d, steps3d, 1, 1);
      cmlSet4(origins[2], 1.f, 1.f, 1.f, 1.f);
      cmlSet4(axis1s[2], 0.f, -1.f, 0.f, 0.f);
      cmlSet4(axis2s[2], 0.f, 0.f, -1.f, 0.f);
      cmlSet4UInt(surfacesteps[3], steps3d, steps3d, 1, 1);
      cmlSet4(origins[3], 1.f, 1.f, 1.f, 1.f);
      cmlSet4(axis1s[3], 0.f, 0.f, -1.f, 0.f);
      cmlSet4(axis2s[3], -1.f, 0.f, 0.f, 0.f);
      break;
    case CML_COLOR_Yuv:
      cmlSet4UInt(surfacesteps[0], steps3d, steps3d, 1, 1);
      cmlSet4(origins[0], 0.f, 0.f, 0.f, 0.f);
      cmlSet4(axis1s[0], 0.f, 0.f, 1.f, 0.f);
      cmlSet4(axis2s[0], 1.f, 0.f, 0.f, 0.f);
      cmlSet4UInt(surfacesteps[1], steps3d, steps3d, 1, 1);
      cmlSet4(origins[1], 1.f, 1.f, 1.f, 1.f);
      cmlSet4(axis1s[1], -1.f, 0.f, 0.f, 0.f);
      cmlSet4(axis2s[1], 0.f, -1.f, 0.f, 0.f);
      cmlSet4UInt(surfacesteps[2], steps3d, steps3d, 1, 1);
      cmlSet4(origins[2], 1.f, 1.f, 1.f, 1.f);
      cmlSet4(axis1s[2], 0.f, -1.f, 0.f, 0.f);
      cmlSet4(axis2s[2], 0.f, 0.f, -1.f, 0.f);
      cmlSet4UInt(surfacesteps[3], steps3d, steps3d, 1, 1);
      cmlSet4(origins[3], 1.f, 1.f, 1.f, 1.f);
      cmlSet4(axis1s[3], 0.f, 0.f, -1.f, 0.f);
      cmlSet4(axis2s[3], -1.f, 0.f, 0.f, 0.f);
      break;
    case CML_COLOR_Yupvp:
      cmlSet4UInt(surfacesteps[0], steps3d, steps3d, 1, 1);
      cmlSet4(origins[0], 0.f, 0.f, 0.f, 0.f);
      cmlSet4(axis1s[0], 0.f, 0.f, 1.f, 0.f);
      cmlSet4(axis2s[0], 1.f, 0.f, 0.f, 0.f);
      cmlSet4UInt(surfacesteps[1], steps3d, steps3d, 1, 1);
      cmlSet4(origins[1], 1.f, 1.f, 1.f, 1.f);
      cmlSet4(axis1s[1], -1.f, 0.f, 0.f, 0.f);
      cmlSet4(axis2s[1], 0.f, -1.f, 0.f, 0.f);
      cmlSet4UInt(surfacesteps[2], steps3d, steps3d, 1, 1);
      cmlSet4(origins[2], 1.f, 1.f, 1.f, 1.f);
      cmlSet4(axis1s[2], 0.f, -1.f, 0.f, 0.f);
      cmlSet4(axis2s[2], 0.f, 0.f, -1.f, 0.f);
      cmlSet4UInt(surfacesteps[3], steps3d, steps3d, 1, 1);
      cmlSet4(origins[3], 1.f, 1.f, 1.f, 1.f);
      cmlSet4(axis1s[3], 0.f, 0.f, -1.f, 0.f);
      cmlSet4(axis2s[3], -1.f, 0.f, 0.f, 0.f);
      break;
    case CML_COLOR_YCbCr:
      cmlSet4UInt(surfacesteps[0], steps3d, steps3d, 1, 1);
      cmlSet4(origins[0], 0.f, 0.f, 0.f, 0.f);
      cmlSet4(axis1s[0], 1.f, 0.f, 0.f, 0.f);
      cmlSet4(axis2s[0], 0.f, 1.f, 0.f, 0.f);
      cmlSet4UInt(surfacesteps[1], steps3d, steps3d, 1, 1);
      cmlSet4(origins[1], 0.f, 0.f, 0.f, 0.f);
      cmlSet4(axis1s[1], 0.f, 1.f, 0.f, 0.f);
      cmlSet4(axis2s[1], 0.f, 0.f, 1.f, 0.f);
      cmlSet4UInt(surfacesteps[2], steps3d, steps3d, 1, 1);
      cmlSet4(origins[2], 0.f, 0.f, 0.f, 0.f);
      cmlSet4(axis1s[2], 0.f, 0.f, 1.f, 0.f);
      cmlSet4(axis2s[2], 1.f, 0.f, 0.f, 0.f);
      cmlSet4UInt(surfacesteps[3], steps3d, steps3d, 1, 1);
      cmlSet4(origins[3], 1.f, 1.f, 1.f, 1.f);
      cmlSet4(axis1s[3], -1.f, 0.f, 0.f, 0.f);
      cmlSet4(axis2s[3], 0.f, -1.f, 0.f, 0.f);
      cmlSet4UInt(surfacesteps[4], steps3d, steps3d, 1, 1);
      cmlSet4(origins[4], 1.f, 1.f, 1.f, 1.f);
      cmlSet4(axis1s[4], 0.f, -1.f, 0.f, 0.f);
      cmlSet4(axis2s[4], 0.f, 0.f, -1.f, 0.f);
      cmlSet4UInt(surfacesteps[5], steps3d, steps3d, 1, 1);
      cmlSet4(origins[5], 1.f, 1.f, 1.f, 1.f);
      cmlSet4(axis1s[5], 0.f, 0.f, -1.f, 0.f);
      cmlSet4(axis2s[5], -1.f, 0.f, 0.f, 0.f);
      break;
    case CML_COLOR_Lab:
      cmlSet4UInt(surfacesteps[0], steps3d, steps3d, 1, 1);
      cmlSet4(origins[0], 0.f, 0.f, 0.f, 0.f);
      cmlSet4(axis1s[0], 1.f, 0.f, 0.f, 0.f);
      cmlSet4(axis2s[0], 0.f, 1.f, 0.f, 0.f);
      cmlSet4UInt(surfacesteps[1], steps3d, steps3d, 1, 1);
      cmlSet4(origins[1], 0.f, 0.f, 0.f, 0.f);
      cmlSet4(axis1s[1], 0.f, 1.f, 0.f, 0.f);
      cmlSet4(axis2s[1], 0.f, 0.f, 1.f, 0.f);
      cmlSet4UInt(surfacesteps[2], steps3d, steps3d, 1, 1);
      cmlSet4(origins[2], 0.f, 0.f, 0.f, 0.f);
      cmlSet4(axis1s[2], 0.f, 0.f, 1.f, 0.f);
      cmlSet4(axis2s[2], 1.f, 0.f, 0.f, 0.f);
      cmlSet4UInt(surfacesteps[3], steps3d, steps3d, 1, 1);
      cmlSet4(origins[3], 1.f, 1.f, 1.f, 1.f);
      cmlSet4(axis1s[3], -1.f, 0.f, 0.f, 0.f);
      cmlSet4(axis2s[3], 0.f, -1.f, 0.f, 0.f);
      cmlSet4UInt(surfacesteps[4], steps3d, steps3d, 1, 1);
      cmlSet4(origins[4], 1.f, 1.f, 1.f, 1.f);
      cmlSet4(axis1s[4], 0.f, -1.f, 0.f, 0.f);
      cmlSet4(axis2s[4], 0.f, 0.f, -1.f, 0.f);
      cmlSet4UInt(surfacesteps[5], steps3d, steps3d, 1, 1);
      cmlSet4(origins[5], 1.f, 1.f, 1.f, 1.f);
      cmlSet4(axis1s[5], 0.f, 0.f, -1.f, 0.f);
      cmlSet4(axis2s[5], -1.f, 0.f, 0.f, 0.f);
      break;
    case CML_COLOR_Lch:
      cmlSet4UInt(surfacesteps[0], steps3d, steps3d * 3 + 1, 1, 1);
      cmlSet4(origins[0], 0.f, 0.f, 0.f, 0.f);
      cmlSet4(axis1s[0], 0.f, 1.f, 0.f, 0.f);
      cmlSet4(axis2s[0], 0.f, 0.f, 1.f, 0.f);
      cmlSet4UInt(surfacesteps[1], steps3d, steps3d * 3 + 1, 1, 1);
      cmlSet4(origins[1], 1.f, 1.f, 1.f, 1.f);
      cmlSet4(axis1s[1], 0.f, -1.f, 0.f, 0.f);
      cmlSet4(axis2s[1], 0.f, 0.f, -1.f, 0.f);
      cmlSet4UInt(surfacesteps[2], steps3d * 3 + 1, steps3d, 1, 1);
      cmlSet4(origins[2], 1.f, 1.f, 1.f, 1.f);
      cmlSet4(axis1s[2], 0.f, 0.f, -1.f, 0.f);
      cmlSet4(axis2s[2], -1.f, 0.f, 0.f, 0.f);
      break;
    case CML_COLOR_Luv:
      cmlSet4UInt(surfacesteps[0], steps3d, steps3d, 1, 1);
      cmlSet4(origins[0], 0.f, 0.f, 0.f, 0.f);
      cmlSet4(axis1s[0], 1.f, 0.f, 0.f, 0.f);
      cmlSet4(axis2s[0], 0.f, 1.f, 0.f, 0.f);
      cmlSet4UInt(surfacesteps[1], steps3d, steps3d, 1, 1);
      cmlSet4(origins[1], 0.f, 0.f, 0.f, 0.f);
      cmlSet4(axis1s[1], 0.f, 0.f, 1.f, 0.f);
      cmlSet4(axis2s[1], 1.f, 0.f, 0.f, 0.f);
      cmlSet4UInt(surfacesteps[2], steps3d, steps3d, 1, 1);
      cmlSet4(origins[2], 1.f, 1.f, 1.f, 1.f);
      cmlSet4(axis1s[2], -1.f, 0.f, 0.f, 0.f);
      cmlSet4(axis2s[2], 0.f, -1.f, 0.f, 0.f);
      cmlSet4UInt(surfacesteps[3], steps3d, steps3d, 1, 1);
      cmlSet4(origins[3], 1.f, 1.f, 1.f, 1.f);
      cmlSet4(axis1s[3], 0.f, -1.f, 0.f, 0.f);
      cmlSet4(axis2s[3], 0.f, 0.f, -1.f, 0.f);
      cmlSet4UInt(surfacesteps[4], steps3d, steps3d, 1, 1);
      cmlSet4(origins[4], 1.f, 1.f, 1.f, 1.f);
      cmlSet4(axis1s[4], 0.f, 0.f, -1.f, 0.f);
      cmlSet4(axis2s[4], -1.f, 0.f, 0.f, 0.f);
      break;
    case CML_COLOR_RGB:
      cmlSet4UInt(surfacesteps[0], steps3d, steps3d, 1, 1);
      cmlSet4(origins[0], 0.f, 0.f, 0.f, 0.f);
      cmlSet4(axis1s[0], 1.f, 0.f, 0.f, 0.f);
      cmlSet4(axis2s[0], 0.f, 1.f, 0.f, 0.f);
      cmlSet4UInt(surfacesteps[1], steps3d, steps3d, 1, 1);
      cmlSet4(origins[1], 0.f, 0.f, 0.f, 0.f);
      cmlSet4(axis1s[1], 0.f, 1.f, 0.f, 0.f);
      cmlSet4(axis2s[1], 0.f, 0.f, 1.f, 0.f);
      cmlSet4UInt(surfacesteps[2], steps3d, steps3d, 1, 1);
      cmlSet4(origins[2], 0.f, 0.f, 0.f, 0.f);
      cmlSet4(axis1s[2], 0.f, 0.f, 1.f, 0.f);
      cmlSet4(axis2s[2], 1.f, 0.f, 0.f, 0.f);
      cmlSet4UInt(surfacesteps[3], steps3d, steps3d, 1, 1);
      cmlSet4(origins[3], 1.f, 1.f, 1.f, 1.f);
      cmlSet4(axis1s[3], -1.f, 0.f, 0.f, 0.f);
      cmlSet4(axis2s[3], 0.f, -1.f, 0.f, 0.f);
      cmlSet4UInt(surfacesteps[4], steps3d, steps3d, 1, 1);
      cmlSet4(origins[4], 1.f, 1.f, 1.f, 1.f);
      cmlSet4(axis1s[4], 0.f, -1.f, 0.f, 0.f);
      cmlSet4(axis2s[4], 0.f, 0.f, -1.f, 0.f);
      cmlSet4UInt(surfacesteps[5], steps3d, steps3d, 1, 1);
      cmlSet4(origins[5], 1.f, 1.f, 1.f, 1.f);
      cmlSet4(axis1s[5], 0.f, 0.f, -1.f, 0.f);
      cmlSet4(axis2s[5], -1.f, 0.f, 0.f, 0.f);
      break;
    case CML_COLOR_HSV:
      cmlSet4UInt(surfacesteps[0], steps3d * 3 + 1, steps3d, 1, 1);
      cmlSet4(origins[0], 1.f, 1.f, 1.f, 1.f);
      cmlSet4(axis1s[0], -1.f, 0.f, 0.f, 0.f);
      cmlSet4(axis2s[0], 0.f, -1.f, 0.f, 0.f);
      cmlSet4UInt(surfacesteps[1], steps3d, steps3d * 3 + 1, 1, 1);
      cmlSet4(origins[1], 1.f, 1.f, 1.f, 1.f);
      cmlSet4(axis1s[1], 0.f, 0.f, -1.f, 0.f);
      cmlSet4(axis2s[1], -1.f, 0.f, 0.f, 0.f);
      break;
    case CML_COLOR_HSL:
      cmlSet4UInt(surfacesteps[0], steps3d * 3 + 1, steps3d, 1, 1);
      cmlSet4(origins[0], 0.f, 0.f, 0.f, 0.f);
      cmlSet4(axis1s[0], 1.f, 0.f, 0.f, 0.f);
      cmlSet4(axis2s[0], 0.f, 1.f, 0.f, 0.f);
      cmlSet4UInt(surfacesteps[1], steps3d * 3 + 1, steps3d, 1, 1);
      cmlSet4(origins[1], 1.f, 1.f, 1.f, 1.f);
      cmlSet4(axis1s[1], -1.f, 0.f, 0.f, 0.f);
      cmlSet4(axis2s[1], 0.f, -1.f, 0.f, 0.f);
      cmlSet4UInt(surfacesteps[2], steps3d, steps3d * 3 + 1, 1, 1);
      cmlSet4(origins[2], 1.f, 1.f, 1.f, 1.f);
      cmlSet4(axis1s[2], 0.f, 0.f, -1.f, 0.f);
      cmlSet4(axis2s[2], -1.f, 0.f, 0.f, 0.f);
      break;
    default: break;
    }

    for(CMLuint32 s=0; s<surfacecount; s++){
      CMLuint32 totalcount = surfacesteps[s][0] * surfacesteps[s][1] * surfacesteps[s][2] * surfacesteps[s][3];
      normedcolorcoords[s] = (float*)CMLcreateNormedGamutSlice(space3d, surfacesteps[s], origins[s], axis1s[s], axis2s[s], NULL, NULL);
      rgbfloatvalues[s] = new float[totalcount*3];
      colorcoords[s] = new float[totalcount*numchannels];
      systemcoords[s] = new float[totalcount*3];
      normedsystemcoords[s] = new float[totalcount*3];

      normedinputconverter(colorcoords[s], normedcolorcoords[s], totalcount);
      coordconverter(cm, systemcoords[s], colorcoords[s], totalcount);
      normedcoordconverter(normedsystemcoords[s], systemcoords[s], totalcount);
      
      // Convert the given values to screen RGBs.
      [(ColorMachineApplication*)NSApp  fillRGBfloatarray:rgbfloatvalues[s]
                                        fromArray:normedcolorcoords[s]
                                    withColorType:space3d
                             normedInputConverter:normedinputconverter
                                            count:totalcount
                                         drawgrid:false
                                         drawmask:false];
    }
    
    // ////////////////////
    // Draw the quads
    // ////////////////////

    for(CMLuint32 s=0; s<surfacecount; s++){
      glEnable(GL_POLYGON_OFFSET_FILL);
      glPolygonOffset(1.f, 1.f);
      glShadeModel(GL_FLAT);
      glBegin(GL_QUADS);
      for(CMLuint32 ax1 = 0; ax1 < surfacesteps[s][1] - 1; ax1++){
        for(CMLuint32 ax2 = 0; ax2 < surfacesteps[s][0] - 1; ax2++){
          int index0 = (ax1 + 0) * surfacesteps[s][0] * 3 + (ax2 + 0) * 3;
          int index1 = (ax1 + 0) * surfacesteps[s][0] * 3 + (ax2 + 1) * 3;
          int index2 = (ax1 + 1) * surfacesteps[s][0] * 3 + (ax2 + 1) * 3;
          int index3 = (ax1 + 1) * surfacesteps[s][0] * 3 + (ax2 + 0) * 3;

          glColor4f(rgbfloatvalues[s][index3 + 0] * bodyalpha / 255.f + backgroundRGB[0] * (1.f - bodyalpha / 255.f),
                    rgbfloatvalues[s][index3 + 1] * bodyalpha / 255.f + backgroundRGB[1] * (1.f - bodyalpha / 255.f),
                    rgbfloatvalues[s][index3 + 2] * bodyalpha / 255.f + backgroundRGB[2] * (1.f - bodyalpha / 255.f),
                    1.f);

          if(hueindex >= 0){
            if(    (fabsf(normedsystemcoords[s][index0 + hueindex] - normedsystemcoords[s][index1 + hueindex]) > .5f)
                || (fabsf(normedsystemcoords[s][index0 + hueindex] - normedsystemcoords[s][index2 + hueindex]) > .5f)
                || (fabsf(normedsystemcoords[s][index0 + hueindex] - normedsystemcoords[s][index3 + hueindex]) > .5f)){
              continue;
            }
          }
          
          glVertex3fv(&(normedsystemcoords[s][index0]));
          glVertex3fv(&(normedsystemcoords[s][index1]));
          glVertex3fv(&(normedsystemcoords[s][index2]));
          glVertex3fv(&(normedsystemcoords[s][index3]));
        }
      }
      glEnd();
      glPolygonOffset(0.f, 0.f);
      glDisable(GL_POLYGON_OFFSET_FILL);
    }

    if(!bodysolid){
      glClear(GL_DEPTH_BUFFER_BIT);
    }

    // ////////////////////
    // Draw the lines
    // ////////////////////

    for(CMLuint32 s=0; s<surfacecount; s++){
      if(gridalpha > 0.f){
        glShadeModel(GL_SMOOTH);
        glDepthFunc(GL_LEQUAL);
        for(CMLuint32 ax1 = 0; ax1 < surfacesteps[s][1] - 1; ax1++){
          for(CMLuint32 ax2 = 0; ax2 < surfacesteps[s][0] - 1; ax2++){
            int index0 = (ax1 + 0) * surfacesteps[s][0] * 3 + (ax2 + 0) * 3;
            int index1 = (ax1 + 0) * surfacesteps[s][0] * 3 + (ax2 + 1) * 3;
            int index2 = (ax1 + 1) * surfacesteps[s][0] * 3 + (ax2 + 1) * 3;
            int index3 = (ax1 + 1) * surfacesteps[s][0] * 3 + (ax2 + 0) * 3;
            if(hueindex >= 0){
              if(    (fabsf(normedsystemcoords[s][index0 + hueindex] - normedsystemcoords[s][index1 + hueindex]) > .5f)
                  || (fabsf(normedsystemcoords[s][index0 + hueindex] - normedsystemcoords[s][index2 + hueindex]) > .5f)
                  || (fabsf(normedsystemcoords[s][index0 + hueindex] - normedsystemcoords[s][index3 + hueindex]) > .5f)){
                continue;
              }
            }
            glBegin(GL_LINE_STRIP);
            glColor4f( rgbfloatvalues[s][index0 + 0] * (1.f - gridwhiteness) + axisRGB[0] * gridwhiteness,
                        rgbfloatvalues[s][index0 + 1] * (1.f - gridwhiteness) + axisRGB[1] * gridwhiteness,
                        rgbfloatvalues[s][index0 + 2] * (1.f - gridwhiteness) + axisRGB[2] * gridwhiteness, gridalpha / 255.f);
            glVertex3fv(&(normedsystemcoords[s][index0]));
            glColor4f( rgbfloatvalues[s][index1 + 0] * (1.f - gridwhiteness) + axisRGB[0] * gridwhiteness,
                        rgbfloatvalues[s][index1 + 1] * (1.f - gridwhiteness) + axisRGB[1] * gridwhiteness,
                        rgbfloatvalues[s][index1 + 2] * (1.f - gridwhiteness) + axisRGB[2] * gridwhiteness, gridalpha / 255.f);
            glVertex3fv(&(normedsystemcoords[s][index1]));
            glColor4f( rgbfloatvalues[s][index2 + 0] * (1.f - gridwhiteness) + axisRGB[0] * gridwhiteness,
                        rgbfloatvalues[s][index2 + 1] * (1.f - gridwhiteness) + axisRGB[1] * gridwhiteness,
                        rgbfloatvalues[s][index2 + 2] * (1.f - gridwhiteness) + axisRGB[2] * gridwhiteness, gridalpha / 255.f);
            glVertex3fv(&(normedsystemcoords[s][index2]));
            glColor4f( rgbfloatvalues[s][index3 + 0] * (1.f - gridwhiteness) + axisRGB[0] * gridwhiteness,
                        rgbfloatvalues[s][index3 + 1] * (1.f - gridwhiteness) + axisRGB[1] * gridwhiteness,
                        rgbfloatvalues[s][index3 + 2] * (1.f - gridwhiteness) + axisRGB[2] * gridwhiteness, gridalpha / 255.f);
            glVertex3fv(&(normedsystemcoords[s][index3]));
            glColor4f( rgbfloatvalues[s][index0 + 0] * (1.f - gridwhiteness) + axisRGB[0] * gridwhiteness,
                        rgbfloatvalues[s][index0 + 1] * (1.f - gridwhiteness) + axisRGB[1] * gridwhiteness,
                        rgbfloatvalues[s][index0 + 2] * (1.f - gridwhiteness) + axisRGB[2] * gridwhiteness, gridalpha / 255.f);
            glVertex3fv(&(normedsystemcoords[s][index0]));

            glEnd();
          }
        }
        glDepthFunc(GL_LESS);
      }

    }

    for(CMLuint32 s=0; s<surfacecount; s++){
      delete [] normedsystemcoords[s];
      delete [] systemcoords[s];
      delete [] colorcoords[s];
      delete [] rgbfloatvalues[s];
      free(normedcolorcoords[s]);
    }

    delete [] normedsystemcoords;
    delete [] systemcoords;
    delete [] colorcoords;
    delete [] rgbfloatvalues;
    delete [] normedcolorcoords;
    delete [] surfacesteps;
    delete [] origins;
    delete [] axis1s;
    delete [] axis2s;
  }
  
  
 
  // ////////////////////
  // Draw the point cloud
  // ////////////////////

  if(pointsalpha > 0.f){
    CMLVec4UInt steps;
    switch(space3d){
    case CML_COLOR_GRAY: cmlSet4UInt(steps, 2*steps3d, 1, 1, 1); break;
    case CML_COLOR_XYZ: cmlSet4UInt(steps, steps3d, steps3d, steps3d, 1); break;
    case CML_COLOR_Yxy: cmlSet4UInt(steps, steps3d, steps3d, steps3d, 1); break;
    case CML_COLOR_Yuv: cmlSet4UInt(steps, steps3d, steps3d, steps3d, 1); break;
    case CML_COLOR_Yupvp: cmlSet4UInt(steps, steps3d, steps3d, steps3d, 1); break;
    case CML_COLOR_YCbCr: cmlSet4UInt(steps, steps3d, steps3d, steps3d, 1); break;
    case CML_COLOR_Lab: cmlSet4UInt(steps, steps3d, steps3d, steps3d, 1); break;
    case CML_COLOR_Lch: cmlSet4UInt(steps, steps3d, steps3d, 3*steps3d + 1, 1); break;
    case CML_COLOR_Luv: cmlSet4UInt(steps, steps3d, steps3d, steps3d, 1); break;
    case CML_COLOR_RGB: cmlSet4UInt(steps, steps3d, steps3d, steps3d, 1); break;
    case CML_COLOR_HSV: cmlSet4UInt(steps, 3*steps3d + 1, steps3d, steps3d, 1); break;
    case CML_COLOR_HSL: cmlSet4UInt(steps, 3*steps3d + 1, steps3d, steps3d, 1); break;
    default: cmlSet4UInt(steps, 1, 1, 1, 1); break;
    }
    CMLuint32 totalcloudcount = steps[0] * steps[1] * steps[2] * steps[3];
    float* cloudnormedcolorcoords = (float*)CMLcreateNormedGamutSlice(space3d, steps, NULL, NULL, NULL, NULL, NULL);
    float* cloudrgbfloatvalues = new float[totalcloudcount*3];
    float* cloudcolorcoords = new float[totalcloudcount*numchannels];
    float* cloudsystemcoords = new float[totalcloudcount*3];
    float* cloudnormedsystemcoords = new float[totalcloudcount*3];

    normedinputconverter(cloudcolorcoords, cloudnormedcolorcoords, totalcloudcount);
    coordconverter(cm, cloudsystemcoords, cloudcolorcoords, totalcloudcount);
    normedcoordconverter(cloudnormedsystemcoords, cloudsystemcoords, totalcloudcount);
    
    // Convert the given values to screen RGBs.
    [(ColorMachineApplication*)NSApp  fillRGBfloatarray:cloudrgbfloatvalues
                                      fromArray:cloudnormedcolorcoords
                                  withColorType:space3d
                           normedInputConverter:normedinputconverter
                                          count:totalcloudcount
                                       drawgrid:false
                                       drawmask:false];

    glDisable(GL_DEPTH_TEST);
    
    glPointSize((2.f / numchannels) / zoom);
    glBegin(GL_POINTS);
    for(CMLuint32 i=0; i<totalcloudcount; i++){
      glColor4f(cloudrgbfloatvalues[i * 3 + 0], cloudrgbfloatvalues[i * 3 + 1], cloudrgbfloatvalues[i * 3 + 2], pointsalpha);
      glVertex3fv(&(cloudnormedsystemcoords[i * 3]));
    }
    glEnd();
    
//    glEnableClientState(GL_COLOR_ARRAY);
//    glColorPointer(3, GL_UNSIGNED_BYTE, 0, cloudrgb8Bitvalues);
//    glEnableClientState(GL_VERTEX_ARRAY);
//    glVertexPointer(3, GL_FLOAT, 0, cloudnormedsystemcoords);
//    glDrawArrays(GL_POINTS, 0, totalcloudcount);
//    glDisableClientState(GL_COLOR_ARRAY);
//    glDisableClientState(GL_VERTEX_ARRAY);
    delete [] cloudnormedsystemcoords;
    delete [] cloudcolorcoords;
    delete [] cloudsystemcoords;
    delete [] cloudrgbfloatvalues;
    free(cloudnormedcolorcoords);
  }


  
  
  


  // /////////////////////
  // Draw the spectral curve
  // /////////////////////

  if(showspectrum){
    float imin = CML_DEFAULT_INTEGRATION_MIN;
    float imax = CML_DEFAULT_INTEGRATION_MAX;
    int32 intervals = (int32)((imax - imin) / CML_DEFAULT_INTEGRATION_STEPSIZE) + 1;
    
    CMLColorConverter xyzconverter = cmlGetColorConverter(coordspace, CML_COLOR_XYZ);

    glBegin(GL_LINE_STRIP);
      float prevnormedhue = -CML_INFINITY;
      for(int32 istep = 0; istep <= intervals; istep++){
        float l = imin + (((imax - imin) * istep) / intervals);
        CMLVec3 curXYZ;
        CMLgetSpectralXYZColor(cm, curXYZ, l);
        if(curXYZ[1] > 0){
          CMLVec3 curRGB;
          CMLVec3 curcoords;
          CMLVec3 curnormedcoords;
          xyzconverter(cm, curcoords, curXYZ, 1);
          normedcoordconverter(curnormedcoords, curcoords, 1);
          if(hueindex >= 0){
            if((prevnormedhue != -CML_INFINITY) && (fabsf(prevnormedhue - curnormedcoords[hueindex]) > .5f)){
              glEnd();
              glBegin(GL_LINE_STRIP);      
              prevnormedhue = -CML_INFINITY;
              continue;
            }else{
              prevnormedhue = curnormedcoords[hueindex];
            }
          }
          CMLXYZtoRGB(cm, curRGB, curXYZ, 1);
          cmlMul3(curRGB, .7f);
          cmlClampRGB(curRGB, 1);
          cmlMul3(curRGB, .7f);
          glColor4f(curRGB[0], curRGB[1], curRGB[2], 1.f);
          glVertex3fv(curnormedcoords);
        }
      }
    glEnd();
  }


  // /////////////////////////
  // Draw the axis
  // /////////////////////////


  if(showaxis){
    glClear(GL_DEPTH_BUFFER_BIT);
    glColor3fv(axisRGB);

    float ax[3] = {0.f, 0.f, 0.f};
    float normedax[3];
    glBegin(GL_LINES);
      ax[0] = min[0];
      normedcoordconverter(normedax, ax, 1);
      glVertex3fv(normedax);
      ax[0] = max[0];
      normedcoordconverter(normedax, ax, 1);
      glVertex3fv(normedax);
      ax[0] = 0.f;
      ax[1] = min[1];
      normedcoordconverter(normedax, ax, 1);
      glVertex3fv(normedax);
      ax[1] = max[1];
      normedcoordconverter(normedax, ax, 1);
      glVertex3fv(normedax);
      ax[1] = 0.f;
      ax[2] = min[2];
      normedcoordconverter(normedax, ax, 1);
      glVertex3fv(normedax);
      ax[2] = max[2];
      normedcoordconverter(normedax, ax, 1);
      glVertex3fv(normedax);
      ax[2] = 0.f;
    glEnd();

    ax[0] = max[0] * 1.03f;
    normedcoordconverter(normedax, ax, 1);
//    OpenGLtextoutput(normedax[0], normedax[1], normedax[2], labels[0]);
    ax[0] = 0.f;
    ax[1] = max[1] * 1.03f;
    normedcoordconverter(normedax, ax, 1);
//    OpenGLtextoutput(normedax[0], normedax[1], normedax[2], labels[1]);
    ax[1] = 0.f;
    ax[2] = max[2] * 1.03f;
    normedcoordconverter(normedax, ax, 1);
//    OpenGLtextoutput(normedax[0], normedax[1], normedax[2], labels[2]);
    ax[2] = 0.f;
  }

  [[self openGLContext] flushBuffer];
}

- (void)mouseDown:(NSEvent*)event{
  NSPoint eventLocation = [event locationInWindow];
  NSPoint pos = [self convertPoint:eventLocation fromView:nil];
//  float scalefactor = [ColorMachineApplication getUIScaleFactorForWindow:[self window]];
  float scalefactor = 1.f;
  mousex = (float)pos.x * scalefactor;
  mousey = (float)pos.y * scalefactor;
}

- (void)mouseDragged:(NSEvent*)event{
  NSPoint eventLocation = [event locationInWindow];
  NSPoint pos = [self convertPoint:eventLocation fromView:nil];
//  float scalefactor = [ColorMachineApplication getUIScaleFactorForWindow:[self window]];
  float scalefactor = 1.f;
  float newmousex = (float)pos.x * scalefactor;
  float newmousey = (float)pos.y * scalefactor;

  viewequ -= (newmousex - mousex) * .01f;
  viewpol += (newmousey - mousey) * .01f;

  mousex = newmousex;
  mousey = newmousey;
  [self fixViewParameters];
  [self setNeedsDisplay:YES];
}


- (void)scrollWheel:(NSEvent*)event{
  zoom *= 1.f + (float)[event deltaY] * .01f;
  [self fixViewParameters];
  [self setNeedsDisplay:YES];
}


@end








const char* coordsystemnames[NUMBER_OF_COORDINATE_SYSTEMS] = {
  "XYZ",
  "Yxy",
  "Yuv",
  "YCbCr",
  "Lab",
  "Lch Cartesian",
  "Luv",
  "RGB",
  "HSV",
  "HSV Cartesian",
  "HSL",
  "HSL Cartesian",
};


@implementation ThreeDeeWindowController

- (void)awakeFromNib{
//  [[self window] makeFirstResponder:self];
  [[self window] setDelegate:self];
  backgroundgray = 0.3f;
  rotation = 0.f;
  dispatchinprogress = false;
  bodyalpha = 48;
  bodysolid = true;
  gridalpha = 255;
  gridwhiteness = .5f;

  space3d = CML_COLOR_RGB;
  coord3d = COORDSYSTEM_LAB;
  steps3d = 25;
  fovy = 50.f;
  showaxis = true;
  showspectrum = false;
  [space3dselect removeAllItems];
  for(uint32 i=0; i<CML_NUMBER_OF_COLORTYPES; ++i){
    if((CMLColorType)i >= CML_COLOR_CMYK){continue;}
    [space3dselect insertItemWithTitle:[NSString stringWithUTF8String:CMLgetColorTypeString((CMLColorType)i)] atIndex:i];
  }
  [space3dselect selectItemAtIndex:(int)space3d];

  [coord3dselect removeAllItems];
  for(uint32 i=0; i<NUMBER_OF_COORDINATE_SYSTEMS; ++i){
    [coord3dselect insertItemWithTitle:[NSString stringWithUTF8String:coordsystemnames[(CMLColorType)i]] atIndex:i];
  }
  
  semaphore = dispatch_semaphore_create(1);
  [self update];
}

- (void)dealloc{
  dispatch_release(semaphore);
  [super dealloc];
}

- (void) update{
  [space3dselect selectItemAtIndex:(int)space3d];
  [coord3dselect selectItemAtIndex:(int)coord3d];
  [steps3dslider setFloatValue:steps3d];
  [pointsalphaslider setFloatValue:pointsalpha];
  [gridalphaslider setIntValue:gridalpha];
  [gridtintsslider setFloatValue:1.f - gridwhiteness];
  [bodyalphaslider setIntValue:bodyalpha];
  [backgroundcolorslider setFloatValue:backgroundgray];
  [fovyslider setFloatValue:fovy];
  [rotationslider setFloatValue:-rotation * 40];
  [solidcheckbox setState:bodysolid?NSOnState:NSOffState];
  [axischeckbox setState:showaxis?NSOnState:NSOffState];
  [spectrumcheckbox setState:showspectrum?NSOnState:NSOffState];
  
  bool manualupdate = false;
  bool startautoupdate = false;
  long timeout = dispatch_semaphore_wait(semaphore, DISPATCH_TIME_FOREVER);
  if(timeout){return;}
  if(!dispatchinprogress){
    if(rotation != 0.){
      startautoupdate = true;
      dispatchinprogress = true;
    }else{
      manualupdate = true;
    }
  }
  dispatch_semaphore_signal(semaphore);

  if(startautoupdate){
    [self autodisplay];
  }
  if(manualupdate){
    [colordisplay setNeedsDisplay:YES];
  }
}

- (void)showDialog{
  [[self window] makeKeyAndOrderFront:self];
}

- (void)windowWillClose:(NSNotification *)notification{
  [self stopRotation:nil];
}

- (void)getBackgroundRGB:(CMLVec3) returncolor{
  cmlSet3(returncolor, backgroundgray, backgroundgray, backgroundgray);
}

- (void)getAxisRGB:(CMLVec3) returncolor{
  float axisgray = backgroundgray + .5f;
  if(axisgray > 1.f){axisgray -= 1.f;}
  cmlSet3(returncolor, axisgray, axisgray, axisgray);
}

- (float)getFovy{
  return fovy;
}

- (bool)getShowAxis{
  return showaxis;
}

- (bool)getShowSpectrum{
  return showspectrum;
}

- (CMLColorType)getColorSpace{
  return space3d;
}

- (CoordSystemType)getCoordinateSpace{
  return coord3d;
}

- (uint8)getSteps{
  return steps3d;
}

- (bool)getBodySolid{
  return bodysolid;
}

- (float)getPointsAlpha{
  return pointsalpha;
}

- (uint8)getBodyAlpha{
  return bodyalpha;
}

- (uint8)getGridAlpha{
  return gridalpha;
}

- (float)getGridWhiteness{
  return gridwhiteness;
}

- (void)autodisplay{  

  long timeout = dispatch_semaphore_wait(semaphore, DISPATCH_TIME_FOREVER);
  if(timeout){return;}

  if(rotation != 0.f){
    int64_t fps = 30;
    dispatch_time_t nexttime = dispatch_time(DISPATCH_TIME_NOW, 1000000000 / fps);
    dispatch_queue_t queue = dispatch_get_main_queue();
    dispatch_after(nexttime, queue, ^{
      [colordisplay rotateBy:rotation];
      [colordisplay setNeedsDisplay:YES];
      [self autodisplay];
      });
  }else{
    dispatchinprogress = false;
  }
  
  dispatch_semaphore_signal(semaphore);
}

//- (IBAction)switchFullscreen:(NSButton*)sender{
//  fullscreen = !fullscreen;
//  if(fullscreen){
//  }
//  [self update];
//}
//
- (IBAction)space3dChange:(NSPopUpButton*)sender {
  space3d = (CMLColorType)([sender indexOfSelectedItem]);
  if((space3d == CML_COLOR_GRAY) && (pointsalpha < .2f)){pointsalpha = 1.f;}
  [self update];
}

- (IBAction)coord3dChange:(NSPopUpButton*)sender {
  coord3d = (CoordSystemType)([sender indexOfSelectedItem]);
  [self update];
}

- (IBAction)steps3dChange:(NSSlider*)sender {
  steps3d = [sender intValue];
  [self update];
}

- (IBAction)bodyalphaChange:(NSSlider*)sender{
  bodyalpha = [sender intValue];
  [self update];
}
- (IBAction)gridwhitenessChange:(NSSlider*)sender{
  gridwhiteness = 1.f - [sender floatValue];
  [self update];
}
- (IBAction)pointsalphaChange:(NSSlider*)sender{
  pointsalpha = [sender floatValue];
  [self update];
}

- (IBAction)gridalphaChange:(NSSlider*)sender{
  gridalpha = [sender intValue];
  [self update];
}

- (IBAction)perspectivityChange:(NSSlider*)sender {
  fovy = [sender floatValue];
  if(fovy < 10.f){
    fovy = 0.f;
    [sender setFloatValue: 0.f];
  }
  [self update];
}

- (IBAction)backgroundChange:(NSSlider*)sender {
  backgroundgray = [sender floatValue];
  [self update];
}

- (IBAction)spectralChange:(NSButton*)sender {
  showspectrum = ([sender state] == NSOnState)?true:false;
  [self update];
}

- (IBAction)solidChange:(NSButton*)sender {
  bodysolid = ([sender state] == NSOnState)?true:false;
  [self update];
}

- (IBAction)axisChange:(NSButton*)sender {
  showaxis = ([sender state] == NSOnState)?true:false;
  [self update];
}

- (IBAction)rotationChange:(NSSlider*)sender {
  long timeout = dispatch_semaphore_wait(semaphore, DISPATCH_TIME_FOREVER);
  if(timeout){return;}
  rotation = -[sender floatValue] * .025f;
  if((rotation > -.0025) && (rotation < .0025)){rotation = 0.f;}
  dispatch_semaphore_signal(semaphore);
  [self update];
}

- (IBAction)stopRotation:(NSButton*)sender{
  long timeout = dispatch_semaphore_wait(semaphore, DISPATCH_TIME_FOREVER);
  if(timeout){return;}
  rotation = 0.f;
  dispatch_semaphore_signal(semaphore);
  [self update];
}

@end
