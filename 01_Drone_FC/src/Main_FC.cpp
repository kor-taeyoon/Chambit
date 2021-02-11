
// PreFix
// ========== ========== ========== ========== 
//#define DEBUG

// Buzzer
//#define pin_buzzer 0

// MPU-9250
#define pin_mpu_INT 2

// nRF24L01+
#define pin_nRF_CE 7
#define pin_nRF_CSN 8

// GPS serial
#define pin_gps_RX 9
#define pin_gps_TX 10

// Lidar Serial



// Libraries
// ========== ========== ========== ========== 
#include <Arduino.h>
#include <SimpleTimer.h>
#include <string.h>
#include <SoftwareSerial.h>

#include "I2Cdev.h"
#include "MPU6050_6Axis_MotionApps20.h"
#include "Wire.h"

#include <RF24.h>
#include <nRF24L01.h>
#include <SPI.h>

#include <TinyGPS++.h>



// ========== ========== ========== ========== ========== ========== ========== ========== 
// ========== ========== ========== ========== ========== ========== ========== ========== 
// ========== ========== ========== ========== ========== ========== ========== ========== 



// Objects
// ========== ========== ========== ========== 
MPU6050 mpu;
RF24 radio(pin_nRF_CE, pin_nRF_CSN);
SimpleTimer timer;
SoftwareSerial gpsSerial(pin_gps_RX, pin_gps_TX);
TinyGPSPlus gps;


// variables
// ========== ========== ========== ========== 
// Most Significant variables
int motorValidated = 0;
float target_throttle = 0;
float target_yaw = 0;
float target_pitch = 0;
float target_roll = 0;

float current_throttle = 0;
float current_yaw = 0;
float current_pitch = 0;
float current_roll = 0;

// MPU control/status vars
uint8_t mpuIntStatus;   // holds actual interrupt status byte from MPU
uint8_t devStatus;      // return status after each device operation (0 = success, !0 = error)
uint16_t packetSize;    // expected DMP packet size (default is 42 bytes)
uint16_t fifoCount;     // count of all bytes currently in FIFO
uint8_t fifoBuffer[64]; // FIFO storage buffer
Quaternion q;           // [w, x, y, z]         quaternion container
VectorInt16 aa;         // [x, y, z]            accel sensor measurements
VectorInt16 aaReal;     // [x, y, z]            gravity-free accel sensor measurements
VectorInt16 aaWorld;    // [x, y, z]            world-frame accel sensor measurements
VectorFloat gravity;    // [x, y, z]            gravity vector
uint8_t teapotPacket[14] = { '$', 0x02, 0,0, 0,0, 0,0, 0,0, 0x00, 0x00, '\r', '\n' };
float euler[3];         // [psi, theta, phi]    Euler angle container
float ypr[3];           // [yaw, pitch, roll]   yaw/pitch/roll container and gravity vector
volatile bool mpuInterrupt = false;     // detecting Interrupt pin's HIGH edge

// Radio variables
const byte address[6] = "01001";
char rxCommand[7] = "";


// GPS variables
float current_lat;
float current_lng;
long gps_last_updated = 0;
int gps_load_divide = 0;

// Lidar variables


// Buzzer variables




// ========== ========== ========== ========== ========== ========== ========== ========== 
// ========== ========== ========== ========== ========== ========== ========== ========== 
// ========== ========== ========== ========== ========== ========== ========== ========== 



// functions
// ========== ========== ========== ========== 
void buzzer_bbip(){
    //digitalWrite(pin_buzzer, !digitalRead(pin_buzzer));
}

void dmpDataReady() {
    mpuInterrupt = true;
}



void SerialHandler(String command){
    // if gps 
}

void RadioHandler(){
    // 들어온 신호에 이상이 있는 것
    if(rxCommand[0] != '!' || rxCommand[5] != '~'){
        timer.setTimer(100, buzzer_bbip, 4);
        strcpy(rxCommand, "");
    }
    else{
        //starter
        if(!strcmp(rxCommand, "!!!!!~")){
            motorValidated = 1;
        }
        // stopper
        else if(!strcmp(rxCommand, "!~~~~~")){
            motorValidated = 0;
        }
        else{
            target_throttle = int(rxCommand[1]) - 25;
            target_yaw = int(rxCommand[2]) - 48;
            target_pitch = int(rxCommand[3]) - 79;
            target_roll = int(rxCommand[4]) - 79;
        }

    }
}

void RadioSignalReceiver(){
    if(radio.available()) {
        radio.read(&rxCommand, sizeof(rxCommand));
        RadioHandler();
        strcpy(rxCommand, "");
        // 마지막 명령 도착 시간 업데이트
    }
    // 만약 신호가 1초 이상 끊겼다면 부저 울리기 시작
}


void GpsLocRefresher(){
    if(gps.location.isValid()){
        current_lat = gps.location.lat();
        current_lng = gps.location.lng();
        
        Serial.print(current_lat, 6);
        Serial.print("\t");
        
        Serial.print(current_lng, 6);
        Serial.print("\t");

        Serial.print(current_yaw, 6);
        Serial.print("\t");

        //Serial.print(current_pitch, 6);
        //Serial.print("\t");

        //Serial.print(current_roll, 6);
        //Serial.print("\t");

        //Serial.print(target_yaw, 6);
        //Serial.print("\t");

        //Serial.print(target_pitch, 6);
        //Serial.print("\t");

        //Serial.print(target_roll, 6);
        //Serial.print("\t");

        

        
        Serial.println();
    }
    else{
        Serial.println("GPS not connected!");
    }
}

void debugger(){
    Serial.print(millis()/1000);
    Serial.print("\t");

    Serial.print(int(target_throttle));
    Serial.print("\t");

    Serial.print(int(target_pitch));
    Serial.print("\t");

    Serial.print(int(target_roll));
    Serial.print("\t");

    Serial.println();
}


// ========== ========== ========== ========== ========== ========== ========== ========== 
// ========== ========== ========== ========== ========== ========== ========== ========== 
// ========== ========== ========== ========== ========== ========== ========== ========== 



// Main Setup
// ========== ========== ========== ========== 
void setup() {
    Wire.begin();
    Wire.setClock(400000);      // 400kHz I2C
    Serial.begin(115200);       // USB UART
    gpsSerial.begin(9600);

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
        attachInterrupt(digitalPinToInterrupt(pin_mpu_INT), dmpDataReady, RISING);

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
    pinMode(pin_mpu_INT, INPUT);

    // timer setup
    //timer.setInterval(25, RadioSignalReceiver);
    //timer.setInterval(500, GpsLocRefresher);
    //timer.setInterval(500, debugger);
}


// Main Loop
// ========== ========== ========== ========== 
void loop() {
    // wait for MPU interrupt or extra packet(s) available
    while (!mpuInterrupt && fifoCount < packetSize) {
        if (mpuInterrupt && fifoCount < packetSize) {
            // try to get out of the infinite loop 
            fifoCount = mpu.getFIFOCount();
        }
        
        debugger();
        // substantial loop
        // ========== ========== ========== ========== 
        // timer loop
        //timer.run();
        
        if(gpsSerial.available()){
            gps.encode(gpsSerial.read());
        }
        if(gps.location.isValid() || millis() - gps_last_updated >=500){
            if(gps_load_divide == 0){
                current_lat = gps.location.lat();
                gps_load_divide = 1;
            }
            else{
                current_lng = gps.location.lng();
                gps_load_divide = 0;
            }
            gps_last_updated = millis();
        }
        
        if(radio.available()) {
            radio.read(&rxCommand, sizeof(rxCommand));
            RadioHandler();
            strcpy(rxCommand, "");
            // 마지막 명령 도착 시간 업데이트
        }

        // USB Serial data fresher
        //if(Serial.available()){
        //    String command = Serial.readStringUntil('#');
        //    SerialHandler(command);
        //}
        
        
        // ========== ========== ========== ========== 
    }

    // reset interrupt flag and get INT_STATUS byte
    mpuInterrupt = false;
    mpuIntStatus = mpu.getIntStatus();

    // get current FIFO count
    fifoCount = mpu.getFIFOCount();
	if(fifoCount >= packetSize){
        // check overflow
        if ((mpuIntStatus & (0x01 << MPU6050_INTERRUPT_FIFO_OFLOW_BIT)) || fifoCount >= 1024) {
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
            current_yaw = ypr[0] * 180/PI;
            current_pitch = ypr[1] * 180/PI;
            current_roll = ypr[2] * 180/PI;
        }
    }

}
