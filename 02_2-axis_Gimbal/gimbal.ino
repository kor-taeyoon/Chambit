
#define focuser_step 0
#define focuser_dir 0
#define focuser_m1 0
#define focuser_m2 0
#define focuser_m3 0

#define filterWheel_step 0
#define filterWheel_dir 0
#define filterWheel_en 0

#define bluetooth_rx 8
#define bluetooth_tx 7

#include <SoftwareSerial.h>
#include <AccelStepper.h>
#include <SimpleTimer.h>

AccelStepper focuser(AccelStepper::DRIVER, focuser_step, focuser_dir);
AccelStepper filterWheel(AccelStepper::DRIVER, filterWheel_step, filterWheel_dir);
SimpleTimer timer;
SoftwareSerial bluetooth(bluetooth_rx, bluetooth_tx);

String command = "";
int currentuStep = 0;

void setup() {
    Serial.begin(9600);
    bluetooth.begin(9600);
    
    focuser.setMaxSpeed(1000);
    focuser.setAcceleration(4000);
    focuser.setCurrentPosition(0);
    //focuser.setPinsInverted(true, false, false);

    filterWheel.setMaxSpeed(1000);
    filterWheel.setAcceleration(4000);
    filterWheel.setCurrentPosition(0);
    //filterWheel.setPinsInverted(true, false, false);

    digitalWrite(filterWheel_en, LOW);
    uStepConverter('4');

    timer.setInterval(100, CorRenew);
    
}

void loop() {
    focuser.run();
    filterWheel.run();
    timer.run();
    if(bluetooth.available()){
        command = bluetooth.readStringUntil('#');
        BlueHandler();
        command = "";
    }
}
