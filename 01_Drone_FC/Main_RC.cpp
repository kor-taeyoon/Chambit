
/* Pin Mapping
nRF24L01+
VCC  - 3.3v
GND  - GND
CE   - D8
CSN  - D10
SCK  - D13
MOSI - D11
MISO - D12

Throttle slide
VCC   - 5V
GND   - GND
INPUT - A0

pr Joystick
VCC  - 5v
GND  - GND
X    - 
Y    - 
sw   - 

ty Joystick
VCC  - 5v
GND  - GND
X    - A
Y    - A
sw   - 

Starter button
INPUT - D5

Stopper button
INPUT - D4

Buzzer
INPUT - D9
*/

#define pin_CE  8
#define pin_CSN 10

#define pin_slide_t A0

#define pin_pr_x A4
#define pin_pr_y A3
#define pin_pr_sw 2

#define pin_ty_x A2
#define pin_ty_y A1
#define pin_ty_sw 3

#define pin_btn_starter 5
#define pin_btn_stopper 4

#define pin_buzzer 9

#define pin_led_tx 6
#define pin_led_rx 7

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
SimpleTimer SignalRefresher;

// nRF variables
const byte address[6] = "00001";
char txCommand[7] = "";
char rxCommand[7] = "";

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

void RadioHandler(char rxCommand[]){
    // 만약 신호가 1초 이상 끊겼다면 
}

void RadioSignalTransmitter(){
    radio.write(&txCommand, sizeof(txCommand));
}

void RadioSignalCatcher(){
    if(radio.available()) {
        radio.read(&rxCommand, sizeof(rxCommand));
        RadioHandler(rxCommand);
        strcpy(rxCommand, "");
        // 마지막 명령 도착 시간 업데이트
    }
    // 만약 신호가 1초 이상 끊겼다면 부저 울리기 시작
}





// ========== ========== ========== ========== ========== ========== ========== ========== 
// ========== ========== ========== ========== ========== ========== ========== ========== 
// ========== ========== ========== ========== ========== ========== ========== ========== 





// Main Setup
// ========== ========== ========== ========== 
void setup() {
    // nRF setting
    radio.begin();
    radio.openWritingPipe(address);
    radio.setPALevel(RF24_PA_MIN);
    radio.stopListening();

    // pin Initializing
    pinMode(pin_pr_sw, INPUT_PULLUP);
    pinMode(pin_ty_sw, INPUT_PULLUP);
    pinMode(pin_btn_starter, INPUT_PULLUP);
    pinMode(pin_btn_stopper, INPUT_PULLUP);
    pinMode(pin_buzzer, OUTPUT);
    pinMode(pin_led_tx, OUTPUT);
    pinMode(pin_led_rx, OUTPUT);

    // Timer setting
    
}

// Main Loop
// ========== ========== ========== ========== 
void loop() {
    // timer loop
    SignalRefresher.run();

    // analog data refresh
    slide_throttle = map(analogRead(pin_slide_t), 0, 1023, 34, 125);
    //joy_throttle = map(analogRead(pin_ty_y), 0, 1023, 34, 125);
    //joy_yaw = map(analogRead(pin_ty_x), 0, 1023, 34, 125);
    joy_pitch = map(analogRead(pin_ty_y), 0, 1023, 34, 124);
    joy_roll = map(analogRead(pin_ty_x), 0, 1023, 34, 124);
    
    // button processing


}
