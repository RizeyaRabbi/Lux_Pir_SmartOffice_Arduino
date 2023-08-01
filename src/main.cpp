// Library Includes
#include <PubSubClient.h>
#include <Ethernet.h>
#include <SPI.h>

// Private Includes
#include <Topics.h>
#include <EthernetCredentials.h>
#include <MQTTCredentials.h>
#include <MQTTData.h>
#include <Flags.h>
#include <GPIO.h>
#include <LogicLevel.h>

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

/*Manual Control from Web*/
void ManualControl();

/*Ethernet client Initialization*/
EthernetClient ethClient;

/*MQTT client Initialization over Ethernet*/
PubSubClient mqttClient(ethClient);

/*WashRoom0Relay0 Manual Control Function*/
void WashRoom0Relay0Controller();

/*WashRoom1Relay0 Manual Control Function*/
void WashRoom1Relay0Controller();

/*WashRoom1Relay1 Manual Control Function*/
void WashRoom1Relay1Controller();

/*Row0Relay0 Manual Control Function*/
void Row0Relay0Controller();

/*Row0Relay1 Manual Control Function*/
void Row0Relay1Controller();

/*Row1Relay0 Manual Control Function*/
void Row1Relay0Controller();

/*Row1Relay1 Manual Control Function*/
void Row1Relay1Controller();

/*Row2Relay0 Manual Control Function*/
void Row2Relay0Controller();

/*Row0Relay1 Manual Control Function*/
void Row2Relay1Controller();

/*Row3Relay0 Manual Control Function*/
void Row3Relay0Controller();

/*Row3Relay1 Manual Control Function*/
void Row3Relay1Controller();

/*Row4Relay0 Manual Control Function*/
void Row4Relay0Controller();

/*Row4Relay1 Manual Control Function*/
void Row4Relay1Controller();

/*Row5Relay0 Manual Control Function*/
void Row5Relay0Controller();

/*Row5Relay1 Manual Control Function*/
void Row5Relay1Controller();

/*MainRoomRelay0 Manual control Function*/
void MainRoomRelay0Controller();

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
  unsigned long waitTime, startInterval, startWaitTime, startTime, stopTime, debounceDelay,
      secondsInOneMinute, milliSecondsInOneSecond;
  bool deviceOn, keepDeviceOn;

public:
  Automation();
  void setDefaultValue();
  void setValueOnManualToAuto();
  void printValue();
  void controller(uint8_t *, const uint8_t *, const char *, float *, unsigned long);
  void controller(uint8_t *, uint8_t *, const uint8_t *, const char *, unsigned long);
  void controller(uint8_t *, uint8_t *, uint8_t *, const uint8_t *, const char *, unsigned long);
  void controller(uint8_t *, uint8_t *, uint8_t *, uint8_t *, const uint8_t *, const char *, unsigned long);
  void controller(uint8_t *, uint8_t *, uint8_t *, uint8_t *, uint8_t *, const uint8_t *, const char *, unsigned long);
  ~Automation();
};

/*Objects for Automation Class*/
Automation device[16];

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
  if (automation)
  {
    UpdateInputPinStatus();
    AutomaticControl();
    if (setValueOnManualToAutoFlag)
    {
      ChangeValueOnManualToAuto();
    }
  }
  if (!automation)
  {
    if (setValueOnAutoTomanualFlag)
    {
      ChangeValueOnAutoToManual();
    }
    ManualControl();
  }
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
  uint8_t payloadMessage = *payload - 48;
  if (strcmp(topic, luxSensor0_topic) == 0)
  {
    char payLoadBuffer[length];
    for (unsigned int i = 0; i < length; i++)
    {
      payLoadBuffer[i] = payload[i];
    }
    luxSensor0_data_mQTT = (float)atof(payLoadBuffer);
  }

  else if (strcmp(topic, allRelayOn_topic) == 0)
  {
    if (payloadMessage == 1)
    {
      len = length;
      allRelayOn = true;
      allRelayOnButton = true;
      allRelayOnButton_data_mQTT = 1;
    }
    if (payloadMessage == 0)
    {
      len = length;
      allRelayOn = false;
      allRelayOnButton = false;
      allRelayOnButton_data_mQTT = 0;
    }
  }
  else if (strcmp(topic, allRelayOff_topic) == 0)
  {
    if (payloadMessage == 1)
    {
      len = length;
      allRelayOff = true;
      allRelayOffButton = true;
      allRelayOffButton_data_mQTT = 1;
    }
    if (payloadMessage == 0)
    {
      len = length;
      allRelayOff = false;
      allRelayOffButton = false;
      allRelayOffButton_data_mQTT = 0;
    }
  }
  else if (strcmp(topic, automation_topic) == 0)
  {
    if (payloadMessage == 1)
    {
      automation = true;
      setValueOnManualToAutoFlag = true;
    }
    if (payloadMessage == 0)
    {
      automation = false;
      setValueOnAutoTomanualFlag = true;
    }
  }
  else if (strcmp(topic, washRoom0_devices_topic) == 0)
  {
    washRoom0_relay0_data_mQTT = payloadMessage;
    washRoom0_relay0_flag_mQTT = true;
  }
  else if (strcmp(topic, washRoom1_light_topic) == 0)
  {
    washRoom1_relay0_data_mQTT = payloadMessage;
    washRoom1_relay0_flag_mQTT = true;
  }
  else if (strcmp(topic, washRoom1_exhaust_topic) == 0)
  {
    washRoom1_relay1_data_mQTT = payloadMessage;
    washRoom1_relay1_flag_mQTT = true;
  }
  else if (strcmp(topic, row0_light0_topic) == 0)
  {
    row0_relay0_data_mQTT = payloadMessage;
    row0_relay0_flag_mQTT = true;
  }
  else if (strcmp(topic, row0_light1_topic) == 0)
  {
    row0_relay1_data_mQTT = payloadMessage;
    row0_relay1_flag_mQTT = true;
  }
  else if (strcmp(topic, mainRoomLight_topic) == 0)
  {
    mainRoom_relay0_data_mQTT = payloadMessage;
    mainRoom_relay0_flag_mQTT = true;
  }
  else if (strcmp(topic, row1_light0_topic) == 0)
  {
    row1_relay0_data_mQTT = payloadMessage;
    row1_relay0_flag_mQTT = true;
  }
  else if (strcmp(topic, row1_light1_topic) == 0)
  {
    row1_relay1_data_mQTT = payloadMessage;
    row1_relay1_flag_mQTT = true;
  }
  else if (strcmp(topic, row2_light0_topic) == 0)
  {
    row2_relay0_data_mQTT = payloadMessage;
    row2_relay0_flag_mQTT = true;
  }
  else if (strcmp(topic, row2_light1_topic) == 0)
  {
    row2_relay1_data_mQTT = payloadMessage;
    row2_relay1_flag_mQTT = true;
  }
  else if (strcmp(topic, row3_light0_topic) == 0)
  {
    row3_relay0_data_mQTT = payloadMessage;
    row3_relay0_flag_mQTT = true;
  }
  else if (strcmp(topic, row3_light1_topic) == 0)
  {
    row3_relay1_data_mQTT = payloadMessage;
    row3_relay1_flag_mQTT = true;
  }
  else if (strcmp(topic, row4_light0_topic) == 0)
  {
    row4_relay0_data_mQTT = payloadMessage;
    row4_relay0_flag_mQTT = true;
  }
  else if (strcmp(topic, row4_light1_topic) == 0)
  {
    row4_relay1_data_mQTT = payloadMessage;
    row4_relay1_flag_mQTT = true;
  }
  else if (strcmp(topic, row5_light0_topic) == 0)
  {
    row5_relay0_data_mQTT = payloadMessage;
    row5_relay0_flag_mQTT = true;
  }
  else if (strcmp(topic, row5_light1_topic) == 0)
  {
    row5_relay1_data_mQTT = payloadMessage;
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
      Serial.print(F("\n"));
      Serial.print(F("GPIO: "));
      Serial.print(_device);
      Serial.print(F(" Turned ON"));
    }
    else if (_pinStatus == ON)
    {
      Serial.print(F("\n"));
      Serial.print(F("GPIO: "));
      Serial.print(_device);
      Serial.print(F(" Already Turned ON!!!!!!!"));
    }
  }
  if (_mqttMessage == 0)
  {
    uint8_t _pinStatus = digitalRead(_device);
    if (_pinStatus == ON)
    {
      digitalWrite(_device, OFF);
      delay(100);
      Serial.print(F("\n"));
      Serial.print(F("GPIO: "));
      Serial.print(_device);
      Serial.print(F(" Turned OFF"));
    }
    else if (_pinStatus == OFF)
    {
      Serial.print(F("\n"));
      Serial.print(F("GPIO: "));
      Serial.print(_device);
      Serial.print(F(" Already Turned OFF!!!!!!!"));
    }
  }
}

void TopicSubscription()
{
  mqttClient.publish(deviceStatus_topic, "Connected", true);
  mqttClient.subscribe(automation_topic);
  mqttClient.subscribe(allRelayOn_topic);
  mqttClient.subscribe(allRelayOff_topic);
  mqttClient.subscribe(washRoom0_devices_topic);
  mqttClient.subscribe(washRoom1_light_topic);
  mqttClient.subscribe(washRoom1_exhaust_topic);
  mqttClient.subscribe(row0_light0_topic);
  mqttClient.subscribe(row0_light1_topic);
  mqttClient.subscribe(mainRoomLight_topic);
  mqttClient.subscribe(row1_light0_topic);
  mqttClient.subscribe(row1_light1_topic);
  mqttClient.subscribe(row2_light0_topic);
  mqttClient.subscribe(row2_light1_topic);
  mqttClient.subscribe(row3_light0_topic);
  mqttClient.subscribe(row3_light1_topic);
  mqttClient.subscribe(row4_light0_topic);
  mqttClient.subscribe(row4_light1_topic);
  mqttClient.subscribe(row5_light0_topic);
  mqttClient.subscribe(row5_light1_topic);
  mqttClient.subscribe(luxSensor0_topic);
}

void AllRelayOnAction()
{
  uint8_t data[1] = {'1'};
  uint8_t *message = data;
  uint8_t data1[1] = {'0'};
  uint8_t *message1 = data1;
  if (!allRelayOffButton)
  {
    Serial.print(F("\n"));
    Serial.print(F("AllRelayOff Button already turned OFF.."));
  }
  if (allRelayOffButton)
  {
    mqttClient.publish(allRelayOff_topic, message1, len, false);
    Serial.print(F("\n"));
    Serial.print(F("AllRelayOff Button turned OFF.."));
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
  if (!allRelayOnButton)
  {
    Serial.print(F("\n"));
    Serial.print(F("AllrelayOn Button already turned OFF..."));
  }
  if (allRelayOnButton)
  {
    mqttClient.publish(allRelayOn_topic, message, len, false);
    Serial.print(F("\n"));
    Serial.print(F("AllrelayOn Button turned OFF..."));
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
  // device[0].controller(&row0_sensor0_status, &row0_light0, "SmartOffice/2nd_Floor/Output/Row0/Relay0", 1);

  // /************************************ Row0 with 2 Outputs *************************************************/
  // device[0].controller(&row0_sensor0_status, &row0_sensor1_status, &row0_sensor2_status, &row0_sensor3_status, &row0_sensor4_status, &row0_light0, row0_light0_topic, deviceDelay);
  // device[1].controller(&row0_sensor5_status, &row0_sensor6_status, &row0_sensor7_status, &row0_sensor8_status, &row0_sensor9_status, &row0_light1, row0_light1_topic, deviceDelay);
  // /**********************************************************************************************************/

  // /************************************ Row1 with 2 Outputs *************************************************/
  // device[2].controller(&row1_sensor0_status, &row1_sensor1_status, &row1_sensor2_status, &row1_sensor3_status, &row1_light0, row1_light0_topic, deviceDelay);
  // device[3].controller(&row1_sensor4_status, &row1_sensor5_status, &row1_sensor6_status, &row1_light1, row1_light1_topic, deviceDelay);
  // /**********************************************************************************************************/

  // /************************************ Row2 and Row3 with 2 outputs(Row3) **********************************/
  // device[4].controller(&row2_sensor0_status, &row2_sensor1_status, &row3_sensor0_status, &row3_sensor1_status, &row3_light0, row3_light0_topic, deviceDelay);
  // device[5].controller(&row2_sensor2_status, &row2_sensor3_status, &row2_sensor4_status, &row3_sensor2_status, &row3_sensor3_status, &row3_light1, row3_light1_topic, deviceDelay);
  // /**********************************************************************************************************/

  // /************************************ Row4 with 2 Outputs *************************************************/
  // device[6].controller(&row4_sensor0_status, &row4_sensor1_status, &row4_sensor2_status, &row4_light0, row4_light0_topic, deviceDelay);
  // device[7].controller(&row4_sensor3_status, &row4_sensor4_status, &row4_sensor5_status, &row4_light1, row4_light1_topic, deviceDelay);
  // /**********************************************************************************************************/

  // /************************************ Row5 with 2 Outputs *************************************************/
  // device[8].controller(&row5_sensor0_status, &row5_sensor1_status, &row5_sensor2_status, &row5_light0, row5_light0_topic, deviceDelay);
  // device[9].controller(&row5_sensor3_status, &row5_sensor4_status, &row5_sensor5_status, &row5_sensor6_status, &row5_light1, row5_light1_topic, deviceDelay);
  // /**********************************************************************************************************/

  /************************************ MainRoom Light single Output ****************************************/
  device[10].controller(&mainRoom_sensor_status, &mainRoomLight, mainRoomLight_topic, &luxSensor0_data_mQTT, deviceDelay);
  /**********************************************************************************************************/

  /************************************ WashRoom0 single Output *********************************************/
  // device[11].controller(&washRoom0_sensor0_status, &washRoom0_devices, washRoom0_devices_topic, deviceDelay);
  // /**********************************************************************************************************/

  // /************************************ WashRoom1 with 2 Output *********************************************/
  // device[12].controller(&washRoom1_sensor0_status, &washRoom1_sensor1_status, &washRoom1_sensor2_status, &washRoom1_sensor3_status, &washRoom1_light, washRoom1_light_topic, deviceDelay);
  // device[13].controller(&washRoom1_sensor2_status, &washRoom1_sensor3_status, &washRoom1_exhaust, washRoom1_exhaust_topic, deviceDelay);
  /**********************************************************************************************************/

  // WashRoom0Relay0Controller();
  // WashRoom1Relay0Controller();
  // WashRoom1Relay1Controller();
  MainRoomRelay0Controller();
  // Row0Relay0Controller();
  // Row0Relay1Controller();
  // Row1Relay0Controller();
  // Row1Relay1Controller();
  // Row2Relay0Controller();
  // Row2Relay1Controller();
  // Row3Relay0Controller();
  // Row3Relay1Controller();
  // Row4Relay0Controller();
  // Row4Relay1Controller();
  // Row5Relay0Controller();
  // Row5Relay1Controller();
}

void ManualControl()
{
  if (allRelayOn)
  {
    AllRelayOnAction();
  }
  if (allRelayOff)
  {
    AllRelayOffAction();
  }
  WashRoom0Relay0Controller();
  WashRoom1Relay0Controller();
  WashRoom1Relay1Controller();
  MainRoomRelay0Controller();
  Row0Relay0Controller();
  Row0Relay1Controller();
  Row1Relay0Controller();
  Row1Relay1Controller();
  Row2Relay0Controller();
  Row2Relay1Controller();
  Row3Relay0Controller();
  Row3Relay1Controller();
  Row4Relay0Controller();
  Row4Relay1Controller();
  Row5Relay0Controller();
  Row5Relay1Controller();
}

void WashRoom0Relay0Controller()
{
  if (washRoom0_relay0_flag_mQTT)
  {
    Controller(washRoom0_relay0_data_mQTT, washRoom0_devices);
    washRoom0_relay0_flag_mQTT = false;
    if (washRoom0_relay0_data_mQTT == 1)
    {
      AllRelayOffButtonHandler();
    }
    else if (washRoom0_relay0_data_mQTT == 0)
    {
      AllRelayOnButtonHandler();
    }
  }
}

void WashRoom1Relay0Controller()
{
  if (washRoom1_relay0_flag_mQTT)
  {
    Controller(washRoom1_relay0_data_mQTT, washRoom1_light);
    washRoom1_relay0_flag_mQTT = false;
    if (washRoom1_relay0_data_mQTT == 1)
    {
      AllRelayOffButtonHandler();
    }
    else if (washRoom1_relay0_data_mQTT == 0)
    {
      AllRelayOnButtonHandler();
    }
  }
}

void WashRoom1Relay1Controller()
{
  if (washRoom1_relay1_flag_mQTT)
  {
    Controller(washRoom1_relay1_data_mQTT, washRoom1_exhaust);
    washRoom1_relay1_flag_mQTT = false;
    if (washRoom1_relay1_data_mQTT == 1)
    {
      AllRelayOffButtonHandler();
    }
    else if (washRoom1_relay1_data_mQTT == 0)
    {
      AllRelayOnButtonHandler();
    }
  }
}

void MainRoomRelay0Controller()
{
  if (mainRoom_relay0_flag_mQTT)
  {
    Controller(mainRoom_relay0_data_mQTT, mainRoomLight);
    mainRoom_relay0_flag_mQTT = false;
    if (mainRoom_relay0_data_mQTT == 1)
    {
      AllRelayOffButtonHandler();
    }
    else if (mainRoom_relay0_data_mQTT == 0)
    {
      AllRelayOnButtonHandler();
    }
  }
}

void Row0Relay0Controller()
{
  if (row0_relay0_flag_mQTT)
  {
    Controller(row0_relay0_data_mQTT, row0_light0);
    row0_relay0_flag_mQTT = false;
    if (row0_relay0_data_mQTT == 1)
    {
      AllRelayOffButtonHandler();
    }
    else if (row0_relay0_data_mQTT == 0)
    {
      AllRelayOnButtonHandler();
    }
  }
}

void Row0Relay1Controller()
{
  if (row0_relay1_flag_mQTT)
  {
    Controller(row0_relay1_data_mQTT, row0_light1);
    row0_relay1_flag_mQTT = false;
    if (row0_relay1_data_mQTT == 1)
    {
      AllRelayOffButtonHandler();
    }
    else if (row0_relay1_data_mQTT == 0)
    {
      AllRelayOnButtonHandler();
    }
  }
}

void Row1Relay0Controller()
{
  if (row1_relay0_flag_mQTT)
  {
    Controller(row1_relay0_data_mQTT, row1_light0);
    row1_relay0_flag_mQTT = false;
    if (row1_relay0_data_mQTT == 1)
    {
      AllRelayOffButtonHandler();
    }
    else if (row1_relay0_data_mQTT == 0)
    {
      AllRelayOnButtonHandler();
    }
  }
}

void Row1Relay1Controller()
{
  if (row1_relay1_flag_mQTT)
  {
    Controller(row1_relay1_data_mQTT, row1_light1);
    row1_relay1_flag_mQTT = false;
    if (row1_relay1_data_mQTT == 1)
    {
      AllRelayOffButtonHandler();
    }
    else if (row1_relay1_data_mQTT == 0)
    {
      AllRelayOnButtonHandler();
    }
  }
}

void Row2Relay0Controller()
{
  if (row2_relay0_flag_mQTT)
  {
    Controller(row2_relay0_data_mQTT, row2_light0);
    row2_relay0_flag_mQTT = false;
    if (row2_relay0_data_mQTT == 1)
    {
      AllRelayOffButtonHandler();
    }
    else if (row2_relay0_data_mQTT == 0)
    {
      AllRelayOnButtonHandler();
    }
  }
}

void Row2Relay1Controller()
{
  if (row2_relay1_flag_mQTT)
  {
    Controller(row2_relay1_data_mQTT, row2_light1);
    row2_relay1_flag_mQTT = false;
    if (row2_relay1_data_mQTT == 1)
    {
      AllRelayOffButtonHandler();
    }
    else if (row2_relay1_data_mQTT == 0)
    {
      AllRelayOnButtonHandler();
    }
  }
}

void Row3Relay0Controller()
{
  if (row3_relay0_flag_mQTT)
  {
    Controller(row3_relay0_data_mQTT, row3_light0);
    row3_relay0_flag_mQTT = false;
    if (row3_relay0_data_mQTT == 1)
    {
      AllRelayOffButtonHandler();
    }
    else if (row3_relay0_data_mQTT == 0)
    {
      AllRelayOnButtonHandler();
    }
  }
}

void Row3Relay1Controller()
{
  if (row3_relay1_flag_mQTT)
  {
    Controller(row3_relay1_data_mQTT, row3_light1);
    row3_relay1_flag_mQTT = false;
    if (row3_relay1_data_mQTT == 1)
    {
      AllRelayOffButtonHandler();
    }
    else if (row3_relay1_data_mQTT == 0)
    {
      AllRelayOnButtonHandler();
    }
  }
}

void Row4Relay0Controller()
{
  if (row4_relay0_flag_mQTT)
  {
    Controller(row4_relay0_data_mQTT, row4_light0);
    row4_relay0_flag_mQTT = false;
    if (row4_relay0_data_mQTT == 1)
    {
      AllRelayOffButtonHandler();
    }
    else if (row4_relay0_data_mQTT == 0)
    {
      AllRelayOnButtonHandler();
    }
  }
}

void Row4Relay1Controller()
{
  if (row4_relay1_flag_mQTT)
  {
    Controller(row4_relay1_data_mQTT, row4_light1);
    row4_relay1_flag_mQTT = false;
    if (row4_relay1_data_mQTT == 1)
    {
      AllRelayOffButtonHandler();
    }
    else if (row4_relay1_data_mQTT == 0)
    {
      AllRelayOnButtonHandler();
    }
  }
}

void Row5Relay0Controller()
{
  if (row5_relay0_flag_mQTT)
  {
    Controller(row5_relay0_data_mQTT, row5_light0);
    row5_relay0_flag_mQTT = false;
    if (row5_relay0_data_mQTT == 1)
    {
      AllRelayOffButtonHandler();
    }
    else if (row5_relay0_data_mQTT == 0)
    {
      AllRelayOnButtonHandler();
    }
  }
}

void Row5Relay1Controller()
{
  if (row5_relay1_flag_mQTT)
  {
    Controller(row5_relay1_data_mQTT, row5_light1);
    row5_relay1_flag_mQTT = false;
    if (row5_relay1_data_mQTT == 1)
    {
      AllRelayOffButtonHandler();
    }
    else if (row5_relay1_data_mQTT == 0)
    {
      AllRelayOnButtonHandler();
    }
  }
}

Automation::Automation()
{
  startInterval = 0UL;
  debounceDelay = 800UL;
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
      }
      if (digitalRead(*outputPin) == ON)
      {
        Serial.print(F("\n"));
        Serial.print(F("Already Turned ON..."));
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

void Automation::controller(uint8_t *sensorStatus0, uint8_t *sensorStatus1, const uint8_t *outputPin, const char *topic, unsigned long waitTimeInMinute)
{
  waitTime = waitTimeInMinute * secondsInOneMinute * milliSecondsInOneSecond;
  UpdateInputPinStatus();
  if (!deviceOn)
  {
    if (*sensorStatus0 == 1 || *sensorStatus1 == 1)
    {
      uint8_t data[1] = {'1'};
      uint8_t *message = data;
      if (digitalRead(*outputPin) == OFF)
      {
        mqttClient.publish(topic, message, 1, true);
      }
      if (digitalRead(*outputPin) == ON)
      {
        Serial.print(F("\n"));
        Serial.print(F("Already Turned ON..."));
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

void Automation::controller(uint8_t *sensorStatus0, uint8_t *sensorStatus1, uint8_t *sensorStatus2, const uint8_t *outputPin, const char *topic, unsigned long waitTimeInMinute)
{
  waitTime = waitTimeInMinute * secondsInOneMinute * milliSecondsInOneSecond;
  UpdateInputPinStatus();
  if (!deviceOn)
  {
    if (*sensorStatus0 == 1 || *sensorStatus1 == 1 || *sensorStatus2 == 1)
    {
      uint8_t data[1] = {'1'};
      uint8_t *message = data;
      if (digitalRead(*outputPin) == OFF)
      {
        mqttClient.publish(topic, message, 1, true);
      }
      if (digitalRead(*outputPin) == ON)
      {
        Serial.print(F("\n"));
        Serial.print(F("Already Turned ON..."));
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
    if (*sensorStatus0 == 0 && *sensorStatus1 == 0 && *sensorStatus2 == 0 && (millis() - startWaitTime >= waitTime))
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

void Automation::controller(uint8_t *sensorStatus0, uint8_t *sensorStatus1, uint8_t *sensorStatus2, uint8_t *sensorStatus3, const uint8_t *outputPin, const char *topic, unsigned long waitTimeInMinute)
{
  waitTime = waitTimeInMinute * secondsInOneMinute * milliSecondsInOneSecond;
  UpdateInputPinStatus();
  if (!deviceOn)
  {
    if (*sensorStatus0 == 1 || *sensorStatus1 == 1 || *sensorStatus2 == 1 || *sensorStatus3 == 1)
    {
      uint8_t data[1] = {'1'};
      uint8_t *message = data;
      if (digitalRead(*outputPin) == OFF)
      {
        mqttClient.publish(topic, message, 1, true);
      }
      if (digitalRead(*outputPin) == ON)
      {
        Serial.print(F("\n"));
        Serial.print(F("Already Turned ON..."));
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
    if (*sensorStatus0 == 0 && *sensorStatus1 == 0 && *sensorStatus2 == 0 && *sensorStatus3 == 0 && (millis() - startWaitTime >= waitTime))
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

void Automation::controller(uint8_t *sensorStatus0, uint8_t *sensorStatus1, uint8_t *sensorStatus2, uint8_t *sensorStatus3, uint8_t *sensorStatus4, const uint8_t *outputPin, const char *topic, unsigned long waitTimeInMinute)
{
  waitTime = waitTimeInMinute * secondsInOneMinute * milliSecondsInOneSecond;
  UpdateInputPinStatus();
  if (!deviceOn)
  {
    if (*sensorStatus0 == 1 || *sensorStatus1 == 1 || *sensorStatus2 == 1 || *sensorStatus3 == 1 || *sensorStatus4 == 1)
    {
      uint8_t data[1] = {'1'};
      uint8_t *message = data;
      if (digitalRead(*outputPin) == OFF)
      {
        mqttClient.publish(topic, message, 1, true);
      }
      if (digitalRead(*outputPin) == ON)
      {
        Serial.print(F("\n"));
        Serial.print(F("Already Turned ON..."));
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
    if (*sensorStatus0 == 0 && *sensorStatus1 == 0 && *sensorStatus2 == 0 && *sensorStatus3 == 0 && *sensorStatus4 == 0 && (millis() - startWaitTime >= waitTime))
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
  Serial.print(F("\n"));
  Serial.print(F("setValueOnAutoToManual::"));
  Serial.print(F(" Objects Value Set To Default.."));
  startInterval = 0UL;
  debounceDelay = 800UL;
  secondsInOneMinute = 60UL;
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
    Serial.print(F("\n"));
    Serial.print(F("AllrelayOn Button turned OFF..."));
  }
  else if (allRelayOnButton_data_mQTT == 0)
  {
    Serial.print(F("\n"));
    Serial.print(F("AllRelayOn Button already turned OFF.."));
  }
}

void AllRelayOffButtonHandler()
{
  uint8_t data[1] = {'0'};
  uint8_t *message = data;
  if (allRelayOffButton_data_mQTT == 1)
  {
    mqttClient.publish(allRelayOff_topic, message, len, false);
    Serial.print(F("\n"));
    Serial.print(F("AllRelayOff Button turned OFF.."));
  }
  else if (allRelayOffButton_data_mQTT == 0)
  {
    Serial.print(F("\n"));
    Serial.print(F("AllRelayOff Button already turned OFF.."));
  }
}
