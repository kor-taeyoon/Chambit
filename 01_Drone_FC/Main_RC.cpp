
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
GND   - 
INPUT - 

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

Start button
INPUT - 

Emergency button
INPUT - 

Buzzer
INPUT - 
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

#define pin_btn_starter 4
#define pin_btn_stopper 5

#define pin_buzzer 9

#define pin_led_tx 6
#define pin_led_rx 7

#include <Arduino.h>
#include <SimpleTimer.h>
#include <string.h>

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
const byte address[6] = "00001";
char txCommand[7] = "";
char rxCommand[7] = "";




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
    timer.run();
    
    
}
