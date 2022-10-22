
#include "CMColorRenderingIndex.h"
#include "CML.h"
#include "CMWhitePoints.h"
#include "CMColorConversionsYcdUVW.h"

// Metamer names:
//Light greyish red
//Dark greyish yellow
//Strong yellow green
//Moderate yellow green
//Light bluish green
//Light blue
//Light violet
//Light reddish purple
//Strong Red
//Strong Yellow
//Strong green
//Strong blue
//Light yellowish pink
//Moderate olive green

#define METAMER_DATA_COUNT 81
#define METAMER_DATA_LAMBDA_MIN 380.f
#define METAMER_DATA_LAMBDA_MAX 780.f
const float metamer1Data[] = {
  0.219f, 0.239f, 0.252f, 0.256f, 0.256f, 0.254f, 0.252f, 0.248f, 0.244f, 0.240f,
  0.237f, 0.232f, 0.230f, 0.226f, 0.225f, 0.222f, 0.220f, 0.218f, 0.216f, 0.214f,
  0.214f, 0.214f, 0.216f, 0.218f, 0.223f, 0.225f, 0.226f, 0.226f, 0.225f, 0.225f,
  0.227f, 0.230f, 0.236f, 0.245f, 0.253f, 0.262f, 0.272f, 0.283f, 0.298f, 0.318f,
  0.341f, 0.367f, 0.390f, 0.409f, 0.424f, 0.435f, 0.442f, 0.448f, 0.450f, 0.451f,
  0.451f, 0.451f, 0.451f, 0.451f, 0.450f, 0.450f, 0.451f, 0.451f, 0.453f, 0.454f,
  0.455f, 0.457f, 0.458f, 0.460f, 0.462f, 0.463f, 0.464f, 0.465f, 0.466f, 0.466f,
  0.466f, 0.466f, 0.467f, 0.467f, 0.467f, 0.467f, 0.467f, 0.467f, 0.467f, 0.467f,
  0.467f};
const float metamer2Data[] = {
  0.070f, 0.079f, 0.089f, 0.101f, 0.111f, 0.116f, 0.118f, 0.120f, 0.121f, 0.122f,
  0.122f, 0.122f, 0.123f, 0.124f, 0.127f, 0.128f, 0.131f, 0.134f, 0.138f, 0.143f,
  0.150f, 0.159f, 0.174f, 0.190f, 0.207f, 0.225f, 0.242f, 0.253f, 0.260f, 0.264f,
  0.267f, 0.269f, 0.272f, 0.276f, 0.282f, 0.289f, 0.299f, 0.309f, 0.322f, 0.329f,
  0.335f, 0.339f, 0.341f, 0.341f, 0.342f, 0.342f, 0.342f, 0.341f, 0.341f, 0.339f,
  0.339f, 0.338f, 0.338f, 0.337f, 0.336f, 0.335f, 0.334f, 0.332f, 0.332f, 0.331f,
  0.331f, 0.330f, 0.329f, 0.328f, 0.328f, 0.327f, 0.326f, 0.325f, 0.324f, 0.324f,
  0.324f, 0.323f, 0.322f, 0.321f, 0.320f, 0.318f, 0.316f, 0.315f, 0.315f, 0.314f,
  0.314f};
const float metamer3Data[] = {
  0.065f, 0.068f, 0.070f, 0.072f, 0.073f, 0.073f, 0.074f, 0.074f, 0.074f, 0.073f,
  0.073f, 0.073f, 0.073f, 0.073f, 0.074f, 0.075f, 0.077f, 0.080f, 0.085f, 0.094f,
  0.109f, 0.126f, 0.148f, 0.172f, 0.198f, 0.221f, 0.241f, 0.260f, 0.278f, 0.302f,
  0.339f, 0.370f, 0.392f, 0.399f, 0.400f, 0.393f, 0.380f, 0.365f, 0.349f, 0.332f,
  0.315f, 0.299f, 0.285f, 0.272f, 0.264f, 0.257f, 0.252f, 0.247f, 0.241f, 0.235f,
  0.229f, 0.224f, 0.220f, 0.217f, 0.216f, 0.216f, 0.219f, 0.224f, 0.230f, 0.238f,
  0.251f, 0.269f, 0.288f, 0.312f, 0.340f, 0.366f, 0.390f, 0.412f, 0.431f, 0.447f,
  0.460f, 0.472f, 0.481f, 0.488f, 0.493f, 0.497f, 0.500f, 0.502f, 0.505f, 0.510f,
  0.516f};
const float metamer4Data[] = {
  0.074f, 0.083f, 0.093f, 0.105f, 0.116f, 0.121f, 0.124f, 0.126f, 0.128f, 0.131f,
  0.135f, 0.139f, 0.144f, 0.151f, 0.161f, 0.172f, 0.186f, 0.205f, 0.229f, 0.254f,
  0.281f, 0.308f, 0.332f, 0.352f, 0.370f, 0.383f, 0.390f, 0.394f, 0.395f, 0.392f,
  0.385f, 0.377f, 0.367f, 0.354f, 0.341f, 0.327f, 0.312f, 0.296f, 0.280f, 0.263f,
  0.247f, 0.229f, 0.214f, 0.198f, 0.185f, 0.175f, 0.169f, 0.164f, 0.160f, 0.156f,
  0.154f, 0.152f, 0.151f, 0.149f, 0.148f, 0.148f, 0.148f, 0.149f, 0.151f, 0.154f,
  0.158f, 0.162f, 0.165f, 0.168f, 0.170f, 0.171f, 0.170f, 0.168f, 0.166f, 0.164f,
  0.164f, 0.165f, 0.168f, 0.172f, 0.177f, 0.181f, 0.185f, 0.189f, 0.192f, 0.194f,
  0.197f};
const float metamer5Data[] = {
  0.295f, 0.306f, 0.310f, 0.312f, 0.313f, 0.315f, 0.319f, 0.322f, 0.326f, 0.330f,
  0.334f, 0.339f, 0.346f, 0.352f, 0.360f, 0.369f, 0.381f, 0.394f, 0.403f, 0.410f,
  0.415f, 0.418f, 0.419f, 0.417f, 0.413f, 0.409f, 0.403f, 0.396f, 0.389f, 0.381f,
  0.372f, 0.363f, 0.353f, 0.342f, 0.331f, 0.320f, 0.308f, 0.296f, 0.284f, 0.271f,
  0.260f, 0.247f, 0.232f, 0.220f, 0.210f, 0.200f, 0.194f, 0.189f, 0.185f, 0.183f,
  0.180f, 0.177f, 0.176f, 0.175f, 0.175f, 0.175f, 0.175f, 0.177f, 0.180f, 0.183f,
  0.186f, 0.189f, 0.192f, 0.195f, 0.199f, 0.200f, 0.199f, 0.198f, 0.196f, 0.195f,
  0.195f, 0.196f, 0.197f, 0.200f, 0.203f, 0.205f, 0.208f, 0.212f, 0.215f, 0.217f,
  0.219f};
const float metamer6Data[] = {
  0.151f, 0.203f, 0.265f, 0.339f, 0.410f, 0.464f, 0.492f, 0.508f, 0.517f, 0.524f,
  0.531f, 0.538f, 0.544f, 0.551f, 0.556f, 0.556f, 0.554f, 0.549f, 0.541f, 0.531f,
  0.519f, 0.504f, 0.488f, 0.469f, 0.450f, 0.431f, 0.414f, 0.395f, 0.377f, 0.358f,
  0.341f, 0.325f, 0.309f, 0.293f, 0.279f, 0.265f, 0.253f, 0.241f, 0.234f, 0.227f,
  0.225f, 0.222f, 0.221f, 0.220f, 0.220f, 0.220f, 0.220f, 0.220f, 0.223f, 0.227f,
  0.233f, 0.239f, 0.244f, 0.251f, 0.258f, 0.263f, 0.268f, 0.273f, 0.278f, 0.281f,
  0.283f, 0.286f, 0.291f, 0.296f, 0.302f, 0.313f, 0.325f, 0.338f, 0.351f, 0.364f,
  0.376f, 0.389f, 0.401f, 0.413f, 0.425f, 0.436f, 0.447f, 0.458f, 0.469f, 0.477f,
  0.485f};
const float metamer7Data[] = {
  0.378f, 0.459f, 0.524f, 0.546f, 0.551f, 0.555f, 0.559f, 0.560f, 0.561f, 0.558f,
  0.556f, 0.551f, 0.544f, 0.535f, 0.522f, 0.506f, 0.488f, 0.469f, 0.448f, 0.429f,
  0.408f, 0.385f, 0.363f, 0.341f, 0.324f, 0.311f, 0.301f, 0.291f, 0.283f, 0.273f,
  0.265f, 0.260f, 0.257f, 0.257f, 0.259f, 0.260f, 0.260f, 0.258f, 0.256f, 0.254f,
  0.254f, 0.259f, 0.270f, 0.284f, 0.302f, 0.324f, 0.344f, 0.362f, 0.377f, 0.389f,
  0.400f, 0.410f, 0.420f, 0.429f, 0.438f, 0.445f, 0.452f, 0.457f, 0.462f, 0.466f,
  0.468f, 0.470f, 0.473f, 0.477f, 0.483f, 0.489f, 0.496f, 0.503f, 0.511f, 0.518f,
  0.525f, 0.532f, 0.539f, 0.546f, 0.553f, 0.559f, 0.565f, 0.570f, 0.575f, 0.578f,
  0.581f};
const float metamer8Data[] = {
  0.104f, 0.129f, 0.170f, 0.240f, 0.319f, 0.416f, 0.462f, 0.482f, 0.490f, 0.488f,
  0.482f, 0.473f, 0.462f, 0.450f, 0.439f, 0.426f, 0.413f, 0.397f, 0.382f, 0.366f,
  0.352f, 0.337f, 0.325f, 0.310f, 0.299f, 0.289f, 0.283f, 0.276f, 0.270f, 0.262f,
  0.256f, 0.251f, 0.250f, 0.251f, 0.254f, 0.258f, 0.264f, 0.269f, 0.272f, 0.274f,
  0.278f, 0.284f, 0.295f, 0.316f, 0.348f, 0.384f, 0.434f, 0.482f, 0.528f, 0.568f,
  0.604f, 0.629f, 0.648f, 0.663f, 0.676f, 0.685f, 0.693f, 0.700f, 0.705f, 0.709f,
  0.712f, 0.715f, 0.717f, 0.719f, 0.721f, 0.720f, 0.719f, 0.722f, 0.725f, 0.727f,
  0.729f, 0.730f, 0.730f, 0.730f, 0.730f, 0.730f, 0.730f, 0.730f, 0.730f, 0.730f,
  0.730f};
const float metamer9Data[] = {
  0.066f, 0.062f, 0.058f, 0.055f, 0.052f, 0.052f, 0.051f, 0.050f, 0.050f, 0.049f,
  0.048f, 0.047f, 0.046f, 0.044f, 0.042f, 0.041f, 0.038f, 0.035f, 0.033f, 0.031f,
  0.030f, 0.029f, 0.028f, 0.028f, 0.028f, 0.029f, 0.030f, 0.030f, 0.031f, 0.031f,
  0.032f, 0.032f, 0.033f, 0.034f, 0.035f, 0.037f, 0.041f, 0.044f, 0.048f, 0.052f,
  0.060f, 0.076f, 0.102f, 0.136f, 0.190f, 0.256f, 0.336f, 0.418f, 0.505f, 0.581f,
  0.641f, 0.682f, 0.717f, 0.740f, 0.758f, 0.770f, 0.781f, 0.790f, 0.797f, 0.803f,
  0.809f, 0.814f, 0.819f, 0.824f, 0.828f, 0.830f, 0.831f, 0.833f, 0.835f, 0.836f,
  0.836f, 0.837f, 0.838f, 0.839f, 0.839f, 0.839f, 0.839f, 0.839f, 0.839f, 0.839f,
  0.839f};
const float metamer10Data[] = {
  0.050f, 0.054f, 0.059f, 0.063f, 0.066f, 0.067f, 0.068f, 0.069f, 0.069f, 0.070f,
  0.072f, 0.073f, 0.076f, 0.078f, 0.083f, 0.088f, 0.095f, 0.103f, 0.113f, 0.125f,
  0.142f, 0.162f, 0.189f, 0.219f, 0.262f, 0.305f, 0.365f, 0.416f, 0.465f, 0.509f,
  0.546f, 0.581f, 0.610f, 0.634f, 0.653f, 0.666f, 0.678f, 0.687f, 0.693f, 0.698f,
  0.701f, 0.704f, 0.705f, 0.705f, 0.706f, 0.707f, 0.707f, 0.707f, 0.708f, 0.708f,
  0.710f, 0.711f, 0.712f, 0.714f, 0.716f, 0.718f, 0.720f, 0.722f, 0.725f, 0.729f,
  0.731f, 0.735f, 0.739f, 0.742f, 0.746f, 0.748f, 0.749f, 0.751f, 0.753f, 0.754f,
  0.755f, 0.755f, 0.755f, 0.755f, 0.756f, 0.757f, 0.758f, 0.759f, 0.759f, 0.759f,
  0.759f};
const float metamer11Data[] = {
  0.111f, 0.121f, 0.127f, 0.129f, 0.127f, 0.121f, 0.116f, 0.112f, 0.108f, 0.105f,
  0.104f, 0.104f, 0.105f, 0.106f, 0.110f, 0.115f, 0.123f, 0.134f, 0.148f, 0.167f,
  0.192f, 0.219f, 0.252f, 0.291f, 0.325f, 0.347f, 0.356f, 0.353f, 0.346f, 0.333f,
  0.314f, 0.294f, 0.271f, 0.248f, 0.227f, 0.206f, 0.188f, 0.170f, 0.153f, 0.138f,
  0.125f, 0.114f, 0.106f, 0.100f, 0.096f, 0.092f, 0.090f, 0.087f, 0.085f, 0.082f,
  0.080f, 0.079f, 0.078f, 0.078f, 0.078f, 0.078f, 0.081f, 0.083f, 0.088f, 0.093f,
  0.102f, 0.112f, 0.125f, 0.141f, 0.161f, 0.182f, 0.203f, 0.223f, 0.242f, 0.257f,
  0.270f, 0.282f, 0.292f, 0.302f, 0.310f, 0.314f, 0.317f, 0.323f, 0.330f, 0.334f,
  0.338f};
const float metamer12Data[] = {
  0.120f, 0.103f, 0.090f, 0.082f, 0.076f, 0.068f, 0.064f, 0.065f, 0.075f, 0.093f,
  0.123f, 0.160f, 0.207f, 0.256f, 0.300f, 0.331f, 0.346f, 0.347f, 0.341f, 0.328f,
  0.307f, 0.282f, 0.257f, 0.230f, 0.204f, 0.178f, 0.154f, 0.129f, 0.109f, 0.090f,
  0.075f, 0.062f, 0.051f, 0.041f, 0.035f, 0.029f, 0.025f, 0.022f, 0.019f, 0.017f,
  0.017f, 0.017f, 0.016f, 0.016f, 0.016f, 0.016f, 0.016f, 0.016f, 0.016f, 0.016f,
  0.018f, 0.018f, 0.018f, 0.018f, 0.019f, 0.020f, 0.023f, 0.024f, 0.026f, 0.030f,
  0.035f, 0.043f, 0.056f, 0.074f, 0.097f, 0.128f, 0.166f, 0.210f, 0.257f, 0.305f,
  0.354f, 0.401f, 0.446f, 0.485f, 0.520f, 0.551f, 0.577f, 0.599f, 0.618f, 0.633f,
  0.645f};
const float metamer13Data[] = {
  0.104f, 0.127f, 0.161f, 0.211f, 0.264f, 0.313f, 0.341f, 0.352f, 0.359f, 0.361f,
  0.364f, 0.365f, 0.367f, 0.369f, 0.372f, 0.374f, 0.376f, 0.379f, 0.384f, 0.389f,
  0.397f, 0.405f, 0.416f, 0.429f, 0.443f, 0.454f, 0.461f, 0.466f, 0.469f, 0.471f,
  0.474f, 0.476f, 0.483f, 0.490f, 0.506f, 0.526f, 0.553f, 0.582f, 0.618f, 0.651f,
  0.680f, 0.701f, 0.717f, 0.729f, 0.736f, 0.742f, 0.745f, 0.747f, 0.748f, 0.748f,
  0.748f, 0.748f, 0.748f, 0.748f, 0.748f, 0.748f, 0.747f, 0.747f, 0.747f, 0.747f,
  0.747f, 0.747f, 0.747f, 0.746f, 0.746f, 0.746f, 0.745f, 0.744f, 0.743f, 0.744f,
  0.745f, 0.748f, 0.750f, 0.750f, 0.749f, 0.748f, 0.748f, 0.747f, 0.747f, 0.747f,
  0.747f};
const float metamer14Data[] = {
  0.036f, 0.036f, 0.037f, 0.038f, 0.039f, 0.039f, 0.040f, 0.041f, 0.042f, 0.042f,
  0.043f, 0.044f, 0.044f, 0.045f, 0.045f, 0.046f, 0.047f, 0.048f, 0.050f, 0.052f,
  0.055f, 0.057f, 0.062f, 0.067f, 0.075f, 0.083f, 0.092f, 0.100f, 0.108f, 0.121f,
  0.133f, 0.142f, 0.150f, 0.154f, 0.155f, 0.152f, 0.147f, 0.140f, 0.133f, 0.125f,
  0.118f, 0.112f, 0.106f, 0.101f, 0.098f, 0.095f, 0.093f, 0.090f, 0.089f, 0.087f,
  0.086f, 0.085f, 0.084f, 0.084f, 0.084f, 0.084f, 0.085f, 0.087f, 0.092f, 0.096f,
  0.102f, 0.110f, 0.123f, 0.137f, 0.152f, 0.169f, 0.188f, 0.207f, 0.226f, 0.243f,
  0.260f, 0.277f, 0.294f, 0.310f, 0.325f, 0.339f, 0.353f, 0.366f, 0.379f, 0.390f,
  0.399f};



CMColorRenderingColors cmComputeColorRenderingColors(CMLFunction* observer2Funcs[3], const CMWhitePoints* refWhitePoint2, const CMWhitePoints* illWhitePoint2, const CMLFunction* refSpec){

  CMColorRenderingColors colorRenderingColors;
  
  CMLColorMachine* cm = cmGetCurrentColorMachine();
  CMLColorMachine* sm = cmGetCurrentScreenMachine();
  const CMLFunction* illuminationSpec = cmlGetReferenceIlluminationSpectrum(cm);

  CMLIntegration integration = cmlMakeDefaultIntegration();

  const float* metamerdata[14] = {metamer1Data, metamer2Data, metamer3Data, metamer4Data, metamer5Data,
                                  metamer6Data, metamer7Data, metamer8Data, metamer9Data, metamer10Data,
                                  metamer11Data, metamer12Data, metamer13Data, metamer14Data};
  float metamerRefXYZ[14 * 3];
  float metamerIllXYZ[14 * 3];

  for(int i = 0; i < 14; ++i){
    CMLArrayFunctionInput input = {
      metamerdata[i],
      NA_FALSE,
      { METAMER_DATA_COUNT,
        METAMER_DATA_LAMBDA_MIN,
        METAMER_DATA_LAMBDA_MAX,
        CML_INTERPOLATION_LINEAR,
        CML_EXTRAPOLATION_LINEAR_ZERO,
        CML_EXTRAPOLATION_LINEAR_ZERO}};
    CMLFunction* metamerfunction = cmlCreateArrayFunction(input);

    float* metamerRefXYZptr = &(metamerRefXYZ[i * 3]);
    float* metamerIllXYZptr = &(metamerIllXYZ[i * 3]);

    CMLVec3 metamerrefUVW;
    if(refSpec){
      CMLFunction* metamerrefremission = cmlCreateFunctionMulFunction(metamerfunction, refSpec);
      cmlSet3(
        metamerRefXYZptr,
        cmlFilterFunction(metamerrefremission, observer2Funcs[0], &integration),
        cmlFilterFunction(metamerrefremission, observer2Funcs[1], &integration),
        cmlFilterFunction(metamerrefremission, observer2Funcs[2], &integration));
      cmlDiv3(metamerRefXYZptr, refWhitePoint2->XYZunnorm[1]);
      CMLVec3 metamerrefYxy;
      cmlConvertXYZToYxy(metamerrefYxy, metamerRefXYZptr, CML_NULL);
      CMLVec3 metamerrefYupvp;
      cmlConvertYxyToYupvp(metamerrefYupvp, metamerrefYxy, CML_NULL);
      CMLVec3 metamerrefYuv;
      // ISO 3664 states in forumal D.14 the computation 6X/(X+15Y+3Z). I'm
      // pretty sure, they meant  6Y/(X+15Y+3Z) which is according to
      // CIE 1960 UCS. This also corresponds to the fact that UVW is based on
      // UCS. In CML, this is Yuv.
      cmlConvertYupvpToYuv(metamerrefYuv, metamerrefYupvp);
      convertYuvtoUVW(metamerrefUVW, metamerrefYuv, refWhitePoint2->Yuv);
      cmlReleaseFunction(metamerrefremission);
    }else{
      cmlSet3(metamerRefXYZptr, 0.f, 0.f, 0.f);
      cmlSet3(metamerrefUVW, 0.f, 0.f, 0.f);
    }

    CMLVec3 metamerillUVW;
    if(illuminationSpec){
      CMLFunction* metamerillremission = cmlCreateFunctionMulFunction(metamerfunction, illuminationSpec);
      cmlSet3(
        metamerIllXYZptr,
        cmlFilterFunction(metamerillremission, observer2Funcs[0], &integration),
        cmlFilterFunction(metamerillremission, observer2Funcs[1], &integration),
        cmlFilterFunction(metamerillremission, observer2Funcs[2], &integration));
      cmlDiv3(metamerIllXYZptr, illWhitePoint2->XYZunnorm[1]);
      CMLVec3 metamerillYxy;
      cmlConvertXYZToYxy(metamerillYxy, metamerIllXYZptr, CML_NULL);
      CMLVec3 metamerillYupvp;
      cmlConvertYxyToYupvp(metamerillYupvp, metamerillYxy, CML_NULL);
      CMLVec3 metamerillYuv;
      cmlConvertYupvpToYuv(metamerillYuv, metamerillYupvp);
      CMLVec3 metamerillYcd;
      convertYuvtoYcd(metamerillYcd, metamerillYuv);
      CMLVec3 metamerillaYuv;
      convertYcdtoadaptedYuv(metamerillaYuv, metamerillYcd, illWhitePoint2->Ycd, refWhitePoint2->Ycd);
      convertYuvtoUVW(metamerillUVW, metamerillaYuv, refWhitePoint2->Yuv);
      cmlReleaseFunction(metamerillremission);
    }else{
      cmlSet3(metamerIllXYZptr, 0.f, 0.f, 0.f);
      cmlSet3(metamerillUVW, 0.f, 0.f, 0.f);
    }

    cmlSub3(metamerrefUVW, metamerillUVW);
    float deltaE = cmlLength3(metamerrefUVW);
    colorRenderingColors.colorRenderingIndex[i] = 100.f - 4.6f * deltaE;
    
    cmlReleaseFunction(metamerfunction);
  }

  fillRGBFloatArrayWithArray(
    cm,
    sm,
    colorRenderingColors.crReferenceRGBFloatData[0],
    metamerRefXYZ,
    CML_COLOR_XYZ,
    cmlGetNormedInputConverter(CML_COLOR_XYZ),
    14,
    NA_FALSE,
    NA_FALSE);
  
  fillRGBFloatArrayWithArray(
    cm,
    sm,
    colorRenderingColors.crMetamerRGBFloatData[0],
    metamerIllXYZ,
    CML_COLOR_XYZ,
    cmlGetNormedInputConverter(CML_COLOR_XYZ),
    14,
    NA_FALSE,
    NA_FALSE);
  
  return colorRenderingColors;
}
