#ifndef NEUTON_MODEL_MODEL_H
#define NEUTON_MODEL_MODEL_H

#ifdef __cplusplus
extern "C"
{
#endif

/* Model info */
#define NEUTON_MODEL_HEADER_VERSION 3
#define NEUTON_MODEL_QLEVEL 32
#define NEUTON_MODEL_FLOAT_SUPPORT 1
#define NEUTON_MODEL_TASK_TYPE 2  // regression
#define NEUTON_MODEL_NEURONS_COUNT 2
#define NEUTON_MODEL_WEIGHTS_COUNT 9
#define NEUTON_MODEL_INPUTS_COUNT 300
#define NEUTON_MODEL_INPUT_LIMITS_COUNT 300
#define NEUTON_MODEL_OUTPUTS_COUNT 1
#define NEUTON_MODEL_LOG_SCALE_OUTPUTS 0

/* Preprocessing */
#define NEUTON_PREPROCESSING_ENABLED 0
#define NEUTON_DROP_ORIGINAL_FEATURES 0
#define NEUTON_BITMASK_ENABLED 1
#define NEUTON_INPUTS_IS_INTEGER 0
#define NEUTON_MODEL_SA_PRECISION 24

/* Types */
typedef float input_t;
typedef float extracted_feature_t;
typedef float coeff_t;
typedef float weight_t;
typedef double acc_signed_t;
typedef double acc_unsigned_t;
typedef uint16_t sources_size_t;
typedef uint8_t weights_size_t;
typedef uint8_t neurons_size_t;

/* Limits */
static const input_t modelInputMin[] = {
	-360, 56, 4057, -3, -3, -3, -367, 55, 3972, -7, -8, -2, -359, 52, 4037,
	-4, -11, -3, -363, 58, 4015, -4, -7, -3, -361, 59, 4020, -3, -7, -2, -357,
	55, 4040, -4, -7, -3, -360, 59, 4058, -2, -3, -4, -356, 54, 4030, -3, -4,
	-3, -359, 53, 4042, -3, -3, -1, -357, 57, 4050, -4, -3, -3, -356, 51, 4056,
	-3, -3, -3, -356, 50, 4051, -3, -3, -2, -359, 54, 4043, -3, -4, -4, -357,
	55, 4050, -4, -3, -2, -352, 56, 4045, -3, -3, -4, -361, 57, 4056, -4, -2,
	-4, -365, 52, 4052, -4, -3, -2, -359, 51, 4054, -3, -3, -2, -356, 50, 4051,
	-3, -2, -3, -358, 53, 4053, -4, -2, -1, -357, 57, 4050, -4, -2, -1, -359,
	51, 4058, -4, -4, -3, -364, 57, 4053, -4, -6, -2, -359, 54, 4014, -4, -3,
	-2, -360, 59, 4056, -3, -2, -3, -354, 54, 4052, -4, -2, -2, -358, 52, 4040,
	-3, -5, -2, -360, 56, 4056, -4, -2, -1, -364, 55, 4048, -4, -2, -3, -359,
	55, 4053, -4, -4, -2, -362, 59, 4057, -3, -2, -2, -363, 55, 4058, -4, -2,
	-2, -356, 52, 4056, -3, -4, -3, -356, 60, 4046, -5, -3, -2, -367, 58, 4057,
	-3, -4, -3, -360, 54, 4052, -3, -3, -4, -361, 56, 4052, -3, -2, -3, -356,
	58, 4057, -5, -3, -3, -356, 53, 4051, -4, -2, -3, -363, 58, 4055, -2, -3,
	-1, -359, 50, 4057, -3, -2, -2, -357, 54, 4057, -2, -2, -3, -355, 47, 4046,
	-3, -3, -2, -355, 53, 4056, -3, -4, -3, -358, 60, 4057, -3, -2, -3, -359,
	62, 4056, -2, -3, -2, -358, 62, 4050, -4, -2, -2, -362, 47, 4051, -3, -2,
	-2, -357, 53, 4053, -4, -3, -3, -358, 53, 4055, -4, -2, -2 };
static const input_t modelInputMax[] = {
	-298, 504, 4227, 3, 2, 4, -291, 500, 4170, 5, 11, 3, -276, 496, 4133, 8,
	8, 4, -295, 504, 4125, 7, 10, 3, -297, 497, 4116, 3, 4, 3, -298, 500, 4103,
	4, 3, 4, -295, 502, 4103, 4, 7, 3, -292, 502, 4106, 4, 4, 3, -293, 502,
	4107, 4, 2, 2, -298, 501, 4110, 4, 4, 3, -302, 498, 4103, 4, 3, 2, -296,
	499, 4101, 5, 4, 2, -297, 507, 4101, 4, 3, 2, -291, 499, 4096, 3, 4, 2,
	-296, 498, 4099, 5, 4, 3, -288, 500, 4109, 4, 5, 3, -296, 494, 4097, 3,
	2, 3, -290, 502, 4098, 4, 3, 3, -302, 501, 4103, 4, 3, 2, -302, 499, 4095,
	4, 3, 3, -303, 498, 4099, 6, 2, 2, -296, 502, 4099, 3, 2, 3, -291, 493,
	4098, 4, 3, 2, -286, 492, 4098, 3, 3, 3, -299, 489, 4101, 3, 3, 3, -298,
	492, 4121, 3, 2, 3, -290, 501, 4099, 4, 2, 3, -300, 494, 4164, 4, 5, 2,
	-297, 495, 4095, 4, 3, 2, -295, 507, 4097, 3, 1, 3, -291, 499, 4100, 4,
	3, 3, -295, 500, 4093, 4, 4, 4, -301, 498, 4097, 5, 3, 2, -292, 497, 4098,
	3, 3, 4, -290, 498, 4101, 5, 3, 3, -302, 498, 4095, 4, 2, 2, -295, 501,
	4100, 5, 2, 3, -296, 501, 4101, 3, 2, 2, -295, 502, 4103, 4, 3, 3, -293,
	499, 4101, 3, 4, 2, -300, 507, 4099, 3, 3, 2, -299, 494, 4096, 5, 4, 3,
	-305, 500, 4100, 5, 3, 3, -297, 503, 4102, 3, 3, 2, -293, 495, 4098, 4,
	2, 3, -300, 495, 4097, 6, 4, 3, -297, 499, 4098, 3, 3, 2, -297, 500, 4094,
	4, 3, 3, -297, 500, 4100, 2, 3, 2, -297, 501, 4096, 5, 2, 3 };

static const uint8_t modelUsedInputsMask[] = {
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x40, 0x18, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x20,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x40, 0x00,
	0x00, 0x00 };

static const float modelOutputMin[] = { 0 };
static const float modelOutputMax[] = { 5 };

/* Structure */
static const weight_t modelWeights[] = {
	-0.011806562, 0.74664474, 0.0093730325, 0.04329649, 0.013984522, -0.021720702,
	-0.64564705, 1, -0.31440619 };

static const sources_size_t modelLinks[] = {
	62, 67, 68, 189, 248, 278, 300, 0, 300 };

static const weights_size_t modelIntLinksBoundaries[] = { 0, 8 };
static const weights_size_t modelExtLinksBoundaries[] = { 7, 9 };

static const coeff_t modelFuncCoeffs[] = { 4.1118913, 9.4972296 };
static const uint8_t modelFuncTypes[] = { 0, 0 };

static const neurons_size_t modelOutputNeurons[] = { 1 };

#ifdef __cplusplus
}
#endif

#endif // NEUTON_MODEL_MODEL_H

