// Library Includes
#include <PubSubClient.h>
#include <Ethernet.h>
#include <SPI.h>
#include <ArduinoJson.h>

// Private Includes
#include "Topics.h"
#include "EthernetCredentials.h"
#include "MQTTCredentials.h"
#include "MQTTData.h"
#include "Flags.h"
#include "GPIO.h"
#include "LogicLevel.h"

/*Reference Variables for Subscription topic*/
const char *&row0_light0_topic = subscriptionToics[0];
const char *&row0_light1_topic = subscriptionToics[1];
const char *&row1_light0_topic = subscriptionToics[2];
const char *&row1_light1_topic = subscriptionToics[3];
const char *&row2_light0_topic = subscriptionToics[4];
const char *&row2_light1_topic = subscriptionToics[5];
const char *&row3_light0_topic = subscriptionToics[6];
const char *&row3_light1_topic = subscriptionToics[7];
const char *&row4_light0_topic = subscriptionToics[8];
const char *&row4_light1_topic = subscriptionToics[9];
const char *&row5_light0_topic = subscriptionToics[10];
const char *&row5_light1_topic = subscriptionToics[11];
const char *&mainRoomLight_topic = subscriptionToics[12];
const char *&washRoom0_devices_topic = subscriptionToics[13];
const char *&washRoom1_light_topic = subscriptionToics[14];
const char *&washRoom1_exhaust_topic = subscriptionToics[15];
const char *&allRelayOn_topic = subscriptionToics[16];
const char *&allRelayOff_topic = subscriptionToics[17];
const char *&automation_topic = subscriptionToics[18];
const char *&pattern_topic = subscriptionToics[19];
const char *&luxSensor0_topic = subscriptionToics[20];
const char *&device_delay_topic = subscriptionToics[21];

/*Reference Variables for relayStatusMQTT[16]*/
uint8_t &row0_relay0_data_mQTT = relayStatusMQTT[0];
uint8_t &row0_relay1_data_mQTT = relayStatusMQTT[1];
uint8_t &row1_relay0_data_mQTT = relayStatusMQTT[2];
uint8_t &row1_relay1_data_mQTT = relayStatusMQTT[3];
uint8_t &row2_relay0_data_mQTT = relayStatusMQTT[4];
uint8_t &row2_relay1_data_mQTT = relayStatusMQTT[5];
uint8_t &row3_relay0_data_mQTT = relayStatusMQTT[6];
uint8_t &row3_relay1_data_mQTT = relayStatusMQTT[7];
uint8_t &row4_relay0_data_mQTT = relayStatusMQTT[8];
uint8_t &row4_relay1_data_mQTT = relayStatusMQTT[9];
uint8_t &row5_relay0_data_mQTT = relayStatusMQTT[10];
uint8_t &row5_relay1_data_mQTT = relayStatusMQTT[11];
uint8_t &mainRoom_relay0_data_mQTT = relayStatusMQTT[12];
uint8_t &washRoom0_relay0_data_mQTT = relayStatusMQTT[13];
uint8_t &washRoom1_relay0_data_mQTT = relayStatusMQTT[14];
uint8_t &washRoom1_relay1_data_mQTT = relayStatusMQTT[15];

/*Refernce Variables for patternFlag[16]*/
bool &row0_light0_pattern_flag_mQTT = patternFlag[0];
bool &row0_light1_pattern_flag_mQTT = patternFlag[1];
bool &row1_light0_pattern_flag_mQTT = patternFlag[2];
bool &row1_light1_pattern_flag_mQTT = patternFlag[3];
bool &row2_light0_pattern_flag_mQTT = patternFlag[4];
bool &row2_light1_pattern_flag_mQTT = patternFlag[5];
bool &row3_light0_pattern_flag_mQTT = patternFlag[6];
bool &row3_light1_pattern_flag_mQTT = patternFlag[7];
bool &row4_light0_pattern_flag_mQTT = patternFlag[8];
bool &row4_light1_pattern_flag_mQTT = patternFlag[9];
bool &row5_light0_pattern_flag_mQTT = patternFlag[10];
bool &row5_light1_pattern_flag_mQTT = patternFlag[11];
bool &mainroom_light_pattern_flag_mQTT = patternFlag[12];
bool &washroom0_devices_pattern_flag_mQTT = patternFlag[13];
bool &washroom1_light_pattern_flag_mQTT = patternFlag[14];
bool &washroom1_exhaust_pattern_flag_mQTT = patternFlag[15];

/*Reference variables for pattern manual data*/
uint8_t &row0_light0_pattern_manual_status = relayStatusPattern[0];
uint8_t &row0_light1_pattern_manual_status = relayStatusPattern[1];
uint8_t &row1_light0_pattern_manual_status = relayStatusPattern[2];
uint8_t &row1_light1_pattern_manual_status = relayStatusPattern[3];
uint8_t &row2_light0_pattern_manual_status = relayStatusPattern[4];
uint8_t &row2_light1_pattern_manual_status = relayStatusPattern[5];
uint8_t &row3_light0_pattern_manual_status = relayStatusPattern[6];
uint8_t &row3_light1_pattern_manual_status = relayStatusPattern[7];
uint8_t &row4_light0_pattern_manual_status = relayStatusPattern[8];
uint8_t &row4_light1_pattern_manual_status = relayStatusPattern[9];
uint8_t &row5_light0_pattern_manual_status = relayStatusPattern[10];
uint8_t &row5_light1_pattern_manual_status = relayStatusPattern[11];
uint8_t &mainroom_light_pattern_manual_status = relayStatusPattern[12];
uint8_t &washroom0_devices_pattern_manual_status = relayStatusPattern[13];
uint8_t &washroom1_light_pattern_manual_status = relayStatusPattern[14];
uint8_t &washroom1_exhaust_pattern_manual_status = relayStatusPattern[15];

/*Reference Variables for relayStatusMQTTFlag[16]*/
bool &row0_relay0_flag_mQTT = relayStatusMQTTFlag[0];
bool &row0_relay1_flag_mQTT = relayStatusMQTTFlag[1];
bool &row1_relay0_flag_mQTT = relayStatusMQTTFlag[2];
bool &row1_relay1_flag_mQTT = relayStatusMQTTFlag[3];
bool &row2_relay0_flag_mQTT = relayStatusMQTTFlag[4];
bool &row2_relay1_flag_mQTT = relayStatusMQTTFlag[5];
bool &row3_relay0_flag_mQTT = relayStatusMQTTFlag[6];
bool &row3_relay1_flag_mQTT = relayStatusMQTTFlag[7];
bool &row4_relay0_flag_mQTT = relayStatusMQTTFlag[8];
bool &row4_relay1_flag_mQTT = relayStatusMQTTFlag[9];
bool &row5_relay0_flag_mQTT = relayStatusMQTTFlag[10];
bool &row5_relay1_flag_mQTT = relayStatusMQTTFlag[11];
bool &mainRoom_relay0_flag_mQTT = relayStatusMQTTFlag[12];
bool &washRoom0_relay0_flag_mQTT = relayStatusMQTTFlag[13];
bool &washRoom1_relay0_flag_mQTT = relayStatusMQTTFlag[14];
bool &washRoom1_relay1_flag_mQTT = relayStatusMQTTFlag[15];

/*Reference variables for output pins*/
const uint8_t &row0_light0 = output[0]; // 54  22
const uint8_t &row0_light1 = output[1]; // 55  24

const uint8_t &row1_light0 = output[2]; // 56  26
const uint8_t &row1_light1 = output[3]; // 57  28

const uint8_t &row2_light0 = output[4]; // 58  30
const uint8_t &row2_light1 = output[5]; // 59  32

const uint8_t &row3_light0 = output[6]; // 60  34
const uint8_t &row3_light1 = output[7]; // 61  36

const uint8_t &row4_light0 = output[8]; // 62  38
const uint8_t &row4_light1 = output[9]; // 63  40

const uint8_t &row5_light0 = output[10]; // 64  42
const uint8_t &row5_light1 = output[11]; // 65  44

const uint8_t &mainRoomLight = output[12];     // 66  46
const uint8_t &washRoom0_devices = output[13]; // 67  48
const uint8_t &washRoom1_light = output[14];   // 68  49
const uint8_t &washRoom1_exhaust = output[15]; // 69  47

/*Reference Variables for INPUT Pins*/
const uint8_t &row0_sensor0 = input[0]; // A0  //22
const uint8_t &row0_sensor1 = input[1]; // A1  //23
const uint8_t &row0_sensor2 = input[2]; // A2  //24
const uint8_t &row0_sensor3 = input[3]; // A3  //25
const uint8_t &row0_sensor4 = input[4]; // A4  //26
const uint8_t &row0_sensor5 = input[5]; // A5  //27
const uint8_t &row0_sensor6 = input[6]; // A6  //28
const uint8_t &row0_sensor7 = input[7]; // A7  //29
const uint8_t &row0_sensor8 = input[8]; // A8  //30
const uint8_t &row0_sensor9 = input[9]; // A9  //31

const uint8_t &row1_sensor0 = input[10]; // 45  //32
const uint8_t &row1_sensor1 = input[11]; // 43  //33
const uint8_t &row1_sensor2 = input[12]; // 41  //34
const uint8_t &row1_sensor3 = input[13]; // 39  //35
const uint8_t &row1_sensor4 = input[14]; // 37  //36
const uint8_t &row1_sensor5 = input[15]; // 35  //37
const uint8_t &row1_sensor6 = input[16]; // 33  //38

const uint8_t &row2_sensor0 = input[17]; // 31  //39
const uint8_t &row2_sensor1 = input[18]; // 29  //40
const uint8_t &row2_sensor2 = input[19]; // 27  //41
const uint8_t &row2_sensor3 = input[20]; // 25  //42
const uint8_t &row2_sensor4 = input[21]; // 23  //43

const uint8_t &row3_sensor0 = input[22]; // 12  //44
const uint8_t &row3_sensor1 = input[23]; // 11  //45
const uint8_t &row3_sensor2 = input[24]; // 9   //46
const uint8_t &row3_sensor3 = input[25]; // 8   //47

const uint8_t &row4_sensor0 = input[26]; // 7   //48
const uint8_t &row4_sensor1 = input[27]; // 6   //49
const uint8_t &row4_sensor2 = input[28]; // 5   //2
const uint8_t &row4_sensor3 = input[29]; // 3   //3
const uint8_t &row4_sensor4 = input[30]; // 2   //5
const uint8_t &row4_sensor5 = input[31]; // 14  //6

const uint8_t &row5_sensor0 = input[32]; // 15  //7
const uint8_t &row5_sensor1 = input[33]; // 16  //8
const uint8_t &row5_sensor2 = input[34]; // 17  //9
const uint8_t &row5_sensor3 = input[35]; // 18  //11
const uint8_t &row5_sensor4 = input[36]; // 19  //12
const uint8_t &row5_sensor5 = input[37]; // 20  //14
const uint8_t &row5_sensor6 = input[38]; // 21  //15

const uint8_t &washRoom1_sensor0 = input[39]; // A11  //16
const uint8_t &washRoom1_sensor1 = input[40]; // A13  //17
const uint8_t &washRoom1_sensor2 = input[41]; // A12  //18
const uint8_t &washRoom1_sensor3 = input[42]; // A10  //19

const uint8_t &washRoom0_sensor0 = input[43]; // A14  //20

const uint8_t &mainRoom_sensor = input[44]; // A15  //21

/*Reference Variables for input status*/
uint8_t &row0_sensor0_status = input_status[0];
uint8_t &row0_sensor1_status = input_status[1];
uint8_t &row0_sensor2_status = input_status[2];
uint8_t &row0_sensor3_status = input_status[3];
uint8_t &row0_sensor4_status = input_status[4];
uint8_t &row0_sensor5_status = input_status[5];
uint8_t &row0_sensor6_status = input_status[6];
uint8_t &row0_sensor7_status = input_status[7];
uint8_t &row0_sensor8_status = input_status[8];
uint8_t &row0_sensor9_status = input_status[9];

uint8_t &row1_sensor0_status = input_status[10];
uint8_t &row1_sensor1_status = input_status[11];
uint8_t &row1_sensor2_status = input_status[12];
uint8_t &row1_sensor3_status = input_status[13];
uint8_t &row1_sensor4_status = input_status[14];
uint8_t &row1_sensor5_status = input_status[15];
uint8_t &row1_sensor6_status = input_status[16];

uint8_t &row2_sensor0_status = input_status[17];
uint8_t &row2_sensor1_status = input_status[18];
uint8_t &row2_sensor2_status = input_status[19];
uint8_t &row2_sensor3_status = input_status[20];
uint8_t &row2_sensor4_status = input_status[21];

uint8_t &row3_sensor0_status = input_status[22];
uint8_t &row3_sensor1_status = input_status[23];
uint8_t &row3_sensor2_status = input_status[24];
uint8_t &row3_sensor3_status = input_status[25];

uint8_t &row4_sensor0_status = input_status[26];
uint8_t &row4_sensor1_status = input_status[27];
uint8_t &row4_sensor2_status = input_status[28];
uint8_t &row4_sensor3_status = input_status[29];
uint8_t &row4_sensor4_status = input_status[30];
uint8_t &row4_sensor5_status = input_status[31];

uint8_t &row5_sensor0_status = input_status[32];
uint8_t &row5_sensor1_status = input_status[33];
uint8_t &row5_sensor2_status = input_status[34];
uint8_t &row5_sensor3_status = input_status[35];
uint8_t &row5_sensor4_status = input_status[36];
uint8_t &row5_sensor5_status = input_status[37];
uint8_t &row5_sensor6_status = input_status[38];

uint8_t &washRoom1_sensor0_status = input_status[39];
uint8_t &washRoom1_sensor1_status = input_status[40];
uint8_t &washRoom1_sensor2_status = input_status[41];
uint8_t &washRoom1_sensor3_status = input_status[42];

uint8_t &washRoom0_sensor0_status = input_status[43];

uint8_t &mainRoom_sensor_status = input_status[44];

/*Configures Output Pins*/
void OutputConfig();

/*Configures Input Pins*/
void InputConfig();

/*Updates Input Pin Status*/
void UpdateInputPinStatus();

/*Configures and connects to Ethernet*/
void InitializeEthernet();

/*Prints Ethernet Hardware Status*/
void PrintEthernetHardwareStatus();

/*Reconnects to MQTT and Ethernet after lost connection*/
void Reconnect();

/*Configures and Connects to MQTT broker*/
void InitializeMQTT();

/*MQTT messages arrives here*/
void Callback(char *, uint8_t *, unsigned int);

/*Switches OUTPUT devices according to MQTT message*/
void Controller(const uint8_t, const uint8_t);

/*Subscribes to MQTT topics*/
void TopicSubscription();

/*Publish to topics on all Relay ON*/
void AllRelayOnAction();

/*Publish to topics on all Relay OFF*/
void AllRelayOffAction();

/*Sensor based Automation*/
void AutomaticControl();

/*Ethernet client Initialization*/
EthernetClient ethClient;

/*MQTT client Initialization over Ethernet*/
PubSubClient mqttClient(ethClient);

/* All Relay Controller Function upon MQTT message*/
void RelayController();

/*Pattern Controller*/
void PatternController();

/*Set and reset Value to Objects during RunTime*/
void ChangeValueOnManualToAuto();
void ChangeValueOnAutoToManual();

/*All Relay ON OFF button Handler*/
void AllRelayOnButtonHandler();
void AllRelayOffButtonHandler();

/*Class for sensor based automation*/
class Automation
{
private:
  unsigned long waitTime, startInterval, startWaitTime, startTime, stopTime,
      secondsInOneMinute, milliSecondsInOneSecond;
  bool deviceOn, keepDeviceOn;

public:
  Automation();
  void setDefaultValue();
  void setValueOnManualToAuto();
  void printValue();
  void controller(uint8_t *, const uint8_t *, const char *, float *, unsigned long);
  void controller(uint8_t *, uint8_t *, const uint8_t *, const char *, float *, unsigned long);
  void controller(uint8_t *, uint8_t *, uint8_t *, const uint8_t *, const char *, float *, unsigned long);
  void controller(uint8_t *, uint8_t *, uint8_t *, uint8_t *, const uint8_t *, const char *, float *, unsigned long);
  void controller(uint8_t *, uint8_t *, uint8_t *, uint8_t *, uint8_t *, const uint8_t *, const char *, float *, unsigned long);
  ~Automation();
};

/*Objects for Automation Class*/
Automation device[16];

/*Class to send PIR sensor data to MQTT server*/
class PIRtoMQTT
{
public:
  PIRtoMQTT();
  void sendToMQTT(byte, const char *);

private:
  boolean _triggered;
};

PIRtoMQTT pirSensor[45];

/*Continously sends PIR sensor data to MQTT*/
void sendPirToMQTT();

void setup()
{
  Serial.begin(9600);
  OutputConfig();
  InputConfig();
  UpdateInputPinStatus();
  InitializeEthernet();
  InitializeMQTT();
}

void loop()
{
  if (!mqttClient.connected())
  {
    Reconnect();
  }
  mqttClient.loop();
  // sendPirToMQTT();
  AutomaticControl();
  if (patternControllerFlag)
  {
    PatternController();
    patternControllerFlag = false;
  }
  RelayController();
}

void InitializeEthernet()
{
  Ethernet.begin(mac, ip);
  delay(3000);
  PrintEthernetHardwareStatus();
  if (Ethernet.linkStatus() == LinkOFF)
  {
    Serial.println(F("Ethernet cable is unplugged or defective"));
  }
}

void PrintEthernetHardwareStatus()
{
  Serial.print(F("\n"));
  if (Ethernet.hardwareStatus() == EthernetW5500)
  {
    Serial.println(F("W5500 Ethernet controller detected."));
  }
  else if (Ethernet.hardwareStatus() == EthernetW5100)
  {
    Serial.println(F("W5100 Ethernet controller detected."));
  }
  else if (Ethernet.hardwareStatus() == EthernetNoHardware)
  {
    Serial.println(F("Ethernet shield was not found."));
  }
}

void Reconnect()
{
  while (!mqttClient.connected())
  {
    Serial.print(F("\n"));
    Serial.print(F("Attempting MQTT connection:: "));
    if (mqttClient.connect(clientId, mqtt_username, mqtt_password, deviceStatus_topic, 0, true, "Disconnected"))
    {
      Serial.println(F("Connected"));
      TopicSubscription();
    }
    else
    {
      reconnectCounter += 1;
      switch (mqttClient.state())
      {
      case -4:
        Serial.print(F("MQTT_CONNECTION_TIMEOUT"));
        break;
      case -3:
        Serial.print(F("MQTT_CONNECTION_LOST"));
        break;
      case -2:
        Serial.print(F("MQTT_CONNECT_FAILED"));
        break;
      case -1:
        Serial.print(F("MQTT_DISCONNECTED"));
        break;
      case 0:
        Serial.print(F("MQTT_CONNECTED"));
        break;
      case 1:
        Serial.print(F("MQTT_CONNECT_BAD_PROTOCOL"));
        break;
      case 2:
        Serial.print(F("MQTT_CONNECT_BAD_CLIENT_ID"));
        break;
      case 3:
        Serial.print(F("MQTT_CONNECT_UNAVAILABLE"));
        break;
      case 4:
        Serial.print(F("MQTT_CONNECT_BAD_CREDENTIALS"));
        break;
      case 5:
        Serial.print(F("MQTT_CONNECT_UNAUTHORIZED"));
        break;
      default:
        Serial.print(F("Invalid State"));
        break;
      }
      Serial.print(F("\n"));
      Serial.print(F("Retrying..."));
      Serial.print(F("\n"));
      delay(2000);
      if (reconnectCounter == 3)
      {
        if (Ethernet.linkStatus() == LinkON)
        {
          Serial.println(F("Retrying..."));
          Ethernet.begin(mac, ip);
          delay(1000);
          reconnectCounter = 0;
        }
        else if (Ethernet.linkStatus() == LinkOFF)
        {
          Serial.println(F("Ethernet cable is unplugged or defective"));
          reconnectCounter = 0;
        }
      }
    }
  }
}

void InitializeMQTT()
{
  mqttClient.setServer(mqtt_server, mqtt_port);
  mqttClient.setCallback(Callback);
  if (mqttClient.connect(clientId, mqtt_username, mqtt_password, deviceStatus_topic, 0, true, "Disconnected"))
  {
    Serial.println(F("Connected to MQTT broker"));
    TopicSubscription();
  }
  else
  {
    Serial.println(F("Could not connect to MQTT broker"));
  }
}

void Callback(char *topic, uint8_t *payload, unsigned int length)
{
  if (strcmp(topic, luxSensor0_topic) == 0)
  {
    char payLoadBuffer[length];
    for (unsigned int i = 0; i < length; i++)
    {
      payLoadBuffer[i] = payload[i];
    }
    luxSensor0_data_mQTT = (float)atof(payLoadBuffer);
  }
  else if (strcmp(topic, device_delay_topic) == 0)
  {
    StaticJsonDocument<192> doc;
    deserializeJson(doc, payload);
    if (doc["0"] > 0)
    {
      individualDelayTime[0] = doc["0"];
    }
    if (doc["1"] > 0)
    {
      individualDelayTime[1] = doc["1"];
    }
    if (doc["2"] > 0)
    {
      individualDelayTime[2] = doc["2"];
    }
    if (doc["3"] > 0)
    {
      individualDelayTime[3] = doc["3"];
    }
    if (doc["4"] > 0)
    {
      individualDelayTime[4] = doc["4"];
    }
    if (doc["5"] > 0)
    {
      individualDelayTime[5] = doc["5"];
    }
    if (doc["6"] > 0)
    {
      individualDelayTime[6] = doc["6"];
    }
    if (doc["7"] > 0)
    {
      individualDelayTime[7] = doc["7"];
    }
    if (doc["8"] > 0)
    {
      individualDelayTime[8] = doc["8"];
    }
    if (doc["9"] > 0)
    {
      individualDelayTime[9] = doc["9"];
    }
    if (doc["10"] > 0)
    {
      individualDelayTime[10] = doc["10"];
    }
    if (doc["11"] > 0)
    {
      individualDelayTime[11] = doc["11"];
    }
    if (doc["12"] > 0)
    {
      individualDelayTime[12] = doc["12"];
    }
    if (doc["13"] > 0)
    {
      individualDelayTime[13] = doc["13"];
    }
    if (doc["14"] > 0)
    {
      individualDelayTime[14] = doc["14"];
    }
    if (doc["15"] > 0)
    {
      individualDelayTime[15] = doc["15"];
    }

    Serial.print("\n");
    for (uint8_t i = 0; i < sizeof(individualDelayTime) / sizeof(individualDelayTime[0]); i++)
    {
      Serial.print(individualDelayTime[i]);
      Serial.print("  ");
    }
  }
  else if (strcmp(topic, pattern_topic) == 0)
  {
    StaticJsonDocument<192> doc;
    deserializeJson(doc, payload);

    if (doc["0"] == MANUAL_OFF || doc["0"] == MANUAL_ON)
    {
      row0_light0_pattern_flag_mQTT = false;
      row0_light0_pattern_manual_status = doc["0"];
      device[0].setDefaultValue();
    }
    else if (doc["0"] == AUTOMATION)
    {
      row0_light0_pattern_flag_mQTT = true;
    }

    if (doc["1"] == MANUAL_OFF || doc["1"] == MANUAL_ON)
    {
      row0_light1_pattern_flag_mQTT = false;
      row0_light1_pattern_manual_status = doc["1"];
      device[1].setDefaultValue();
    }
    else if (doc["1"] == AUTOMATION)
    {
      row0_light1_pattern_flag_mQTT = true;
    }

    if (doc["2"] == MANUAL_OFF || doc["2"] == MANUAL_ON)
    {
      row1_light0_pattern_flag_mQTT = false;
      row1_light0_pattern_manual_status = doc["2"];
      device[2].setDefaultValue();
    }
    else if (doc["2"] == AUTOMATION)
    {
      row1_light0_pattern_flag_mQTT = true;
    }

    if (doc["3"] == MANUAL_OFF || doc["3"] == MANUAL_ON)
    {
      row1_light1_pattern_flag_mQTT = false;
      row1_light1_pattern_manual_status = doc["3"];
      device[3].setDefaultValue();
    }
    else if (doc["3"] == AUTOMATION)
    {
      row1_light1_pattern_flag_mQTT = true;
    }

    if (doc["4"] == MANUAL_OFF || doc["4"] == MANUAL_ON)
    {
      row2_light0_pattern_flag_mQTT = false;
      row2_light0_pattern_manual_status = doc["4"];
      device[4].setDefaultValue();
    }
    else if (doc["4"] == AUTOMATION)
    {
      row2_light0_pattern_flag_mQTT = true;
    }

    if (doc["5"] == MANUAL_OFF || doc["5"] == MANUAL_ON)
    {
      row2_light1_pattern_flag_mQTT = false;
      row2_light1_pattern_manual_status = doc["5"];
      device[5].setDefaultValue();
    }
    else if (doc["5"] == AUTOMATION)
    {
      row2_light1_pattern_flag_mQTT = true;
    }

    if (doc["6"] == MANUAL_OFF || doc["6"] == MANUAL_ON)
    {
      row3_light0_pattern_flag_mQTT = false;
      row3_light0_pattern_manual_status = doc["6"];
      device[6].setDefaultValue();
    }
    else if (doc["6"] == AUTOMATION)
    {
      row3_light0_pattern_flag_mQTT = true;
    }

    if (doc["7"] == MANUAL_OFF || doc["7"] == MANUAL_ON)
    {
      row3_light1_pattern_flag_mQTT = false;
      row3_light1_pattern_manual_status = doc["7"];
      device[7].setDefaultValue();
    }
    else if (doc["7"] == AUTOMATION)
    {
      row3_light1_pattern_flag_mQTT = true;
    }

    if (doc["8"] == MANUAL_OFF || doc["8"] == MANUAL_ON)
    {
      row4_light0_pattern_flag_mQTT = false;
      row4_light0_pattern_manual_status = doc["8"];
      device[8].setDefaultValue();
    }
    else if (doc["8"] == AUTOMATION)
    {
      row4_light0_pattern_flag_mQTT = true;
    }

    if (doc["9"] == MANUAL_OFF || doc["9"] == MANUAL_ON)
    {
      row4_light1_pattern_flag_mQTT = false;
      row4_light1_pattern_manual_status = doc["9"];
      device[9].setDefaultValue();
    }
    else if (doc["9"] == AUTOMATION)
    {
      row4_light1_pattern_flag_mQTT = true;
    }

    if (doc["10"] == MANUAL_OFF || doc["10"] == MANUAL_ON)
    {
      row5_light0_pattern_flag_mQTT = false;
      row5_light0_pattern_manual_status = doc["10"];
      device[10].setDefaultValue();
    }
    else if (doc["10"] == AUTOMATION)
    {
      row5_light0_pattern_flag_mQTT = true;
    }

    if (doc["11"] == MANUAL_OFF || doc["11"] == MANUAL_ON)
    {
      row5_light1_pattern_flag_mQTT = false;
      row5_light1_pattern_manual_status = doc["11"];
      device[11].setDefaultValue();
    }
    else if (doc["11"] == AUTOMATION)
    {
      row5_light1_pattern_flag_mQTT = true;
    }

    if (doc["12"] == MANUAL_OFF || doc["12"] == MANUAL_ON)
    {
      mainroom_light_pattern_flag_mQTT = false;
      mainroom_light_pattern_manual_status = doc["12"];
      device[12].setDefaultValue();
    }
    else if (doc["12"] == AUTOMATION)
    {
      mainroom_light_pattern_flag_mQTT = true;
    }

    if (doc["13"] == MANUAL_OFF || doc["13"] == MANUAL_ON)
    {
      washroom0_devices_pattern_flag_mQTT = false;
      washroom0_devices_pattern_manual_status = doc["13"];
      device[13].setDefaultValue();
    }
    else if (doc["13"] == AUTOMATION)
    {
      washroom0_devices_pattern_flag_mQTT = true;
    }

    if (doc["14"] == MANUAL_OFF || doc["14"] == MANUAL_ON)
    {
      washroom1_light_pattern_flag_mQTT = false;
      washroom1_light_pattern_manual_status = doc["14"];
      device[14].setDefaultValue();
    }
    else if (doc["14"] == AUTOMATION)
    {
      washroom1_light_pattern_flag_mQTT = true;
    }

    if (doc["15"] == MANUAL_OFF || doc["15"] == MANUAL_ON)
    {
      washroom1_exhaust_pattern_flag_mQTT = false;
      washroom1_exhaust_pattern_manual_status = doc["15"];
      device[15].setDefaultValue();
    }
    else if (doc["15"] == AUTOMATION)
    {
      washroom1_exhaust_pattern_flag_mQTT = true;
    }
    patternControllerFlag = true;
  }
  else if (strcmp(topic, automation_topic) == 0)
  {
    if ((*payload - 48) == 1)
    {
      automation = true;
      setValueOnManualToAutoFlag = true;
    }
    if ((*payload - 48) == 0)
    {
      automation = false;
      setValueOnAutoTomanualFlag = true;
    }
  }
  else if (strcmp(topic, allRelayOn_topic) == 0)
  {
    if ((*payload - 48) == 1)
    {
      len = length;
      allRelayOn = true;
      allRelayOnButton = true;
      allRelayOnButton_data_mQTT = 1;
    }
    if ((*payload - 48) == 0)
    {
      len = length;
      allRelayOn = false;
      allRelayOnButton = false;
      allRelayOnButton_data_mQTT = 0;
    }
  }
  else if (strcmp(topic, allRelayOff_topic) == 0)
  {
    if ((*payload - 48) == 1)
    {
      len = length;
      allRelayOff = true;
      allRelayOffButton = true;
      allRelayOffButton_data_mQTT = 1;
    }
    if ((*payload - 48) == 0)
    {
      len = length;
      allRelayOff = false;
      allRelayOffButton = false;
      allRelayOffButton_data_mQTT = 0;
    }
  }
  else if (strcmp(topic, washRoom0_devices_topic) == 0)
  {
    washRoom0_relay0_data_mQTT = *payload - 48;
    washRoom0_relay0_flag_mQTT = true;
  }
  else if (strcmp(topic, washRoom1_light_topic) == 0)
  {
    washRoom1_relay0_data_mQTT = *payload - 48;
    washRoom1_relay0_flag_mQTT = true;
  }
  else if (strcmp(topic, washRoom1_exhaust_topic) == 0)
  {
    washRoom1_relay1_data_mQTT = *payload - 48;
    washRoom1_relay1_flag_mQTT = true;
  }
  else if (strcmp(topic, row0_light0_topic) == 0)
  {
    int payloadData = *payload - 48;
    row0_relay0_data_mQTT = payloadData;
    row0_relay0_flag_mQTT = true;
  }
  else if (strcmp(topic, row0_light1_topic) == 0)
  {
    row0_relay1_data_mQTT = *payload - 48;
    row0_relay1_flag_mQTT = true;
  }
  else if (strcmp(topic, mainRoomLight_topic) == 0)
  {
    mainRoom_relay0_data_mQTT = *payload - 48;
    mainRoom_relay0_flag_mQTT = true;
  }
  else if (strcmp(topic, row1_light0_topic) == 0)
  {
    row1_relay0_data_mQTT = *payload - 48;
    row1_relay0_flag_mQTT = true;
  }
  else if (strcmp(topic, row1_light1_topic) == 0)
  {
    row1_relay1_data_mQTT = *payload - 48;
    row1_relay1_flag_mQTT = true;
  }
  else if (strcmp(topic, row2_light0_topic) == 0)
  {
    row2_relay0_data_mQTT = *payload - 48;
    row2_relay0_flag_mQTT = true;
  }
  else if (strcmp(topic, row2_light1_topic) == 0)
  {
    row2_relay1_data_mQTT = *payload - 48;
    row2_relay1_flag_mQTT = true;
  }
  else if (strcmp(topic, row3_light0_topic) == 0)
  {
    row3_relay0_data_mQTT = *payload - 48;
    row3_relay0_flag_mQTT = true;
  }
  else if (strcmp(topic, row3_light1_topic) == 0)
  {
    row3_relay1_data_mQTT = *payload - 48;
    row3_relay1_flag_mQTT = true;
  }
  else if (strcmp(topic, row4_light0_topic) == 0)
  {
    row4_relay0_data_mQTT = *payload - 48;
    row4_relay0_flag_mQTT = true;
  }
  else if (strcmp(topic, row4_light1_topic) == 0)
  {
    row4_relay1_data_mQTT = *payload - 48;
    row4_relay1_flag_mQTT = true;
  }
  else if (strcmp(topic, row5_light0_topic) == 0)
  {
    row5_relay0_data_mQTT = *payload - 48;
    row5_relay0_flag_mQTT = true;
  }
  else if (strcmp(topic, row5_light1_topic) == 0)
  {
    row5_relay1_data_mQTT = *payload - 48;
    row5_relay1_flag_mQTT = true;
  }
}

void Controller(const uint8_t _mqttMessage, const uint8_t _device)
{
  if (_mqttMessage == 1)
  {
    uint8_t _pinStatus = digitalRead(_device);
    if (_pinStatus == OFF)
    {
      digitalWrite(_device, ON);
      delay(100);
    }
  }
  if (_mqttMessage == 0)
  {
    uint8_t _pinStatus = digitalRead(_device);
    if (_pinStatus == ON)
    {
      digitalWrite(_device, OFF);
      delay(100);
    }
  }
}

void TopicSubscription()
{
  mqttClient.publish(deviceStatus_topic, "Connected", true);
  for (uint8_t i = 0; i < sizeof(subscriptionToics) / sizeof(subscriptionToics[0]); i++)
  {
    mqttClient.subscribe(subscriptionToics[i]);
  }
}

void AllRelayOnAction()
{
  Serial.print(F("\n"));
  Serial.print(F("AllRelayOnAction Called: "));
  uint8_t data[1] = {'1'};
  uint8_t *message = data;
  uint8_t data1[1] = {'0'};
  uint8_t *message1 = data1;
  if (allRelayOffButton)
  {
    mqttClient.publish(allRelayOff_topic, message1, len, false);
    allRelayOffButton = false;
  }
  mqttClient.publish(washRoom0_devices_topic, message, len, true);
  mqttClient.publish(washRoom1_light_topic, message, len, true);
  mqttClient.publish(washRoom1_exhaust_topic, message, len, true);
  mqttClient.publish(row0_light0_topic, message, len, true);
  mqttClient.publish(row0_light1_topic, message, len, true);
  mqttClient.publish(mainRoomLight_topic, message, len, true);
  mqttClient.publish(row1_light0_topic, message, len, true);
  mqttClient.publish(row1_light1_topic, message, len, true);
  mqttClient.publish(row2_light0_topic, message, len, true);
  mqttClient.publish(row2_light1_topic, message, len, true);
  mqttClient.publish(row3_light0_topic, message, len, true);
  mqttClient.publish(row3_light1_topic, message, len, true);
  mqttClient.publish(row4_light0_topic, message, len, true);
  mqttClient.publish(row4_light1_topic, message, len, true);
  mqttClient.publish(row5_light0_topic, message, len, true);
  mqttClient.publish(row5_light1_topic, message, len, true);
  allRelayOn = false;
}

void AllRelayOffAction()
{
  uint8_t data[1] = {'0'};
  uint8_t *message = data;
  if (allRelayOnButton)
  {
    mqttClient.publish(allRelayOn_topic, message, len, false);
    allRelayOnButton = false;
  }
  mqttClient.publish(washRoom0_devices_topic, message, len, true);
  mqttClient.publish(washRoom1_light_topic, message, len, true);
  mqttClient.publish(washRoom1_exhaust_topic, message, len, true);
  mqttClient.publish(row0_light0_topic, message, len, true);
  mqttClient.publish(row0_light1_topic, message, len, true);
  mqttClient.publish(mainRoomLight_topic, message, len, true);
  mqttClient.publish(row1_light0_topic, message, len, true);
  mqttClient.publish(row1_light1_topic, message, len, true);
  mqttClient.publish(row2_light0_topic, message, len, true);
  mqttClient.publish(row2_light1_topic, message, len, true);
  mqttClient.publish(row3_light0_topic, message, len, true);
  mqttClient.publish(row3_light1_topic, message, len, true);
  mqttClient.publish(row4_light0_topic, message, len, true);
  mqttClient.publish(row4_light1_topic, message, len, true);
  mqttClient.publish(row5_light0_topic, message, len, true);
  mqttClient.publish(row5_light1_topic, message, len, true);
  allRelayOff = false;
}

void AutomaticControl()
{
  UpdateInputPinStatus();
  /************************************ Row0 with 2 Outputs *************************************************/
  if (row0_light0_pattern_flag_mQTT)
  {
    device[0].controller(&row0_sensor0_status, &row0_sensor1_status, &row0_sensor2_status, &row0_sensor3_status, &row0_sensor4_status, &row0_light0, row0_light0_topic, &luxSensor_testValue, individualDelayTime[0]);
  }

  if (row0_light1_pattern_flag_mQTT)
  {
    device[1].controller(&row0_sensor5_status, &row0_sensor6_status, &row0_sensor7_status, &row0_sensor8_status, &row0_sensor9_status, &row0_light1, row0_light1_topic, &luxSensor_testValue, individualDelayTime[1]);
  }
  /**********************************************************************************************************/

  /************************************ Row1 with 2 Outputs *************************************************/
  if (row1_light0_pattern_flag_mQTT)
  {
    device[2].controller(&row1_sensor0_status, &row1_sensor1_status, &row1_sensor2_status, &row1_sensor3_status, &row1_light0, row1_light0_topic, &luxSensor_testValue, individualDelayTime[2]);
  }
  if (row1_light1_pattern_flag_mQTT)
  {
    device[3].controller(&row1_sensor4_status, &row1_sensor5_status, &row1_sensor6_status, &row1_light1, row1_light1_topic, &luxSensor_testValue, individualDelayTime[3]);
  }
  /**********************************************************************************************************/

  /************************************ Row2 and Row3 with 2 outputs(Row3) **********************************/
  if (row2_light0_pattern_flag_mQTT)
  {
    device[4].controller(&row2_sensor0_status, &row2_sensor1_status, &row2_light0, row2_light0_topic, &luxSensor_testValue, individualDelayTime[4]);
  }
  if (row2_light1_pattern_flag_mQTT)
  {
    device[5].controller(&row2_sensor2_status, &row2_sensor3_status, &row2_sensor4_status, &row2_light1, row2_light1_topic, &luxSensor_testValue, individualDelayTime[5]);
  }
  if (row3_light0_pattern_flag_mQTT)
  {
    device[6].controller(&row3_sensor0_status, &row3_sensor1_status, &row3_light0, row3_light0_topic, &luxSensor_testValue, individualDelayTime[6]);
  }
  if (row3_light1_pattern_flag_mQTT)
  {
    device[7].controller(&row3_sensor2_status, &row3_sensor3_status, &row3_light1, row3_light1_topic, &luxSensor_testValue, individualDelayTime[7]);
  }
  /**********************************************************************************************************/

  /************************************ Row4 with 2 Outputs *************************************************/
  if (row4_light0_pattern_flag_mQTT)
  {
    device[8].controller(&row4_sensor0_status, &row4_sensor1_status, &row4_sensor2_status, &row4_light0, row4_light0_topic, &luxSensor_testValue, individualDelayTime[8]);
  }
  if (row4_light1_pattern_flag_mQTT)
  {
    device[9].controller(&row4_sensor3_status, &row4_sensor4_status, &row4_sensor5_status, &row4_light1, row4_light1_topic, &luxSensor_testValue, individualDelayTime[9]);
  }
  /**********************************************************************************************************/

  /************************************ Row5 with 2 Outputs *************************************************/
  if (row5_light0_pattern_flag_mQTT)
  {
    device[10].controller(&row5_sensor0_status, &row5_sensor1_status, &row5_sensor2_status, &row5_light0, row5_light0_topic, &luxSensor_testValue, individualDelayTime[10]);
  }
  if (row5_light1_pattern_flag_mQTT)
  {
    device[11].controller(&row5_sensor3_status, &row5_sensor4_status, &row5_sensor5_status, &row5_sensor6_status, &row5_light1, row5_light1_topic, &luxSensor_testValue, individualDelayTime[11]);
  }
  /**********************************************************************************************************/

  /************************************ MainRoom Light single Output ****************************************/
  if (mainroom_light_pattern_flag_mQTT)
  {
    device[12].controller(&mainRoom_sensor_status, &mainRoomLight, mainRoomLight_topic, &luxSensor0_data_mQTT, individualDelayTime[12]);
  }
  /**********************************************************************************************************/

  /************************************ WashRoom0 single Output *********************************************/
  if (washroom0_devices_pattern_flag_mQTT)
  {
    device[13].controller(&washRoom0_sensor0_status, &washRoom0_devices, washRoom0_devices_topic, &luxSensor_testValue, individualDelayTime[13]);
  }
  /**********************************************************************************************************/

  /************************************ WashRoom1 with 2 Output *********************************************/
  if (washroom1_light_pattern_flag_mQTT)
  {
    device[14].controller(&washRoom1_sensor0_status, &washRoom1_sensor1_status, &washRoom1_sensor2_status, &washRoom1_sensor3_status, &washRoom1_light, washRoom1_light_topic, &luxSensor_testValue, individualDelayTime[14]);
  }
  if (washroom1_exhaust_pattern_flag_mQTT)
  {
    device[15].controller(&washRoom1_sensor2_status, &washRoom1_sensor3_status, &washRoom1_exhaust, washRoom1_exhaust_topic, &luxSensor_testValue, individualDelayTime[15]);
  }
  /**********************************************************************************************************/
}

void RelayController()
{
  for (uint8_t i = 0; i < (sizeof(relayStatusMQTTFlag) / sizeof(relayStatusMQTTFlag[0])); i++)
  {
    if (relayStatusMQTTFlag[i])
    {
      Controller(relayStatusMQTT[i], output[i]);
      relayStatusMQTTFlag[i] = false;
      if (relayStatusMQTT[i] == 1)
      {
        AllRelayOffButtonHandler();
      }
      else if (relayStatusMQTT[i] == 0)
      {
        AllRelayOnButtonHandler();
      }
    }
  }
}

Automation::Automation()
{
  startInterval = 0UL;
  secondsInOneMinute = 60UL;
  milliSecondsInOneSecond = 1000UL;
  deviceOn = false;
  keepDeviceOn = false;
}

Automation::~Automation()
{
  Serial.println(F("Destructor Called..."));
}

void Automation::controller(uint8_t *sensorStatus0, const uint8_t *outputPin, const char *topic, float *luxSensorValue, unsigned long waitTimeInMinute)
{
  waitTime = waitTimeInMinute * secondsInOneMinute * milliSecondsInOneSecond;
  if (!deviceOn)
  {
    if ((*sensorStatus0 == 1) && (*luxSensorValue < luxSensorThreshold))
    {
      uint8_t data[1] = {'1'};
      uint8_t *message = data;
      if (digitalRead(*outputPin) == OFF)
      {
        mqttClient.publish(topic, message, 1, true);
        Serial.print(F("\n"));
        Serial.print(*outputPin);
        Serial.print(F(" :Turned ON"));
      }
      if (digitalRead(*outputPin) == ON)
      {
        Serial.print(F("\n"));
        Serial.print(*outputPin);
        Serial.print(F(" :Already Turned ON"));
      }
      deviceOn = true;
      keepDeviceOn = true;
    }
  }
  if (deviceOn)
  {
    if (*sensorStatus0 == 0)
    {
      deviceOn = false;
      startWaitTime = millis();
    }
  }
  if (keepDeviceOn)
  {
    if (*luxSensorValue >= luxSensorThreshold)
    {
      if (digitalRead(*outputPin) == OFF)
      {
        keepDeviceOn = false;
        deviceOn = false;
      }
      if (digitalRead(*outputPin) == ON)
      {
        uint8_t data[1] = {'0'};
        uint8_t *message = data;
        mqttClient.publish(topic, message, 1, true);
        keepDeviceOn = false;
        deviceOn = false;
      }
    }

    if ((*sensorStatus0 == 0) && (millis() - startWaitTime >= waitTime))
    {
      uint8_t data[1] = {'0'};
      uint8_t *message = data;
      if (digitalRead(*outputPin) == ON)
      {
        mqttClient.publish(topic, message, 1, true);
      }
      if (digitalRead(*outputPin) == OFF)
      {
        Serial.print(F("\n"));
        Serial.print(F("Already Turned OFF..."));
      }
      keepDeviceOn = false;
    }
  }
}

void Automation::controller(uint8_t *sensorStatus0, uint8_t *sensorStatus1, const uint8_t *outputPin, const char *topic, float *luxSensorValue, unsigned long waitTimeInMinute)
{
  waitTime = waitTimeInMinute * secondsInOneMinute * milliSecondsInOneSecond;
  UpdateInputPinStatus();
  if (!deviceOn)
  {
    if ((*sensorStatus0 == 1 || *sensorStatus1 == 1) && (*luxSensorValue < luxSensorThreshold))
    {
      uint8_t data[1] = {'1'};
      uint8_t *message = data;
      if (digitalRead(*outputPin) == OFF)
      {
        mqttClient.publish(topic, message, 1, true);
        Serial.print(F("\n"));
        Serial.print(*outputPin);
        Serial.print(F(" :Turned ON"));
      }
      if (digitalRead(*outputPin) == ON)
      {
        Serial.print(F("\n"));
        Serial.print(*outputPin);
        Serial.print(F(" :Already Turned ON..."));
      }
      deviceOn = true;
      keepDeviceOn = true;
    }
  }
  if (deviceOn)
  {
    if (*sensorStatus0 == 0 && *sensorStatus1 == 0)
    {
      deviceOn = false;
      startWaitTime = millis();
    }
  }
  if (keepDeviceOn)
  {
    if (*luxSensorValue >= luxSensorThreshold)
    {
      if (digitalRead(*outputPin) == OFF)
      {
        keepDeviceOn = false;
        deviceOn = false;
      }
      if (digitalRead(*outputPin) == ON)
      {
        uint8_t data[1] = {'0'};
        uint8_t *message = data;
        mqttClient.publish(topic, message, 1, true);
        keepDeviceOn = false;
        deviceOn = false;
      }
    }
    if (*sensorStatus0 == 0 && *sensorStatus1 == 0 && (millis() - startWaitTime >= waitTime))
    {
      uint8_t data[1] = {'0'};
      uint8_t *message = data;
      if (digitalRead(*outputPin) == ON)
      {
        mqttClient.publish(topic, message, 1, true);
      }
      if (digitalRead(*outputPin) == OFF)
      {
        Serial.print(F("\n"));
        Serial.print(F("Already Turned OFF..."));
      }
      keepDeviceOn = false;
    }
  }
}

void Automation::controller(uint8_t *sensorStatus0, uint8_t *sensorStatus1, uint8_t *sensorStatus2, const uint8_t *outputPin, const char *topic, float *luxSensorValue, unsigned long waitTimeInMinute)
{
  waitTime = waitTimeInMinute * secondsInOneMinute * milliSecondsInOneSecond;
  UpdateInputPinStatus();
  if (!deviceOn)
  {
    if ((*sensorStatus0 == 1 || *sensorStatus1 == 1 || *sensorStatus2 == 1) && (*luxSensorValue < luxSensorThreshold))
    {
      uint8_t data[1] = {'1'};
      uint8_t *message = data;
      if (digitalRead(*outputPin) == OFF)
      {
        mqttClient.publish(topic, message, 1, true);
        Serial.print(F("\n"));
        Serial.print(*outputPin);
        Serial.print(F(" :Turned ON"));
      }
      if (digitalRead(*outputPin) == ON)
      {
        Serial.print(F("\n"));
        Serial.print(*outputPin);
        Serial.print(F(" :Already Turned ON..."));
      }
      deviceOn = true;
      keepDeviceOn = true;
    }
  }
  if (deviceOn)
  {
    if (*sensorStatus0 == 0 && *sensorStatus1 == 0 && *sensorStatus2 == 0)
    {
      deviceOn = false;
      startWaitTime = millis();
    }
  }
  if (keepDeviceOn)
  {
    if (*luxSensorValue >= luxSensorThreshold)
    {
      if (digitalRead(*outputPin) == OFF)
      {
        keepDeviceOn = false;
        deviceOn = false;
      }
      if (digitalRead(*outputPin) == ON)
      {
        uint8_t data[1] = {'0'};
        uint8_t *message = data;
        mqttClient.publish(topic, message, 1, true);
        keepDeviceOn = false;
        deviceOn = false;
      }
    }
    if ((*sensorStatus0 == 0 && *sensorStatus1 == 0 && *sensorStatus2 == 0) && (millis() - startWaitTime >= waitTime))
    {
      uint8_t data[1] = {'0'};
      uint8_t *message = data;
      if (digitalRead(*outputPin) == ON)
      {
        mqttClient.publish(topic, message, 1, true);
      }
      if (digitalRead(*outputPin) == OFF)
      {
        Serial.print(F("\n"));
        Serial.print(F("Already Turned OFF..."));
      }
      keepDeviceOn = false;
    }
  }
}

void Automation::controller(uint8_t *sensorStatus0, uint8_t *sensorStatus1, uint8_t *sensorStatus2, uint8_t *sensorStatus3, const uint8_t *outputPin, const char *topic, float *luxSensorValue, unsigned long waitTimeInMinute)
{
  waitTime = waitTimeInMinute * secondsInOneMinute * milliSecondsInOneSecond;
  UpdateInputPinStatus();
  if (!deviceOn)
  {
    if ((*sensorStatus0 == 1 || *sensorStatus1 == 1 || *sensorStatus2 == 1 || *sensorStatus3 == 1) && (*luxSensorValue < luxSensorThreshold))
    {
      uint8_t data[1] = {'1'};
      uint8_t *message = data;
      if (digitalRead(*outputPin) == OFF)
      {
        mqttClient.publish(topic, message, 1, true);
        Serial.print(F("\n"));
        Serial.print(*outputPin);
        Serial.print(F(" :Turned ON"));
      }
      if (digitalRead(*outputPin) == ON)
      {
        Serial.print(F("\n"));
        Serial.print(*outputPin);
        Serial.print(F(" :Already Turned ON..."));
      }
      deviceOn = true;
      keepDeviceOn = true;
    }
  }
  if (deviceOn)
  {
    if (*sensorStatus0 == 0 && *sensorStatus1 == 0 && *sensorStatus2 == 0 && *sensorStatus3 == 0)
    {
      deviceOn = false;
      startWaitTime = millis();
    }
  }
  if (keepDeviceOn)
  {
    if (*luxSensorValue >= luxSensorThreshold)
    {
      if (digitalRead(*outputPin) == OFF)
      {
        keepDeviceOn = false;
        deviceOn = false;
      }
      if (digitalRead(*outputPin) == ON)
      {
        uint8_t data[1] = {'0'};
        uint8_t *message = data;
        mqttClient.publish(topic, message, 1, true);
        keepDeviceOn = false;
        deviceOn = false;
      }
    }
    if ((*sensorStatus0 == 0 && *sensorStatus1 == 0 && *sensorStatus2 == 0 && *sensorStatus3 == 0) && (millis() - startWaitTime >= waitTime))
    {
      uint8_t data[1] = {'0'};
      uint8_t *message = data;
      if (digitalRead(*outputPin) == ON)
      {
        mqttClient.publish(topic, message, 1, true);
      }
      if (digitalRead(*outputPin) == OFF)
      {
        Serial.print(F("\n"));
        Serial.print(F("Already Turned OFF..."));
      }
      keepDeviceOn = false;
    }
  }
}

void Automation::controller(uint8_t *sensorStatus0, uint8_t *sensorStatus1, uint8_t *sensorStatus2, uint8_t *sensorStatus3, uint8_t *sensorStatus4, const uint8_t *outputPin, const char *topic, float *luxSensorValue, unsigned long waitTimeInMinute)
{
  waitTime = waitTimeInMinute * secondsInOneMinute * milliSecondsInOneSecond;
  UpdateInputPinStatus();
  if (!deviceOn)
  {
    if ((*sensorStatus0 == 1 || *sensorStatus1 == 1 || *sensorStatus2 == 1 || *sensorStatus3 == 1 || *sensorStatus4 == 1) && (*luxSensorValue < luxSensorThreshold))
    {
      uint8_t data[1] = {'1'};
      uint8_t *message = data;
      if (digitalRead(*outputPin) == OFF)
      {
        mqttClient.publish(topic, message, 1, true);
        Serial.print(F("\n"));
        Serial.print(*outputPin);
        Serial.print(F(" :Turned ON"));
      }
      if (digitalRead(*outputPin) == ON)
      {
        Serial.print(F("\n"));
        Serial.print(*outputPin);
        Serial.print(F(" :Already Turned ON..."));
      }
      deviceOn = true;
      keepDeviceOn = true;
    }
  }
  if (deviceOn)
  {
    if (*sensorStatus0 == 0 && *sensorStatus1 == 0 && *sensorStatus2 == 0 && *sensorStatus3 == 0 && *sensorStatus4 == 0)
    {
      deviceOn = false;
      startWaitTime = millis();
    }
  }
  if (keepDeviceOn)
  {
    if (*luxSensorValue >= luxSensorThreshold)
    {
      if (digitalRead(*outputPin) == OFF)
      {
        keepDeviceOn = false;
        deviceOn = false;
      }
      if (digitalRead(*outputPin) == ON)
      {
        uint8_t data[1] = {'0'};
        uint8_t *message = data;
        mqttClient.publish(topic, message, 1, true);
        keepDeviceOn = false;
        deviceOn = false;
      }
    }
    if ((*sensorStatus0 == 0 && *sensorStatus1 == 0 && *sensorStatus2 == 0 && *sensorStatus3 == 0 && *sensorStatus4 == 0) && (millis() - startWaitTime >= waitTime))
    {
      uint8_t data[1] = {'0'};
      uint8_t *message = data;
      if (digitalRead(*outputPin) == ON)
      {
        mqttClient.publish(topic, message, 1, true);
      }
      if (digitalRead(*outputPin) == OFF)
      {
        Serial.print(F("\n"));
        Serial.print(F("Already Turned OFF..."));
      }
      keepDeviceOn = false;
    }
  }
}

void Automation::setDefaultValue()
{
  startInterval = 0UL;
  secondsInOneMinute = 1UL;
  milliSecondsInOneSecond = 1000UL;
  deviceOn = false;
  keepDeviceOn = false;
}

void Automation::setValueOnManualToAuto()
{
  Serial.print(F("\n"));
  Serial.print(F("setValueOnManualToAuto::"));
  Serial.print(F(" done..."));
  deviceOn = true;
  keepDeviceOn = true;
}

void Automation::printValue()
{
  Serial.print(F("\n"));
  Serial.print(deviceOn);
  Serial.print(F("\t"));
  Serial.print(keepDeviceOn);
}

void ChangeValueOnManualToAuto()
{
  uint8_t data[1] = {'0'};
  uint8_t *message = data;
  mqttClient.publish(allRelayOn_topic, message, len, false);
  mqttClient.publish(allRelayOff_topic, message, len, false);
  for (uint8_t i = 0; i < 16; i++)
  {
    device[i].setValueOnManualToAuto();
  }
  setValueOnManualToAutoFlag = false;
  Serial.print(F("\n"));
  Serial.print(F("\n"));
  Serial.print(F("Automation Turned ON..."));
  Serial.print(F("\n"));
}

void ChangeValueOnAutoToManual()
{
  for (uint8_t i = 0; i < 16; i++)
  {
    device[i].setDefaultValue();
  }
  setValueOnAutoTomanualFlag = false;
  Serial.print(F("\n"));
  Serial.print(F("\n"));
  Serial.print(F("Manual Control Turned ON..."));
  Serial.print(F("\n"));
}

void AllRelayOnButtonHandler()
{
  uint8_t data[1] = {'0'};
  uint8_t *message = data;

  if (allRelayOnButton_data_mQTT == 1)
  {
    mqttClient.publish(allRelayOn_topic, message, len, false);
  }
}

void AllRelayOffButtonHandler()
{
  uint8_t data[1] = {'0'};
  uint8_t *message = data;
  if (allRelayOffButton_data_mQTT == 1)
  {
    mqttClient.publish(allRelayOff_topic, message, len, false);
  }
}

void OutputConfig()
{
  for (uint8_t i = 0; i < (sizeof(output) / sizeof(output[0])); i++)
  {
    pinMode(output[i], OUTPUT);
  }
  for (uint8_t i = 0; i < (sizeof(output) / sizeof(output[0])); i++)
  {
    digitalWrite(output[i], OFF);
  }
}

void InputConfig()
{
  for (uint8_t i = 0; i < (sizeof(input) / sizeof(input[0])); i++)
  {
    pinMode(input[i], INPUT_PULLUP);
  }
}

void UpdateInputPinStatus()
{
  for (uint8_t i = 0; i < (sizeof(input) / sizeof(input[0])); i++)
  {
    input_status[i] = digitalRead(input[i]);
  }
}

PIRtoMQTT::PIRtoMQTT()
{
  _triggered = false;
}

void PIRtoMQTT::sendToMQTT(byte _inputPin, const char *_topic)
{
  byte _pinStatus = digitalRead(_inputPin);
  if (!_triggered)
  {
    if (_pinStatus == HIGH)
    {
      _triggered = true;
      uint8_t data[1] = {'1'};
      uint8_t *message = data;
      mqttClient.publish(_topic, message, 1, true);
    }
  }
  if (_triggered)
  {
    if (_pinStatus == LOW)
    {
      _triggered = false;
      uint8_t data[1] = {'0'};
      uint8_t *message = data;
      mqttClient.publish(_topic, message, 1, true);
    }
  }
}

void sendPirToMQTT()
{
  pirSensor[0].sendToMQTT(row0_sensor0, row0_sensor0_topic);
  pirSensor[1].sendToMQTT(row0_sensor1, row0_sensor1_topic);
  pirSensor[2].sendToMQTT(row0_sensor2, row0_sensor2_topic);
  pirSensor[3].sendToMQTT(row0_sensor3, row0_sensor3_topic);
  pirSensor[4].sendToMQTT(row0_sensor4, row0_sensor4_topic);
  pirSensor[5].sendToMQTT(row0_sensor5, row0_sensor5_topic);
  pirSensor[6].sendToMQTT(row0_sensor6, row0_sensor6_topic);
  pirSensor[7].sendToMQTT(row0_sensor7, row0_sensor7_topic);
  pirSensor[8].sendToMQTT(row0_sensor8, row0_sensor8_topic);
  pirSensor[9].sendToMQTT(row0_sensor9, row0_sensor9_topic);

  pirSensor[10].sendToMQTT(row1_sensor0, row1_sensor0_topic);
  pirSensor[11].sendToMQTT(row1_sensor1, row1_sensor1_topic);
  pirSensor[12].sendToMQTT(row1_sensor2, row1_sensor2_topic);
  pirSensor[13].sendToMQTT(row1_sensor3, row1_sensor3_topic);
  pirSensor[14].sendToMQTT(row1_sensor4, row1_sensor4_topic);
  pirSensor[15].sendToMQTT(row1_sensor5, row1_sensor5_topic);
  pirSensor[16].sendToMQTT(row1_sensor6, row1_sensor6_topic);

  pirSensor[17].sendToMQTT(row2_sensor0, row2_sensor0_topic);
  pirSensor[18].sendToMQTT(row2_sensor1, row2_sensor1_topic);
  pirSensor[19].sendToMQTT(row2_sensor2, row2_sensor2_topic);
  pirSensor[20].sendToMQTT(row2_sensor3, row2_sensor3_topic);
  pirSensor[21].sendToMQTT(row2_sensor4, row2_sensor4_topic);

  pirSensor[22].sendToMQTT(row3_sensor0, row3_sensor0_topic);
  pirSensor[23].sendToMQTT(row3_sensor1, row3_sensor1_topic);
  pirSensor[24].sendToMQTT(row3_sensor2, row3_sensor2_topic);
  pirSensor[25].sendToMQTT(row3_sensor3, row3_sensor3_topic);

  pirSensor[26].sendToMQTT(row4_sensor0, row4_sensor0_topic);
  pirSensor[27].sendToMQTT(row4_sensor1, row4_sensor1_topic);
  pirSensor[28].sendToMQTT(row4_sensor2, row4_sensor2_topic);
  pirSensor[29].sendToMQTT(row4_sensor3, row4_sensor3_topic);
  pirSensor[30].sendToMQTT(row4_sensor4, row4_sensor4_topic);
  pirSensor[31].sendToMQTT(row4_sensor5, row4_sensor5_topic);

  pirSensor[32].sendToMQTT(row5_sensor0, row5_sensor0_topic);
  pirSensor[33].sendToMQTT(row5_sensor1, row5_sensor1_topic);
  pirSensor[34].sendToMQTT(row5_sensor2, row5_sensor2_topic);
  pirSensor[35].sendToMQTT(row5_sensor3, row5_sensor3_topic);
  pirSensor[36].sendToMQTT(row5_sensor4, row5_sensor4_topic);
  pirSensor[37].sendToMQTT(row5_sensor5, row5_sensor5_topic);
  pirSensor[38].sendToMQTT(row5_sensor6, row5_sensor6_topic);

  pirSensor[39].sendToMQTT(washRoom0_sensor0, washRoom0_sensor0_topic);

  pirSensor[40].sendToMQTT(mainRoom_sensor, mainRoom_sensor_topic);

  pirSensor[41].sendToMQTT(washRoom1_sensor0, washRoom1_sensor0_topic);
  pirSensor[42].sendToMQTT(washRoom1_sensor1, washRoom1_sensor1_topic);
  pirSensor[43].sendToMQTT(washRoom1_sensor2, washRoom1_sensor2_topic);
  pirSensor[44].sendToMQTT(washRoom1_sensor3, washRoom1_sensor3_topic);
}

void PatternController()
{
  for (uint8_t i = 0; i < sizeof(patternFlag) / sizeof(patternFlag[0]); i++)
  {
    if (!patternFlag[i])
    {
      if (relayStatusPattern[i] == 1)
      {
        uint8_t data[1] = {'1'};
        uint8_t *message = data;
        if (relayStatusPattern[i] != relayStatusMQTT[i])
        {
          mqttClient.publish(subscriptionToics[i], message, len, true);
        }
      }
      else if (relayStatusPattern[i] == 0)
      {
        uint8_t data[1] = {'0'};
        uint8_t *message = data;
        if (relayStatusPattern[i] != relayStatusMQTT[i])
        {
          mqttClient.publish(subscriptionToics[i], message, len, true);
        }
      }
    }
  }
}
