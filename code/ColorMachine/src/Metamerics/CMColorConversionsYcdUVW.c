
#include "CMColorConversionsYcdUVW.h"
#include "mainC.h"

void convertYuvtoYcd(float* Ycd, const float* yuv){
  cmlSet3(
    Ycd,
    yuv[0],
    (4.f - yuv[1] - 10.f * yuv[2]) / yuv[2],
    (1.708f * yuv[2] + 0.404f - 1.481f * yuv[1]) / yuv[2]);
}

void convertYcdtoadaptedYuv(float* yuv, const float* Ycd, const float* srcWhitePointYcd, const float* dstWhitePointYcd){
  float cfactor = Ycd[1] * dstWhitePointYcd[1] / srcWhitePointYcd[1];
  float dfactor = Ycd[2] * dstWhitePointYcd[2] / srcWhitePointYcd[2];
  float divisor = (16.518f + 1.481f * cfactor - dfactor);
  yuv[0] = Ycd[0];
  yuv[1] = (10.872f + 0.404f * cfactor - 4.f * dfactor) / divisor;
  yuv[2] = 5.520f / divisor;
}

// ISO 3664 states in forumal D.14 the computation 6X/(X+15Y+3Z). I'm
// pretty sure, they meant  6Y/(X+15Y+3Z) which is according to
// CIE 1960 UCS. This also corresponds to the fact that UVW is based on UCS.
// In CML, this is Yuv.
// UVW is CIE 1964.
void convertYuvtoUVW(float* UVW, float* yuv, const float* whitePointYuv){
  UVW[2] = 25.f * cmlCbrt(yuv[0] * 100.f) - 17.f;
  UVW[0] = 13.f * UVW[2] * (yuv[1] - whitePointYuv[1]);
  UVW[1] = 13.f * UVW[2] * (yuv[2] - whitePointYuv[2]);
}
