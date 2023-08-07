#ifndef MQTTData_H
#define MQTTData_H
#include <stdint.h>

/*Variables to store mqtt messages*/
uint8_t relayStatusMQTT[] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
uint8_t allRelayOnButton_data_mQTT = 0;
uint8_t allRelayOffButton_data_mQTT = 0;

/*MQTT payload length*/
unsigned int len = 0;

/*Variable to store delayTime in Minute*/
uint8_t deviceDelay = 1;

// Variable to store lux sensor value
float luxSensor0_data_mQTT = 0.0;
float luxSensor_testValue = 0.0;

// Lux Sensor threshold
float luxSensorThreshold = 80.0;

#endif