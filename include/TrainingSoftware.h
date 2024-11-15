#ifndef TRAINING_SOFTWARE_H
#define TRAINING_SOFTWARE_H

#include "PinAssignments.h"

#include "RoveCommExtension.h"
#include <RoveComm.h>

// RoveComm
RoveCommEthernet RoveComm;

// State Variables
bool ledIsOn = false;
int16_t temperatures[2] = {0, 0};

// Telemetry
#define TELEMETRY_PERIOD 2000
int timestamp;
void telemetry();

#endif // TRAINING_SOFTWARE_H
