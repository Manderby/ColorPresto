
#include "mainC.h"
#include "NAMemory.h"


void fillRGBFloatArrayWithArray(const CMLColorMachine* cm, const CMLColorMachine* sm, float* outData, float* inputData, CMLColorType inputColorType, CMLNormedConverter normedConverter, size_t count, NABool drawgridlines, NABool drawmask){
  
  size_t numColorChannels = cmlGetNumChannels(inputColorType);
  CMLVec3 cmWhitePointYxy;
  CMLVec3 smWhitePointYxy;
  CMLColorConverter colorToXYZ = cmlGetColorConverter(CML_COLOR_XYZ, inputColorType);
  float* colorBuffer = naMalloc(numColorChannels * count * sizeof(float));
//  float* RGBbuffer = new float[3 * count];
  float* XYZbuffer = naMalloc(3 * count * sizeof(float));
  
  cmlCpy3(cmWhitePointYxy, cmlGetReferenceWhitePointYxy(cm));
  cmWhitePointYxy[0] = 1.f;
  cmlCpy3(smWhitePointYxy, cmlGetReferenceWhitePointYxy(sm));
  smWhitePointYxy[0] = 1.f;
  
  normedConverter(colorBuffer, inputData, count);
  colorToXYZ(cm, XYZbuffer, colorBuffer, count);
  float* aXYZbuffer = naMalloc(3 * count * sizeof(float));
  CMLMat33 amatrix;
  cmlFillChromaticAdaptationMatrix(amatrix, CML_CHROMATIC_ADAPTATION_NONE, smWhitePointYxy, cmWhitePointYxy);
  for(size_t i=0; i<count; i++){
    cmlConvertXYZToChromaticAdaptedXYZ(&(aXYZbuffer[i*3]), &(XYZbuffer[i*3]), amatrix);
  }
  cmlXYZToRGB(sm, outData, aXYZbuffer, count);
  naFree(aXYZbuffer);

//  if((showmask && drawmask) || (showgrid && drawgridlines)){
//    size_t nummaskchannels = cmlGetNumChannels(maskcolor);
//    CMLColorConverter colortomask = cmlGetColorConverter(maskcolor, inputColorType);
//    CMLNormedConverter masktonormal = cmlGetNormedOutputConverter(maskcolor);
//    float* maskbuffer = new float[count];
//    float* maskcolorarray = new float[nummaskchannels * count];
//    float* normedcolor = new float[nummaskchannels * count];
//    for(size_t i=0; i<count; i++){maskbuffer[i] = 1.f;}
//    colortomask(cm, maskcolorarray, colorBuffer, count);
//    masktonormal(normedcolor, maskcolorarray, count);
//    if(showmask && drawmask){
//      for(size_t i=0; i<count * nummaskchannels; i++){
//        if(!CMLInRange(normedcolor[i], 0.f, 1.f)){maskbuffer[i/nummaskchannels] = .2f;}
//      }
//    }
//    if(showgrid && drawgridlines){
//      float sharpness = .01f;
//      float ledge = 1.f / ((float)(bordercount + 1)) * sharpness;
//      float* coordsbuffer = new float[((bordercount + 2) * 4)];
//      float* valsbuffer = new float[((bordercount + 2) * 4)];
//      
//      for(uint32 i=0; i<bordercount + 2; i++){
//        float pos = ((float)i)/((float)(bordercount+1));
//        coordsbuffer[i*4+0] = pos - borderthickness - ledge;
//        coordsbuffer[i*4+1] = pos - borderthickness + ledge;
//        coordsbuffer[i*4+2] = pos + borderthickness - ledge;
//        coordsbuffer[i*4+3] = pos + borderthickness + ledge;
//        valsbuffer[i*4+0] = 1.f;
//        valsbuffer[i*4+1] = .5f;
//        valsbuffer[i*4+2] = .5f;
//        valsbuffer[i*4+3] = 1.f;
//      }
////      CMLArray coords(coordsbuffer, true, (bordercount + 2) * 4);
////      CMLArray vals(valsbuffer, true, (bordercount + 2) * 4);
////      CMLSampleArrayFunction gridlines(coords, vals, CML_INTERPOLATION_LINEAR, CML_EXTRAPOLATION_CLAMP);
////      for(size_t i=0; i<count * nummaskchannels; i++){
////        maskbuffer[i/nummaskchannels] *= gridlines(normedcolor[i]);
////      }
//    }
//
//    for(size_t i=0; i<count * 3; i++){
//      RGBbuffer[i] *= maskbuffer[i/3];
//    }
//    delete [] normedcolor;
//    delete [] maskcolorarray;
//    delete [] maskbuffer;
//  }
  cmlClampRGB(outData, count);
//  cmlClampRGB(RGBbuffer, count);
//  cmlRGBToData8(sm, outData, RGBbuffer, count);
  
  naFree(XYZbuffer);
//  delete [] RGBbuffer;
  naFree(colorBuffer);
}


