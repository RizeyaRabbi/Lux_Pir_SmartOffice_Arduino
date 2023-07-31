#ifndef TOPICS_H
#define TOPICS_H

/*MQTT Topics*/
const char *row0_light0_topic = "SmartOffice/2nd_Floor/Output/Row0/Relay0";
const char *row0_light1_topic = "SmartOffice/2nd_Floor/Output/Row0/Relay1";
const char *row1_light0_topic = "SmartOffice/2nd_Floor/Output/Row1/Relay0";
const char *row1_light1_topic = "SmartOffice/2nd_Floor/Output/Row1/Relay1";
const char *row2_light0_topic = "SmartOffice/2nd_Floor/Output/Row2/Relay0";
const char *row2_light1_topic = "SmartOffice/2nd_Floor/Output/Row2/Relay1";
const char *row3_light0_topic = "SmartOffice/2nd_Floor/Output/Row3/Relay0";
const char *row3_light1_topic = "SmartOffice/2nd_Floor/Output/Row3/Relay1";
const char *row4_light0_topic = "SmartOffice/2nd_Floor/Output/Row4/Relay0";
const char *row4_light1_topic = "SmartOffice/2nd_Floor/Output/Row4/Relay1";
const char *row5_light0_topic = "SmartOffice/2nd_Floor/Output/Row5/Relay0";
const char *row5_light1_topic = "SmartOffice/2nd_Floor/Output/Row5/Relay1";
const char *mainRoomLight_topic = "SmartOffice/2nd_Floor/Output/Row0/Relay2";
const char *washRoom0_devices_topic = "SmartOffice/2nd_Floor/Output/WashRoom0/Relay0";
const char *washRoom1_light_topic = "SmartOffice/2nd_Floor/Output/WashRoom1/Relay0";
const char *washRoom1_exhaust_topic = "SmartOffice/2nd_Floor/Output/WashRoom1/Relay1";
const char *allRelayOn_topic = "SmartOffice/2nd_Floor/Output/AllRelay/ON";
const char *allRelayOff_topic = "SmartOffice/2nd_Floor/Output/AllRelay/OFF";
const char *automation_topic = "SmartOffice/2nd_Floor/Output/AllRelay/Automation";
const char *deviceStatus_topic = "SmartOffice/2nd_Floor/DeviceStatus/Output/ArduinoEthernetRelay";
const char *luxSensor0_topic = "SmartOffice/2nd_Floor/Input/LuxSensor/Row0/Sensor0";

#endif