// Basic demo for accelerometer readings from Adafruit MPU6050

// ESP32 Guide: https://RandomNerdTutorials.com/esp32-mpu-6050-accelerometer-gyroscope-arduino/
// ESP8266 Guide: https://RandomNerdTutorials.com/esp8266-nodemcu-mpu-6050-accelerometer-gyroscope-arduino/
// Arduino Guide: https://RandomNerdTutorials.com/arduino-mpu-6050-accelerometer-gyroscope/

#include <Adafruit_MPU6050.h>
#include <Adafruit_Sensor.h>
Adafruit_MPU6050 mpu;

int LedVerde = D5;
int LedGiallo = D6;
int LedRosso = D7;
int val =0;



void setup(void) {
  Serial.begin(115200);
  while (!Serial)
    delay(10); // will pause Zero, Leonardo, etc until serial console opens

  Serial.println("Adafruit MPU6050 test!");

  // Try to initialize!
  if (!mpu.begin()) {
    Serial.println("Failed to find MPU6050 chip");
    while (1) {
      delay(10);
    }
  }
  Serial.println("MPU6050 Found!");
  
  mpu.setAccelerometerRange(MPU6050_RANGE_8_G);
  Serial.print("Accelerometer range set to: ");
  switch (mpu.getAccelerometerRange()) {
  case MPU6050_RANGE_2_G:
    Serial.println("+-2G");
    break;
  case MPU6050_RANGE_4_G:
    Serial.println("+-4G");
    break;
  case MPU6050_RANGE_8_G:
    Serial.println("+-8G");
    break;
  case MPU6050_RANGE_16_G:
    Serial.println("+-16G");
    break;
  }
  mpu.setGyroRange(MPU6050_RANGE_500_DEG);
  Serial.print("Gyro range set to: ");
  switch (mpu.getGyroRange()) {
  case MPU6050_RANGE_250_DEG:
    Serial.println("+- 250 deg/s");
    break;
  case MPU6050_RANGE_500_DEG:
    Serial.println("+- 500 deg/s");
    break;
  case MPU6050_RANGE_1000_DEG:
    Serial.println("+- 1000 deg/s");
    break;
  case MPU6050_RANGE_2000_DEG:
    Serial.println("+- 2000 deg/s");
    break;
  }

  mpu.setFilterBandwidth(MPU6050_BAND_5_HZ);
  Serial.print("Filter bandwidth set to: ");
  switch (mpu.getFilterBandwidth()) {
  case MPU6050_BAND_260_HZ:
    Serial.println("260 Hz");
    break;
  case MPU6050_BAND_184_HZ:
    Serial.println("184 Hz");
    break;
  case MPU6050_BAND_94_HZ:
    Serial.println("94 Hz");
    break;
  case MPU6050_BAND_44_HZ:
    Serial.println("44 Hz");
    break;
  case MPU6050_BAND_21_HZ:
    Serial.println("21 Hz");
    break;
  case MPU6050_BAND_10_HZ:
    Serial.println("10 Hz");
    break;
  case MPU6050_BAND_5_HZ:
    Serial.println("5 Hz");
    break;
}

  pinMode(LedVerde, OUTPUT);
  pinMode(LedGiallo, OUTPUT);
  pinMode(LedRosso, OUTPUT);
  digitalWrite(LedVerde, LOW);
  digitalWrite(LedGiallo, LOW);
  digitalWrite(LedRosso, LOW);
 

  Serial.println("");
  delay(100);


  digitalWrite(LedVerde, HIGH);
  digitalWrite(LedGiallo, HIGH);
  digitalWrite(LedRosso, HIGH);
   delay(2000);

  digitalWrite(LedVerde, LOW);
  digitalWrite(LedGiallo, LOW);
  digitalWrite(LedRosso, LOW);

}
void loop() {
  
  
  /* Get new sensor events with the readings */
  sensors_event_t a, g, temp;
  mpu.getEvent(&a, &g, &temp);
  
  /* Print out the values */
  Serial.print("Acceleration X: ");
  Serial.print(a.acceleration.x);
  Serial.print(", Y: ");
  Serial.print(a.acceleration.y);
  Serial.print(", Z: ");
  Serial.print(a.acceleration.z);
  Serial.println(" m/s^2");

  Serial.print("Rotation X: ");
  Serial.print(g.gyro.x);
  Serial.print(", Y: ");
  Serial.print(g.gyro.y);
  Serial.print(", Z: ");
  Serial.print(g.gyro.z);
  Serial.println(" rad/s");

  Serial.print("Temperature: ");
  Serial.print(temp.temperature);
  Serial.println(" degC");

  Serial.print("val: ");
  

  val = a.acceleration.x*a.acceleration.x + a.acceleration.y*a.acceleration.y;
  Serial.println(val);
  Serial.println("--------------------------------------------");


   if(val>30){
        Serial.println("VAL >30");
        digitalWrite(LedVerde, HIGH);
        digitalWrite(LedGiallo, HIGH);
        digitalWrite(LedRosso, HIGH);
   }else if( val > 20 ){ 
        Serial.println("VAL >20");
        digitalWrite(LedVerde, HIGH);
        digitalWrite(LedGiallo, HIGH);
        digitalWrite(LedRosso, LOW);
   }else if(val>0 ){
        Serial.println("VAL >0");
        digitalWrite(LedVerde, HIGH);
        digitalWrite(LedGiallo, LOW);
        digitalWrite(LedRosso, LOW);
   }else{
        Serial.println("VAL < 0");
        digitalWrite(LedVerde, LOW);
        digitalWrite(LedGiallo, LOW);
        digitalWrite(LedRosso, LOW);
   }
   
  delay(500);
}
