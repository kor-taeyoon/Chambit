
// PreFix
// ========== ========== ========== ========== 
// nRF24L01 Module
#define pin_CE  8
#define pin_CSN 10

// Slide Potentiometer
#define pin_slide_t A0

// Joystick
#define pin_pr_x A4
#define pin_pr_y A3
#define pin_pr_sw 2
#define pin_ty_x A2
#define pin_ty_y A1
#define pin_ty_sw 3

// Button
#define pin_btn_starter 5
#define pin_btn_stopper 4

// Buzzer
#define pin_buzzer 9

// LED
#define pin_led_tx 6
#define pin_led_rx 7



// Linking
// ========== ========== ========== ========== 
#include <Arduino.h>
#include <SimpleTimer.h>
#include <string.h>
#include <math.h>

#include <RF24.h>
#include <SPI.h>
#include <nRF24L01.h>



// ========== ========== ========== ========== ========== ========== ========== ========== 
// ========== ========== ========== ========== ========== ========== ========== ========== 
// ========== ========== ========== ========== ========== ========== ========== ========== 



// Global Objects & Variables
// ========== ========== ========== ========== 
// objects
RF24 radio(pin_CE, pin_CSN); // CE, CSN
SimpleTimer timer;

// nRF variables
const byte address[6] = "01001";
char rxCommand[7] = "";
char txCommand[7] = "";

// Joystick variables
volatile unsigned joy_throttle = 0;
volatile int joy_yaw = 0;
volatile int joy_pitch = 0;
volatile int joy_roll = 0;

// Potentiometer variables
volatile unsigned slide_throttle = 0;

// Button variables
unsigned starter_last_pressed = 0;
unsigned stopper_last_pressed = 0;



// ========== ========== ========== ========== ========== ========== ========== ========== 
// ========== ========== ========== ========== ========== ========== ========== ========== 
// ========== ========== ========== ========== ========== ========== ========== ========== 



// Functions
// ========== ========== ========== ========== 
void buzzer_bbip(){
    digitalWrite(pin_buzzer, !digitalRead(pin_buzzer));
}

void Led_tx_blink(){
    digitalWrite(pin_led_tx, !digitalRead(pin_led_tx));
}

void RadioSignalTransmitter(){      // 만들어진 전역변수 command를 전송.
    radio.write(&txCommand, sizeof(txCommand));
    timer.setTimer(20, Led_tx_blink, 2);
}

void PotentioRefresher(){
    // 아날로그 값 획득, 매핑, 업데이트
    txCommand[1] = slide_throttle = map(analogRead(pin_slide_t), 0, 1023, 34, 125);
    //joy_throttle = map(analogRead(pin_ty_y), 0, 1023, 34, 125);
    txCommand[2] = joy_yaw = map(analogRead(pin_ty_x), 0, 1023, 34, 125);
    txCommand[3] = joy_pitch = map(analogRead(pin_ty_y), 0, 1023, 34, 124);
    txCommand[4] = joy_roll = map(analogRead(pin_ty_x), 0, 1023, 34, 124);
}

void ButtonChecker(){
    // Starter
    if((digitalRead(pin_btn_starter) == 0) && (millis() - starter_last_pressed > 800)){
        if(slide_throttle == 34){
            strcpy(txCommand, "!!!!!~");
            radio.write(&txCommand, sizeof(txCommand));
            starter_last_pressed = millis();
            timer.setTimer(20, Led_tx_blink, 2);
            timer.setTimer(100, buzzer_bbip, 4);
        }
        else{
            timer.setTimer(100, buzzer_bbip, 8);
        }
        
        
    }

    // Stopper
    if((digitalRead(pin_btn_stopper) == 0) && (millis() - stopper_last_pressed > 1200)){
        strcpy(txCommand, "!~~~~~");
        radio.write(&txCommand, sizeof(txCommand));
        stopper_last_pressed = millis();
        timer.setTimer(20, Led_tx_blink, 2);
        timer.setTimer(100, buzzer_bbip, 6);
    }
}



// ========== ========== ========== ========== ========== ========== ========== ========== 
// ========== ========== ========== ========== ========== ========== ========== ========== 
// ========== ========== ========== ========== ========== ========== ========== ========== 



// Main Setup
// ========== ========== ========== ========== 
void setup() {
    // nRF tx setting
    radio.begin();
    radio.openWritingPipe(address);
    radio.setPALevel(RF24_PA_MAX);
    radio.stopListening();

    // pin Initializing
    pinMode(pin_pr_sw, INPUT_PULLUP);
    pinMode(pin_ty_sw, INPUT_PULLUP);
    pinMode(pin_btn_starter, INPUT_PULLUP);
    pinMode(pin_btn_stopper, INPUT_PULLUP);
    pinMode(pin_buzzer, OUTPUT);
    pinMode(pin_led_tx, OUTPUT);
    pinMode(pin_led_rx, OUTPUT);

    // variable initializing
    txCommand[0] = 33;      // !
    txCommand[5] = 126;     // ~

    // Timer setting
    timer.setInterval(100, RadioSignalTransmitter);
}

// Main Loop
// ========== ========== ========== ========== 
void loop() {
    // timer loop
    timer.run();

    // Data refresh
    PotentioRefresher();
    ButtonChecker();
}
