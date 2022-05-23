# Arduino-Nano-33-BLE-AHRS-Mahony

This is AHRS implementation for Arduino Nano 33 BLE, based off of [https://github.com/jremington/LSM9DS1-AHRS](https://github.com/jremington/LSM9DS1-AHRS). Added Hatire support for use with OpenTrack Software for headtracking in simulator games. Currently does not support Bluetooth serial communication.

## Usage
Arduino sensors must be calibrated before use.

### Calibration
To generate data for calibration use file generate_calibration_data.ino, and copy data from Arduino serial to separate file. First three columns in output data represent accelerometer (x,y,z), second three columns represent magnetometer (x,y,z). Separate the accelerometer data and magnetometer data to 2 separate .csv files, which will be used as input for calibration program. Examples of .csv input files are in /Calibration/Magneto.

Calibrate data using magneto.exe. It will output B and Ainv matrices which are used for calibration in ahrs.ino files. 

### Change calibration data in ahrs.ino and ahrs_hatire.ino with your own calibration data
```c
 //Gyro scale 245 dps convert to radians/sec and offsets
float Gscale = (M_PI / 180.0) * 0.00875; //245 dps scale sensitivity = 8.75 mdps/LSB
float G_offset[3] = {0, 0, 0.05};

//Accel scale 1.0 to normalize
float A_B[3]
{ 0.0049 , -0.04 ,-0.002};

float A_Ainv[3][3]
{ {  1.04036, -0.01699,  0.01123},
  { -0.01699,  0.96608,  0.01616},
  {  0.01123,  0.01616,  0.97912}
};

//Mag scale 51.0 to normalize
float M_B[3]
{  15.97,   28.38,    2.82};

float M_Ainv[3][3]
{ {  1.38541,  0.02445,  0.01669},
  {  0.02445,  1.40471, -0.00056},
  {  0.01669, -0.00056,  1.46882}
};

// local magnetic declination in degrees
float declination = +4.44;

```
