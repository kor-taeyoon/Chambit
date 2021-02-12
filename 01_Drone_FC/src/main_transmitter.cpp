
// PreFix
// ========== ========== ========== ========== 
// nRF24L01 Module
#define pin_CE  8
#define pin_CSN 10

// Slide Potentiometer
#define pin_slide_t A0

// Joystick
#define pin_pr_x A3
#define pin_pr_y A4
#define pin_pr_sw 2
#define pin_ty_x A1
#define pin_ty_y A2
#define pin_ty_sw 3

// Button
#define pin_btn_starter 5
#define pin_btn_stopper 4

// Buzzer
#define pin_buzzer 9

// LED
#define pin_led_tx 6
#define pin_led_rx 7



// Libraries
// ========== ========== ========== ========== 
#include <Arduino.h>
#include <SimpleTimer.h>
#include <RF24.h>
#include <nRF24L01.h>
#include <SPI.h>

struct Data_to_be_sent {
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
Data_to_be_sent sent_data;

void buzzer_bbip(){
    digitalWrite(pin_buzzer, !digitalRead(pin_buzzer));
}

void Led_tx_blink(){
    digitalWrite(pin_led_tx, !digitalRead(pin_led_tx));
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
    
    sent_data.T = 127;
    sent_data.R = 127;
    sent_data.E = 127;
    sent_data.A = 127;

    // pin Initializing
    pinMode(pin_pr_sw, INPUT_PULLUP);
    pinMode(pin_ty_sw, INPUT_PULLUP);
    pinMode(pin_btn_starter, INPUT_PULLUP);
    pinMode(pin_btn_stopper, INPUT_PULLUP);
    pinMode(pin_buzzer, OUTPUT);
    pinMode(pin_led_tx, OUTPUT);
    pinMode(pin_led_rx, OUTPUT);
}

void loop() {
    // timer loop
    bipper.run();
    blinker.run();
    
    // data refresh
    sent_data.T = map(analogRead(pin_slide_t), 0, 1023, 0, 255);
    sent_data.R = map(analogRead(pin_ty_x),    0, 1023, 0, 255);
    sent_data.E = map(analogRead(pin_pr_y),    0, 1023, 0, 255);
    sent_data.A = map(analogRead(pin_pr_x),    0, 1023, 0, 255);

    // signal transmit
    radio.write(&sent_data, sizeof(sent_data));
}
