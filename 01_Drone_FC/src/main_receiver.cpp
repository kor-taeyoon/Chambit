
// can be pwm -> 
// using -> 8, 10, 11, 12, 13
// PreFix
// ========== ========== ========== ========== 
// nRF24L01 Module
#define pin_T 2
#define pin_R 3
#define pin_E 4
#define pin_A 5

#define pin_CE  8
#define pin_CSN 10



// Libraries
// ========== ========== ========== ========== 
#include <Arduino.h>
#include <SimpleTimer.h>
#include <RF24.h>
#include <nRF24L01.h>
#include <SPI.h>
#include <Servo.h>

struct Received_data {
    byte T;
    byte R;
    byte E;
    byte A;
};



// Objects & Variables
// ========== ========== ========== ========== 
RF24 radio(pin_CE, pin_CSN); // CE, CSN
const byte address[6] = "01001";
SimpleTimer bipper;
SimpleTimer blinker;
Received_data received_data;
Servo channel_1;
Servo channel_2;
Servo channel_3;
Servo channel_4;

int ch1_value = 0;
int ch2_value = 0;
int ch3_value = 0;
int ch4_value = 0;

unsigned long lastRecvTime = 0;

void reset_the_Data(){
    received_data.T = 0;
    received_data.R = 127;
    received_data.E = 127;
    received_data.A = 127;
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
    channel_1.attach(pin_T);
    channel_2.attach(pin_R);
    channel_3.attach(pin_E);
    channel_4.attach(pin_A);
    
    // nRF tx setting
    radio.begin();
    radio.setAutoAck(false);
    radio.setDataRate(RF24_250KBPS);
    radio.openReadingPipe(1, address);
    radio.setPALevel(RF24_PA_MAX);

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
    
    channel_1.writeMicroseconds(ch1_value);
    channel_2.writeMicroseconds(ch2_value);
    channel_3.writeMicroseconds(ch3_value);
    channel_4.writeMicroseconds(ch4_value);
}
