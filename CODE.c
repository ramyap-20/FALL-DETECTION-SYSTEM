#include <Wire.h>
#include <MPU6050.h>

MPU6050 mpu;

int buzzer = PA5;

float ax, ay, az;
float totalAccel;

void setup() {

  Serial.begin(115200);
  Wire.begin();

  pinMode(buzzer, OUTPUT);

  Serial.println("Initializing MPU6050...");

  mpu.initialize();

  if (!mpu.testConnection()) {
    Serial.println("MPU6050 connection failed");
    while(1);
  }

  Serial.println("MPU6050 Ready");
}

void loop() {

  int16_t ax_raw, ay_raw, az_raw;

  mpu.getAcceleration(&ax_raw, &ay_raw, &az_raw);

  ax = ax_raw / 16384.0;
  ay = ay_raw / 16384.0;
  az = az_raw / 16384.0;

  totalAccel = sqrt(ax*ax + ay*ay + az*az);

  Serial.print("Accel: ");
  Serial.println(totalAccel);

  // Fall detection condition
  if(totalAccel > 2.5 || totalAccel < 0.5) {

    Serial.println("Fall Detected!");

    digitalWrite(buzzer, HIGH);
    delay(2000);

  } 
  else {

    digitalWrite(buzzer, LOW);

  }

  delay(200);
}