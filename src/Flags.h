#ifndef FLAGS_H
#define FLAGS_H
#include <stdint.h>

/*Global flags for MQTT message on All topics*/
bool relayStatusMQTTFlag[] = {false, false, false, false, false, false, false, false, false,
                              false, false, false, false, false, false, false};

/*Global flags for Individual Device Automation*/
bool patternFlag[] = {false, false, false, false, false, false, false, false, false,
                      false, false, false, false, false, false, false};

/*Global flags to publish MQTT messages outside Callback function*/
bool allRelayOn = false;
bool allRelayOnButton = false;
bool allRelayOff = false;
bool allRelayOffButton = false;
bool automation = false;
bool setValueOnAutoTomanualFlag = false;
bool setValueOnManualToAutoFlag = false;
bool patternControllerFlag = false;
bool printFlag = false;
/*Ethernet Reconnection Flag*/
uint8_t reconnectCounter = 0;

#endif