
// PreFix
// ========== ========== ========== ========== 
// nRF24L01 Module
#define pin_CE  8
#define pin_CSN 10

// Potentiometer
#define pin_trans_t A0  // potentiometer

// Joystick
//#define pin_pr_sw 2
//#define pin_ty_sw 3
//#define pin_trans_t A4  // joystick
#define pin_trans_r A3
#define pin_trans_e A2
#define pin_trans_a A1

// Button
#define pin_btn_dji 4
#define pin_btn_diy 5

// Buzzer
#define pin_buzzer 9

// LED
#define pin_led_dji 7
#define pin_led_diy 6



// Libraries
// ========== ========== ========== ========== 
#include <Arduino.h>
#include <SimpleTimer.h>
#include <RF24.h>
#include <nRF24L01.h>
#include <SPI.h>



// Objects & Variables
// ========== ========== ========== ========== 
RF24 radio(pin_CE, pin_CSN); // CE, CSN
const byte address[6] = "01001";
SimpleTimer timer;
Data_to_be_sent sent_data;

int diy_toggle = 0;
int diy_last_pressed = 0;
int dji_toggle = 0;
int dji_last_pressed = 0;



// Struct, Functions
// ========== ========== ========== ========== 
struct Data_to_be_sent {
    byte T;
    byte R;
    byte E;
    byte A;
    byte M;
    byte X;
};

void BtnChecker(){
    if(digitalRead(pin_btn_dji) == 0){
        digitalWrite(pin_led_dji, !digitalRead(pin_led_dji));
    }
    if(digitalRead(pin_btn_diy) == 0){
        digitalWrite(pin_led_diy, !digitalRead(pin_led_diy));
    }
}



// Main Flow
// ========== ========== ========== ========== 
void setup() {
    // nRF tx setting
    radio.begin();
    radio.setAutoAck(false);
    radio.setDataRate(RF24_250KBPS);
    radio.openWritingPipe(address);
    radio.setPALevel(RF24_PA_MAX);
    
    // data packet initialize
    sent_data.T = 127;
    sent_data.R = 127;
    sent_data.E = 127;
    sent_data.A = 127;
    sent_data.M = 0;
    sent_data.X = 0;

    // pin Initializing
    pinMode(pin_btn_diy, INPUT_PULLUP);
    pinMode(pin_btn_dji, INPUT_PULLUP);
    pinMode(pin_buzzer, OUTPUT);
    pinMode(pin_led_diy, OUTPUT);
    pinMode(pin_led_dji, OUTPUT);

    // timer
    timer.setInterval(500, BtnChecker);
}

void loop() {
    // timer loop
    timer.run();
    
    // data refresh
    sent_data.T = map(analogRead(pin_trans_t), 0, 1023, 0, 255);
    sent_data.R = map(analogRead(pin_trans_r), 0, 1023, 0, 255);
    sent_data.E = map(analogRead(pin_trans_e), 0, 1023, 0, 255);
    sent_data.A = map(analogRead(pin_trans_a), 0, 1023, 0, 255);
    sent_data.M = digitalRead(pin_btn_dji);
    sent_data.X = digitalRead(pin_btn_diy);

    // signal transmit
    radio.write(&sent_data, sizeof(sent_data));
}
