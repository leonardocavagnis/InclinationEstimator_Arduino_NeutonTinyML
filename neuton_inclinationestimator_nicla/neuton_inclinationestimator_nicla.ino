/**
  ******************************************************************************
  * @file    neuton_inclinationestimator_nicla.ino
  * @author  Leonardo Cavagnis
  * @brief   An Inclination estimator system with Neuton TinyML
  *
  ******************************************************************************
  */
#define REGRESSION 0
#define MULTICLASS 1
#define TASK_TYPE  REGRESSION

/* Includes ------------------------------------------------------------------*/
#include "Arduino.h"
#include "Arduino_BHY2.h"

#if (TASK_TYPE == REGRESSION)
   #include "src/regression/neuton.h"
#elif (TASK_TYPE == MULTICLASS)
   #include "src/multiclass/neuton.h"
#endif

/* Private define ------------------------------------------------------------*/
#define NUM_SAMPLES     50
#define SAMPLE_TIME_MS  20

/* Private variables ---------------------------------------------------------*/
SensorXYZ acc(SENSOR_ID_ACC);
SensorXYZ gyro(SENSOR_ID_GYRO);

float inputs[NUM_SAMPLES*6] = { 0 };

void setup() {
  // init serial port
  Serial.begin(115200);
  while (!Serial) {
    delay(10);
  }

  // init IMU sensor
  BHY2.begin();
  acc.begin();
  gyro.begin();

  Serial.println("Neuton neural network model: Inclination estimator system");
}

void loop() {
  int samplesRead = 0;

  // perform IMU measurement
  while (samplesRead < NUM_SAMPLES) {
    // read the acceleration and gyroscope data
    BHY2.update();

    // fill sensor data array (model input)
    inputs[0+samplesRead*6] = (float) acc.x();
    inputs[1+samplesRead*6] = (float) acc.y();
    inputs[2+samplesRead*6] = (float) acc.z();
    inputs[3+samplesRead*6] = (float) gyro.x();
    inputs[4+samplesRead*6] = (float) gyro.y();
    inputs[5+samplesRead*6] = (float) gyro.z();

    samplesRead++;
    
    delay(SAMPLE_TIME_MS);
  }

  // provide inputs to Neuton neural network model
  if (neuton_model_set_inputs(inputs) == 0) {
    uint16_t  predictedClass;
    float*    probabilities;

    // run model inference
    if (neuton_model_run_inference(&predictedClass, &probabilities) == 0) {
      Serial.print("Estimated slope: ");
      #if (TASK_TYPE == MULTICLASS) 
        Serial.print(predictedClass);
        Serial.print("°");
        // show class probabilities
        Serial.print(" - Probabilities [ ");
        for (int i=0; i<neuton_model_outputs_count(); i++) {
            Serial.print(probabilities[i]);
            Serial.print(" ");
        }
        Serial.println("]");   
      #elif (TASK_TYPE == REGRESSION) 
        Serial.print(probabilities[0]);
        Serial.println("°");
      #endif
    } else {
      Serial.println("Inference result not valid");
    }
   } else {
    Serial.println("Failed to initialize Neuton model");
   }
}
