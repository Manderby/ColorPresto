
#include "CMUVMetamericIndexController.h"

#include "CMDesign.h"
#include "CMTwoColorController.h"
#include "CMMetamericsController.h"
#include "CMTranslations.h"
#include "CMWhitePoints.h"

#include "mainC.h"

#include "NAApp.h"



#define FLUORESCENT_REMISSION_DATA_COUNT 35
#define FLUORESCENT_REMISSION_DATA_LAMBDA_MIN 400.f
#define FLUORESCENT_REMISSION_DATA_LAMBDA_MAX 570.f
const float fluorescentRemissionData[FLUORESCENT_REMISSION_DATA_COUNT] = {
  0.008f, 0.011f, 0.022f, 0.036f, 0.051f, 0.070f, 0.085f, 0.092f, 0.090f, 0.081f,
  0.071f, 0.064f, 0.056f, 0.048f, 0.039f, 0.033f, 0.028f, 0.022f, 0.018f, 0.014f,
  0.011f, 0.009f, 0.008f, 0.006f, 0.005f, 0.004f, 0.004f, 0.003f, 0.003f, 0.003f,
  0.001f, 0.001f, 0.001f, 0.001f, 0.001f};

#define UV_STANDARD_DATA_COUNT 61
#define UV_STANDARD_DATA_LAMBDA_MIN 400.f
#define UV_STANDARD_DATA_LAMBDA_MAX 700.f
const float UVStandard1Data[UV_STANDARD_DATA_COUNT] = {
  0.638f, 0.661f, 0.683f, 0.704f, 0.722f, 0.734f, 0.742f, 0.750f, 0.756f, 0.761f,
  0.766f, 0.770f, 0.774f, 0.778f, 0.782f, 0.788f, 0.794f, 0.799f, 0.804f, 0.808f,
  0.812f, 0.817f, 0.822f, 0.827f, 0.830f, 0.831f, 0.831f, 0.831f, 0.832f, 0.832f,
  0.833f, 0.833f, 0.834f, 0.834f, 0.835f, 0.835f, 0.836f, 0.837f, 0.837f, 0.837f,
  0.838f, 0.839f, 0.840f, 0.842f, 0.844f, 0.846f, 0.848f, 0.850f, 0.852f, 0.854f,
  0.856f, 0.857f, 0.857f, 0.857f, 0.858f, 0.859f, 0.860f, 0.861f, 0.862f, 0.863f,
  0.864f};
const float UVStandard2Data[UV_STANDARD_DATA_COUNT] = {
  0.490f, 0.570f, 0.640f, 0.678f, 0.701f, 0.718f, 0.730f, 0.744f, 0.755f, 0.762f,
  0.766f, 0.770f, 0.774f, 0.778f, 0.782f, 0.788f, 0.794f, 0.799f, 0.804f, 0.808f,
  0.812f, 0.817f, 0.822f, 0.827f, 0.830f, 0.831f, 0.831f, 0.831f, 0.832f, 0.832f,
  0.833f, 0.833f, 0.834f, 0.834f, 0.835f, 0.835f, 0.836f, 0.837f, 0.837f, 0.837f,
  0.838f, 0.839f, 0.840f, 0.842f, 0.844f, 0.846f, 0.848f, 0.850f, 0.852f, 0.854f,
  0.856f, 0.857f, 0.857f, 0.857f, 0.858f, 0.859f, 0.860f, 0.861f, 0.862f, 0.863f,
  0.864f};
const float UVStandard3Data[UV_STANDARD_DATA_COUNT] = {
  0.194f, 0.270f, 0.357f, 0.437f, 0.517f, 0.603f, 0.676f, 0.712f, 0.731f, 0.744f,
  0.753f, 0.764f, 0.773f, 0.778f, 0.782f, 0.788f, 0.794f, 0.799f, 0.804f, 0.808f,
  0.812f, 0.817f, 0.822f, 0.827f, 0.830f, 0.831f, 0.831f, 0.831f, 0.832f, 0.832f,
  0.833f, 0.833f, 0.834f, 0.834f, 0.835f, 0.835f, 0.836f, 0.837f, 0.837f, 0.837f,
  0.838f, 0.839f, 0.840f, 0.842f, 0.844f, 0.846f, 0.848f, 0.850f, 0.852f, 0.854f,
  0.856f, 0.857f, 0.857f, 0.857f, 0.858f, 0.859f, 0.860f, 0.861f, 0.862f, 0.863f,
  0.864f};

// Following are the data as they can be found in ISO-23603:2005 Table 5. But
// the table lists the values premultiplied with deltaLambda, which is 5. As
// CML will do normalization automatically, the values have been divided by 5
// in this code. See below.

//const float UVExcitation1Data[] = {
//  0.182f, 0.194f, 0.205f, 0.214f, 0.220f, 0.226f, 0.230f, 0.232f, 0.232f, 0.230f,
//  0.224f, 0.216f, 0.204f, 0.177f, 0.145f, 0.117f, 0.088f, 0.056f, 0.028f, 0.016f,
//  0.011f, 0.009f, 0.006f, 0.002f, 0.000f, 0.000f, 0.000f, 0.000f, 0.000f, 0.000f,
//  0.000f, 0.000f, 0.000f};
//const float UVExcitation2Data[] = {
//  0.000f, 0.000f, 0.001f, 0.001f, 0.006f, 0.023f, 0.050f, 0.075f, 0.102f, 0.137f,
//  0.174f, 0.204f, 0.218f, 0.227f, 0.229f, 0.228f, 0.220f, 0.196f, 0.164f, 0.134f,
//  0.104f, 0.068f, 0.038f, 0.023f, 0.016f, 0.011f, 0.007f, 0.004f, 0.001f, 0.000f,
//  0.000f, 0.000f, 0.000f};
//const float UVExcitation3Data[] = {
//  0.000f, 0.000f, 0.000f, 0.000f, 0.000f, 0.000f, 0.001f, 0.001f, 0.002f, 0.025f,
//  0.055f, 0.082f, 0.111f, 0.152f, 0.191f, 0.218f, 0.235f, 0.244f, 0.245f, 0.245f,
//  0.237f, 0.213f, 0.182f, 0.153f, 0.120f, 0.082f, 0.046f, 0.028f, 0.019f, 0.013f,
//  0.009f, 0.005f, 0.001f};

#define UV_EXCITATION_DATA_COUNT 33
#define UV_EXCITATION_DATA_LAMBDA_MIN 300.f
#define UV_EXCITATION_DATA_LAMBDA_MAX 460.f
const float UVExcitation1Data[UV_EXCITATION_DATA_COUNT] = {
  0.0364f, 0.0388f, 0.0410f, 0.0428f, 0.0440f, 0.0452f, 0.0460f, 0.0464f, 0.0464f, 0.0460f,
  0.0448f, 0.0432f, 0.0408f, 0.0354f, 0.0290f, 0.0234f, 0.0176f, 0.0112f, 0.0056f, 0.0032f,
  0.0022f, 0.0018f, 0.0012f, 0.0004f, 0.0000f, 0.0000f, 0.0000f, 0.0000f, 0.0000f, 0.0000f,
  0.0000f, 0.0000f, 0.0000f};
const float UVExcitation2Data[UV_EXCITATION_DATA_COUNT] = {
  0.0000f, 0.0000f, 0.0002f, 0.0002f, 0.0012f, 0.0046f, 0.0100f, 0.0150f, 0.0204f, 0.0274f,
  0.0348f, 0.0408f, 0.0436f, 0.0454f, 0.0458f, 0.0456f, 0.0440f, 0.0392f, 0.0328f, 0.0268f,
  0.0208f, 0.0136f, 0.0076f, 0.0046f, 0.0032f, 0.0022f, 0.0014f, 0.0008f, 0.0002f, 0.0000f,
  0.0000f, 0.0000f, 0.0000f};
const float UVExcitation3Data[UV_EXCITATION_DATA_COUNT] = {
  0.0000f, 0.0000f, 0.0000f, 0.0000f, 0.0000f, 0.0000f, 0.0002f, 0.0002f, 0.0004f, 0.0050f,
  0.0110f, 0.0164f, 0.0222f, 0.0304f, 0.0382f, 0.0436f, 0.0470f, 0.0488f, 0.0490f, 0.0490f,
  0.0474f, 0.0426f, 0.0364f, 0.0306f, 0.0240f, 0.0164f, 0.0092f, 0.0056f, 0.0038f, 0.0026f,
  0.0018f, 0.0010f, 0.0002f};

#define UV_METAMER_DATA_COUNT 61
#define UV_METAMER_DATA_LAMBDA_MIN 400.f
#define UV_METAMER_DATA_LAMBDA_MAX 700.f
const float UVMetamer1D50Data[] = {
  0.662f, 0.687f, 0.711f, 0.742f, 0.767f, 0.797f, 0.822f, 0.824f, 0.820f, 0.816f,
  0.810f, 0.808f, 0.807f, 0.807f, 0.804f, 0.806f, 0.810f, 0.812f, 0.814f, 0.816f,
  0.818f, 0.822f, 0.826f, 0.830f, 0.831f, 0.832f, 0.832f, 0.832f, 0.833f, 0.833f,
  0.834f, 0.835f, 0.835f, 0.835f, 0.836f, 0.836f, 0.836f, 0.837f, 0.837f, 0.837f,
  0.838f, 0.839f, 0.840f, 0.842f, 0.844f, 0.846f, 0.848f, 0.850f, 0.851f, 0.851f,
  0.852f, 0.852f, 0.852f, 0.853f, 0.853f, 0.853f, 0.853f, 0.853f, 0.853f, 0.853f,
  0.853f};
const float UVMetamer2D50Data[] = {
  0.505f, 0.589f, 0.668f, 0.723f, 0.764f, 0.805f, 0.838f, 0.845f, 0.843f, 0.836f,
  0.826f, 0.822f, 0.820f, 0.816f, 0.813f, 0.813f, 0.816f, 0.817f, 0.818f, 0.819f,
  0.821f, 0.825f, 0.829f, 0.831f, 0.833f, 0.833f, 0.833f, 0.833f, 0.834f, 0.834f,
  0.834f, 0.834f, 0.834f, 0.834f, 0.835f, 0.835f, 0.836f, 0.837f, 0.837f, 0.837f,
  0.838f, 0.839f, 0.840f, 0.842f, 0.844f, 0.846f, 0.848f, 0.850f, 0.852f, 0.854f,
  0.856f, 0.856f, 0.856f, 0.856f, 0.856f, 0.858f, 0.858f, 0.858f, 0.858f, 0.858f,
  0.859f};
const float UVMetamer3D50Data[] = {
  0.212f, 0.293f, 0.401f, 0.507f, 0.613f, 0.737f, 0.842f, 0.868f, 0.866f, 0.857f,
  0.845f, 0.845f, 0.843f, 0.837f, 0.830f, 0.828f, 0.827f, 0.826f, 0.826f, 0.825f,
  0.825f, 0.828f, 0.831f, 0.834f, 0.836f, 0.836f, 0.835f, 0.834f, 0.835f, 0.835f,
  0.834f, 0.834f, 0.835f, 0.835f, 0.836f, 0.835f, 0.836f, 0.837f, 0.837f, 0.837f,
  0.838f, 0.839f, 0.840f, 0.842f, 0.844f, 0.846f, 0.848f, 0.850f, 0.852f, 0.854f,
  0.856f, 0.857f, 0.857f, 0.857f, 0.858f, 0.859f, 0.860f, 0.861f, 0.862f, 0.863f,
  0.864f};

const float UVMetamer1D55Data[] = {
  0.646f, 0.674f, 0.705f, 0.740f, 0.773f, 0.806f, 0.832f, 0.835f, 0.831f, 0.825f,
  0.818f, 0.815f, 0.814f, 0.812f, 0.810f, 0.811f, 0.814f, 0.815f, 0.817f, 0.818f,
  0.820f, 0.824f, 0.828f, 0.831f, 0.833f, 0.833f, 0.833f, 0.833f, 0.834f, 0.834f,
  0.834f, 0.834f, 0.835f, 0.835f, 0.836f, 0.835f, 0.836f, 0.837f, 0.837f, 0.837f,
  0.838f, 0.839f, 0.840f, 0.842f, 0.844f, 0.846f, 0.848f, 0.850f, 0.852f, 0.854f,
  0.856f, 0.857f, 0.857f, 0.857f, 0.858f, 0.859f, 0.860f, 0.861f, 0.862f, 0.863f,
  0.864f};
const float UVMetamer2D55Data[] = {
  0.501f, 0.587f, 0.669f, 0.725f, 0.769f, 0.813f, 0.848f, 0.856f, 0.854f, 0.846f,
  0.835f, 0.830f, 0.827f, 0.823f, 0.819f, 0.818f, 0.820f, 0.820f, 0.821f, 0.821f,
  0.823f, 0.826f, 0.830f, 0.832f, 0.834f, 0.834f, 0.834f, 0.833f, 0.834f, 0.834f,
  0.834f, 0.834f, 0.835f, 0.835f, 0.836f, 0.835f, 0.836f, 0.837f, 0.837f, 0.837f,
  0.838f, 0.839f, 0.840f, 0.842f, 0.844f, 0.846f, 0.848f, 0.850f, 0.852f, 0.854f,
  0.856f, 0.857f, 0.857f, 0.857f, 0.858f, 0.859f, 0.860f, 0.861f, 0.862f, 0.863f,
  0.864f};
const float UVMetamer3D55Data[] = {
  0.210f, 0.295f, 0.400f, 0.507f, 0.618f, 0.744f, 0.852f, 0.878f, 0.878f, 0.869f,
  0.855f, 0.853f, 0.851f, 0.845f, 0.838f, 0.833f, 0.832f, 0.830f, 0.829f, 0.828f,
  0.828f, 0.830f, 0.833f, 0.835f, 0.837f, 0.836f, 0.836f, 0.834f, 0.835f, 0.835f,
  0.835f, 0.835f, 0.836f, 0.836f, 0.837f, 0.835f, 0.836f, 0.837f, 0.837f, 0.837f,
  0.838f, 0.839f, 0.840f, 0.842f, 0.844f, 0.846f, 0.848f, 0.850f, 0.852f, 0.854f,
  0.856f, 0.857f, 0.857f, 0.857f, 0.858f, 0.859f, 0.860f, 0.861f, 0.862f, 0.863f,
  0.864f};

const float UVMetamer1D65Data[] = {
  0.648f, 0.676f, 0.709f, 0.748f, 0.785f, 0.824f, 0.855f, 0.860f, 0.855f, 0.846f,
  0.836f, 0.832f, 0.829f, 0.825f, 0.822f, 0.821f, 0.822f, 0.822f, 0.823f, 0.823f,
  0.824f, 0.827f, 0.831f, 0.833f, 0.835f, 0.835f, 0.835f, 0.834f, 0.835f, 0.835f,
  0.834f, 0.834f, 0.835f, 0.835f, 0.836f, 0.835f, 0.836f, 0.837f, 0.837f, 0.837f,
  0.838f, 0.839f, 0.840f, 0.842f, 0.844f, 0.846f, 0.848f, 0.850f, 0.852f, 0.854f,
  0.856f, 0.857f, 0.857f, 0.857f, 0.858f, 0.859f, 0.860f, 0.861f, 0.862f, 0.863f,
  0.864f};
const float UVMetamer2D65Data[] = {
  0.502f, 0.589f, 0.672f, 0.731f, 0.778f, 0.828f, 0.868f, 0.878f, 0.876f, 0.866f,
  0.852f, 0.846f, 0.841f, 0.836f, 0.831f, 0.828f, 0.828f, 0.827f, 0.827f, 0.826f,
  0.827f, 0.829f, 0.833f, 0.835f, 0.836f, 0.836f, 0.836f, 0.834f, 0.835f, 0.835f,
  0.835f, 0.835f, 0.836f, 0.836f, 0.837f, 0.835f, 0.836f, 0.837f, 0.837f, 0.837f,
  0.838f, 0.839f, 0.840f, 0.842f, 0.844f, 0.846f, 0.848f, 0.850f, 0.852f, 0.854f,
  0.856f, 0.857f, 0.857f, 0.857f, 0.858f, 0.859f, 0.860f, 0.861f, 0.862f, 0.863f,
  0.864f};
const float UVMetamer3D65Data[] = {
  0.211f, 0.296f, 0.402f, 0.511f, 0.625f, 0.755f, 0.868f, 0.898f, 0.899f, 0.888f,
  0.872f, 0.869f, 0.866f, 0.859f, 0.850f, 0.843f, 0.841f, 0.838f, 0.836f, 0.833f,
  0.833f, 0.834f, 0.837f, 0.838f, 0.839f, 0.837f, 0.837f, 0.835f, 0.836f, 0.836f,
  0.835f, 0.835f, 0.836f, 0.836f, 0.837f, 0.835f, 0.836f, 0.837f, 0.837f, 0.837f,
  0.838f, 0.839f, 0.840f, 0.842f, 0.844f, 0.846f, 0.848f, 0.850f, 0.852f, 0.854f,
  0.856f, 0.857f, 0.857f, 0.857f, 0.858f, 0.859f, 0.860f, 0.861f, 0.862f, 0.863f,
  0.864f};

const float UVMetamer1D75Data[] = {
  0.649f, 0.679f, 0.713f, 0.754f, 0.795f, 0.838f, 0.875f, 0.881f, 0.875f, 0.865f,
  0.852f, 0.846f, 0.842f, 0.837f, 0.832f, 0.829f, 0.830f, 0.828f, 0.828f, 0.827f,
  0.828f, 0.830f, 0.834f, 0.835f, 0.837f, 0.836f, 0.836f, 0.834f, 0.836f, 0.836f,
  0.835f, 0.835f, 0.836f, 0.836f, 0.837f, 0.835f, 0.836f, 0.837f, 0.837f, 0.837f,
  0.838f, 0.839f, 0.840f, 0.842f, 0.844f, 0.846f, 0.848f, 0.850f, 0.852f, 0.854f,
  0.856f, 0.857f, 0.857f, 0.857f, 0.858f, 0.859f, 0.860f, 0.861f, 0.862f, 0.863f,
  0.864f};
const float UVMetamer2D75Data[] = {
  0.503f, 0.590f, 0.675f, 0.736f, 0.786f, 0.839f, 0.885f, 0.896f, 0.894f, 0.882f,
  0.866f, 0.859f, 0.853f, 0.847f, 0.840f, 0.836f, 0.835f, 0.833f, 0.832f, 0.830f,
  0.831f, 0.832f, 0.835f, 0.837f, 0.838f, 0.837f, 0.837f, 0.835f, 0.836f, 0.836f,
  0.835f, 0.835f, 0.836f, 0.836f, 0.837f, 0.835f, 0.836f, 0.837f, 0.837f, 0.837f,
  0.838f, 0.839f, 0.840f, 0.842f, 0.844f, 0.846f, 0.848f, 0.850f, 0.852f, 0.854f,
  0.856f, 0.857f, 0.857f, 0.857f, 0.858f, 0.859f, 0.860f, 0.861f, 0.862f, 0.863f,
  0.864f};
const float UVMetamer3D75Data[] = {
  0.211f, 0.297f, 0.403f, 0.514f, 0.630f, 0.764f, 0.881f, 0.913f, 0.915f, 0.903f,
  0.886f, 0.882f, 0.878f, 0.869f, 0.859f, 0.852f, 0.849f, 0.844f, 0.841f, 0.838f,
  0.837f, 0.837f, 0.840f, 0.840f, 0.841f, 0.839f, 0.839f, 0.836f, 0.837f, 0.837f,
  0.836f, 0.836f, 0.837f, 0.837f, 0.838f, 0.835f, 0.836f, 0.837f, 0.837f, 0.837f,
  0.838f, 0.839f, 0.840f, 0.842f, 0.844f, 0.846f, 0.848f, 0.850f, 0.852f, 0.854f,
  0.856f, 0.857f, 0.857f, 0.857f, 0.858f, 0.859f, 0.860f, 0.861f, 0.862f, 0.863f,
  0.864f};



typedef struct CMUVMetamericColors CMUVMetamericColors;
struct CMUVMetamericColors{
  CMLVec3 uvStandardRGBFloatData[3];
  CMLVec3 uvMetamerRGBFloatData[3];
  float metamericIndex[3];
  float avg3;
};

struct CMUVMetamericIndexController{
  NASpace* space;

  NALabel* title;
  NALabel* metamerics6IndexLabel;
  NALabel* metamerics6Label;
  CMTwoColorController* metamerics6Display;
  NALabel* metamerics7IndexLabel;
  NALabel* metamerics7Label;
  CMTwoColorController* metamerics7Display;
  NALabel* metamerics8IndexLabel;
  NALabel* metamerics8Label;
  CMTwoColorController* metamerics8Display;
  NALabel* metamericsAverageLabel;
  NALabel* metamericsLabel;
  NALabel* metamericsGradeLabel;
  
  CMUVMetamericColors uvMetamericColors;
};



CMUVMetamericColors cmComputeUVMetamericColors(
  CMLFunction* observer10Funcs[3],
  const CMWhitePoints* illWhitePoint10,
  CMReferenceIlluminationType referenceIlluminationType)
{
  CMUVMetamericColors metamericColors;

  CMLColorMachine* cm = cmGetCurrentColorMachine();
  CMLColorMachine* sm = cmGetCurrentScreenMachine();
  CMLIntegration integration = cmlMakeDefaultIntegration();
  const CMLFunction* illuminationSpec = cmlGetReferenceIlluminationSpectrum(cm);

  CMLArrayFunctionInput inputFluorescent = {
    fluorescentRemissionData,
    NA_FALSE,
    { FLUORESCENT_REMISSION_DATA_COUNT,
      FLUORESCENT_REMISSION_DATA_LAMBDA_MIN,
      FLUORESCENT_REMISSION_DATA_LAMBDA_MAX,
      CML_INTERPOLATION_LINEAR,
      CML_EXTRAPOLATION_LINEAR_ZERO,
      CML_EXTRAPOLATION_LINEAR_ZERO}};
  CMLFunction* fluorescentRemissionFunction = cmlCreateArrayFunction(inputFluorescent);
  const float* UVStandardData[3] = {UVStandard1Data, UVStandard2Data, UVStandard3Data};
  const float* UVExcitationData[3] = {UVExcitation1Data, UVExcitation2Data, UVExcitation3Data};

  const float* UVMetamerData[3];
  switch(referenceIlluminationType){
  case REFERENCE_ILLUMINATION_D50:
    UVMetamerData[0] = UVMetamer1D50Data;
    UVMetamerData[1] = UVMetamer2D50Data;
    UVMetamerData[2] = UVMetamer3D50Data;
    break;
  case REFERENCE_ILLUMINATION_D55:
    UVMetamerData[0] = UVMetamer1D55Data;
    UVMetamerData[1] = UVMetamer2D55Data;
    UVMetamerData[2] = UVMetamer3D55Data;
    break;
  case REFERENCE_ILLUMINATION_D65:
    UVMetamerData[0] = UVMetamer1D65Data;
    UVMetamerData[1] = UVMetamer2D65Data;
    UVMetamerData[2] = UVMetamer3D65Data;
    break;
  case REFERENCE_ILLUMINATION_D75:
    UVMetamerData[0] = UVMetamer1D75Data;
    UVMetamerData[1] = UVMetamer2D75Data;
    UVMetamerData[2] = UVMetamer3D75Data;
    break;
  default:
    UVMetamerData[0] = UVMetamer1D50Data;
    UVMetamerData[1] = UVMetamer2D50Data;
    UVMetamerData[2] = UVMetamer3D50Data;
    break;
  }

  float uvStandardXYZ[3 * 3];
  float uvMetamerXYZ[3 * 3];

  for(int i = 0; i < 3; ++i){
    CMLArrayFunctionInput inputUVStandard = {
      UVStandardData[i],
      NA_FALSE,
      { UV_STANDARD_DATA_COUNT,
        UV_STANDARD_DATA_LAMBDA_MIN,
        UV_STANDARD_DATA_LAMBDA_MAX,
        CML_INTERPOLATION_LINEAR,
        CML_EXTRAPOLATION_LINEAR_ZERO,
        CML_EXTRAPOLATION_LINEAR_ZERO}};
    CMLFunction* UVStandardFunction = cmlCreateArrayFunction(inputUVStandard);
    CMLArrayFunctionInput inputUVExcitation = {
      UVExcitationData[i],
      NA_FALSE,
      { UV_EXCITATION_DATA_COUNT,
        UV_EXCITATION_DATA_LAMBDA_MIN,
        UV_EXCITATION_DATA_LAMBDA_MAX,
        CML_INTERPOLATION_LINEAR,
        CML_EXTRAPOLATION_LINEAR_ZERO,
        CML_EXTRAPOLATION_LINEAR_ZERO}};
    CMLFunction* UVExcitationFunction = cmlCreateArrayFunction(inputUVExcitation);
    CMLArrayFunctionInput inputUVMetamer = {
      UVMetamerData[i],
      NA_FALSE,
      { UV_METAMER_DATA_COUNT,
        UV_METAMER_DATA_LAMBDA_MIN,
        UV_METAMER_DATA_LAMBDA_MAX,
        CML_INTERPOLATION_LINEAR,
        CML_EXTRAPOLATION_LINEAR_ZERO,
        CML_EXTRAPOLATION_LINEAR_ZERO}};
    CMLFunction* UVMetamerFunction = cmlCreateArrayFunction(inputUVMetamer);

    float* uvStandardXYZptr = &(uvStandardXYZ[i * 3]);
    float* uvMetamerXYZptr = &(uvMetamerXYZ[i * 3]);

    CMLVec3 UVStandardLab;
    CMLVec3 UVMetamerLab;

    if(illuminationSpec){
      // To correspond with the ISO standard, the excitationN factor must be
      // displayed with (100.f * excitationN * 5.f / illXYZunnorm10[1])
      // The strange factor 5 needs to be here because in the ISO norm, the
      // excitation values are multiplied with the normalized illumination and
      // with a deltaLambda which with the current dataset (see above) is 5.
      // In CML, any normalization is returned as a number independent of
      // deltaLambda, or, so to speak, relative to deltaLambda = 1. This allows
      // to normalize the computational result at the very end. Therefore,
      // to comply with the temporary results published in ISO-3664, the
      // normalization factor 5 must be introduced manually.
      float excitationN = cmlFilterFunction(illuminationSpec, UVExcitationFunction, &integration);
      CMLFunction* betaTemp = cmlCreateFunctionDivFunction(fluorescentRemissionFunction, illuminationSpec);
      CMLFunction* betaL = cmlCreateFunctionMulScalar(betaTemp, excitationN);
      CMLFunction* betaT = cmlCreateFunctionAddFunction(UVStandardFunction, betaL);

      CMLFunction* UVStandardRemission = cmlCreateFunctionMulFunction(betaT, illuminationSpec);
      cmlSet3(
        uvStandardXYZptr,
        cmlFilterFunction(UVStandardRemission, observer10Funcs[0], &integration),
        cmlFilterFunction(UVStandardRemission, observer10Funcs[1], &integration),
        cmlFilterFunction(UVStandardRemission, observer10Funcs[2], &integration));
      cmlDiv3(uvStandardXYZptr, illWhitePoint10->XYZunnorm[1]);
      cmlConvertXYZToLab(UVStandardLab, uvStandardXYZptr, illWhitePoint10->XYZ);

      CMLFunction* UVMetamerRemission = cmlCreateFunctionMulFunction(UVMetamerFunction, illuminationSpec);
      cmlSet3(
        uvMetamerXYZptr,
        cmlFilterFunction(UVMetamerRemission, observer10Funcs[0], &integration),
        cmlFilterFunction(UVMetamerRemission, observer10Funcs[1], &integration),
        cmlFilterFunction(UVMetamerRemission, observer10Funcs[2], &integration));
      cmlDiv3(uvMetamerXYZptr, illWhitePoint10->XYZunnorm[1]);
      cmlConvertXYZToLab(UVMetamerLab, uvMetamerXYZptr, illWhitePoint10->XYZ);
      cmlReleaseFunction(betaTemp);
      cmlReleaseFunction(betaL);
      cmlReleaseFunction(betaT);
      cmlReleaseFunction(UVStandardRemission);
      cmlReleaseFunction(UVMetamerRemission);
    }else{
      cmlSet3(uvStandardXYZptr, 0.f, 0.f, 0.f);
      cmlSet3(UVStandardLab, 0.f, 0.f, 0.f);
      cmlSet3(uvMetamerXYZptr, 0.f, 0.f, 0.f);
      cmlSet3(UVMetamerLab, 0.f, 0.f, 0.f);
    }
    
    cmlSub3(UVMetamerLab, UVStandardLab);
    metamericColors.metamericIndex[i] = cmlLength2(&((UVMetamerLab)[1]));

    cmlReleaseFunction(UVStandardFunction);
    cmlReleaseFunction(UVExcitationFunction);
    cmlReleaseFunction(UVMetamerFunction);
  }

  cmlReleaseFunction(fluorescentRemissionFunction);
  
  // Note that the use of a chromatic adaptation is purely for displaying
  // reasons and is not in the ISO-standard at all. The differences between
  // the colors can be seen better when using the 10 deg observer. That's all.
  CMLMat33 adaptationMatrix;
  CMLVec3 screenWhitePoint;
  cmlCpy3(screenWhitePoint, cmlGetReferenceWhitePointYxy(sm));
  screenWhitePoint[0] = 1.f;
  cmlFillChromaticAdaptationMatrix(adaptationMatrix, CML_CHROMATIC_ADAPTATION_BRADFORD, screenWhitePoint, illWhitePoint10->Yxy);

  float uvStandardAdaptedXYZData[3 * 3];
  cmlConvertXYZToChromaticAdaptedXYZ(&(uvStandardAdaptedXYZData[0]), &(uvStandardXYZ[0]), adaptationMatrix);
  cmlConvertXYZToChromaticAdaptedXYZ(&(uvStandardAdaptedXYZData[3]), &(uvStandardXYZ[3]), adaptationMatrix);
  cmlConvertXYZToChromaticAdaptedXYZ(&(uvStandardAdaptedXYZData[6]), &(uvStandardXYZ[6]), adaptationMatrix);
  fillRGBFloatArrayWithArray(
    cm,
    sm,
    metamericColors.uvStandardRGBFloatData[0],
    uvStandardAdaptedXYZData,
    CML_COLOR_XYZ,
    cmlGetNormedInputConverter(CML_COLOR_XYZ),
    3,
    NA_FALSE,
    NA_FALSE);
  
  float uvMetamerAdaptedXYZData[3 * 3];
  cmlConvertXYZToChromaticAdaptedXYZ(&(uvMetamerAdaptedXYZData[0]), &(uvMetamerXYZ[0]), adaptationMatrix);
  cmlConvertXYZToChromaticAdaptedXYZ(&(uvMetamerAdaptedXYZData[3]), &(uvMetamerXYZ[3]), adaptationMatrix);
  cmlConvertXYZToChromaticAdaptedXYZ(&(uvMetamerAdaptedXYZData[6]), &(uvMetamerXYZ[6]), adaptationMatrix);
  fillRGBFloatArrayWithArray(
    cm,
    sm,
    metamericColors.uvMetamerRGBFloatData[0],
    uvMetamerAdaptedXYZData,
    CML_COLOR_XYZ,
    cmlGetNormedInputConverter(CML_COLOR_XYZ),
    3,
    NA_FALSE,
    NA_FALSE);

  metamericColors.avg3 = metamericColors.metamericIndex[0]
    + metamericColors.metamericIndex[1]
    + metamericColors.metamericIndex[2];
  metamericColors.avg3 /= 3.f;

  return metamericColors;
}



CMUVMetamericIndexController* cmAllocUVMetamericIndexController(void){
  CMUVMetamericIndexController* con = naAlloc(CMUVMetamericIndexController);
  naZeron(con, sizeof(CMUVMetamericIndexController));

  double marginH1 = 0.;
  double marginH2 = 5.;

  double spaceWidth = spaceMarginLeft + indexWidth + marginH1 + valueWidth + marginH2 + twoColorWidth + spaceMarginRight;
  double spaceHeight = 5 * uiElemHeight + spaceMarginV;

  double valueLeft = spaceMarginLeft + indexWidth + marginH1;
  double colorLeft = valueLeft + valueWidth + marginH2;

  con->space = naNewSpace(naMakeSize(spaceWidth, spaceHeight));
//  naSetSpaceAlternateBackground(con->space, NA_TRUE);



  con->title = cmNewTitleLabel(cmTranslate(CMUVMetamericIndex), 250);

  con->metamerics6IndexLabel = naNewLabel("6:", indexWidth);
  con->metamerics6Label = cmNewValueLabel();
  con->metamerics6Display = cmAllocTwoColorController(naMakeSize(twoColorWidth, 21));

  con->metamerics7IndexLabel = naNewLabel("7:", indexWidth);
  con->metamerics7Label = cmNewValueLabel();
  con->metamerics7Display = cmAllocTwoColorController(naMakeSize(twoColorWidth, 21));

  con->metamerics8IndexLabel = naNewLabel("8:", indexWidth);
  con->metamerics8Label = cmNewValueLabel();
  con->metamerics8Display = cmAllocTwoColorController(naMakeSize(twoColorWidth, 21));

  con->metamericsAverageLabel = naNewLabel(cmTranslate(CMAverage), 120);
  con->metamericsLabel = cmNewValueLabel();
  con->metamericsGradeLabel = naNewLabel("", 120);



  // Adding elements to the space

  double spaceY = spaceHeight - spaceMarginTop;
  spaceY -= uiElemHeight;
  naAddSpaceChild(con->space, con->title, naMakePos(spaceMarginLeft, spaceY));
  
  spaceY -= uiElemHeight;
  naAddSpaceChild(con->space, con->metamerics6IndexLabel, naMakePos(spaceMarginLeft, spaceY));
  naAddSpaceChild(con->space, con->metamerics6Label, naMakePos(valueLeft, spaceY));
  naAddSpaceChild(con->space, cmGetTwoColorControllerUIElement(con->metamerics6Display), naMakePos(colorLeft, spaceY));

  spaceY -= uiElemHeight;
  naAddSpaceChild(con->space, con->metamerics7IndexLabel, naMakePos(spaceMarginLeft, spaceY));
  naAddSpaceChild(con->space, con->metamerics7Label, naMakePos(valueLeft, spaceY));
  naAddSpaceChild(con->space, cmGetTwoColorControllerUIElement(con->metamerics7Display), naMakePos(colorLeft, spaceY));

  spaceY -= uiElemHeight;
  naAddSpaceChild(con->space, con->metamerics8IndexLabel, naMakePos(spaceMarginLeft, spaceY));
  naAddSpaceChild(con->space, con->metamerics8Label, naMakePos(valueLeft, spaceY));
  naAddSpaceChild(con->space, cmGetTwoColorControllerUIElement(con->metamerics8Display), naMakePos(colorLeft, spaceY));

  spaceY -= uiElemHeight;
  naAddSpaceChild(con->space, con->metamericsAverageLabel, naMakePos(spaceMarginLeft, spaceY));
  naAddSpaceChild(con->space, con->metamericsLabel, naMakePos(valueLeft, spaceY));
  naAddSpaceChild(con->space, con->metamericsGradeLabel, naMakePos(colorLeft, spaceY));

  return con;
}



void cmDeallocUVMetamericIndexController(CMUVMetamericIndexController* con){
  naFree(con);
}



NASpace* cmGetUVMetamericIndexUIElement(CMUVMetamericIndexController* con){
  return con->space;
}



float cmGetUVMetamericIndexAverage(CMUVMetamericIndexController* con){
  return con->uvMetamericColors.avg3;
}



void cmUpdateUVMetamericIndexController(
  CMUVMetamericIndexController* con,
  CMLFunction* observer10Funcs[3],
  const CMWhitePoints* illWhitePoint10,
  CMReferenceIlluminationType referenceIlluminationType,
  NABool valid)
{
  if(valid){
    con->uvMetamericColors = cmComputeUVMetamericColors(
      observer10Funcs,
      illWhitePoint10,
      referenceIlluminationType);

    naSetLabelText(
      con->metamerics6Label,
      naAllocSprintf(NA_TRUE, "%1.04f", con->uvMetamericColors.metamericIndex[0]));
    cmUpdateTwoColorController(
      con->metamerics6Display,
      con->uvMetamericColors.uvStandardRGBFloatData[0],
      con->uvMetamericColors.uvMetamerRGBFloatData[0]);

    naSetLabelText(
      con->metamerics7Label,
      naAllocSprintf(NA_TRUE, "%1.04f", con->uvMetamericColors.metamericIndex[1]));
    cmUpdateTwoColorController(
      con->metamerics7Display,
      con->uvMetamericColors.uvStandardRGBFloatData[1],
      con->uvMetamericColors.uvMetamerRGBFloatData[1]);
    
    naSetLabelText(
      con->metamerics8Label,
      naAllocSprintf(NA_TRUE, "%1.04f", con->uvMetamericColors.metamericIndex[2]));
    cmUpdateTwoColorController(
      con->metamerics8Display,
      con->uvMetamericColors.uvStandardRGBFloatData[2],
      con->uvMetamericColors.uvMetamerRGBFloatData[2]);

    naSetLabelText(con->metamericsLabel, naAllocSprintf(NA_TRUE, "%1.04f", con->uvMetamericColors.avg3));
    naSetLabelText(con->metamericsGradeLabel, naAllocSprintf(NA_TRUE, cmTranslate(CMGrade), getGrade(con->uvMetamericColors.avg3)));\
  }else{
    naSetLabelText(con->metamerics6Label, "");
    naSetLabelText(con->metamerics7Label, "");
    naSetLabelText(con->metamerics8Label, "");
    cmUpdateTwoColorController(con->metamerics6Display, greyColor, greyColor);
    cmUpdateTwoColorController(con->metamerics7Display, greyColor, greyColor);
    cmUpdateTwoColorController(con->metamerics8Display, greyColor, greyColor);
    naSetLabelText(con->metamericsLabel, "");
    naSetLabelText(con->metamericsGradeLabel, "");
  }
}
