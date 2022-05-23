#include <Arduino_LSM9DS1.h>

float ax, ay, az;
float gx, gy, gz;
float mx, my, mz;

#define PRINT_SPEED 300 // 300 ms between prints
static unsigned long lastPrint = 0; // Keep track of print time

void setup() {
  Serial.begin(115200);
  while (!Serial);
  Serial.println("Started");

  if (!IMU.begin()) {
    Serial.println("Failed to initialize IMU!");
    while (1);
  }

  Serial.println("Collecting gyro data, hold still");
  delay(3000);
  // get gyro offset
  float gxa = 0, gya = 0, gza = 0;
  for (int i = 0; i < 700; i++) {
    if ( IMU.gyroscopeAvailable() )
    {
      IMU.readGyroscope(gx, gy, gz);
      gxa += gx;
      gya += gy;
      gza += gz;
    }
  }
  Serial.println(F("gyro offsets"));
  Serial.print(gxa / 700);
  Serial.print(", ");
  Serial.print(gya / 700);
  Serial.print(", ");
  Serial.println(gza / 700);
  Serial.println();
  
  Serial.println(F("rotate slowly and carefully in 3D"));
  delay(3000);
  Serial.println("starting");


}

void loop(){
  static int n = 0; //count values transmitted
  // Update the sensor values whenever new data is available

  if ( IMU.accelerationAvailable() ) 
  {
    // To read from the accelerometer, first call the
    // readAccel() function. When it exits, it'll update the
    // ax, ay, and az variables with the most current data.
    IMU.readAcceleration(ax,ay,az);
  }
  if ( IMU.magneticFieldAvailable() )
  {
    IMU.readMagneticField(mx,my,mz);
  }

  if (millis() - lastPrint > PRINT_SPEED)
  {
    Serial.print(ax);
    Serial.print(", ");
    Serial.print(ay);
    Serial.print(", ");
    Serial.print(az);
    Serial.print(", ");
    Serial.print(mx);
    Serial.print(", ");
    Serial.print(my);
    Serial.print(", ");
    Serial.println(mz);
    if (n++ > 299) {
      Serial.println("Done.");
      while (1); //hang here
    }
    lastPrint = millis(); // Update lastPrint time
  }
}