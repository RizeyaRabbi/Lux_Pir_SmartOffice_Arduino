#ifndef FLAGS_H
#define FLAGS_H

/*Global flags for MQTT message on All topics*/
bool relayStatusMQTTFlag[] = {false, false, false, false, false, false, false, false, false,
                              false, false, false, false, false, false, false};

/*Global flags to publish MQTT messages outside Callback function*/
bool allRelayOn = false;
bool allRelayOnButton = false;
bool allRelayOff = false;
bool allRelayOffButton = false;
bool automation = false;
bool setValueOnAutoTomanualFlag = false;
bool setValueOnManualToAutoFlag = false;

#endif