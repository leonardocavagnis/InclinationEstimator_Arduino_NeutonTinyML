/**
  ******************************************************************************
  * @file    neuton_csvcapture_nicla.ino
  * @author  Leonardo Cavagnis
  * @brief   CSV dataset capture program according to Neuton dataset requirements
  *
  ******************************************************************************
  */
  
/* Includes ------------------------------------------------------------------*/
#include "Arduino.h"
#include "Arduino_BHY2.h"

/* Private define ------------------------------------------------------------*/
#define NUM_SAMPLES     50
#define SAMPLE_TIME_MS  20

/* Private variables ---------------------------------------------------------*/
// IMU sensor handlers
SensorXYZ acc(SENSOR_ID_ACC);
SensorXYZ gyro(SENSOR_ID_GYRO);

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

  // print the CSV header (ax0,ay0,az0,...,gx49,gy49,gz49,target)
  for (int i=0; i<NUM_SAMPLES; i++) {
    Serial.print("aX");
    Serial.print(i);
    Serial.print(",aY");
    Serial.print(i);
    Serial.print(",aZ");
    Serial.print(i);
    Serial.print(",gX");
    Serial.print(i);
    Serial.print(",gY");
    Serial.print(i);
    Serial.print(",gZ");
    Serial.print(i);
    Serial.print(",");
  }
  Serial.println("target");
}

void loop() {
  static int samplesRead = 0;
  static String target;

  // wait for user input (degree target value)
  while(Serial.available() == 0) {}
  target = Serial.readStringUntil('\n');
  samplesRead = 0;

  // read samples of the requested input orientation
  while (samplesRead < NUM_SAMPLES) {
    // read the acceleration and gyroscope data
    BHY2.update();

    samplesRead++;

    // print the sensor data in CSV format
    Serial.print(acc.x());
    Serial.print(',');
    Serial.print(acc.y());
    Serial.print(',');
    Serial.print(acc.z());
    Serial.print(',');
    Serial.print(gyro.x());
    Serial.print(',');
    Serial.print(gyro.y());
    Serial.print(',');
    Serial.print(gyro.z());
    Serial.print(',');

    // print target at the end of samples acquisition
    if (samplesRead == NUM_SAMPLES) {
      Serial.println(target);
    }
    
    delay(SAMPLE_TIME_MS);
  }
}
