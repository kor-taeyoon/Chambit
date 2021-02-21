
// PreFix
// ========== ========== ========== ========== 
// nRF24L01 Module
#define pin_T 4
#define pin_R 5
#define pin_E 6
#define pin_A 7
#define pin_M ?
#define pin_gps_rx 2
#define pin_gps_tx A0
#define pin_lidar_rx 3
#define pin_lidar_tx A1

#define pin_CE  8
#define pin_CSN 10



// Libraries
// ========== ========== ========== ========== 
#include <Arduino.h>
#include <RF24.h>
#include <nRF24L01.h>
#include <SPI.h>
#include <Servo.h>
#include <SoftwareSerial.h>



// Objects & Variables
// ========== ========== ========== ========== 
RF24 radio(pin_CE, pin_CSN); // CE, CSN
const byte address[6] = "01001";
Received_data received_data;
Servo channel_1;
Servo channel_2;
Servo channel_3;
Servo channel_4;
Servo channel_5;
SoftwareSerial GpsSerial(2, A3);
SoftwareSerial LidarSerial(3, A4);

int ch1_value = 0;
int ch2_value = 0;
int ch3_value = 0;
int ch4_value = 0;
int ch5_value = 0;
int ch6_value = 0;

unsigned long lastRecvTime = 0;



// Struct, Functions
// ========== ========== ========== ========== 
struct Received_data {
    byte T;
    byte R;
    byte E;
    byte A;
    byte M;
    byte X;
};

void reset_the_Data(){
    received_data.T = 0;
    received_data.R = 127;
    received_data.E = 127;
    received_data.A = 127;
    //received_data.M = 0;  // atti mode
}

void receive_the_data(){
    while(radio.available()){
        radio.read(&received_data, sizeof(received_data));
        lastRecvTime = millis();
    }
}



// Main Flow
// ========== ========== ========== ========== 
void setup() {
    // pwm initialize
    channel_1.attach(pin_T);
    channel_2.attach(pin_R);
    channel_3.attach(pin_E);
    channel_4.attach(pin_A);
    channel_5.attach(pin_M);
    
    // Seiral initialize
    Serial.begin(9600); // communicate with Rasp
    GpsSerial.begin(9600);
    LidarSerial.begin(115200);


    // nRF tx setting
    radio.begin();
    radio.setAutoAck(false);
    radio.setDataRate(RF24_250KBPS);
    radio.openReadingPipe(1, address);
    radio.setPALevel(RF24_PA_MAX);

    // nRF communication start
    radio.startListening();
}

void loop() {
    // data refresh
    receive_the_data();

    // rf connection test
    if((millis() - lastRecvTime) > 1000){
        reset_the_Data();
    }

    // signal processing
    ch1_value = map(received_data.T, 0, 255, 1000, 2000);
    ch2_value = map(received_data.R, 0, 255, 1000, 2000);
    ch3_value = map(received_data.E, 0, 255, 1000, 2000);
    ch4_value = map(received_data.A, 0, 255, 1000, 2000);
    ch5_value = map(received_data.M, 0,   1, 1000, 2000);

    // pwm generator
    channel_1.writeMicroseconds(ch1_value);
    channel_2.writeMicroseconds(ch2_value);
    channel_3.writeMicroseconds(ch3_value);
    channel_4.writeMicroseconds(ch4_value);
    channel_5.writeMicroseconds(ch5_value);
}
