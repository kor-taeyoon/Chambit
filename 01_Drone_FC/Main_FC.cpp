
// Pin Mapping & PreFix
// ========== ========== ========== ========== ========== ========== ========== ========== 
/*
nRF24L01+
VCC  - 3.3v
GND  - GND
CE   - D8
CSN  - D10
SCK  - D13
MOSI - D11
MISO - 12

MPU9250/6500
VCC  - 3.3v
GND  - GND
SCL  - D15/SCL
SDA  - D14/SDA
INT  - D2

Lidar
VCC
GND
RX
TX
*/
#define INTERRUPT_PIN 2  // use pin 2 on Arduino Uno & most boards





// Libraries
// ========== ========== ========== ========== ========== ========== ========== ========== 
#include <Arduino.h>
#include "I2Cdev.h"
#include "MPU6050_6Axis_MotionApps20.h"
#include "Wire.h"

#include <RF24.h>
#include <nRF24L01.h>
#include <SPI.h>





// Objects
// ========== ========== ========== ========== ========== ========== ========== ========== 
MPU6050 mpu;
RF24 radio(8, 10);





// variables
// ========== ========== ========== ========== ========== ========== ========== ========== 
// MPU control/status vars
uint8_t mpuIntStatus;   // holds actual interrupt status byte from MPU
uint8_t devStatus;      // return status after each device operation (0 = success, !0 = error)
uint16_t packetSize;    // expected DMP packet size (default is 42 bytes)
uint16_t fifoCount;     // count of all bytes currently in FIFO
uint8_t fifoBuffer[64]; // FIFO storage buffer

// orientation/motion vars
Quaternion q;           // [w, x, y, z]         quaternion container
VectorInt16 aa;         // [x, y, z]            accel sensor measurements
VectorInt16 aaReal;     // [x, y, z]            gravity-free accel sensor measurements
VectorInt16 aaWorld;    // [x, y, z]            world-frame accel sensor measurements
VectorFloat gravity;    // [x, y, z]            gravity vector
float euler[3];         // [psi, theta, phi]    Euler angle container
float ypr[3];           // [yaw, pitch, roll]   yaw/pitch/roll container and gravity vector
volatile bool mpuInterrupt = false;     // detecting Interrupt pin's HIGH edge

// packet structure for InvenSense teapot demo
uint8_t teapotPacket[14] = { '$', 0x02, 0,0, 0,0, 0,0, 0,0, 0x00, 0x00, '\r', '\n' };


const byte address[6] = "00001";



// functions
// ========== ========== ========== ========== ========== ========== ========== ========== 

void dmpDataReady() {
    mpuInterrupt = true;
}





// Main Algorithms
// ========== ========== ========== ========== ========== ========== ========== ========== 
// ========== ========== ========== ========== ========== ========== ========== ========== 
// ========== ========== ========== ========== ========== ========== ========== ========== 
// ========== ========== ========== ========== ========== ========== ========== ========== 
// ========== ========== ========== ========== ========== ========== ========== ========== 





// Main Setup
// ========== ========== ========== ========== ========== ========== ========== ========== 
void setup() {
    
    Wire.begin();
    Wire.setClock(400000); // 400kHz I2C
    Serial.begin(115200);
    radio.begin();
    radio.openReadingPipe(0, address);
    radio.setPALevel(RF24_PA_MAX);
    radio.startListening();



    mpu.initialize();       // initialize device
    mpu.testConnection();    // verify connection
    delay(3000);    // wait for ready
    
    while (Serial.available() && Serial.read());    // empty buffer

    // load and configure the DMP
    devStatus = mpu.dmpInitialize();

    // make sure it worked (returns 0 if so)
    if (devStatus == 0) {
        // supply your own gyro offsets here, scaled for min sensitivity
        mpu.setXGyroOffset(220);
        mpu.setYGyroOffset(76);
        mpu.setZGyroOffset(-85);
        mpu.setZAccelOffset(1788); // 1688 factory default for my test chip
        
        // Calibration Time: generate offsets and calibrate our MPU6050
        mpu.CalibrateAccel(6);
        mpu.CalibrateGyro(6);
        mpu.PrintActiveOffsets();
        mpu.setDMPEnabled(true);

        // enable Arduino interrupt detection
        Serial.print(digitalPinToInterrupt(INTERRUPT_PIN));
        attachInterrupt(digitalPinToInterrupt(INTERRUPT_PIN), dmpDataReady, RISING);

        // get expected DMP packet size for later comparison
        packetSize = mpu.dmpGetFIFOPacketSize();
    }
    else {  // ERROR!
        // 1 = initial memory load failed
        // 2 = DMP configuration updates failed
        Serial.print(F("DMP Initialization failed\tcode "));
        Serial.println(devStatus);
        while(1){
            Serial.println("MCU Sleeping..");
            // Buzzer PPIP PPIP PPIP !!!
            delay(1000);
        }
    }

    // initialize pins
    pinMode(INTERRUPT_PIN, INPUT);
}


// Main Loop
// ========== ========== ========== ========== ========== ========== ========== ========== 
void loop() {
    // wait for MPU interrupt or extra packet(s) available
    while (!mpuInterrupt && fifoCount < packetSize) {
        if (mpuInterrupt && fifoCount < packetSize) {
            // try to get out of the infinite loop 
            fifoCount = mpu.getFIFOCount();
        }
    }

    // reset interrupt flag and get INT_STATUS byte
    mpuInterrupt = false;
    mpuIntStatus = mpu.getIntStatus();

    // get current FIFO count
    fifoCount = mpu.getFIFOCount();
	if(fifoCount >= packetSize){
        // check overflow
        if ((mpuIntStatus & (0x01 << MPU6050_INTERRUPT_FIFO_OFLOW_BIT)) || fifoCount >= 1024) {
            Serial.println(F("FIFO overflow!"));
            mpu.resetFIFO(); // reset so we can continue cleanly
            return;
        }
        // normal state
        else if (mpuIntStatus & (0x01 << MPU6050_INTERRUPT_DMP_INT_BIT)) {
            while(fifoCount >= packetSize){
                mpu.getFIFOBytes(fifoBuffer, packetSize);
                fifoCount -= packetSize;
            }
            mpu.dmpGetQuaternion(&q, fifoBuffer);
            mpu.dmpGetGravity(&gravity, &q);
            mpu.dmpGetYawPitchRoll(ypr, &q, &gravity);
            /*
            Serial.print("ypr\t");
            Serial.print(ypr[0] * 180/PI);      // yaw
            Serial.print("\t");
            Serial.print(ypr[1] * 180/PI);      // pitch
            Serial.print("\t");
            Serial.println(ypr[2] * 180/PI);    // roll
            */

        }
    }
}
