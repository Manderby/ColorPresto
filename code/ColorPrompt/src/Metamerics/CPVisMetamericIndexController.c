
#include "CPVisMetamericIndexController.h"

#include "../CPColorPromptApplication.h"
#include "../CPDesign.h"
#include "../CPTranslations.h"
#include "CPTwoColorController.h"
#include "CPWhitePoints.h"

#include "NAApp.h"



// ISO-23603
#define VIS_METAMER_STANDARD_DATA_COUNT 81
#define VIS_METAMER_STANDARD_DATA_LAMBDA_MIN 380.f
#define VIS_METAMER_STANDARD_DATA_LAMBDA_MAX 780.f
const float standard1Data[] = {
  0.056f, 0.054f, 0.052f, 0.050f, 0.048f, 0.045f, 0.043f, 0.041f, 0.040f, 0.038f,
  0.037f, 0.036f, 0.035f, 0.034f, 0.034f, 0.035f, 0.036f, 0.037f, 0.039f, 0.041f,
  0.045f, 0.051f, 0.058f, 0.067f, 0.077f, 0.089f, 0.102f, 0.115f, 0.127f, 0.139f,
  0.151f, 0.162f, 0.174f, 0.185f, 0.198f, 0.213f, 0.230f, 0.251f, 0.276f, 0.305f,
  0.336f, 0.369f, 0.401f, 0.431f, 0.459f, 0.482f, 0.501f, 0.516f, 0.528f, 0.537f,
  0.544f, 0.551f, 0.557f, 0.562f, 0.567f, 0.573f, 0.579f, 0.585f, 0.592f, 0.598f,
  0.605f, 0.613f, 0.621f, 0.629f, 0.637f, 0.645f, 0.653f, 0.661f, 0.669f, 0.677f,
  0.685f, 0.693f, 0.701f, 0.709f, 0.717f, 0.725f, 0.733f, 0.741f, 0.749f, 0.757f,
  0.765f};
const float standard2Data[] = {
  0.054f, 0.062f, 0.069f, 0.075f, 0.080f, 0.084f, 0.087f, 0.089f, 0.089f, 0.088f,
  0.085f, 0.082f, 0.078f, 0.074f, 0.070f, 0.066f, 0.063f, 0.060f, 0.057f, 0.054f,
  0.052f, 0.050f, 0.048f, 0.046f, 0.044f, 0.042f, 0.041f, 0.039f, 0.038f, 0.037f,
  0.036f, 0.035f, 0.034f, 0.033f, 0.032f, 0.031f, 0.031f, 0.031f, 0.031f, 0.032f,
  0.033f, 0.035f, 0.037f, 0.041f, 0.046f, 0.053f, 0.061f, 0.071f, 0.082f, 0.095f,
  0.109f, 0.121f, 0.133f, 0.145f, 0.156f, 0.166f, 0.177f, 0.188f, 0.201f, 0.217f,
  0.236f, 0.257f, 0.279f, 0.302f, 0.326f, 0.350f, 0.374f, 0.398f, 0.422f, 0.446f,
  0.470f, 0.494f, 0.518f, 0.542f, 0.566f, 0.590f, 0.614f, 0.638f, 0.662f, 0.686f,
  0.710f};
const float standard3Data[] = {
  0.052f, 0.050f, 0.048f, 0.046f, 0.044f, 0.042f, 0.040f, 0.038f, 0.037f, 0.036f,
  0.035f, 0.034f, 0.033f, 0.032f, 0.032f, 0.032f, 0.032f, 0.033f, 0.034f, 0.036f,
  0.038f, 0.041f, 0.045f, 0.049f, 0.055f, 0.062f, 0.070f, 0.078f, 0.086f, 0.092f,
  0.097f, 0.101f, 0.104f, 0.106f, 0.107f, 0.107f, 0.106f, 0.104f, 0.101f, 0.099f,
  0.096f, 0.093f, 0.090f, 0.089f, 0.089f, 0.089f, 0.090f, 0.091f, 0.092f, 0.092f,
  0.092f, 0.093f, 0.096f, 0.101f, 0.109f, 0.120f, 0.134f, 0.154f, 0.177f, 0.202f,
  0.228f, 0.252f, 0.275f, 0.296f, 0.316f, 0.336f, 0.355f, 0.373f, 0.390f, 0.406f,
  0.421f, 0.435f, 0.448f, 0.460f, 0.471f, 0.481f, 0.490f, 0.498f, 0.505f, 0.511f,
  0.516f};
const float standard4Data[] = {
  0.318f, 0.314f, 0.301f, 0.299f, 0.298f, 0.298f, 0.300f, 0.305f, 0.311f, 0.318f,
  0.326f, 0.335f, 0.346f, 0.357f, 0.369f, 0.381f, 0.391f, 0.398f, 0.401f, 0.400f,
  0.396f, 0.387f, 0.376f, 0.363f, 0.348f, 0.331f, 0.313f, 0.297f, 0.283f, 0.272f,
  0.262f, 0.251f, 0.241f, 0.230f, 0.220f, 0.213f, 0.208f, 0.207f, 0.208f, 0.208f,
  0.208f, 0.206f, 0.204f, 0.202f, 0.203f, 0.209f, 0.220f, 0.236f, 0.256f, 0.277f,
  0.298f, 0.317f, 0.337f, 0.361f, 0.391f, 0.430f, 0.476f, 0.531f, 0.589f, 0.647f,
  0.702f, 0.749f, 0.787f, 0.816f, 0.835f, 0.847f, 0.855f, 0.861f, 0.865f, 0.867f,
  0.868f, 0.868f, 0.868f, 0.868f, 0.868f, 0.868f, 0.868f, 0.868f, 0.868f, 0.868f,
  0.868f};
const float standard5Data[] = {
  0.120f, 0.115f, 0.111f, 0.108f, 0.106f, 0.106f, 0.109f, 0.114f, 0.120f, 0.127f,
  0.136f, 0.146f, 0.156f, 0.166f, 0.176f, 0.184f, 0.191f, 0.195f, 0.197f, 0.195f,
  0.191f, 0.183f, 0.174f, 0.165f, 0.155f, 0.146f, 0.137f, 0.129f, 0.122f, 0.115f,
  0.110f, 0.107f, 0.105f, 0.105f, 0.105f, 0.105f, 0.105f, 0.105f, 0.107f, 0.111f,
  0.120f, 0.135f, 0.156f, 0.183f, 0.214f, 0.250f, 0.285f, 0.313f, 0.333f, 0.340f,
  0.342f, 0.341f, 0.345f, 0.362f, 0.391f, 0.434f, 0.487f, 0.547f, 0.609f, 0.667f,
  0.721f, 0.766f, 0.803f, 0.830f, 0.849f, 0.859f, 0.866f, 0.871f, 0.875f, 0.878f,
  0.880f, 0.881f, 0.881f, 0.881f, 0.881f, 0.881f, 0.881f, 0.881f, 0.881f, 0.881f,
  0.881f};
  
#define VIS_METAMER_SPECIMEN_DATA_COUNT 81
#define VIS_METAMER_SPECIMEN_DATA_LAMBDA_MIN 380.f
#define VIS_METAMER_SPECIMEN_DATA_LAMBDA_MAX 780.f  
const float specimen1D50Data[] = {
  0.050f, 0.049f, 0.045f, 0.042f, 0.035f, 0.029f, 0.027f, 0.026f, 0.024f, 0.024f,
  0.024f, 0.025f, 0.025f, 0.026f, 0.027f, 0.028f, 0.031f, 0.035f, 0.043f, 0.054f,
  0.068f, 0.085f, 0.103f, 0.121f, 0.136f, 0.148f, 0.156f, 0.160f, 0.160f, 0.162f,
  0.164f, 0.167f, 0.172f, 0.177f, 0.182f, 0.189f, 0.196f, 0.209f, 0.226f, 0.248f,
  0.275f, 0.309f, 0.345f, 0.384f, 0.427f, 0.473f, 0.515f, 0.552f, 0.582f, 0.608f,
  0.630f, 0.646f, 0.659f, 0.671f, 0.683f, 0.695f, 0.708f, 0.723f, 0.736f, 0.750f,
  0.755f, 0.762f, 0.770f, 0.778f, 0.782f, 0.785f, 0.787f, 0.788f, 0.789f, 0.790f,
  0.791f, 0.791f, 0.791f, 0.792f, 0.792f, 0.792f, 0.792f, 0.792f, 0.792f, 0.792f,
  0.792f};
const float specimen2D50Data[] = {
  0.069f, 0.068f, 0.066f, 0.064f, 0.059f, 0.059f, 0.063f, 0.074f, 0.081f, 0.088f,
  0.089f, 0.088f, 0.083f, 0.081f, 0.076f, 0.071f, 0.066f, 0.059f, 0.052f, 0.048f,
  0.045f, 0.042f, 0.038f, 0.037f, 0.034f, 0.035f, 0.033f, 0.032f, 0.032f, 0.032f,
  0.032f, 0.032f, 0.033f, 0.033f, 0.033f, 0.032f, 0.030f, 0.032f, 0.036f, 0.041f,
  0.045f, 0.049f, 0.055f, 0.063f, 0.072f, 0.077f, 0.083f, 0.085f, 0.086f, 0.087f,
  0.087f, 0.087f, 0.087f, 0.088f, 0.088f, 0.088f, 0.088f, 0.088f, 0.088f, 0.088f,
  0.088f, 0.088f, 0.088f, 0.088f, 0.088f, 0.089f, 0.089f, 0.089f, 0.089f, 0.089f,
  0.089f, 0.089f, 0.089f, 0.089f, 0.089f, 0.089f, 0.089f, 0.089f, 0.089f, 0.089f,
  0.089f};
const float specimen3D50Data[] = {
  0.033f, 0.032f, 0.032f, 0.030f, 0.028f, 0.028f, 0.027f, 0.027f, 0.027f, 0.026f,
  0.026f, 0.024f, 0.025f, 0.026f, 0.027f, 0.029f, 0.031f, 0.034f, 0.037f, 0.045f,
  0.056f, 0.067f, 0.077f, 0.086f, 0.092f, 0.095f, 0.097f, 0.095f, 0.092f, 0.090f,
  0.089f, 0.088f, 0.086f, 0.084f, 0.084f, 0.085f, 0.087f, 0.088f, 0.091f, 0.094f,
  0.096f, 0.097f, 0.097f, 0.100f, 0.102f, 0.103f, 0.104f, 0.104f, 0.104f, 0.103f,
  0.103f, 0.104f, 0.104f, 0.106f, 0.108f, 0.113f, 0.119f, 0.128f, 0.141f, 0.158f,
  0.174f, 0.195f, 0.213f, 0.234f, 0.257f, 0.281f, 0.308f, 0.332f, 0.354f, 0.374f,
  0.389f, 0.400f, 0.410f, 0.417f, 0.424f, 0.429f, 0.431f, 0.432f, 0.432f, 0.432f,
  0.432f};
const float specimen4D50Data[] = {
  0.401f, 0.401f, 0.401f, 0.401f, 0.401f, 0.401f, 0.401f, 0.401f, 0.401f, 0.400f,
  0.398f, 0.393f, 0.387f, 0.375f, 0.372f, 0.366f, 0.360f, 0.353f, 0.345f, 0.336f,
  0.327f, 0.319f, 0.311f, 0.304f, 0.296f, 0.289f, 0.281f, 0.276f, 0.271f, 0.265f,
  0.260f, 0.255f, 0.250f, 0.248f, 0.246f, 0.245f, 0.244f, 0.243f, 0.241f, 0.239f,
  0.236f, 0.234f, 0.234f, 0.235f, 0.238f, 0.240f, 0.241f, 0.240f, 0.237f, 0.234f,
  0.229f, 0.228f, 0.228f, 0.236f, 0.245f, 0.264f, 0.287f, 0.320f, 0.358f, 0.403f,
  0.455f, 0.505f, 0.560f, 0.610f, 0.660f, 0.710f, 0.755f, 0.795f, 0.825f, 0.850f,
  0.870f, 0.885f, 0.895f, 0.900f, 0.900f, 0.900f, 0.900f, 0.900f, 0.900f, 0.900f,
  0.900f};
const float specimen5D50Data[] = {
  0.173f, 0.174f, 0.175f, 0.176f, 0.177f, 0.178f, 0.179f, 0.180f, 0.184f, 0.187f,
  0.187f, 0.186f, 0.181f, 0.178f, 0.174f, 0.170f, 0.165f, 0.160f, 0.156f, 0.151f,
  0.148f, 0.144f, 0.141f, 0.139f, 0.137f, 0.135f, 0.135f, 0.132f, 0.129f, 0.125f,
  0.122f, 0.121f, 0.121f, 0.121f, 0.121f, 0.119f, 0.116f, 0.110f, 0.109f, 0.113f,
  0.119f, 0.131f, 0.149f, 0.174f, 0.200f, 0.228f, 0.258f, 0.286f, 0.316f, 0.342f,
  0.366f, 0.387f, 0.405f, 0.424f, 0.440f, 0.454f, 0.469f, 0.485f, 0.506f, 0.526f,
  0.548f, 0.567f, 0.591f, 0.616f, 0.641f, 0.659f, 0.676f, 0.692f, 0.705f, 0.715f,
  0.725f, 0.734f, 0.744f, 0.754f, 0.764f, 0.774f, 0.784f, 0.794f, 0.804f, 0.814f,
  0.824f};

const float specimen1D55Data[] = {
  0.037f, 0.035f, 0.033f, 0.030f, 0.029f, 0.028f, 0.027f, 0.026f, 0.026f, 0.025f,
  0.025f, 0.025f, 0.025f, 0.026f, 0.028f, 0.029f, 0.032f, 0.036f, 0.044f, 0.054f,
  0.068f, 0.085f, 0.103f, 0.121f, 0.136f, 0.147f, 0.155f, 0.158f, 0.159f, 0.161f,
  0.163f, 0.166f, 0.170f, 0.175f, 0.180f, 0.187f, 0.195f, 0.208f, 0.225f, 0.247f,
  0.275f, 0.309f, 0.346f, 0.386f, 0.430f, 0.476f, 0.518f, 0.555f, 0.586f, 0.611f,
  0.633f, 0.649f, 0.662f, 0.674f, 0.686f, 0.698f, 0.711f, 0.725f, 0.739f, 0.753f,
  0.770f, 0.785f, 0.800f, 0.812f, 0.823f, 0.834f, 0.843f, 0.851f, 0.859f, 0.865f,
  0.870f, 0.875f, 0.879f, 0.880f, 0.880f, 0.880f, 0.880f, 0.880f, 0.880f, 0.880f,
  0.880f};
const float specimen2D55Data[] = {
  0.025f, 0.033f, 0.041f, 0.046f, 0.054f, 0.060f, 0.067f, 0.074f, 0.081f, 0.088f,
  0.088f, 0.088f, 0.083f, 0.081f, 0.076f, 0.071f, 0.066f, 0.059f, 0.052f, 0.048f,
  0.045f, 0.042f, 0.039f, 0.037f, 0.034f, 0.035f, 0.033f, 0.033f, 0.033f, 0.033f,
  0.033f, 0.033f, 0.033f, 0.033f, 0.033f, 0.032f, 0.030f, 0.032f, 0.036f, 0.040f,
  0.045f, 0.050f, 0.055f, 0.063f, 0.071f, 0.075f, 0.082f, 0.084f, 0.086f, 0.086f,
  0.086f, 0.086f, 0.086f, 0.086f, 0.087f, 0.087f, 0.087f, 0.087f, 0.087f, 0.088f,
  0.088f, 0.088f, 0.089f, 0.089f, 0.089f, 0.090f, 0.090f, 0.090f, 0.090f, 0.090f,
  0.090f, 0.090f, 0.090f, 0.090f, 0.090f, 0.090f, 0.090f, 0.090f, 0.090f, 0.090f,
  0.090f};
const float specimen3D55Data[] = {
  0.040f, 0.036f, 0.035f, 0.031f, 0.030f, 0.028f, 0.028f, 0.027f, 0.027f, 0.026f,
  0.026f, 0.025f, 0.026f, 0.027f, 0.027f, 0.029f, 0.031f, 0.034f, 0.038f, 0.046f,
  0.056f, 0.067f, 0.077f, 0.086f, 0.092f, 0.095f, 0.096f, 0.094f, 0.091f, 0.089f,
  0.088f, 0.087f, 0.086f, 0.084f, 0.084f, 0.085f, 0.086f, 0.088f, 0.091f, 0.094f,
  0.096f, 0.097f, 0.098f, 0.101f, 0.103f, 0.104f, 0.104f, 0.104f, 0.104f, 0.103f,
  0.103f, 0.104f, 0.105f, 0.107f, 0.110f, 0.115f, 0.121f, 0.130f, 0.141f, 0.155f,
  0.171f, 0.190f, 0.210f, 0.231f, 0.257f, 0.283f, 0.314f, 0.344f, 0.374f, 0.404f,
  0.434f, 0.464f, 0.524f, 0.554f, 0.581f, 0.612f, 0.641f, 0.670f, 0.699f, 0.728f,
  0.757f};
const float specimen4D55Data[] = {
  0.408f, 0.407f, 0.406f, 0.400f, 0.399f, 0.399f, 0.399f, 0.398f, 0.398f, 0.398f,
  0.395f, 0.390f, 0.382f, 0.376f, 0.370f, 0.364f, 0.358f, 0.351f, 0.343f, 0.335f,
  0.327f, 0.319f, 0.312f, 0.304f, 0.297f, 0.290f, 0.283f, 0.278f, 0.273f, 0.267f,
  0.262f, 0.257f, 0.253f, 0.250f, 0.248f, 0.246f, 0.245f, 0.244f, 0.242f, 0.239f,
  0.235f, 0.233f, 0.232f, 0.233f, 0.235f, 0.237f, 0.239f, 0.237f, 0.234f, 0.230f,
  0.225f, 0.223f, 0.225f, 0.231f, 0.243f, 0.260f, 0.285f, 0.317f, 0.353f, 0.402f,
  0.450f, 0.504f, 0.556f, 0.605f, 0.652f, 0.697f, 0.734f, 0.771f, 0.803f, 0.832f,
  0.855f, 0.873f, 0.887f, 0.894f, 0.896f, 0.896f, 0.896f, 0.896f, 0.896f, 0.896f,
  0.896f};
const float specimen5D55Data[] = {
  0.145f, 0.153f, 0.160f, 0.164f, 0.169f, 0.173f, 0.177f, 0.181f, 0.183f, 0.185f,
  0.185f, 0.184f, 0.180f, 0.177f, 0.173f, 0.169f, 0.164f, 0.159f, 0.155f, 0.150f,
  0.147f, 0.143f, 0.141f, 0.139f, 0.137f, 0.135f, 0.135f, 0.133f, 0.130f, 0.126f,
  0.123f, 0.122f, 0.122f, 0.122f, 0.122f, 0.119f, 0.116f, 0.111f, 0.109f, 0.113f,
  0.119f, 0.131f, 0.149f, 0.173f, 0.199f, 0.227f, 0.258f, 0.286f, 0.315f, 0.341f,
  0.365f, 0.386f, 0.405f, 0.422f, 0.437f, 0.452f, 0.468f, 0.484f, 0.504f, 0.524f,
  0.547f, 0.570f, 0.593f, 0.616f, 0.635f, 0.661f, 0.681f, 0.698f, 0.711f, 0.724f,
  0.736f, 0.747f, 0.757f, 0.766f, 0.774f, 0.781f, 0.785f, 0.780f, 0.794f, 0.797f,
  0.799f};

const float specimen1D65Data[] = {
  0.036f, 0.035f, 0.034f, 0.034f, 0.033f, 0.030f, 0.028f, 0.026f, 0.026f, 0.026f,
  0.026f, 0.026f, 0.026f, 0.027f, 0.029f, 0.030f, 0.033f, 0.037f, 0.044f, 0.054f,
  0.068f, 0.085f, 0.104f, 0.121f, 0.136f, 0.146f, 0.153f, 0.156f, 0.157f, 0.159f,
  0.161f, 0.164f, 0.167f, 0.172f, 0.177f, 0.184f, 0.193f, 0.206f, 0.223f, 0.246f,
  0.275f, 0.309f, 0.347f, 0.389f, 0.434f, 0.480f, 0.523f, 0.560f, 0.593f, 0.619f,
  0.641f, 0.657f, 0.669f, 0.681f, 0.691f, 0.703f, 0.712f, 0.727f, 0.742f, 0.756f,
  0.769f, 0.781f, 0.792f, 0.802f, 0.811f, 0.818f, 0.825f, 0.831f, 0.836f, 0.840f,
  0.844f, 0.846f, 0.847f, 0.847f, 0.847f, 0.847f, 0.847f, 0.847f, 0.847f, 0.847f,
  0.847f};
const float specimen2D65Data[] = {
  0.051f, 0.052f, 0.054f, 0.056f, 0.055f, 0.057f, 0.063f, 0.073f, 0.080f, 0.088f,
  0.089f, 0.088f, 0.083f, 0.081f, 0.076f, 0.071f, 0.066f, 0.059f, 0.052f, 0.048f,
  0.045f, 0.043f, 0.040f, 0.037f, 0.034f, 0.035f, 0.033f, 0.033f, 0.034f, 0.034f,
  0.034f, 0.034f, 0.034f, 0.033f, 0.033f, 0.031f, 0.031f, 0.033f, 0.036f, 0.041f,
  0.045f, 0.049f, 0.054f, 0.062f, 0.069f, 0.074f, 0.081f, 0.083f, 0.085f, 0.085f,
  0.085f, 0.085f, 0.085f, 0.085f, 0.085f, 0.084f, 0.084f, 0.085f, 0.084f, 0.084f,
  0.084f, 0.084f, 0.084f, 0.084f, 0.084f, 0.083f, 0.082f, 0.082f, 0.082f, 0.082f,
  0.081f, 0.081f, 0.081f, 0.081f, 0.081f, 0.081f, 0.081f, 0.081f, 0.081f, 0.081f,
  0.081f};
const float specimen3D65Data[] = {
  0.043f, 0.042f, 0.040f, 0.037f, 0.031f, 0.028f, 0.028f, 0.027f, 0.027f, 0.026f,
  0.026f, 0.026f, 0.027f, 0.028f, 0.028f, 0.029f, 0.031f, 0.034f, 0.039f, 0.047f,
  0.057f, 0.067f, 0.077f, 0.086f, 0.092f, 0.095f, 0.095f, 0.093f, 0.090f, 0.088f,
  0.087f, 0.086f, 0.085f, 0.083f, 0.083f, 0.083f, 0.084f, 0.088f, 0.091f, 0.094f,
  0.096f, 0.098f, 0.100f, 0.102f, 0.104f, 0.105f, 0.104f, 0.105f, 0.105f, 0.104f,
  0.104f, 0.105f, 0.106f, 0.108f, 0.111f, 0.116f, 0.124f, 0.135f, 0.147f, 0.162f,
  0.179f, 0.198f, 0.218f, 0.240f, 0.263f, 0.270f, 0.270f, 0.271f, 0.271f, 0.271f,
  0.272f, 0.272f, 0.273f, 0.273f, 0.273f, 0.273f, 0.273f, 0.273f, 0.273f, 0.273f,
  0.273f};
const float specimen4D65Data[] = {
  0.389f, 0.389f, 0.389f, 0.389f, 0.391f, 0.393f, 0.394f, 0.395f, 0.396f, 0.395f,
  0.392f, 0.387f, 0.379f, 0.373f, 0.367f, 0.361f, 0.355f, 0.348f, 0.340f, 0.333f,
  0.326f, 0.319f, 0.312f, 0.305f, 0.300f, 0.292f, 0.286f, 0.281f, 0.276f, 0.270f,
  0.265f, 0.260f, 0.257f, 0.253f, 0.251f, 0.249f, 0.248f, 0.246f, 0.243f, 0.238f,
  0.234f, 0.231f, 0.229f, 0.229f, 0.230f, 0.232f, 0.234f, 0.232f, 0.228f, 0.224f,
  0.220f, 0.218f, 0.221f, 0.227f, 0.238f, 0.254f, 0.278f, 0.309f, 0.347f, 0.391f,
  0.446f, 0.496f, 0.547f, 0.601f, 0.647f, 0.693f, 0.733f, 0.773f, 0.807f, 0.837f,
  0.880f, 0.888f, 0.893f, 0.893f, 0.894f, 0.894f, 0.894f, 0.894f, 0.894f, 0.894f,
  0.894f};
const float specimen5D65Data[] = {
  0.075f, 0.094f, 0.111f, 0.128f, 0.150f, 0.169f, 0.176f, 0.180f, 0.182f, 0.183f,
  0.183f, 0.182f, 0.179f, 0.175f, 0.171f, 0.167f, 0.162f, 0.157f, 0.153f, 0.149f,
  0.146f, 0.143f, 0.141f, 0.139f, 0.138f, 0.137f, 0.136f, 0.134f, 0.131f, 0.127f,
  0.124f, 0.123f, 0.123f, 0.122f, 0.122f, 0.120f, 0.117f, 0.113f, 0.111f, 0.113f,
  0.119f, 0.131f, 0.149f, 0.172f, 0.198f, 0.226f, 0.256f, 0.285f, 0.313f, 0.339f,
  0.363f, 0.384f, 0.402f, 0.419f, 0.435f, 0.451f, 0.464f, 0.485f, 0.504f, 0.524f,
  0.545f, 0.566f, 0.585f, 0.601f, 0.615f, 0.631f, 0.647f, 0.662f, 0.676f, 0.686f,
  0.701f, 0.710f, 0.720f, 0.729f, 0.738f, 0.744f, 0.747f, 0.751f, 0.754f, 0.756f,
  0.757f};

const float specimen1D75Data[] = {
  0.038f, 0.036f, 0.035f, 0.034f, 0.031f, 0.030f, 0.029f, 0.027f, 0.027f, 0.026f,
  0.026f, 0.026f, 0.026f, 0.027f, 0.029f, 0.031f, 0.034f, 0.038f, 0.045f, 0.055f,
  0.069f, 0.086f, 0.104f, 0.121f, 0.136f, 0.145f, 0.152f, 0.154f, 0.155f, 0.157f,
  0.159f, 0.162f, 0.166f, 0.170f, 0.175f, 0.182f, 0.191f, 0.204f, 0.221f, 0.245f,
  0.275f, 0.309f, 0.348f, 0.391f, 0.437f, 0.483f, 0.527f, 0.564f, 0.596f, 0.622f,
  0.645f, 0.661f, 0.674f, 0.686f, 0.698f, 0.711f, 0.723f, 0.736f, 0.749f, 0.764f,
  0.777f, 0.792f, 0.804f, 0.814f, 0.822f, 0.826f, 0.833f, 0.838f, 0.842f, 0.843f,
  0.844f, 0.845f, 0.846f, 0.847f, 0.848f, 0.849f, 0.850f, 0.851f, 0.852f, 0.853f,
  0.854f};
const float specimen2D75Data[] = {
  0.008f, 0.018f, 0.028f, 0.038f, 0.047f, 0.058f, 0.065f, 0.073f, 0.080f, 0.088f,
  0.089f, 0.088f, 0.083f, 0.081f, 0.076f, 0.071f, 0.066f, 0.059f, 0.052f, 0.048f,
  0.046f, 0.042f, 0.039f, 0.037f, 0.034f, 0.035f, 0.033f, 0.034f, 0.035f, 0.035f,
  0.035f, 0.035f, 0.034f, 0.033f, 0.033f, 0.032f, 0.031f, 0.032f, 0.036f, 0.041f,
  0.045f, 0.049f, 0.055f, 0.060f, 0.069f, 0.073f, 0.079f, 0.081f, 0.083f, 0.084f,
  0.084f, 0.084f, 0.084f, 0.084f, 0.085f, 0.085f, 0.086f, 0.087f, 0.087f, 0.088f,
  0.089f, 0.089f, 0.089f, 0.089f, 0.089f, 0.089f, 0.089f, 0.089f, 0.089f, 0.089f,
  0.089f, 0.089f, 0.089f, 0.089f, 0.089f, 0.089f, 0.089f, 0.089f, 0.089f, 0.089f,
  0.089f};
const float specimen3D75Data[] = {
  0.037f, 0.034f, 0.032f, 0.032f, 0.030f, 0.030f, 0.028f, 0.027f, 0.027f, 0.026f,
  0.026f, 0.027f, 0.027f, 0.028f, 0.028f, 0.029f, 0.032f, 0.035f, 0.040f, 0.048f,
  0.057f, 0.067f, 0.077f, 0.086f, 0.092f, 0.094f, 0.094f, 0.092f, 0.089f, 0.087f,
  0.086f, 0.085f, 0.084f, 0.083f, 0.083f, 0.083f, 0.084f, 0.087f, 0.090f, 0.093f,
  0.096f, 0.098f, 0.100f, 0.103f, 0.105f, 0.106f, 0.106f, 0.106f, 0.106f, 0.105f,
  0.105f, 0.106f, 0.107f, 0.109f, 0.112f, 0.117f, 0.124f, 0.133f, 0.144f, 0.158f,
  0.175f, 0.196f, 0.218f, 0.239f, 0.261f, 0.278f, 0.299f, 0.318f, 0.362f, 0.383f,
  0.406f, 0.427f, 0.448f, 0.468f, 0.488f, 0.508f, 0.528f, 0.548f, 0.568f, 0.588f,
  0.608f};
const float specimen4D75Data[] = {
  0.422f, 0.419f, 0.415f, 0.409f, 0.400f, 0.396f, 0.393f, 0.393f, 0.393f, 0.393f,
  0.390f, 0.385f, 0.378f, 0.371f, 0.365f, 0.359f, 0.353f, 0.346f, 0.338f, 0.331f,
  0.324f, 0.318f, 0.311f, 0.305f, 0.299f, 0.294f, 0.288f, 0.284f, 0.279f, 0.273f,
  0.268f, 0.263f, 0.259f, 0.256f, 0.254f, 0.252f, 0.250f, 0.247f, 0.244f, 0.238f,
  0.233f, 0.229f, 0.228f, 0.226f, 0.226f, 0.228f, 0.230f, 0.228f, 0.225f, 0.221f,
  0.217f, 0.215f, 0.217f, 0.222f, 0.232f, 0.249f, 0.272f, 0.303f, 0.339f, 0.380f,
  0.425f, 0.475f, 0.525f, 0.570f, 0.615f, 0.655f, 0.690f, 0.722f, 0.757f, 0.784f,
  0.804f, 0.825f, 0.850f, 0.860f, 0.865f, 0.875f, 0.885f, 0.887f, 0.891f, 0.894f,
  0.897f};
const float specimen5D75Data[] = {
  0.158f, 0.161f, 0.163f, 0.167f, 0.168f, 0.170f, 0.174f, 0.177f, 0.179f, 0.180f,
  0.181f, 0.180f, 0.178f, 0.174f, 0.170f, 0.166f, 0.161f, 0.156f, 0.152f, 0.148f,
  0.145f, 0.143f, 0.141f, 0.139f, 0.138f, 0.137f, 0.137f, 0.135f, 0.132f, 0.128f,
  0.125f, 0.124f, 0.124f, 0.123f, 0.123f, 0.121f, 0.118f, 0.113f, 0.111f, 0.113f,
  0.119f, 0.131f, 0.149f, 0.171f, 0.197f, 0.225f, 0.255f, 0.284f, 0.311f, 0.337f,
  0.361f, 0.382f, 0.400f, 0.417f, 0.430f, 0.446f, 0.464f, 0.484f, 0.505f, 0.527f,
  0.547f, 0.568f, 0.588f, 0.608f, 0.627f, 0.648f, 0.668f, 0.688f, 0.709f, 0.729f,
  0.749f, 0.769f, 0.787f, 0.803f, 0.817f, 0.829f, 0.839f, 0.849f, 0.853f, 0.857f,
  0.859f};



typedef struct CMVisMetamericColors CMVisMetamericColors;
struct CMVisMetamericColors{
  CMLVec3 visStandardRGBFloatData[5];
  CMLVec3 visMetamerRGBFloatData[5];
  float metamericIndex[5];
  float avg5;
};

struct CPVisMetamericIndexController{
  NASpace* space;

  NALabel* title;
  NALabel* metamerics1IndexLabel;
  NALabel* metamerics1Label;
  CPTwoColorController* metamerics1Display;
  NALabel* metamerics2IndexLabel;
  NALabel* metamerics2Label;
  CPTwoColorController* metamerics2Display;
  NALabel* metamerics3IndexLabel;
  NALabel* metamerics3Label;
  CPTwoColorController* metamerics3Display;
  NALabel* metamerics4IndexLabel;
  NALabel* metamerics4Label;
  CPTwoColorController* metamerics4Display;
  NALabel* metamerics5IndexLabel;
  NALabel* metamerics5Label;
  CPTwoColorController* metamerics5Display;
  NALabel* metamericsAverageLabel;
  NALabel* metamericsLabel;
  NALabel* metamericsGradeLabel;

  CMVisMetamericColors visMetamericColors;
};



CMVisMetamericColors cmComputeVisMetamericColors(
  CMLFunction* observer10Funcs[3],
  const CPWhitePoints* illWhitePoint10,
  const CMLMat33 adaptationMatrix,
  CMReferenceIlluminationType referenceIlluminationType){
  
  CMVisMetamericColors metamericColors;
  
  CMLColorMachine* cm = cmGetCurrentColorMachine();
  CMLColorMachine* sm = cmGetCurrentScreenMachine();
  CMLIntegration integration = cmlMakeDefaultIntegration();
  const CMLFunction* illuminationSpec = cmlGetIlluminationSpectrum(cm);

  const float* standardData[5] = {standard1Data, standard2Data, standard3Data, standard4Data, standard5Data};
  const float* specimenData[5];
  switch(referenceIlluminationType){
  case REFERENCE_ILLUMINATION_D50:
    specimenData[0] = specimen1D50Data;
    specimenData[1] = specimen2D50Data;
    specimenData[2] = specimen3D50Data;
    specimenData[3] = specimen4D50Data;
    specimenData[4] = specimen5D50Data;
    break;
  case REFERENCE_ILLUMINATION_D55:
    specimenData[0] = specimen1D55Data;
    specimenData[1] = specimen2D55Data;
    specimenData[2] = specimen3D55Data;
    specimenData[3] = specimen4D55Data;
    specimenData[4] = specimen5D55Data;
    break;
  case REFERENCE_ILLUMINATION_D65:
    specimenData[0] = specimen1D65Data;
    specimenData[1] = specimen2D65Data;
    specimenData[2] = specimen3D65Data;
    specimenData[3] = specimen4D65Data;
    specimenData[4] = specimen5D65Data;
    break;
  case REFERENCE_ILLUMINATION_D75:
    specimenData[0] = specimen1D75Data;
    specimenData[1] = specimen2D75Data;
    specimenData[2] = specimen3D75Data;
    specimenData[3] = specimen4D75Data;
    specimenData[4] = specimen5D75Data;
    break;
  default:
    specimenData[0] = specimen1D50Data;
    specimenData[1] = specimen2D50Data;
    specimenData[2] = specimen3D50Data;
    specimenData[3] = specimen4D50Data;
    specimenData[4] = specimen5D50Data;
    break;
  }

  float standardXYZ[5 * 3];
  float specimenXYZ[5 * 3];

  for(int i = 0; i < 5; ++i){
    CMLArrayFunctionInput inputStandard = {
      standardData[i],
      NA_FALSE,
      { VIS_METAMER_STANDARD_DATA_COUNT,
        VIS_METAMER_STANDARD_DATA_LAMBDA_MIN,
        VIS_METAMER_STANDARD_DATA_LAMBDA_MAX,
        CML_INTERPOLATION_LINEAR,
        CML_EXTRAPOLATION_LINEAR_ZERO,
        CML_EXTRAPOLATION_LINEAR_ZERO}};
    CMLFunction* standardfunction = cmlCreateArrayFunction(inputStandard);
    CMLArrayFunctionInput inputSpecimen = {
      specimenData[i],
      NA_FALSE,
      { VIS_METAMER_SPECIMEN_DATA_COUNT,
        VIS_METAMER_SPECIMEN_DATA_LAMBDA_MIN,
        VIS_METAMER_SPECIMEN_DATA_LAMBDA_MAX,
        CML_INTERPOLATION_LINEAR,
        CML_EXTRAPOLATION_LINEAR_ZERO,
        CML_EXTRAPOLATION_LINEAR_ZERO}};
    CMLFunction* specimenfunction = cmlCreateArrayFunction(inputSpecimen);

    float* standardXYZptr = &(standardXYZ[i * 3]);
    float* specimenXYZptr = &(specimenXYZ[i * 3]);

    CMLVec3 standardLab;
    CMLVec3 specimenLab;

    if(illuminationSpec){
      CMLFunction* standardremission = cmlCreateFunctionMulFunction(standardfunction, illuminationSpec);
      cmlSet3(
        standardXYZptr,
        cmlFilterFunction(standardremission, observer10Funcs[0], &integration),
        cmlFilterFunction(standardremission, observer10Funcs[1], &integration),
        cmlFilterFunction(standardremission, observer10Funcs[2], &integration));
      cmlDiv3(standardXYZptr, illWhitePoint10->XYZunnorm[1]);
      cmlConvertXYZToLab(standardLab, standardXYZptr, illWhitePoint10->XYZ);

      CMLFunction* specimenremission = cmlCreateFunctionMulFunction(specimenfunction, illuminationSpec);
      cmlSet3(
        specimenXYZptr,
        cmlFilterFunction(specimenremission, observer10Funcs[0], &integration),
        cmlFilterFunction(specimenremission, observer10Funcs[1], &integration),
        cmlFilterFunction(specimenremission, observer10Funcs[2], &integration));
      cmlDiv3(specimenXYZptr, illWhitePoint10->XYZunnorm[1]);
      cmlConvertXYZToLab(specimenLab, specimenXYZptr, illWhitePoint10->XYZ);
      cmlReleaseFunction(standardremission);
      cmlReleaseFunction(specimenremission);
    }else{
      cmlSet3(standardXYZptr, 0.f, 0.f, 0.f);
      cmlSet3(standardLab, 0.f, 0.f, 0.f);
      cmlSet3(specimenXYZptr, 0.f, 0.f, 0.f);
      cmlSet3(specimenLab, 0.f, 0.f, 0.f);
    }
    
    cmlSub3(specimenLab, standardLab);
    metamericColors.metamericIndex[i] = cmlLength2(&((specimenLab)[1]));
  }

  float standardAdaptedXYZData[5 * 3];
  cmlConvertXYZToChromaticAdaptedXYZ(&(standardAdaptedXYZData[0]), &(standardXYZ[0]), adaptationMatrix);
  cmlConvertXYZToChromaticAdaptedXYZ(&(standardAdaptedXYZData[3]), &(standardXYZ[3]), adaptationMatrix);
  cmlConvertXYZToChromaticAdaptedXYZ(&(standardAdaptedXYZData[6]), &(standardXYZ[6]), adaptationMatrix);
  cmlConvertXYZToChromaticAdaptedXYZ(&(standardAdaptedXYZData[9]), &(standardXYZ[9]), adaptationMatrix);
  cmlConvertXYZToChromaticAdaptedXYZ(&(standardAdaptedXYZData[12]), &(standardXYZ[12]), adaptationMatrix);
  fillRGBFloatArrayWithArray(
    cm,
    sm,
    metamericColors.visStandardRGBFloatData[0],
    standardAdaptedXYZData,
    CML_COLOR_XYZ,
    cmlGetNormedInputConverter(CML_COLOR_XYZ),
    5);
  
  float specimenAptedXYZData[5 * 3];
  cmlConvertXYZToChromaticAdaptedXYZ(&(specimenAptedXYZData[0]), &(specimenXYZ[0]), adaptationMatrix);
  cmlConvertXYZToChromaticAdaptedXYZ(&(specimenAptedXYZData[3]), &(specimenXYZ[3]), adaptationMatrix);
  cmlConvertXYZToChromaticAdaptedXYZ(&(specimenAptedXYZData[6]), &(specimenXYZ[6]), adaptationMatrix);
  cmlConvertXYZToChromaticAdaptedXYZ(&(specimenAptedXYZData[9]), &(specimenXYZ[9]), adaptationMatrix);
  cmlConvertXYZToChromaticAdaptedXYZ(&(specimenAptedXYZData[12]), &(specimenXYZ[12]), adaptationMatrix);
  fillRGBFloatArrayWithArray(
    cm,
    sm,
    metamericColors.visMetamerRGBFloatData[0],
    specimenAptedXYZData,
    CML_COLOR_XYZ,
    cmlGetNormedInputConverter(CML_COLOR_XYZ),
    5);

  metamericColors.avg5 = metamericColors.metamericIndex[0]
    + metamericColors.metamericIndex[1]
    + metamericColors.metamericIndex[2]
    + metamericColors.metamericIndex[3]
    + metamericColors.metamericIndex[4];
  metamericColors.avg5 /= 5.f;

  return metamericColors;
}



CPVisMetamericIndexController* cmAllocVisMetamericIndexController(void){
  CPVisMetamericIndexController* con = naAlloc(CPVisMetamericIndexController);

  con->space = naNewSpace(naMakeSize(1, 1));
//  naSetSpaceAlternateBackground(con->space, NA_TRUE);

  con->title = cmNewTitleLabel(cmTranslate(CMVisMetamericIndex), 250);
  
  con->metamerics1IndexLabel = naNewLabel(cmTranslate(CMColorIndex1), indexWidth);
  con->metamerics1Label = cmNewValueLabel();
  con->metamerics1Display = cmAllocTwoColorController();

  con->metamerics2IndexLabel = naNewLabel(cmTranslate(CMColorIndex2), indexWidth);
  con->metamerics2Label = cmNewValueLabel();
  con->metamerics2Display = cmAllocTwoColorController();

  con->metamerics3IndexLabel = naNewLabel(cmTranslate(CMColorIndex3), indexWidth);
  con->metamerics3Label = cmNewValueLabel();
  con->metamerics3Display = cmAllocTwoColorController();

  con->metamerics4IndexLabel = naNewLabel(cmTranslate(CMColorIndex4), indexWidth);
  con->metamerics4Label = cmNewValueLabel();
  con->metamerics4Display = cmAllocTwoColorController();

  con->metamerics5IndexLabel = naNewLabel(cmTranslate(CMColorIndex5), indexWidth);
  con->metamerics5Label = cmNewValueLabel();
  con->metamerics5Display = cmAllocTwoColorController();

  con->metamericsAverageLabel = naNewLabel(cmTranslate(CMAverage), indexWidth);
  con->metamericsLabel = cmNewValueLabel();
  con->metamericsGradeLabel = naNewLabel("", 120);



  // Placing elements in the space

  cmBeginUILayout(con->space, spaceBezel);
  cmAddUIRow(con->title, uiElemHeight);

  cmAddUIRow(con->metamerics1IndexLabel, uiElemHeight);
  cmAddUICol(con->metamerics1Label, indexMargin);
  cmAddUICol(cmGetTwoColorControllerUIElement(con->metamerics1Display), valueMargin);

  cmAddUIRow(con->metamerics2IndexLabel, uiElemHeight);
  cmAddUICol(con->metamerics2Label, indexMargin);
  cmAddUICol(cmGetTwoColorControllerUIElement(con->metamerics2Display), valueMargin);

  cmAddUIRow(con->metamerics3IndexLabel, uiElemHeight);
  cmAddUICol(con->metamerics3Label, indexMargin);
  cmAddUICol(cmGetTwoColorControllerUIElement(con->metamerics3Display), valueMargin);

  cmAddUIRow(con->metamerics4IndexLabel, uiElemHeight);
  cmAddUICol(con->metamerics4Label, indexMargin);
  cmAddUICol(cmGetTwoColorControllerUIElement(con->metamerics4Display), valueMargin);

  cmAddUIRow(con->metamerics5IndexLabel, uiElemHeight);
  cmAddUICol(con->metamerics5Label, indexMargin);
  cmAddUICol(cmGetTwoColorControllerUIElement(con->metamerics5Display), valueMargin);

  cmAddUIRow(con->metamericsAverageLabel, uiElemHeight);
  cmAddUICol(con->metamericsLabel, indexMargin);
  cmAddUICol(con->metamericsGradeLabel, valueMargin);

  cmEndUILayout();

  return con;
}



void cmDeallocVisMetamericIndexController(CPVisMetamericIndexController* con){
  naFree(con);
}



NASpace* cmGetVisMetamericIndexUIElement(CPVisMetamericIndexController* con){
  return con->space;
}



float cmGetVisMetamericIndexAverage(CPVisMetamericIndexController* con){
  return con->visMetamericColors.avg5;
}



void cmUpdateVisMetamericIndexController(
  CPVisMetamericIndexController* con,
  CMLFunction* observer10Funcs[3],
  const CPWhitePoints* illWhitePoint10,
  const CMLMat33 adaptationMatrix,
  CMReferenceIlluminationType referenceIlluminationType,
  NABool valid)
{
  if(valid){
    con->visMetamericColors = cmComputeVisMetamericColors(
      observer10Funcs,
      illWhitePoint10,
      adaptationMatrix,
      referenceIlluminationType);

    naSetLabelText(
      con->metamerics1Label,
      naAllocSprintf(NA_TRUE, "%1.04f", con->visMetamericColors.metamericIndex[0]));
    cmUpdateTwoColorController(
      con->metamerics1Display,
      con->visMetamericColors.visStandardRGBFloatData[0],
      con->visMetamericColors.visMetamerRGBFloatData[0]);

    naSetLabelText(
      con->metamerics2Label,
      naAllocSprintf(NA_TRUE, "%1.04f", con->visMetamericColors.metamericIndex[1]));
    cmUpdateTwoColorController(
      con->metamerics2Display,
      con->visMetamericColors.visStandardRGBFloatData[1],
      con->visMetamericColors.visMetamerRGBFloatData[1]);

    naSetLabelText(
      con->metamerics3Label,
      naAllocSprintf(NA_TRUE, "%1.04f", con->visMetamericColors.metamericIndex[2]));
    cmUpdateTwoColorController(
      con->metamerics3Display,
      con->visMetamericColors.visStandardRGBFloatData[2],
      con->visMetamericColors.visMetamerRGBFloatData[2]);

    naSetLabelText(
      con->metamerics4Label,
      naAllocSprintf(NA_TRUE, "%1.04f", con->visMetamericColors.metamericIndex[3]));
    cmUpdateTwoColorController(
      con->metamerics4Display,
      con->visMetamericColors.visStandardRGBFloatData[3],
      con->visMetamericColors.visMetamerRGBFloatData[3]);

    naSetLabelText(
      con->metamerics5Label,
      naAllocSprintf(NA_TRUE, "%1.04f", con->visMetamericColors.metamericIndex[4]));
    cmUpdateTwoColorController(
      con->metamerics5Display,
      con->visMetamericColors.visStandardRGBFloatData[4],
      con->visMetamericColors.visMetamerRGBFloatData[4]);

    naSetLabelText(con->metamericsLabel, naAllocSprintf(NA_TRUE, "%1.04f", con->visMetamericColors.avg5));
    naSetLabelText(con->metamericsGradeLabel, naAllocSprintf(NA_TRUE, cmTranslate(CMGrade), getGrade(con->visMetamericColors.avg5)));
  }else{
    naSetLabelText(con->metamerics1Label, "");
    naSetLabelText(con->metamerics2Label, "");
    naSetLabelText(con->metamerics3Label, "");
    naSetLabelText(con->metamerics4Label, "");
    naSetLabelText(con->metamerics5Label, "");
    cmUpdateTwoColorController(con->metamerics1Display, greyColor, greyColor);
    cmUpdateTwoColorController(con->metamerics2Display, greyColor, greyColor);
    cmUpdateTwoColorController(con->metamerics3Display, greyColor, greyColor);
    cmUpdateTwoColorController(con->metamerics4Display, greyColor, greyColor);
    cmUpdateTwoColorController(con->metamerics5Display, greyColor, greyColor);
    naSetLabelText(con->metamericsLabel, "");
    naSetLabelText(con->metamericsGradeLabel, "");
  }
}
