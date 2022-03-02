
#include <Arduino.h>

#define PIN_A 18
#define PIN_B 19
#define PIN_EN 21
#define PIN_POT 13

// setting PWM properties
#define PWM_CHANNEL 0
#define PWM_FREQ 5000
#define PWM_RES 12

void setup() {
    // Set software serial baud to 115200;

    Serial.begin(115200);

    pinMode(PIN_A, OUTPUT);
    pinMode(PIN_B, OUTPUT);
    pinMode(PIN_EN, OUTPUT);

    // configure LED PWM functionalitites
    ledcSetup(PWM_CHANNEL, PWM_FREQ, PWM_RES);

    // attach the channel to the GPIO to be controlled
    ledcAttachPin(PIN_EN, PWM_CHANNEL);
    ledcWrite(PWM_CHANNEL, 0);


    digitalWrite(PIN_A, HIGH);
    digitalWrite(PIN_B, LOW);
}

void loop() {

    int potValue = analogRead(PIN_POT) - 2047;
    Serial.printf("Reading: %d\n", potValue);

    if(potValue > 0){
        digitalWrite(PIN_A, HIGH);
        digitalWrite(PIN_B, LOW);
        ledcWrite(PWM_CHANNEL, 2*potValue);
    }else{
        digitalWrite(PIN_A, LOW);
        digitalWrite(PIN_B, HIGH);
        ledcWrite(PWM_CHANNEL, -2*potValue);
    }

    delay(50);
}
