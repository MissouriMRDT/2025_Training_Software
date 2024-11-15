#include <Arduino.h>

#include "TrainingSoftware.h"

void setup() {
    Serial.begin(115200);
    delay(10);

    pinMode(SW_1, INPUT_PULLDOWN);
    pinMode(SW_2, INPUT_PULLUP);

    pinMode(LED, OUTPUT);

    pinMode(TEMP1, INPUT);
    pinMode(TEMP2, INPUT);

    Serial.println("Initializing RoveComm");
    RoveComm.begin(RC_TRAININGSOFTWARE_IPADDRESS);
    Serial.println("Finished.");

    timestamp = millis();
}

RoveCommPacket packet;
void loop() {
    for (int i = 0; i < 2; i++) {
        temperatures[i] = analogRead(i == 0 ? TEMP1 : TEMP2);
    }

    RoveComm.read(packet);
    switch (packet.dataId) {
    case RC_TRAININGSOFTWARE_REQUESTTEMP_DATA_ID: {
        RoveComm.write(RC_TRAININGSOFTWARE_REQUESTTEMP_DATA_ID, 2, temperatures);
    }
    }
    if (digitalRead(SW_2)) {
        RoveComm.write(RC_TRAININGSOFTWARE_REQUESTTEMP_DATA_ID, 2, temperatures);
        delay(1000);
    }

    // Toggle LED if SW_1 is pressed
    if (digitalRead(SW_1)) {
        if (ledIsOn) {
            ledIsOn = false;
            digitalWrite(LED, LOW);
        } else {
            ledIsOn = true;
            digitalWrite(LED, HIGH);
        }
        delay(1000);
    }

    if (millis() - timestamp >= TELEMETRY_PERIOD) {
        telemetry();
        timestamp = millis();
    }
}

void telemetry() { RoveComm.write(RC_TRAININGSOFTWARE_REQUESTTEMP_DATA_ID, 2, temperatures); }
